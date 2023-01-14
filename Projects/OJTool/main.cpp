#include "Curl.hpp"
#include <regex>
#include <errno.h>
#include "tidy/tidy.h"
#include "tidy/tidybuffio.h"
#include "TinyXML.hpp"
#include "MD5.hpp"

// If the login failed, set the Failed flag to true, and exit the program
bool Failed = false;

class TOOL
{
private:
    class LUOGU
    {
    private:
        map<int, string> LanguageName, LanguageMarkdownName;
        map<int, pair<string, string>> DifficultyName, TagName, RecordName;
        map<string, string> TypeName, ColorList;

    public:
        LUOGU();
        void Login(string Username, string Password);
        void ClockIn();
        void GetQuestionDetail(string QuestionID);
        void SubmitCode(string QuestionID);
        void GetAnswerOrTips(string QuestionID);
    };
    class ETIGER
    {
    private:
        string Token = "";
        map<int, pair<string, string>> DifficultyName;

    public:
        ETIGER();
        void Login(string Username, string Password);
        void ClockIn();
        void GetQuestionDetail(string QuestionID);
        void SubmitCode(string QuestionID);
        void GetAnswerOrTips(string QuestionID);
    };
    class CODEFORCES
    {
    private:
        const string ftaa = "rv5q0yv00p85nhpyi7";
        const string bfaa = "f1b3f18c715565b589b7823cda7448ce";
        string GetCRSF();
        string OutputPre(TiXmlElement *Input);
        string Output(TiXmlElement *Input, bool InLatex = false);
        string ToNormalName(string Input);
        string TidyHTMLDocument(string Input);

    public:
        void Login(string Username, string Password);
        void GetQuestionDetail(string QuestionID);
        void SubmitCode(string QuestionID);
    };
    class UVA
    {
    public:
        void Login(string Username, string Password);
        void GetQuestionDetail(string QuestionID);
        void SubmitCode(string QuestionID);
    };

public:
    TOOL(string FileName, string Operation);
    TOOL(string ServerName, string Username, string Password);
    ~TOOL();
};
string GetCPHFileName(string Path, string FileName)
{
    // Create an object of the MD5 class to encode the file name
    MD5 MD5Encoder;
    // Return the file name in the CPH directory
    return "../../../CPH/." +
           FileName +
           ".cpp_" +
           // Encode the full path of the file
           MD5Encoder.encode("/workspaces/Coding/" +
                             Path +
                             "/" +
                             FileName +
                             ".cpp") +
           // Add the .prob extension to the file name
           ".prob";
}
TOOL::LUOGU::LUOGU()
{
    ColorList["blue-1"] = "e0f7ff";
    ColorList["blue-2"] = "89d1f5";
    ColorList["blue-3"] = "3498db";
    ColorList["blue-4"] = "14558f";
    ColorList["blue-5"] = "052242";
    ColorList["green-1"] = "d9f0c7";
    ColorList["green-2"] = "94d66d";
    ColorList["green-3"] = "52c41a";
    ColorList["green-4"] = "22700a";
    ColorList["green-5"] = "072401";
    ColorList["purple-1"] = "fbedff";
    ColorList["purple-2"] = "ce8ee8";
    ColorList["purple-3"] = "9d3dcf";
    ColorList["purple-4"] = "561982";
    ColorList["purple-5"] = "1f0736";
    ColorList["orange-1"] = "ffedb5";
    ColorList["orange-2"] = "ffce63";
    ColorList["orange-3"] = "f39c11";
    ColorList["orange-4"] = "a65b00";
    ColorList["orange-5"] = "592b00";
    ColorList["pink-1"] = "fff0f0";
    ColorList["pink-2"] = "ff9ea3";
    ColorList["pink-3"] = "fe4c61";
    ColorList["pink-4"] = "b3243e";
    ColorList["pink-5"] = "660e24";
    ColorList["lapis-1"] = "cad5e8";
    ColorList["lapis-2"] = "728dcf";
    ColorList["lapis-3"] = "2949b4";
    ColorList["lapis-4"] = "0e1d69";
    ColorList["lapis-5"] = "02051c";
    ColorList["gold-1"] = "fff6ba";
    ColorList["gold-2"] = "ffe169";
    ColorList["gold-3"] = "ffc116";
    ColorList["gold-4"] = "b37700";
    ColorList["gold-5"] = "663d00";
    ColorList["cyan-1"] = "b5f5ec";
    ColorList["cyan-2"] = "5cdbd3";
    ColorList["cyan-3"] = "13c2c2";
    ColorList["cyan-4"] = "006d75";
    ColorList["cyan-5"] = "002329";
    ColorList["yellow-1"] = "ffffb8";
    ColorList["yellow-2"] = "fffb8f";
    ColorList["yellow-3"] = "fadb14";
    ColorList["yellow-4"] = "ad8b00";
    ColorList["yellow-5"] = "614700";
    ColorList["red-1"] = "ffebe6";
    ColorList["red-2"] = "ffa694";
    ColorList["red-3"] = "e74c3c";
    ColorList["red-4"] = "9c1d19";
    ColorList["red-5"] = "4f080a";
    ColorList["grey-1"] = "fafafa";
    ColorList["grey-2"] = "e8e8e8";
    ColorList["grey-3"] = "bfbfbf";
    ColorList["grey-4"] = "595959";
    ColorList["grey-5"] = "262626";
    ColorList["lgreen-1"] = "dae0d3";
    ColorList["lgreen-2"] = "aac791";
    ColorList["lgreen-3"] = "70ad47";
    ColorList["lgreen-4"] = "34611e";
    ColorList["lgreen-5"] = "091405";
    ColorList["primary"] = "3498db";
    ColorList["link"] = "3498db";
    ColorList["success"] = "52c41a";
    ColorList["warning"] = "ffc116";
    ColorList["error"] = "e74c3c";
    ColorList["clicked"] = "2949b4";
    ColorList["background"] = "e8e8e8";
    ColorList["level-0"] = "bfbfbf";
    ColorList["level-1"] = "3498db";
    ColorList["level-2"] = "52c41a";
    ColorList["level-3"] = "f39c11";
    ColorList["level-4"] = "fe4c61";
    ColorList["level-5"] = "9d3dcf";
    ColorList["level--1"] = "ad8b00";
    ColorList["user-color-Cheater"] = "ad8b00";
    ColorList["user-color-Gray"] = "bfbfbf";
    ColorList["user-color-Blue"] = "3498db";
    ColorList["user-color-Green"] = "52c41a";
    ColorList["user-color-Orange"] = "f39c11";
    ColorList["user-color-Red"] = "fe4c61";
    ColorList["user-color-Purple"] = "9d3dcf";
    ColorList["vip"] = "dfc289";

    // Get the configuration information of the luogu website.
    cout << "Getting luogu config... " << flush;
    GetDataToFile("https://www.luogu.com.cn/_lfe/config");
    json Config = json::parse(GetDataFromFileToString());
    cout << "Succeed" << endl
         << "Getting luogu tags... " << flush;

    // Get the tag information of the luogu website.
    GetDataToFile("https://www.luogu.com.cn/_lfe/tags");
    json Tag = json::parse(GetDataFromFileToString());
    cout << "Succeed" << endl;

    // Get the language information of the luogu website.
    for (auto i : Config["codeLanguages"])
    {
        LanguageName[i["value"].as_integer()] = i["name"].as_string();
        LanguageMarkdownName[i["value"].as_integer()] = i["hljsMode"].as_string();
    }
    LanguageName[0] = "自动识别语言";

    // Get the difficulty information of the luogu website.
    for (auto i : Config["problemDifficulty"])
        DifficultyName[i["id"].as_integer()] = make_pair(i["name"].as_string(),
                                                         i["color"].as_string());

    // Get the problem type information of the luogu website.
    for (auto i : Config["problemTypes"])
        TypeName[i["id"].as_string()] = i["name"].as_string();
    json Temp;

    // Get the tag type information of the luogu website.
    for (auto i : Tag["types"])
        Temp[i["id"].as_integer()] = i["color"].as_string();

    // Get the tag information of the luogu website.
    for (auto i : Tag["tags"])
        TagName[i["id"].as_integer()] = make_pair(i["name"].as_string(),
                                                  Temp[i["type"].as_integer()]);

    // Get the submission status information of the luogu website.
    for (auto i : Config["recordStatus"])
        RecordName[i["id"].as_integer()] = make_pair(i["name"].as_string(),
                                                     i["shortName"].as_string());
}
void TOOL::LUOGU::Login(string Username, string Password)
{
    // Check if the user is logged in.
    int HTTPResponseCode = 0;
    cout << "Checking login... " << flush;
    GetDataToFile("https://www.luogu.com.cn/auth/login",
                  "Header.tmp",
                  "Body.tmp",
                  false,
                  "",
                  NULL,
                  &HTTPResponseCode);
    if (HTTPResponseCode == 302)
    {
        cout << "Already logged in" << endl;
        return;
    }
    cout << "Not logged in" << endl;

    // Get csrf token
    string Token = GetStringBetween(GetDataFromFileToString(),
                                    "<meta name=\"csrf-token\" content=\"", "\"");
    int ErrorCounter = 0;
    while (1)
    {
        // Get login captcha
        cout << "Getting login captcha... " << flush;
        GetDataToFile("https://www.luogu.com.cn/api/verify/captcha");
        cout << "Succeed" << endl;

        // Predict captcha
        curl_slist *HeaderList = NULL;
        HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json");
        cout << "Predicting captcha... " << flush;
        GetDataToFile("https://luogu-captcha-bypass.piterator.com/predict/",
                      "Header.tmp",
                      "Body.tmp",
                      true,
                      string("data:image/jpeg;base64," + Base64Encode(GetDataFromFileToString())),
                      HeaderList);
        cout << "Succeed" << endl;

        // Create a json object to store the login request info
        string Captcha = GetDataFromFileToString();
        json LoginRequest;
        LoginRequest["username"] = Username;
        LoginRequest["password"] = Password;
        LoginRequest["captcha"] = Captcha;

        // Create a header list for the curl request
        HeaderList = NULL;
        HeaderList = curl_slist_append(HeaderList, string("X-CSRF-TOKEN: " + Token).c_str());
        HeaderList = curl_slist_append(HeaderList, string("Content-Length: " +
                                                          to_string(LoginRequest.dump().size()))
                                                       .c_str());
        HeaderList = curl_slist_append(HeaderList, "Host: www.luogu.com.cn");
        HeaderList = curl_slist_append(HeaderList, "Referer: https://www.luogu.com.cn/auth/login");
        HeaderList = curl_slist_append(HeaderList, "Origin: https://www.luogu.com.cn");
        HeaderList = curl_slist_append(HeaderList, "X-Requested-With: XMLHttpRequest");

        // Send the login request to the server
        cout << "Logging in... " << flush;
        GetDataToFile("https://www.luogu.com.cn/api/auth/userPassLogin",
                      "Header.tmp",
                      "Body.tmp",
                      true,
                      LoginRequest.dump(),
                      HeaderList);

        // Parse the response to a json object
        json LoginInfo = json::parse(GetDataFromFileToString());
        if (!LoginInfo["status"].is_null())
        {
            // If the captcha is incorrect and the error counter is less than 5, try again.
            if (LoginInfo["data"].as_string() != "验证码错误" && ErrorCounter < 5)
            {
                Failed = true;
                cout << "Failed" << endl
                     << "Error number: " << LoginInfo["status"].as_integer() << endl
                     << "Error message: " << LoginInfo["data"].as_string() << endl;
                return;
            }
            else
                cout << "Failed (Captcha check failed for " << ErrorCounter + 1 << " times)" << endl;
        }
        else
        {
            cout << "Succeed" << endl;
            break;
        }
        ErrorCounter++;
    }
}
void TOOL::LUOGU::ClockIn()
{
    // Gets the clock-in page data
    cout << "Get clock in page data... " << flush;
    GetDataToFile("https://www.luogu.com.cn/");

    // Gets the clock-in token
    string Token = GetStringBetween(GetDataFromFileToString(),
                                    "<meta name=\"csrf-token\" content=\"", "\"");
    cout << "Succeed" << endl;

    // Gets the clock-in header
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, string("X-CSRF-TOKEN: " + Token).c_str());
    HeaderList = curl_slist_append(HeaderList, "Host: www.luogu.com.cn");
    HeaderList = curl_slist_append(HeaderList, "Referer: https://www.luogu.com.cn/");
    HeaderList = curl_slist_append(HeaderList, "Origin: https://www.luogu.com.cn");
    HeaderList = curl_slist_append(HeaderList, "X-Requested-With: XMLHttpRequest");

    // Clocks in
    cout << "Clocking in... " << flush;
    GetDataToFile("https://www.luogu.com.cn/index/ajax_punch",
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  "{}",
                  HeaderList);

    // Parse the response to a json object
    json ClockInInfo = json::parse(GetDataFromFileToString());
    if (ClockInInfo["code"].as_integer() != 200)
    {
        Failed = true;
        cout << "Failed" << endl
             << "Error number: " << ClockInInfo["code"].as_integer() << endl
             << "Error message: " << ClockInInfo["message"].as_string() << endl;
        return;
    }
    cout << "Succeed" << endl;
}
void TOOL::LUOGU::GetQuestionDetail(string QuestionID)
{
    // Gets the question detail page
    cout << "Getting question detail page... " << flush;
    GetDataToFile("https://www.luogu.com.cn/problem/" + QuestionID + (QuestionID.find("?") == string::npos ? "?" : "&") + "_contentOnly=1");
    json QuestionInfo = json::parse(GetDataFromFileToString());
    if (QuestionInfo["code"].as_integer() != 200)
    {
        Failed = true;
        cout << "Failed" << endl
             << "Error number: " << QuestionInfo["code"].as_integer() << endl
             << "Error message: " << QuestionInfo["currentData"]["errorMessage"].as_string() << endl;
        return;
    }
    cout << "Succeed" << endl;

    // Save data for CPH
    MD5 MD5Encoder;
    json CPHData;
    CPHData["name"] = QuestionInfo["currentData"]["problem"]["title"].as_string();
    CPHData["group"] = "Luogu - test";
    CPHData["url"] = "https://www.luogu.com.cn/problem/" + QuestionID;
    CPHData["interactive"] = false;
    CPHData["memoryLimit"] = 0;
    for (auto i : QuestionInfo["currentData"]["problem"]["limits"]["memory"])
        CPHData["memoryLimit"] = max(CPHData["memoryLimit"].as_integer(), i.as_integer());
    CPHData["timeLimit"] = 0;
    for (auto i : QuestionInfo["currentData"]["problem"]["limits"]["time"])
        CPHData["timeLimit"] = max(CPHData["timeLimit"].as_integer(), i.as_integer());
    for (size_t i = 0; i < QuestionInfo["currentData"]["problem"]["samples"].size(); i++)
    {
        json Temp;
        Temp["id"] = i;
        Temp["input"] = FixString(QuestionInfo["currentData"]["problem"]["samples"][i]["input"].as_string());
        Temp["output"] = FixString(QuestionInfo["currentData"]["problem"]["samples"][i]["output"].as_string());
        CPHData["tests"].push_back(json(Temp));
    }
    CPHData["local"] = false;
    CPHData["srcPath"] = "/workspaces/Coding/Luogu/" + QuestionID + ".cpp";
    CPHData["testType"] = "single";
    CPHData["input"]["type"] = "stdin";
    CPHData["output"]["type"] = "stdout";
    CPHData["languages"]["java"]["mainClass"] = "Main";
    CPHData["languages"]["java"]["taskClass"] = "GCastleDefense";
    CPHData["batch"]["id"] = MD5Encoder.encode(QuestionID);
    CPHData["batch"]["size"] = 1;
    cout << string("/workspaces/Coding/Luogu/" + QuestionID + ".cpp") << endl;
    SetDataFromStringToFile(GetCPHFileName("Luogu", QuestionID), CPHData.dump());

    // Save data for markdown
    ofstream OutputFileStream(string("/workspaces/Coding/Luogu/" + QuestionID + ".md").c_str());
    OutputFileStream << "# " << QuestionID << " "
                     << QuestionInfo["currentData"]["problem"]["title"].as_string() << endl;
    if (QuestionInfo["currentData"]["problem"]["accepted"].as_bool())
        OutputFileStream << "***您已经通过此题！***" << endl
                         << endl;
    else if (QuestionInfo["currentData"]["problem"]["submitted"].as_bool())
        OutputFileStream << "***您已经提交过此题但未通过！***" << endl
                         << endl;
    if (QuestionInfo["currentData"]["problem"]["background"].as_string() != "")
        OutputFileStream << "## 题目背景" << endl
                         << endl
                         << FixString(QuestionInfo["currentData"]["problem"]["background"]) << endl
                         << endl;
    OutputFileStream << "## 题目描述" << endl
                     << endl
                     << FixString(QuestionInfo["currentData"]["problem"]["description"]) << endl
                     << endl
                     << "## 输入格式" << endl
                     << endl
                     << FixString(QuestionInfo["currentData"]["problem"]["inputFormat"]) << endl
                     << endl
                     << "## 输出格式" << endl
                     << endl
                     << FixString(QuestionInfo["currentData"]["problem"]["outputFormat"]) << endl
                     << endl
                     << "## 输入输出样例" << endl
                     << endl;
    if (QuestionInfo["currentData"]["problem"]["samples"].size() == 0)
        OutputFileStream << "无" << endl
                         << endl;
    else
    {
        int Counter = 1;
        for (auto cit : QuestionInfo["currentData"]["problem"]["samples"])
        {
            OutputFileStream << "输入 #" << Counter << endl
                             << "```" << endl
                             << FixString(cit[0].as_string()) << endl
                             << "```" << endl
                             << "输出 #" << Counter << endl
                             << "```" << endl
                             << FixString(cit[1].as_string()) << endl
                             << "```" << endl;
            Counter++;
        }
    }
    OutputFileStream << endl
                     << "## 提示" << endl
                     << endl
                     << FixString(QuestionInfo["currentData"]["problem"]["hint"]) << endl
                     << endl;
    OutputFileStream << "## 时空限制" << endl;
    OutputFileStream << "|测试点编号|时间限制|空间限制|" << endl
                     << "|:---:|:---:|:---:|" << endl;
    for (unsigned int Counter = 0; Counter < QuestionInfo["currentData"]["problem"]["limits"]["memory"].size(); Counter++)
    {
        OutputFileStream << "|$" << (Counter + 1) << "$"
                         << "|$" << (QuestionInfo["currentData"]["problem"]["limits"]["memory"][Counter].as_integer() / 1024.0) << "MB$"
                         << "|$" << (QuestionInfo["currentData"]["problem"]["limits"]["time"][Counter].as_integer() / 1000) << "s$"
                         << "|" << endl;
    }
    OutputFileStream << endl
                     << "## 最后一次提交代码" << endl
                     << endl
                     << "```" << LanguageMarkdownName[QuestionInfo["currentData"]["lastLanguage"].as_integer()] << endl
                     << FixString(QuestionInfo["currentData"]["lastCode"].as_string()) << endl
                     << "```" << endl
                     << endl
                     << "## 其他数据" << endl
                     << endl;
    string Tags = "";
    for (auto i : QuestionInfo["currentData"]["problem"]["tags"])
        Tags += string("<span style=\"display: inline-block; ") +
                "margin-right: 5px; " +
                "margin-bottom: 5px; " +
                "border-radius: 2px; " +
                "color: white; " +
                "padding: 0px 8px; " +
                "background-color: #" + ColorList[TagName[i.as_integer()].second] + "; \">" +
                TagName[i.as_integer()].first +
                "</span>";
    OutputFileStream << "|项目|值|" << endl
                     << "|:---:|:---:|" << endl
                     << "|难度|<span style=\"font-weight: bold; color: #" << ColorList[DifficultyName[QuestionInfo["currentData"]["problem"]["difficulty"].as_integer()].second] << "\">" << DifficultyName[QuestionInfo["currentData"]["problem"]["difficulty"].as_integer()].first << "</span>|" << endl
                     << "|标签|" << Tags << "|" << endl
                     << "|提交人数|$" << QuestionInfo["currentData"]["problem"]["totalSubmit"]
                     << "$|" << endl
                     << "|通过人数|$" << QuestionInfo["currentData"]["problem"]["totalAccepted"] << "$|" << endl
                     << "|通过率|$" << (QuestionInfo["currentData"]["problem"]["totalAccepted"].as_integer() * 100.0 / QuestionInfo["currentData"]["problem"]["totalSubmit"].as_integer()) << "\\%$|" << endl
                     << "|来源|`" << TypeName[QuestionInfo["currentData"]["problem"]["type"].as_string()] << "`|" << endl
                     << "|最后一次提交语言|`" << LanguageName[QuestionInfo["currentData"]["lastLanguage"].as_integer()] << "`|" << endl
                     << endl;
    OutputFileStream.close();

    // Open the file
    if (system(string("code /workspaces/Coding/Luogu/" + QuestionID + ".md").c_str()))
        cout << "Open file \"/workspaces/Coding/Luogu/" << QuestionID << ".md\" failed, please open it manually" << endl;
}
void TOOL::LUOGU::SubmitCode(string QuestionID)
{
    // Get the code
    string Code = GetDataFromFileToString(string("../../../Luogu/" + QuestionID + ".cpp"));

    // Get the token
    cout << "Getting submit page data... " << flush;
    GetDataToFile("https://www.luogu.com.cn/problem/" + QuestionID);
    string Token = GetStringBetween(GetDataFromFileToString(),
                                    "<meta name=\"csrf-token\" content=\"", "\"");
    cout << "Succeed" << endl;

    // Create the request
    json SubmitRequest;
    SubmitRequest["code"] = Code;
    SubmitRequest["enableO2"] = 1;
    SubmitRequest["lang"] = 0;

    // Create the header
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, string("X-CSRF-TOKEN: " + Token).c_str());
    HeaderList = curl_slist_append(HeaderList, string("Content-Length: " +
                                                      to_string(SubmitRequest.dump().size()))
                                                   .c_str());
    HeaderList = curl_slist_append(HeaderList, "Host: www.luogu.com.cn");
    HeaderList = curl_slist_append(HeaderList, string("Referer: https://www.luogu.com.cn/problem/" +
                                                      QuestionID)
                                                   .c_str());
    HeaderList = curl_slist_append(HeaderList, "Origin: https://www.luogu.com.cn");
    HeaderList = curl_slist_append(HeaderList, "X-Requested-With: XMLHttpRequest");

    // Submit the code
    cout << "Submitting... " << flush;
    GetDataToFile("https://www.luogu.com.cn/fe/api/problem/submit/" + QuestionID,
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  SubmitRequest.dump(),
                  HeaderList);

    // Get the result
    json SubmitInfo = json::parse(GetDataFromFileToString());
    if (!SubmitInfo["status"].is_null())
    {
        Failed = true;
        cout << "Failed" << endl
             << "Error number: " << SubmitInfo["status"].as_integer() << endl
             << "Error message: " << SubmitInfo["errorMessage"].as_string() << endl;
        return;
    }
    cout << "Succeed" << endl;

    // Get the record ID
    int RecordID = SubmitInfo["rid"].as_integer();

    // Get the record info and wait for the result
    json RecordInfo;
    cout << "Judging... " << flush;
    while (1)
    {
        GetDataToFile("https://www.luogu.com.cn/record/" + to_string(RecordID) + (QuestionID.find("?") == string::npos ? "?" : "&") + "_contentOnly=1");
        RecordInfo = json::parse(GetDataFromFileToString());
        if (RecordInfo["currentData"]["record"]["status"].is_number() &&
            RecordInfo["currentData"]["record"]["status"].as_integer() >= 2)
            break;
        usleep(500000);
    }
    cout << "Succeed" << endl;

    // Check whether there is a compile error
    if (!RecordInfo["currentData"]["record"]["detail"]["compileResult"]["success"].as_bool())
        cout << "Compile error: " << endl
             << RecordInfo["currentData"]["record"]["detail"]["compileResult"]["message"].as_string() << endl;
    else
    {
        // Check whether the code is accepted
        if (RecordInfo["currentData"]["record"]["score"].as_integer() == 100)
        {
            // Delete the temporary files
            remove((CurrentDir + GetCPHFileName("Luogu", QuestionID)).c_str());
            remove(string("/workspaces/Coding/Luogu/" + QuestionID + ".md").c_str());
            remove(string("/workspaces/Coding/Luogu/" + QuestionID).c_str());
            cout << "Congratulations! You have passed this question!" << endl;
        }
        else
        {
            // Get the result
            for (auto jit : RecordInfo["currentData"]
                                      ["record"]
                                      ["detail"]
                                      ["judgeResult"]
                                      ["subtasks"])
            {
                cout << "#" << jit["id"].as_string() << endl;
                for (auto jit2 : RecordInfo["currentData"]
                                           ["record"]
                                           ["detail"]
                                           ["judgeResult"]
                                           ["subtasks"]
                                           [atoi(jit["id"].as_string().c_str())]
                                           ["testCases"])
                    cout
                        << "    #" << jit2["id"].as_integer() << " "
                        << jit2["score"].as_integer() << "pts "
                        << RecordName[jit2["status"].as_integer()].second << " "
                        << jit2["time"].as_integer() << "ms "
                        << jit2["memory"].as_integer() << "KB" << endl;
            }
            cout << RecordInfo["currentData"]["record"]["score"].as_integer() << "pts" << endl;
        }
    }
}
void TOOL::LUOGU::GetAnswerOrTips(string QuestionID)
{
    // Get the solution page data
    cout << "Getting solution page data... " << flush;
    GetDataToFile("https://www.luogu.com.cn/problem/solution/" + QuestionID + (QuestionID.find("?") == string::npos ? "?" : "&") + "_contentOnly=1");
    json SolutionInfo = json::parse(GetDataFromFileToString());
    cout << "Succeed" << endl;
    for (auto i : SolutionInfo["currentData"]["solutions"]["result"])
    {
        string Answer = "";

        // Iterate through all the code blocks
        vector<string> Spilt = StringSpilt(i["content"].as_string(), "```");
        for (size_t j = 0; j < Spilt.size(); j++)
        {
            if (j % 2)
            {
                // Get the code block
                string CurrentAnswer = Spilt[j];

                // If the code block is only one line, skip it
                size_t k = 0;
                while (k < CurrentAnswer.size() && CurrentAnswer[k] != '\n')
                    k++;
                if (k == CurrentAnswer.size())
                    continue;

                // Delete the first line which is the language names
                CurrentAnswer = CurrentAnswer.substr(k + 1, string::npos);

                // If the code block is a C++ code block and it's longer than the current answer, replace the current answer
                if (CurrentAnswer.find("main") != string::npos &&
                    CurrentAnswer.find("include") != string::npos &&
                    CurrentAnswer.find("return") != string::npos &&
                    CurrentAnswer.find(";") != string::npos &&
                    CurrentAnswer.size() > Answer.size())
                    Answer = CurrentAnswer;
            }
        }
        // Delete leading and trailing spaces and line breaks.
        Answer = FixString(Answer);
        if (Answer != "")
        {
            // Write the answer as a comment to the file.
            SetDataFromStringToFile("../../../Luogu/" + QuestionID + ".cpp",
                                    FixString(GetDataFromFileToString("../../../Luogu/" + QuestionID + ".cpp")) +
                                        "\n" +
                                        "\n" +
                                        "/*\n" +
                                        Answer +
                                        "\n*/" +
                                        "\n");
            break;
        }
    }
}
TOOL::ETIGER::ETIGER()
{
    DifficultyName[1] = make_pair("入门难度", "#979797");
    DifficultyName[2] = make_pair("普及-", "#79d479");
    DifficultyName[3] = make_pair("普及/提高-", "#4191ff");
    DifficultyName[4] = make_pair("普及+/提高", "yellowgreen");
    DifficultyName[5] = make_pair("提高+/省选-", "plum");
    DifficultyName[6] = make_pair("省选+/NOI", "goldenrod");
    DifficultyName[7] = make_pair("NOI+/CTSC/IOI", "orange");
    DifficultyName[8] = make_pair("传说", "red");
}
void TOOL::ETIGER::Login(string Username, string Password)
{
    // Create login request
    json LoginRequest;
    LoginRequest["name"] = Username;
    LoginRequest["password"] = Password;

    // Add headers
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json;charset=utf-8");
    HeaderList = curl_slist_append(HeaderList, "lang: zh");
    HeaderList = curl_slist_append(HeaderList, "Host: www.etiger.vip");

    // Send login request
    cout << "Logging in... " << flush;
    GetDataToFile("https://www.etiger.vip/thrall-web/user/login",
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  LoginRequest.dump(),
                  HeaderList);

    // Parse login response
    json LoginInfo = json::parse(GetDataFromFileToString());

    // Check login response
    if (LoginInfo["code"] != 200)
    {
        Failed = true;
        cout << "Failed" << endl
             << "Error number: " << LoginInfo["code"].as_integer() << endl
             << "Error message: " << LoginInfo["msg"].as_string() << endl;
        return;
    }
    cout << "Succeed" << endl;

    // Save token
    Token = LoginInfo["data"]["ticket"].as_string();
}
void TOOL::ETIGER::ClockIn()
{
    // Add headers
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json;charset=utf-8");
    HeaderList = curl_slist_append(HeaderList, "lang: zh");
    HeaderList = curl_slist_append(HeaderList, "Host: www.etiger.vip");
    HeaderList = curl_slist_append(HeaderList, string("Token: " + Token).c_str());

    // Send clock in request
    cout << "Clocking in... " << flush;
    GetDataToFile("https://www.etiger.vip/thrall-web/sign/dailySign",
                  "Header.tmp",
                  "Body.tmp",
                  false,
                  "",
                  HeaderList);

    // Parse clock in response
    json ClockInInfo = json::parse(GetDataFromFileToString());
    if (ClockInInfo["code"] != 200)
    {
        Failed = true;
        cout << "Failed" << endl
             << "Error number: " << ClockInInfo["code"].as_integer() << endl
             << "Error message: " << ClockInInfo["msg"].as_string() << endl;
        return;
    }
    cout << "Succeed" << endl;
}
void TOOL::ETIGER::GetQuestionDetail(string QuestionID)
{
    // Add headers
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json;charset=utf-8");
    HeaderList = curl_slist_append(HeaderList, "lang: zh");
    HeaderList = curl_slist_append(HeaderList, "Host: www.etiger.vip");
    HeaderList = curl_slist_append(HeaderList, string("Token: " + Token).c_str());

    // Send request
    cout << "Getting question detail... " << flush;
    GetDataToFile("https://www.etiger.vip/thrall-web/question/getById?id=" + QuestionID,
                  "Header.tmp",
                  "Body.tmp",
                  false,
                  "",
                  HeaderList);

    // Parse response
    json QuestionInfo = json::parse(GetDataFromFileToString());
    if (QuestionInfo["code"] != 200)
    {
        Failed = true;
        cout << "Failed" << endl
             << "Error number: " << QuestionInfo["code"].as_integer() << endl
             << "Error message: " << QuestionInfo["msg"].as_string() << endl;
        return;
    }
    cout << "Succeed" << endl;

    // Save data for CPH
    json CPHData;
    CPHData["name"] = QuestionInfo["data"]["title"].as_string();
    CPHData["group"] = "Etiger - test";
    CPHData["url"] = "https://etiger.vip";
    CPHData["interactive"] = false;
    CPHData["memoryLimit"] = QuestionInfo["data"]["memLimit"].as_integer();
    CPHData["timeLimit"] = QuestionInfo["data"]["timeLimit"].as_integer() * 1000;
    string InputSample = QuestionInfo["data"]["inputSample"].as_string();
    string OutputSample = QuestionInfo["data"]["outputSample"].as_string();
    vector<string> InputSamples = StringSpilt(InputSample, ";");
    vector<string> OutputSamples = StringSpilt(OutputSample, ";");
    for (size_t i = 0; i < InputSamples.size(); i++)
    {
        string Input = FixString(InputSamples[i]);
        string Output = FixString(OutputSamples[i]);
        // If input or output is empty, skip this test case
        if (Input == "" || Input == "无" || Output == "" || Output == "无")
            continue;
        CPHData["tests"][i]["input"] = Input;
        CPHData["tests"][i]["output"] = Output;
        CPHData["tests"][i]["id"] = i;
    }
    CPHData["local"] = false;
    CPHData["srcPath"] = "/workspaces/Coding/Etiger/" + QuestionID + ".cpp";
    CPHData["testType"] = "single";
    CPHData["input"]["type"] = "stdin";
    CPHData["output"]["type"] = "stdout";
    CPHData["languages"]["java"]["mainClass"] = "Main";
    CPHData["languages"]["java"]["taskClass"] = "GCastleDefense";
    CPHData["batch"]["id"] = QuestionID;
    CPHData["batch"]["size"] = 1;
    SetDataFromStringToFile(GetCPHFileName("Etiger", QuestionID), CPHData.dump());

    // Sava markdown file
    ofstream OutputFileStream(string("/workspaces/Coding/Etiger/" + QuestionID + ".md"));
    OutputFileStream << "# " << QuestionID << " " << QuestionInfo["data"]["title"].as_string() << endl
                     << endl
                     << "## 题目描述" << endl
                     << endl
                     << FixString(EraseHTMLElement(QuestionInfo["data"]["content"].as_string())) << endl
                     << endl
                     << "## 输入格式" << endl
                     << endl
                     << FixString(QuestionInfo["data"]["inputFormat"].as_string()) << endl
                     << endl
                     << "## 输出格式" << endl
                     << endl
                     << FixString(QuestionInfo["data"]["outputFormat"].as_string()) << endl
                     << endl;
    if (!QuestionInfo["data"]["ioName"].is_null())
        OutputFileStream << "## 输入输出文件" << endl
                         << endl
                         << "`" << FixString(QuestionInfo["data"]["ioName"].as_string()) << "`" << endl
                         << endl;
    OutputFileStream << "## 输入输出样例" << endl
                     << endl;
    int Counter = 1;
    while (InputSample.find(";") != string::npos && OutputSample.find(";") != string::npos)
    {
        if (FixString(InputSample.substr(0, InputSample.find(";"))) != "无")
        {
            OutputFileStream << "输入 #" << Counter << endl
                             << "```" << endl
                             << FixString(InputSample.substr(0, InputSample.find(";"))) << endl
                             << "```" << endl
                             << "输出 #" << Counter << endl
                             << "```" << endl
                             << FixString(OutputSample.substr(0, OutputSample.find(";"))) << endl
                             << "```" << endl;
        }
        InputSample.erase(0, InputSample.find(";") + 1);
        OutputSample.erase(0, OutputSample.find(";") + 1);
        Counter++;
    }
    OutputFileStream << endl;
    if (EraseHTMLElement(QuestionInfo["data"]["description"].as_string()) != "")
    {
        OutputFileStream << "## 说明" << endl
                         << endl
                         << FixString(EraseHTMLElement(QuestionInfo["data"]["description"].as_string())) << endl
                         << endl;
    }
    OutputFileStream << "## 其他数据" << endl
                     << endl
                     << "|项目|值|" << endl
                     << "|:---:|:---:|" << endl
                     << "|难度|<span style=\""
                     << "text-align: center; "
                     << "display: inline-block; "
                     << "border-radius: 3px; "
                     << "color: white; "
                     << "width: 120px; "
                     << "height: 24px; "
                     << "background-color: " << DifficultyName[QuestionInfo["data"]["level"].as_integer()].second
                     << "\">"
                     << DifficultyName[QuestionInfo["data"]["level"].as_integer()].first << "</span>|" << endl
                     << "|提交次数|$" << QuestionInfo["data"]["submitInfo"]["totalCount"] << "$|" << endl
                     << "|提交人数|$" << QuestionInfo["data"]["submitInfo"]["submitPersonCount"] << "$|" << endl
                     << "|通过人数|$" << QuestionInfo["data"]["submitInfo"]["passCount"] << "$|" << endl
                     << "|通过率|$" << QuestionInfo["data"]["submitInfo"]["passRate"] << "\\%$|" << endl
                     << endl;
    OutputFileStream.close();

    // Open file
    if (system(string("code /workspaces/Coding/Etiger/" + QuestionID + ".md").c_str()))
        cout << "Open file \"/workspaces/Coding/Etiger/" << QuestionID << ".md\" failed, please open it manually" << endl;
}
void TOOL::ETIGER::SubmitCode(string QuestionID)
{
    // Get code
    string Code = GetDataFromFileToString(string("../../../Etiger/" + QuestionID + ".cpp"));

    // Uncomment freopen and save
    Code = StringReplaceAll(Code, "// freopen", "freopen");
    SetDataFromStringToFile("../../../Etiger/" + QuestionID + ".cpp", Code);

    // Create submit request
    json SubmitRequest;
    SubmitRequest["comment"] = "";
    SubmitRequest["lang"] = "CPP";
    SubmitRequest["submitType"] = 0;
    SubmitRequest["questionId"] = QuestionID;
    SubmitRequest["src"] = Code;

    // Create header
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json;charset=utf-8");
    HeaderList = curl_slist_append(HeaderList, "lang: zh");
    HeaderList = curl_slist_append(HeaderList, "Host: www.etiger.vip");
    HeaderList = curl_slist_append(HeaderList, string("Token: " + Token).c_str());

    // Submit
    cout << "Submitting... " << flush;
    GetDataToFile("https://www.etiger.vip/thrall-web/saveSubmit",
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  SubmitRequest.dump(),
                  HeaderList);

    // Get result
    json SubmitInfo = json::parse(GetDataFromFileToString());
    if (SubmitInfo["code"] != 200)
    {
        Failed = true;
        cout << "Failed" << endl
             << "Error number: " << SubmitInfo["code"].as_integer() << endl
             << "Error message: " << SubmitInfo["msg"].as_string() << endl;
        return;
    }
    cout << "Succeed" << endl;

    // Check whether the code is accepted
    if (SubmitInfo["data"]["grade"].as_integer() == 100)
    {
        // Remove temporary files
        remove((CurrentDir + GetCPHFileName("Etiger", QuestionID)).c_str());
        remove(string("/workspaces/Coding/Etiger/" + QuestionID + ".md").c_str());
        remove(string("/workspaces/Coding/Etiger/" + QuestionID).c_str());
        cout << "Congratulations! You have passed this question!" << endl;
    }
    else
    {
        // Output result
        int Counter = 1;
        for (auto i : SubmitInfo["data"]["result"])
        {
            cout << "#" << Counter << " "
                 << i["type"].as_string() << " "
                 << i["timeUsed"] << "ms "
                 << i["memUsed"] << "B" << endl;
            Counter++;
            if (i["input"].as_string() != "")
            {
                cout << "    Input: " << i["input"].as_string() << endl
                     << "    Standard output: " << i["output"].as_string() << endl
                     << "    My output: " << i["myOutput"].as_string() << endl;
                json CPHData = json::parse(GetDataFromFileToString(GetCPHFileName("Etiger", QuestionID)));
                CPHData["tests"].push_back({{"input", i["input"].as_string()},
                                            {"output", i["output"].as_string()},
                                            {"id", Counter}});
                SetDataFromStringToFile(GetCPHFileName("Etiger", QuestionID), CPHData.dump());
            }
        }
        cout << SubmitInfo["data"]["grade"] << "pts" << endl;
    }
}
void TOOL::ETIGER::GetAnswerOrTips(string QuestionID)
{
    // Create header
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json;charset=utf-8");
    HeaderList = curl_slist_append(HeaderList, "lang: zh");
    HeaderList = curl_slist_append(HeaderList, "Host: www.etiger.vip");
    HeaderList = curl_slist_append(HeaderList, string("Token: " + Token).c_str());

    // Get tips
    cout << "Getting comments page data... " << flush;
    GetDataToFile("https://www.etiger.vip/thrall-web/comment/getByQuestionForPage?questionId=" + QuestionID + "&cpage=1&pagesize=10",
                  "Header.tmp",
                  "Body.tmp",
                  false,
                  "",
                  HeaderList);

    // Get result
    json CommentsData = json::parse(GetDataFromFileToString());
    if (CommentsData["code"] != 200)
    {
        Failed = true;
        cout << "Failed" << endl
             << "Error number: " << CommentsData["code"].as_integer() << endl
             << "Error message: " << CommentsData["msg"].as_string() << endl;
        return;
    }
    cout << "Success" << endl;

    // Save comments to a string joined by newline
    string Comments = "";
    for (auto i : CommentsData["data"]["records"])
        Comments += FixString(i["content"].as_string()) + "\n";

    // Add comments to the code
    SetDataFromStringToFile("../../../Etiger/" + QuestionID + ".cpp",
                            FixString(GetDataFromFileToString("../../../Etiger/" + QuestionID + ".cpp")) +
                                "\n" +
                                "\n" +
                                "/*\n" +
                                Comments +
                                "*/" +
                                "\n");
}
string TOOL::CODEFORCES::GetCRSF()
{
    // Get csrf token
    return GetStringBetween(GetDataFromFileToString(),
                            "<input type='hidden' name='csrf_token' value='", "'/>");
}
string TOOL::CODEFORCES::OutputPre(TiXmlElement *Input)
{
    // Output pre tag
    string Output;
    Output += "```\n";
    for (TiXmlNode *i = Input->FirstChild(); i != NULL; i = i->NextSibling())
        // If the node is text, output it
        if (i->Type() == TiXmlNode::TINYXML_TEXT)
            Output += i->ToText()->Value();

        // If the node is br, output a newline
        else if (i->Type() == TiXmlNode::TINYXML_ELEMENT)
            if (string(i->Value()) == "br")
                Output += "\n";

    // If the last character is not a newline, add a newline
    if (Output[Output.size() - 1] != '\n')
        Output += "\n";
    Output += "```";
    return Output;
}
string TOOL::CODEFORCES::Output(TiXmlElement *Input, bool InLatex)
{
    string OutputValue = "";
    string Value = Input->Value();

    // If the node is pre, call OutputPre to output it
    if (Value == "pre")
    {
        OutputValue += "\n" + OutputPre(Input) + "\n";
        return OutputValue;
    }

    // If the node is img, output it as a markdown image
    else if (Value == "img")
    {
        OutputValue += " ![](" + string(Input->Attribute("src")) + ") ";
        return OutputValue;
    }

    // If the node is a ul output as a newline
    else if (Value == "ul")
        OutputValue += "\n";

    // If the node is a li output as a list
    else if (Value == "li")
        OutputValue += "- ";

    // If the node is a span, output it as it should be
    else if (Value == "span" && Input->Attribute("class") != NULL)
    {
        string Class = Input->Attribute("class");

        // If it is bold
        if (Class == "tex-font-style-bf")
            OutputValue += " **";

        // If it is italic
        else if (Class == "tex-font-style-tt")
            OutputValue += " `";

        // Else it is a latex expressions
        else
            OutputValue += " $";
        InLatex = true;
    }

    // If the node is a sup, output it as a superscript
    else if (Value == "sup")
        OutputValue += "^{";

    // If the node is a sub, output it as a subscript
    else if (Value == "sub")
        OutputValue += "_{";

    // Output the node's children
    for (TiXmlNode *i = Input->FirstChild(); i != NULL; i = i->NextSibling())
        // If the node is text, output it
        if (i->Type() == TiXmlNode::TINYXML_TEXT)
            OutputValue += i->ToText()->Value();

        // If the node is element, call Output to output it
        else if (i->Type() == TiXmlNode::TINYXML_ELEMENT)
            OutputValue += Output(i->ToElement(), InLatex);

    // End all expressions as above
    if (Value == "span" && Input->Attribute("class") != NULL)
    {
        string Class = Input->Attribute("class");
        if (Class == "tex-font-style-bf")
            OutputValue += "** ";
        else if (Class == "tex-font-style-tt")
            OutputValue += "` ";
        else
            OutputValue += "$ ";
    }
    else if (Value == "li")
        OutputValue += "\n";
    else if (Value == "ul")
        OutputValue += "\n";
    else if (Value == "sup")
        OutputValue += "}";
    else if (Value == "sub")
        OutputValue += "}";
    else if (Value == "p")
        OutputValue += "\n";
    return OutputValue;
}
string TOOL::CODEFORCES::ToNormalName(string Input)
{
    // Convert the Codeforces name to normal judge name
    if (Input == "OK")
        return "AC";
    if (Input == "FAILED")
        return "FAIL";
    if (Input == "PARTIAL")
        return "PRT";
    if (Input == "COMPILATION_ERROR")
        return "CE";
    if (Input == "RUNTIME_ERROR")
        return "RE";
    if (Input == "WRONG_ANSWER")
        return "WA";
    if (Input == "PRESENTATION_ERROR")
        return "PE";
    if (Input == "TIME_LIMIT_EXCEEDED")
        return "TLE";
    if (Input == "MEMORY_LIMIT_EXCEEDED")
        return "MLE";
    if (Input == "IDLENESS_LIMIT_EXCEEDED")
        return "ILE";
    if (Input == "SECURITY_VIOLATED")
        return "SV";
    if (Input == "CRASHED")
        return "CRS";
    if (Input == "INPUT_PREPARATION_CRASHED")
        return "IPC";
    if (Input == "CHALLENGED")
        return "CHL";
    if (Input == "SKIPPED")
        return "SKP";
    if (Input == "TESTING")
        return "TST";
    if (Input == "REJECTED")
        return "REJ";
    return Input;
}
string TOOL::CODEFORCES::TidyHTMLDocument(string Input)
{
    // Use Tidy to tidy the HTML document to XHTML
    TidyBuffer OutputBuffer = {0};
    TidyBuffer ErrorBuffer = {0};
    TidyDoc TidyDocument = tidyCreate();
    tidyOptSetBool(TidyDocument, TidyXhtmlOut, yes);
    tidySetErrorBuffer(TidyDocument, &ErrorBuffer);
    tidyParseString(TidyDocument, Input.c_str());
    tidyCleanAndRepair(TidyDocument);
    tidyRunDiagnostics(TidyDocument);
    tidyOptSetBool(TidyDocument, TidyForceOutput, yes);
    tidySaveBuffer(TidyDocument, &OutputBuffer);
    string Output = string(reinterpret_cast<const char *>(OutputBuffer.bp));
    tidyBufFree(&OutputBuffer);
    tidyBufFree(&ErrorBuffer);
    tidyRelease(TidyDocument);
    return Output;
}
void TOOL::CODEFORCES::Login(string Username, string Password)
{
    // Check if the user is already logged in
    int HTTPResponseCode = 0;
    cout << "Checking login... " << flush;
    GetDataToFile("https://codeforces.com/enter",
                  "Header.tmp",
                  "Body.tmp",
                  false,
                  "",
                  NULL,
                  &HTTPResponseCode);
    if (HTTPResponseCode == 302)
    {
        cout << "Already logged in" << endl;
        return;
    }
    cout << "Not logged in" << endl;
    HTTPResponseCode = 0;

    // Login
    cout << "Logging in... " << flush;
    GetDataToFile("https://codeforces.com/enter",
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  string("csrf_token=" + GetCRSF() +
                         "&action=enter" +
                         "&ftaa=" + ftaa +
                         "&bfaa=" + bfaa +
                         "&handleOrEmail=" + URLEncode(Username.c_str()) +
                         "&password=" + URLEncode(Password.c_str()) +
                         "&_tta=176" +
                         "&remember=on")
                      .c_str(),
                  NULL,
                  &HTTPResponseCode,
                  FORM);
    if (HTTPResponseCode == 200)
    {
        // Login failed
        string LoginPageData = GetDataFromFileToString();

        // If the login failed because of the check of javascript
        if (LoginPageData.find("toNumbers"))
        {
            // Get the javascript code and write it to a file
            SetDataFromStringToFile("Run.js",
                                    // Get the javascript library
                                    GetDataFromFileToString("aes.min.js") +
                                        "\n\n\n\nfunction " +
                                        // Remove set cookie code and replace it with a variable
                                        StringReplaceAll(
                                            GetStringBetween(LoginPageData,
                                                             "<script>function ",
                                                             "document.location.href="),
                                            "document.cookie", "var Output") +
                                        "\n\nconsole.log(Output);\n");

            // Run the javascript code
            system(string("nodejs " + CurrentDir + "Run.js >> " + CurrentDir + "Output.tmp").c_str());

            // Delete the javascript code
            unlink(string(CurrentDir + "Run.js").c_str());

            // Get the output of the javascript code and try to login again
            GetDataToFile(GetStringBetween(LoginPageData, "document.location.href=\"", "\";</script>"),
                          "Header.tmp",
                          "Body.tmp",
                          true,
                          string("csrf_token=" + GetCRSF() +
                                 "&action=enter" +
                                 "&ftaa=" + ftaa +
                                 "&bfaa=" + bfaa +
                                 "&handleOrEmail=" + URLEncode(Username.c_str()) +
                                 "&password=" + URLEncode(Password.c_str()) +
                                 "&_tta=176" +
                                 "&remember=on")
                              .c_str(),
                          NULL,
                          &HTTPResponseCode,
                          FORM,
                          // Set the cookie
                          "#HttpOnly_codeforces.com\tFALSE\t/\tFALSE\t0\tRCPC\t" + GetStringBetween(GetDataFromFileToString("Output.tmp"), "RCPC=", ";"));

            // Remove the javascript output file
            unlink(string(CurrentDir + "Output.tmp").c_str());
            if (HTTPResponseCode == 200)
            {
                Failed = true;
                cout << "Failed" << endl;
                return;
            }
        }
        else
        {
            Failed = true;
            cout << "Failed" << endl;
            return;
        }
    }
    cout << "Succeed" << endl;
}
void TOOL::CODEFORCES::GetQuestionDetail(string QuestionID)
{
    // Get the question detail
    cout << "Getting question detail... " << flush;
    GetDataToFile("https://codeforces.com/problemset/problem/" +
                  QuestionID.substr(0, QuestionID.size() - 1) + "/" +
                  QuestionID.substr(QuestionID.size() - 1));
    cout << "Succeed" << endl;

    // Format the question detail and prase it
    TiXmlDocument QuestionXmlDocument;
    QuestionXmlDocument.Parse(TidyHTMLDocument(GetDataFromFileToString()).c_str());
    if (QuestionXmlDocument.Error())
    {
        cout << "Formatting problem data error, error message: " << QuestionXmlDocument.ErrorDesc() << endl;
        return;
    }
    ofstream OutputFileStream(string("/workspaces/Coding/Codeforces/" + QuestionID + ".md").c_str());

    // Find the question detail
    TiXmlHandle QuestionXmlHandle = TiXmlHandle(&QuestionXmlDocument)
                                        .FirstChild("html")
                                        .FirstChild("body")
                                        .Child("div", 3)
                                        .Child("div", 4)
                                        .Child("div", 1)
                                        .Child("div", 2)
                                        .Child("div", 1)
                                        .Child("div", 0);

    // Output the question detail
    OutputFileStream << "# " << QuestionXmlHandle.Child(0).Child(0).ToElement()->GetText()
                     << endl
                     << endl
                     << "## Description" << endl
                     << Output(QuestionXmlHandle.Child(1).ToElement()) << endl
                     << endl;
    for (TiXmlNode *i = QuestionXmlHandle.Child(2).Node(); i != NULL; i = i->NextSibling())
    {
        TiXmlNode *j = i->ToElement()->FirstChild();
        OutputFileStream << "## " << j->ToElement()->FirstChild()->ToText()->Value() << endl
                         << endl;
        j = j->NextSibling();
        for (; j != NULL; j = j->NextSibling())
            OutputFileStream << Output(j->ToElement()) << endl;
        OutputFileStream << endl;
    }
    OutputFileStream << "## More details" << endl
                     << endl
                     << "|Name|Value|" << endl
                     << "|:---:|:---:|" << endl
                     << "|Time Limit|" << QuestionXmlHandle.Child(0).Child(1).Child(1).ToText()->Value() << "|" << endl
                     << "|Memory Limit|" << QuestionXmlHandle.Child(0).Child(2).Child(1).ToText()->Value() << "|" << endl
                     << "|Input|" << QuestionXmlHandle.Child(0).Child(3).Child(1).ToText()->Value() << "|" << endl
                     << "|Output|" << QuestionXmlHandle.Child(0).Child(4).Child(1).ToText()->Value() << "|" << endl
                     << endl;
    OutputFileStream.close();

    // Open the question detail file
    if (system(string("code /workspaces/Coding/Codeforces/" + QuestionID + ".md").c_str()))
        cout << "Open file \"/workspaces/Coding/Codeforces/" << QuestionID << ".md\" failed, please open it manually" << endl;
}
void TOOL::CODEFORCES::SubmitCode(string QuestionID)
{
    // Get the code
    string Code = GetDataFromFileToString("../../../Codeforces/" + QuestionID + ".cpp");

    // Add a number to the code to avoid submitting the same code
    Code += "\n\n// " + to_string(time(NULL));

    // Get submit page data
    cout << "Getting submit page data... " << flush;
    GetDataToFile("https://codeforces.com/problemset/submit");
    cout << "Succeed" << endl;

    // Submit the code
    int HTTPResponseCode = 0;
    cout << "Submitting... " << flush;
    GetDataToFile("https://codeforces.com/problemset/submit?csrf_token=" + GetCRSF(),
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  string(
                      "csrf_token=" + GetCRSF() +
                      "&ftaa=" + ftaa +
                      "&bfaa=" + bfaa +
                      "&action=submitSolutionFormSubmitted" +
                      "&contestId=" + QuestionID.substr(0, QuestionID.size() - 1) +
                      "&submittedProblemIndex=" + QuestionID.substr(QuestionID.size() - 1) +
                      "&programTypeId=50" +
                      "&source=" + URLEncode(Code) +
                      "&tabSize=4&sourceFile=&_tta=153")
                      .c_str(),
                  NULL,
                  &HTTPResponseCode,
                  FORM);
    if (HTTPResponseCode == 200)
    {
        Failed = true;
        cout << "Failed" << endl;
        return;
    }
    cout << "Succeed" << endl;

    // Crate a header list
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList,
                                   "Referer: https://codeforces.com/problemset/status/page/1?my=on");

    // Get the submission list page data
    cout << "Getting submission ID... " << flush;
    GetDataToFile("https://codeforces.com/problemset/status/page/1?my=on");
    cout << "Succeed" << endl;

    // Parse the submission list
    TiXmlDocument SubmitListXmlDocument;
    SubmitListXmlDocument.Parse(TidyHTMLDocument(GetDataFromFileToString()).c_str());
    if (SubmitListXmlDocument.Error())
    {
        cout << "Formatting submission list error, error message: " << SubmitListXmlDocument.ErrorDesc() << endl;
        return;
    }

    // Get the submission ID
    string SubmitID = TiXmlHandle(&SubmitListXmlDocument)
                          .FirstChild("html")
                          .FirstChild("body")
                          .Child("div", 3)
                          .Child("div", 4)
                          .FirstChild("div")
                          .Child("div", 3)
                          .Child("div", 5)
                          .FirstChild("table")
                          .Child("tr", 1)
                          .ToElement()
                          ->Attribute("data-submission-id");
    cout << "Judging... " << flush;

    // Get the submission result
    json result;
    do
    {
        GetDataToFile("https://codeforces.com/data/submitSource",
                      "Header.tmp",
                      "Body.tmp",
                      true,
                      string("submissionId=" + SubmitID +
                             "&csrf_token=" + GetCRSF()),
                      HeaderList,
                      NULL,
                      FORM);
        result = json::parse(GetDataFromFileToString());
    } while (!result["waiting"].is_null() && result["waiting"].as_string() == "true");
    cout << "Succeed" << endl;

    // Get the submission result
    int ACNumber = 0;
    int TestNumber = atoi(result["testCount"].as_string().c_str());
    for (int i = 1; i <= TestNumber; i++)
    {
        // Save the input and output file
        SetDataFromStringToFile("/workspaces/Coding/Codeforces/" + QuestionID + "_" + to_string(i) + ".in",
                                result["input#" + to_string(i)].as_string());
        SetDataFromStringToFile("/workspaces/Coding/Codeforces/" + QuestionID + "_" + to_string(i) + ".out",
                                result["answer#" + to_string(i)].as_string());

        // Print the result
        cout << "#" << i << " "
             << ToNormalName(result["verdict#" + to_string(i)].as_string()) << " "
             << result["timeConsumed#" + to_string(i)].as_string() << "ms "
             << result["memoryConsumed#" + to_string(i)].as_string() << "B     "
             << result["checkerStdoutAndStderr#" + to_string(i)].as_string();
        if (result["rejected#" + to_string(i)].as_string() == "false")
            ACNumber++;
    }
    cout << int(ACNumber * 1.0 / TestNumber) << "pts" << endl;
}
void TOOL::UVA::Login(string Username, string Password)
{
    // Check if already logged in
    cout << "Checking login... " << flush;
    GetDataToFile("https://onlinejudge.org/index.php?option=com_comprofiler");
    if (GetDataFromFileToString().find("You need to login.") == string::npos)
    {
        cout << "Already logged in" << endl;
        return;
    }
    cout << "Not logged in" << endl;

    // Get the login page data
    GetDataToFile("https://onlinejudge.org/index.php");
    string LoginPageHTML = GetDataFromFileToString();
    int HTTPResponseCode = 0;
    string cbsecuritym3 = GetStringBetween(LoginPageHTML,
                                           "<input type=\"hidden\" name=\"cbsecuritym3\" value=\"",
                                           "\" />");

    // Login
    cout << "Logging in... " << flush;
    GetDataToFile("https://onlinejudge.org/index.php?option=com_comprofiler&task=login",
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  string("username=" + URLEncode(Username) +
                         "&passwd=" + URLEncode(Password) +
                         "&op2=login" +
                         "&lang=english" +
                         "&force_session=1" +
                         "&return=" +
                         URLEncode(
                             GetStringBetween(LoginPageHTML.c_str(),
                                              "<input type=\"hidden\" name=\"return\" value=\"",
                                              "\" />")) +
                         "&message=0" +
                         "&loginfrom=loginmodule" +
                         "&cbsecuritym3=" + cbsecuritym3 +
                         "&" +
                         GetStringBetween(LoginPageHTML.c_str(),
                                          cbsecuritym3 + "\" />\n<input type=\"hidden\" name=\"",
                                          "\" value=\"1\" />") +
                         "=1" +
                         "&remember=yes" +
                         "&Submit=Login"),
                  NULL,
                  &HTTPResponseCode,
                  FORM);
    if (HTTPResponseCode == 200)
    {
        Failed = true;
        cout << "Failed" << endl;
        return;
    }
    cout << "Succeed" << endl;
}
void TOOL::UVA::GetQuestionDetail(string QuestionID)
{
    // Get the question detail
    string FixedQuestionID = QuestionID;
    while (FixedQuestionID[0] == '0')
        FixedQuestionID.erase(0, 1);

    // Save the pdf file
    cout << "Getting question detail... " << flush;
    GetDataToFile("https://onlinejudge.org/external/" +
                      FixedQuestionID.substr(0, FixedQuestionID.size() - 2) +
                      "/p" + FixedQuestionID + ".pdf",
                  "Header.tmp",
                  "../../../UVa/" + QuestionID + ".pdf",
                  false,
                  "",
                  NULL,
                  NULL,
                  "application/json",
                  "",
                  true);
    cout << "Succeed" << endl;

    // Open the pdf file
    if (system(string("code /workspaces/Coding/UVa/" + QuestionID + ".pdf").c_str()))
        cout << "Open file \"/workspaces/Coding/UVa/" << QuestionID << ".md\" failed, please open it manually" << endl;
}
void TOOL::UVA::SubmitCode(string QuestionID)
{
    // Get the submit page data
    cout << "Getting submit page data... " << flush;
    GetDataToFile("https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=25&page=submit_problem");
    cout << "Succeed" << endl;
    string FixedQuestionID = QuestionID;
    while (FixedQuestionID[0] == '0')
        FixedQuestionID.erase(0, 1);

    // Get the code
    string Code = GetDataFromFileToString("../../../UVa/" + QuestionID + ".cpp");

    // Create the header list
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8");
    HeaderList = curl_slist_append(HeaderList, "Accept-Encoding: gzip, deflate, br");
    HeaderList = curl_slist_append(HeaderList, "Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2");
    HeaderList = curl_slist_append(HeaderList, "Origin: https://onlinejudge.org");
    HeaderList = curl_slist_append(HeaderList, "Sec-Fetch-Dest: document");
    HeaderList = curl_slist_append(HeaderList, "Sec-Fetch-Mode: navigate");
    HeaderList = curl_slist_append(HeaderList, "Sec-Fetch-Site: same-origin");
    HeaderList = curl_slist_append(HeaderList, "Sec-Fetch-User: ?1");
    HeaderList = curl_slist_append(HeaderList, "Upgrade-Insecure-Requests: 1");
    HeaderList = curl_slist_append(HeaderList, "Connection: keep-alive");
    HeaderList = curl_slist_append(HeaderList, "Host: onlinejudge.org");
    HeaderList = curl_slist_append(HeaderList, "Referer: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=25&page=submit_problem");
    int HTTPResponseCode = 0;

    // Create the multipart data
    string tmp = "--" + MULTIPART_BOUNDARY + "\n" +
                 "Content-Disposition: form-data; name=\"problemid\"\n" +
                 "\n" +
                 "\n" +
                 "--" + MULTIPART_BOUNDARY + "\n" +
                 "Content-Disposition: form-data; name=\"category\"\n" +
                 "\n" +
                 "\n" +
                 "--" + MULTIPART_BOUNDARY + "\n" +
                 "Content-Disposition: form-data; name=\"localid\"\n" +
                 "\n" +
                 FixedQuestionID + "\n" +
                 "--" + MULTIPART_BOUNDARY + "\n" +
                 "Content-Disposition: form-data; name=\"language\"\n" +
                 "\n" +
                 "5\n" +
                 "--" + MULTIPART_BOUNDARY + "\n" +
                 "Content-Disposition: form-data; name=\"code\"\n" +
                 "\n" +
                 Code + "\n" +
                 "\n" +
                 "--" + MULTIPART_BOUNDARY + "\n" + "Content-Disposition: form-data; name=\"codeupl\"; filename=\"\"\n" +
                 "Content-Type: application/octet-stream\n" +
                 "\n" +
                 "\n" +
                 "--" + MULTIPART_BOUNDARY + "--\n";

    // Submit the code
    cout << "Submitting... " << flush;
    GetDataToFile("https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=25&page=save_submission",
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  tmp,
                  HeaderList,
                  &HTTPResponseCode,
                  MULTIPART);
    if (HTTPResponseCode == 200)
    {
        Failed = true;
        cout << "Failed" << endl;
        return;
    }

    // Get the submission id
    string SubmissionID = FindLocation();
    SubmissionID = SubmissionID.substr(SubmissionID.find_last_of('+') + 1);
    if (atoi(SubmissionID.c_str()) == 0)
    {
        Failed = true;
        cout << "Failed" << endl;
        return;
    }
    cout << "Succeed" << endl;

    // Get the submission result
    cout << "Judging... " << flush;
    while (1)
    {
        // Get the submission list
        GetDataToFile("https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=9");
        string Data = GetDataFromFileToString();
        Data = StringReplaceAll(Data, "\t", "");
        Data = StringReplaceAll(Data, "\r", "");
        Data = StringReplaceAll(Data, "\n", "");
        Data = StringReplaceAll(Data, "< ", "<");
        Data = StringReplaceAll(Data, " <", "<");
        Data = StringReplaceAll(Data, "> ", ">");
        Data = StringReplaceAll(Data, " >", ">");
        SetDataFromStringToFile("Data.tmp", Data);

        // Find the submission
        smatch Match;
        if (regex_search(Data.cbegin(), Data.cend(), Match, regex("<tr class=\"sectiontableentry[0-9]\"><td>" + SubmissionID + "</td><td align=\"right\"><a href=\"index\\.php\\?option=com_onlinejudge&amp;Itemid=8&amp;page=show_problem&amp;problem=[0-9]*\">[0-9]*</a></td><td><a href=\"index\\.php\\?option=com_onlinejudge&amp;Itemid=8&amp;page=show_problem&amp;problem=[0-9]*\">[^<]*</a></td><td>([^<]*)</td><td>C\\+\\+11</td><td>([0-9\\.]*)</td><!--<td></td>--><td>[^<]*</td></tr>")))
        {
            // Get the result
            string Verdict = Match[1];
            if (Verdict == "In judge queue")
                usleep(500000);
            else
            {
                cout << "Succeed" << endl
                     << "Verdict: " << Verdict << endl
                     << "Run Time: " << Match[2] << "s" << endl;
                break;
            }
        }
        else
            cout << "无法找到提交记录对应的提交信息";
    }
}
TOOL::TOOL(string FileName, string Operation)
{
    // Choose the tool
    if (FileName.find("Luogu") != string::npos)
    {
        LUOGU Luogu;
        Luogu.Login(GetDataFromFileToString("../../../Keys/LuoguUsername"), GetDataFromFileToString("../../../Keys/LuoguPassword"));
        if (Failed)
            return;
        if (Operation == "ClockIn")
            Luogu.ClockIn();
        else if (Operation == "GetQuestionDetail")
            Luogu.GetQuestionDetail(GetStringBetween(FileName, "Luogu/", ".cpp"));
        else if (Operation == "SubmitCode")
            Luogu.SubmitCode(GetStringBetween(FileName, "Luogu/", ".cpp"));
        else if (Operation == "GetAnswerOrTips")
            Luogu.GetAnswerOrTips(GetStringBetween(FileName, "Luogu/", ".cpp"));
        else
            cout << "传参错误" << endl;
        if (Failed)
            return;
    }
    else if (FileName.find("Etiger") != string::npos)
    {
        ETIGER Etiger;
        Etiger.Login(GetDataFromFileToString("../../../Keys/EtigerUsername"), GetDataFromFileToString("../../../Keys/EtigerPassword"));
        if (Failed)
            return;
        if (Operation == "ClockIn")
            Etiger.ClockIn();
        else if (Operation == "GetQuestionDetail")
            Etiger.GetQuestionDetail(GetStringBetween(FileName, "Etiger/", ".cpp"));
        else if (Operation == "SubmitCode")
            Etiger.SubmitCode(GetStringBetween(FileName, "Etiger/", ".cpp"));
        else if (Operation == "GetAnswerOrTips")
            Etiger.GetAnswerOrTips(GetStringBetween(FileName, "Etiger/", ".cpp"));
        else
            cout << "传参错误" << endl;
        if (Failed)
            return;
    }
    else if (FileName.find("UVa") != string::npos)
    {
        UVA UVa;
        UVa.Login(GetDataFromFileToString("../../../Keys/UVaUsername"), GetDataFromFileToString("../../../Keys/UVaPassword"));
        if (Failed)
            return;
        if (Operation == "GetQuestionDetail")
            UVa.GetQuestionDetail(GetStringBetween(FileName, "UVa/", ".cpp"));
        else if (Operation == "SubmitCode")
            UVa.SubmitCode(GetStringBetween(FileName, "UVa/", ".cpp"));
        else
            cout << "传参错误" << endl;
        if (Failed)
            return;
    }
    else if (FileName.find("Codeforces") != string::npos)
    {
        CODEFORCES Codeforces;
        Codeforces.Login(GetDataFromFileToString("../../../Keys/CodeforcesUsername"), GetDataFromFileToString("../../../Keys/CodeforcesPassword"));
        if (Failed)
            return;
        if (Operation == "GetQuestionDetail")
            Codeforces.GetQuestionDetail(GetStringBetween(GetStringBetween(FileName, "Codeforces/", ".cpp"), "", "/"));
        else if (Operation == "SubmitCode")
            Codeforces.SubmitCode(GetStringBetween(GetStringBetween(FileName, "Codeforces/", ".cpp"), "", "/"));
        else
            cout << "传参错误" << endl;
        if (Failed)
            return;
    }
    else
        cout << "传参错误" << endl;
}
TOOL::TOOL(string ServerName, string Username, string Password)
{
    // Fix leading and trailing spaces and line breaks in the username and password
    Username = FixString(Username);
    Password = FixString(Password);
    if (ServerName == "Luogu")
    {
        LUOGU Luogu;
        Luogu.Login(Username, Password);
        Luogu.ClockIn();
    }
    else if (ServerName == "Etiger")
    {
        ETIGER Etiger;
        Etiger.Login(Username, Password);
        Etiger.ClockIn();
    }
    else
        cout << "传参错误" << endl;
}
TOOL::~TOOL()
{
    // Clean up
    Clean();
}
int main(int argc, char **argv)
{
    GetCurrentDir();
    // If the Cookies.tmp file does not exist, create it
    if (!IfFileExist("../../../Keys/Cookies.tmp"))
    {
        system(string("mkdir " + CurrentDir + "../../../Keys").c_str());
        system(string("touch " + CurrentDir + "../../../Keys/Cookies.tmp").c_str());
    }
    try
    {
        // If the argument count is 3, the tool is used to GetQuestionDetail/SubmitCode/GetAnswerOrTips
        if (argc == 3)
            TOOL Tool(argv[1], argv[2]);

        // If the argument count is 4, the tool is used to login and clock in
        else if (argc == 4)
            TOOL Tool(argv[1], argv[2], argv[3]);
        else
            cout << "传参错误" << endl;
    }
    // Catch json parsing errors
    catch (const configor::configor_exception &Exception)
    {
        cerr << Exception.what() << endl;
    }
    return 0;
}
