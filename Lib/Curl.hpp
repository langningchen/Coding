#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <unistd.h>
#include "./configor/json.hpp"
#include "./StringOperation.hpp"
using namespace std;
using namespace configor;
string UA = "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Mobile Safari/537.36 Edg/108.0.1462.76";
const string WECHAT_UA = "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36 NetType/WIFI MicroMessenger/7.0.20.1781(0x6700143B) WindowsWechat(0x6307062c)";
const string FORM = "application/x-www-form-urlencoded";
const string MULTIPART_BOUNDARY = "qv5wyfw459yhugv5swbmq39m8yuw4";
const string MULTIPART = "multipart/form-data; boundary=" + MULTIPART_BOUNDARY;
string HTTPResponseString(int HTTPResponseCode)
{
    switch (HTTPResponseCode)
    {
    case 100:
        return "Continue";
        break;
    case 101:
        return "Switching Protocols";
        break;
    case 102:
        return "Processing";
        break;
    case 103:
        return "Early Hints";
        break;
    case 200:
        return "OK";
        break;
    case 201:
        return "Created";
        break;
    case 202:
        return "Accepted";
        break;
    case 203:
        return "Non-Authoritative Information";
        break;
    case 204:
        return "No Content";
        break;
    case 205:
        return "Reset Content";
        break;
    case 206:
        return "Partial Content";
        break;
    case 207:
        return "Multi-Status";
        break;
    case 208:
        return "Already Reported";
        break;
    case 226:
        return "IM Used";
        break;
    case 300:
        return "Multiple Choice";
        break;
    case 301:
        return "Moved Permanently";
        break;
    case 302:
        return "Found";
        break;
    case 303:
        return "See Other";
        break;
    case 304:
        return "Not Modified";
        break;
    case 305:
        return "Use Proxy";
        break;
    case 306:
        return "unused";
        break;
    case 307:
        return "Temporary Redirect";
        break;
    case 308:
        return "Permanent Redirect";
        break;
    case 400:
        return "Bad Request";
        break;
    case 401:
        return "Unauthorized";
        break;
    case 402:
        return "Payment Required";
        break;
    case 403:
        return "Forbidden";
        break;
    case 404:
        return "Not Found";
        break;
    case 405:
        return "Method Not Allowed";
        break;
    case 406:
        return "Not Acceptable";
        break;
    case 407:
        return "Proxy Authentication Required";
        break;
    case 408:
        return "Request Timeout";
        break;
    case 409:
        return "Conflict";
        break;
    case 410:
        return "Gone";
        break;
    case 411:
        return "Length Required";
        break;
    case 412:
        return "Precondition Failed";
        break;
    case 413:
        return "Payload Too Large";
        break;
    case 414:
        return "URI Too Long";
        break;
    case 415:
        return "Unsupported Media Type";
        break;
    case 416:
        return "Range Not Satisfiable";
        break;
    case 417:
        return "Expectation Failed";
        break;
    case 418:
        return "I'm a teapot";
        break;
    case 421:
        return "Misdirected Request";
        break;
    case 422:
        return "Unprocessable Entity";
        break;
    case 423:
        return "Locked";
        break;
    case 424:
        return "Failed Dependency";
        break;
    case 425:
        return "Too Early";
        break;
    case 426:
        return "Upgrade Required";
        break;
    case 428:
        return "Precondition Required";
        break;
    case 429:
        return "Too Many Requests";
        break;
    case 431:
        return "Request Header Fields Too Large";
        break;
    case 451:
        return "Unavailable For Legal Reasons";
        break;
    case 500:
        return "Internal Server Error";
        break;
    case 501:
        return "Not Implemented";
        break;
    case 502:
        return "Bad Gateway";
        break;
    case 503:
        return "Service Unavailable";
        break;
    case 504:
        return "Gateway Timeout";
        break;
    case 505:
        return "HTTP Version Not Supported";
        break;
    case 506:
        return "Variant Also Negotiates";
        break;
    case 507:
        return "Insufficient Storage";
        break;
    case 508:
        return "Loop Detected";
        break;
    case 510:
        return "Not Extended";
        break;
    case 511:
        return "Network Authentication Required";
        break;
    default:
        return to_string(HTTPResponseCode);
    }
}
struct PROGRESS
{
    CURL *Curl;
};
int GetDataToFileProgressCallback(void *_Param,
                                  curl_off_t DownloadTotal, curl_off_t DownloadNow,
                                  curl_off_t UploadTotal, curl_off_t UploadNow)

{
    struct PROGRESS *Param = (struct PROGRESS *)_Param;
    CURL *Curl = Param->Curl;
    string OutputString = "\033[2K\r" + to_string(DownloadNow * 1.0 / DownloadTotal * 100) + "% ";
    double Speed = 0;
    curl_easy_getinfo(Curl, CURLINFO_SPEED_DOWNLOAD, &Speed); // curl_get_info必须在curl_easy_perform之后调用
    if (Speed > 1024 * 1024 * 1024)
        OutputString += to_string(Speed / 1024 / 1024 / 1024) + "GB/s";
    else if (Speed > 1024 * 1024)
        OutputString += to_string(Speed / 1024 / 1024) + "MB/s";
    else if (Speed > 1024)
        OutputString += to_string(Speed / 1024) + "KB/s";
    else
        OutputString += to_string(Speed) + "B/s";
    printf("%s", OutputString.c_str());
    fflush(stdout);
    return 0;
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
                  bool ShowProgress = false)
{
    if (CurrentDir == "")
        GetCurrentDir();
    FILE *HeaderFilePointer = fopen((CurrentDir + HeaderFileName).c_str(), "w");
    FILE *BodyFilePointer = fopen((CurrentDir + BodyFileName).c_str(), "w");
    CURLcode CurlCode = curl_global_init(CURL_GLOBAL_ALL);
    if (CurlCode != 0)
    {
        fclose(BodyFilePointer);
        fclose(HeaderFilePointer);
        cout << "Curl init failed!" << endl
             << CurlCode << ": " << curl_easy_strerror(CurlCode) << endl;
        return 1;
    }
    CURL *Curl = curl_easy_init();
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYSTATUS, false);
    curl_easy_setopt(Curl, CURLOPT_HEADERDATA, HeaderFilePointer);
    curl_easy_setopt(Curl, CURLOPT_WRITEDATA, BodyFilePointer);
    curl_easy_setopt(Curl, CURLOPT_CONNECTTIMEOUT, 10);
    if (ShowProgress)
    {
        cout << endl
             << "\033[?25l";
        struct PROGRESS Param;
        Param.Curl = Curl;
        curl_easy_setopt(Curl, CURLOPT_XFERINFOFUNCTION, GetDataToFileProgressCallback);
        curl_easy_setopt(Curl, CURLOPT_XFERINFODATA, &Param);
        curl_easy_setopt(Curl, CURLOPT_NOPROGRESS, false);
    }
    if (Cookie != "")
        curl_easy_setopt(Curl, CURLOPT_COOKIELIST, Cookie.c_str());
    curl_easy_setopt(Curl, CURLOPT_COOKIEFILE, "/workspaces/Coding/Keys/Cookies.tmp");
    curl_easy_setopt(Curl, CURLOPT_COOKIEJAR, "/workspaces/Coding/Keys/Cookies.tmp");
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
    if (ShowProgress)
    {
        cout << "\033[2K\033[?25h\r" << endl;
    }
    if (CurlCode != 0)
    {
        fclose(BodyFilePointer);
        fclose(HeaderFilePointer);
        cout << "Request with URL \"" << URL << "\" failed! " << endl
             << CurlCode << ": " << curl_easy_strerror(CurlCode) << endl;
        return 1;
    }
    int TempHTTPResponseCode = 0;
    curl_easy_getinfo(Curl, CURLINFO_RESPONSE_CODE, &TempHTTPResponseCode);
    if (TempHTTPResponseCode >= 500)
    {
        fclose(BodyFilePointer);
        fclose(HeaderFilePointer);
        cout << "Request with URL \"" << URL << "\" failed! " << endl
             << TempHTTPResponseCode << endl;
        return 1;
    }
    if (HTTPResponseCode != NULL)
        *HTTPResponseCode = TempHTTPResponseCode;
    curl_easy_cleanup(Curl);
    fclose(BodyFilePointer);
    fclose(HeaderFilePointer);
    return 0;
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
    return FixString(RedirectURL.substr(0, RedirectURL.size()));
}
