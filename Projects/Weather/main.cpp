#include "Curl.hpp"
#include <regex>
using namespace std;
string GetCityID(string QueryName)
{
    GetDataToFile("https://m.weathercn.com/citysearchajax.do?q=" +
                  URLEncode(QueryName, true));
    json CityData = json::parse(GetDataFromFileToString());
    if (CityData["listAccuCity"].size() == 0)
        return "";
    return CityData["listAccuCity"][0]["key"];
}
int main()
{
    map<string, string> DefaultCity;
    DefaultCity["北京"] = "北京";
    DefaultCity["上海"] = "上海";
    DefaultCity["天津"] = "天津";
    DefaultCity["重庆"] = "重庆";
    DefaultCity["香港"] = "香港";
    DefaultCity["澳门"] = "澳门";
    DefaultCity["台湾"] = "台北";
    DefaultCity["河北"] = "石家庄";
    DefaultCity["山西"] = "太原";
    DefaultCity["内蒙古"] = "呼和浩特";
    DefaultCity["辽宁"] = "沈阳";
    DefaultCity["吉林"] = "长春";
    DefaultCity["黑龙江"] = "哈尔滨";
    DefaultCity["江苏"] = "南京";
    DefaultCity["浙江"] = "杭州";
    DefaultCity["安徽"] = "合肥";
    DefaultCity["福建"] = "福州";
    DefaultCity["江西"] = "南昌";
    DefaultCity["山东"] = "济南";
    DefaultCity["河南"] = "郑州";
    DefaultCity["湖北"] = "武汉";
    DefaultCity["湖南"] = "长沙";
    DefaultCity["广东"] = "广州";
    DefaultCity["广西"] = "南宁";
    DefaultCity["海南"] = "海口";
    DefaultCity["四川"] = "成都";
    DefaultCity["贵州"] = "贵阳";
    DefaultCity["云南"] = "昆明";
    DefaultCity["西藏"] = "拉萨";
    DefaultCity["陕西"] = "西安";
    DefaultCity["甘肃"] = "兰州";
    DefaultCity["青海"] = "西宁";
    DefaultCity["宁夏"] = "银川";
    DefaultCity["新疆"] = "乌鲁木齐";

    GetDataToFile("https://ip.useragentinfo.com/json");
    json IPData = json::parse(GetDataFromFileToString());
    string CityID = "";
    if (IPData["area"].as_string() == "" ||
        ((CityID = GetCityID(IPData["area"].as_string())) == "") ||
        IPData["city"].as_string() == "" ||
        ((CityID = GetCityID(IPData["city"].as_string())) == ""))
    {
        bool Founded = false;
        for (auto i : DefaultCity)
            if (IPData["province"].as_string().find(i.first) != string::npos)
            {
                Founded = true;
                if ((CityID = GetCityID(i.second)) == "")
                    CityID = GetCityID("北京");
            }
        if (!Founded)
            CityID = GetCityID("北京");
    }
    GetDataToFile("https://m.weathercn.com/current-weather.do?partner=1000001069_hfaw&id=" + CityID + "&p_source=&p_type=jump");
    string Data = GetDataFromFileToString();
    Data = StringReplaceAll(Data, "\r", "");
    Data = StringReplaceAll(Data, "\t", "");
    Data = StringReplaceAll(Data, " \n", "\n");
    Data = StringReplaceAll(Data, "\n ", "\n");
    Data = StringReplaceAll(Data, "\n", " ");
    Data = StringReplaceAll(Data, "< ", "<");
    Data = StringReplaceAll(Data, " >", ">");
    Data = StringReplaceAll(Data, " <", "<");
    Data = StringReplaceAll(Data, "> ", ">");
    Data = StringReplaceAll(Data, "= ", "=");
    Data = StringReplaceAll(Data, " =", "=");
    Data = StringReplaceAll(Data, "\" ", "\"");
    Data = StringReplaceAll(Data, " \"", "\"");
    Data = StringReplaceAll(Data, "' ", "'");
    Data = StringReplaceAll(Data, " '", "'");
    Data = StringReplaceAll(Data, "  ", " ");

    SetDataFromStringToFile("Output.tmp", Data);

    smatch Match;
    regex Regex = regex("var _country=\"([^\"]*)\"\\|\\|\"NULL\"; var _province=\"([^\"]*)\"\\|\\|\"NULL\"; var _city=\"([^\"]*)\"\\|\\|\"NULL\"; .*<span class=\"current-date\">([0-9]{2})月([0-9]{2})日 星期(.{3})<\\/span><div class=\"current-weather-center\"><div class=\"current-weather-left\"><div class=\"current-temperature\"><img src=\"\\/\\/static\\.weathercn\\.com\\/1080\\/pro-20221226102938\\/static\\/images\\/weather_icon\\/light\\/cma\\/[0-9]{2}\\.png\"alt=\"\"\\/><p>([-0-9]*)<span>℃<\\/span><\\/p><\\/div>(<a class=\"current-weather-warning\"href=\"\\/weather-warning\\.do\\?partner=1000001069_hfaw&language=zh-cn&id=106570&p_source=&p_type=jump\"><img src=\"\\/\\/static\\.weathercn\\.com\\/1080\\/pro-20221226102938\\/static\\/images\\/warning_icon\\/[0-9]*\\.png\">([^<]*)<\\/a>)?<\\/div><div class=\"current-weather-right\"><p>([^<]*)<\\/p><p>([-0-9]*)℃<span>\\/<\\/span>([-0-9]*)℃<\\/p><a href=\"\\/air-quality\\.do\\?partner=1000001069_hfaw&language=zh-cn&id=[0-9]*&p_source=&p_type=jump\">空气质量：([^<]*)<\\/a><\\/div><\\/div><\\/div><ul class=\"current-details\"><li><img src=\"\\/\\/static\\.weathercn\\.com\\/1080\\/pro-20221226102938\\/static\\/images\\/[^\\.]*\\.png\"alt=\"\"\\/><span>([^<]*)<\\/span><p>([^<]*)<\\/p><\\/li><li><img src=\"\\/\\/static\\.weathercn\\.com\\/1080\\/pro-20221226102938\\/static\\/images\\/[^\\.]*\\.png\"alt=\"\"\\/><span>([^<]*)<\\/span><p>([^<]*)<\\/p><\\/li><li><img src=\"\\/\\/static\\.weathercn\\.com\\/1080\\/pro-20221226102938\\/static\\/images\\/[^\\.]*\\.png\"alt=\"\"\\/><span>([^<]*)<\\/span><p>([^<]*)<\\/p><\\/li><li><img src=\"\\/\\/static\\.weathercn\\.com\\/1080\\/pro-20221226102938\\/static\\/images\\/[^\\.]*\\.png\"alt=\"\"\\/><span>([^<]*)<\\/span><p>([^<]*)<\\/p><\\/li><li><img src=\"\\/\\/static\\.weathercn\\.com\\/1080\\/pro-20221226102938\\/static\\/images\\/[^\\.]*\\.png\"alt=\"\"\\/><span>([^<]*)<\\/span><p>([^<]*)<\\/p><\\/li><li><img src=\"\\/\\/static\\.weathercn\\.com\\/1080\\/pro-20221226102938\\/static\\/images\\/[^\\.]*\\.png\"alt=\"\"\\/><span>([^<]*)<\\/span><p>([^<]*)<\\/p><\\/li><li><img src=\"\\/\\/static\\.weathercn\\.com\\/1080\\/pro-20221226102938\\/static\\/images\\/[^\\.]*\\.png\"alt=\"\"\\/><span>([^<]*)<\\/span><p>([^<]*)<\\/p><\\/li><li><img src=\"\\/\\/static\\.weathercn\\.com\\/1080\\/pro-20221226102938\\/static\\/images\\/[^\\.]*\\.png\"alt=\"\"\\/><span>([^<]*)<\\/span><p>([^<]*)<\\/p><\\/li><\\/ul><\\/div><section.*<\\/section><div class=\"common-wrapper wind\"><h4>风力风向<\\/h4><div class=\"wind-con\"><div class=\"wind-icon\"><\\/div><div class=\"wind-line\"><\\/div><div class=\"wind-detail\"><p><span>风<\\/span>([^0-9]*)([0-9]*)级<\\/p><p><span>阵风<\\/span>([^0-9]*)([0-9]*)级<\\/p><\\/div><\\/div><\\/div><div class=\"common-wrapper sunrise\"><h4>日出日落<\\/h4><div class=\"sunrise-canvas\"><canvas id=\"canvas\"width=400 height=400 style=\"\"><\\/canvas><\\/div><div class=\"sunrise-detail sunrise-sun\"><p><span>日出<\\/span>.{6}([0-9]{2}):([0-9]{2})<\\/p><p><span>日落<\\/span>.{6}([0-9]{2}):([0-9]{2})<\\/p><\\/div><div class=\"sunrise-detail\"><p><span>月出<\\/span>.{6}([0-9]{2}):([0-9]{2})<\\/p><p><span>月落<\\/span>.{6}([0-9]{2}):([0-9]{2})<\\/p><\\/div><img src=\"\\/\\/static\\.weathercn\\.com\\/1080\\/pro-20221226102938\\/static\\/images\\/icon_sun\\.png\"class=\"sunrise-img-sun hide\"><img src=\"\\/\\/static\\.weathercn\\.com\\/1080\\/pro-20221226102938\\/static\\/images\\/icon_moon\\.png\"class=\"sunrise-img-moon hide\"><\\/div><div class=\"living-index js-index-module\"><h2 class=\"h2\">生活指数<a href=\"\\/livingindex\\.do\\?partner=1000001069_hfaw&id=[0-9]*&p_source=&p_type=jump\">更多<\\/a><\\/h2><div class=\"living-index-con\"><div class=\"living-index-tab\"><a href=\"javascript:;\"class=\"on js-statistics-btn\"btn-name=\"生活指数模块-今天\">今天<\\/a><a href=\"javascript:;\"class=\"js-statistics-btn\"btn-name=\"生活指数模块-明天\">明天<\\/a><a href=\"javascript:;\"class=\"js-statistics-btn\"btn-name=\"生活指数模块-后天\">后天<\\/a><\\/div><div class=\"living-index-list\"><div class=\"living-index-row\"><div class=\"living-index-wind\"><i><\\/i><p>风力<\\/p><strong>微风<\\/strong><\\/div><div class=\"living-index-wind-direction\"><i><\\/i><p>风向<\\/p><strong>南风<\\/strong><\\/div><div class=\"living-index-dressing\"><i><\\/i><p>穿衣<\\/p><strong>风衣<\\/strong><\\/div><div class=\"living-index-movement\"><i><\\/i><p>运动<\\/p><strong>室内<\\/strong><\\/div><\\/div><div class=\"living-index-row\"><div class=\"living-index-ill\"><i><\\/i><p>感冒<\\/p><strong>容易<\\/strong><\\/div><div class=\"living-index-car\"><i><\\/i><p>洗车<\\/p><strong>不宜<\\/strong><\\/div><div class=\"living-index-allergy\"><i><\\/i><p>过敏<\\/p><strong>不易<\\/strong><\\/div><div class=\"living-index-fishing\"><i><\\/i><p>钓鱼<\\/p><strong>适宜<\\/strong><\\/div><\\/div><\\/div><\\/div><\\/div><section class=\"calendar-module\"><h4 class=\"h2\">天气日历<\\/h4><div class=\"calendar-con\"><div class=\"calendar-date\"><strong class='[^']*'>[^<]*<\\/strong><p class=\"calendar-week\">星期.{3}<\\/p><p class=\"calendar-lunar\"><em>农历<\\/em>([^<]*)<\\/p><p class=\"calendar-year\">(.{6})·(.{3})<strong>&nbsp;&nbsp;(.{6})<\\/strong><\\/p><\\/div><p class=\"calendar-text\">当前为(.{6})节气第([0-9]*)天<br>距离下一个节气(.{6})还有([0-9]*)天<\\/p><ul class=\"calendar-can\"><li class=\"calendar-can-y\"><strong>宜<\\/strong><p>(.*)<\\/p><\\/li><li class=\"calendar-can-n\"><strong>忌<\\/strong><p>(.*)<\\/p><\\/li><\\/ul><ol class=\"calendar-list\"><li><img src=\"\\/\\/static\\.weathercn\\.com\\/1080\\/pro-20221226102938\\/static\\/images\\/calendar\\/constellation-[0-9]*\\.png\"><div><p>(.{6})座<\\/p><span>([0-9]*)月([0-9]*)日-([0-9]*)月([0-9]*)日<\\/span><\\/div><\\/li><\\/ol><\\/div><\\/section>");
    regex_search(Data, Match, Regex);
    cout << Match.str(1) << " " << Match.str(2) << " " << Match.str(3) << "     " << Match.str(4) << "/" << Match.str(5) << " 星期" << Match.str(6) << "     " << Match.str(43) << "·" << Match.str(44) << "  " << Match.str(42) << endl
         << Match.str(46) << "-" << Match.str(47) << "天-今天-" << Match.str(49) << "天-" << Match.str(48) << "     " << Match.str(52) << " " << Match.str(53) << "月" << Match.str(54) << "日~" << Match.str(55) << "月" << Match.str(56) << "日" << endl
         << Match.str(7) << "°C   " << Match.str(11) << "°C~" << Match.str(12) << "°C     " << Match.str(10) << "   " << Match.str(13) << "  \033[1;31m" << Match.str(9) << "\033[0m" << endl
         << Match.str(14) << "：" << Match.str(15) << "\t" << Match.str(16) << "：" << Match.str(17) << "\t" << Match.str(20) << "：" << Match.str(21) << "\t" << Match.str(22) << "：" << Match.str(23) << endl
         << Match.str(18) << "：" << Match.str(19) << "\t" << Match.str(28) << "：" << Match.str(29) << "\t\t" << Match.str(24) << "：" << Match.str(25) << "\t" << Match.str(26) << "：" << Match.str(27) << endl
         << Match.str(30) << "风" << Match.str(31) << "级   " << Match.str(32) << "阵风" << Match.str(33) << "级     日" << Match.str(34) << ":" << Match.str(35) << "~" << Match.str(36) << ":" << Match.str(37) << "   月 " << Match.str(38) << ":" << Match.str(39) << "~" << Match.str(40) << ":" << Match.str(41) << endl;
    vector<string> Temp = StringSpilt(Match.str(50), "&nbsp;");
    cout << "宜：";
    for (auto i : Temp)
        cout << i << " ";
    cout << endl;
    cout << "忌：";
    Temp = StringSpilt(Match.str(51), "&nbsp;");
    for (auto i : Temp)
        cout << i << " ";
    cout << endl;
    return 0;
}
