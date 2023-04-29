#include "Curl.hpp"
extern string CurrentDir;
string VTTToLRC(string Input)
{
    vector<string> Lines = SpiltString(StringReplaceAll(Input, "\r", ""), "\n");
    string Output = "";
    for (auto i : Lines)
        if (i == "" || i == "WEBVTT")
            continue;
        else if (i.find("-->") != string::npos)
            Output += "\n[" + GetStringBetween(i, "", " --> ") + "]";
        else
            Output += StringReplaceAll(StringReplaceAll(i, "[", " "), "]", " ") + " ";
    Output.erase(0, 1);
    return Output;
}
int main()
{
    CLN_TRY
    // string ShowName = "tabs-vs-spaces";
    string ShowName;
    cout << "Please input the name of the show you want to download:  " << flush;
    cin >> ShowName;
    GetDataToFile("https://learn.microsoft.com/api/contentbrowser/search/shows/" + ShowName + "/episodes" +
                  "?locale=en-us" +
                  "&facet=languages" +
                  "&%24orderBy=upload_date%20desc" +
                  "&%24top=30");
    json JSONData = json::parse(GetDataFromFileToString());
    int Counter = 0;
    for (auto i : JSONData["results"])
    {
        Counter++;
        cout << (Counter < 10 ? "0" : "") << Counter << " " << i["title"].as_string() << endl;
    }
    cout << "Please input the id of the video you want to download:  " << flush;
    int Choice = 0;
#ifdef TEST
    Choice = 1;
    cout << 1 << endl;
#else
    cin >> Choice;
#endif
    if (Choice > Counter || Choice < 1)
    {
        TRIGGER_ERROR("Input invalid");
    }
    string Name = JSONData["results"][Choice - 1]["title"].as_string();
    string EntryID = JSONData["results"][Choice - 1]["entry_id"].as_string();
    GetDataToFile(string("https://learn.microsoft.com/api/video/public/v1/entries/" + EntryID));
    JSONData = json::parse(GetDataFromFileToString());
    cout << "Downloading video... " << flush;
    GetDataToFile(
        StringReplaceAll(
            string("https://learn.microsoft.com" +
                   StringReplaceAll(JSONData["publicVideo"]["highQualityVideoUrl"].as_string(),
                                    "https://learn.microsoft.com",
                                    "")),
            " ", "%20"),
        "Header.tmp",
        Name + ".mp4",
        false,
        "",
        NULL,
        NULL,
        "application/json",
        "",
        true);
    cout << "Success" << endl;
    cout << "Changing video format... " << flush;
    if (system(("ffmpeg -y -hide_banner -loglevel error -i "s +
                "\"" + CurrentDir + Name + ".mp4\" " +
                "\"" + CurrentDir + Name + ".mp3\"")
                   .c_str()))
    {
        TRIGGER_ERROR("Change video to audio failed");
    }
    // remove((CurrentDir + Name + ".mp4").c_str());
    cout << "Success" << endl;
    cout << "Downloading subtitle... " << flush;
    for (json::iterator jit = JSONData["publicVideo"]["captions"].begin(); jit != JSONData["publicVideo"]["captions"].end(); jit++)
        if (jit.value()["language"].as_string() == "en-us")
            GetDataToFile("https://learn.microsoft.com" +
                              StringReplaceAll(jit.value()["url"].as_string(), "https://learn.microsoft.com", ""),
                          "Header.tmp",
                          Name + ".vtt");
    cout << "Success" << endl;
    cout << "Changing subtitle format... " << flush;
    SetDataFromStringToFile(Name + ".lrc",
                            VTTToLRC(GetDataFromFileToString(
                                Name + ".vtt")));
    remove((CurrentDir + Name + ".vtt").c_str());
    cout << "Success" << endl;
#ifdef TEST
    OutputSummary("Success");
#endif
    CLN_CATCH return 0;
}
