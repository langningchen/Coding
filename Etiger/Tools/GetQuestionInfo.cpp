#include <bits/stdc++.h>
#include <memory.h>
#include <curl/curl.h>
#include "lib/configor-0.9.17/include/configor/json.hpp"
using namespace std;
using namespace configor;
string Token = "";

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
void PostDataToFile(string URL, string FileName, string PostData)
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
        curl_easy_setopt(Curl, CURLOPT_POSTFIELDS, PostData.c_str());

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
string PostDataToString(string URL, string PostData)
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

string EraseHTMLElement(string Ans)
{
    int HTMLStartIndex = 0;
    for (int i = 0; i < Ans.size(); i++)
    {
        if (Ans[i] == '<')
        {
            HTMLStartIndex = i;
        }
        if (Ans[i] == '>')
        {
            Ans.erase(HTMLStartIndex, i - HTMLStartIndex + 1);
            i = HTMLStartIndex;
        }
    }
    return Ans;
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        cout << "使用方法：UploadOne <用户名> <密码> <题目编号>" << endl;
        return 0;
    }

    string Username = argv[1];
    string Password = argv[2];
    json PostData;
    PostData["name"] = Username;
    PostData["password"] = Password;
    json Response = json::parse(PostDataToString("https://www.etiger.vip/thrall-web/user/login", "{\"name\":\"" + Username +
                                                                                                     "\",\"password\":\"" + Password +
                                                                                                     "\"}"));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        return 0;
    }
    Token = Response["data"]["ticket"].as_string();

    string QuestionID = argv[3];
    Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/question/getById?id=" + QuestionID));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        return 0;
    }
    FILE *FilePointer = fopen(string("/workspaces/Coding/Etiger/" + QuestionID + ".txt").c_str(), "w");
    fprintf(FilePointer, "%s. %s\n", QuestionID.c_str(), Response["data"]["title"].as_string().c_str());
    fprintf(FilePointer, "\n");
    fprintf(FilePointer, "题目描述\n");
    fprintf(FilePointer, "%s\n", EraseHTMLElement(Response["data"]["content"].as_string()).c_str());
    fprintf(FilePointer, "\n");
    fprintf(FilePointer, "输入输出格式\n");
    fprintf(FilePointer, "输入格式\n");
    fprintf(FilePointer, "%s\n", Response["data"]["inputFormat"].as_string().c_str());
    fprintf(FilePointer, "输出格式\n");
    fprintf(FilePointer, "%s\n", Response["data"]["outputFormat"].as_string().c_str());
    fprintf(FilePointer, "输入输出文件\n");
    fprintf(FilePointer, "%s\n", Response["data"]["ioName"].as_string().c_str());
    fprintf(FilePointer, "\n");
    fprintf(FilePointer, "输入输出样例\n");
    int Counter = 1;
    string InputSample = Response["data"]["inputSample"].as_string();
    string OutputSample = Response["data"]["outputSample"].as_string();
    while (InputSample.find(";") != InputSample.npos && OutputSample.find(";") != OutputSample.npos)
    {
        fprintf(FilePointer, "输入样例#%d：%s\n", Counter, InputSample.substr(0, InputSample.find(";")).c_str());
        InputSample = InputSample.erase(0, InputSample.find(";") + 1);
        fprintf(FilePointer, "输出样例#%d：%s\n", Counter, OutputSample.substr(0, OutputSample.find(";")).c_str());
        OutputSample = OutputSample.erase(0, OutputSample.find(";") + 1);
        fprintf(FilePointer, "\n");
    }
    fprintf(FilePointer, "\n");
    fprintf(FilePointer, "说明\n");
    fprintf(FilePointer, "%s\n", Response["data"]["description"].as_string().c_str());
    fclose(FilePointer);
    return 0;
}
