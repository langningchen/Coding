#include <iostream>
#include <unistd.h>
#include "../lib/Curl.cpp"
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
    用户名
        登录用户名
    密码
        登录密码
    命令
        ClockIn
            签到
        GetQuestionDetail
            获取题目信息
        SubmitCode
            提交代码
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
            若命令为ClockIn
                无输出
            若命令为GetQuestionDetail
                打开文件"/workspaces/Coding/Luogu/<题目编号>.md"
                写入题目数据
                关闭文件
            若命令为SubmitCode
                读取文件"/workspaces/Coding/Luogu/<题目编号>.cpp"
                提交
                输出评测结果
        若服务器名称为Etiger
            若命令为ClockIn
                无输出
            若命令为GetQuestionDetail
                打开文件"/workspaces/Coding/Etiger/<题目编号>.md"
                写入题目数据
                关闭文件
            若命令为SubmitCode
                读取文件"/workspaces/Coding/Etiger/<题目编号>.cpp"
                提交
                输出评测结果
        若服务器名称为UVa
            若命令为ClockIn
                不支持此命令
            若命令为GetQuestionDetail
                打开文件"/workspaces/Coding/UVa/<题目编号>.pdf"
                写入题目数据
                关闭文件
            若命令为SubmitCode
                现在没有设计好，暂不支持此命令
                // 读取文件"/workspaces/Coding/UVa/<题目编号>.cpp"
                // 提交
                // 输出评测结果
    若程序运行失败
        输出错误信息或返回非0
)" << endl;
    Clean();
    exit(0);
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
        string LoginPageData = GetDataFromFileToString();
        string TokenStartString = "<meta name=\"csrf-token\" content=\"";
        unsigned int TokenStartPos = LoginPageData.find(TokenStartString);
        if (TokenStartPos == LoginPageData.npos)
        {
            cout << "无法找到登录密钥开始位置。" << endl;
            return;
        }
        TokenStartPos += TokenStartString.size();
        unsigned int TokenEndPos = TokenStartPos + 1;
        while (TokenEndPos < LoginPageData.size() && LoginPageData[TokenEndPos] != '"')
            TokenEndPos++;
        if (TokenEndPos == LoginPageData.size())
        {
            cout << "无法找到登录密钥结束位置。" << endl;
            return;
        }
        string Token = LoginPageData.substr(TokenStartPos, TokenEndPos - TokenStartPos);
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
                    cout << "登录失败，错误码：" << LoginInfo["status"].as_integer() << "，错误信息：" << LoginInfo["currentData"]["errorMessage"].as_string() << endl;
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
        string LoginPageData = GetDataFromFileToString();
        string TokenStartString = "<meta name=\"csrf-token\" content=\"";
        unsigned int TokenStartPos = LoginPageData.find(TokenStartString);
        if (TokenStartPos == LoginPageData.npos)
        {
            cout << "无法找到打卡密钥开始位置。" << endl;
            return;
        }
        TokenStartPos += TokenStartString.size();
        unsigned int TokenEndPos = TokenStartPos + 1;
        while (TokenEndPos < LoginPageData.size() && LoginPageData[TokenEndPos] != '"')
            TokenEndPos++;
        if (TokenEndPos == LoginPageData.size())
        {
            cout << "无法找到打卡密钥结束位置。" << endl;
            return;
        }
        string Token = LoginPageData.substr(TokenStartPos, TokenEndPos - TokenStartPos);
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
        string LoginPageData = GetDataFromFileToString();
        string TokenStartString = "<meta name=\"csrf-token\" content=\"";
        unsigned int TokenStartPos = LoginPageData.find(TokenStartString);
        if (TokenStartPos == LoginPageData.npos)
        {
            cout << "无法找到提交密钥起始位置。" << endl;
            return;
        }
        TokenStartPos += TokenStartString.size();
        unsigned int TokenEndPos = TokenStartPos + 1;
        while (TokenEndPos < LoginPageData.size() && LoginPageData[TokenEndPos] != '"')
            TokenEndPos++;
        if (TokenEndPos == LoginPageData.size())
        {
            cout << "无法找到提交密钥结束位置。" << endl;
            return;
        }
        string Token = LoginPageData.substr(TokenStartPos, TokenEndPos - TokenStartPos);
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
        DifficultyName[5] = make_pair("提高+/省选-", "plu20m");
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
            OutputFileStream << "输入 #" << Counter << endl
                             << "```" << endl
                             << FixString(InputSample.substr(0, InputSample.find(";"))) << endl
                             << "```" << endl
                             << "输出 #" << Counter << endl
                             << "```" << endl
                             << FixString(OutputSample.substr(0, OutputSample.find(";"))) << endl
                             << "```" << endl;
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
    }
    void SubmitCode(string QuestionID)
    {
        string Code = GetDataFromFileToString(string("../Etiger/" + QuestionID + ".cpp"));
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
    }
    void Temp()
    {
        for (int i = 3000; i < 4000; i++)
        {
            string QuestionID = to_string(i);
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
                continue;
            }
            cout << i << " " << FixString(QuestionInfo["data"]["ioName"].as_string()) << endl;
        }
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
    int BufferSize = 1024;
    char *Buffer = new char[BufferSize];
    readlink("/proc/self/exe", Buffer, BufferSize);
    CurrentDir = Buffer;
    delete Buffer;
    CurrentDir.erase(CurrentDir.find_last_of("/") + 1, CurrentDir.npos);
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
        else if (string(argv[4]) == "Temp")
            argc == 5 ? Temp() : Usage();
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
    else
        Usage();
    Clean();
    return 0;
}
