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
    UpdateWorkDir();
}
TEST_CASE::~TEST_CASE() {}

JUDGE_RESULT TEST_CASE::GetResult() { return Result; }
std::string TEST_CASE::GetDescription() { return Description; }
std::string TEST_CASE::GetInput() { return Input; }
std::string TEST_CASE::GetAnswer() { return Answer; }
int TEST_CASE::GetTime() { return Time; }
int TEST_CASE::GetMemory() { return Memory; }
int TEST_CASE::GetScore() { return Score; }

bool TEST_CASE::RedirectIO()
{
    if (freopen((WorkDir + "/" + IOFileName + ".in").c_str(), "r", stdin) == nullptr)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not open input data file";
        Logger.Error("Can not open input data file \"" + IOFileName + ".in\"");
        return false;
    }
    Logger.Info("Redirected stdin to \"" + IOFileName + ".in\"");

    if (IOFileName == std::to_string(ID))
    {
        if (freopen((WorkDir + "/" + IOFileName + ".out").c_str(), "w", stdout) == nullptr)
        {
            Result = JUDGE_RESULT::SYSTEM_ERROR;
            Description = "Can not open output data file";
            Logger.Error("Can not open output data file \"" + IOFileName + ".out\"");
            return false;
        }
        Logger.Info("Redirected stdout to \"" + IOFileName + ".out\"");
    }
    else
    {
        if (freopen((WorkDir + "/std.out").c_str(), "w", stdout) == nullptr)
        {
            Result = JUDGE_RESULT::SYSTEM_ERROR;
            Description = "Can not open output data file";
            Logger.Error("Can not open output data file \"std.out\"");
            return false;
        }
        Logger.Info("Redirected stdout to \"std.out\"");
    }

    if (freopen((WorkDir + "/std.err").c_str(), "w", stderr) == nullptr)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not open error data file";
        Logger.Error("Can not open error data file \"std.err\"");
        return false;
    }
    Logger.Info("Redirected stderr to \"std.err\"");

    return true;
}
bool TEST_CASE::SetupEnvrionment()
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
            Result = JUDGE_RESULT::SYSTEM_ERROR;
            Description = "Can not create dir for the new root";
            Logger.Error("Can not create dir " + DirsToMake[i] + " for the new root");
            return false;
        }
        Logger.Info("Create dir \"" + DirsToMake[i] + "\" for the new root");
    }

    if (chown("./root", Settings.GetJudgeUserID(), Settings.GetJudgeUserGroupID()) == -1)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not change the owner of the new root";
        Logger.Error("Can not change the owner of the new root ./root");
        return false;
    }
    Logger.Info("Changed the owner of the new root ./root");

    if (chown("./tmp", Settings.GetJudgeUserID(), Settings.GetJudgeUserGroupID()) == -1)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not change the owner of the new root";
        Logger.Error("Can not change the owner of the new root ./tmp");
        return false;
    }
    Logger.Info("Changed the owner of the new root ./tmp");

    if (mount("/usr", "./usr", "ext4", MS_BIND, nullptr) == -1)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not mount the new root";
        Logger.Error("Can not mount the new root ./usr");
        return false;
    }
    Logger.Info("Mounted ./usr");

    if (mount("/usr", "./usr", "ext4", MS_BIND | MS_REMOUNT | MS_RDONLY, nullptr) == -1)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not remount the new root";
        Logger.Error("Can not remount the new root ./usr");
        return false;
    }
    Logger.Info("Remounted ./usr");

    if (mount("/proc", "./proc", "proc", MS_BIND, nullptr) == -1)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not mount the new root";
        Logger.Error("Can not mount the new root ./proc");
        return false;
    }
    Logger.Info("Mounted ./proc");

    if (mount("/dev", "./dev", "devtmpfs", MS_BIND, nullptr) == -1)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not mount the new root";
        Logger.Error("Can not mount the new root ./dev");
        return false;
    }
    Logger.Info("Mounted ./dev");

    if (mount("/dev", "./dev", "devtmpfs", MS_BIND | MS_REMOUNT | MS_RDONLY, nullptr) == -1)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
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
            Result = JUDGE_RESULT::SYSTEM_ERROR;
            Description = "Can not create symlink for the new root";
            Logger.Error("Can not create symlink for the new root " + DirsToLink[i]);
            return false;
        }
        Logger.Info("Created symlink for the new root " + DirsToLink[i]);
    }

    if (!Utilities.CopyDir("/etc/alternatives", "./etc/alternatives"))
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not copy alternatives for the new root";
        Logger.Error("Can not copy alternatives for the new root");
        return false;
    }

    if (chroot(WorkDir.c_str()) != 0)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not change root dir";
        Logger.Error("Can not change root dir " + WorkDir);
        return false;
    }
    Logger.SetLogFileName("Log.log");
    Logger.Info("Changed root dir to " + WorkDir);

    Logger.Warning("Environment setted");

    return true;
}
bool TEST_CASE::RemoveEnvrionment()
{
    if (chdir(WorkDir.c_str()) == -1)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
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
bool TEST_CASE::ChangeUser()
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
bool TEST_CASE::SetLimits()
{
    struct rlimit Limit;
    Limit.rlim_cur = Limit.rlim_max = TimeLimit + 1;
    if (setrlimit(RLIMIT_CPU, &Limit))
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not set cpu limit";
        Logger.Error("Can not set cpu limit");
        return false;
    }
    Logger.Info("Set cpu limit to " + std::to_string(TimeLimit + 1));

    if (alarm(ceil(TimeLimit / 1000.0) + 1) != 0)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not set alarm";
        Logger.Error("Can not set alarm to " + std::to_string(ceil(TimeLimit / 1000.0) + 1));
        return false;
    }
    Logger.Info("Set alarm to " + std::to_string(ceil(TimeLimit / 1000.0) + 1));

    Limit.rlim_max = MemoryLimit + 1024 * 1024;
    Limit.rlim_cur = MemoryLimit;
    if (setrlimit(RLIMIT_AS, &Limit))
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not set memory limit";
        Logger.Error("Can not set memory limit");
        return false;
    }
    Logger.Info("Set memory limit to " + std::to_string(MemoryLimit + 1024 * 1024));

    Limit.rlim_max = 32 * 1024 * 1024 + 1024 * 1024;
    Limit.rlim_cur = 32 * 1024 * 1024;
    if (setrlimit(RLIMIT_FSIZE, &Limit))
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not set file size limit";
        Logger.Error("Can not set file size limit");
        return false;
    }
    Logger.Info("Set file size limit to " + std::to_string(32 * 1024 * 1024 + 1024 * 1024));

    Limit.rlim_max = Limit.rlim_cur = 1;
    if (setrlimit(RLIMIT_NPROC, &Limit))
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not set process limit";
        Logger.Error("Can not set process limit");
        return false;
    }
    Logger.Info("Set process limit to 1");

    Limit.rlim_max = 256 * 1024 * 1024 + 1024 * 1024;
    Limit.rlim_cur = 256 * 1024 * 1024;
    if (setrlimit(RLIMIT_STACK, &Limit))
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not set stack limit";
        Logger.Error("Can not set stack limit");
        return false;
    }
    Logger.Info("Set stack limit to " + std::to_string(256 * 1024 * 1024 + 1024 * 1024));

    Limit.rlim_max = Limit.rlim_cur = 0;
    if (setrlimit(RLIMIT_CORE, &Limit))
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not set core limit";
        Logger.Error("Can not set core limit");
        return false;
    }
    Logger.Info("Set core limit to 0");

    return true;
}
void TEST_CASE::ChildProcess()
{
    Logger.Info("Entered child process");

    if (nice(19) != 19)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not change nice value";
        Logger.Error("Can not change nice value to 19");
        return;
    }
    Logger.Info("Changed nice value to 19");

    if (chdir(WorkDir.c_str()) == -1)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not change to work dir";
        Logger.Error("Can not change to work dir " + WorkDir);
        return;
    }
    Logger.Info("Changed to work dir \"" + WorkDir + "\"");

    if (!RedirectIO() || !SetupEnvrionment() || !ChangeUser() || !SetLimits())
        return;

    if (ptrace(PTRACE_TRACEME, 0, nullptr, nullptr) == -1)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not trace self";
        Logger.Error("Can not trace self");
        return;
    }
    Logger.Info("Traced self");

    execl("/main", "main", nullptr);

    Result = JUDGE_RESULT::SYSTEM_ERROR;
    Description = "Can not execute program";
    Logger.Error("Can not execute program");
}
bool TEST_CASE::CheckSignal()
{
    int Status;
    struct rusage Usage;
    if (wait4(PID, &Status, 0, &Usage) == -1)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not wait for child process";
        Logger.Error("Can not wait for child process");
        kill(PID, SIGKILL);
        return false;
    }
    if (WIFEXITED(Status))
    {
        int ExitCode = WEXITSTATUS(Status);
        Logger.Info("Child process exited with code " + std::to_string(ExitCode));
        if (ExitCode != 0)
        {
            Result = JUDGE_RESULT::RUNTIME_ERROR;
            Description = "Child process exited with code " + std::to_string(ExitCode);
            Logger.Warning("This is recognized as runtime error");
        }
        Time = (Usage.ru_utime.tv_sec * 1000 + Usage.ru_utime.tv_usec / 1000) +
               (Usage.ru_stime.tv_sec * 1000 + Usage.ru_stime.tv_usec / 1000);
        if (Time > TimeLimit)
        {
            Result = JUDGE_RESULT::TIME_LIMIT_EXCEEDED;
            Description = "Time limit exceeded";
            Logger.Warning("Time limit exceeded");
        }
        return false;
    }
    if (WIFSIGNALED(Status))
    {
        int Signal = WTERMSIG(Status);
        Logger.Info("Child process terminated by signal " + std::to_string(Signal) + ": " + strsignal(Signal));
        if (Signal == SIGVTALRM || Signal == SIGCHLD)
        {
            alarm(0);
            Result = JUDGE_RESULT::TIME_LIMIT_EXCEEDED;
            Description = "Time limit exceeded";
            Logger.Warning("Time limit exceeded");
            kill(PID, SIGKILL);
        }
        else if (Signal == SIGALRM || Signal == SIGXCPU)
        {
            Result = JUDGE_RESULT::TIME_LIMIT_EXCEEDED;
            Description = "Time limit exceeded";
            Logger.Warning("Time limit exceeded");
            kill(PID, SIGKILL);
        }
        else if (Signal == SIGXFSZ)
        {
            Result = JUDGE_RESULT::OUTPUT_LIMIT_EXCEEDED;
            Description = "Output limit exceeded";
            Logger.Warning("Output limit exceeded");
            kill(PID, SIGKILL);
        }
        else if (Signal == SIGSEGV)
        {
            Result = JUDGE_RESULT::MEMORY_LIMIT_EXCEEDED;
            Description = "Memory limit exceeded";
            Logger.Warning("Memory limit exceeded");
            kill(PID, SIGKILL);
        }
        else
        {
            Result = JUDGE_RESULT::RUNTIME_ERROR;
            Description = "Child process terminated by signal " + std::to_string(Signal);
            Logger.Warning("Can not recognize signal");
            kill(PID, SIGKILL);
        }
        Time = (Usage.ru_utime.tv_sec * 1000 + Usage.ru_utime.tv_usec / 1000) +
               (Usage.ru_stime.tv_sec * 1000 + Usage.ru_stime.tv_usec / 1000);
        if (Time > TimeLimit)
        {
            Result = JUDGE_RESULT::TIME_LIMIT_EXCEEDED;
            Description = "Time limit exceeded";
            Logger.Warning("Time limit exceeded");
        }
        return false;
    }
    if (WIFSTOPPED(Status))
    {
        int Signal = WSTOPSIG(Status);
        if (Signal == SIGTRAP)
        {
            if (ptrace(PTRACE_SYSCALL, PID, nullptr, nullptr) == -1)
            {
                Result = JUDGE_RESULT::SYSTEM_ERROR;
                Description = "Can not continue child process";
                Logger.Error("Can not continue child process");
                kill(PID, SIGKILL);
                return false;
            }
        }
        else
        {
            Logger.Info("Child process stopped by signal " + std::to_string(Signal) + ": " + strsignal(Signal));
            if (ptrace(PTRACE_SYSCALL, PID, nullptr, Signal) == -1)
            {
                Result = JUDGE_RESULT::SYSTEM_ERROR;
                Description = "Can not continue child process";
                Logger.Error("Can not continue child process");
                kill(PID, SIGKILL);
                return false;
            }
        }
    }
    return true;
}
bool TEST_CASE::CheckMemory()
{
    std::ifstream ProcessStatus("/proc/" + std::to_string(PID) + "/status");
    if (!ProcessStatus.is_open())
    {
        Logger.Warning("Can not open process status file /proc/" + std::to_string(PID) + "/status");
        return true;
    }
    std::string Line;
    while (std::getline(ProcessStatus, Line))
    {
        if (Line.substr(0, 6) == "VmPeak")
        {
            int CurrentMemory = std::stoi(Line.substr(7, Line.find("kB") - 7));
            if (CurrentMemory > Memory)
            {
                Memory = CurrentMemory;
                Logger.Info("Current memory usage is " + std::to_string(Memory) + "kB");
            }
            if (Memory > MemoryLimit)
            {
                Result = JUDGE_RESULT::MEMORY_LIMIT_EXCEEDED;
                Description = "Memory limit exceeded";
                Logger.Warning("Memory limit exceeded");
                kill(PID, SIGKILL);
                return false;
            }
            break;
        }
    }
    ProcessStatus.close();
    return true;
}
bool TEST_CASE::CheckSystemCall()
{
    struct user_regs_struct Regs;
    if (ptrace(PTRACE_GETREGS, PID, nullptr, &Regs) == -1)
    {
        Logger.Warning("Can not get register of child process");
        return true;
    }
    int CallID = (unsigned int)Regs.orig_rax % Settings.SystemCallCount;
    SystemCallCount[CallID]++;
    Logger.Info("Child process tried to execute system call " + std::to_string(CallID) + ": \"" + Settings.GetSystemCallName(CallID) + "\" for " + std::to_string(SystemCallCount[CallID]) + " times");
    if (Settings.IsBannedSystemCall(CallID, SystemCallCount[CallID]))
    {
        Result = JUDGE_RESULT::RESTRICTED_FUNCTION;
        Description = "Child process tried to execute system call " + std::to_string(CallID);
        Logger.Warning("The system call is banned");
        kill(PID, SIGKILL);
        return false;
    }
    if (ptrace(PTRACE_SYSCALL, PID, nullptr, nullptr) != 0)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not trace system calls";
        Logger.Error("Can not trace system calls");
        kill(PID, SIGKILL);
        return false;
    }
    return true;
}
void TEST_CASE::ParentProcess()
{
    Logger.Info("Entered parent process, child process is " + std::to_string(PID));
    while (1)
    {
        Logger.Debug("Waiting for child process");

        if (Result != JUDGE_RESULT::JUDGING)
        {
            Logger.Warning("Judge stopped because of status is not JUDGING");
            return;
        }

        if (!CheckSignal() || !CheckMemory() || !CheckSystemCall())
            return;
    }
}
void TEST_CASE::Run()
{
    std::ofstream InputFile(WorkDir + "/" + IOFileName + ".in");
    if (!InputFile.is_open())
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not open data file";
        Logger.Error("Can not open data file " + WorkDir + "/" + IOFileName + ".in");
        return;
    }
    InputFile << Input;
    InputFile.close();
    Logger.Info("Input file written");

    if (chown((WorkDir + "/" + IOFileName + ".in").c_str(), Settings.GetJudgeUserID(), Settings.GetJudgeUserGroupID()) == -1)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not change group of input file";
        Logger.Error("Can not change group of input file \"" + IOFileName + ".in\"");
        return;
    }
    Logger.Info("Changed group of input file \"" + IOFileName + ".in\"");

    if (chmod((WorkDir + "/" + IOFileName + ".in").c_str(), 0740) == -1)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not change permission of input file";
        Logger.Error("Can not change permission of input file \"" + IOFileName + ".in\"");
        return;
    }
    Logger.Info("Changed permission of input file \"" + IOFileName + ".in\"");

    std::ofstream OutputFile(WorkDir + "/" + IOFileName + ".out");
    if (!OutputFile.is_open())
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not open data file";
        Logger.Error("Can not open data file \"" + WorkDir + "/" + IOFileName + ".out\"");
        return;
    }
    OutputFile.close();
    Logger.Info("Output file created");

    if (chown((WorkDir + "/" + IOFileName + ".out").c_str(), Settings.GetJudgeUserID(), Settings.GetJudgeUserGroupID()) == -1)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not change group of output file";
        Logger.Error("Can not change group of output file \"" + IOFileName + ".out\"");
        return;
    }
    Logger.Info("Changed group of output file \"" + IOFileName + ".out\"");

    if (chmod((WorkDir + "/" + IOFileName + ".out").c_str(), 0760) == -1)
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not change permission of output file";
        Logger.Error("Can not change permission of output file \"" + IOFileName + ".out\"");
        return;
    }
    Logger.Info("Changed permission of output file \"" + IOFileName + ".out\"");

    std::ofstream StandardOutputFile(WorkDir + "/std.out");
    if (!StandardOutputFile.is_open())
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not open data file";
        Logger.Error("Can not open data file \"" + WorkDir + "/std.out\"");
        return;
    }
    StandardOutputFile.close();
    Logger.Info("Standard error file created");

    std::ofstream StandardErrorFile(WorkDir + "/std.err");
    if (!StandardErrorFile.is_open())
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not open data file";
        Logger.Error("Can not open data file \"" + WorkDir + "/std.err\"");
        return;
    }
    StandardErrorFile.close();
    Logger.Info("Standard error file created");

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
    }
}
void TEST_CASE::Compare()
{
    if (Result != JUDGE_RESULT::JUDGING)
    {
        Logger.Warning("Can not compare test case because it is not judging");
        return;
    }

    std::string Line;
    std::ifstream OutputFile(WorkDir + "/" + IOFileName + ".out");
    if (!OutputFile.is_open())
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not open data file";
        Logger.Error("Can not open data file " + WorkDir + "/" + IOFileName + ".out");
        return;
    }
    while (std::getline(OutputFile, Line))
        Output += Line + "\n";
    OutputFile.close();
    Logger.Info("Output file read");

    std::ifstream StandardOutputFile(WorkDir + "/std.out");
    if (!StandardOutputFile.is_open())
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not open data file";
        Logger.Error("Can not open data file " + WorkDir + "/std.out");
        return;
    }
    while (std::getline(StandardOutputFile, Line))
        StandardOutput += Line + "\n";
    StandardOutputFile.close();
    Logger.Info("Standard output file read");

    std::ifstream StandardErrorFile(WorkDir + "/std.err");
    if (!StandardErrorFile.is_open())
    {
        Result = JUDGE_RESULT::SYSTEM_ERROR;
        Description = "Can not open data file";
        Logger.Error("Can not open data file " + WorkDir + "/std.err");
        return;
    }
    while (std::getline(StandardErrorFile, Line))
        StandardError += Line + "\n";
    StandardErrorFile.close();
    Logger.Info("Standard error file read");

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

    Logger.Info("Output: \"" + Output + "\"");
    Logger.Info("Answer: \"" + Answer + "\"");
    Logger.Info("Standard output: \"" + StandardOutput + "\"");
    Logger.Info("Standard error: \"" + StandardError + "\"");
    Logger.Info("Fixed output: \"" + FixedOutput + "\"");
    Logger.Info("Fixed answer: \"" + FixedAnswer + "\"");

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
}

bool TEST_CASE::LoadFromSubmission(std::string SubmissionID, std::string TestGroupID, std::string ID)
{
    this->SubmissionID = SubmissionID;
    this->TestGroupID = TestGroupID;
    this->ID = atoi(ID.c_str());
    UpdateWorkDir();
    if (!Utilities.LoadFile(WorkDir + "/Result", (int &)Result) ||
        !Utilities.LoadFile(WorkDir + "/Description", Description) ||
        !Utilities.LoadFile(WorkDir + "/Time", Time) ||
        !Utilities.LoadFile(WorkDir + "/TimeLimit", TimeLimit) ||
        !Utilities.LoadFile(WorkDir + "/Memory", Memory) ||
        !Utilities.LoadFile(WorkDir + "/MemoryLimit", MemoryLimit) ||
        !Utilities.LoadFile(WorkDir + "/Score", Score) ||
        !Utilities.LoadFile(WorkDir + "/Input", Input) ||
        !Utilities.LoadFile(WorkDir + "/Answer", Answer) ||
        !Utilities.LoadFile(WorkDir + "/IOFileName", IOFileName))
    {
        Logger.Warning("Submission " + SubmissionID + " test group " + TestGroupID + " test case " + ID + " load failed");
        return false;
    }
    Logger.Info("Submission " + SubmissionID + " test group " + TestGroupID + " test case " + ID + " loaded");
    return true;
}
bool TEST_CASE::LoadFromProblem(std::string ProblemID, std::string TestGroupID, std::string ID)
{
    std::string CurrentTestCaseBaseFolder = Settings.GetProblemBaseFolder() + "/" + ProblemID + "/TestGroups/" + TestGroupID + "/" + ID;
    if (!Utilities.LoadFile(CurrentTestCaseBaseFolder + "/Input", Input) ||
        !Utilities.LoadFile(CurrentTestCaseBaseFolder + "/Answer", Answer) ||
        !Utilities.LoadFile(CurrentTestCaseBaseFolder + "/IOFileName", IOFileName) ||
        !Utilities.LoadFile(CurrentTestCaseBaseFolder + "/TimeLimit", TimeLimit) ||
        !Utilities.LoadFile(CurrentTestCaseBaseFolder + "/MemoryLimit", MemoryLimit) ||
        !Utilities.LoadFile(CurrentTestCaseBaseFolder + "/Score", Score))
    {
        Logger.Warning("Problem \"" + ProblemID + "\" test group " + TestGroupID + " test case " + ID + " load failed");
        return false;
    }
    this->ID = atoi(ID.c_str());
    Logger.Info("Problem \"" + ProblemID + "\" test group " + TestGroupID + " test case " + ID + " loaded");
    return true;
}
bool TEST_CASE::SaveToProblem(std::string ProblemID, std::string TestGroupID)
{
    std::string CurrentTestCaseBaseFolder = Settings.GetProblemBaseFolder() + "/" + ProblemID + "/TestGroups/" + TestGroupID + "/" + std::to_string(ID);
    if (!Utilities.MakeDir(CurrentTestCaseBaseFolder) ||
        !Utilities.SaveFile(CurrentTestCaseBaseFolder + "/Input", Input) ||
        !Utilities.SaveFile(CurrentTestCaseBaseFolder + "/Answer", Answer) ||
        !Utilities.SaveFile(CurrentTestCaseBaseFolder + "/IOFileName", IOFileName) ||
        !Utilities.SaveFile(CurrentTestCaseBaseFolder + "/TimeLimit", TimeLimit) ||
        !Utilities.SaveFile(CurrentTestCaseBaseFolder + "/MemoryLimit", MemoryLimit) ||
        !Utilities.SaveFile(CurrentTestCaseBaseFolder + "/Score", Score))
    {
        Logger.Warning("Problem \"" + ProblemID + "\" test group " + TestGroupID + " test case " + std::to_string(ID) + " save failed");
        return false;
    }
    Logger.Info("Problem \"" + ProblemID + "\" test group " + TestGroupID + " test case " + std::to_string(ID) + " saved");
    return true;
}
bool TEST_CASE::SaveToSubmission()
{
    Utilities.MakeDir(WorkDir);
    if (!Utilities.SaveFile(WorkDir + "/Result", Result) ||
        !Utilities.SaveFile(WorkDir + "/Description", Description) ||
        !Utilities.SaveFile(WorkDir + "/Time", Time) ||
        !Utilities.SaveFile(WorkDir + "/TimeLimit", TimeLimit) ||
        !Utilities.SaveFile(WorkDir + "/Memory", Memory) ||
        !Utilities.SaveFile(WorkDir + "/MemoryLimit", MemoryLimit) ||
        !Utilities.SaveFile(WorkDir + "/Score", Score) ||
        !Utilities.SaveFile(WorkDir + "/Input", Input) ||
        !Utilities.SaveFile(WorkDir + "/Answer", Answer) ||
        !Utilities.SaveFile(WorkDir + "/IOFileName", IOFileName))
    {
        Logger.Warning("Submission " + SubmissionID + " test group " + TestGroupID + " test case " + std::to_string(ID) + " save failed");
        return false;
    }
    Logger.Info("Submission " + SubmissionID + " test group " + TestGroupID + " test case " + std::to_string(ID) + " saved");
    return true;
}
void TEST_CASE::UpdateWorkDir()
{
    WorkDir = Settings.GetSubmissionBaseFolder() + "/" + SubmissionID + "/" + TestGroupID + "/" + std::to_string(ID);
    if (!Utilities.MakeDir(WorkDir))
        Logger.Error("Can not remake work dir \"" + WorkDir + "\"");
    else
        Logger.SetLogFileName(WorkDir + "/Log.log");
}
void TEST_CASE::Judge()
{
    if (!Utilities.MakeDir(WorkDir))
    {
        this->Result = JUDGE_RESULT::SYSTEM_ERROR;
        this->Description = "Can not remake working directory";
        goto Exit;
    }

    if (!Utilities.CopyFile(WorkDir + "/../../main", WorkDir + "/main"))
    {
        this->Result = JUDGE_RESULT::SYSTEM_ERROR;
        this->Description = "Can not copy program file";
        goto Exit;
    }
    Logger.Info("Copied program file \"" + WorkDir + "/../../main\" to \"" + WorkDir + "/main\"");

    Logger.Info("Start judging test case " + std::to_string(ID) + " of test group " + TestGroupID + " of submission " + SubmissionID);
    Result = JUDGE_RESULT::JUDGING;
    SaveToSubmission();
    if (IOFileName == "")
        IOFileName = std::to_string(ID);
    Run();
    Logger.Info("");
    Compare();
    Score = (Result == JUDGE_RESULT::ACCEPTED ? Score : 0);
    Logger.Info("");
    Logger.Info("Score: " + std::to_string(Score));
    Logger.Info("Judge result: " + GetJudgeResultColorString(Result));
    Logger.Info("Judge description: \"" + Description + "\"");
    Logger.Info("Time: " + std::to_string(Time) + "ms");
    Logger.Info("Memory: " + std::to_string(Memory) + "b");

Exit:
    SaveToSubmission();
}
