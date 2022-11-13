#include <iostream>
#include <unistd.h>
#include "../Lib/tidy/tidy.h"
#include "../Lib/tidy/tidybuffio.h"
#include <stdio.h>
#include <errno.h>
#include "../Lib/Curl.cpp"
#include "../Lib/TinyXML.cpp"
void Usage()
{
    cout << R"(
使用方法
    本程序文件名 <服务器名称> <用户名> <密码> <命令> [<参数>]

输入参数
    服务器名称
        Luogu
            洛谷
        Etiger
            太戈编程
        UVa
            UVa Online Judge
        Codeforces
            codeforces
    用户名
        登录用户名
    密码
        登录密码
    命令
        GetQuestionDetail
            获取题目信息
        SubmitCode
            提交代码
        ClockIn (仅支持部分服务器)
            签到
    参数（可选）
        若命令为ClockIn
            此参数省略
        若命令为GetQuestionDetail
            此参数为题目ID
        若命令为SubmitCode
            此参数为题目ID

输出内容
    若程序运行正确
        若服务器名称为Luogu
            若命令为GetQuestionDetail
                打开文件"/workspaces/Coding/Luogu/<题目编号>.md"
                写入题目数据
                关闭文件
            若命令为SubmitCode
                读取文件"/workspaces/Coding/Luogu/<题目编号>.cpp"
                提交
                输出评测结果
            若命令为ClockIn
                无输出
        若服务器名称为Etiger
            若命令为GetQuestionDetail
                打开文件"/workspaces/Coding/Etiger/<题目编号>.md"
                写入题目数据
                关闭文件
            若命令为SubmitCode
                读取文件"/workspaces/Coding/Etiger/<题目编号>.cpp"
                提交
                输出评测结果
            若命令为ClockIn
                无输出
        若服务器名称为UVa
            若命令为GetQuestionDetail
                现在没有设计好，暂不支持此命令
                // 打开文件"/workspaces/Coding/UVa/<题目编号>.pdf"
                // 写入题目数据
                // 关闭文件
            若命令为SubmitCode
                现在没有设计好，暂不支持此命令
                // 读取文件"/workspaces/Coding/UVa/<题目编号>.cpp"
                // 提交
                // 输出评测结果
        若服务器名称为Codeforces
            若命令为GetQuestionDetail
                打开文件"/workspaces/Coding/Codeforces/<题目编号>.md"
                写入题目数据
                关闭文件
            若命令为SubmitCode
                现在没有设计好，暂不支持此命令
                // 读取文件"/workspaces/Coding/Codeforces/<题目编号>.cpp"
                // 提交
                // 输出评测结果
    若程序运行失败
        输出错误信息或返回非0
)" << endl;
    Clean();
    exit(0);
}
string Tidy(string Input)
{
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
namespace Luogu
{
    map<int, string> LanguageName, LanguageMarkdownName;
    map<int, pair<string, string>> DifficultyName, TagName, RecordName;
    map<string, string> TypeName, ColorList;
    void Init()
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

        GetDataToFile("https://www.luogu.com.cn/_lfe/config");
        json Config = json::parse(GetDataFromFileToString());
        GetDataToFile("https://www.luogu.com.cn/_lfe/tags");
        json Tag = json::parse(GetDataFromFileToString());
        for (json::iterator jit = Config["codeLanguages"].begin(); jit != Config["codeLanguages"].end(); jit++)
        {
            LanguageName[jit.value()["value"].as_integer()] = jit.value()["name"].as_string();
            LanguageMarkdownName[jit.value()["value"].as_integer()] = jit.value()["hljsMode"].as_string();
        }
        LanguageName[0] = "自动识别语言";
        for (json::iterator jit = Config["problemDifficulty"].begin(); jit != Config["problemDifficulty"].end(); jit++)
            DifficultyName[jit.value()["id"].as_integer()] = make_pair(jit.value()["name"].as_string(), jit.value()["color"].as_string());
        for (json::iterator jit = Config["problemTypes"].begin(); jit != Config["problemTypes"].end(); jit++)
            TypeName[jit.value()["id"].as_string()] = jit.value()["name"].as_string();
        json Temp;
        for (json::iterator jit = Tag["types"].begin(); jit != Tag["types"].end(); jit++)
            Temp[jit.value()["id"].as_integer()] = jit.value()["color"].as_string();
        for (json::iterator jit = Tag["tags"].begin(); jit != Tag["tags"].end(); jit++)
            TagName[jit.value()["id"].as_integer()] = make_pair(jit.value()["name"].as_string(), Temp[jit.value()["type"].as_integer()]);
        for (json::iterator jit = Config["recordStatus"].begin(); jit != Config["recordStatus"].end(); jit++)
            RecordName[jit.value()["id"].as_integer()] = make_pair(jit.value()["name"].as_string(), jit.value()["shortName"].as_string());
    }
    void Login(string Username, string Password)
    {
        int HTTPResponseCode;
        GetDataToFile("https://www.luogu.com.cn/auth/login", "Header.tmp", "Body.tmp", false, "", NULL, &HTTPResponseCode);
        if (HTTPResponseCode == 302)
            return;
        string Token = GetStringBetween(GetDataFromFileToString(), "<meta name=\"csrf-token\" content=\"", "\"");
        int ErrorCounter = 0;
        while (1)
        {
            GetDataToFile("https://www.luogu.com.cn/api/verify/captcha");
            curl_slist *HeaderList = NULL;
            HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json");
            GetDataToFile("https://luogu-captcha-bypass.piterator.com/predict/", "Header.tmp", "Body.tmp", true, string("data:image/jpeg;base64," + Base64Encode(GetDataFromFileToString())), HeaderList);
            string Captcha = GetDataFromFileToString();
            json LoginRequest;
            LoginRequest["username"] = Username;
            LoginRequest["password"] = Password;
            LoginRequest["captcha"] = Captcha;
            HeaderList = NULL;
            HeaderList = curl_slist_append(HeaderList, string("X-CSRF-TOKEN: " + Token).c_str());
            HeaderList = curl_slist_append(HeaderList, string("Content-Length: " + to_string(LoginRequest.dump().size())).c_str());
            HeaderList = curl_slist_append(HeaderList, "Host: www.luogu.com.cn");
            HeaderList = curl_slist_append(HeaderList, "Referer: https://www.luogu.com.cn/auth/login");
            HeaderList = curl_slist_append(HeaderList, "Origin: https://www.luogu.com.cn");
            HeaderList = curl_slist_append(HeaderList, "X-Requested-With: XMLHttpRequest");
            GetDataToFile("https://www.luogu.com.cn/api/auth/userPassLogin", "Header.tmp", "Body.tmp", true, LoginRequest.dump(), HeaderList);
            json LoginInfo = json::parse(GetDataFromFileToString());
            if (!LoginInfo["status"].is_null())
            {
                if (LoginInfo["currentData"]["errorMessage"].as_string() != "验证码错误" && ErrorCounter < 5)
                {
                    cout << "登录失败，错误码：" << LoginInfo["status"].as_integer() << "，错误信息：" << LoginInfo["data"].as_string() << endl;
                    return;
                }
            }
            else
                break;
            ErrorCounter++;
        }
    }
    void ClockIn()
    {
        GetDataToFile("https://www.luogu.com.cn/");
        string Token = GetStringBetween(GetDataFromFileToString(), "<meta name=\"csrf-token\" content=\"", "\"");
        curl_slist *HeaderList = NULL;
        HeaderList = curl_slist_append(HeaderList, string("X-CSRF-TOKEN: " + Token).c_str());
        HeaderList = curl_slist_append(HeaderList, "Host: www.luogu.com.cn");
        HeaderList = curl_slist_append(HeaderList, "Referer: https://www.luogu.com.cn/");
        HeaderList = curl_slist_append(HeaderList, "Origin: https://www.luogu.com.cn");
        HeaderList = curl_slist_append(HeaderList, "X-Requested-With: XMLHttpRequest");
        GetDataToFile("https://www.luogu.com.cn/index/ajax_punch", "Header.tmp", "Body.tmp", true, "{}", HeaderList);
        json ClockInInfo = json::parse(GetDataFromFileToString());
        if (ClockInInfo["code"].as_integer() != 200)
        {
            cout << "打卡失败，错误码：" << ClockInInfo["code"].as_integer() << "，错误信息：" << ClockInInfo["message"].as_string() << endl;
            return;
        }
    }
    void GetQuestionDetail(string QuestionID)
    {
        GetDataToFile("https://www.luogu.com.cn/problem/" + QuestionID + "?_contentOnly=1");
        json QuestionInfo = json::parse(GetDataFromFileToString());
        if (QuestionInfo["code"].as_integer() != 200)
        {
            cout << "获取题目信息失败，错误码：" << QuestionInfo["code"].as_integer() << "，错误信息：" << QuestionInfo["currentData"]["errorMessage"].as_string() << endl;
            return;
        }
        ofstream OutputFileStream(string("/workspaces/Coding/Luogu/" + QuestionID + ".md").c_str());
        if (OutputFileStream.bad())
        {
            cout << "无法打开输出文件。" << endl;
            return;
        }
        OutputFileStream << "# " << QuestionID << " " << QuestionInfo["currentData"]["problem"]["title"] << endl;
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
            for (json::iterator cit = QuestionInfo["currentData"]["problem"]["samples"].begin(); cit != QuestionInfo["currentData"]["problem"]["samples"].end(); cit++)
            {
                OutputFileStream << "输入 #" << Counter << endl
                                 << "```" << endl
                                 << FixString(cit.value()[0].as_string()) << endl
                                 << "```" << endl
                                 << "输出 #" << Counter << endl
                                 << "```" << endl
                                 << FixString(cit.value()[1].as_string()) << endl
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
        for (json::iterator cit = QuestionInfo["currentData"]["problem"]["tags"].begin(); cit != QuestionInfo["currentData"]["problem"]["tags"].end(); cit++)
            Tags += "<span style=\"display: inline-block; margin-right: 5px; margin-bottom: 5px; border-radius: 2px; color: white; padding: 0px 8px; background-color: #" + ColorList[TagName[cit.value().as_integer()].second] + "; \">" + TagName[cit.value().as_integer()].first + "</span>";
        OutputFileStream << "|项目|值|" << endl
                         << "|:---:|:---:|" << endl
                         << "|难度|<span style=\"font-weight: bold; color: #" << ColorList[DifficultyName[QuestionInfo["currentData"]["problem"]["difficulty"].as_integer()].second] << "\">" << DifficultyName[QuestionInfo["currentData"]["problem"]["difficulty"].as_integer()].first << "</span>|" << endl
                         << "|标签|" << Tags << "|" << endl
                         << "|提交人数|$" << QuestionInfo["currentData"]["problem"]["totalSubmit"] << "$|" << endl
                         << "|通过人数|$" << QuestionInfo["currentData"]["problem"]["totalAccepted"] << "$|" << endl
                         << "|通过率|$" << (QuestionInfo["currentData"]["problem"]["totalAccepted"].as_integer() * 100.0 / QuestionInfo["currentData"]["problem"]["totalSubmit"].as_integer()) << "\\%$|" << endl
                         << "|来源|`" << TypeName[QuestionInfo["currentData"]["problem"]["type"].as_string()] << "`|" << endl
                         << "|最后一次提交语言|`" << LanguageName[QuestionInfo["currentData"]["lastLanguage"].as_integer()] << "`|" << endl
                         << endl;
        OutputFileStream.close();
    }
    void SubmitCode(string QuestionID)
    {
        string Code = GetDataFromFileToString(string("../Luogu/" + QuestionID + ".cpp"));
        GetDataToFile("https://www.luogu.com.cn/problem/" + QuestionID);
        string Token = GetStringBetween(GetDataFromFileToString(), "<meta name=\"csrf-token\" content=\"", "\"");
        json SubmitRequest;
        SubmitRequest["code"] = Code;
        SubmitRequest["enableO2"] = 1;
        SubmitRequest["lang"] = 0;
        curl_slist *HeaderList = NULL;
        HeaderList = curl_slist_append(HeaderList, string("X-CSRF-TOKEN: " + Token).c_str());
        HeaderList = curl_slist_append(HeaderList, string("Content-Length: " + to_string(SubmitRequest.dump().size())).c_str());
        HeaderList = curl_slist_append(HeaderList, "Host: www.luogu.com.cn");
        HeaderList = curl_slist_append(HeaderList, string("Referer: https://www.luogu.com.cn/problem/" + QuestionID).c_str());
        HeaderList = curl_slist_append(HeaderList, "Origin: https://www.luogu.com.cn");
        HeaderList = curl_slist_append(HeaderList, "X-Requested-With: XMLHttpRequest");
        GetDataToFile("https://www.luogu.com.cn/fe/api/problem/submit/" + QuestionID, "Header.tmp", "Body.tmp", true, SubmitRequest.dump(), HeaderList);
        json SubmitInfo = json::parse(GetDataFromFileToString());
        if (!SubmitInfo["status"].is_null())
        {
            cout << "提交失败，错误码：" << SubmitInfo["status"].as_integer() << "，错误信息：" << SubmitInfo["errorMessage"].as_string() << endl;
            return;
        }
        int RecordID = SubmitInfo["rid"].as_integer();
        json RecordInfo;
        while (!RecordInfo["currentData"]["record"]["status"].is_number() || RecordInfo["currentData"]["record"]["status"].as_integer() < 2)
        {
            GetDataToFile("https://www.luogu.com.cn/record/" + to_string(RecordID) + "?_contentOnly=1");
            RecordInfo = json::parse(GetDataFromFileToString());
        }
        if (!RecordInfo["currentData"]["record"]["detail"]["compileResult"]["success"].as_bool())
            cout << "编译错误：" << endl
                 << RecordInfo["currentData"]["record"]["detail"]["compileResult"]["message"].as_string() << endl;
        else
        {
            cout << RecordInfo["currentData"]["record"]["score"].as_integer() << "pts" << endl;
            for (json::iterator jit = RecordInfo["currentData"]["record"]["detail"]["judgeResult"]["subtasks"].begin(); jit != RecordInfo["currentData"]["record"]["detail"]["judgeResult"]["subtasks"].end(); jit++)
            {
                cout << "#" << jit.value()["id"] << endl;
                for (json::iterator jit2 = RecordInfo["currentData"]["record"]["detail"]["judgeResult"]["subtasks"][jit.value()["id"].as_integer()]["testCases"].begin(); jit2 != RecordInfo["currentData"]["record"]["detail"]["judgeResult"]["subtasks"][jit.value()["id"].as_integer()]["testCases"].end(); jit2++)
                    cout << "    #" << jit2.value()["id"].as_integer() << " " << jit2.value()["score"].as_integer() << "pts " << RecordName[jit2.value()["status"].as_integer()].second << " " << jit2.value()["time"].as_integer() << "ms " << jit2.value()["memory"].as_integer() << "KB" << endl;
            }
            cout << RecordInfo["currentData"]["record"]["score"].as_integer() << "pts" << endl;
        }
    }
}
namespace Etiger
{
    string Token = "";
    map<int, pair<string, string>> DifficultyName;
    void Init()
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
    void Login(string Username, string Password)
    {
        json LoginRequest;
        LoginRequest["name"] = Username;
        LoginRequest["password"] = Password;
        curl_slist *HeaderList = NULL;
        HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json;charset=utf-8");
        HeaderList = curl_slist_append(HeaderList, "lang: zh");
        HeaderList = curl_slist_append(HeaderList, "Host: www.etiger.vip");
        GetDataToFile("https://www.etiger.vip/thrall-web/user/login", "Header.tmp", "Body.tmp", true, LoginRequest.dump(), HeaderList);
        json LoginInfo = json::parse(GetDataFromFileToString());
        if (LoginInfo["code"] != 200)
        {
            cout << "登录失败，错误码：" << LoginInfo["code"].as_integer() << "，错误信息：" << LoginInfo["msg"].as_string() << endl;
            return;
        }
        Token = LoginInfo["data"]["ticket"].as_string();
    }
    void ClockIn()
    {
        curl_slist *HeaderList = NULL;
        HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json;charset=utf-8");
        HeaderList = curl_slist_append(HeaderList, "lang: zh");
        HeaderList = curl_slist_append(HeaderList, "Host: www.etiger.vip");
        HeaderList = curl_slist_append(HeaderList, string("Token: " + Token).c_str());
        GetDataToFile("https://www.etiger.vip/thrall-web/sign/dailySign", "Header.tmp", "Body.tmp", false, "", HeaderList);
        json ClockInInfo = json::parse(GetDataFromFileToString());
        if (ClockInInfo["code"] != 200)
        {
            cout << "签到失败，错误码：" << ClockInInfo["code"].as_integer() << "，错误信息：" << ClockInInfo["msg"].as_string() << endl;
            return;
        }
    }
    void GetQuestionDetail(string QuestionID)
    {
        curl_slist *HeaderList = NULL;
        HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json;charset=utf-8");
        HeaderList = curl_slist_append(HeaderList, "lang: zh");
        HeaderList = curl_slist_append(HeaderList, "Host: www.etiger.vip");
        HeaderList = curl_slist_append(HeaderList, string("Token: " + Token).c_str());
        GetDataToFile("https://www.etiger.vip/thrall-web/question/getById?id=" + QuestionID, "Header.tmp", "Body.tmp", false, "", HeaderList);
        json QuestionInfo = json::parse(GetDataFromFileToString());
        if (QuestionInfo["code"] != 200)
        {
            cout << "获取题目信息失败，错误码：" << QuestionInfo["code"].as_integer() << "，错误信息：" << QuestionInfo["msg"].as_string() << endl;
            return;
        }
        ofstream OutputFileStream(string("/workspaces/Coding/Etiger/" + QuestionID + ".md"));
        if (OutputFileStream.bad())
        {
            cout << "无法打开输出文件。" << endl;
            return;
        }
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
        string InputSample = QuestionInfo["data"]["inputSample"].as_string();
        string OutputSample = QuestionInfo["data"]["outputSample"].as_string();
        while (InputSample.find(";") != InputSample.npos && OutputSample.find(";") != OutputSample.npos)
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
                         << "|难度|<span style=\"text-align: center; display: inline-block; border-radius: 3px; color: white; width: 120px; height: 24px; background-color: " << DifficultyName[QuestionInfo["data"]["level"].as_integer()].second << "\">" << DifficultyName[QuestionInfo["data"]["level"].as_integer()].first << "</span>|" << endl
                         << "|提交次数|$" << QuestionInfo["data"]["submitInfo"]["totalCount"] << "$|" << endl
                         << "|提交人数|$" << QuestionInfo["data"]["submitInfo"]["submitPersonCount"] << "$|" << endl
                         << "|通过人数|$" << QuestionInfo["data"]["submitInfo"]["passCount"] << "$|" << endl
                         << "|通过率|$" << QuestionInfo["data"]["submitInfo"]["passRate"] << "\\%$|" << endl
                         << endl;
        OutputFileStream.close();
        system(string("code /workspaces/Coding/Etiger/" + QuestionID + ".md").c_str());
    }
    void SubmitCode(string QuestionID)
    {
        string Code = GetDataFromFileToString(string("../Etiger/" + QuestionID + ".cpp"));
        // Code = StringReplaceAll(Code, "// freopen", "freopen");
        // ofstream OutputFileStream("/workspaces/Coding/Etiger/" + QuestionID + ".cpp");
        // OutputFileStream << Code << endl;
        // OutputFileStream.close();
        json SubmitRequest;
        SubmitRequest["comment"] = "";
        SubmitRequest["lang"] = "CPP";
        SubmitRequest["submitType"] = 0;
        SubmitRequest["questionId"] = QuestionID;
        SubmitRequest["src"] = Code;
        curl_slist *HeaderList = NULL;
        HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json;charset=utf-8");
        HeaderList = curl_slist_append(HeaderList, "lang: zh");
        HeaderList = curl_slist_append(HeaderList, "Host: www.etiger.vip");
        HeaderList = curl_slist_append(HeaderList, string("Token: " + Token).c_str());
        GetDataToFile("https://www.etiger.vip/thrall-web/saveSubmit", "Header.tmp", "Body.tmp", true, SubmitRequest.dump(), HeaderList);
        json SubmitInfo = json::parse(GetDataFromFileToString());
        if (SubmitInfo["code"] != 200)
        {
            cout << "提交失败，错误码：" << SubmitInfo["code"].as_integer() << "，错误信息：" << SubmitInfo["msg"].as_string() << endl;
            return;
        }
        cout << SubmitInfo["data"]["grade"] << "pts" << endl;
        int Counter = 1;
        for (detail::iterator<json> Iterator = SubmitInfo["data"]["result"].begin(); Iterator != SubmitInfo["data"]["result"].end(); Iterator++)
        {
            cout << "#" << Counter << " " << Iterator.value()["type"].as_string() << " " << Iterator.value()["timeUsed"] << "ms " << Iterator.value()["memUsed"] << "B" << endl;
            Counter++;
            if (Iterator.value()["input"].as_string() != "")
            {
                cout << "    输入：" << Iterator.value()["input"].as_string() << endl
                     << "    标准输出：" << Iterator.value()["output"].as_string() << endl
                     << "    我的输出：" << Iterator.value()["myOutput"].as_string() << endl;
            }
        }
        cout << SubmitInfo["data"]["grade"] << "pts" << endl;
        if (SubmitInfo["data"]["grade"] == 100)
            remove(string("/workspaces/Coding/Etiger/" + QuestionID + ".md").c_str());
    }
}
namespace Codeforces
{
    const string ftaa = "rv5q0yv00p85nhpyi7";
    const string bfaa = "f1b3f18c715565b589b7823cda7448ce";
    string GetCRSF()
    {
        return GetStringBetween(GetDataFromFileToString(), "<input type='hidden' name='csrf_token' value='", "'/>");
    }
    void Login(string Username, string Password)
    {
        int HTTPResponseCode;
        GetDataToFile("https://codeforces.com/enter",
                      "Header.tmp",
                      "Body.tmp",
                      false,
                      "",
                      NULL,
                      &HTTPResponseCode);
        if (HTTPResponseCode == 302)
            return;
        HTTPResponseCode = 0;
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
                      "application/x-www-form-urlencoded");
        if (HTTPResponseCode != 302)
        {
            cout << "登录失败" << endl;
            return;
        }
    }
    string OutputPre(TiXmlElement *Input)
    {
        string Output;
        Output += "```\n";
        for (TiXmlNode *i = Input->FirstChild(); i != NULL; i = i->NextSibling())
            if (i->Type() == TiXmlNode::TINYXML_TEXT)
                Output += i->ToText()->Value();
            else if (i->Type() == TiXmlNode::TINYXML_ELEMENT)
                if (string(i->Value()) == "br")
                    Output += "\n";
        if (Output[Output.size() - 1] != '\n')
            Output += "\n";
        Output += "```";
        return Output;
    }
    string Output(TiXmlElement *Input, bool InLatex = false)
    {
        string OutputValue = "";
        string Value = Input->Value();
        if (Value == "pre")
        {
            OutputValue += "\n" + OutputPre(Input) + "\n";
            return OutputValue;
        }
        else if (Value == "img")
        {
            OutputValue += " ![](" + string(Input->Attribute("src")) + ") ";
            return OutputValue;
        }
        if (Value == "ul")
            OutputValue += "\n";
        else if (Value == "li")
            OutputValue += "- ";
        else if (Value == "span" && Input->Attribute("class") != NULL)
        {
            string Class = Input->Attribute("class");
            if (Class == "tex-font-style-bf")
                OutputValue += " **";
            else if (Class == "tex-font-style-tt")
                OutputValue += " `";
            else
                OutputValue += " $";
            InLatex = true;
        }
        else if (Value == "sup")
            OutputValue += "^{";
        else if (Value == "sub")
            OutputValue += "_{";

        for (TiXmlNode *i = Input->FirstChild(); i != NULL; i = i->NextSibling())
            if (i->Type() == TiXmlNode::TINYXML_TEXT)
                OutputValue += i->ToText()->Value();
            else if (i->Type() == TiXmlNode::TINYXML_ELEMENT)
                OutputValue += Output(i->ToElement(), InLatex);

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
    void GetQuestionDetail(string QuestionID)
    {
        GetDataToFile("https://codeforces.com/problemset/problem/" + QuestionID.substr(0, QuestionID.size() - 1) + "/" + QuestionID.substr(QuestionID.size() - 1));
        TiXmlDocument QuestionXmlDocument;
        QuestionXmlDocument.Parse(Tidy(GetDataFromFileToString()).c_str());
        if (QuestionXmlDocument.Error())
        {
            cout << "系统错误：" << QuestionXmlDocument.ErrorDesc() << endl;
            return;
        }
        ofstream OutputFileStream(string("/workspaces/Coding/Codeforces/" + QuestionID + ".md").c_str());
        if (OutputFileStream.bad())
        {
            cout << "无法打开输出文件。" << endl;
            return;
        }
        TiXmlHandle QuestionXmlHandle = TiXmlHandle(&QuestionXmlDocument).FirstChild("html").FirstChild("body").Child("div", 3).Child("div", 4).Child("div", 1).Child("div", 2).Child("div", 1).Child("div", 0);
        OutputFileStream << "# " << QuestionXmlHandle.Child(0).Child(0).ToElement()->GetText() << endl
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
    }
    void SubmitCode(string QuestionID)
    {
        string Code = GetDataFromFileToString("../Codeforces/" + QuestionID + ".cpp");
        Code += "\n\n// " + to_string(time(NULL));
        GetDataToFile("https://codeforces.com/problemset/submit");
        int HTTPResponseCode = 0;
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
                      "application/x-www-form-urlencoded");
        if (HTTPResponseCode != 302)
        {
            cout << "提交失败，Codeforces不允许提交两次相同的代码" << endl;
            return;
        }
        GetDataToFile("https://codeforces.com/problemset/status/page/1?my=on");
        TiXmlDocument SubmitXmlDocument;
        SubmitXmlDocument.Parse(Tidy(GetDataFromFileToString()).c_str());
        if (SubmitXmlDocument.Error())
        {
            cout << "系统错误：" << SubmitXmlDocument.ErrorDesc() << endl;
            return;
        }
        TiXmlHandle SubmitXmlHandle = TiXmlHandle(&SubmitXmlDocument).FirstChild("html").FirstChild("body").Child("div", 5).Child("div", 3).FirstChild("div").Child("div", 3).Child("div", 5).FirstChild("table").FirstChild("tbody").Child("tr", 1).FirstChild().FirstChild();
    }
}
namespace UVa
{
    void Init()
    {
        cout << "现在没有设计好，暂不支持此命令" << endl;
    }
    void Login(string Username, string Password)
    {
        cout << "现在没有设计好，暂不支持此命令" << endl;
    }
    void SubmitCode(string QuestionID)
    {
        cout << "现在没有设计好，暂不支持此命令" << endl;
    }
    void GetQuestionDetail(string QuestionID)
    {
        cout << "现在没有设计好，暂不支持此命令" << endl;
    }
}
int main(int argc, char **argv)
{
    if (argc != 5 && argc != 6)
        Usage();
    if (string(argv[1]) == "Luogu")
    {
        using namespace Luogu;
        Init();
        Login(argv[2], argv[3]);
        if (string(argv[4]) == "ClockIn")
            argc == 5 ? ClockIn() : Usage();
        else if (string(argv[4]) == "GetQuestionDetail")
            argc == 6 ? GetQuestionDetail(argv[5]) : Usage();
        else if (string(argv[4]) == "SubmitCode")
            argc == 6 ? SubmitCode(argv[5]) : Usage();
        else
            Usage();
    }
    else if (string(argv[1]) == "Etiger")
    {
        using namespace Etiger;
        Init();
        Login(argv[2], argv[3]);
        if (string(argv[4]) == "ClockIn")
            argc == 5 ? ClockIn() : Usage();
        else if (string(argv[4]) == "GetQuestionDetail")
            argc == 6 ? GetQuestionDetail(argv[5]) : Usage();
        else if (string(argv[4]) == "SubmitCode")
            argc == 6 ? SubmitCode(argv[5]) : Usage();
        else
            Usage();
    }
    else if (string(argv[1]) == "UVa")
    {
        using namespace UVa;
        Init();
        Login(argv[2], argv[3]);
        if (string(argv[4]) == "GetQuestionDetail")
            argc == 6 ? GetQuestionDetail(argv[5]) : Usage();
        else if (string(argv[4]) == "SubmitCode")
            argc == 6 ? SubmitCode(argv[5]) : Usage();
        else
            Usage();
    }
    else if (string(argv[1]) == "Codeforces")
    {
        using namespace Codeforces;
        Login(argv[2], argv[3]);
        if (string(argv[4]) == "GetQuestionDetail")
            argc == 6 ? GetQuestionDetail(argv[5]) : Usage();
        else if (string(argv[4]) == "SubmitCode")
            argc == 6 ? SubmitCode(argv[5]) : Usage();
        else
            Usage();
    }
    else
        Usage();
    Clean();
    return 0;
}
