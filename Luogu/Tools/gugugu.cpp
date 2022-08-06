#include <iostream>
#include <fstream>
#include <unistd.h>
#include <curl/curl.h>
#include "lib/configor-0.9.17/include/configor/json.hpp"
using namespace std;
using namespace configor;
map<int, string> LanguageName, LanguageMarkdownName;
map<int, pair<string, string>> DifficultyName, TagName, RecordName;
map<string, string> TypeName, ColorList;
void GetDataToFile(string URL, string HeaderFileName = "Header.tmp", string BodyFileName = "Body.tmp", bool IsPost = false, string PostData = "", curl_slist *HeaderList = NULL, int *HTTPResponseCode = NULL)
{
    FILE *HeaderFilePointer = fopen(HeaderFileName.c_str(), "w");
    FILE *BodyFilePointer = fopen(BodyFileName.c_str(), "w");
    CURLcode CurlCode = curl_global_init(CURL_GLOBAL_ALL);
    if (CurlCode != 0)
    {
        cout << "libcurl初始化失败，错误代码：" << CurlCode << "。" << endl;
        fclose(BodyFilePointer);
        fclose(HeaderFilePointer);
        return;
    }
    CURL *Curl = curl_easy_init();
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYSTATUS, false);
    curl_easy_setopt(Curl, CURLOPT_HEADERDATA, HeaderFilePointer);
    curl_easy_setopt(Curl, CURLOPT_WRITEDATA, BodyFilePointer);
    curl_easy_setopt(Curl, CURLOPT_COOKIEFILE, "Cookies.tmp");
    curl_easy_setopt(Curl, CURLOPT_COOKIEJAR, "Cookies.tmp");
    curl_easy_setopt(Curl, CURLOPT_URL, URL.c_str());
    if (IsPost)
    {
        HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json");
        curl_easy_setopt(Curl, CURLOPT_POST, true);
        curl_easy_setopt(Curl, CURLOPT_POSTFIELDS, PostData.c_str());
    }
    curl_easy_setopt(Curl, CURLOPT_HTTPHEADER, HeaderList);
    CurlCode = curl_easy_perform(Curl);
    if (CurlCode != 0)
        cout << "请求发送失败，错误代码：" << CurlCode << "。" << endl;
    if (HTTPResponseCode != NULL)
        curl_easy_getinfo(Curl, CURLINFO_RESPONSE_CODE, HTTPResponseCode);
    curl_easy_cleanup(Curl);
    fclose(BodyFilePointer);
    fclose(HeaderFilePointer);
}
string GetDataFromFileToString(string FileName = "Body.tmp")
{
    string Data = "";
    FILE *BodyFilePointer = fopen(FileName.c_str(), "r");
    while (!feof(BodyFilePointer))
        Data.push_back(fgetc(BodyFilePointer));
    fclose(BodyFilePointer);
    while (Data.size() > 0 && (Data[Data.size() - 1] == 0x00 || Data[Data.size() - 1] == 0xFF || Data[Data.size() - 1] == -1 || Data[Data.size() - 1] == '\r' || Data[Data.size() - 1] == '\n'))
        Data.erase(Data.size() - 1);
    return Data;
}
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
    int TokenStartPos = LoginPageData.find(TokenStartString);
    if (TokenStartPos == LoginPageData.npos)
    {
        cout << "无法找到登录密钥开始位置。" << endl;
        return;
    }
    TokenStartPos += TokenStartString.size();
    int TokenEndPos = TokenStartPos + 1;
    while (TokenEndPos < LoginPageData.size() && LoginPageData[TokenEndPos] != '"')
        TokenEndPos++;
    if (TokenEndPos == LoginPageData.size())
    {
        cout << "无法找到登录密钥结束位置。" << endl;
        return;
    }
    string Token = LoginPageData.substr(TokenStartPos, TokenEndPos - TokenStartPos);
    GetDataToFile("https://www.luogu.com.cn/api/verify/captcha", "Header.tmp", "Captcha.jpeg");
    string Captcha = "";
    while (Captcha.size() != 4)
    {
        cout << "请打开文件\"Captcha.jpeg\"并输入4位验证码：";
        cin >> Captcha;
    }
    json LoginInfo;
    LoginInfo["username"] = Username;
    LoginInfo["password"] = Password;
    LoginInfo["captcha"] = Captcha;
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, string("X-CSRF-TOKEN: " + Token).c_str());
    HeaderList = curl_slist_append(HeaderList, string("Content-Length: " + to_string(LoginInfo.dump().size())).c_str());
    HeaderList = curl_slist_append(HeaderList, "Host: www.luogu.com.cn");
    HeaderList = curl_slist_append(HeaderList, "Referer: https://www.luogu.com.cn/auth/login");
    HeaderList = curl_slist_append(HeaderList, "Origin: https://www.luogu.com.cn");
    HeaderList = curl_slist_append(HeaderList, "X-Requested-With: XMLHttpRequest");
    HeaderList = curl_slist_append(HeaderList, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:103.0) Gecko/20100101 Firefox/103.0");
    GetDataToFile("https://www.luogu.com.cn/api/auth/userPassLogin", "Header.tmp", "Body.tmp", true, LoginInfo.dump(), HeaderList);
    json ResponseInfo = json::parse(GetDataFromFileToString());
    if (ResponseInfo["status"].dump() != "null")
        cout << "登录失败，错误码" << ResponseInfo["status"].as_integer() << "，错误信息" << ResponseInfo["errorMessage"].as_string() << endl;
}
void SubmitCode(string QuestionID)
{
    string Code = "";
    FILE *FilePointer = fopen(string("../" + QuestionID + ".cpp").c_str(), "r");
    if (FilePointer == NULL)
    {
        cout << "无法打开输入文件。" << endl;
        return;
    }
    while (!feof(FilePointer))
        Code.push_back(fgetc(FilePointer));
    fclose(FilePointer);
    while (Code.size() >= 0 && Code[Code.size() - 1] == -1)
        Code.erase(Code.size() - 1, 1);
    GetDataToFile("https://www.luogu.com.cn/problem/" + QuestionID);
    string LoginPageData = GetDataFromFileToString();
    string TokenStartString = "<meta name=\"csrf-token\" content=\"";
    int TokenStartPos = LoginPageData.find(TokenStartString);
    if (TokenStartPos == LoginPageData.npos)
    {
        cout << "无法找到提交密钥起始位置。" << endl;
        return;
    }
    TokenStartPos += TokenStartString.size();
    int TokenEndPos = TokenStartPos + 1;
    while (TokenEndPos < LoginPageData.size() && LoginPageData[TokenEndPos] != '"')
        TokenEndPos++;
    if (TokenEndPos == LoginPageData.size())
    {
        cout << "无法找到提交密钥结束位置。" << endl;
        return;
    }
    string Token = LoginPageData.substr(TokenStartPos, TokenEndPos - TokenStartPos);
    json SubmitInfo;
    SubmitInfo["code"] = Code;
    SubmitInfo["enableO2"] = 1;
    SubmitInfo["lang"] = 0;
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, string("X-CSRF-TOKEN: " + Token).c_str());
    HeaderList = curl_slist_append(HeaderList, string("Content-Length: " + to_string(SubmitInfo.dump().size())).c_str());
    HeaderList = curl_slist_append(HeaderList, "Host: www.luogu.com.cn");
    HeaderList = curl_slist_append(HeaderList, string("Referer: https://www.luogu.com.cn/problem/" + QuestionID).c_str());
    HeaderList = curl_slist_append(HeaderList, "Origin: https://www.luogu.com.cn");
    HeaderList = curl_slist_append(HeaderList, "X-Requested-With: XMLHttpRequest");
    HeaderList = curl_slist_append(HeaderList, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:103.0) Gecko/20100101 Firefox/103.0");
    GetDataToFile("https://www.luogu.com.cn/fe/api/problem/submit/" + QuestionID, "Header.tmp", "Body.tmp", true, SubmitInfo.dump(), HeaderList);
    json ResponseInfo = json::parse(GetDataFromFileToString());
    if (ResponseInfo["status"].dump() != "null")
    {
        cout << "提交失败，错误码" << ResponseInfo["status"].as_integer() << "，错误信息" << ResponseInfo["errorMessage"].as_string() << endl;
        return;
    }
    int RecordID = ResponseInfo["rid"].as_integer();
    json RecordData;
    while (!RecordData["currentData"]["record"]["status"].is_number() || RecordData["currentData"]["record"]["status"].as_integer() < 2)
    {
        GetDataToFile("https://www.luogu.com.cn/record/" + to_string(RecordID) + "?_contentOnly=1");
        RecordData = json::parse(GetDataFromFileToString());
    }
    time_t TimeStamp = RecordData["currentData"]["record"]["submitTime"].as_integer();
    tm *FormatedTime = localtime(&TimeStamp);
    if (!RecordData["currentData"]["record"]["detail"]["compileResult"]["success"].as_bool())
        cout << "编译错误：" << endl
             << RecordData["currentData"]["record"]["detail"]["compileResult"]["message"].as_string() << endl;
    else
    {
        cout << RecordData["currentData"]["record"]["score"].as_integer() << "pts" << endl;
        for (json::iterator jit = RecordData["currentData"]["record"]["detail"]["judgeResult"]["subtasks"].begin(); jit != RecordData["currentData"]["record"]["detail"]["judgeResult"]["subtasks"].end(); jit++)
        {
            cout << "#" << jit.value()["id"] << endl;
            for (json::iterator jit2 = RecordData["currentData"]["record"]["detail"]["judgeResult"]["subtasks"][jit.value()["id"].as_integer()]["testCases"].begin(); jit2 != RecordData["currentData"]["record"]["detail"]["judgeResult"]["subtasks"][jit.value()["id"].as_integer()]["testCases"].end(); jit2++)
                cout << "    #" << jit2.value()["id"].as_integer() << " " << jit2.value()["score"].as_integer() << "pts " << RecordName[jit2.value()["status"].as_integer()].second << " " << jit2.value()["time"].as_integer() << "ms " << jit2.value()["memory"].as_integer() << "KB" << endl;
        }
        cout << RecordData["currentData"]["record"]["score"].as_integer() << "pts" << endl;
    }
}
string FixString(string Data)
{
    return (Data[Data.size() - 1] == '\n' ? FixString(Data.erase(Data.size() - 1, 1)) : Data);
}
string StringReplaceAll(string Data, string Before, string After)
{
    int FoundedPos;
    while ((FoundedPos = Data.find(Before)) != Data.npos)
        Data.replace(FoundedPos, Before.size(), After);
    return Data;
}
void GetQuestionDetail(string QuestionID)
{
    GetDataToFile("https://www.luogu.com.cn/problem/" + QuestionID + "?_contentOnly=1");
    json JSONData = json::parse(GetDataFromFileToString());
    if (JSONData["code"].as_integer() != 200)
    {
        cout << "获取题目信息失败，错误码" << JSONData["code"].as_integer() << "，错误信息" << JSONData["currentData"]["errorMessage"].as_string() << endl;
        return;
    }
    ofstream OutputFileStream(string("../" + QuestionID + ".md").c_str());
    if (OutputFileStream.bad())
    {
        cout << "无法打开输出文件。" << endl;
        return;
    }
    OutputFileStream << "# " << QuestionID << " " << JSONData["currentData"]["problem"]["title"] << endl;
    if (JSONData["currentData"]["problem"]["accepted"].as_bool())
        OutputFileStream << "***您已经通过此题！***" << endl
                         << endl;
    else if (JSONData["currentData"]["problem"]["submitted"].as_bool())
        OutputFileStream << "***您已经提交过此题但未通过！***" << endl
                         << endl;

    if (JSONData["currentData"]["problem"]["background"].as_string() != "")
        OutputFileStream << "## 题目背景" << endl
                         << endl
                         << FixString(JSONData["currentData"]["problem"]["background"]) << endl
                         << endl;

    OutputFileStream << "## 题目描述" << endl
                     << endl
                     << FixString(JSONData["currentData"]["problem"]["description"]) << endl
                     << endl
                     << "## 输入格式" << endl
                     << endl
                     << FixString(JSONData["currentData"]["problem"]["inputFormat"]) << endl
                     << endl
                     << "## 输出格式" << endl
                     << endl
                     << FixString(JSONData["currentData"]["problem"]["outputFormat"]) << endl
                     << endl
                     << "## 输入输出样例" << endl
                     << endl;

    if (JSONData["currentData"]["problem"]["samples"].size() == 0)
        OutputFileStream << "无" << endl
                         << endl;
    else
    {
        int Counter = 1;
        for (json::iterator cit = JSONData["currentData"]["problem"]["samples"].begin(); cit != JSONData["currentData"]["problem"]["samples"].end(); cit++)
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
    OutputFileStream << "## 提示" << endl
                     << endl
                     << FixString(JSONData["currentData"]["problem"]["hint"]) << endl
                     << endl;
    OutputFileStream << "## 时空限制" << endl;
    OutputFileStream << "|测试点编号|时间限制|空间限制|" << endl
                     << "|:---:|:---:|:---:|" << endl;
    for (int Counter = 0; Counter < JSONData["currentData"]["problem"]["limits"]["memory"].size(); Counter++)
    {
        OutputFileStream << "|$" << (Counter + 1) << "$"
                         << "|$" << (JSONData["currentData"]["problem"]["limits"]["memory"][Counter].as_integer() / 1024.0) << "MB$"
                         << "|$" << (JSONData["currentData"]["problem"]["limits"]["time"][Counter].as_integer() / 1000) << "s$"
                         << "|" << endl;
    }
    OutputFileStream << endl
                     << "## 最后一次提交代码" << endl
                     << endl
                     << "```" << LanguageMarkdownName[JSONData["currentData"]["lastLanguage"].as_integer()] << endl
                     << FixString(JSONData["currentData"]["lastCode"].as_string()) << endl
                     << "```" << endl
                     << endl
                     << "## 其他数据" << endl
                     << endl;
    string Tags = "";
    for (json::iterator cit = JSONData["currentData"]["problem"]["tags"].begin(); cit != JSONData["currentData"]["problem"]["tags"].end(); cit++)
        Tags += "<span style=\"display: inline-block; margin-right: 5px; border-radius: 2px; color: white; padding: 0px 8px; background-color: #" + ColorList[TagName[cit.value().as_integer()].second] + "\">" + TagName[cit.value().as_integer()].first + "</span>";
    OutputFileStream << "|项目|值|" << endl
                     << "|:---:|:---:|" << endl
                     << "|难度|<span style=\"font-weight: bold; color: #" << ColorList[DifficultyName[JSONData["currentData"]["problem"]["difficulty"].as_integer()].second] << "\">" << DifficultyName[JSONData["currentData"]["problem"]["difficulty"].as_integer()].first << "</span>|" << endl
                     << "|标签|" << Tags << "|" << endl
                     << "|提交人数|$" << JSONData["currentData"]["problem"]["totalSubmit"] << "$|" << endl
                     << "|通过人数|$" << JSONData["currentData"]["problem"]["totalAccepted"] << "$|" << endl
                     << "|通过率|$" << (JSONData["currentData"]["problem"]["totalAccepted"].as_integer() * 100.0 / JSONData["currentData"]["problem"]["totalSubmit"].as_integer()) << "%$|" << endl
                     << "|来源|`" << TypeName[JSONData["currentData"]["problem"]["type"].as_string()] << "`|" << endl
                     << "|最后一次提交语言|`" << LanguageName[JSONData["currentData"]["lastLanguage"].as_integer()] << "`|" << endl
                     << endl;
    OutputFileStream.close();
}
void ClockIn()
{
    GetDataToFile("https://www.luogu.com.cn/");
    string LoginPageData = GetDataFromFileToString();
    string TokenStartString = "<meta name=\"csrf-token\" content=\"";
    int TokenStartPos = LoginPageData.find(TokenStartString);
    if (TokenStartPos == LoginPageData.npos)
    {
        cout << "无法找到打卡密钥开始位置。" << endl;
        return;
    }
    TokenStartPos += TokenStartString.size();
    int TokenEndPos = TokenStartPos + 1;
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
    HeaderList = curl_slist_append(HeaderList, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:103.0) Gecko/20100101 Firefox/103.0");
    GetDataToFile("https://www.luogu.com.cn/index/ajax_punch", "Header.tmp", "Body.tmp", true, "", HeaderList);
}
int main(int argc, char **argv)
{
    Init();
    Login("langningc2009", "1!2@3#qQwWeE");
    ClockIn();
    // GetQuestionDetail("P1000");
    SubmitCode("P1002");
    remove("Captcha.jpeg");
    remove("Body.tmp");
    remove("Header.tmp");
    return 0;
}
