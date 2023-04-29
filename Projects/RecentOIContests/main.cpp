#include "Curl.hpp"
#include "MD5.hpp"
#include <regex>
time_t CurrentTime = time(NULL);
struct CONTEST
{
    string Name;
    time_t StartTime;
    time_t EndTime;
    string URL;
    string Description;
    enum TYPE
    {
        ACM,
        NOI,
        IOI,
        CODEFORCES,
        _51NOD,
        LE_DUO,
        UNKNOWN,
        ALL
    } Type;
    enum STATUS
    {
        NOT_STARTED,
        RUNNING,
        ENDED,
        PRACTICE,
        PERMANENT
    } Status;
    enum ORIGIN
    {
        _51NOD_WEB,
        ATCODER_WEB,
        CODEFORCES_WEB,
        LUOGU_WEB,
        NOW_CODER_WEB,
        CODE_CHEF_WEB,
        LEET_CODE_WEB,
        USACO_WEB
    } Origin;
};
vector<CONTEST> Contests;
string FixDescription(string Input)
{
    Input = regex_replace(Input, regex("<style>.*</style>"), "");
    Input = EraseHTMLElement(Input);
    Input = HTMLDecode(Input);
    Input = StringReplaceAll(Input, "\r", " ");
    Input = StringReplaceAll(Input, "\t", " ");
    Input = StringReplaceAll(Input, "\n", " ");
    Input = StringReplaceAll(Input, "  ", " ");
    return Input;
}
time_t ISOToTimeStamp(string ISO)
{
    struct tm Time;
    memset(&Time, 0, sizeof(Time));
    int DeltaHour = 0;
    int DeltaMinute = 0;
    char Sign = '+';
    sscanf(ISO.c_str(), "%d-%d-%dT%d:%d:%d%c%d:%d", &Time.tm_year, &Time.tm_mon, &Time.tm_mday, &Time.tm_hour, &Time.tm_min, &Time.tm_sec, &Sign, &DeltaHour, &DeltaMinute);
    if (Time.tm_year == 0)
        return 0;
    Time.tm_year -= 1900;
    Time.tm_mon -= 1;
    if (Sign == '-')
    {
        DeltaHour = -DeltaHour;
        DeltaMinute = -DeltaMinute;
    }
    size_t TimeStamp = mktime(&Time);
    TimeStamp += DeltaHour * 3600 + DeltaMinute * 60;
    return TimeStamp;
}
string SqueezeHTML(string Data)
{
    Data = StringReplaceAll(Data, "\r", " ");
    Data = StringReplaceAll(Data, "\n", " ");
    Data = StringReplaceAll(Data, "\t", " ");
    Data = StringReplaceAll(Data, "  ", " ");
    Data = StringReplaceAll(Data, "< ", "<");
    Data = StringReplaceAll(Data, " <", "<");
    Data = StringReplaceAll(Data, "> ", ">");
    Data = StringReplaceAll(Data, " >", ">");
    Data = StringReplaceAll(Data, "= ", "=");
    Data = StringReplaceAll(Data, " =", "=");
    Data = StringReplaceAll(Data, " '", "'");
    Data = StringReplaceAll(Data, "' ", "'");
    Data = StringReplaceAll(Data, " \"", "\"");
    Data = StringReplaceAll(Data, "\" ", "\"");
    return Data;
}
int MonthStringToMonth(string Input)
{
    Input = Input.substr(0, 3);
    if (Input == "Jan")
        return 1;
    else if (Input == "Feb")
        return 2;
    else if (Input == "Mar")
        return 3;
    else if (Input == "Apr")
        return 4;
    else if (Input == "May")
        return 5;
    else if (Input == "Jun")
        return 6;
    else if (Input == "Jul")
        return 7;
    else if (Input == "Aug")
        return 8;
    else if (Input == "Sep")
        return 9;
    else if (Input == "Oct")
        return 10;
    else if (Input == "Nov")
        return 11;
    else if (Input == "Dec")
        return 12;
    return 0;
}

void _51nod()
{
    GetDataToFile("https://www.51nod.com/Contest/ContestList");
    json Data = json::parse(GetDataFromFileToString());
    for (auto i : Data["ContestViews"])
    {
        CONTEST Temp;
        Temp.Name = i["Contest"]["Title"].as_string();
        Temp.StartTime = i["Contest"]["StartTime"].as_integer() / 1000;
        Temp.EndTime = i["Contest"]["EndTime"].as_integer() / 1000;
        Temp.URL = "https://www.51nod.com/Contest/ContestDescription.html#contestId=" + to_string(i["Contest"]["Id"].as_integer());
        Temp.Description = FixDescription(i["Contest"]["Description"].as_string());
        if (i["Contest"]["ScoreType"].as_integer() == 0)
            Temp.Type = CONTEST::TYPE::ALL;
        else if (i["Contest"]["ScoreType"].as_integer() == 1)
            Temp.Type = CONTEST::TYPE::_51NOD;
        else if (i["Contest"]["ScoreType"].as_integer() == 2)
            Temp.Type = CONTEST::TYPE::ACM;
        else if (i["Contest"]["ScoreType"].as_integer() == 3)
            Temp.Type = CONTEST::TYPE::NOI;
        else
            Temp.Type = CONTEST::TYPE::UNKNOWN;
        if (i["Contest"]["IsEnd"].is_bool())
            Temp.Status = CONTEST::STATUS::ENDED;
        else if (i["Contest"]["IsStart"].is_bool())
            Temp.Status = CONTEST::STATUS::RUNNING;
        else
            Temp.Status = CONTEST::STATUS::NOT_STARTED;
        Temp.Origin = CONTEST::ORIGIN::_51NOD_WEB;
        Contests.push_back(Temp);
    }
}
void CodeChef()
{
    GetDataToFile("https://www.codechef.com/api/list/contests/all?sort_by=START&sorting_order=asc&offset=0&mode=all");
    json Data = json::parse(GetDataFromFileToString());
    for (auto i : Data["future_contests"])
    {
        CONTEST Temp;
        Temp.Name = i["contest_name"].as_string();
        Temp.StartTime = ISOToTimeStamp(i["contest_start_date_iso"].as_string());
        Temp.EndTime = ISOToTimeStamp(i["contest_end_date_iso"].as_string());
        Temp.URL = "https://www.codechef.com/" + i["contest_code"].as_string();
        Temp.Description = "";
        Temp.Type = CONTEST::TYPE::IOI;
        Temp.Status = CONTEST::STATUS::NOT_STARTED;
        Temp.Origin = CONTEST::ORIGIN::CODE_CHEF_WEB;
        Contests.push_back(Temp);
    }
    for (auto i : Data["past_contests"])
    {
        CONTEST Temp;
        Temp.Name = i["contest_name"].as_string();
        Temp.StartTime = ISOToTimeStamp(i["contest_start_date_iso"].as_string());
        Temp.EndTime = ISOToTimeStamp(i["contest_end_date_iso"].as_string());
        Temp.URL = "https://www.codechef.com/" + i["contest_code"].as_string();
        Temp.Description = "";
        Temp.Type = CONTEST::TYPE::IOI;
        Temp.Status = CONTEST::STATUS::ENDED;
        Temp.Origin = CONTEST::ORIGIN::CODE_CHEF_WEB;
        Contests.push_back(Temp);
    }
    for (auto i : Data["practice_contests"])
    {
        CONTEST Temp;
        Temp.Name = i["contest_name"].as_string();
        Temp.StartTime = ISOToTimeStamp(i["contest_start_date_iso"].as_string());
        Temp.EndTime = ISOToTimeStamp(i["contest_end_date_iso"].as_string());
        Temp.URL = "https://www.codechef.com/" + i["contest_code"].as_string();
        Temp.Description = "";
        Temp.Type = CONTEST::TYPE::IOI;
        Temp.Status = CONTEST::STATUS::PRACTICE;
        Temp.Origin = CONTEST::ORIGIN::CODE_CHEF_WEB;
        Contests.push_back(Temp);
    }
    for (auto i : Data["present_contests"])
    {
        CONTEST Temp;
        Temp.Name = i["contest_name"].as_string();
        Temp.StartTime = ISOToTimeStamp(i["contest_start_date_iso"].as_string());
        Temp.EndTime = ISOToTimeStamp(i["contest_end_date_iso"].as_string());
        Temp.URL = "https://www.codechef.com/" + i["contest_code"].as_string();
        Temp.Description = "";
        Temp.Type = CONTEST::TYPE::IOI;
        Temp.Status = CONTEST::STATUS::RUNNING;
        Temp.Origin = CONTEST::ORIGIN::CODE_CHEF_WEB;
        Contests.push_back(Temp);
    }
}
void AtCoder()
{
    GetDataToFile("https://atcoder.jp/contests/");
    string Data = SqueezeHTML(GetDataFromFileToString());
    auto Do = [](CONTEST::STATUS Status, string Data)
    {
        smatch Match;
        string::const_iterator StartPos = Data.cbegin();
        while (regex_search(StartPos, Data.cend(), Match, regex("<tr><td class=\"text-center\"><a href='[^']*'target='blank'><time class='fixtime fixtime-full'>([^<]*)</time></a></td><td><span aria-hidden='true'data-toggle='tooltip'data-placement='top'title=\"(Algorithm|Heuristic)\">(Ⓐ|Ⓗ)</span><span class=\"(|user-red|user-orange|user-blue)\">◉</span><a href=\"/contests/([^\"]*)\">([^<]*)</a></td><td class=\"text-center\">([0-9]*):([0-9]*)</td><td class=\"text-center\">[^<]*</td></tr>")))
        {
            CONTEST Temp;
            Temp.Name = Match.str(6);
            Temp.StartTime = ISOToTimeStamp(StringReplaceAll(Match.str(1), " ", "T").substr(0, 22) + ":" + Match.str(1).substr(22, 2));
            Temp.EndTime = Temp.StartTime + 60 * 60 * stoi(Match.str(7)) + 60 * stoi(Match.str(8));
            Temp.URL = "https://atcoder.jp/contests/" + Match.str(5);
            Temp.Description = "";
            Temp.Type = CONTEST::TYPE::ACM;
            if (Match.str(4) == "user-red")
                Temp.Name = "ARC " + Temp.Name;
            else if (Match.str(4) == "user-orange")
                Temp.Name = "AGC " + Temp.Name;
            else if (Match.str(4) == "user-blue")
                Temp.Name = "ABC " + Temp.Name;
            else if (Match.str(2) == "Heuristic")
                Temp.Name = "AHC " + Temp.Name;
            Temp.Status = Status;
            Temp.Origin = CONTEST::ORIGIN::ATCODER_WEB;
            Contests.push_back(Temp);
            StartPos = Match.suffix().first;
        }
    };
    Do(CONTEST::STATUS::RUNNING, GetStringBetween(Data, "<h3>Active Contests</h3>", "<h3>"));
    Do(CONTEST::STATUS::NOT_STARTED, GetStringBetween(Data, "<h3>Upcoming Contests</h3>", "<h3>"));
    Do(CONTEST::STATUS::ENDED, GetStringBetween(Data, "<h3>Recent Contests</h3>", "More..."));

    smatch Match;
    string::const_iterator StartPos = Data.cbegin();
    while (regex_search(StartPos, Data.cend(), Match, regex("<tr><td style=\"padding-left:10px;\"><span aria-hidden='true'data-toggle='tooltip'data-placement='top'title=\"Algorithm\">Ⓐ</span><span class=\"\">◉</span><a href=\"/contests/([^\"]*)\">([^<]*)</a></td><td class=\"text-center\">-</td></tr>")))
    {
        CONTEST Temp;
        Temp.Name = Match.str(2);
        Temp.StartTime = 0;
        Temp.EndTime = 0;
        Temp.URL = "https://atcoder.jp/contests/" + Match.str(1);
        Temp.Description = "";
        Temp.Type = CONTEST::TYPE::ACM;
        Temp.Status = CONTEST::STATUS::PERMANENT;
        Temp.Origin = CONTEST::ORIGIN::ATCODER_WEB;
        Contests.push_back(Temp);
        StartPos = Match.suffix().first;
    }
}
void Codeforces()
{
    // GetDataToFile("https://codeforces.com/contests");
    // string HTMLData = SqueezeHTML(GetDataFromFileToString());
    // SetDataFromStringToFile("Temp.html", HTMLData);

    // smatch Match;
    // string::const_iterator StartPos = HTMLData.cbegin();
    // while (regex_search(StartPos, HTMLData.cend(), Match, regex("")))
    // {
    //     CONTEST Temp;
    //     Temp.Name = Match.str(2);

    //     struct tm StartTime;
    //     memset(&StartTime, 0, sizeof(StartTime));
    //     StartTime.tm_year = atoi(Match.str(7).c_str()) - 1900;
    //     StartTime.tm_mon = atoi(Match.str(6).c_str()) - 1;
    //     StartTime.tm_mday = atoi(Match.str(5).c_str());
    //     StartTime.tm_hour = atoi(Match.str(8).c_str());
    //     StartTime.tm_min = atoi(Match.str(9).c_str());
    //     StartTime.tm_sec = atoi(Match.str(10).c_str());
    //     time_t TimeStamp = mktime(&StartTime);
    //     TimeStamp += 5 * 60 * 60;
    //     Temp.StartTime = TimeStamp;

    //     TimeStamp += atoi(Match.str(11).c_str()) * 60 * 60 + atoi(Match.str(12).c_str()) * 60;
    //     Temp.EndTime = TimeStamp;

    //     Temp.URL = "https://codeforces.com/contests/" + Match.str(1);
    //     Temp.Description = "";
    //     Temp.Type = CONTEST::TYPE::CODEFORCES;
    //     Temp.Status = CONTEST::STATUS::NOT_STARTED;
    //     Temp.Origin = CONTEST::ORIGIN::CODEFORCES_WEB;
    //     Contests.push_back(Temp);
    //     StartPos = Match.suffix().first;
    // }

    // StartPos = HTMLData.cbegin();
    // while (regex_search(StartPos, HTMLData.cend(), Match, regex("<tr data-contestId=\"([0-9]*)\"><td>([^<]*)<br/><a style=\"font-size: 0\\.8em;\"href=\"/contest/[0-9]*\">Enter &raquo;</a><br/>(<a style=\"font-size: 0\\.8em;\"href=\"/contest/[0-9]*/virtual\">Virtual participation &raquo;</a><br/>)?</td><td class=\"small\">(<a href=\"/profile/[^\"]*\"title=\"[^\"]*\"class=\"[^\"]*\">(<span class=\"legendary-user-first-letter\">.</span>)?[^<]*</a><br/>)*</td><td><span class=\"format-date\"data-locale=\"[^\"]*\">([^/]*)/([0-9]*)/([0-9]*) ([0-9]*):([0-9]*)</span><br/><span class=\"format-time-only\"data-locale=\"[^\"]*\">[^<]*</span></td><td>([0-9]*):([0-9]*)(:([0-9]*))?</td><td class=\"state\"><div><a href=\"/contest/[0-9]*/standings\">Final standings</a></div></td><td style=\"font-size:0\\.8em;\"><a class=\"contestParticipantCountLinkMargin\"title=\"Registered\"href=\"/contestRegistrants/[0-9]*\"><img style=\"vertical-align: middle;\"src=\"https://codeforces\\.org/s/28182/images/icons/user\\.png\"/>&nbsp;x[0-9]*</a></td></tr>")))
    // {
    //     CONTEST Temp;
    //     Temp.Name = Match.str(2);

    //     struct tm StartTime;
    //     memset(&StartTime, 0, sizeof(StartTime));
    //     StartTime.tm_year = atoi(Match.str(7).c_str()) - 1900;
    //     StartTime.tm_mon = atoi(Match.str(6).c_str()) - 1;
    //     StartTime.tm_mday = atoi(Match.str(5).c_str());
    //     StartTime.tm_hour = atoi(Match.str(8).c_str());
    //     StartTime.tm_min = atoi(Match.str(9).c_str());
    //     StartTime.tm_sec = atoi(Match.str(10).c_str());
    //     time_t TimeStamp = mktime(&StartTime);
    //     TimeStamp += 5 * 60 * 60;
    //     Temp.StartTime = TimeStamp;

    //     TimeStamp += atoi(Match.str(11).c_str()) * 60 * 60 + atoi(Match.str(12).c_str()) * 60;
    //     Temp.EndTime = TimeStamp;

    //     Temp.URL = "https://codeforces.com/contests/" + Match.str(1);
    //     Temp.Description = "";
    //     Temp.Type = CONTEST::TYPE::CODEFORCES;
    //     Temp.Status = CONTEST::STATUS::NOT_STARTED;
    //     Temp.Origin = CONTEST::ORIGIN::CODEFORCES_WEB;
    //     Contests.push_back(Temp);
    //     StartPos = Match.suffix().first;
    // }
}
void USACO()
{
    GetDataToFile("http://www.usaco.org/");
    string HTMLData = GetDataFromFileToString();
    smatch Match;
    regex_search(HTMLData, Match, regex("<h2> ([0-9]*)-[0-9]* Schedule </h2>\\n((.*<br>\\n)*)\\s*</div>"));
    int Year = atoi(Match.str(1).c_str());
    vector<string> Temp = SpiltString(Match.str(2), "\n");
    for (auto i : Temp)
    {
        if (i == "")
            continue;
        regex_search(i, Match, regex(" *([a-zA-Z]*) ([0-9]*)-(([a-zA-Z]*) )?([0-9]*): (.*) <br>"));
        CONTEST Contest;
        Contest.Name = Match.str(6);

        struct tm Time;
        memset(&Time, 0, sizeof(Time));
        Time.tm_mon = MonthStringToMonth(Match.str(1)) - 1;
        Time.tm_year = Year - 1900 + (Time.tm_mon < 10);
        Time.tm_mday = atoi(Match.str(2).c_str());
        Time.tm_hour = 0;
        Time.tm_min = 0;
        Time.tm_sec = 0;
        Contest.StartTime = mktime(&Time) + 13 * 60 * 60;

        if (Match.str(4) != "")
            Time.tm_mon = MonthStringToMonth(Match.str(4)) - 1;
        Time.tm_mday = atoi(Match.str(5).c_str());
        Contest.EndTime = mktime(&Time) + 13 * 60 * 60;

        Contest.URL = "http://www.usaco.org/index.php?page=contests";
        Contest.Description = "";
        Contest.Type = CONTEST::TYPE::IOI;
        if (CurrentTime < Contest.StartTime)
            Contest.Status = CONTEST::STATUS::NOT_STARTED;
        else if (CurrentTime > Contest.EndTime)
            Contest.Status = CONTEST::STATUS::ENDED;
        else
            Contest.Status = CONTEST::STATUS::RUNNING;
        Contest.Origin = CONTEST::ORIGIN::USACO_WEB;
        Contests.push_back(Contest);
    }
}
void Luogu()
{
    GetDataToFile("https://www.luogu.com.cn/contest/list?_contentOnly=1");
    json Data = json::parse(GetDataFromFileToString());
    for (auto i : Data["currentData"]["contests"]["result"])
    {
        CONTEST Temp;
        Temp.Name = i["name"].as_string();
        Temp.StartTime = i["startTime"].as_integer();
        Temp.EndTime = i["endTime"].as_integer();
        Temp.URL = "https://www.luogu.com.cn/contest/" + to_string(i["id"].as_integer());
        Temp.Description = "";
        if (i["ruleType"].as_integer() == 1)
            Temp.Type = CONTEST::TYPE::NOI;
        else if (i["ruleType"].as_integer() == 2)
            Temp.Type = CONTEST::TYPE::ACM;
        else if (i["ruleType"].as_integer() == 3)
            Temp.Type = CONTEST::TYPE::LE_DUO;
        else if (i["ruleType"].as_integer() == 4)
            Temp.Type = CONTEST::TYPE::IOI;
        else if (i["ruleType"].as_integer() == 5)
            Temp.Type = CONTEST::TYPE::CODEFORCES;
        else
            Temp.Type = CONTEST::TYPE::UNKNOWN;
        if (CurrentTime < Temp.StartTime)
            Temp.Status = CONTEST::STATUS::NOT_STARTED;
        else if (CurrentTime > Temp.EndTime)
            Temp.Status = CONTEST::STATUS::ENDED;
        else
            Temp.Status = CONTEST::STATUS::RUNNING;
        Temp.Origin = CONTEST::ORIGIN::LUOGU_WEB;
        Contests.push_back(Temp);
    }
}
void NowCoder()
{
    GetDataToFile("https://ac.nowcoder.com/acm/contest/vip-index");
    string HTMLData = SqueezeHTML(GetDataFromFileToString());
    string Data = "";
    while (1)
    {
        Data = GetStringBetween(HTMLData, "data-json=\"", "\">");
        if (Data == "")
            break;
        HTMLData = HTMLData.substr(HTMLData.find("data-json=\"") + 12);
        json JSONData = json::parse(HTMLDecode(HTMLDecode(Data)));
        CONTEST Temp;
        Temp.Name = JSONData["contestName"].as_string();
        Temp.StartTime = JSONData["contestStartTime"].as_integer() / 1000;
        Temp.EndTime = JSONData["contestEndTime"].as_integer() / 1000;
        Temp.URL = "https://ac.nowcoder.com/acm/contest/" + JSONData["contestId"].as_string();
        Temp.Description = "创建者：" + JSONData["creatorName"].as_string() + "  " +
                           "主办方：" + JSONData["settingInfo"]["organizerName"].as_string() + "  " +
                           (JSONData["settingInfo"]["ratingStatus"].as_string() == "Finished" ? "不计Rating的范围：Rating>" + JSONData["settingInfo"]["ratingUpperLimit"].as_string() + "  " : "") +
                           "参与人数：" + JSONData["signUpCount"].as_string();
        if (JSONData["type"].as_integer() == 0)
            Temp.Type = CONTEST::TYPE::ACM;
        else if (JSONData["type"].as_integer() == 2)
            Temp.Type = CONTEST::TYPE::NOI;
        else if (JSONData["type"].as_integer() == 3)
            Temp.Type = CONTEST::TYPE::IOI;
        else
            Temp.Type = CONTEST::TYPE::UNKNOWN;
        if (CurrentTime < Temp.StartTime)
            Temp.Status = CONTEST::STATUS::NOT_STARTED;
        else if (CurrentTime > Temp.EndTime)
            Temp.Status = CONTEST::STATUS::ENDED;
        else
            Temp.Status = CONTEST::STATUS::RUNNING;
        Temp.Origin = CONTEST::ORIGIN::NOW_CODER_WEB;
        Contests.push_back(Temp);
    }
}
void LeetCode()
{
    GetDataToFile("https://leetcode.cn/contest/");
    string CSRF = GetStringBetween(GetDataFromFileToString("Header.tmp"), "csrftoken=", ";");
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, ("x-csrftoken: " + CSRF).c_str());
    HeaderList = curl_slist_append(HeaderList, "referer: https://leetcode.cn/contest/");
    GetDataToFile("https://leetcode.cn/graphql",
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  R"({"operationName":null,"variables":{},"query":"{\n  contestUpcomingContests {\n    containsPremium\n    title\n    cardImg\n    titleSlug\n    description\n    startTime\n    duration\n    originStartTime\n    isVirtual\n    isLightCardFontColor\n    company {\n      watermark\n      __typename\n    }\n    __typename\n  }\n}\n"})",
                  HeaderList);
    json Data = json::parse(GetDataFromFileToString());
    for (auto i : Data["data"]["contestUpcomingContests"])
    {
        CONTEST Temp;
        Temp.Name = i["title"].as_string();
        Temp.StartTime = i["startTime"].as_integer();
        Temp.EndTime = Temp.StartTime + i["duration"].as_integer();
        Temp.URL = "https://leetcode.cn/contest/" + i["titleSlug"].as_string();
        Temp.Description = FixDescription(i["description"].as_string());
        Temp.Type = CONTEST::TYPE::ACM;
        Temp.Status = CONTEST::STATUS::NOT_STARTED;
        Temp.Origin = CONTEST::ORIGIN::LEET_CODE_WEB;
        Contests.push_back(Temp);
    }
    GetDataToFile("https://leetcode.cn/graphql",
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  R"({"operationName":"contestHistory","variables":{"pageNum":1,"pageSize":10},"query":"query contestHistory($pageNum: Int!, $pageSize: Int) {\n  contestHistory(pageNum: $pageNum, pageSize: $pageSize) {\n    totalNum\n    contests {\n      containsPremium\n      title\n      cardImg\n      titleSlug\n      description\n      startTime\n      duration\n      originStartTime\n      isVirtual\n      company {\n        watermark\n        __typename\n      }\n      isEeExamContest\n      __typename\n    }\n    __typename\n  }\n}\n"})",
                  HeaderList);
    Data = json::parse(GetDataFromFileToString());
    for (auto i : Data["data"]["contestHistory"]["contests"])
    {
        CONTEST Temp;
        Temp.Name = i["title"].as_string();
        Temp.StartTime = i["startTime"].as_integer();
        Temp.EndTime = Temp.StartTime + i["duration"].as_integer();
        Temp.URL = "https://leetcode.cn/contest/" + i["titleSlug"].as_string();
        Temp.Description = FixDescription(i["description"].as_string());
        Temp.Type = CONTEST::TYPE::ACM;
        Temp.Status = CONTEST::STATUS::ENDED;
        Temp.Origin = CONTEST::ORIGIN::LEET_CODE_WEB;
        Contests.push_back(Temp);
    }
}

int main()
{
    CLN_TRY
    _51nod();
    AtCoder();
    CodeChef();
    Codeforces();
    USACO();
    Luogu();
    NowCoder();
    LeetCode();
    sort(Contests.begin(), Contests.end(),
         [](const CONTEST &a, const CONTEST &b) -> bool
         {
             if (a.StartTime == b.StartTime)
                 return a.EndTime < b.EndTime;
             return a.StartTime < b.StartTime;
         });
    json JSON;
    for (auto i : Contests)
        JSON.push_back(json(
            {{"Name", i.Name},
             {"URL", i.URL},
             {"Description", i.Description},
             {"StartTime", i.StartTime},
             {"EndTime", i.EndTime},
             {"Type", (int)i.Type},
             {"Status", (int)i.Status},
             {"Origin", (int)i.Origin}}));
    SetDataFromStringToFile("Contests.json", JSON.dump());
    CLN_CATCH
    return 0;
}
