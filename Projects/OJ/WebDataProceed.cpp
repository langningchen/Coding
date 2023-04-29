#include "WebDataProceed.hpp"
#include "Settings.hpp"
#include "TestCase.hpp"
#include "TestGroup.hpp"
#include "Regexes.hpp"
#include "ProblemList.hpp"
#include "Submission.hpp"
#include "JudgingList.hpp"
#include "Utilities.hpp"
#include <string>
#include <regex>
#include <unistd.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <list>
#include <algorithm>

bool WEB_DATA_PROCEED::CheckTypes(configor::json JSON, std::vector<std::pair<std::string, configor::config_value_type>> Types)
{
    for (auto i : Types)
        if (JSON["Data"][i.first].type() != i.second)
            return false;
    return true;
}
configor::json WEB_DATA_PROCEED::Login(std::string Username, std::string Password)
{
    configor::json ResponseJSON = BaseJSON;
    if (!std::regex_match(Username, REGEX_USERNAME))
        ResponseJSON["Message"] = "Username invalid";
    else if (std::regex_match(Password, REGEX_NOT_PASSWORD))
        ResponseJSON["Message"] = "Password invalid";
    else
    {
        if (access((Settings.GetUserBaseFolder() + "/" + Username).c_str(), F_OK | R_OK) == -1)
            ResponseJSON["Message"] = "No such user";
        else if (access((Settings.GetUserBaseFolder() + "/" + Username + "/Password").c_str(), F_OK | R_OK) == -1)
            ResponseJSON["Message"] = "No password store in system";
        else
        {
            std::string RightPassword;
            if (!Utilities.LoadFile(Settings.GetUserBaseFolder() + "/" + Username + "/Password", RightPassword))
                ResponseJSON["Message"] = "Can not load password in system";
            else if (Password != Utilities.RemoveSpaces(RightPassword))
                ResponseJSON["Message"] = "Password incorrect";
            else
            {
                std::string Token;
                for (int i = 0; i < 32; i++)
                    Token.push_back(random() % 95 + 32);
                if (!Utilities.MakeDir(Settings.GetTokenBaseFolder() + "/" + Token) ||
                    !Utilities.SaveFile(Settings.GetTokenBaseFolder() + "/" + Token + "/Username", Username) ||
                    !Utilities.SaveFile(Settings.GetTokenBaseFolder() + "/" + Token + "/SaveTime", time(NULL)))
                    ResponseJSON["Message"] = "Can not save token data";
                else
                {
                    ResponseJSON["Success"] = true;
                    ResponseJSON["Data"]["Token"] = Token;
                }
            }
        }
    }
    return ResponseJSON;
}
configor::json WEB_DATA_PROCEED::CheckUsernameAvailable(std::string Username)
{
    configor::json ResponseJSON = BaseJSON;
    if (!std::regex_match(Username, REGEX_USERNAME))
        ResponseJSON["Message"] = "Username invalid";
    else if (access((Settings.GetUserBaseFolder() + "/" + Username).c_str(), F_OK | R_OK) == -1)
        ResponseJSON["Success"] = true;
    else
        ResponseJSON["Message"] = "Username already exist";
    return ResponseJSON;
}
configor::json WEB_DATA_PROCEED::SendVerifyCode(std::string EmailAddress)
{
    configor::json ResponseJSON = BaseJSON;
    if (!std::regex_match(EmailAddress, REGEX_EMAIL_ADDRESS))
        ResponseJSON["Message"] = "Email address invalid";
    else
    {
        int TempCorrectCode = rand() % 1000000;
        std::string CorrectCode;
        if (TempCorrectCode < 10)
            CorrectCode += "0";
        if (TempCorrectCode < 100)
            CorrectCode += "0";
        if (TempCorrectCode < 1000)
            CorrectCode += "0";
        if (TempCorrectCode < 10000)
            CorrectCode += "0";
        if (TempCorrectCode < 100000)
            CorrectCode += "0";
        CorrectCode += std::to_string(TempCorrectCode);
        if (!Utilities.SaveFile(Settings.GetVerifyCodeBaseFolder() + "/" + EmailAddress, CorrectCode))
            ResponseJSON["Message"] = "Can not save verify code";
        else
        {
            std::string EmailContent = "Your verify code is " + CorrectCode;
            if (!Utilities.SendEmail(EmailAddress, "Verify Code", EmailContent))
                ResponseJSON["Message"] = "Can not send email";
            else
                ResponseJSON["Success"] = true;
        }
    }
    return ResponseJSON;
}
configor::json WEB_DATA_PROCEED::Register(std::string Username, std::string Password, std::string Nickname, std::string EmailAddress, std::string VerifyCode)
{
    configor::json ResponseJSON = BaseJSON;
    if (!std::regex_match(Username, REGEX_USERNAME))
        ResponseJSON["Message"] = "Username invalid";
    else if (std::regex_match(Password, REGEX_NOT_PASSWORD))
        ResponseJSON["Message"] = "Password invalid";
    else if (!std::regex_match(Nickname, REGEX_NICKNAME))
        ResponseJSON["Message"] = "Nickname invalid";
    else if (!std::regex_match(EmailAddress, REGEX_EMAIL_ADDRESS))
        ResponseJSON["Message"] = "Email address invalid";
    else if (!std::regex_match(VerifyCode, REGEX_VERIFY_CODE))
        ResponseJSON["Message"] = "Verify code invalid";
    else if (access((Settings.GetUserBaseFolder() + "/" + Username).c_str(), F_OK | R_OK) != -1)
        ResponseJSON["Message"] = "Username already exist";
    else
    {
        std::string RightVerifyCode;
        if (!Utilities.LoadFile(Settings.GetVerifyCodeBaseFolder() + "/" + EmailAddress, RightVerifyCode))
            ResponseJSON["Message"] = "Can not load verify code";
        else if (VerifyCode != Utilities.RemoveSpaces(RightVerifyCode))
            ResponseJSON["Message"] = "Verify code incorrect";
        else if (!Utilities.MakeDir(Settings.GetUserBaseFolder() + "/" + Username) ||
                 !Utilities.SaveFile(Settings.GetUserBaseFolder() + "/" + Username + "/Password", Password) ||
                 !Utilities.SaveFile(Settings.GetUserBaseFolder() + "/" + Username + "/Nickname", Nickname) ||
                 !Utilities.SaveFile(Settings.GetUserBaseFolder() + "/" + Username + "/EmailAddress", EmailAddress) ||
                 !Utilities.SaveFile(Settings.GetUserBaseFolder() + "/" + Username + "/RegisterTime", time(NULL)))
            ResponseJSON["Message"] = "Can not save user data";
        else
            ResponseJSON["Success"] = true;
    }
    return ResponseJSON;
}
configor::json WEB_DATA_PROCEED::CheckTokenAvailable(std::string Token)
{
    configor::json ResponseJSON = BaseJSON;
    std::string CurrentTokenBaseFolder = Settings.GetTokenBaseFolder() + "/" + Token;
    if (access(CurrentTokenBaseFolder.c_str(), F_OK | R_OK) == -1)
        ResponseJSON["Message"] = "Token does not exist";
    else
    {
        int SaveTime;
        std::string Username;
        if (!Utilities.LoadFile(CurrentTokenBaseFolder + "/SaveTime", SaveTime) ||
            !Utilities.LoadFile(CurrentTokenBaseFolder + "/Username", Username))
        {
            ResponseJSON["Message"] = "Token does not exist";
            Utilities.RemoveDir(CurrentTokenBaseFolder);
        }
        else if (time(NULL) - SaveTime > 7 * 24 * 60 * 60)
        {
            ResponseJSON["Message"] = "Token expired";
            Utilities.RemoveDir(CurrentTokenBaseFolder);
        }
        else
            ResponseJSON["Success"] = true;
    }
    return ResponseJSON;
}
configor::json WEB_DATA_PROCEED::GetSubmission(int SubmissionID)
{
    configor::json ResponseJSON = BaseJSON;
    SUBMISSION Submission;
    if (!Submission.Load(SubmissionID))
        ResponseJSON["Message"] = "Submission load failed";
    else
    {
        ResponseJSON["Success"] = true;
        ResponseJSON["Data"]["Result"] = (int)Submission.Result;
        ResponseJSON["Data"]["Description"] = Submission.Description;
        ResponseJSON["Data"]["ProblemID"] = Submission.ProblemID;
        ResponseJSON["Data"]["Source"] = Submission.Source;
        ResponseJSON["Data"]["Time"] = Submission.Time;
        ResponseJSON["Data"]["TimeSum"] = Submission.TimeSum;
        ResponseJSON["Data"]["Memory"] = Submission.Memory;
        ResponseJSON["Data"]["Score"] = Submission.Score;
        configor::json::array_type TestGroups;
        for (auto i : Submission.TestGroups)
        {
            configor::json TempTestGroup;
            TempTestGroup["Index"] = i.ID;
            TempTestGroup["Score"] = i.Score;
            TempTestGroup["Result"] = (int)i.Result;
            TempTestGroup["TestCasesPassed"] = i.TestCasesPassed;
            TempTestGroup["Time"] = i.Time;
            TempTestGroup["TimeSum"] = i.TimeSum;
            TempTestGroup["Memory"] = i.Memory;
            TempTestGroup["TestCases"].array({});
            configor::json::array_type TestCases;
            for (auto j : i.TestCases)
            {
                configor::json TempTestCase;
                TempTestCase["Index"] = j.ID;
                TempTestCase["Result"] = (int)j.Result;
                TempTestCase["Description"] = j.Description;
                TempTestCase["Time"] = j.Time;
                TempTestCase["TimeLimit"] = j.TimeLimit;
                TempTestCase["Memory"] = j.Memory;
                TempTestCase["MemoryLimit"] = j.MemoryLimit;
                TempTestCase["Score"] = j.Score;
                TestCases.push_back(TempTestCase);
            }
            TempTestGroup["TestCases"] = TestCases;
            TestGroups.push_back(TempTestGroup);
        }
        ResponseJSON["Data"]["TestGroups"] = TestGroups;
    }
    return ResponseJSON;
}
configor::json WEB_DATA_PROCEED::Submit(std::string ProblemID, bool EnableO2, std::string Code)
{
    configor::json ResponseJSON = BaseJSON;
    SUBMISSION Submission(Code, ProblemID);
    Submission.EnableO2 = EnableO2;
    int SubmissionID = JudgingList.Add(Submission);
    if (SubmissionID == 0)
        ResponseJSON["Message"] = "Submit failed";
    {
        ResponseJSON["Success"] = true;
        ResponseJSON["Data"]["SubmissionID"] = SubmissionID;
    }
    return ResponseJSON;
}

WEB_DATA_PROCEED::WEB_DATA_PROCEED()
{
    Logger.SetLogFileName(Settings.GetBaseFolder() + "/WebDataProceed.log");
}

HTTP_RESPONSE WEB_DATA_PROCEED::Proceed(HTTP_REQUEST HTTPRequest)
{
    std::string BasicFolder = "/home/langningc2009/Coding/Projects/OJ/HTML";
    HTTP_RESPONSE HTTPResponse;
    if (HTTPRequest.GetPath() == "/api")
    {
        HTTPResponse.SetHeader("Content-Type", "application/json");
        configor::json ResponseJSON = BaseJSON;
        if (HTTPRequest.GetVerb() != "POST")
            ResponseJSON["Message"] = "Only allow POST";
        else
        {
            try
            {
                configor::json RequestJSON = configor::json::parse(HTTPRequest.GetBody());
                if (RequestJSON["Action"].type() != configor::config_value_type::string)
                    ResponseJSON["Message"] = "Action must be string";
                else if (RequestJSON["Action"].as_string() == "Login")
                {
                    if (!CheckTypes(RequestJSON, {{"Username", configor::config_value_type::string},
                                                  {"Password", configor::config_value_type::string}}))
                        ResponseJSON["Message"] = "Invalid parameters";
                    else
                        ResponseJSON = Login(RequestJSON["Data"]["Username"].as_string(),
                                             RequestJSON["Data"]["Password"].as_string());
                }
                else if (RequestJSON["Action"].as_string() == "CheckUsernameAvailable")
                {
                    if (!CheckTypes(RequestJSON, {{"Username", configor::config_value_type::string}}))
                        ResponseJSON["Message"] = "Invalid parameters";
                    else
                        ResponseJSON = CheckUsernameAvailable(RequestJSON["Data"]["Username"].as_string());
                }
                else if (RequestJSON["Action"].as_string() == "SendVerifyCode")
                {
                    if (!CheckTypes(RequestJSON, {{"EmailAddress", configor::config_value_type::string}}))
                        ResponseJSON["Message"] = "Invalid parameters";
                    else
                        ResponseJSON = SendVerifyCode(RequestJSON["Data"]["EmailAddress"].as_string());
                }
                else if (RequestJSON["Action"].as_string() == "Register")
                {
                    if (!CheckTypes(RequestJSON, {{"Username", configor::config_value_type::string},
                                                  {"Password", configor::config_value_type::string},
                                                  {"Nickname", configor::config_value_type::string},
                                                  {"EmailAddress", configor::config_value_type::string},
                                                  {"VerifyCode", configor::config_value_type::string}}))
                        ResponseJSON["Message"] = "Invalid parameters";
                    else
                        ResponseJSON = Register(RequestJSON["Data"]["Username"].as_string(),
                                                RequestJSON["Data"]["Password"].as_string(),
                                                RequestJSON["Data"]["Nickname"].as_string(),
                                                RequestJSON["Data"]["EmailAddress"].as_string(),
                                                RequestJSON["Data"]["VerifyCode"].as_string());
                }
                else if (RequestJSON["Action"].as_string() == "CheckTokenAvailable")
                {
                    if (!CheckTypes(RequestJSON, {{"Token", configor::config_value_type::string}}))
                        ResponseJSON["Message"] = "Invalid parameters";
                    else
                        ResponseJSON = CheckTokenAvailable(RequestJSON["Data"]["Token"].as_string());
                }
                else if (RequestJSON["Action"].as_string() == "GetSubmission")
                {
                    if (!CheckTypes(RequestJSON, {{"SubmissionID", configor::config_value_type::number_integer},
                                                  {"Token", configor::config_value_type::string}}))
                        ResponseJSON["Message"] = "Invalid parameters";
                    else if (CheckTokenAvailable(RequestJSON["Data"]["Token"].as_string())["Success"].as_bool() == false)
                        ResponseJSON["Message"] = "Invalid token";
                    else
                        ResponseJSON = GetSubmission(RequestJSON["Data"]["SubmissionID"].as_integer());
                }
                else if (RequestJSON["Action"].as_string() == "Submit")
                {
                    if (!CheckTypes(RequestJSON, {{"ProblemID", configor::config_value_type::string},
                                                  {"EnableO2", configor::config_value_type::boolean},
                                                  {"Code", configor::config_value_type::string},
                                                  {"Token", configor::config_value_type::string}}))
                        ResponseJSON["Message"] = "Invalid parameters";
                    else if (CheckTokenAvailable(RequestJSON["Data"]["Token"].as_string())["Success"].as_bool() == false)
                        ResponseJSON["Message"] = "Invalid token";
                    else
                        ResponseJSON = Submit(RequestJSON["Data"]["ProblemID"].as_string(),
                                              RequestJSON["Data"]["EnableO2"].as_bool(),
                                              RequestJSON["Data"]["Code"].as_string());
                }
                else
                    ResponseJSON["Message"] = "No such action";
            }
            catch (const configor::configor_exception &e)
            {
                ResponseJSON["Message"] = std::string("JSON parse failed: ") + e.what();
            }
        }
        HTTPResponse.SetBody(ResponseJSON.dump());
    }
    else if (HTTPRequest.GetPath() == "/main.js")
    {
        std::string Data;
        if (!Utilities.LoadFile(BasicFolder + "/main.js", Data))
            Data = "System error: can not load file /main.js";
        HTTPResponse.SetBody(Data);
        HTTPResponse.SetHeader("Content-Type", "application/javascript");
    }
    else if (HTTPRequest.GetPath() == "/main.css")
    {
        std::string Data;
        if (!Utilities.LoadFile(BasicFolder + "/main.css", Data))
            Data = "System error: can not load file /main.css";
        HTTPResponse.SetBody(Data);
        HTTPResponse.SetHeader("Content-Type", "text/css");
    }
    else
    {
        std::string Data;
        if (!Utilities.LoadFile(BasicFolder + "/main.html", Data))
            Data = "System error: can not load file /main.html";
        HTTPResponse.SetBody(Data);
    }
    return HTTPResponse;
}
