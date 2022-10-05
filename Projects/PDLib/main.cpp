#include "../../lib/Curl.cpp"
int main()
{
    // while (1)
    // {
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, "");
    HeaderList = curl_slist_append(HeaderList, "Host: wx1.pdlib.com");
    HeaderList = curl_slist_append(HeaderList, "Connection: keep-alive");
    HeaderList = curl_slist_append(HeaderList, "Cache-Control: max-age=0");
    HeaderList = curl_slist_append(HeaderList, "Upgrade-Insecure-Requests: 1");
    HeaderList = curl_slist_append(HeaderList, "User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36 NetType/WIFI MicroMessenger/7.0.20.1781(0x6700143B) WindowsWechat(0x6307062c)");
    HeaderList = curl_slist_append(HeaderList, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9");
    HeaderList = curl_slist_append(HeaderList, "Cookie: JSESSIONID=a1d84402-587f-42ef-be2e-4b54573d74ba; sid=a1d84402-587f-42ef-be2e-4b54573d74ba; JSESSIONID=a1d84402-587f-42ef-be2e-4b54573d74ba; Hm_lvt_65876f79c70a58ea028389d123f46b2d=1663579619; Hm_lpvt_65876f79c70a58ea028389d123f46b2d=1663579801");
    HeaderList = curl_slist_append(HeaderList, "Sec-Fetch-Site: same-origin");
    HeaderList = curl_slist_append(HeaderList, "Sec-Fetch-Mode: navigate");
    HeaderList = curl_slist_append(HeaderList, "Sec-Fetch-User: ?1");
    HeaderList = curl_slist_append(HeaderList, "Sec-Fetch-Dest: document");
    HeaderList = curl_slist_append(HeaderList, "Referer: https://wx1.pdlib.com/pudonglib-weixin/activity/categorylist2");
    HeaderList = curl_slist_append(HeaderList, "Accept-Encoding: gzip, deflate, br");
    HeaderList = curl_slist_append(HeaderList, "Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7");
    GetDataToFile("https://wx1.pdlib.com/pudonglib-weixin/activity/detail?id=3090&src=list", "Header.tmp", "Body.tmp", false, "", HeaderList);
    // }
    return 0;
}