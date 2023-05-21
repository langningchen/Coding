#include "Utilities.hpp"
#include "Logger.hpp"
#include "Settings.hpp"
#include "TestCase.hpp"
#include <map>
#include <fstream>
#include <math.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <sys/ptrace.h>
#include <sys/resource.h>

TEST_CASE::TEST_CASE() {}
TEST_CASE::TEST_CASE(const TEST_CASE &Other)
{
    ID = Other.ID;
    PID = Other.PID;
    Input = Other.Input;
    Output = Other.Output;
    Answer = Other.Answer;
    StandardOutput = Other.StandardOutput;
    StandardError = Other.StandardError;
    IOFileName = Other.IOFileName;
    SubmissionID = Other.SubmissionID;
    TestGroupID = Other.TestGroupID;
    WorkDir = Other.WorkDir;
    Result = Other.Result;
    Description = Other.Description;
    Time = Other.Time;
    TimeLimit = Other.TimeLimit;
    Memory = Other.Memory;
    MemoryLimit = Other.MemoryLimit;
    Score = Other.Score;
    for (int i = 0; i < Settings.SystemCallCount; i++)
        SystemCallCount[i] = Other.SystemCallCount[i];
    Logger = Other.Logger;
}

TEST_CASE::TEST_CASE(int ID, std::string TestGroupID, std::string Input, std::string Answer, std::string IOFileName, std::string SubmissionID, int TimeLimit, int MemoryLimit, int Score)
{
    TEST_CASE();
    this->ID = ID;
    this->Input = Input;
    this->Answer = Answer;
    this->IOFileName = IOFileName;
    this->SubmissionID = SubmissionID;
    this->Result = JUDGE_RESULT::UNKNOWN_ERROR;
    this->TimeLimit = TimeLimit;
    this->MemoryLimit = MemoryLimit;
    this->Score = Score;
    UpdateWorkDirFromSubmission();
}
TEST_CASE::~TEST_CASE() {}

JUDGE_RESULT TEST_CASE::GetResult() { return Result; }
std::string TEST_CASE::GetDescription() { return Description; }
std::string TEST_CASE::GetInput() { return Input; }
std::string TEST_CASE::GetAnswer() { return Answer; }
int TEST_CASE::GetTime() { return Time; }
int TEST_CASE::GetMemory() { return Memory; }
int TEST_CASE::GetScore() { return Score; }

RESULT TEST_CASE::RedirectIO()
{
    if (freopen((WorkDir + "/" + IOFileName + ".in").c_str(), "r", stdin) == nullptr)
        CREATE_RESULT(false, "Can not open input data file")

    if (IOFileName == std::to_string(ID))
    {
        if (freopen((WorkDir + "/" + IOFileName + ".out").c_str(), "w", stdout) == nullptr)
            CREATE_RESULT(false, "Can not open output data file");
    }
    else
    {
        if (freopen((WorkDir + "/std.out").c_str(), "w", stdout) == nullptr)
            CREATE_RESULT(false, "Can not open output data file")
    }

    if (freopen((WorkDir + "/std.err").c_str(), "w", stderr) == nullptr)
        CREATE_RESULT(false, "Can not open error data file")

    CREATE_RESULT(true, "Redirected IO")
}
RESULT TEST_CASE::SetupEnvrionment()
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
            CREATE_RESULT(false, "Can not create dir for the new root")
    }

    if (chown("./root", Settings.GetJudgeUserID(), Settings.GetJudgeUserGroupID()) == -1)
        CREATE_RESULT(false, "Can not change the owner of the new root")

    if (chown("./tmp", Settings.GetJudgeUserID(), Settings.GetJudgeUserGroupID()) == -1)
        CREATE_RESULT(false, "Can not change the owner of the new root")

    if (mount("/usr", "./usr", "ext4", MS_BIND, nullptr) == -1)
        CREATE_RESULT(false, "Can not mount the new root")

    if (mount("/usr", "./usr", "ext4", MS_BIND | MS_REMOUNT | MS_RDONLY, nullptr) == -1)
        CREATE_RESULT(false, "Can not remount the new root")

    if (mount("/proc", "./proc", "proc", MS_BIND, nullptr) == -1)
        CREATE_RESULT(false, "Can not mount the new root")

    if (mount("/dev", "./dev", "devtmpfs", MS_BIND, nullptr) == -1)
        CREATE_RESULT(false, "Can not mount the new root")

    if (mount("/dev", "./dev", "devtmpfs", MS_BIND | MS_REMOUNT | MS_RDONLY, nullptr) == -1)
        CREATE_RESULT(false, "Can not remount the new root")

    const std::string DirsToLink[5] = {
        "bin",
        "lib",
        "lib32",
        "libx32",
        "lib64"};
    for (int i = 0; i < 5; i++)
    {
        if (symlink(("/usr/" + DirsToLink[i]).c_str(), DirsToLink[i].c_str()) == -1)
            CREATE_RESULT(false, "Can not create symlink for the new root")
    }

    RETURN_IF_FAILED(Utilities.CopyDir("/etc/alternatives", "./etc/alternatives"))

    if (chroot(WorkDir.c_str()) != 0)
        CREATE_RESULT(false, "Can not change root dir")
    Logger.SetLogFileName("Log.log");

    CREATE_RESULT(true, "Environment setted")
}
RESULT TEST_CASE::RemoveEnvrionment()
{
    if (chdir(WorkDir.c_str()) == -1)
        CREATE_RESULT(false, "Can not change directory")

    const std::string DirsToUmount[4] = {
        "usr",
        "proc",
        "dev",
        "usr"};
    for (int i = 0; i < 4; i++)
        umount(DirsToUmount[i].c_str());

    const std::string FilesToRemove[5] = {
        "bin",
        "lib",
        "lib32",
        "lib64",
        "libx32"};
    for (int i = 0; i < 5; i++)
        remove(FilesToRemove[i].c_str());

    const std::string DirsToRemove[6] = {
        "root",
        "etc",
        "dev",
        "proc",
        "tmp",
        "usr"};
    for (int i = 0; i < 6; i++)
        RETURN_IF_FAILED(Utilities.RemoveDir(DirsToRemove[i].c_str()))

    CREATE_RESULT(true, "Environment removed")
}
RESULT TEST_CASE::ChangeUser()
{
    if (setgid(Settings.GetJudgeUserGroupID()) != 0)
        CREATE_RESULT(false, "Can not change gid")
    if (setuid(Settings.GetJudgeUserID()) != 0)
        CREATE_RESULT(false, "Can not change uid")
    if (setresgid(Settings.GetJudgeUserGroupID(),
                  Settings.GetJudgeUserGroupID(),
                  Settings.GetJudgeUserGroupID()) != 0)
        CREATE_RESULT(false, "Can not change real gid")
    if (setresuid(Settings.GetJudgeUserID(),
                  Settings.GetJudgeUserID(),
                  Settings.GetJudgeUserID()) != 0)
        CREATE_RESULT(false, "Can not change real uid")

    CREATE_RESULT(true, "Changed uid and gid")
}
RESULT TEST_CASE::SetLimits()
{
    struct rlimit Limit;
    Limit.rlim_cur = Limit.rlim_max = TimeLimit + 1;
    if (setrlimit(RLIMIT_CPU, &Limit))
        CREATE_RESULT(false, "Can not set cpu limit")

    if (alarm(ceil(TimeLimit / 1000.0) + 1) != 0)
        CREATE_RESULT(false, "Can not set alarm")

    Limit.rlim_max = MemoryLimit + 1024 * 1024;
    Limit.rlim_cur = MemoryLimit;
    if (setrlimit(RLIMIT_AS, &Limit))
        CREATE_RESULT(false, "Can not set memory limit")

    Limit.rlim_max = 32 * 1024 * 1024 + 1024 * 1024;
    Limit.rlim_cur = 32 * 1024 * 1024;
    if (setrlimit(RLIMIT_FSIZE, &Limit))
        CREATE_RESULT(false, "Can not set file size limit")

    Limit.rlim_max = Limit.rlim_cur = 1;
    if (setrlimit(RLIMIT_NPROC, &Limit))
        CREATE_RESULT(false, "Can not set process limit")

    Limit.rlim_max = 256 * 1024 * 1024 + 1024 * 1024;
    Limit.rlim_cur = 256 * 1024 * 1024;
    if (setrlimit(RLIMIT_STACK, &Limit))
        CREATE_RESULT(false, "Can not set stack limit")

    Limit.rlim_max = Limit.rlim_cur = 0;
    if (setrlimit(RLIMIT_CORE, &Limit))
        CREATE_RESULT(false, "Can not set core limit")

    CREATE_RESULT(true, "Set limits")
}
RESULT TEST_CASE::ChildProcess()
{

    if (nice(19) != 19)
        CREATE_RESULT(false, "Can not change nice value")
    if (chdir(WorkDir.c_str()) == -1)
        CREATE_RESULT(false, "Can not change to work dir")

    RETURN_IF_FAILED(RedirectIO())
    RETURN_IF_FAILED(SetupEnvrionment())
    RETURN_IF_FAILED(ChangeUser())
    RETURN_IF_FAILED(SetLimits())

    if (ptrace(PTRACE_TRACEME, 0, nullptr, nullptr) == -1)
        CREATE_RESULT(false, "Can not trace self")

    execl("/main", "main", nullptr);

    CREATE_RESULT(false, "Can not execute program");
}
RESULT TEST_CASE::CheckSignal()
{
    int Status;
    struct rusage Usage;
    if (wait4(PID, &Status, 0, &Usage) == -1)
        CREATE_RESULT(false, "Can not wait for child process")
    Time = (Usage.ru_utime.tv_sec * 1000 + Usage.ru_utime.tv_usec / 1000) +
           (Usage.ru_stime.tv_sec * 1000 + Usage.ru_stime.tv_usec / 1000);
    if (WIFEXITED(Status))
    {
        int ExitCode = WEXITSTATUS(Status);
        if (ExitCode != 0)
        {
            Result = JUDGE_RESULT::RUNTIME_ERROR;
            Description = "Child process exited with code " + std::to_string(ExitCode) + " which is recognized as runtime error";
            CREATE_RESULT(false, "Child process exited with code " + std::to_string(ExitCode))
        }
        Result = JUDGE_RESULT::JUDGED;
        CREATE_RESULT(false, "Judged")
    }
    if (WIFSIGNALED(Status))
    {
        int Signal = WTERMSIG(Status);
        if (Signal == SIGVTALRM || Signal == SIGALRM || Signal == SIGXCPU)
        {
            Result = JUDGE_RESULT::TIME_LIMIT_EXCEEDED;
            DEBUG_HERE
            CREATE_RESULT(false, "Time limit exceeded");
        }
        else if (Signal == SIGXFSZ)
        {
            Result = JUDGE_RESULT::OUTPUT_LIMIT_EXCEEDED;
            CREATE_RESULT(false, "Output limit exceeded");
        }
        else if (Signal == SIGSEGV)
        {
            Result = JUDGE_RESULT::MEMORY_LIMIT_EXCEEDED;
            CREATE_RESULT(false, "Memory limit exceeded");
        }
        else
        {
            Result = JUDGE_RESULT::RUNTIME_ERROR;
            CREATE_RESULT(false, "Can not recognize signal");
        }
        Result = JUDGE_RESULT::JUDGED;
        CREATE_RESULT(false, "Got signal");
    }
    if (WIFSTOPPED(Status))
    {
        int Signal = WSTOPSIG(Status);
        if (Signal == SIGTRAP)
        {
            if (ptrace(PTRACE_SYSCALL, PID, nullptr, nullptr) == -1)
                CREATE_RESULT(false, "Can not continue child process");
        }
        else
        {
            if (ptrace(PTRACE_SYSCALL, PID, nullptr, Signal) == -1)
                CREATE_RESULT(false, "Can not continue child process");
        }
    }
    CREATE_RESULT(true, "No signal");
}
RESULT TEST_CASE::CheckMemory()
{
    std::ifstream ProcessStatus("/proc/" + std::to_string(PID) + "/status");
    if (!ProcessStatus.is_open())
        CREATE_RESULT(false, "Can not open process status file");
    std::string Line;
    while (std::getline(ProcessStatus, Line))
        if (Line.substr(0, 6) == "VmPeak")
        {
            Memory = std::max(Memory, std::stoi(Line.substr(7, Line.find("kB") - 7)));
            if (Memory > MemoryLimit)
            {
                Result = JUDGE_RESULT::MEMORY_LIMIT_EXCEEDED;
                CREATE_RESULT(false, "Memory limit exceeded");
            }
            break;
        }
    ProcessStatus.close();
    CREATE_RESULT(true, "Memory is OK");
}
RESULT TEST_CASE::CheckSystemCall()
{
    struct user_regs_struct Regs;
    if (ptrace(PTRACE_GETREGS, PID, nullptr, &Regs) == -1)
        CREATE_RESULT(true, "Can not get registers")
    int CallID = (unsigned int)Regs.orig_rax % Settings.SystemCallCount;
    SystemCallCount[CallID]++;
    if (Settings.IsBannedSystemCall(CallID, SystemCallCount[CallID]))
    {
        Result = JUDGE_RESULT::RESTRICTED_FUNCTION;
        Description = "Child process tried to execute system call " + std::to_string(CallID);
        CREATE_RESULT(false, "The system call is banned")
    }
    if (ptrace(PTRACE_SYSCALL, PID, nullptr, nullptr) != 0)
        CREATE_RESULT(false, "Can not trace system calls")
    CREATE_RESULT(true, "No banned system call");
}
RESULT TEST_CASE::ParentProcess()
{
    while (1)
    {
        if (Result != JUDGE_RESULT::JUDGING)
            CREATE_RESULT(true, "Judge stopped because of status is not JUDGING")

        RETURN_IF_FAILED(CheckSignal())
        RETURN_IF_FAILED(CheckMemory())
        RETURN_IF_FAILED(CheckSystemCall())
    }
    CREATE_RESULT(false, "Shouldn't go here");
}
RESULT TEST_CASE::Run()
{
    std::ofstream InputFile(WorkDir + "/" + IOFileName + ".in");
    if (!InputFile.is_open())
        CREATE_RESULT(false, "Can not open data file")
    InputFile << Input;
    InputFile.close();

    if (chown((WorkDir + "/" + IOFileName + ".in").c_str(), Settings.GetJudgeUserID(), Settings.GetJudgeUserGroupID()) == -1)
        CREATE_RESULT(false, "Can not change group of input file")

    if (chmod((WorkDir + "/" + IOFileName + ".in").c_str(), 0740) == -1)
        CREATE_RESULT(false, "Can not change permission of input file")

    std::ofstream OutputFile(WorkDir + "/" + IOFileName + ".out");
    if (!OutputFile.is_open())
        CREATE_RESULT(false, "Can not open data file")
    OutputFile.close();

    if (chown((WorkDir + "/" + IOFileName + ".out").c_str(), Settings.GetJudgeUserID(), Settings.GetJudgeUserGroupID()) == -1)
        CREATE_RESULT(false, "Can not change group of output file")

    if (chmod((WorkDir + "/" + IOFileName + ".out").c_str(), 0760) == -1)
        CREATE_RESULT(false, "Can not change permission of output file")

    std::ofstream StandardOutputFile(WorkDir + "/std.out");
    if (!StandardOutputFile.is_open())
        CREATE_RESULT(false, "Can not open data file")
    StandardOutputFile.close();

    std::ofstream StandardErrorFile(WorkDir + "/std.err");
    if (!StandardErrorFile.is_open())
        CREATE_RESULT(false, "Can not open data file")
    StandardErrorFile.close();

    pid_t PID = fork();
    if (PID == 0)
    {
        RETURN_IF_FAILED(ChildProcess())
        exit(0);
    }
    else
    {
        this->PID = PID;
        ParentProcess();
        RemoveEnvrionment();
    }

    CREATE_RESULT(true, "Run ended");
}
RESULT TEST_CASE::Compare()
{
    if (Result != JUDGE_RESULT::JUDGED)
        CREATE_RESULT(true, "Judge stopped because of status is not JUDGED")

    Result = JUDGE_RESULT::COMPARING;

    std::string Line;
    std::ifstream OutputFile(WorkDir + "/" + IOFileName + ".out");
    if (!OutputFile.is_open())
        CREATE_RESULT(false, "Can not open data file")
    while (std::getline(OutputFile, Line))
        Output += Line + "\n";
    OutputFile.close();

    std::ifstream StandardOutputFile(WorkDir + "/std.out");
    if (!StandardOutputFile.is_open())
        CREATE_RESULT(false, "Can not open data file")
    while (std::getline(StandardOutputFile, Line))
        StandardOutput += Line + "\n";
    StandardOutputFile.close();

    std::ifstream StandardErrorFile(WorkDir + "/std.err");
    if (!StandardErrorFile.is_open())
        CREATE_RESULT(false, "Can not open data file")
    while (std::getline(StandardErrorFile, Line))
        StandardError += Line + "\n";
    StandardErrorFile.close();

    Output = Utilities.RemoveSpaces(Output);
    Answer = Utilities.RemoveSpaces(Answer);
    StandardOutput = Utilities.RemoveSpaces(StandardOutput);
    StandardError = Utilities.RemoveSpaces(StandardError);

    std::string FixedOutput = Utilities.StringReplaceAll(Output, "\r", "");
    FixedOutput = Utilities.StringReplaceAll(FixedOutput, "\n", "");
    FixedOutput = Utilities.StringReplaceAll(FixedOutput, "\t", "");
    FixedOutput = Utilities.StringReplaceAll(FixedOutput, " ", "");
    std::string FixedAnswer = Utilities.StringReplaceAll(Answer, "\r", "");
    FixedAnswer = Utilities.StringReplaceAll(FixedAnswer, "\n", "");
    FixedAnswer = Utilities.StringReplaceAll(FixedAnswer, "\t", "");
    FixedAnswer = Utilities.StringReplaceAll(FixedAnswer, " ", "");

    if (StandardError != "")
    {
        Result = JUDGE_RESULT::RUNTIME_ERROR;
        Description = "Do not output to stderr if you do so. ";
    }
    else if (Output == Answer)
    {
        Result = JUDGE_RESULT::ACCEPTED;
        Description = "Accepted";
    }
    else
    {
        if (FixedOutput == FixedAnswer)
        {
            Result = JUDGE_RESULT::PRESENTATION_ERROR;
            Description = "Presentation error";
        }
        else if (Output == "" && StandardOutput != "")
        {
            Result = JUDGE_RESULT::RUNTIME_ERROR;
            Description = "Your program outputs data to stdout instead of a file";
        }
        else if (Output == "" && StandardOutput == "")
        {
            Result = JUDGE_RESULT::RUNTIME_ERROR;
            Description = "Output is empty, checking if the program output it's data to a wrong file";
        }
        else
        {
            Result = JUDGE_RESULT::WRONG_ANSWER;
            Description = "Wrong answer";
        }
    }
    CREATE_RESULT(true, "Compared");
}

RESULT TEST_CASE::LoadFromSubmission(std::string SubmissionID, std::string TestGroupID, std::string ID)
{
    this->SubmissionID = SubmissionID;
    this->TestGroupID = TestGroupID;
    this->ID = atoi(ID.c_str());
    UpdateWorkDirFromSubmission();
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Result", (int &)Result))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Description", Description))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Time", Time))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/TimeLimit", TimeLimit))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Memory", Memory))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/MemoryLimit", MemoryLimit))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Score", Score))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Input", Input))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Answer", Answer))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/IOFileName", IOFileName))
    CREATE_RESULT(true, "Submission " + SubmissionID + " test group " + TestGroupID + " test case " + ID + " loaded");
}
RESULT TEST_CASE::LoadFromProblem(std::string ProblemID, std::string TestGroupID, std::string ID)
{
    this->ProblemID = ProblemID;
    this->TestGroupID = TestGroupID;
    UpdateWorkDirFromProblem();
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Input", Input))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Answer", Answer))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/TimeLimit", TimeLimit))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/MemoryLimit", MemoryLimit))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Score", Score))
    this->ID = atoi(ID.c_str());
    CREATE_RESULT(true, "Problem \"" + ProblemID + "\" test group " + TestGroupID + " test case " + ID + " loaded");
}
RESULT TEST_CASE::SaveToProblem(std::string ProblemID, std::string TestGroupID)
{
    this->ProblemID = ProblemID;
    this->TestGroupID = TestGroupID;
    RETURN_IF_FAILED(Utilities.MakeDir(WorkDir))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Input", Input))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Answer", Answer))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/TimeLimit", TimeLimit))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/MemoryLimit", MemoryLimit))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Score", Score))
    CREATE_RESULT(true, "Problem \"" + ProblemID + "\" test group " + TestGroupID + " test case " + std::to_string(ID) + " saved");
}
RESULT TEST_CASE::SaveToSubmission()
{
    Utilities.MakeDir(WorkDir);
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Result", Result))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Description", Description))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Time", Time))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/TimeLimit", TimeLimit))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Memory", Memory))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/MemoryLimit", MemoryLimit))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Score", Score))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Input", Input))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Answer", Answer))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/IOFileName", IOFileName))
    CREATE_RESULT(true, "Submission " + SubmissionID + " test group " + TestGroupID + " test case " + std::to_string(ID) + " saved");
}
RESULT TEST_CASE::UpdateWorkDirFromSubmission()
{
    WorkDir = Settings.GetSubmissionBaseFolder() + "/" + SubmissionID + "/" + TestGroupID + "/" + std::to_string(ID);
    RETURN_IF_FAILED(Utilities.MakeDir(WorkDir))
    CREATE_RESULT(true, "Updated work dir from submission")
}
RESULT TEST_CASE::UpdateWorkDirFromProblem()
{
    WorkDir = Settings.GetProblemBaseFolder() + "/" + ProblemID + "/TestGroups/" + TestGroupID + "/" + std::to_string(ID);
    RETURN_IF_FAILED(Utilities.MakeDir(WorkDir))
    CREATE_RESULT(true, "Updated work dir from problem")
}
RESULT TEST_CASE::Judge()
{
    RETURN_IF_FAILED(Utilities.MakeDir(WorkDir))
    RETURN_IF_FAILED(Utilities.CopyFile(WorkDir + "/../../main", WorkDir + "/main"))

    Result = JUDGE_RESULT::JUDGING;
    RETURN_IF_FAILED(SaveToSubmission())
    if (IOFileName == "")
        IOFileName = std::to_string(ID);

    RESULT RunResult = Run();
    if (Time > TimeLimit)
    {
        Result = JUDGE_RESULT::TIME_LIMIT_EXCEEDED;
        DEBUG_HERE
        CREATE_RESULT(false, "Time limit exceeded")
    }
    kill(PID, SIGKILL);
    waitpid(PID, nullptr, 0);
    if (!RunResult.Success && Result == JUDGE_RESULT::JUDGING)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = RunResult.Message;
        CREATE_RESULT(true, "Judged with system error from run")
    }

    RESULT CompareResult = Compare();
    if (!CompareResult.Success && Result == JUDGE_RESULT::JUDGING)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = CompareResult.Message;
        CREATE_RESULT(true, "Judged with system error from compare")
    }

    Score = (Result == JUDGE_RESULT::ACCEPTED ? Score : 0);

    CREATE_RESULT(true, "Judged")
}
