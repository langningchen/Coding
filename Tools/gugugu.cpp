#include <iostream>
#include <fstream>
#include <unistd.h>
#include <curl/curl.h>
#include "lib/configor-0.9.17/include/configor/json.hpp"
using namespace std;
using namespace configor;
const string UA = "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:103.0) Gecko/20100101 Firefox/103.0";
string CurrentDir;
int GetDataToFile(string URL, string HeaderFileName = "Header.tmp", string BodyFileName = "Body.tmp", bool IsPost = false, string PostData = "", curl_slist *HeaderList = NULL, int *HTTPResponseCode = NULL)
{
    FILE *HeaderFilePointer = fopen((CurrentDir + HeaderFileName).c_str(), "w");
    FILE *BodyFilePointer = fopen((CurrentDir + BodyFileName).c_str(), "w");
    CURLcode CurlCode = curl_global_init(CURL_GLOBAL_ALL);
    if (CurlCode != 0)
    {
        cout << "libcurl初始化失败，错误代码：" << CurlCode << "。" << endl;
        fclose(BodyFilePointer);
        fclose(HeaderFilePointer);
        return -1;
    }
    CURL *Curl = curl_easy_init();
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYSTATUS, false);
    curl_easy_setopt(Curl, CURLOPT_HEADERDATA, HeaderFilePointer);
    curl_easy_setopt(Curl, CURLOPT_WRITEDATA, BodyFilePointer);
    curl_easy_setopt(Curl, CURLOPT_COOKIEFILE, (CurrentDir + "Cookies.tmp").c_str());
    curl_easy_setopt(Curl, CURLOPT_COOKIEJAR, (CurrentDir + "Cookies.tmp").c_str());
    curl_easy_setopt(Curl, CURLOPT_URL, URL.c_str());
    if (IsPost)
    {
        HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json");
        curl_easy_setopt(Curl, CURLOPT_POST, true);
        curl_easy_setopt(Curl, CURLOPT_POSTFIELDS, PostData.c_str());
    }
    HeaderList = curl_slist_append(HeaderList, string("User-Agent: " + UA).c_str());
    curl_easy_setopt(Curl, CURLOPT_HTTPHEADER, HeaderList);
    CurlCode = curl_easy_perform(Curl);
    if (CurlCode != 0)
    {
        cout << "请求发送失败，错误代码：" << CurlCode << "。" << endl;
        return -1;
    }
    if (HTTPResponseCode != NULL)
        curl_easy_getinfo(Curl, CURLINFO_RESPONSE_CODE, HTTPResponseCode);
    curl_easy_cleanup(Curl);
    fclose(BodyFilePointer);
    fclose(HeaderFilePointer);
    return 0;
}
string GetDataFromFileToString(string FileName = "Body.tmp")
{
    string Data = "";
    FILE *BodyFilePointer = fopen((CurrentDir + FileName).c_str(), "r");
    while (!feof(BodyFilePointer))
        Data.push_back(fgetc(BodyFilePointer));
    fclose(BodyFilePointer);
    while (Data.size() > 0 && (Data[Data.size() - 1] == 0x00 || Data[Data.size() - 1] == 0xFF || Data[Data.size() - 1] == -1 || Data[Data.size() - 1] == '\r' || Data[Data.size() - 1] == '\n'))
        Data.erase(Data.size() - 1);
    return Data;
}
string FixString(string Data)
{
    return (Data[Data.size() - 1] == '\n' ? FixString(Data.erase(Data.size() - 1, 1)) : Data);
}
string EraseHTMLElement(string Data)
{
    int HTMLStartIndex = 0;
    for (int i = 0; i < Data.size(); i++)
        if (Data[i] == '<')
            HTMLStartIndex = i;
        else if (Data[i] == '>')
        {
            Data.erase(HTMLStartIndex, i - HTMLStartIndex + 1);
            i = HTMLStartIndex;
        }
    return Data;
}
void Clean()
{
    remove((CurrentDir + "Captcha.jpeg").c_str());
    remove((CurrentDir + "Body.tmp").c_str());
    remove((CurrentDir + "Header.tmp").c_str());
}
string Base64Encode(string Input)
{
    string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    string Output;
    for (int k = 0; k < Input.size(); k += 3)
    {
        Output.push_back(base64_chars[(Input[k] & 0xfc) >> 2]);
        Output.push_back(base64_chars[((Input[k] & 0x03) << 4) + ((Input[k + 1] & 0xf0) >> 4)]);
        Output.push_back(base64_chars[((Input[k + 1] & 0x0f) << 2) + ((Input[k + 2] & 0xc0) >> 6)]);
        Output.push_back(base64_chars[Input[k + 2] & 0x3f]);
    }
    if (Input.size() % 3 == 1)
        Output.replace(Output.size() - 2, 2, "==");
    else if (Input.size() % 3 == 2)
        Output.replace(Output.size() - 1, 1, "=");
    return Output;
}
string Decode(string Input, int OBFSKEY)
{
    for (int i = 0; i < Input.size(); i++)
    {
        Input[i] -= 32;
        if (Input[i] < 95)
            Input[i] = (Input[i] + 95 - OBFSKEY) % 95;
        Input[i] += 32;
    }
    return Input;
}
void Usage()
{
    cout << R"(咕咕咕)" << endl;
    Clean();
    exit(0);
}
void Login(string Username, string Password)
{
    int HTTPResponseCode;
    GetDataToFile("https://www.luogu.com.cn/auth/login", "Header.tmp", "Body.tmp", false, "", NULL, &HTTPResponseCode);
    if (HTTPResponseCode != 302)
    {
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
    GetDataToFile("https://class.luogu.com.cn/course", "Header.tmp", "Body.tmp", false, "", NULL, &HTTPResponseCode);
    if (HTTPResponseCode != 200)
    {
        GetDataToFile("https://www.luogu.com.cn/api/OAuth2/authorize?response_type=code&client_id=lgclass.luoguclass&scope=oauth2.login&redirect_uri=https%3A%2F%2Fclass.luogu.com.cn%2Flogin%2Fcheck-luogu");
        string HeaderData = GetDataFromFileToString("Header.tmp");
        string LocationStartString = "Location: ";
        int LocationStartPos = HeaderData.find(LocationStartString);
        if (LocationStartPos == HeaderData.npos)
        {
            LocationStartString = "location: ";
            LocationStartPos = HeaderData.find(LocationStartString);
            if (LocationStartPos == HeaderData.npos)
            {
                cout << "无法找到重定向网址起始位置" << endl;
                return;
            }
        }
        LocationStartPos += LocationStartString.size();
        int LocationEndPos = LocationStartPos + 1;
        while (HeaderData[LocationEndPos] != '\n' && HeaderData[LocationEndPos] != '\r' && LocationEndPos < HeaderData.size())
            LocationEndPos++;
        GetDataToFile(HeaderData.substr(LocationStartPos, LocationEndPos - LocationStartPos));
    }
}
void DownloadVideo(string CourseID)
{
    GetDataToFile(string("https://class.luogu.com.cn/classroom/" + CourseID + "?_contentOnly=1"));
    json CourseInfo = json::parse(GetDataFromFileToString());
    if (CourseInfo["code"].as_integer() != 200)
    {
        cout << "获取课程信息失败，错误码：" << CourseInfo["code"].as_integer() << "，错误信息：" << CourseInfo["currentData"]["errorMessage"].as_string() << endl;
        return;
    }
    int M3U8Counter = 0;
    for (json::iterator jit = CourseInfo["currentData"]["replayFiles"].begin(); jit != CourseInfo["currentData"]["replayFiles"].end(); jit++)
    {
        GetDataToFile(Decode(jit.value()["url"]["HD"].as_string(), CourseInfo["currentData"]["obfsKey"].as_integer()));
        string M3U8Detail = GetDataFromFileToString();
        int TSCounter = 0;
        if (system(string("mkdir \"" + CurrentDir + CourseInfo["currentData"]["lesson"]["name"].as_string() + "\"").c_str()) != 0)
        {
            cout << "创建文件夹失败" << endl;
            return;
        }
        ofstream OutputFileStream(string(CurrentDir + CourseInfo["currentData"]["lesson"]["name"].as_string() + "/index.m3u8"));
        if (OutputFileStream.bad())
        {
            cout << "无法打开输出文件" << endl;
            return;
        }
        for (int i = 0; i < M3U8Detail.size(); i++)
        {
            int LineStartPos = i;
            int LineEndPos = i + 1;
            while (LineEndPos < M3U8Detail.size() && M3U8Detail[LineEndPos] != '\n')
                LineEndPos++;
            string Line = M3U8Detail.substr(LineStartPos, LineEndPos - LineStartPos);
            if (Line.size() > 0 && Line[0] != '#')
            {
                GetDataToFile(string("https://class.luogu.com.cn/api/live/signReplay?url=https://video.class.luogu.com.cn/yugu-live/" + CourseID + "/" + Line));
                json TSURLInfo = json::parse(GetDataFromFileToString());
                cout << TSURLInfo["url"].as_string() << endl;
                if (GetDataToFile(TSURLInfo["url"].as_string(), "Header.tmp", string(CourseInfo["currentData"]["lesson"]["name"].as_string() + "/" + to_string(TSCounter) + ".ts")) == -1)
                {
                    i--;
                    continue;
                }
                OutputFileStream << TSCounter << ".ts" << endl;
                TSCounter++;
            }
            else
            {
                if (Line.find("https://class.luogu.com.cn/") != Line.npos)
                    Line.replace(Line.find("https://class.luogu.com.cn/"), 27, "https://class.luogu.com.cn/api/");
                OutputFileStream << Line << endl;
            }
            i = LineEndPos;
        }
        OutputFileStream.close();
        if (system(string("ffmpeg -protocol_whitelist concat,file,http,https,tcp,tls,crypto -i \"" + CurrentDir + CourseInfo["currentData"]["lesson"]["name"].as_string() + "/index.m3u8\" \"" + CurrentDir + CourseInfo["currentData"]["lesson"]["name"].as_string() + "/index.mp4\"").c_str()) == 0)
        {
            if (system(string("cp \"" + CurrentDir + CourseInfo["currentData"]["lesson"]["name"].as_string() + "/index.mp4\" \"" + CurrentDir + CourseInfo["currentData"]["lesson"]["name"].as_string() + "_" + to_string(M3U8Counter) + ".mp4\"").c_str()) == 0)
            {
                if (system(string("rm -r \"" + CurrentDir + CourseInfo["currentData"]["lesson"]["name"].as_string() + "\"").c_str()) != 0)
                {
                    cout << "删除临时文件出错" << endl;
                    return;
                }
            }
            else
            {
                cout << "MP4复制出错" << endl;
                return;
            }
        }
        else
        {
            cout << "TS文件合并出错" << endl;
            return;
        }
        M3U8Counter++;
    }
}
int main()
{
    int BufferSize = 1024;
    char *Buffer = new char[BufferSize];
    int ReadedSize = readlink("/proc/self/exe", Buffer, BufferSize);
    CurrentDir = Buffer;
    delete Buffer;
    CurrentDir.erase(CurrentDir.find_last_of("/") + 1, CurrentDir.npos);
    string CourseID;
    cin >> CourseID;
    Login("langningc2009", "1!2@3#qQwWeE");
    DownloadVideo(CourseID);
    Clean();
    return 0;
}
