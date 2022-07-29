#include <bits/stdc++.h>
#include <memory.h>
#include <curl/curl.h>
#include "lib/configor-0.9.17/include/configor/json.hpp"
using namespace std;
using namespace configor;

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

        Status = curl_easy_perform(Curl);
        if (Status != CURLE_OK)
        {
            cout << "在访问网址" << URL << "时发生错误，错误信息：" << curl_easy_strerror(Status) << endl;
        }
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

int HexToDec(char Data)
{
    if (Data >= '0' && Data <= '9')
        return Data - '0';
    else if (Data >= 'a' && Data <= 'f')
        return Data - 'a' + 10;
    else if (Data >= 'A' && Data <= 'F')
        return Data - 'A' + 10;
    return 0;
}

string URLDecode(string Input)
{
    string Output = "";
    for (int i = 0; i < Input.size(); i++)
        if (Input[i] != '%')
            Output.push_back(Input[i]);
        else
        {
            Output.push_back(HexToDec(Input[i + 1]) * 16 + HexToDec(Input[i + 2]));
            i += 2;
        }
    return Output;
}

string WstringToString(wstring Input)
{
    char *OutputTemp = new char[Input.size() * sizeof(wchar_t)];
    wcstombs(OutputTemp, Input.c_str(), Input.size() * sizeof(wchar_t));
    string Output = OutputTemp;
    delete OutputTemp;
    return Output;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "使用方法：GetQuestionInfo <题目编号>" << endl;
        return 0;
    }
    string HTMLData = GetDataToString(string("https://www.luogu.com.cn/problem/") + string(argv[1]));
    string JSONDataStartString = "window._feInjection = JSON.parse(decodeURIComponent(\"";
    string JSONDataEndString = "\"));window._feConfigVersion=";
    int JSONDataStartPos = HTMLData.find(JSONDataStartString);
    if (JSONDataStartPos == HTMLData.npos)
    {
        cout << "无法找到JSON数据起始位置";
        return 0;
    }
    JSONDataStartPos += JSONDataStartString.size();
    int JSONDataEndPos = HTMLData.find(JSONDataEndString);
    if (JSONDataEndPos == HTMLData.npos)
    {
        cout << "无法找到JSON数据结束位置";
        return 0;
    }
    string JSONRawData = HTMLData.substr(JSONDataStartPos, JSONDataEndPos - JSONDataStartPos);
    json JSONData = json::parse(URLDecode(JSONRawData));
    ofstream OutputFileStream("temp.md");
    OutputFileStream << JSONData["currentData"]["problem"]["background"].as_string() << endl
                     << endl;
    OutputFileStream << JSONData["currentData"]["problem"]["description"].as_string() << endl
                     << endl;
    OutputFileStream.close();
    return 0;
}