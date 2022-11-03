#include "../../Lib/Curl.cpp"
#include <regex>
int main()
{
    int BufferSize = 1024;
    char *Buffer = new char[BufferSize];
    readlink("/proc/self/exe", Buffer, BufferSize);
    CurrentDir = Buffer;
    delete Buffer;
    CurrentDir.erase(CurrentDir.find_last_of("/") + 1, CurrentDir.npos);
    string Name, cardCode, phone;
    // cout << "姓名：";
    // cin >> Name;
    // cout << "身份证号：";
    // cin >> cardCode;
    // cout << "手机号：";
    // cin >> phone;
    Name = "陈朗宁";
    cardCode = "370112200901170017";
    phone = "18018511393";
    UA = "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36 NetType/WIFI MicroMessenger/7.0.20.1781(0x6700143B) WindowsWechat(0x6307062c)";
    // GetDataToFile("https://wx1.pdlib.com/pudonglib-weixin/activity/list/load1?pageSize=10&currentPage=1&categoryid=33", "Header.tmp", "Body.tmp", true);
    // json ListData = json::parse(GetDataFromFileToString());
    int ActiveID = 3131;
    GetDataToFile("https://wx1.pdlib.com/pudonglib-weixin/activity/detail?id=" + to_string(ActiveID) + "&src=list");
    string Data = GetDataFromFileToString();
    Data = StringReplaceAll(Data, "\t", "");
    Data = StringReplaceAll(Data, "\r", "");
    Data = StringReplaceAll(Data, "\n", "");
    Data = StringReplaceAll(Data, "< ", "<");
    Data = StringReplaceAll(Data, " <", "<");
    Data = StringReplaceAll(Data, "> ", ">");
    Data = StringReplaceAll(Data, " >", ">");
    smatch Match;
    if (regex_search(Data, Match, regex("<h4 class=\"activity_name\">([^<]*)</h4>")))
        cout << Match.str(1) << endl;
    string::const_iterator StartPos = Data.cbegin();
    while (regex_search(StartPos, Data.cend(), Match, regex("<h5 class=\"activity_desc\">([^<]*)</h5>")))
    {
        cout << Match.str(1) << endl;
        StartPos = Match.suffix().first;
    }
    while (1)
    {
        time_t TempTime = time(NULL);
        tm *Now = localtime(&TempTime);
        cout << (Now->tm_hour < 10 ? "0" : "") << Now->tm_hour << ":" << (Now->tm_min < 10 ? "0" : "") << Now->tm_min << ":" << (Now->tm_sec < 10 ? "0" : "") << Now->tm_sec << " 状态：";
        if (Data.find("<button type=\"button\" class=\"air_button\" onclick=\"signup(" + to_string(ActiveID) + ")\">报名</button>") != string::npos)
        {
            cout << "可以报名" << endl
                 << endl
                 << "是否报名？(Y/N)" << endl;
            char Input;
            // cin >> Input;
            Input = 'Y';
            if (Input == 'Y' || Input == 'y')
            {
                int HTTPResponseCode = 0;
                GetDataToFile("https://wx1.pdlib.com/pudonglib-weixin/activity/signup/submit", "Header.tmp", "Body.tmp", true,
                              "activityId=" + to_string(ActiveID) +
                                  "&hidAge=" +
                                  "&activityType=2" +
                                  "&selectedSeatIds=" +
                                  "&name=" + URLEncode(Base64Encode(URLEncode(Name))) +
                                  "&cardType=0" +
                                  "&cardCode=" + URLEncode(Base64Encode(cardCode)) +
                                  "&phone=" + URLEncode(Base64Encode(phone)) +
                                  "&smscode=0000" +
                                  "&canvasStr=0000" +
                                  "&num=0",
                              NULL, &HTTPResponseCode, "application/x-www-form-urlencoded");
                if (HTTPResponseCode == 303)
                    cout << "报名成功！" << endl;
                else
                    cout << "报名失败！" << endl;
            }
            Clean();
            return 0;
        }
        else if (Data.find("<button type=\"button\" class=\"air_button\" onclick=\"cancelSign(" + to_string(ActiveID) + ")\">取消报名</button>") != string::npos)
        {
            cout << "已报名" << endl
                 << endl
                 << "是否取消报名？(Y/N)" << endl;
            char Input;
            cin >> Input;
            if (Input == 'Y' || Input == 'y')
            {
                int HTTPResponseCode = 0;
                GetDataToFile("https://wx1.pdlib.com/pudonglib-weixin/activity/signup/cancel", "Header.tmp", "Body.tmp", true, "activityId=" + to_string(ActiveID), NULL, &HTTPResponseCode, "application/x-www-form-urlencoded");
                if (json::parse(GetDataFromFileToString())["success"].as_bool())
                    cout << "取消报名成功！" << endl;
                else
                    cout << "取消报名失败！" << endl;
            }
            Clean();
            return 0;
        }
        else if (Data.find("<button type=\"button\" class=\"air_button\">已报满</button>") != string::npos)
        {
            cout << "已报满";
        }
        else if (Data.find("<button type=\"button\" class=\"air_button\">不在报名时间内</button>") != string::npos)
        {
            cout << "不在报名时间内";
        }
        else
        {
            cout << "未知";
        }
        cout << "          \r";
        fflush(stdout);
        sleep(5);
        GetDataToFile("https://wx1.pdlib.com/pudonglib-weixin/activity/detail?id=" + to_string(ActiveID) + "&src=list");
        Data = GetDataFromFileToString();
        Data = StringReplaceAll(Data, "\t", "");
        Data = StringReplaceAll(Data, "\r", "");
        Data = StringReplaceAll(Data, "\n", "");
        Data = StringReplaceAll(Data, "< ", "<");
        Data = StringReplaceAll(Data, " <", "<");
        Data = StringReplaceAll(Data, "> ", ">");
        Data = StringReplaceAll(Data, " >", ">");
    }
    Clean();
    return 0;
}