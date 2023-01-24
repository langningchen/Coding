#include "Curl.hpp"
#include <regex>
#include <sys/stat.h>
void Login()
{
    int HTTPResponseCode = 0;
    GetDataToFile("https://m.qlchat.com/wechat/page/mine/collect",
                  "Header.tmp",
                  "Body.tmp",
                  false,
                  "",
                  NULL,
                  &HTTPResponseCode);
    if (HTTPResponseCode == 302)
    {
        GetDataToFile("https://open.weixin.qq.com/connect/qrconnect?appid=wx485213694a978438&scope=snsapi_login&redirect_uri=https://m.qlchat.com/qrLogin.htm");
        string LoginQRCodeID = GetStringBetween(GetDataFromFileToString(), "<div class=\"wrp_code\"><img class=\"qrcode lightBorder\" src=\"/connect/qrcode/", "\"/></div>");
        GetDataToFile("https://open.weixin.qq.com/connect/qrcode/" + LoginQRCodeID, "Header.tmp", "QRCode.jpeg");
        system(string("code \"" + CurrentDir + "QRCode.jpeg\"").c_str());
        bool Scanned = false;
        while (true)
        {
            curl_slist *HeaderList = NULL;
            HeaderList = curl_slist_append(HeaderList, "Referer: https://open.weixin.qq.com/");
            GetDataToFile("https://lp.open.weixin.qq.com/connect/l/qrconnect?uuid=" + LoginQRCodeID + (Scanned ? "&last=404" : "") + "&_=" + to_string(time(NULL)),
                          "Header.tmp",
                          "Body.tmp",
                          false,
                          "",
                          HeaderList);
            string LoginQRCodeStatus = GetStringBetween(GetDataFromFileToString(), "window.wx_errcode=", ";");
            if (LoginQRCodeStatus == "404")
            {
                remove((CurrentDir + "QRCode.jpeg").c_str());
                cout << "已扫描，请在手机上确认" << endl;
                Scanned = true;
            }
            else if (LoginQRCodeStatus == "403")
            {
                cout << "登录已取消" << endl;
                exit(0);
            }
            else if (LoginQRCodeStatus == "500")
                cout << "正在等待继续操作" << endl;
            else if (LoginQRCodeStatus == "405")
            {
                string LoginCode = GetStringBetween(GetDataFromFileToString(), "window.wx_code='", "'");
                GetDataToFile("https://m.qlchat.com/qrLogin.htm?code=" + LoginCode + "&state=");
                cout << "登录成功" << endl;
                break;
            }
            else if (LoginQRCodeStatus == "408")
                cout << "正在等待" << endl;
            else
                cout << "未知错误 " << LoginQRCodeStatus << endl;
        }
    }
    else
        cout << "已登录" << endl;
}
void DownloadTopic(string LiveID,
                   int ChannelCounter, int ChannelSize, string ChannelName,
                   int TopicCounter, int TopicSize, string TopicID, string TopicName)
{
    string DownloadDir = "0" + to_string(ChannelCounter) + ChannelName + "_" + (TopicCounter < 10 ? "0" : "") + to_string(TopicCounter) + TopicName + "/";
    if (access((CurrentDir + DownloadDir).c_str(), 0) != -1)
    {
        cout << "已存在" << DownloadDir << "，跳过" << endl;
        return;
    }
    mkdir((CurrentDir + DownloadDir).c_str(), 0755);
    curl_slist *HeaderList = curl_slist_append(NULL, string("referer: https://m.qlchat.com/topic/details?topicId=" + TopicID).c_str());
    json PostData;
    PostData["topicId"] = TopicID;
    PostData["type"] = "audio";
    GetDataToFile("https://m.qlchat.com/api/wechat/topic/total-speak-list",
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  PostData.dump(),
                  HeaderList);
    json Data = json::parse(GetDataFromFileToString());
    int Counter = 0;
    string Command = "ffmpeg -y -hide_banner -loglevel error -i \"concat:";
    for (auto i : Data["data"]["speakList"])
    {
        Counter++;
        cout << "\r"
             << "正在下载 "
             << ChannelCounter << "/" << ChannelSize << ": " << ChannelName << "   "
             << TopicCounter << "/" << TopicSize << ": " << TopicName << "   "
             << "1/2   "
             << Counter << "/" << Data["data"]["speakList"].size() << "      " << flush;
        try
        {
            GetDataToFile(i["content"].as_string(),
                          "Header.tmp",
                          DownloadDir + to_string(Counter) + ".mp3",
                          false,
                          "",
                          NULL,
                          NULL,
                          "application/json",
                          "",
                          true);
        }
        catch (CLNException &Exception)
        {
            cout << "下载失败，正在等待5秒" << endl;
            usleep(5000000);
            Counter--;
            continue;
        }
        Command += CurrentDir + DownloadDir + to_string(Counter) + ".mp3|";
    }
    Command.erase(Command.size() - 1, 1);
    Command += "\" " + CurrentDir + DownloadDir + "00.mp3";
    if (system(Command.c_str()) == 0)
        for (int i = 1; i <= Data["data"]["speakList"].size(); i++)
            remove((CurrentDir + DownloadDir + to_string(i) + ".mp3").c_str());
    string LastTime = "0";
    vector<string> ImageURLList;
    bool Break = false;
    while (!Break)
    {
        PostData = json();
        PostData["topicId"] = TopicID;
        PostData["liveId"] = LiveID;
        PostData["time"] = LastTime;
        PostData["beforeOrAfter"] = "after";
        PostData["hideLuckyMoney"] = false;
        PostData["pullComment"] = "N";
        GetDataToFile("https://m.qlchat.com/api/wechat/topic/getTopicSpeak",
                      "Header.tmp",
                      "Body.tmp",
                      true,
                      PostData.dump(),
                      HeaderList);
        Data = json::parse(GetDataFromFileToString());
        for (auto i : Data["data"]["liveSpeakViews"])
            if (i["type"].as_string() == "image")
                ImageURLList.push_back(i["content"].as_string());
            else if (i["type"].as_string() == "end")
                Break = true;
        if (Data["data"]["liveSpeakViews"].size() < 30)
            Break = true;
        LastTime = (*Data["data"]["liveSpeakViews"].rbegin())["createTime"].as_string();
    }
    Counter = 0;
    for (auto i : ImageURLList)
    {
        Counter++;
        cout << "\r"
             << "正在下载 "
             << ChannelCounter << "/" << ChannelSize << ": " << ChannelName << "   "
             << TopicCounter << "/" << TopicSize << ": " << TopicName << "   "
             << "2/2   "
             << Counter << "/" << ImageURLList.size() << "      " << flush;
        try
        {
            GetDataToFile(i,
                          "Header.tmp",
                          DownloadDir + (Counter < 10 ? "0" : "") + to_string(Counter) + ".jpg",
                          false,
                          "",
                          NULL,
                          NULL,
                          "application/json",
                          "",
                          true);
        }
        catch (CLNException &Exception)
        {
            cout << "下载失败，正在等待5秒" << endl;
            usleep(5000000);
            Counter--;
            continue;
        }
    }
}
void DownloadChannel(string LiveID,
                     int ChannelCounter, int ChannelSize, string ChannelName, string ChannelID)
{
    json PostData;
    PostData["businessId"] = "";
    PostData["channelId"] = ChannelID;
    PostData["liveId"] = LiveID;
    PostData["page"]["page"] = 1;
    PostData["page"]["size"] = 20;
    PostData["sort"] = "asc";
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, string("referer: https://m.qlchat.com/wechat/page/channel-intro?channelId=" + ChannelID).c_str());
    GetDataToFile("https://m.qlchat.com/api/wechat/transfer/h5/interact/getCourseList",
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  PostData.dump());
    json Data = json::parse(GetDataFromFileToString());
    int Counter = 0;
    for (auto i : Data["data"]["dataList"])
    {
        Counter++;
        DownloadTopic(LiveID,
                      ChannelCounter, ChannelSize, ChannelName,
                      Counter, Data["data"]["dataList"].size(), i["businessId"].as_string(), i["businessName"].as_string());
    }
}
int main()
{
    Login();
    string LiveID = "210000327499248";
    json PostData;
    PostData["displayStatus"] = "Y";
    PostData["liveId"] = LiveID;
    PostData["page"]["page"] = 1;
    PostData["page"]["size"] = 20;
    PostData["isCamp"] = "N";
    PostData["tagId"] = 0;
    GetDataToFile("https://m.qlchat.com/api/wechat/transfer/h5/channel/getChannels",
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  PostData.dump());
    json Data = json::parse(GetDataFromFileToString());
    int Counter = 0;
    for (auto i : Data["data"]["liveChannels"])
    {
        Counter++;
        DownloadChannel(LiveID,
                        Counter, Data["data"]["liveChannels"].size(), i["name"].as_string(), i["id"].as_string());
    }
    return 0;
}
