#include <iostream>
#include <fstream>
#include <memory.h>
#include <iconv.h>
#include <curl/curl.h>
#include "lib/configor-0.9.17/include/configor/json.hpp"
using namespace std;
using namespace configor;
string Token = "";
string UserName = "";
json UserData;

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
        return;
    }
    UserName = Response["data"]["nickname"].as_string();
    Token = Response["data"]["ticket"].as_string();
    cout << UserName << "，登录成功！" << endl;
}

void GetUserNumberStatic(short UserDataIndex)
{
    json Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/report/userSubmitStatic?userId=" + UserData["UserData"][UserDataIndex]["UserId"].as_string()));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        return;
    }
    UserData["UserData"][UserDataIndex]["PassQuestionsCount"] = Response["data"]["passCount"];
    UserData["UserData"][UserDataIndex]["PassQuestions"] = Response["data"]["passQuestionIds"];
    UserData["UserData"][UserDataIndex]["UnpassQuestionsCount"] = Response["data"]["unpassCount"];
    UserData["UserData"][UserDataIndex]["UnpassQuestions"] = Response["data"]["unpassQuestionIds"];
    UserData["UserData"][UserDataIndex]["SubmitCount"] = Response["data"]["submitCount"];
    UserData["UserData"][UserDataIndex]["AbilityLevel"] = Response["data"]["ability"];
    UserData["UserData"][UserDataIndex]["ACDifficulty"] = Response["data"]["acLevel"];
}

void GetUserComment(short UserDataIndex, short Type)
{
    json Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/comment/getByUserForPage?cpage=1&pagesize=0&type=" + to_string(Type) + "&userId=" + UserData["UserData"][UserDataIndex]["UserId"].as_string()));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        return;
    }
    Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/comment/getByUserForPage?cpage=1&pagesize=" + Response["recordCount"].as_string() + "&type=" + to_string(Type) + "&userId=" + UserData["UserData"][UserDataIndex]["UserId"].as_string()));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        return;
    }
    int Counter = 0;
    string TypeName = "";
    if (Type == 0)
        TypeName = "Comments";
    if (Type == 1)
        TypeName = "ProblemSolvingReport";
    if (Type == 2)
        TypeName = "ErrorSummary";
    for (detail::iterator<json> Iterator = Response["data"]["records"].begin(); Iterator != Response["data"]["records"].end(); Iterator++)
    {
        UserData["UserData"][UserDataIndex]["Comments"][Counter]["CommentID"] = Iterator.value()["id"];
        UserData["UserData"][UserDataIndex]["Comments"][Counter]["QuestionID"] = Iterator.value()["questionId"];
        UserData["UserData"][UserDataIndex]["Comments"][Counter]["Content"] = Iterator.value()["content"];
        UserData["UserData"][UserDataIndex]["Comments"][Counter]["CreateTime"] = Iterator.value()["createTime"];
        UserData["UserData"][UserDataIndex]["Comments"][Counter]["Type"] = TypeName;
        Counter++;
    }
}

void GetUserContent(short UserDataIndex)
{
    json Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/contest/getUserContestResultForPage?cpage=1&pagesize=0&userId=" + UserData["UserData"][UserDataIndex]["UserId"].as_string()));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        return;
    }
    Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/contest/getUserContestResultForPage?cpage=1&pagesize=" + Response["recordCount"].as_string() + "&userId=" + UserData["UserData"][UserDataIndex]["UserId"].as_string()));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        return;
    }
    int Counter = 0;
    for (detail::iterator<json> Iterator = Response["data"]["records"].begin(); Iterator != Response["data"]["records"].end(); Iterator++)
    {
        UserData["UserData"][UserDataIndex]["Contests"][Counter]["ID"] = Iterator.value()["id"];
        UserData["UserData"][UserDataIndex]["Contests"][Counter]["ContestID"] = Iterator.value()["contestId"];
        UserData["UserData"][UserDataIndex]["Contests"][Counter]["ContestTitle"] = Iterator.value()["contestTitle"];
        UserData["UserData"][UserDataIndex]["Contests"][Counter]["Grade"] = Iterator.value()["grade"];
        UserData["UserData"][UserDataIndex]["Contests"][Counter]["Rank"] = Iterator.value()["rank"];
        UserData["UserData"][UserDataIndex]["Contests"][Counter]["CreateTime"] = Iterator.value()["createTime"];
        Counter++;
    }
}

void GetUserTaskProgress(short UserDataIndex)
{
    json Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/task/getUserTaskProgress?cpage=1&pagesize=0&userId=" + UserData["UserData"][UserDataIndex]["UserId"].as_string()));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        return;
    }
    Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/task/getUserTaskProgress?cpage=1&pagesize=" + Response["recordCount"].as_string() + "&userId=" + UserData["UserData"][UserDataIndex]["UserId"].as_string()));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        return;
    }
    int Counter = 0;
    for (detail::iterator<json> Iterator = Response["data"]["records"].begin(); Iterator != Response["data"]["records"].end(); Iterator++)
    {
        UserData["UserData"][UserDataIndex]["Tasks"][Counter]["TaskID"] = Iterator.value()["taskId"];
        UserData["UserData"][UserDataIndex]["Tasks"][Counter]["TaskTitle"] = Iterator.value()["title"];
        UserData["UserData"][UserDataIndex]["Tasks"][Counter]["Description"] = Iterator.value()["desc"];
        UserData["UserData"][UserDataIndex]["Tasks"][Counter]["ACNumber"] = Iterator.value()["acNum"];
        UserData["UserData"][UserDataIndex]["Tasks"][Counter]["QuestionNumber"] = Iterator.value()["questionNum"];
        UserData["UserData"][UserDataIndex]["Tasks"][Counter]["ParticipantNumber"] = Iterator.value()["participantNum"];
        UserData["UserData"][UserDataIndex]["Tasks"][Counter]["Progress"] = Iterator.value()["progress"];
        Counter++;
    }
}

void GetUserPointDetail(short UserDataIndex)
{
    json Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/user/getPointDetail?cpage=1&pagesize=0&userId=" + UserData["UserData"][UserDataIndex]["UserId"].as_string()));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        return;
    }
    Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/user/getPointDetail?cpage=1&pagesize=" + Response["recordCount"].as_string() + "&userId=" + UserData["UserData"][UserDataIndex]["UserId"].as_string()));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        return;
    }
    int Counter = 0;
    for (detail::iterator<json> Iterator = Response["data"]["records"].begin(); Iterator != Response["data"]["records"].end(); Iterator++)
    {
        UserData["UserData"][UserDataIndex]["Points"][Counter]["ID"] = Iterator.value()["id"];
        UserData["UserData"][UserDataIndex]["Points"][Counter]["Point"] = Iterator.value()["point"];
        UserData["UserData"][UserDataIndex]["Points"][Counter]["Type"] = Iterator.value()["type"];
        UserData["UserData"][UserDataIndex]["Points"][Counter]["Time"] = Iterator.value()["createTime"];
        Counter++;
    }
}

string GetSubmitCodeHistory(short SubmitID)
{
    json Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/user/getSubmitForPage?cpage=1&pagesize=0&userId=" + UserData["UserData"][UserDataIndex]["UserId"].as_string()));
    if (Response["code"] != 200)
    {
        return "";
    }
    return Response["data"].as_string();
}

void GetUserSubmitHistory(short UserDataIndex)
{
    json Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/user/getSubmitForPage?cpage=1&pagesize=0&userId=" + UserData["UserData"][UserDataIndex]["UserId"].as_string()));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        return;
    }
    Response = json::parse(GetDataToString("https://www.etiger.vip/thrall-web/user/getSubmitForPage?cpage=1&pagesize=" + Response["recordCount"].as_string() + "&userId=" + UserData["UserData"][UserDataIndex]["UserId"].as_string()));
    if (Response["code"] != 200)
    {
        cout << "太戈编程返回错误信息：" << Response["msg"] << endl;
        return;
    }
    int Counter = 0;
    for (detail::iterator<json> Iterator = Response["data"]["records"].begin(); Iterator != Response["data"]["records"].end(); Iterator++)
    {
        UserData["UserData"][UserDataIndex]["Submits"][Counter]["ID"] = Iterator.value()["id"];
        UserData["UserData"][UserDataIndex]["Submits"][Counter]["QuestionID"] = Iterator.value()["questionId"];
        UserData["UserData"][UserDataIndex]["Submits"][Counter]["Grade"] = Iterator.value()["grade"];
        UserData["UserData"][UserDataIndex]["Submits"][Counter]["FirstGrade"] = Iterator.value()["firstGrade"];
        UserData["UserData"][UserDataIndex]["Submits"][Counter]["Result"] = Iterator.value()["result"];
        UserData["UserData"][UserDataIndex]["Submits"][Counter]["FirstResult"] = Iterator.value()["firstResult"];
        UserData["UserData"][UserDataIndex]["Submits"][Counter]["RunTime"] = Iterator.value()["runTime"];
        UserData["UserData"][UserDataIndex]["Submits"][Counter]["SubmitCount"] = Iterator.value()["submitCount"];
        UserData["UserData"][UserDataIndex]["Submits"][Counter]["Time"] = Iterator.value()["createTime"];
        UserData["UserData"][UserDataIndex]["Submits"][Counter]["Code"] = GetSubmitCodeHistory(Iterator.value()["id"]);
        Counter++;
    }
}

int main()
{
    cout << "登录..." << endl;
    Login("18117121393", "LangNing0117");
    ifstream InputFileStream("UserInfo.json");
    InputFileStream >> UserData;
    InputFileStream.close();
    for (int i = 0; i < 1 /*UserData["UserData"].size()*/; i++)
    {
        GetUserNumberStatic(i);
        GetUserComment(i, 0);
        GetUserComment(i, 1);
        GetUserComment(i, 2);
        GetUserContent(i);
        GetUserTaskProgress(i);
        GetUserPointDetail(i);

        cout << i << endl;
    }
    ofstream OutputFileStream("UserInfo2.json");
    OutputFileStream << setw(4) << UserData << endl;
    OutputFileStream.close();
    return 0;
}
