#include <iostream>
#include <memory.h>
#include <unistd.h>
#include <thread>
#include <curl/curl.h>
#include <ncurses.h>
#include "lib/configor-0.9.17/include/configor/json.hpp"
using namespace std;
using namespace configor;

string Token = "";
string LoadingList = "⡇⠏⠛⠹⢸⣰⣤⣆";
json Response;

/**
 * @brief 从网络用POST方法信息到字符串
 *
 * @param URL 文件地址
 * @param PostData 发送的请求数据
 * @return string 信息
 */
string PostDataToString(string URL, string PostData)
{
    FILE *FilePointer;
    CURL *Curl;
    CURLcode Status;
    curl_slist *CurlHeader = NULL;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    Curl = curl_easy_init();
    FilePointer = fopen("CurlTemp.tmp", "w");
    if (FilePointer == NULL)
    {
        cout << "无法打开输出文件："
             << "CurlTemp.tmp" << endl;
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

    string Ans = "";
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
 * @brief 字符串全部替换
 *
 * @param Data 字符串
 * @param Before 查找
 * @param After 替换为
 */
void StringReplaceAll(string &Data, string Before, string After)
{
    for (int i = 0; i < Data.size() - Before.size(); i++)
    {
        if (Data.substr(i, Before.size()) == Before)
        {
            Data.replace(i, Before.size(), After);
            i += Before.size();
        }
    }
}

void Output()
{
    while (1)
    {
        string s;
        for (int i = 0; i < 24; i += 3)
        {
            cout << "正在等待太戈编程返回结果...... " << LoadingList[i] << LoadingList[i + 1] << LoadingList[i + 2] << " \r";
            fflush(stdout);
            usleep(100000);
            if (Response.as_string() != "")
                return;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        cout << "使用方法：UploadOne <用户名> <密码> <文件名>" << endl
             << "文件命名方式：四位数题号+.cpp" << endl
             << "如0001.cpp" << endl
             << endl
             << "注意！代码文件内不能包含任何非美国信息交换标准代码（ASCII）字符！" << endl;
        return 0;
    }

    string Username = argv[1];
    string Password = argv[2];
    json PostData;
    PostData["name"] = Username;
    PostData["password"] = Password;
    json LoginResponse = json::parse(PostDataToString("https://www.etiger.vip/thrall-web/user/login", "{\"name\":\"" + Username +
                                                                                                          "\",\"password\":\"" + Password +
                                                                                                          "\"}"));
    if (LoginResponse["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << LoginResponse["msg"] << endl;
        return 0;
    }
    Token = LoginResponse["data"]["ticket"].as_string();

    FILE *FilePointer;
    string FileName = argv[3];
    string QuestionID = FileName.substr(FileName.size() - 8, 4);
    FilePointer = fopen(FileName.c_str(), "r");
    if (FilePointer == NULL)
    {
        cout << "无法打开代码" << FileName << errno << endl;
        return 0;
    }
    string Code = "";
    while (!feof(FilePointer))
        Code.push_back(fgetc(FilePointer));
    fclose(FilePointer);
    while (Code[Code.size() - 1] == '\n' || Code[Code.size() - 1] == '\r' || Code[Code.size() - 1] == -1)
        Code.erase(Code.size() - 1);
    StringReplaceAll(Code, "\\", "\\\\");
    StringReplaceAll(Code, "\r", "\\r");
    StringReplaceAll(Code, "\n", "\\n");
    StringReplaceAll(Code, "\t", "\\t");
    StringReplaceAll(Code, "\"", "\\\"");

    cout << "提交第" << QuestionID << "题..." << endl;
    thread OutputThread(Output);
    Response = json::parse(PostDataToString("https://www.etiger.vip/thrall-web/saveSubmit", "{\"comment\":\"\",\"lang\":\"CPP\",\"submitType\":0,\"questionId\":" + QuestionID +
                                                                                                ",\"src\":\"" + Code +
                                                                                                "\"}"));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << "        " << endl;
        return 0;
    }
    cout << "得分：" << Response["data"]["grade"] << "                                " << endl
         << endl;
    int Counter = 0;
    for (detail::iterator<json> Iterator = Response["data"]["result"].begin(); Iterator != Response["data"]["result"].end(); Iterator++)
    {
        cout << "测试点" << (Counter++) << "：" << Iterator.value()["type"].as_string() << " " << Iterator.value()["timeUsed"] << "ms " << Iterator.value()["memUsed"] << "B" << endl;
        if (Iterator.value()["input"].as_string() != "")
        {
            cout << "输入：" << Iterator.value()["input"].as_string() << endl
                 << "标准输出：" << Iterator.value()["output"].as_string() << endl
                 << "我的输出：" << Iterator.value()["myOutput"].as_string() << endl;
        }
    }
    cout << endl
         << "得分：" << Response["data"]["grade"] << endl
         << endl;
    return 0;
}
