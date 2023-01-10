#include "Curl.hpp"
int main()
{
    string TopicID = "260000212225925";
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, string(string("cookie: uid=01859021-0CC5-QL0C-A726-03FFBC6FEED5=1673160364=1704782764; ") +
                                                      "rsessionid=qlwrsid%3A5A238C2A-73EC-45CA-BB59-3E8E1BEDBC5A.i1sk7nQO7ewC5RImOX4baV6h57Tmx%2FEr2w0bmyvSO0I" +
                                                      "JSESSIONID=2A93882E907DE682D2473F2FB9BA5A3C; " +
                                                      "QL_PG_WB=0; " +
                                                      "QLZB_SESSIONID=47425334514A4A665A475366593265704B51625267324265722B704C6A63616E546678343075676F32316B3D; " +
                                                      "userId=2000002185269187; " +
                                                      "isCheckJsession=true; " +
                                                      "B_END_POINT_LEARN_TIME_210000327499248=1")
                                                   .c_str());
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
        GetDataToFile(i["content"].as_string(), "Header.tmp", "../" + to_string(Counter) + ".mp3");
        Counter++;
        cout << Counter << "/" << Data["data"]["speakList"].size() << "  " << i["content"].as_string() << endl;
        Command += CurrentDir + "../" + to_string(Counter - 1) + ".mp3|";
    }
    Command.erase(Command.size() - 1, 1);
    Command += "\" Output.mp3";
    if (system(Command.c_str()) == 0)
        for (int i = 0; i < Data["data"]["speakList"].size(); i++)
            remove((CurrentDir + "../" + to_string(i) + ".mp3").c_str());
    GetDataToFile("https://m.qlchat.com/api/wechat/topic/getTopicSpeak",
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  "{\"topicId\":\"" + TopicID + "\",\"liveId\":\"210000327499248\",\"time\":1482150169000,\"beforeOrAfter\":\"after\",\"hideLuckyMoney\":false,\"pullComment\":\"N\"}",
                  HeaderList);
    Data = json::parse(GetDataFromFileToString());
    Counter = 0;
    for (auto i : Data["data"]["liveSpeakViews"])
        if (i["content"].as_string().find(".jpg") != string::npos)
        {
            GetDataToFile(i["content"].as_string(), "Header.tmp", "../" + to_string(Counter) + ".jpg");
            Counter++;
            cout << Counter << "/" << Data["data"]["liveSpeakViews"].size() << "  " << i["content"].as_string() << endl;
        }
    Clean();
    return 0;
}