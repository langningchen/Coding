#include "Settings.hpp"
#include "Utilities.hpp"
#include <unistd.h>
#include <fstream>
#include <vector>
#include <sys/stat.h>

SETTINGS::SETTINGS()
{
}
SETTINGS::~SETTINGS() {}
void SETTINGS::Save()
{
    CheckSettings();
    std::string SystemCallsString = "";
    for (int i = 0; i < SystemCallCount; i++)
        SystemCallsString += SystemCalls[i].Name + " " + std::to_string(SystemCalls[i].AvailableCount) + "\n";
    if (!Utilities.SaveFile(SettingBaseFolder + "/JudgeUser", JudgeUser) ||
        !Utilities.SaveFile(SettingBaseFolder + "/Compiler", Compiler) ||
        !Utilities.SaveFile(SettingBaseFolder + "/SocketPort", std::to_string(SocketPort)) ||
        !Utilities.SaveFile(SettingBaseFolder + "/CompileTimeLimit", std::to_string(CompileTimeLimit)) ||
        !Utilities.SaveFile(SettingBaseFolder + "/CompileOutputLimit", std::to_string(CompileOutputLimit)) ||
        !Utilities.SaveFile(SettingBaseFolder + "/Email", Email) ||
        !Utilities.SaveFile(SettingBaseFolder + "/EmailPassword", EmailPassword) ||
        !Utilities.SaveFile(SettingBaseFolder + "/SystemCalls", SystemCallsString))
        Logger.Error("Can not save settings");
    else
        Logger.Info("Settings saved");
}
void SETTINGS::Load(std::string JudgeUser)
{
    std::string SettingBaseFolder = "/home/" + JudgeUser + "/Settings";
    std::string SystemCallsString;
    if (!Utilities.LoadFile(SettingBaseFolder + "/JudgeUser", JudgeUser) ||
        !Utilities.LoadFile(SettingBaseFolder + "/Compiler", Compiler) ||
        !Utilities.LoadFile(SettingBaseFolder + "/SocketPort", SocketPort) ||
        !Utilities.LoadFile(SettingBaseFolder + "/CompileTimeLimit", CompileTimeLimit) ||
        !Utilities.LoadFile(SettingBaseFolder + "/CompileOutputLimit", CompileOutputLimit) ||
        !Utilities.LoadFile(SettingBaseFolder + "/Email", Email) ||
        !Utilities.LoadFile(SettingBaseFolder + "/EmailPassword", EmailPassword) ||
        !Utilities.LoadFile(SettingBaseFolder + "/SystemCalls", SystemCallsString))
    {
        Logger.Error("Can not load settings");
        return;
    }
    std::vector<std::string> SystemCallsLines;
    for (size_t i = 0; i < SystemCallsString.size(); i++)
        if (SystemCallsString[i] == '\n')
        {
            SystemCallsLines.push_back(SystemCallsString.substr(0, i));
            SystemCallsString = SystemCallsString.substr(i + 1);
            i = 0;
        }
    for (size_t i = 0; i < SystemCallsLines.size(); i++)
    {
        std::string SystemCallName = SystemCallsLines[i].substr(0, SystemCallsLines[i].find(' '));
        int SystemCallAvailableCount = std::stoi(SystemCallsLines[i].substr(SystemCallsLines[i].find(' ') + 1));
        SystemCalls[i].Name = SystemCallName;
        SystemCalls[i].AvailableCount = SystemCallAvailableCount;
    }
    CheckSettings();
    Logger.Info("Settings loaded");
}

std::string SETTINGS::GetBaseFolder() { return BaseFolder; }
std::string SETTINGS::GetSubmissionBaseFolder() { return SubmissionBaseFolder; }
std::string SETTINGS::GetProblemBaseFolder() { return ProblemBaseFolder; }
std::string SETTINGS::GetUserBaseFolder() { return UserBaseFolder; }
std::string SETTINGS::GetVerifyCodeBaseFolder() { return VerifyCodeBaseFolder; }
std::string SETTINGS::GetSettingsBaseFolder() { return SettingBaseFolder; }
std::string SETTINGS::GetTokenBaseFolder() { return TokenBaseFolder; }
std::string SETTINGS::GetJudgeUser() { return JudgeUser; }
int SETTINGS::GetJudgeUserID() { return JudgeUserID; }
// std::string SETTINGS::GetJudgeUserGroup() { return JudgeUserGroup; }
int SETTINGS::GetJudgeUserGroupID() { return JudgeUserGroupID; }
bool SETTINGS::IsBannedSystemCall(int SystemCall, int CallCount)
{
    if (SystemCall < 0 || SystemCall >= SystemCallCount)
    {
        Logger.Warning("System call " + std::to_string(SystemCall) + " is not valid");
        return true;
    }
    return SystemCalls[SystemCall].AvailableCount < CallCount &&
           SystemCalls[SystemCall].AvailableCount != -1;
}
std::string SETTINGS::GetSystemCallName(int SystemCall)
{
    if (SystemCall < 0 || SystemCall >= SystemCallCount)
    {
        Logger.Warning("System call " + std::to_string(SystemCall) + " is not valid");
        return "";
    }
    return SystemCalls[SystemCall].Name;
}
std::string SETTINGS::GetCompiler() { return Compiler; }
int SETTINGS::GetSocketPort() { return SocketPort; }
int SETTINGS::GetCompileTimeLimit() { return CompileTimeLimit; }
int SETTINGS::GetCompileOutputLimit() { return CompileOutputLimit; }
std::string SETTINGS::GetEmail() { return Email; }
std::string SETTINGS::GetEmailPassword() { return EmailPassword; }

void SETTINGS::SetJudgeUser(std::string JudgeUser)
{
    this->JudgeUser = JudgeUser;
    CheckJudgeUser();
    Logger.Info("JudgeUser is set to " + JudgeUser);
}
void SETTINGS::SetSystemCallAvailableCount(int SystemCall, int AvailableCount)
{
    if (SystemCall < 0 || SystemCall >= SystemCallCount)
        Logger.Warning("System call " + std::to_string(SystemCall) + " is not valid");
    else
    {
        SystemCalls[SystemCall].AvailableCount = AvailableCount;
        Logger.Info("Set system call " + std::to_string(SystemCall) + " available count to " + std::to_string(AvailableCount));
    }
}
void SETTINGS::SetCompiler(std::string Compiler)
{
    this->Compiler = Compiler;
    CheckCompiler();
    Logger.Info("Compiler is set to " + Compiler);
}
void SETTINGS::SetSocketPort(int SocketPort) { this->SocketPort = SocketPort; }
void SETTINGS::SetCompileTimeLimit(int CompileTimeLimit) { this->CompileTimeLimit = CompileTimeLimit; }
void SETTINGS::SetCompileOutputLimit(int CompileOutputLimit) { this->CompileOutputLimit = CompileOutputLimit; }
void SETTINGS::SetEmail(std::string Email) { this->Email = Email; }
void SETTINGS::SetEmailPassword(std::string EmailPassword) { this->EmailPassword = EmailPassword; }

void SETTINGS::CheckJudgeUser()
{
    if (JudgeUser == "")
        Logger.Fetal("Judge user is empty");
    GetJudgeUserIDByUserName();

    BaseFolder = "/home/" + JudgeUser;
    if (access(BaseFolder.c_str(), F_OK) == -1)
    {
        if (mkdir(BaseFolder.c_str(), 0755) == -1)
            Logger.Fetal("Can not create base folder");
        if (chown(BaseFolder.c_str(), JudgeUserID, JudgeUserGroupID) == -1)
            Logger.Fetal("Can not change base folder owner");
    }

    Logger.SetLogFileName(Settings.GetBaseFolder() + "/Settings.log");

    SubmissionBaseFolder = BaseFolder + "/Submissions";
    if (access(SubmissionBaseFolder.c_str(), F_OK) == -1)
    {
        if (mkdir(SubmissionBaseFolder.c_str(), 0755) == -1)
            Logger.Fetal("Can not create judge base folder");
        if (chown(SubmissionBaseFolder.c_str(), JudgeUserID, JudgeUserGroupID) == -1)
            Logger.Fetal("Can not change judge base folder owner");
    }

    ProblemBaseFolder = BaseFolder + "/Problems";
    if (access(ProblemBaseFolder.c_str(), F_OK) == -1)
    {
        if (mkdir(ProblemBaseFolder.c_str(), 0755) == -1)
            Logger.Fetal("Can not create problem base folder");
        if (chown(ProblemBaseFolder.c_str(), JudgeUserID, JudgeUserGroupID) == -1)
            Logger.Fetal("Can not change problem base folder owner");
    }

    VerifyCodeBaseFolder = BaseFolder + "/VerifyCodes";
    if (access(VerifyCodeBaseFolder.c_str(), F_OK) == -1)
    {
        if (mkdir(VerifyCodeBaseFolder.c_str(), 0755) == -1)
            Logger.Fetal("Can not create verify code base folder");
        if (chown(VerifyCodeBaseFolder.c_str(), JudgeUserID, JudgeUserGroupID) == -1)
            Logger.Fetal("Can not change verify code base folder owner");
    }

    SettingBaseFolder = BaseFolder + "/Settings";
    if (access(SettingBaseFolder.c_str(), F_OK) == -1)
    {
        if (mkdir(SettingBaseFolder.c_str(), 0755) == -1)
            Logger.Fetal("Can not create setting base folder");
        if (chown(SettingBaseFolder.c_str(), JudgeUserID, JudgeUserGroupID) == -1)
            Logger.Fetal("Can not change setting base folder owner");
    }

    TokenBaseFolder = BaseFolder + "/Token";
    if (access(TokenBaseFolder.c_str(), F_OK) == -1)
    {
        if (mkdir(TokenBaseFolder.c_str(), 0755) == -1)
            Logger.Fetal("Can not create token base folder");
        if (chown(TokenBaseFolder.c_str(), JudgeUserID, JudgeUserGroupID) == -1)
            Logger.Fetal("Can not change token base folder owner");
    }

    UserBaseFolder = BaseFolder + "/Users";
    if (access(UserBaseFolder.c_str(), F_OK) == -1)
    {
        if (mkdir(UserBaseFolder.c_str(), 0755) == -1)
            Logger.Fetal("Can not create user base folder");
        if (chown(UserBaseFolder.c_str(), JudgeUserID, JudgeUserGroupID) == -1)
            Logger.Fetal("Can not change user base folder owner");
    }
}
void SETTINGS::GetJudgeUserIDByUserName()
{
    std::ifstream InputFile("/etc/passwd");
    if (!InputFile.is_open())
        Logger.Fetal("Can not open password file \"/etc/passwd\"");
    std::string Line;
    while (getline(InputFile, Line))
    {
        if (Line.substr(0, Line.find(":")) == JudgeUser)
        {
            int StartPosition = Line.find(":", Line.find(":") + 1) + 1;
            int EndPosition = Line.find(":", StartPosition);
            JudgeUserID = atoi(Line.substr(StartPosition, EndPosition - StartPosition).c_str());
            StartPosition = EndPosition;
            EndPosition = Line.find(":", StartPosition);
            JudgeUserGroupID = atoi(Line.substr(StartPosition, EndPosition - StartPosition).c_str());
            Logger.Debug("Judge user \"" + JudgeUser + "\" is " +
                         std::to_string(JudgeUserID) + " in user id, " +
                         "\"" + std::to_string(JudgeUserGroupID) + "\" in group id");
            // GetJudgeUserGroupNameByGroupID();
            return;
        }
    }
    Logger.Fetal("Judge user \"" + JudgeUser + "\" does not exist");
}
// void SETTINGS::GetJudgeUserGroupNameByGroupID()
// {
//     std::ifstream InputFile("/etc/group");
//     std::string Line;
//     while (getline(InputFile, Line))
//     {
//         int FirstColonPosition = Line.find(":");
//         int SecondColonPosition = Line.find(":", FirstColonPosition);
//         int ThirdColonPosition = Line.find(":", SecondColonPosition);
//         if (Line.substr(SecondColonPosition, ThirdColonPosition - SecondColonPosition) == std::to_string(JudgeUserGroupID))
//         {
//             JudgeUserGroup = Line.substr(0, FirstColonPosition);
//             Logger.Info("Judge user group " + std::to_string(JudgeUserGroupID) + " is \"" + JudgeUserGroup + "\" in group name");
//             return;
//         }
//     }
//     Logger.Fetal("Judge user group " + std::to_string(JudgeUserGroupID) + " does not exist");
// }
void SETTINGS::CheckCompiler()
{
    if (access(SubmissionBaseFolder.c_str(), X_OK) != 0)
        Logger.Fetal("Compiler does not exist");
}

void SETTINGS::CheckSettings()
{
    CheckJudgeUser();
    CheckCompiler();
}

SETTINGS Settings;
