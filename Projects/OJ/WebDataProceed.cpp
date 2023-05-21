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
    RETURN_JSON_IF_FALSE(std::regex_match(Username, REGEX_USERNAME), "Username invalid")
    RETURN_JSON_IF_FALSE(!std::regex_match(Password, REGEX_NOT_PASSWORD), "Password invalid")
    RETURN_JSON_IF_FALSE(access((Settings.GetUserBaseFolder() + "/" + Username).c_str(), F_OK | R_OK) == 0, "No such user")
    RETURN_JSON_IF_FALSE(access((Settings.GetUserBaseFolder() + "/" + Username + "/Password").c_str(), F_OK | R_OK) == 0, "No password store in system")
    std::string RightPassword;
    RETURN_JSON_IF_FAILED(Utilities.LoadFile(Settings.GetUserBaseFolder() + "/" + Username + "/Password", RightPassword))
    RETURN_JSON_IF_FALSE(Password == Utilities.RemoveSpaces(RightPassword), "Password incorrect")
    std::string Token;
    const std::string TokenCharList = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 32; i++)
        Token.push_back(TokenCharList[rand() % TokenCharList.size()]);
    RETURN_JSON_IF_FAILED(Utilities.MakeDir(Settings.GetTokenBaseFolder() + "/" + Token))
    RETURN_JSON_IF_FAILED(Utilities.SaveFile(Settings.GetTokenBaseFolder() + "/" + Token + "/Username", Username))
    RETURN_JSON_IF_FAILED(Utilities.SaveFile(Settings.GetTokenBaseFolder() + "/" + Token + "/SaveTime", time(NULL)))
    configor::json ResponseJSON = BaseJSON;
    ResponseJSON["Success"] = true;
    ResponseJSON["Message"] = "Login success";
    ResponseJSON["Data"]["Token"] = Token;
    return ResponseJSON;
}
configor::json WEB_DATA_PROCEED::CheckUsernameAvailable(std::string Username)
{
    RETURN_JSON_IF_FALSE(std::regex_match(Username, REGEX_USERNAME), "Username invalid")
    RETURN_JSON_IF_FALSE(access((Settings.GetUserBaseFolder() + "/" + Username).c_str(), F_OK | R_OK) == -1, "Username already exist")
    CREATE_JSON(true, "Username available");
}
configor::json WEB_DATA_PROCEED::SendVerifyCode(std::string EmailAddress)
{
    RETURN_JSON_IF_FALSE(std::regex_match(EmailAddress, REGEX_EMAIL_ADDRESS), "Email address invalid")
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
    RETURN_JSON_IF_FAILED(Utilities.SaveFile(Settings.GetVerifyCodeBaseFolder() + "/" + EmailAddress, CorrectCode))
    std::string EmailContent = "Your verify code is " + CorrectCode;
    RETURN_JSON_IF_FAILED(Utilities.SendEmail(EmailAddress, "Verify Code", EmailContent))
    CREATE_JSON(true, "Send verify code success")
}
configor::json WEB_DATA_PROCEED::Register(std::string Username, std::string Password, std::string Nickname, std::string EmailAddress, std::string VerifyCode)
{
    RETURN_JSON_IF_FALSE(std::regex_match(Username, REGEX_USERNAME), "Username invalid")
    RETURN_JSON_IF_FALSE(!std::regex_match(Password, REGEX_NOT_PASSWORD), "Password invalid")
    RETURN_JSON_IF_FALSE(std::regex_match(Nickname, REGEX_NICKNAME), "Nickname invalid")
    RETURN_JSON_IF_FALSE(std::regex_match(EmailAddress, REGEX_EMAIL_ADDRESS), "Email address invalid")
    RETURN_JSON_IF_FALSE(std::regex_match(VerifyCode, REGEX_VERIFY_CODE), "Verify code invalid")
    RETURN_JSON_IF_FALSE(access((Settings.GetUserBaseFolder() + "/" + Username).c_str(), F_OK | R_OK) == -1, "Username already exist")
    std::string RightVerifyCode;
    RETURN_JSON_IF_FAILED(Utilities.LoadFile(Settings.GetVerifyCodeBaseFolder() + "/" + EmailAddress, RightVerifyCode))
    RETURN_JSON_IF_FALSE(VerifyCode == Utilities.RemoveSpaces(RightVerifyCode), "Verify code incorrect")
    RETURN_JSON_IF_FAILED(Utilities.MakeDir(Settings.GetUserBaseFolder() + "/" + Username))
    RETURN_JSON_IF_FAILED(Utilities.SaveFile(Settings.GetUserBaseFolder() + "/" + Username + "/Password", Password))
    RETURN_JSON_IF_FAILED(Utilities.SaveFile(Settings.GetUserBaseFolder() + "/" + Username + "/Nickname", Nickname))
    RETURN_JSON_IF_FAILED(Utilities.SaveFile(Settings.GetUserBaseFolder() + "/" + Username + "/EmailAddress", EmailAddress))
    RETURN_JSON_IF_FAILED(Utilities.SaveFile(Settings.GetUserBaseFolder() + "/" + Username + "/RegisterTime", time(NULL)))
    CREATE_JSON(true, "Register success")
}
configor::json WEB_DATA_PROCEED::CheckTokenAvailable(std::string Token)
{
    RETURN_JSON_IF_FALSE(access((Settings.GetTokenBaseFolder() + "/" + Token).c_str(), F_OK | R_OK) == 0, "Token does not exist")
    int SaveTime;
    std::string Username;
    RETURN_JSON_IF_FAILED(Utilities.LoadFile(Settings.GetTokenBaseFolder() + "/" + Token + "/SaveTime", SaveTime))
    RETURN_JSON_IF_FAILED(Utilities.LoadFile(Settings.GetTokenBaseFolder() + "/" + Token + "/Username", Username))
    RETURN_JSON_IF_FALSE_WITH_OPERATION(time(NULL) - SaveTime < 7 * 24 * 60 * 60, "Token expired", Utilities.RemoveDir(Settings.GetTokenBaseFolder() + "/" + Token))
    CREATE_JSON(true, "Token available")
}
configor::json WEB_DATA_PROCEED::GetSubmission(int SubmissionID)
{
    SUBMISSION Submission;
    RETURN_JSON_IF_FAILED(Submission.Load(SubmissionID))
    configor::json ResponseJSON = BaseJSON;
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
    return ResponseJSON;
}
configor::json WEB_DATA_PROCEED::Submit(std::string ProblemID, bool EnableO2, std::string Code)
{
    SUBMISSION Submission;
    RETURN_JSON_IF_FAILED(Submission.Set(Code, ProblemID))
    Submission.EnableO2 = EnableO2;
    int SubmissionID;
    RETURN_JSON_IF_FAILED(JudgingList.Add(Submission, SubmissionID))
    configor::json ResponseJSON = BaseJSON;
    ResponseJSON["Success"] = true;
    ResponseJSON["Message"] = "Submit success";
    ResponseJSON["Data"]["SubmissionID"] = SubmissionID;
    return ResponseJSON;
}
configor::json WEB_DATA_PROCEED::GetProblem(std::string ProblemID)
{
    configor::json ResponseJSON = BaseJSON;
    PROBLEM Problem;
    RETURN_JSON_IF_FAILED(Problem.Load(ProblemID))
    ResponseJSON["Success"] = true;
    ResponseJSON["Data"]["ID"] = Problem.ID;
    ResponseJSON["Data"]["Title"] = Problem.Title;
    ResponseJSON["Data"]["Description"] = Problem.Description;
    ResponseJSON["Data"]["Input"] = Problem.Input;
    ResponseJSON["Data"]["Output"] = Problem.Output;
    configor::json::array_type Samples;
    for (auto i : Problem.Samples)
    {
        configor::json TempSample;
        TempSample["Input"] = i.Input;
        TempSample["Output"] = i.Output;
        Samples.push_back(TempSample);
    }
    ResponseJSON["Data"]["Samples"] = Samples;
    configor::json::array_type TestGroups;
    for (auto i : Problem.TestGroups)
    {
        configor::json TempTestGroup;
        TempTestGroup["ID"] = i.ID;
        configor::json::array_type TestCases;
        for (auto j : i.TestCases)
        {
            configor::json TempTestCase;
            TempTestCase["ID"] = j.ID;
            TempTestCase["TimeLimit"] = j.TimeLimit;
            TempTestCase["MemoryLimit"] = j.MemoryLimit;
            TempTestCase["Score"] = j.Score;
            ResponseJSON["Data"]["IOFileName"] = j.IOFileName;
            TestCases.push_back(TempTestCase);
        }
        TempTestGroup["TestCases"] = TestCases;
        TestGroups.push_back(TempTestGroup);
    }
    ResponseJSON["Data"]["TestGroups"] = TestGroups;
    ResponseJSON["Data"]["Range"] = Problem.Range;
    ResponseJSON["Data"]["Hint"] = Problem.Hint;
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
                else if (RequestJSON["Action"].as_string() == "GetProblem")
                {
                    if (!CheckTypes(RequestJSON, {{"ProblemID", configor::config_value_type::string},
                                                  {"Token", configor::config_value_type::string}}))
                        ResponseJSON["Message"] = "Invalid parameters";
                    else if (CheckTokenAvailable(RequestJSON["Data"]["Token"].as_string())["Success"].as_bool() == false)
                        ResponseJSON["Message"] = "Invalid token";
                    else
                        ResponseJSON = GetProblem(RequestJSON["Data"]["ProblemID"].as_string());
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
        if (!Utilities.LoadFile(BasicFolder + "/main.js", Data).Success)
            Data = "System error: can not load file /main.js";
        HTTPResponse.SetBody(Data);
        HTTPResponse.SetHeader("Content-Type", "application/javascript");
    }
    else if (HTTPRequest.GetPath() == "/main.css")
    {
        std::string Data;
        if (!Utilities.LoadFile(BasicFolder + "/main.css", Data).Success)
            Data = "System error: can not load file /main.css";
        HTTPResponse.SetBody(Data);
        HTTPResponse.SetHeader("Content-Type", "text/css");
    }
    else
    {
        std::string Data;
        if (!Utilities.LoadFile(BasicFolder + "/main.html", Data).Success)
            Data = "System error: can not load file /main.html";
        HTTPResponse.SetBody(Data);
    }
    return HTTPResponse;
}
