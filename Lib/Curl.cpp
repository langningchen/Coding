#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <unistd.h>
#include "./configor/json.hpp"
using namespace std;
using namespace configor;
string CurrentDir;
string UA = "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:107.0) Gecko/20100101 Firefox/107.0";
const string FORM = "application/x-www-form-urlencoded";
const string MULTIPART_BOUNDARY = "qv5wyfw459yhugv5swbmq39m8yuw4";
const string MULTIPART = "multipart/form-data; boundary=" + MULTIPART_BOUNDARY;
void GetCurrentDir()
{
    int BufferSize = 1024;
    char *Buffer = new char[BufferSize];
    if (readlink("/proc/self/exe", Buffer, BufferSize) == 0)
        return;
    CurrentDir = Buffer;
    delete Buffer;
    CurrentDir.erase(CurrentDir.find_last_of("/") + 1, string::npos);
}
int GetDataToFile(string URL,
                  string HeaderFileName = "Header.tmp",
                  string BodyFileName = "Body.tmp",
                  bool IsPost = false,
                  string PostData = "",
                  curl_slist *HeaderList = NULL,
                  int *HTTPResponseCode = NULL,
                  string PostContentType = "application/json",
                  string Cookie = "",
                  CURLU *URL2 = NULL)
{
    if (CurrentDir == "")
        GetCurrentDir();
    FILE *HeaderFilePointer = fopen((CurrentDir + HeaderFileName).c_str(), "w");
    FILE *BodyFilePointer = fopen((CurrentDir + BodyFileName).c_str(), "w");
    CURLcode CurlCode = curl_global_init(CURL_GLOBAL_ALL);
    if (CurlCode != 0)
    {
        cout << "libcurl初始化失败，错误代码：" << CurlCode << "。" << endl;
        fclose(BodyFilePointer);
        fclose(HeaderFilePointer);
        getchar();
        exit(0);
    }
    CURL *Curl = curl_easy_init();
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYSTATUS, false);
    curl_easy_setopt(Curl, CURLOPT_HEADERDATA, HeaderFilePointer);
    curl_easy_setopt(Curl, CURLOPT_WRITEDATA, BodyFilePointer);
    curl_easy_setopt(Curl, CURLOPT_TIMEOUT, 10);
    if (Cookie != "")
        curl_easy_setopt(Curl, CURLOPT_COOKIELIST, Cookie.c_str());
    curl_easy_setopt(Curl, CURLOPT_COOKIEFILE, "/workspaces/Coding/Keys/Cookies.tmp");
    curl_easy_setopt(Curl, CURLOPT_COOKIEJAR, "/workspaces/Coding/Keys/Cookies.tmp");
    if (URL == "")
        curl_easy_setopt(Curl, CURLOPT_CURLU, URL2);
    else
        curl_easy_setopt(Curl, CURLOPT_URL, URL.c_str());
    if (IsPost)
    {
        HeaderList = curl_slist_append(HeaderList, string("Content-Type: " + PostContentType).c_str());
        curl_easy_setopt(Curl, CURLOPT_POST, true);
        curl_easy_setopt(Curl, CURLOPT_POSTFIELDS, PostData.c_str());
    }
    HeaderList = curl_slist_append(HeaderList, string("User-Agent: " + UA).c_str());
    curl_easy_setopt(Curl, CURLOPT_HTTPHEADER, HeaderList);
    CurlCode = curl_easy_perform(Curl);
    if (CurlCode != 0)
    {
        cout << "请求发送失败，错误代码：" << CurlCode << "。" << endl;
        getchar();
        exit(0);
    }
    if (HTTPResponseCode != NULL)
        curl_easy_getinfo(Curl, CURLINFO_RESPONSE_CODE, HTTPResponseCode);
    curl_easy_cleanup(Curl);
    fclose(BodyFilePointer);
    fclose(HeaderFilePointer);
    return 0;
}
bool IfFileExist(string FileName)
{
    if (CurrentDir == "")
        GetCurrentDir();
    ifstream InputFileStream(CurrentDir + FileName);
    if (InputFileStream.bad())
        return false;
    InputFileStream.close();
    return true;
}
string GetDataFromFileToString(string FileName = "Body.tmp")
{
    if (CurrentDir == "")
        GetCurrentDir();
    string Data = "";
    FILE *BodyFilePointer = fopen((CurrentDir + FileName).c_str(), "r");
    if (BodyFilePointer == NULL)
    {
        cout << "无法打开文件" << FileName << endl;
        getchar();
        exit(0);
    }
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
    for (unsigned int i = 0; i < Data.size(); i++)
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
    if (CurrentDir == "")
        GetCurrentDir();
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
    for (unsigned int k = 0; k < Input.size(); k += 3)
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
string StringReplaceAll(string Data, string Before, string After)
{
    size_t Index = 0;
    while ((Index = Data.find(Before)) != string::npos)
        Data.replace(Index, Before.size(), After);
    return Data;
}
unsigned char ToHex(unsigned char x)
{
    return x > 9 ? x + 55 : x + 48;
}
unsigned char FromHex(unsigned char x)
{
    unsigned char y;
    if (x >= 'A' && x <= 'Z')
        y = x - 'A' + 10;
    else if (x >= 'a' && x <= 'z')
        y = x - 'a' + 10;
    else if (x >= '0' && x <= '9')
        y = x - '0';
    else
        assert(0);
    return y;
}
string URLEncode(string Input)
{
    string Output = "";
    size_t length = Input.length();
    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)Input[i]) ||
            (Input[i] == '-') ||
            (Input[i] == '_') ||
            (Input[i] == '.') ||
            (Input[i] == '~'))
            Output += Input[i];
        else if (Input[i] == ' ')
            Output += "+";
        else
        {
            Output += '%';
            Output += ToHex((unsigned char)Input[i] >> 4);
            Output += ToHex((unsigned char)Input[i] % 16);
        }
    }
    return Output;
}
string URLDecode(string Input)
{
    string Output = "";
    size_t length = Input.length();
    for (size_t i = 0; i < length; i++)
    {
        if (Input[i] == '+')
            Output += ' ';
        else if (Input[i] == '%')
        {
            assert(i + 2 < length);
            unsigned char high = FromHex((unsigned char)Input[++i]);
            unsigned char low = FromHex((unsigned char)Input[++i]);
            Output += high * 16 + low;
        }
        else
            Output += Input[i];
    }
    return Output;
}
string GetStringBetween(string Data, string Start, string End)
{
    int StartPos = Data.find(Start);
    if (StartPos == -1)
        return "";
    StartPos += Start.size();
    int EndPos = Data.find(End, StartPos + 1);
    if (EndPos == -1)
        return "";
    return Data.substr(StartPos, EndPos - StartPos);
}
string FindLocation()
{
    if (CurrentDir == "")
        GetCurrentDir();
    string Header = GetDataFromFileToString("Header.tmp");
    Header += "\n";
    string RedirectURL = GetStringBetween(Header, "Location: ", "\n");
    if (RedirectURL == "")
        RedirectURL = GetStringBetween(Header, "location: ", "\n");
    if (RedirectURL == "")
    {
        cout << "无法找到重定向位置" << endl;
        getchar();
        exit(0);
    }
    return RedirectURL.substr(0, RedirectURL.size() - 1);
}
