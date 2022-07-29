#include <bits/stdc++.h>
#include <memory.h>
#include <iconv.h>
#include <dirent.h>
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

int main()
{
    string Username = "18117121393";
    string Password = " LangNing0117";

    cout << "登录..." << endl;
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

    cout << "获得题目列表..." << endl;
    set<int> FileList;
    DIR *DirPointer = opendir("../");
    dirent *DirentPointer = NULL;
    while ((DirentPointer = readdir(DirPointer)) != NULL)
        if (DirentPointer->d_type == DT_REG)
            FileList.insert(atoi(DirentPointer->d_name));
    closedir(DirPointer);

    json Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/report/userSubmitStatic"));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        exit(0);
    }
    for (detail::iterator<json> Iterator = Response["data"]["passQuestionIds"].begin(); Iterator != Response["data"]["passQuestionIds"].end(); Iterator++)
        if (FileList.find(Iterator.value()) == FileList.end())
        {
            cout << Iterator.value() << endl;
            json Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/question/getUserCodeByQuestionId?questionId=" + to_string(Iterator.value().as_integer())));
            if (Response["code"] != 200)
            {
                cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
                continue;
            }
            string FileName = string(Iterator.value() < 1000 ? "0" : "") +
                              string(Iterator.value() < 100 ? "0" : "") +
                              string(Iterator.value() < 10 ? "0" : "") +
                              string(Iterator.value().as_string());
            FILE *FilePointer;
            FilePointer = fopen(string(FileName + ".cpp").c_str(), "w");
            fprintf(FilePointer, "%s", Response["data"]["code"].as_string().c_str());
            fclose(FilePointer);
        }
    return 0;
}
