#include "../../lib/Curl.cpp"
int main()
{
    GetDataToFile("https://docs.microsoft.com/zh-cn/shows/vs-code-livestreams/release-party-v1-70");
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
    GetDataToFile(string("https://docs.microsoft.com/api/video/public/v1/entries/" + EntryId));
    json JSONData = json::parse(GetDataFromFileToString());
    GetDataToFile(string(JSONData["publicVideo"]["highQualityVideoUrl"].as_string()), "Header.tmp", string(JSONData["title"] + ".mp4"));
    for (json::iterator jit = JSONData["publicVideo"]["captions"].begin(); jit != JSONData["publicVideo"]["captions"].end(); jit++)
        if (jit.value["language"].as_string() == "en-us")
            GetDataToFile(jit.value()["url"], string(JSONData["title"] + ".vtt"));
    Clean();
    return 0;
}