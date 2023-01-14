#include "Curl.hpp"
string VTTToLRC(string Input)
{
    vector<string> Lines = StringSpilt(StringReplaceAll(Input, "\r", ""), "\n");
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
    string ShowName = "visual-studio-toolbox";
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
    cout << "请输入要下载的视频序号  " << flush;
    int Choice;
    cin >> Choice;
    if (Choice > Counter || Choice < 1)
    {
        cout << "输入错误" << endl;
        return 0;
    }
    string Name = JSONData["results"][Choice - 1]["title"].as_string();
    string EntryID = JSONData["results"][Choice - 1]["entry_id"].as_string();
    GetDataToFile(string("https://learn.microsoft.com/api/video/public/v1/entries/" + EntryID));
    JSONData = json::parse(GetDataFromFileToString());
    cout << "开始下载视频  " << flush;
    GetDataToFile(
        StringReplaceAll(
            string("https://learn.microsoft.com" +
                   JSONData["publicVideo"]["audioUrl"].as_string()),
            " ", "%20"),
        "Header.tmp",
        "../" + Name + ".mp4",
        false,
        "",
        NULL,
        NULL,
        "application/json",
        "",
        true);
    cout << "结束" << endl;
    cout << "开始转换视频  " << flush;
    if (system((string("ffmpeg -hide_banner -loglevel error -i ") +
                "\"" + CurrentDir + "../" + Name + ".mp4\" " +
                "\"" + CurrentDir + "../" + Name + ".mp3\"")
                   .c_str()))
    {
        cout << "转换失败" << endl;
        return 0;
    }
    remove((CurrentDir + "../" + Name + ".mp4").c_str());
    cout << "结束" << endl;
    cout << "开始下载字幕  " << flush;
    for (json::iterator jit = JSONData["publicVideo"]["captions"].begin(); jit != JSONData["publicVideo"]["captions"].end(); jit++)
        if (jit.value()["language"].as_string() == "en-us")
            GetDataToFile("https://learn.microsoft.com" + jit.value()["url"].as_string(),
                          "Header.tmp",
                          "../" + Name + ".vtt");
    cout << "结束" << endl;
    cout << "开始转换字幕  " << flush;
    SetDataFromStringToFile("../" + Name + ".lrc",
                            VTTToLRC(GetDataFromFileToString(
                                "../" + Name + ".vtt")));
    remove((CurrentDir + "../" + Name + ".vtt").c_str());
    cout << "结束" << endl;
    Clean();
    return 0;
}
