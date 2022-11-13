#include "../../Lib/Curl.cpp"
int main()
{
    GetDataToFile("https://learn.microsoft.com/zh-cn/shows/vs-code-livestreams/release-party-v1-70");
    string HTMLData = GetDataFromFileToString();
    string EntryId = GetStringBetween(HTMLData, "<meta name=\"entryId\" content=\"", "\"");
    cout << EntryId << endl;
    GetDataToFile(string("https://learn.microsoft.com/api/video/public/v1/entries/" + EntryId));
    json JSONData = json::parse(GetDataFromFileToString());
    cout << "开始下载  ";
    GetDataToFile(StringReplaceAll(string("https://learn.microsoft.com" + JSONData["publicVideo"]["audioUrl"].as_string()), " ", "%20"), "Header.tmp", string(JSONData["title"].as_string() + ".mp4"));
    cout << "结束" << endl;
    for (json::iterator jit = JSONData["publicVideo"]["captions"].begin(); jit != JSONData["publicVideo"]["captions"].end(); jit++)
        if (jit.value()["language"].as_string() == "en-us")
            GetDataToFile("https://learn.microsoft.com" + jit.value()["url"].as_string(), "Header.tmp", string(JSONData["title"].as_string() + ".vtt"));
    Clean();
    return 0;
}
