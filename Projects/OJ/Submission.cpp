#include "Settings.hpp"
#include "ProblemList.hpp"
#include "Submission.hpp"
#include "Utilities.hpp"
#include <fstream>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <sys/ptrace.h>
#include <sys/resource.h>

SUBMISSION::SUBMISSION() {}
SUBMISSION::SUBMISSION(std::string Source, std::string ProblemID)
{
    Logger.SetLogFileName(Settings.GetBaseFolder() + "/Submission.log");
    UpdateAllResults(JUDGE_RESULT::WAITING);
    this->Source = Source;
    this->ProblemID = ProblemID;
    Score = 0;
    TestGroupsPassed = 0;
    if (!ProblemList.GetProblem(ProblemID, this->Problem))
    {
        UpdateAllResults(JUDGE_RESULT::REJECTED);
        this->Description = "Problem not found";
    }
    if (Source.length() > 1024 * 1024)
    {
        UpdateAllResults(JUDGE_RESULT::REJECTED);
        this->Description = "Source is too long";
    }
}
SUBMISSION::~SUBMISSION() {}

void SUBMISSION::UpdateWorkDir()
{
    WorkDir = Settings.GetSubmissionBaseFolder() + "/" + std::to_string(ID);
    if (!Utilities.MakeDir(WorkDir))
        Logger.Error("Can not remake work dir \"" + WorkDir + "\"");
    else
        Logger.SetLogFileName(WorkDir + "/Log.log");
}
void SUBMISSION::UpdateAllResults(JUDGE_RESULT Result)
{
    this->Result = Result;
    for (size_t i = 0; i < TestGroups.size(); i++)
        TestGroups[i].UpdateAllResults(Result);
    Save();
}
void SUBMISSION::CopyTestGroups()
{
    TestGroups = Problem.GetTestGroups();
    for (size_t i = 0; i < TestGroups.size(); i++)
    {
        TestGroups[i].ID = i;
        TestGroups[i].SubmissionID = std::to_string(ID);
        TestGroups[i].UpdateWorkDir();
    }
    Logger.Info("Copied " + std::to_string(TestGroups.size()) + " test groups");
    if (TestGroups.size() == 0)
    {
        UpdateAllResults(JUDGE_RESULT::REJECTED);
        Description = "No test groups";
        Logger.Warning("No test groups");
    }
}
bool SUBMISSION::RedirectIO()
{
    if (freopen((WorkDir + "/main.log").c_str(), "w", stdout) == nullptr)
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not open output data file";
        Logger.Error("Can not open output data file \"main.log\"");
        return false;
    }
    Logger.Info("Redirected stdout to \"main.log\"");

    if (freopen((WorkDir + "/main.log").c_str(), "w", stderr) == nullptr)
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not open error data file";
        Logger.Error("Can not open error data file \"main.log\"");
        return false;
    }
    Logger.Info("Redirected stderr to \"main.log\"");

    return true;
}
bool SUBMISSION::SetupEnvrionment()
{
    const std::string DirsToMake[7] = {
        "./root",
        "./usr",
        "./etc",
        "./etc/alternatives",
        "./proc",
        "./tmp",
        "./dev"};
    for (int i = 0; i < 7; i++)
    {
        if (mkdir(DirsToMake[i].c_str(), 0755) == -1)
        {
            UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
            Description = "Can not create dir for the new root";
            Logger.Error("Can not create dir " + DirsToMake[i] + " for the new root");
            return false;
        }
        Logger.Info("Create dir \"" + DirsToMake[i] + "\" for the new root");
    }

    if (chown("./root", Settings.GetJudgeUserID(), Settings.GetJudgeUserGroupID()) == -1)
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not change the owner of the new root";
        Logger.Error("Can not change the owner of the new root ./root");
        return false;
    }
    Logger.Info("Changed the owner of the new root ./root");

    if (chown("./tmp", Settings.GetJudgeUserID(), Settings.GetJudgeUserGroupID()) == -1)
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not change the owner of the new root";
        Logger.Error("Can not change the owner of the new root ./tmp");
        return false;
    }
    Logger.Info("Changed the owner of the new root ./tmp");

    if (mount("/usr", "./usr", "ext4", MS_BIND, nullptr) == -1)
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not mount the new root";
        Logger.Error("Can not mount the new root ./usr");
        return false;
    }
    Logger.Info("Mounted ./usr");

    if (mount("/usr", "./usr", "ext4", MS_BIND | MS_REMOUNT | MS_RDONLY, nullptr) == -1)
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not remount the new root";
        Logger.Error("Can not remount the new root ./usr");
        return false;
    }
    Logger.Info("Remounted ./usr");

    if (mount("/proc", "./proc", "proc", MS_BIND, nullptr) == -1)
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not mount the new root";
        Logger.Error("Can not mount the new root ./proc");
        return false;
    }
    Logger.Info("Mounted ./proc");

    if (mount("/dev", "./dev", "devtmpfs", MS_BIND, nullptr) == -1)
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not mount the new root";
        Logger.Error("Can not mount the new root ./dev");
        return false;
    }
    Logger.Info("Mounted ./dev");

    if (mount("/dev", "./dev", "devtmpfs", MS_BIND | MS_REMOUNT | MS_RDONLY, nullptr) == -1)
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not remount the new root";
        Logger.Error("Can not remount the new root ./dev");
        return false;
    }
    Logger.Info("Remounted ./dev");

    const std::string DirsToLink[5] = {
        "bin",
        "lib",
        "lib32",
        "libx32",
        "lib64"};
    for (int i = 0; i < 5; i++)
    {
        if (symlink(("/usr/" + DirsToLink[i]).c_str(), DirsToLink[i].c_str()) == -1)
        {
            UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
            Description = "Can not create symlink for the new root";
            Logger.Error("Can not create symlink for the new root " + DirsToLink[i]);
            return false;
        }
        Logger.Info("Created symlink for the new root " + DirsToLink[i]);
    }

    if (!Utilities.CopyDir("/etc/alternatives", "./etc/alternatives"))
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not copy alternatives for the new root";
        Logger.Error("Can not copy alternatives for the new root");
        return false;
    }

    if (chroot(WorkDir.c_str()) != 0)
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not change root dir";
        Logger.Error("Can not change root dir " + WorkDir);
        return false;
    }
    Logger.SetLogFileName("Log.log");
    Logger.Info("Changed root dir to " + WorkDir);

    Logger.Warning("Environment setted");

    return true;
}
bool SUBMISSION::RemoveEnvrionment()
{
    if (chdir(WorkDir.c_str()) == -1)
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not change directory";
        Logger.Error("Can not change directory to " + WorkDir);
        return false;
    }

    const std::string DirsToUmount[4] = {
        "usr",
        "proc",
        "dev",
        "usr"};
    for (int i = 0; i < 4; i++)
        if (umount(DirsToUmount[i].c_str()) == -1)
            Logger.Warning("Can not unmount directory " + DirsToUmount[i]);
        else
            Logger.Info("Unmounted " + DirsToUmount[i]);

    const std::string FilesToRemove[5] = {
        "bin",
        "lib",
        "lib32",
        "lib64",
        "libx32"};
    for (int i = 0; i < 5; i++)
        if (remove(FilesToRemove[i].c_str()) == -1)
            Logger.Warning("Can not remove file " + FilesToRemove[i]);
        else
            Logger.Info("Removed file \"" + FilesToRemove[i] + "\"");

    const std::string DirsToRemove[6] = {
        "root",
        "etc",
        "dev",
        "proc",
        "tmp",
        "usr"};
    for (int i = 0; i < 6; i++)
        if (!Utilities.RemoveDir(DirsToRemove[i].c_str()))
            Logger.Warning("Can not remove directory " + DirsToRemove[i]);
        else
            Logger.Info("Removed directory \"" + DirsToRemove[i] + "\"");

    Logger.Warning("Environment removed");

    return true;
}
bool SUBMISSION::ChangeUser()
{
    while (setgid(Settings.GetJudgeUserGroupID()) != 0)
        sleep(1);
    while (setuid(Settings.GetJudgeUserID()) != 0)
        sleep(1);
    while (setresuid(Settings.GetJudgeUserID(),
                     Settings.GetJudgeUserID(),
                     Settings.GetJudgeUserID()) != 0)
        sleep(1);
    while (setresgid(Settings.GetJudgeUserGroupID(),
                     Settings.GetJudgeUserGroupID(),
                     Settings.GetJudgeUserGroupID()) != 0)
        sleep(1);
    Logger.Info("Changed uid to " + std::to_string(Settings.GetJudgeUserID()) + " and gid to " + std::to_string(Settings.GetJudgeUserGroupID()));

    return true;
}
bool SUBMISSION::SetLimits()
{
    int TimeLimit = Settings.GetCompileTimeLimit();
    int OutputLimit = Settings.GetCompileOutputLimit();
    struct rlimit Limit;
    Limit.rlim_cur = Limit.rlim_max = TimeLimit + 1;
    if (setrlimit(RLIMIT_CPU, &Limit))
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not set cpu limit";
        Logger.Error("Can not set cpu limit");
        return false;
    }
    Logger.Info("Set cpu limit to " + std::to_string(TimeLimit + 1));

    if (alarm(ceil(TimeLimit / 1000.0) + 1) != 0)
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not set alarm";
        Logger.Error("Can not set alarm to " + std::to_string(ceil(TimeLimit / 1000.0) + 1));
        return false;
    }
    Logger.Info("Set alarm to " + std::to_string(ceil(TimeLimit / 1000.0) + 1));

    Limit.rlim_max = OutputLimit + 1024 * 1024;
    Limit.rlim_cur = OutputLimit;
    if (setrlimit(RLIMIT_FSIZE, &Limit))
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not set file size limit";
        Logger.Error("Can not set file size limit");
        return false;
    }
    Logger.Info("Set file size limit to " + std::to_string(OutputLimit));

    Limit.rlim_max = Limit.rlim_cur = 0;
    if (setrlimit(RLIMIT_CORE, &Limit))
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not set core limit";
        Logger.Error("Can not set core limit");
        return false;
    }
    Logger.Info("Set core limit to 0");

    return true;
}
void SUBMISSION::ChildProcess()
{
    Logger.Info("Entered child process");

    std::vector<std::string> CompileCommands = {Settings.GetCompiler(),
                                                "-fno-diagnostics-color",
                                                "-fno-asm",
                                                "-w",
                                                "-lm",
                                                "-fmax-errors=1",
                                                "-std=c++14",
                                                EnableO2 ? "-O2" : "-O1",
                                                "--static",
                                                "-DONLINE_JUDGE",
                                                "-o",
                                                "/main",
                                                "/main.cpp"};

    if (nice(19) != 19)
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not change nice value";
        Logger.Error("Can not change nice value to 19");
        return;
    }
    Logger.Info("Changed nice value to 19");

    if (chdir(WorkDir.c_str()) == -1)
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not change to work dir";
        Logger.Error("Can not change to work dir " + WorkDir);
        return;
    }
    Logger.Info("Changed to work dir \"" + WorkDir + "\"");

    if (!RedirectIO() || !SetupEnvrionment() || !ChangeUser() || !SetLimits())
        return;

    char **CompileArguments = new char *[CompileCommands.size() + 1];
    for (size_t i = 0; i < CompileCommands.size(); i++)
    {
        CompileArguments[i] = (char *)CompileCommands[i].c_str();
        Logger.Debug("Compile argument " + std::to_string(i) + ": \"" + CompileArguments[i] + "\"");
    }
    CompileArguments[CompileCommands.size()] = nullptr;
    // execlp("ls", "ls", "-l", "/usr/lib/gcc/x86_64-linux-gnu/9/", nullptr);
    execvp(Settings.GetCompiler().c_str(), CompileArguments);

    UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
    Description = "Can not execute program";
    Logger.Error("Can not execute program");
}
void SUBMISSION::ParentProcess()
{
    while (1)
    {
        int Status;
        struct rusage Usage;
        if (wait4(PID, &Status, 0, &Usage) == -1)
        {
            UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
            Description = "Can not wait for child process";
            Logger.Error("Can not wait for child process");
            ptrace(PTRACE_KILL, PID, nullptr, nullptr);
            return;
        }
        if (WIFEXITED(Status) || WIFSIGNALED(Status) || WIFSTOPPED(Status))
        {
            return;
        }
    }
}
bool SUBMISSION::CreateFiles()
{
    std::ofstream LogFile(WorkDir + "/main.log");
    if (!LogFile.is_open())
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not open data file";
        Logger.Error("Can not open data file \"/main.log\"");
        return false;
    }
    LogFile.close();
    Logger.Info("Output file created");

    if (chown((WorkDir + "/main.log").c_str(), Settings.GetJudgeUserID(), Settings.GetJudgeUserGroupID()) == -1)
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not change group of compile log file";
        Logger.Error("Can not change group of compile log file \"main.log\"");
        return false;
    }
    Logger.Info("Changed group of compile log file \"main.log\"");

    if (chmod((WorkDir + "/main.log").c_str(), 0760) == -1)
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not change permission of compile log file";
        Logger.Error("Can not change permission of compile log file \"main.log\"");
        return false;
    }
    Logger.Info("Changed permission of compile log file \"main.log\"");

    std::ofstream OutputFile(WorkDir + "/main");
    if (!OutputFile.is_open())
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not open data file";
        Logger.Error("Can not open data file \"/main\"");
        return false;
    }
    OutputFile.close();
    Logger.Info("Output file created");

    if (chown((WorkDir + "/main").c_str(), Settings.GetJudgeUserID(), Settings.GetJudgeUserGroupID()) == -1)
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not change group of compile output file";
        Logger.Error("Can not change group of compile output file \"main\"");
        return false;
    }
    Logger.Info("Changed group of compile output file \"main\"");

    if (chmod((WorkDir + "/main").c_str(), 0760) == -1)
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not change permission of compile output file";
        Logger.Error("Can not change permission of compile output file \"main\"");
        return false;
    }
    Logger.Info("Changed permission of compile output file \"main\"");

    return true;
}
void SUBMISSION::Compile()
{
    Logger.Info("Start compiling submission " + std::to_string(ID));
    UpdateAllResults(JUDGE_RESULT::COMPILING);

    if (!CreateFiles())
        return;

    pid_t PID = fork();
    if (PID == 0)
    {
        ChildProcess();
        exit(0);
    }
    else
    {
        this->PID = PID;
        ParentProcess();
        RemoveEnvrionment();
        if (Result != JUDGE_RESULT::COMPILING)
            return;

        struct stat OutputFileStatus;

        if (stat((WorkDir + "/main").c_str(), &OutputFileStatus) < 0)
        {
            UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
            Description = "Can not open check compile output file status";
            Logger.Error("Can not open check compile output file \"" + WorkDir + "/main.log\" status");
            return;
        }
        if (OutputFileStatus.st_size != 0)
        {
            UpdateAllResults(JUDGE_RESULT::COMPILED);
            Logger.Info("Submission " + std::to_string(ID) + " compiled successfully");
            return;
        }

        std::ifstream CompileLog(WorkDir + "/main.log");
        if (!CompileLog.is_open())
        {
            UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
            Description = "Can not open compile output log file";
            Logger.Error("Can not open compile output log file \"" + WorkDir + "/main.log\"");
            return;
        }

        std::string CompileResult;
        std::string Line;
        while (getline(CompileLog, Line))
            CompileResult += Line + "\n";
        CompileLog.close();

        if (CompileResult == "")
        {
            UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
            Description = "Compiler output log file is empty but compile failed";
            Logger.Error("Compiler output log file \"" + WorkDir + "/main.log\" is empty but compile failed");
            return;
        }
        UpdateAllResults(JUDGE_RESULT::COMPILATION_ERROR);
        Description = CompileResult;
        Logger.Info("Submission " + std::to_string(ID) + " compile failed");
    }
}
void SUBMISSION::RunTestGroups()
{
    if (Result != JUDGE_RESULT::COMPILED)
    {
        Logger.Warning("Can not compare test case because it is not compiled");
        return;
    }
    for (size_t i = 0; i < TestGroups.size(); i++)
    {
        Logger.Info("Test group " + std::to_string(i + 1) + " of " + std::to_string(TestGroups.size()));
        TestGroups[i].Judge();
        Score += TestGroups[i].GetScore();
        ResultCount[TestGroups[i].GetResult()]++;
        Logger.Info("Result: " + GetJudgeResultColorString(TestGroups[i].GetResult()) + "  " + std::to_string(TestGroups[i].GetTime()) + "ms  " + std::to_string(TestGroups[i].GetMemory()) + "b");
        Time = std::max(Time, TestGroups[i].GetTime());
        TimeSum += TestGroups[i].GetTime();
        Memory = std::max(Memory, TestGroups[i].GetMemory());
    }

    int MaxCount = 0;
    JUDGE_RESULT MaxResult = JUDGE_RESULT::UNKNOWN_ERROR;
    int SecondMaxCount = 0;
    JUDGE_RESULT SecondMaxResult = JUDGE_RESULT::UNKNOWN_ERROR;
    for (size_t i = 0; i < JUDGE_RESULT::REJECTED; i++)
        if (ResultCount[i] > MaxCount)
        {
            SecondMaxCount = MaxCount;
            SecondMaxResult = MaxResult;
            MaxCount = ResultCount[i];
            MaxResult = (JUDGE_RESULT)i;
        }
        else if (ResultCount[i] > SecondMaxCount)
        {
            SecondMaxCount = ResultCount[i];
            SecondMaxResult = (JUDGE_RESULT)i;
        }
    Result = (SecondMaxCount == 0 || MaxResult != JUDGE_RESULT::ACCEPTED) ? MaxResult : SecondMaxResult;
    Logger.Debug("Max result: " + GetJudgeResultColorString(MaxResult) + "  " + std::to_string(MaxCount));
    Logger.Debug("Second max result: " + GetJudgeResultColorString(SecondMaxResult) + "  " + std::to_string(SecondMaxCount));
}
bool SUBMISSION::Load(int ID)
{
    this->ID = ID;
    UpdateWorkDir();
    if (!Utilities.LoadFile(WorkDir + "/Result", (int &)Result) ||
        !Utilities.LoadFile(WorkDir + "/Description", Description) ||
        !Utilities.LoadFile(WorkDir + "/ProblemID", ProblemID) ||
        !Utilities.LoadFile(WorkDir + "/Source", Source) ||
        !Utilities.LoadFile(WorkDir + "/Time", Time) ||
        !Utilities.LoadFile(WorkDir + "/TimeSum", TimeSum) ||
        !Utilities.LoadFile(WorkDir + "/Memory", Memory) ||
        !Utilities.LoadFile(WorkDir + "/Score", Score) ||
        !Utilities.LoadFile(WorkDir + "/EnableO2", (int &)EnableO2))
    {
        Logger.Warning("Submission " + std::to_string(ID) + " load failed");
        return false;
    }
    Problem.Load(ProblemID);
    DIR *Dir = opendir(WorkDir.c_str());
    if (Dir == nullptr)
    {
        Logger.Warning("Submission " + std::to_string(ID) + " load failed");
        return false;
    }
    struct dirent *DirEntry;
    while ((DirEntry = readdir(Dir)) != nullptr)
    {
        if (DirEntry->d_type == DT_DIR)
        {
            std::string TestGroupID = DirEntry->d_name;
            if (TestGroupID == "." || TestGroupID == ".." || (TestGroupID != "0" && atoi(TestGroupID.c_str()) == 0))
                continue;
            TEST_GROUP TestGroup;
            if (!TestGroup.LoadFromSubmission(std::to_string(ID), TestGroupID))
            {
                Logger.Warning("Submission " + std::to_string(ID) + " load failed because of the failed of test group " + TestGroupID);
                return false;
            }
            TestGroups.push_back(TestGroup);
        }
    }
    closedir(Dir);
    if (TestGroups.size() == 0)
        CopyTestGroups();
    Logger.Info("Submission " + std::to_string(ID) + " loaded");
    return true;
}
bool SUBMISSION::Save()
{
    if (!Utilities.SaveFile(WorkDir + "/Result", Result) ||
        !Utilities.SaveFile(WorkDir + "/Description", Description) ||
        !Utilities.SaveFile(WorkDir + "/ProblemID", ProblemID) ||
        !Utilities.SaveFile(WorkDir + "/Source", Source) ||
        !Utilities.SaveFile(WorkDir + "/Time", Time) ||
        !Utilities.SaveFile(WorkDir + "/TimeSum", TimeSum) ||
        !Utilities.SaveFile(WorkDir + "/Memory", Memory) ||
        !Utilities.SaveFile(WorkDir + "/Score", Score) ||
        !Utilities.SaveFile(WorkDir + "/EnableO2", EnableO2))
    {
        Logger.Warning("Submission " + std::to_string(ID) + " save failed");
        return false;
    }
    for (auto i : TestGroups)
        if (!i.SaveToSubmission())
            return false;
    Logger.Info("Submission " + std::to_string(ID) + " saved");
    return true;
}

void SUBMISSION::Judge()
{
    std::ofstream SourceFile;
    if (Result != JUDGE_RESULT::WAITING)
        goto Exit;
    UpdateAllResults(JUDGE_RESULT::FETCHED);

    if (!Utilities.MakeDir(WorkDir))
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not remake working directory";
        Logger.Error("Can not remake working directory \"" + WorkDir + "\"");
        goto Exit;
    }

    Logger.Info("Start judging submission " + std::to_string(ID));
    SourceFile = std::ofstream(WorkDir + "/main.cpp");
    if (!SourceFile.is_open())
    {
        UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
        Description = "Can not open source file";
        Logger.Error("Can not open source file \"" + WorkDir + "/main.cpp\"");
        goto Exit;
    }
    SourceFile << Source;
    SourceFile.close();
    Compile();
    Logger.Info("");
    RunTestGroups();
    Logger.Info("");
    Logger.Info("Score: " + std::to_string(Score));
    Logger.Info("Judge result: " + GetJudgeResultColorString(Result));
    Logger.Info("Judge description: \"" + Description + "\"");
    Logger.Info("Time: " + std::to_string(Time) + "ms");
    Logger.Info("Time sum: " + std::to_string(TimeSum) + "ms");
    Logger.Info("Memory: " + std::to_string(Memory) + "b");

Exit:
    Save();
}
