#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include "./configor/json.hpp"
#include "./StringOperation.hpp"
using namespace std;
using namespace configor;

struct PROGRESS
{
    CURL *Curl;
};
class EXIT_CHECK
{
public:
    ~EXIT_CHECK();
};

extern string UA;
const string WECHAT_UA = "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36 NetType/WIFI MicroMessenger/7.0.20.1781(0x6700143B) WindowsWechat(0x6307062c)";
const string FORM = "application/x-www-form-urlencoded";
const string MULTIPART_BOUNDARY = "----WebKitFormBoundarywTx7kyVBVbT6I1IG";
const string MULTIPART = "multipart/form-data; boundary=" + MULTIPART_BOUNDARY;
extern EXIT_CHECK ExitCheck;
int GetDataToFileProgressCallback(void *_Param,
                                  curl_off_t DownloadTotal, curl_off_t DownloadNow,
                                  curl_off_t UploadTotal, curl_off_t UploadNow);
void GetDataToFile(string URL,
                   string HeaderFileName = "Header.tmp",
                   string BodyFileName = "Body.tmp",
                   bool IsPost = false,
                   string PostData = "",
                   curl_slist *HeaderList = NULL,
                   int *HTTPResponseCode = NULL,
                   string PostContentType = "application/json",
                   string Cookie = "",
                   bool ShowProgress = false);
string EraseHTMLElement(string Data);
string Base64Encode(string Input);
unsigned char ToHex(unsigned char x);
unsigned char FromHex(unsigned char x);
string URLEncode(string Input);
string URLDecode(string Input);
string HTMLEncode(string Data);
string HTMLDecode(string Data);
string FindLocation();
