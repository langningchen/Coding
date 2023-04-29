#include <curl/curl.h>
#include <unistd.h>
#include "./configor/json.hpp"
#include "./StringOperation-QT.hpp"
using namespace configor;
QString UA = "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:107.0) Gecko/20100101 Firefox/107.0";
const QString FORM = "application/x-www-form-urlencoded";
const QString MULTIPART_BOUNDARY = "qv5wyfw459yhugv5swbmq39m8yuw4";
const QString MULTIPART = "multipart/form-data; boundary=" + MULTIPART_BOUNDARY;
int GetDataToFile(QString URL,
                  QString HeaderFileName = "Header.tmp",
                  QString BodyFileName = "Body.tmp",
                  bool IsPost = false,
                  QString PostData = "",
                  curl_slist *HeaderList = NULL,
                  int *HTTPResponseCode = NULL,
                  QString PostContentType = "application/json",
                  QString Cookie = "")
{
    if (CurrentDir == "")
        GetCurrentDir();
    CURLcode CurlCode = curl_global_init(CURL_GLOBAL_ALL);
    if (CurlCode != 0)
    {
        QMessageBox::critical(NULL, QTranslator::tr("Error"), QTranslator::tr("Curl init failed!\n") + QString::number(CurlCode) + QTranslator::tr(": ") + curl_easy_strerror(CurlCode));
        return 1;
    }
    FILE *HeaderFile = fopen(QString(CurrentDir + HeaderFileName).toStdString().c_str(), "w");
    if (HeaderFile == NULL)
    {
        QMessageBox::critical(NULL, QTranslator::tr("Error"), QTranslator::tr("Can not open output file: ") + CurrentDir + HeaderFileName);
        return 1;
    }
    FILE *BodyFile = fopen(QString(CurrentDir + BodyFileName).toStdString().c_str(), "w");
    if (BodyFile == NULL)
    {
        fclose(BodyFile);
        QMessageBox::critical(NULL, QTranslator::tr("Error"), QTranslator::tr("Can not open output file: ") + CurrentDir + BodyFileName);
        return 1;
    }
    CURL *Curl = curl_easy_init();
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYSTATUS, false);
    curl_easy_setopt(Curl, CURLOPT_HEADERDATA, HeaderFile);
    curl_easy_setopt(Curl, CURLOPT_WRITEDATA, BodyFile);
    curl_easy_setopt(Curl, CURLOPT_CONNECTTIMEOUT, 10);
    if (Cookie != "")
        curl_easy_setopt(Curl, CURLOPT_COOKIELIST, Cookie.toStdString().c_str());
    curl_easy_setopt(Curl, CURLOPT_COOKIEFILE, (CurrentDir + "Keys/Cookies.tmp").c_str());
    curl_easy_setopt(Curl, CURLOPT_COOKIEJAR, (CurrentDir + "Keys/Cookies.tmp").c_str());
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
        return 1;
    }
    int TempHTTPResponseCode = 0;
    curl_easy_getinfo(Curl, CURLINFO_RESPONSE_CODE, &TempHTTPResponseCode);
    if (TempHTTPResponseCode >= 500)
    {
        QMessageBox::critical(NULL, QTranslator::tr("Error"), QTranslator::tr("Request with URL ") + URL + QTranslator::tr("\" failed with error code ") + QString::number(TempHTTPResponseCode));
        return 1;
    }
    if (HTTPResponseCode != NULL)
        *HTTPResponseCode = TempHTTPResponseCode;
    curl_easy_cleanup(Curl);
    fclose(BodyFile);
    fclose(HeaderFile);
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
