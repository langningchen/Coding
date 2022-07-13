#include <bits/stdc++.h>
#include <set>
#include <unistd.h>
#include <memory.h>
#include <iconv.h>
#include <curl/curl.h>
#include <sys/types.h>
#include <dirent.h>
#include "lib/configor-0.9.17/include/configor/json.hpp"
// #define __DEBUG__
using namespace std;
using namespace configor;

bool LoadEnd = false;
string Token = "";
string UserName = "";
vector<string> NotACQuestins;

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
    json Response = json::parse(PostDataToString("https://www.etiger.vip/thrall-web/user/login", PostData.dump()));
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
    for (int i = 0; i < Data.size() - Before.size(); i++)
    {
        if (Data.substr(i, Before.size()) == Before)
        {
            Data.replace(i, Before.size(), After);
            i += Before.size();
        }
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
    if (Response["code"] != 200 && Response["msg"] != "题目未开放")
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        return "";
    }
    return Response["data"]["title"];
}

/**
 * @brief 显示加载画面
 *
 */
void Loading()
{
    string LoadingList = "⡇⠏⠛⠹⢸⣰⣤⣆";
    while (1)
    {
        string s;
        for (int i = 0; i < 24; i += 3)
        {
            cout << "正在等待太戈编程返回结果...... " << LoadingList[i] << LoadingList[i + 1] << LoadingList[i + 2] << " \r";
            fflush(stdout);
            usleep(100000);
            if (LoadEnd)
                return;
        }
    }
}

json GetCustomIOs(short QuestionID)
{
    json Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/question/getUserCodeByQuestionId?questionId=" + to_string(QuestionID)));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        exit(0);
    }
    return Response;
}

/**
 * @brief 提交一份代码
 *
 * @param QuestionID 问题ID
 * @param Code 代码
 */
void SubmitCode(short QuestionID, string Code)
{
    StringReplaceAll(Code, "\\", "\\\\");
    StringReplaceAll(Code, "\r", "\\r");
    StringReplaceAll(Code, "\n", "\\n");
    StringReplaceAll(Code, "\t", "\\t");
    StringReplaceAll(Code, "\"", "\\\"");
    LoadEnd = false;
    thread LoadThread(Loading);
    string PostData = "{\"comment\":\"\",\"lang\":\"CPP\",\"submitType\":0,\"questionId\":" + to_string(QuestionID) + ",\"src\":\"" + Code + "\"";
    json CostomIOs = GetCustomIOs(QuestionID);
    if (CostomIOs["data"]["inputCustomIOs"].dump() != "null")
    {
        PostData += ",\"inputCustomIOs\":" + CostomIOs["data"]["inputCustomIOs"].dump();
        PostData += ",\"outputCustomIOs\":" + CostomIOs["data"]["outputCustomIOs"].dump();
    }
    PostData += "}";
    string TempResponse = PostDataToString("https://www.etiger.vip/thrall-web/saveSubmit", PostData);
    LoadEnd = true;
    LoadThread.join();
    if (TempResponse[0] == '<')
    {
        cout << "提交失败，请检查文件内是否包含中文" << endl;
        NotACQuestins.push_back(to_string(QuestionID) + "  提交失败，请检查文件内是否包含中文");
        return;
    }
    json Response = json::parse(TempResponse);
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << "        " << endl;
        NotACQuestins.push_back(to_string(QuestionID) + "  太戈编程返回错误信息：" + Response["msg"].as_string());
        return;
    }
    if (Response["data"]["grade"] != 100)
    {
        NotACQuestins.push_back(to_string(QuestionID) + "  得分" + Response["data"]["grade"].as_string());
    }
    cout << "得分：" << Response["data"]["grade"] << "                                " << endl;
    int Counter = 0;
    for (detail::iterator<json> Iterator = Response["data"]["result"].begin(); Iterator != Response["data"]["result"].end(); Iterator++)
    {
        cout << "测试点" << (Counter++) << "：";
        switch (Iterator.value()["type"].as_string())
        {
        case "AC":
            cout << "\033[0;32;32m";
            break;
        case "WA":
            cout << "\033[0;32;31m";
            break;
        case "CE":
            cout << "\033[1;33m";
            break;
        case "TE":
            cout << "\033[1;33m";
            break;
        case "RTE":
            cout << "\033[0;32;34m";
            break;
        case "ME":
            cout << "\033[0;37m";
            break;
        default:
            break;
        }
        cout << Iterator.value()["type"].as_string() << "\033[m " << Iterator.value()["timeUsed"] << "ms " << Iterator.value()["memUsed"] << "B" << endl;
    }
    cout << "得分：" << Response["data"]["grade"] << endl;
}

/**
 * @brief 提交所有的代码
 *
 * @param IDStartChoose 题目ID开始位置定位方式选择
 * @param IDStartPos 题目ID开始位置
 * @param IDStartString 题目ID开始关键字
 * @param IDEndChoose 题目ID结束位置定位方式选择
 * @param IDEndPos 题目ID结束位置
 * @param IDEndString 题目ID结束关键字
 */
void SubmitAllCode(bool IDStartChoose, short IDStartPos, string IDStartString, bool IDEndChoose, short IDEndPos, string IDEndString)
{
    set<string> Files;
    dirent *FileInfo;
    DIR *Dir;
    Dir = opendir("./");
    if (Dir == NULL)
    {
        return;
    }
    while ((FileInfo = readdir(Dir)) != NULL)
    {
        string FileName = FileInfo->d_name;
        if (FileName == "." || FileName == ".." || FileName.find(".cpp") == FileName.npos)
            continue;

        Files.insert(FileName);
    }
    for (set<string>::iterator Iterator = Files.begin(); Iterator != Files.end(); Iterator++)
    {
        string FileName = *Iterator;
        short ThisFileIDStartPos = IDStartPos;
        if (IDStartChoose)
        {
            ThisFileIDStartPos = FileName.find(IDStartString);
            if (ThisFileIDStartPos == FileName.npos)
            {
                cout << "在文件名" << FileName << "中找不到题目ID起始位置标识符“" << IDStartString << "”" << endl;
                continue;
            }
            ThisFileIDStartPos += IDStartString.size();
        }
        short ThisFileIDEndPos = IDEndPos;
        if (IDEndChoose)
        {
            ThisFileIDEndPos = FileName.find(IDEndString);
            if (ThisFileIDEndPos == FileName.npos)
            {
                cout << "在文件名" << FileName << "中找不到题目ID结束位置标识符“" << IDEndString << "”" << endl;
                continue;
            }
        }
        if (ThisFileIDStartPos > ThisFileIDEndPos)
        {
            cout << "在文件名" << FileName << "中题目ID的起始位置" << ThisFileIDStartPos << "大于结束位置" << ThisFileIDEndPos << endl;
            continue;
        }
        if (ThisFileIDEndPos > FileName.size())
        {
            cout << "在文件名" << FileName << "中结束位置" << ThisFileIDEndPos << "大于文件名的长度" << FileName.size() << endl;
            continue;
        }
        short QuestionID = atoi(FileName.substr(ThisFileIDStartPos, ThisFileIDEndPos - ThisFileIDStartPos).c_str());
        if (QuestionID == 0)
        {
            cout << FileName.substr(ThisFileIDStartPos, ThisFileIDEndPos - ThisFileIDStartPos) << "不是数字，跳过文件" << FileName << endl;
            continue;
        }
#ifdef __DEBUG__
        if (QuestionID > 10)
            return;
#endif
        FILE *FilePointer;
        FilePointer = fopen(FileName.c_str(), "r");
        if (FilePointer == NULL)
            continue;
        string Code = "";
        while (!feof(FilePointer))
            Code.push_back(fgetc(FilePointer));
        fclose(FilePointer);
        while (Code[Code.size() - 1] == '\n' || Code[Code.size() - 1] == '\r' || Code[Code.size() - 1] == -1)
            Code.erase(Code.size() - 1);
        cout << "提交第" << QuestionID << "题..." << endl;
        SubmitCode(QuestionID, Code);
        cout << endl;
    }
}

int main()
{
    cout << "登录..." << endl;
    Login("18117121393", "LangNing0117");
    cout << "提交所有题目..." << endl;
    SubmitAllCode(0, 0, "", 1, 0, ".cpp");
    cout << endl;
    cout << "提交完成！" << endl;
    if (NotACQuestins.size() != 0)
    {
        cout << "没有提交或通过的题目及原因：" << endl;
        for (vector<string>::iterator Iterator = NotACQuestins.begin(); Iterator != NotACQuestins.end(); Iterator++)
        {
            cout << *Iterator << endl;
        }
    }
    return 0;
}
