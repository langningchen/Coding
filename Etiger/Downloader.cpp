#include <bits/stdc++.h>
#include <memory.h>
#include <iconv.h>
#include <curl/curl.h>
#include "lib/configor-0.9.17/include/configor/json.hpp"
using namespace std;
using namespace configor;
string Token = "";
string UserName = "";

/**
 * @brief ANSI字符集转换为UTF-8字符集
 *
 * @param Input 输入字符串缓冲区
 * @param InputSize 输入字符串缓冲区大小
 * @param Output 输出字符串缓冲区
 * @param OutputSize 输出字符串缓冲区大小
 */
void ANSIToUTF8(const char *Input, size_t InputSize, char *Output, size_t OutputSize)
{
    iconv_t Iconv = iconv_open("UTF-8", "GBK");
    iconv(Iconv, (char **)&Input, &InputSize, &Output, &OutputSize);
    iconv_close(Iconv);
}

/**
 * @brief 从网络用GET方法下载文件
 *
 * @param URL 文件地址
 * @param FileName 要保存的文件名
 */
void GetDataToFile(string URL, string FileName)
{
    FILE *FilePointer;
    CURL *Curl;
    CURLcode Status;
    curl_slist *CurlHeader = NULL;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    Curl = curl_easy_init();
    FilePointer = fopen(FileName.c_str(), "w");
    if (FilePointer == NULL)
    {
        cout << "无法打开输出文件：" << FileName << endl;
    }
    else if (Curl)
    {
        curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYHOST, false);
        curl_easy_setopt(Curl, CURLOPT_URL, URL.c_str());
        curl_easy_setopt(Curl, CURLOPT_WRITEDATA, FilePointer);

        if (Token != "")
            CurlHeader = curl_slist_append(CurlHeader, string("token: " + Token).c_str());
        curl_easy_setopt(Curl, CURLOPT_HTTPHEADER, CurlHeader);

        Status = curl_easy_perform(Curl);
        if (Status != CURLE_OK)
        {
            cout << "在访问网址" << URL << "时发生错误，错误信息：" << curl_easy_strerror(Status) << endl;
        }
        curl_slist_free_all(CurlHeader);
        curl_easy_cleanup(Curl);
    }
    curl_global_cleanup();
    fclose(FilePointer);
}

/**
 * @brief 从网络用GET方法下载信息到字符串
 *
 * @param URL 文件地址
 * @return string 信息
 */
string GetDataToString(string URL)
{
    GetDataToFile(URL, "CurlTemp.tmp");

    string Ans = "";
    FILE *FilePointer;
    FilePointer = fopen("CurlTemp.tmp", "r");
    if (FilePointer == NULL)
    {
        cout << "无法打开输入文件：CurlTemp.tmp" << endl;
    }
    else
    {
        while (!feof(FilePointer))
        {
            Ans.push_back(fgetc(FilePointer));
        }
    }
    fclose(FilePointer);
    remove("CurlTemp.tmp");
    Ans.erase(Ans.size() - 1);
    return Ans;
}

/**
 * @brief 从网络用POST方法下载文件
 *
 * @param URL 文件地址
 * @param FileName 要保存的文件名
 * @param PostData 发送的请求数据
 */
void PostDataToFile(string URL, string FileName, json PostData)
{
    FILE *FilePointer;
    CURL *Curl;
    CURLcode Status;
    curl_slist *CurlHeader = NULL;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    Curl = curl_easy_init();
    FilePointer = fopen(FileName.c_str(), "w");
    if (FilePointer == NULL)
    {
        cout << "无法打开输出文件：" << FileName << endl;
    }
    else if (Curl)
    {
        curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYHOST, false);
        curl_easy_setopt(Curl, CURLOPT_URL, URL.c_str());
        curl_easy_setopt(Curl, CURLOPT_WRITEDATA, FilePointer);
        curl_easy_setopt(Curl, CURLOPT_POST, 1);
        if (PostData == NULL)
        {
            curl_easy_setopt(Curl, CURLOPT_POSTFIELDS, "{}");
        }
        else
        {
            char ch[255];
            memset(ch, 0, sizeof(ch));
            ANSIToUTF8(PostData.dump().c_str(), PostData.dump().size(), ch, sizeof(ch));
            curl_easy_setopt(Curl, CURLOPT_POSTFIELDS, ch);
        }

        if (Token != "")
            CurlHeader = curl_slist_append(CurlHeader, string("token: " + Token).c_str());
        CurlHeader = curl_slist_append(CurlHeader, "Content-Type: application/json;charset=utf-8");
        CurlHeader = curl_slist_append(CurlHeader, "lang: zh");
        CurlHeader = curl_slist_append(CurlHeader, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:102.0) Gecko/20100101 Firefox/102.0");
        CurlHeader = curl_slist_append(CurlHeader, "Host: www.etiger.vip");
        curl_easy_setopt(Curl, CURLOPT_HTTPHEADER, CurlHeader);

        Status = curl_easy_perform(Curl);
        if (Status != CURLE_OK)
        {
            cout << "在访问网址" << URL << "时发生错误，错误信息：" << curl_easy_strerror(Status) << endl;
        }
        curl_slist_free_all(CurlHeader);
        curl_easy_cleanup(Curl);
    }
    curl_global_cleanup();
    fclose(FilePointer);
}

/**
 * @brief 从网络用POST方法信息到字符串
 *
 * @param URL 文件地址
 * @param PostData 发送的请求数据
 * @return string 信息
 */
string PostDataToString(string URL, json PostData)
{
    PostDataToFile(URL, "CurlTemp.tmp", PostData);

    string Ans = "";
    FILE *FilePointer;
    FilePointer = fopen("CurlTemp.tmp", "r");
    if (FilePointer == NULL)
    {
        cout << "无法打开输入文件：CurlTemp.tmp" << endl;
    }
    else
    {
        while (!feof(FilePointer))
        {
            Ans.push_back(fgetc(FilePointer));
        }
    }
    fclose(FilePointer);
    remove("CurlTemp.tmp");
    Ans.erase(Ans.size() - 1);
    return Ans;
}

/**
 * @brief 登录
 *
 * @param Username 用户名
 * @param Password 密码
 */
void Login(string Username, string Password)
{
    json PostData;
    PostData["name"] = Username;
    PostData["password"] = Password;
    json Response = json::parse(PostDataToString("https://www.etiger.vip/thrall-web/user/login", PostData));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        exit(0);
    }
    UserName = Response["data"]["nickname"].as_string();
    Token = Response["data"]["ticket"].as_string();
    cout << UserName << "，登录成功！" << endl;
}

/**
 * @brief 字符串全部替换
 *
 * @param Data 字符串
 * @param Before 查找
 * @param After 替换为
 */
void StringReplaceAll(string &Data, string Before, string After)
{
    int FoundedPos = 0;
    while ((FoundedPos = Data.find(Before)) != Data.npos)
    {
        Data.replace(FoundedPos, Before.size(), After);
    }
}

/**
 * @brief 获得问题名称
 *
 * @param QuestionID 问题ID
 * @return string 名称
 */
string GetQuestionName(short QuestionID)
{
    json Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/question/getById?id=" + to_string(QuestionID)));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        return "";
    }
    return Response["data"]["title"];
}

/**
 * @brief 获得一份代码
 *
 * @param QuestionID 问题ID
 * @param FileName 文件名模板
 */
void GetCode(short QuestionID, string FileName)
{
    json Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/question/getUserCodeByQuestionId?questionId=" + to_string(QuestionID)));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        return;
    }
    StringReplaceAll(FileName, "{ID}", to_string(QuestionID));
    StringReplaceAll(FileName, "{4ID}", string(string((QuestionID < 1000 ? "0" : "")) + (QuestionID < 100 ? "0" : "") + (QuestionID < 10 ? "0" : "") + to_string(QuestionID)));
    StringReplaceAll(FileName, "{Name}", GetQuestionName(QuestionID));
    FILE *FilePointer;
    FilePointer = fopen(string(FileName + ".cpp").c_str(), "w");
    fprintf(FilePointer, "%s", Response["data"]["code"].as_string().c_str());
    fclose(FilePointer);
}

/**
 * @brief 获得所有代码
 *
 * @param Type 代码类型
 * @param FileName 文件名模板
 *
 * @deprecated 代码类型只能是passQuestionIds或unpassQuestionIds
 * 文件名模板可以包含{ID}为题目编号，{4ID}为用0补全的四位数题目编号，{Name}为题目名称，不需要后缀名
 */
void GetAllCode(string Type, string FileName)
{
    json Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/report/userSubmitStatic"));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        exit(0);
    }
    for (detail::iterator<json> Iterator = Response["data"][Type].begin(); Iterator != Response["data"][Type].end(); Iterator++)
    {
        cout << "下载第" << Iterator.value() << "题代码..." << endl;
        GetCode(Iterator.value(), FileName);
    }
}

int main()
{
    cout << "登录..." << endl;
    Login("18117121393", "LangNing0117");
    cout << "获得题目列表..." << endl;
    GetAllCode("passQuestionIds", "{ID}. {Name}");
    return 0;
}
