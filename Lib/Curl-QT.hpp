#include <curl/curl.h>
#include <unistd.h>
#include "./configor/json.hpp"
#include "./StringOperation-QT.hpp"
using namespace configor;
QString UA = "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:107.0) Gecko/20100101 Firefox/107.0";
const QString FORM = "application/x-www-form-urlencoded";
const QString MULTIPART_BOUNDARY = "qv5wyfw459yhugv5swbmq39m8yuw4";
const QString MULTIPART = "multipart/form-data; boundary=" + MULTIPART_BOUNDARY;
QString HTTPResponseString(int HTTPResponseCode)
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
        return QString::number(HTTPResponseCode);
    }
}
int GetDataToFile(QString URL,
                  QString HeaderFileName = "Header.tmp",
                  QString BodyFileName = "Body.tmp",
                  bool IsPost = false,
                  QString PostData = "",
                  curl_slist *HeaderList = NULL,
                  int *HTTPResponseCode = NULL,
                  QString PostContentType = "application/json",
                  QString Cookie = "",
                  CURLU *URL2 = NULL)
{
    if (CurrentDir == "")
        GetCurrentDir();
    CURLcode CurlCode = curl_global_init(CURL_GLOBAL_ALL);
    if (CurlCode != 0)
    {
        QMessageBox::critical(NULL, QTranslator::tr("Error"), QTranslator::tr("Curl init failed!\n") + QString::number(CurlCode) + QTranslator::tr(": ") + curl_easy_strerror(CurlCode));
        exit(0);
    }
    QFile HeaderFile(CurrentDir + HeaderFileName);
    QFile BodyFile(CurrentDir + BodyFileName);
    CURL *Curl = curl_easy_init();
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYSTATUS, false);
    curl_easy_setopt(Curl, CURLOPT_HEADERDATA, fdopen(HeaderFile.handle(), "w"));
    curl_easy_setopt(Curl, CURLOPT_WRITEDATA, fdopen(BodyFile.handle(), "w"));
    curl_easy_setopt(Curl, CURLOPT_CONNECTTIMEOUT, 10);
    if (Cookie != "")
        curl_easy_setopt(Curl, CURLOPT_COOKIELIST, Cookie.toStdString().c_str());
    curl_easy_setopt(Curl, CURLOPT_COOKIEFILE, "/workspaces/Coding/Keys/Cookies.tmp");
    curl_easy_setopt(Curl, CURLOPT_COOKIEJAR, "/workspaces/Coding/Keys/Cookies.tmp");
    if (URL == "")
        curl_easy_setopt(Curl, CURLOPT_CURLU, URL2);
    else
        curl_easy_setopt(Curl, CURLOPT_URL, URL.toStdString().c_str());
    if (IsPost)
    {
        HeaderList = curl_slist_append(HeaderList, QString("Content-Type: " + PostContentType).toStdString().c_str());
        curl_easy_setopt(Curl, CURLOPT_POST, true);
        curl_easy_setopt(Curl, CURLOPT_POSTFIELDS, PostData.toStdString().c_str());
    }
    HeaderList = curl_slist_append(HeaderList, QString("User-Agent: " + UA).toStdString().c_str());
    curl_easy_setopt(Curl, CURLOPT_HTTPHEADER, HeaderList);
    CurlCode = curl_easy_perform(Curl);
    if (CurlCode != 0)
    {
        QMessageBox::critical(NULL, QTranslator::tr("Error"), QTranslator::tr("Request with URL ") + URL + QTranslator::tr("\" failed! \n") + QString::number(CurlCode) + " " + curl_easy_strerror(CurlCode));
        exit(0);
    }
    int TempHTTPResponseCode = 0;
    curl_easy_getinfo(Curl, CURLINFO_RESPONSE_CODE, &TempHTTPResponseCode);
    if (TempHTTPResponseCode >= 500)
    {
        exit(0);
    }
    if (HTTPResponseCode != NULL)
        *HTTPResponseCode = TempHTTPResponseCode;
    curl_easy_cleanup(Curl);
    BodyFile.close();
    HeaderFile.close();
    return 0;
}
QString EraseHTMLElement(QString Data)
{
    int HTMLStartIndex = 0;
    for (int i = 0; i < Data.size(); i++)
        if (Data[i] == '<')
            HTMLStartIndex = i;
        else if (Data[i] == '>')
        {
            Data.remove(HTMLStartIndex, i - HTMLStartIndex + 1);
            i = HTMLStartIndex;
        }
    return Data;
}
void Clean()
{
    if (CurrentDir == "")
        GetCurrentDir();
    remove((CurrentDir + "Body.tmp").toStdString().c_str());
    remove((CurrentDir + "Header.tmp").toStdString().c_str());
}
QString Base64Encode(QString Input)
{
    QString base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    QString Output;
    for (int k = 0; k < Input.size(); k += 3)
    {
        Output.push_back(base64_chars[(Input.toUtf8().at(k) & 0xfc) >> 2]);
        Output.push_back(base64_chars[((Input.toUtf8().at(k) & 0x03) << 4) + ((Input.toUtf8().at(k + 1) & 0xf0) >> 4)]);
        Output.push_back(base64_chars[((Input.toUtf8().at(k + 1) & 0x0f) << 2) + ((Input.toUtf8().at(k + 2) & 0xc0) >> 6)]);
        Output.push_back(base64_chars[Input.toUtf8().at(k + 2) & 0x3f]);
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
QString URLEncode(QString Input)
{
    QString Output = "";
    for (int i = 0; i < Input.length(); i++)
    {
        if (isalnum(Input.toUtf8().at(i)) ||
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
            Output += ToHex(Input.toUtf8().at(i) >> 4);
            Output += ToHex(Input.toUtf8().at(i) % 16);
        }
    }
    return Output;
}
QString URLDecode(QString Input)
{
    QString Output = "";
    for (int i = 0; i < Input.length(); i++)
    {
        if (Input[i] == '+')
            Output += ' ';
        else if (Input[i] == '%')
        {
            assert(i + 2 < Input.length());
            unsigned char high = FromHex(Input.toUtf8().at(++i));
            unsigned char low = FromHex(Input.toUtf8().at(++i));
            Output += high * 16 + low;
        }
        else
            Output += Input[i];
    }
    return Output;
}
QString FindLocation()
{
    if (CurrentDir == "")
        GetCurrentDir();
    QString Header = GetDataFromFileToString("Header.tmp");
    Header += "\n";
    QString RedirectURL = GetStringBetween(Header, "Location: ", "\n");
    if (RedirectURL == "")
        RedirectURL = GetStringBetween(Header, "location: ", "\n");
    if (RedirectURL == "")
    {
        QMessageBox::critical(NULL, QTranslator::tr("Error"), QTranslator::tr("Can not find redirect position. "));
        exit(0);
    }
    return FixString(RedirectURL.left(RedirectURL.size()));
}
