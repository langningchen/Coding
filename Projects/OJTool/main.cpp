// TODO Codeforces GetQuestionDetail parsing file failed

#include "Curl.hpp"
#include <regex>
#include <errno.h>
#include "tidy/tidy.h"
#include "tidy/tidybuffio.h"
#include "TinyXML.hpp"
#include "MD5.hpp"

class TOOL
{
private:
    class LUOGU
    {
    private:
        map<int, string> LanguageName, LanguageMarkdownName;
        map<int, pair<string, string>> DifficultyName, TagName, RecordName;
        map<string, string> TypeName, ColorList;
        string GetCSRF();

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
        string GetCSRF();
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
    return "CPH/." +
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
    cout << "Succeed" << endl;

    // Get the tag information of the luogu website.
    cout << "Getting luogu tags... " << flush;
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
string TOOL::LUOGU::GetCSRF()
{
    // Get csrf token
    string Token = GetStringBetween(GetDataFromFileToString(),
                                    "<meta name=\"csrf-token\" content=\"", "\"");
    if (Token == "")
    {
        TRIGGER_ERROR("Can not find csrf token");
    }
    return Token;
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

    string Token = GetCSRF();
    int ErrorCounter = 0;
    while (1)
    {
        // Get login captcha
        cout << "Getting login captcha... " << flush;
        GetDataToFile("https://www.luogu.com.cn/api/verify/captcha",
                      "Header.tmp",
                      "Captcha.jpeg");
        cout << "Succeed" << endl;

        // Predict captcha
        curl_slist *HeaderList = NULL;
        HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json");
        cout << "Predicting captcha by web api... " << flush;
        string Captcha = "";
        try
        {
            GetDataToFile("https://luogu-captcha-bypass.piterator.com/predict/",
                          "Header.tmp",
                          "Body.tmp",
                          true,
                          "data:image/jpeg;base64," +
                              Base64Encode(
                                  GetDataFromFileToString("Captcha.jpeg")),
                          HeaderList);
            cout << "Succeed" << endl;
            Captcha = GetDataFromFileToString();
        }
        catch (CLNException &Exception)
        {
            cout << "Failed" << endl
                 << "Predicting captcha by tensorflow... " << flush;
            if (system(("python " + CurrentDir + "Projects/OJTool/PredictLuoguCaptcha.py > /dev/null 2>&1").c_str()) == 0)
            {
                cout << "Succeed" << endl;
                Captcha = FixString(GetDataFromFileToString("Captcha.txt"));
            }
            else
            {
                cout << "Failed" << endl;
                system(("code " + CurrentDir + "Captcha.jpeg").c_str());
                cout << "Please input the captcha: ";
                cin >> Captcha;
            }
        }
        remove((CurrentDir + "Captcha.jpeg").c_str());

        // Create a json object to store the login request info
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
                TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Login failed",
                                                    LoginInfo["status"].as_integer(),
                                                    LoginInfo["data"].as_string());
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
    string Token = GetCSRF();
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
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Clock in failed",
                                            ClockInInfo["code"].as_integer(),
                                            ClockInInfo["message"].as_string());
    }
    cout << "Succeed" << endl;
}
void TOOL::LUOGU::GetQuestionDetail(string QuestionID)
{
    // Gets the question detail page
    cout << "Getting question detail page... " << flush;
    GetDataToFile("https://www.luogu.com.cn/problem/" + QuestionID + "?_contentOnly=1");
    json QuestionInfo = json::parse(GetDataFromFileToString());
    if (QuestionInfo["code"].as_integer() != 200)
    {
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Get question detail failed",
                                            QuestionInfo["code"].as_integer(),
                                            QuestionInfo["currentData"]["errorMessage"].as_string());
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
        Temp["input"] = FixString(QuestionInfo["currentData"]["problem"]["samples"][i][0].as_string());
        Temp["output"] = FixString(QuestionInfo["currentData"]["problem"]["samples"][i][1].as_string());
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
    SetDataFromStringToFile(GetCPHFileName("Luogu", QuestionID), CPHData.dump());

    // Save data for markdown
    string OutputContent = "# " + QuestionID + " " + QuestionInfo["currentData"]["problem"]["title"].as_string() + "\n";
    if (QuestionInfo["currentData"]["problem"]["accepted"].as_bool())
        OutputContent += string("***您已经通过此题！***\n") +
                         "\n";
    else if (QuestionInfo["currentData"]["problem"]["submitted"].as_bool())
        OutputContent += string("***您已经提交过此题但未通过！***\n") +
                         "\n";
    if (QuestionInfo["currentData"]["problem"]["background"].as_string() != "")
        OutputContent += string("## Background\n") +
                         "\n" +
                         FixString(QuestionInfo["currentData"]["problem"]["background"]) + "\n" +
                         "\n";
    OutputContent += string("## Description\n") +
                     "\n" +
                     FixString(QuestionInfo["currentData"]["problem"]["description"]) + "\n\n## 输入格式\n\n" + FixString(QuestionInfo["currentData"]["problem"]["inputFormat"]) + "\n\n## 输出格式\n\n" + FixString(QuestionInfo["currentData"]["problem"]["outputFormat"]) + "\n" +
                     "\n" +
                     "## Samples\n" +
                     "\n";
    if (QuestionInfo["currentData"]["problem"]["samples"].size() == 0)
        OutputContent += "None\n\n";
    else
    {
        int Counter = 0;
        for (auto cit : QuestionInfo["currentData"]["problem"]["samples"])
        {
            Counter++;
            OutputContent += string("Input #" + to_string(Counter) + "\n") +
                             "```\n" +
                             FixString(cit[0].as_string()) + "\n" +
                             "```\n" +
                             "Output #" + to_string(Counter) + "\n" +
                             "```\n" +
                             FixString(cit[1].as_string()) + "\n" +
                             "```\n";
        }
    }
    OutputContent += string("\n") +
                     "## Hint\n" +
                     "\n" +
                     FixString(QuestionInfo["currentData"]["problem"]["hint"]) +
                     "\n" +
                     "\n";
    OutputContent += "## Limits\n";
    OutputContent += string("|Test case|Time limit|Memory limit|\n") +
                     "|:---:|:---:|:---:|\n";
    for (unsigned int Counter = 0; Counter < QuestionInfo["currentData"]["problem"]["limits"]["memory"].size(); Counter++)
    {
        OutputContent += "|$" + to_string(Counter + 1) + "$|" +
                         "$" + to_string(QuestionInfo["currentData"]["problem"]["limits"]["memory"][Counter].as_integer() / 1024.0) + "MB$|" +
                         "$" + to_string(QuestionInfo["currentData"]["problem"]["limits"]["time"][Counter].as_integer() / 1000) + "s$|\n";
    }
    OutputContent += string("\n") +
                     "## Last submit code\n" +
                     "\n" +
                     "```" + LanguageMarkdownName[QuestionInfo["currentData"]["lastLanguage"].as_integer()] + "\n" +
                     "" + FixString(QuestionInfo["currentData"]["lastCode"].as_string()) + "\n" +
                     "```\n" +
                     "\n" +
                     "## Other information\n" +
                     "\n";
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
    OutputContent += string("|Item|Value|\n") +
                     "|:---:|:---:|\n" +
                     "|Difficulty|<span style=\"font-weight: bold; color: #" + ColorList[DifficultyName[QuestionInfo["currentData"]["problem"]["difficulty"].as_integer()].second] + "\">" + DifficultyName[QuestionInfo["currentData"]["problem"]["difficulty"].as_integer()].first + "</span>|\n" +
                     "|Label|" + Tags + "|\n" +
                     "|Submit count|$" + QuestionInfo["currentData"]["problem"]["totalSubmit"].as_string() + "$|\n" +
                     "|Pass count|$" + QuestionInfo["currentData"]["problem"]["totalAccepted"].as_string() + "$|\n" +
                     "|Pass rate|$" + to_string(QuestionInfo["currentData"]["problem"]["totalAccepted"].as_integer() * 100.0 / QuestionInfo["currentData"]["problem"]["totalSubmit"].as_integer()) + "\\%$|\n" +
                     "|From|`" + TypeName[QuestionInfo["currentData"]["problem"]["type"].as_string()] + "`|\n" +
                     "|Last submit language|`" + LanguageName[QuestionInfo["currentData"]["lastLanguage"].as_integer()] + "`|\n" +
                     "\n";
    SetDataFromStringToFile("Luogu/" + QuestionID + ".md", OutputContent);

#ifndef TEST
    // Open the file
    if (system(string("code " + CurrentDir + "Luogu/" + QuestionID + ".md").c_str()))
        cout << "Open file \"" + CurrentDir + "Luogu/" << QuestionID << ".md\" failed, please open it manually" << endl;
#endif
}
void TOOL::LUOGU::SubmitCode(string QuestionID)
{
    // Get the code
    string Code = GetDataFromFileToString("Luogu/" + QuestionID + ".cpp");

    // Get the token
    cout << "Getting submit page data... " << flush;
    GetDataToFile("https://www.luogu.com.cn/problem/" + QuestionID);
    string Token = GetCSRF();
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
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Submit failed",
                                            SubmitInfo["status"].as_integer(),
                                            SubmitInfo["errorMessage"].as_string());
    }
    cout << "Succeed" << endl;

    // Get the record ID
    int RecordID = SubmitInfo["rid"].as_integer();

    // Get the record info and wait for the result
    json RecordInfo;
    cout << "Judging... " << flush;
    while (1)
    {
        GetDataToFile("https://www.luogu.com.cn/record/" + to_string(RecordID) + "?_contentOnly=1");
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
    GetDataToFile("https://www.luogu.com.cn/problem/solution/" + QuestionID + "?_contentOnly=1");
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
            SetDataFromStringToFile("Luogu/" + QuestionID + ".cpp",
                                    FixString(GetDataFromFileToString("Luogu/" + QuestionID + ".cpp")) +
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
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Login failed",
                                            LoginInfo["code"].as_integer(),
                                            LoginInfo["msg"].as_string());
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
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Clock in failed",
                                            ClockInInfo["code"].as_integer(),
                                            ClockInInfo["msg"].as_string());
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
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Get question detail failed",
                                            QuestionInfo["code"].as_integer(),
                                            QuestionInfo["msg"].as_string());
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
    string OutputContent = "";
    OutputContent += "# " + QuestionID + " " + QuestionInfo["data"]["title"].as_string() + "\n" +
                     "\n" +
                     "## 题目描述\n" +
                     "\n" +
                     FixString(EraseHTMLElement(QuestionInfo["data"]["content"].as_string())) + "\n" +
                     "\n" +
                     "## 输入格式\n" +
                     "\n" +
                     FixString(QuestionInfo["data"]["inputFormat"].as_string()) + "\n" +
                     "\n" +
                     "## 输出格式\n" +
                     "\n" +
                     FixString(QuestionInfo["data"]["outputFormat"].as_string()) + "\n" +
                     "\n";
    if (!QuestionInfo["data"]["ioName"].is_null())
        OutputContent += string("## 输入输出文件\n") +
                         "\n" +
                         "`" + FixString(QuestionInfo["data"]["ioName"].as_string()) + "`\n" +
                         "\n";
    OutputContent += string("## 输入输出样例\n") +
                     "\n";
    int Counter = 1;
    while (InputSample.find(";") != string::npos && OutputSample.find(";") != string::npos)
    {
        if (FixString(InputSample.substr(0, InputSample.find(";"))) != "无")
        {
            OutputContent += "输入 #" + to_string(Counter) + "\n" +
                             "```\n" +
                             FixString(InputSample.substr(0, InputSample.find(";"))) + "\n" +
                             "```\n" +
                             "输出 #" + to_string(Counter) + "\n" +
                             "```\n" +
                             FixString(OutputSample.substr(0, OutputSample.find(";"))) + "\n" +
                             "```\n";
        }
        InputSample.erase(0, InputSample.find(";") + 1);
        OutputSample.erase(0, OutputSample.find(";") + 1);
        Counter++;
    }
    OutputContent += "\n";
    if (EraseHTMLElement(QuestionInfo["data"]["description"].as_string()) != "")
    {
        OutputContent += string("## 说明\n") +
                         "\n" +
                         FixString(EraseHTMLElement(QuestionInfo["data"]["description"].as_string())) + "\n" +
                         "\n";
    }
    OutputContent += string("## 其他数据\n") +
                     "\n" +
                     "|项目|值|\n" +
                     "|:---:|:---:|\n" +
                     "|难度|<span style=\"" +
                     "text-align: center; " +
                     "display: inline-block; " +
                     "border-radius: 3px; " +
                     "color: white; " +
                     "width: 120px; " +
                     "height: 24px; " +
                     "background-color: " + DifficultyName[QuestionInfo["data"]["level"].as_integer()].second +
                     "\">" +
                     DifficultyName[QuestionInfo["data"]["level"].as_integer()].first + "</span>|\n" +
                     "|提交次数|$" + QuestionInfo["data"]["submitInfo"]["totalCount"].as_string() + "$|\n" +
                     "|提交人数|$" + QuestionInfo["data"]["submitInfo"]["submitPersonCount"].as_string() + "$|\n" +
                     "|通过人数|$" + QuestionInfo["data"]["submitInfo"]["passCount"].as_string() + "$|\n" +
                     "|通过率|$" + QuestionInfo["data"]["submitInfo"]["passRate"].as_string() + "\\%$|\n" +
                     "\n";
    SetDataFromStringToFile("Etiger/" + QuestionID + ".md", OutputContent);

#ifndef TEST
    // Open file
    if (system(string("code " + CurrentDir + "Etiger/" + QuestionID + ".md").c_str()))
        cout << "Open file \"" + CurrentDir + "Etiger/" << QuestionID << ".md\" failed, please open it manually" << endl;
#endif
}
void TOOL::ETIGER::SubmitCode(string QuestionID)
{
    // Get code
    string Code = GetDataFromFileToString("Etiger/" + QuestionID + ".cpp");

    // Uncomment freopen and save
    Code = StringReplaceAll(Code, "// freopen", "freopen");
    SetDataFromStringToFile("Etiger/" + QuestionID + ".cpp", Code);

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
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Get submit result failed",
                                            SubmitInfo["code"].as_integer(),
                                            SubmitInfo["msg"].as_string());
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
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Get comments failed",
                                            CommentsData["code"].as_integer(),
                                            CommentsData["msg"].as_string());
    }
    cout << "Success" << endl;

    // Save comments to a string joined by newline
    string Comments = "";
    for (auto i : CommentsData["data"]["records"])
        Comments += FixString(i["content"].as_string()) + "\n";

    // Add comments to the code
    SetDataFromStringToFile("Etiger/" + QuestionID + ".cpp",
                            FixString(GetDataFromFileToString("Etiger/" + QuestionID + ".cpp")) +
                                "\n" +
                                "\n" +
                                "/*\n" +
                                Comments +
                                "*/" +
                                "\n");
}
string TOOL::CODEFORCES::GetCSRF()
{
    // Get csrf token
    string Token = GetStringBetween(GetDataFromFileToString(),
                                    "<input type='hidden' name='csrf_token' value='", "'/>");
    if (Token == "")
    {
        TRIGGER_ERROR("Can not find csrf token");
    }
    return Token;
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
                  string("csrf_token=" + GetCSRF() +
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
                          string("csrf_token=" + GetCSRF() +
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
                TRIGGER_ERROR("Login failed");
            }
        }
        else
        {
            TRIGGER_ERROR("Login failed");
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
        TRIGGER_ERROR(string("Parse question detail error: ") + QuestionXmlDocument.ErrorDesc());
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

#ifndef TEST
    // Open the question detail file
    if (system(string("code /workspaces/Coding/Codeforces/" + QuestionID + ".md").c_str()))
        cout << "Open file \"/workspaces/Coding/Codeforces/" << QuestionID << ".md\" failed, please open it manually" << endl;
#endif
}
void TOOL::CODEFORCES::SubmitCode(string QuestionID)
{
    // Get the code
    string Code = GetDataFromFileToString("Codeforces/" + QuestionID + ".cpp");

    // Add a number to the code to avoid submitting the same code
    Code += "\n\n// " + to_string(time(NULL)) + "\n";

    // Get submit page data
    cout << "Getting submit page data... " << flush;
    GetDataToFile("https://codeforces.com/problemset/submit");
    cout << "Succeed" << endl;

    // Submit the code
    int HTTPResponseCode = 0;
    cout << "Submitting... " << flush;
    GetDataToFile("https://codeforces.com/problemset/submit?csrf_token=" + GetCSRF(),
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  string(
                      "csrf_token=" + GetCSRF() +
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
        TRIGGER_ERROR("Submit failed");
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
        TRIGGER_ERROR(string("Parse submission list error: ") + SubmitListXmlDocument.ErrorDesc());
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
                             "&csrf_token=" + GetCSRF()),
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
        SetDataFromStringToFile("Codeforces/" + QuestionID + "_" + to_string(i) + ".in",
                                result["input#" + to_string(i)].as_string());
        SetDataFromStringToFile("Codeforces/" + QuestionID + "_" + to_string(i) + ".out",
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
        TRIGGER_ERROR("Login failed");
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
                  "UVa/" + QuestionID + ".pdf",
                  false,
                  "",
                  NULL,
                  NULL,
                  "application/json",
                  "",
                  true);
    cout << "Succeed" << endl;

#ifndef TEST
    // Open the pdf file
    if (system(string("code " + CurrentDir + "UVa/" + QuestionID + ".pdf").c_str()))
        cout << "Open file \"" + CurrentDir + "UVa/" << QuestionID << ".md\" failed, please open it manually" << endl;
#endif
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
    string Code = GetDataFromFileToString("UVa/" + QuestionID + ".cpp");

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
    string SubmitPostBody = "--" + MULTIPART_BOUNDARY + "\n" +
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
                            "--" + MULTIPART_BOUNDARY + "\nContent-Disposition: form-data; name=\"codeupl\"; filename=\"\"\n" +
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
                  SubmitPostBody,
                  HeaderList,
                  &HTTPResponseCode,
                  MULTIPART);
    if (HTTPResponseCode == 200)
    {
        TRIGGER_ERROR("Submit failed");
    }

    // Get the submission id
    string SubmissionID = FindLocation();
    SubmissionID = SubmissionID.substr(SubmissionID.find_last_of('+') + 1);
    if (atoi(SubmissionID.c_str()) == 0)
    {
        TRIGGER_ERROR("Get submission id failed");
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
        {
            TRIGGER_ERROR("Can not find the judge result with submission id " + SubmissionID);
        }
    }
}
TOOL::TOOL(string FileName, string Operation)
{
    // Choose the tool
    if (FileName.find("Luogu") != string::npos)
    {
        LUOGU Luogu;
        Luogu.Login(GetDataFromFileToString("Keys/LuoguUsername"), GetDataFromFileToString("Keys/LuoguPassword"));
        if (Operation == "GetQuestionDetail")
        {
#ifdef TEST
            OutputSummary("##### Luogu get question detail");
#endif
            Luogu.GetQuestionDetail(GetStringBetween(FileName, "Luogu/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else if (Operation == "SubmitCode")
        {
#ifdef TEST
            OutputSummary("##### Luogu submit code");
#endif
            Luogu.SubmitCode(GetStringBetween(FileName, "Luogu/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else if (Operation == "GetAnswerOrTips")
        {
#ifdef TEST
            OutputSummary("##### Luogu get answer or tips");
#endif
            Luogu.GetAnswerOrTips(GetStringBetween(FileName, "Luogu/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else
        {
            TRIGGER_ERROR("Arguments invalid");
        }
    }
    else if (FileName.find("Etiger") != string::npos)
    {
        ETIGER Etiger;
        Etiger.Login(GetDataFromFileToString("Keys/EtigerUsername"), GetDataFromFileToString("Keys/EtigerPassword"));
        if (Operation == "GetQuestionDetail")
        {
#ifdef TEST
            OutputSummary("##### Etiger get question detail");
#endif
            Etiger.GetQuestionDetail(GetStringBetween(FileName, "Etiger/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else if (Operation == "SubmitCode")
        {
#ifdef TEST
            OutputSummary("##### Etiger submit code");
#endif
            Etiger.SubmitCode(GetStringBetween(FileName, "Etiger/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else if (Operation == "GetAnswerOrTips")
        {
#ifdef TEST
            OutputSummary("##### Etiger get answer or tips");
#endif
            Etiger.GetAnswerOrTips(GetStringBetween(FileName, "Etiger/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else
        {
            TRIGGER_ERROR("Arguments invalid");
        }
    }
    else if (FileName.find("UVa") != string::npos)
    {
        UVA UVa;
        UVa.Login(GetDataFromFileToString("Keys/UVaUsername"), GetDataFromFileToString("Keys/UVaPassword"));
        if (Operation == "GetQuestionDetail")
        {
#ifdef TEST
            OutputSummary("##### UVa get question detail");
#endif
            UVa.GetQuestionDetail(GetStringBetween(FileName, "UVa/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else if (Operation == "SubmitCode")
        {
#ifdef TEST
            OutputSummary("##### UVa submit code");
#endif
            UVa.SubmitCode(GetStringBetween(FileName, "UVa/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else
        {
            TRIGGER_ERROR("Arguments invalid");
        }
    }
    else if (FileName.find("Codeforces") != string::npos)
    {
        CODEFORCES Codeforces;
        Codeforces.Login(GetDataFromFileToString("Keys/CodeforcesUsername"), GetDataFromFileToString("Keys/CodeforcesPassword"));
        if (Operation == "GetQuestionDetail")
        {
#ifdef TEST
            OutputSummary("##### Codeforces get question detail");
#endif
            Codeforces.GetQuestionDetail(GetStringBetween(FileName, "Codeforces/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else if (Operation == "SubmitCode")
        {
#ifdef TEST
            OutputSummary("##### Codeforces submit code");
#endif
            Codeforces.SubmitCode(GetStringBetween(GetStringBetween(FileName, "Codeforces/", ".cpp"), "", "/"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else
        {
            TRIGGER_ERROR("Arguments invalid");
        }
    }
    else
    {
        TRIGGER_ERROR("Arguments invalid");
    }
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
    {
        TRIGGER_ERROR("Arguments invalid");
    }
}
TOOL::~TOOL()
{
}
int main(int argc, char **argv)
{
    CLN_TRY
    GetCurrentDir();
#ifdef TEST
    TOOL("Luogu/P1000.cpp", "GetQuestionDetail");
    OutputSummary("");
    TOOL("Luogu/P1000.cpp", "SubmitCode");
    OutputSummary("");
    TOOL("Luogu/P1000.cpp", "GetAnswerOrTips");
    OutputSummary("");

    TOOL("Etiger/0001.cpp", "GetQuestionDetail");
    OutputSummary("");
    TOOL("Etiger/0001.cpp", "SubmitCode");
    OutputSummary("");
    TOOL("Etiger/0001.cpp", "GetAnswerOrTips");
    OutputSummary("");

    TOOL("UVa/00100.cpp", "GetQuestionDetail");
    OutputSummary("");
    TOOL("UVa/00100.cpp", "SubmitCode");
    OutputSummary("");

    TOOL("Codeforces/1A.cpp", "GetQuestionDetail");
    OutputSummary("");
    TOOL("Codeforces/1A.cpp", "SubmitCode");
    OutputSummary("");
#else
    // If the argument count is 3, the tool is used to GetQuestionDetail/SubmitCode/GetAnswerOrTips
    if (argc == 3)
        TOOL Tool(argv[1], argv[2]);

    // If the argument count is 4, the tool is used to login and clock in
    else if (argc == 4)
        TOOL Tool(argv[1], argv[2], argv[3]);
    else
    {
        TRIGGER_ERROR("Arguments invalid");
    }
#endif
    CLN_CATCH
    return 0;
}
