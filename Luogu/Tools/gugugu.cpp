#include <iostream>
#include <curl/curl.h>
using namespace std;
void GetDataToFile(string URL)
{
    cout << URL << endl;
    FILE *HeaderFilePointer = fopen("Header.tmp", "w");
    FILE *BodyFilePointer = fopen("Body.tmp", "w");
    CURLcode CurlCode = curl_global_init(CURL_GLOBAL_ALL);
    cout << CurlCode << endl;
    CURL *Curl = curl_easy_init();
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYSTATUS, false);
    curl_easy_setopt(Curl, CURLOPT_HEADERDATA, HeaderFilePointer);
    curl_easy_setopt(Curl, CURLOPT_WRITEDATA, BodyFilePointer);
    curl_easy_setopt(Curl, CURLOPT_COOKIEFILE, "Cookies.tmp");
    curl_easy_setopt(Curl, CURLOPT_COOKIEJAR, "Cookies.tmp");
    curl_easy_setopt(Curl, CURLOPT_URL, URL.c_str());
    CurlCode = curl_easy_perform(Curl);
    cout << CurlCode << endl;
    curl_easy_cleanup(Curl);
    fclose(BodyFilePointer);
    fclose(HeaderFilePointer);
    HeaderFilePointer = fopen("Header.tmp", "r");
    string HeaderData = "";
    while (!feof(HeaderFilePointer))
        HeaderData.push_back(fgetc(HeaderFilePointer));
    fclose(HeaderFilePointer);
    string LocationStartString = "location: ";
    int LocationStartPos = HeaderData.find(LocationStartString);
    if (LocationStartPos != HeaderData.npos)
    {
        LocationStartPos += LocationStartString.size();
        int LocationEndPos = LocationStartPos;
        while (LocationEndPos < HeaderData.size() && HeaderData[LocationEndPos] != '\r' && HeaderData[LocationEndPos] != '\n')
            LocationEndPos++;
        string Location = HeaderData.substr(LocationStartPos, LocationEndPos - LocationStartPos);
        if (Location[0] == '/')
        {
            string Temp = URL;
            for (int i = 0; i < 3; i++)
                Temp = Temp.substr(Temp.find("/") + 1);
            GetDataToFile(URL.substr(0, URL.size() - Temp.size() - 1) + Location);
        }
        else
            GetDataToFile(Location);
    }
}
string GetDataToString(string URL)
{
    GetDataToFile(URL);
    return "";
}
int main()
{
    GetDataToString("https://class.luogu.com.cn/");
    return 0;
}
