#include "Curl.hpp"
#include <regex>
#include <sys/stat.h>
int main()
{
    // https://m.qlchat.com/topic/details?topicId=*** <---这个就是课程ID
    cout << "请输入课程ID：";
    string TopicID;
    // TopicID = "260000212225925";
    cin >> TopicID;
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
                cout << "已扫描，请在手机上确认" << endl;
                Scanned = true;
            }
            else if (LoginQRCodeStatus == "403")
            {
                cout << "登录已取消" << endl;
                return 0;
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
    rmdir((CurrentDir + "../Images").c_str());
    mkdir((CurrentDir + "../Images").c_str(), 0755);
    rmdir((CurrentDir + "../Audios").c_str());
    mkdir((CurrentDir + "../Audios").c_str(), 0755);
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, string("referer: https://m.qlchat.com/topic/details?topicId=" + TopicID).c_str());
    GetDataToFile("https://m.qlchat.com/api/wechat/topic/total-speak-list",
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  "{\"type\":\"audio\",\"topicId\":\"" + TopicID + "\"}",
                  HeaderList);
    json Data = json::parse(GetDataFromFileToString());
    int Counter = 0;
    string Command = "ffmpeg -i \"concat:";
    for (auto i : Data["data"]["speakList"])
    {
        Counter++;
        GetDataToFile(i["content"].as_string(), "Header.tmp", "../Audios/" + to_string(Counter) + ".mp3");
        cout << Counter << "/" << Data["data"]["speakList"].size() << "  " << i["content"].as_string() << endl;
        Command += CurrentDir + "../Audios/" + to_string(Counter) + ".mp3|";
    }
    Command.erase(Command.size() - 1, 1);
    Command += "\" Output.mp3";
    if (system(Command.c_str()) == 0)
        for (int i = 1; i <= Data["data"]["speakList"].size(); i++)
            remove((CurrentDir + "../Audios/" + to_string(i) + ".mp3").c_str());
    string LastTime = "0";
    vector<string> ImageURLList;
    bool Break = false;
    while (!Break)
    {
        GetDataToFile("https://m.qlchat.com/api/wechat/topic/getTopicSpeak",
                      "Header.tmp",
                      "Body.tmp",
                      true,
                      "{\"topicId\":\"" + TopicID + "\",\"liveId\":\"210000327499248\",\"time\":" + LastTime + ",\"beforeOrAfter\":\"after\",\"hideLuckyMoney\":false,\"pullComment\":\"N\"}",
                      HeaderList);
        Data = json::parse(GetDataFromFileToString());
        for (auto i : Data["data"]["liveSpeakViews"])
            if (i["type"].as_string() == "image")
            {
                ImageURLList.push_back(i["content"].as_string());
            }
            else if (i["type"].as_string() == "end")
                Break = true;
        LastTime = (*Data["data"]["liveSpeakViews"].rbegin())["createTime"].as_string();
    }
    Counter = 0;
    for (auto i : ImageURLList)
    {
        Counter++;
        cout << Counter << "/" << ImageURLList.size() << "  " << i << endl;
        GetDataToFile(i, "Header.tmp", "../Images/" + to_string(Counter) + ".jpg");
    }
    return 0;
}