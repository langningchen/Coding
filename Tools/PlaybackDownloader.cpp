#include <iostream>
#include <fstream>
#include <unistd.h>
#include "../Lib/Curl.cpp"
using namespace std;
string Decode(string Input, int OBFSKEY)
{
    for (unsigned int i = 0; i < Input.size(); i++)
    {
        Input[i] -= 32;
        if (Input[i] < 95)
            Input[i] = (Input[i] + 95 - OBFSKEY) % 95;
        Input[i] += 32;
    }
    return Input;
}
void Login(string Username, string Password)
{
    int HTTPResponseCode;
    GetDataToFile("https://www.luogu.com.cn/auth/login", "Header.tmp", "Body.tmp", false, "", NULL, &HTTPResponseCode);
    if (HTTPResponseCode != 302)
    {
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
    GetDataToFile("https://class.luogu.com.cn/course", "Header.tmp", "Body.tmp", false, "", NULL, &HTTPResponseCode);
    if (HTTPResponseCode != 200)
    {
        GetDataToFile("https://www.luogu.com.cn/api/OAuth2/authorize?response_type=code&client_id=lgclass.luoguclass&scope=oauth2.login&redirect_uri=https%3A%2F%2Fclass.luogu.com.cn%2Flogin%2Fcheck-luogu");
        string HeaderData = GetDataFromFileToString("Header.tmp");
        string LocationStartString = "Location: ";
        size_t LocationStartPos = HeaderData.find(LocationStartString);
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
        size_t LocationEndPos = LocationStartPos + 1;
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
    unsigned int M3U8Counter = 0;
    for (json::iterator jit = CourseInfo["currentData"]["replayFiles"].begin(); jit != CourseInfo["currentData"]["replayFiles"].end(); jit++)
    {
        GetDataToFile(Decode(jit.value()["url"]["HD"].as_string(), CourseInfo["currentData"]["obfsKey"].as_integer()));
        string M3U8Detail = GetDataFromFileToString();
        unsigned int TSCounter = 0;
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
        queue<string> TSURLList;
        for (unsigned int i = 0; i < M3U8Detail.size(); i++)
        {
            unsigned int LineStartPos = i;
            unsigned int LineEndPos = i + 1;
            while (LineEndPos < M3U8Detail.size() && M3U8Detail[LineEndPos] != '\n')
                LineEndPos++;
            string Line = M3U8Detail.substr(LineStartPos, LineEndPos - LineStartPos);
            if (Line.size() > 0)
                if (Line[0] != '#')
                    TSCounter++;
                else if (Line.find("https://class.luogu.com.cn/") != Line.npos && Line.find("https://class.luogu.com.cn/api/") == Line.npos)
                    Line.replace(Line.find("https://class.luogu.com.cn/"), 27, "https://class.luogu.com.cn/api/");
            TSURLList.push(Line);
            i = LineEndPos;
        }
        int CurrentTSIndex = 0;
        while (!TSURLList.empty())
        {
            if (TSURLList.front()[0] == '#')
                OutputFileStream << TSURLList.front() << endl;
            else
            {
                GetDataToFile(string("https://class.luogu.com.cn/api/live/signReplay?url=https://video.class.luogu.com.cn/yugu-live/" + CourseID + "/" + TSURLList.front()));
                json TSURLInfo = json::parse(GetDataFromFileToString());
                cout << "\r" << CurrentTSIndex << "/" << TSCounter;
                fflush(stdout);
                if (GetDataToFile(TSURLInfo["url"].as_string(), "Header.tmp", string(CourseInfo["currentData"]["lesson"]["name"].as_string() + "/" + to_string(CurrentTSIndex) + ".ts")) == -1)
                {
                    CurrentTSIndex--;
                    continue;
                }
                OutputFileStream << CurrentTSIndex << ".ts" << endl;
                CurrentTSIndex++;
            }
            TSURLList.pop();
        }
        OutputFileStream.close();
        if (system(string("ffmpeg -protocol_whitelist concat,file,http,https,tcp,tls,crypto -i \"" + CurrentDir + CourseInfo["currentData"]["lesson"]["name"].as_string() + "/index.m3u8\" \"" + CurrentDir + CourseInfo["currentData"]["lesson"]["name"].as_string() + "/index.mp4\"").c_str()) == 0)
        {
            if (system(string("cp \"" + CurrentDir + CourseInfo["currentData"]["lesson"]["name"].as_string() + "/index.mp4\" \"" + CurrentDir + CourseInfo["currentData"]["lesson"]["name"].as_string() + (CourseInfo["currentData"]["replayFiles"].size() == 1 ? "" : "_" + to_string(M3U8Counter)) + ".mp4\"").c_str()) == 0)
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
    readlink("/proc/self/exe", Buffer, BufferSize);
    CurrentDir = Buffer;
    delete Buffer;
    CurrentDir.erase(CurrentDir.find_last_of("/") + 1, CurrentDir.npos);
    string CourseID;
    cin >> CourseID;
    Login(GetDataFromFileToString("../Keys/LuoguUsername"), GetDataFromFileToString("../Keys/LuoguPassword"));
    DownloadVideo(CourseID);
    Clean();
    return 0;
}
