#include "../../lib/Curl.cpp"
int main()
{
    GetDataToFile("https://learn.microsoft.com/zh-cn/shows/vs-code-livestreams/release-party-v1-70");
    string HTMLData = GetDataFromFileToString();
    string EntryIdStartString = "<meta name=\"entryId\" content=\"";
    unsigned int EntryIdStartPos = HTMLData.find(EntryIdStartString);
    if (EntryIdStartPos == HTMLData.npos)
    {
        cout << "Can not find Entry ID start pos. " << endl;
        return 0;
    }
    EntryIdStartPos += EntryIdStartString.size();
    unsigned int EntryIdEndPos = EntryIdStartPos + 1;
    while (EntryIdEndPos < HTMLData.npos && HTMLData[EntryIdEndPos] != '"')
        EntryIdEndPos++;
    string EntryId = HTMLData.substr(EntryIdStartPos, EntryIdEndPos - EntryIdStartPos);
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
