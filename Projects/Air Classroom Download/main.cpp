#include "../../Lib/Curl.cpp"
string LoginURL = "https://cas2.edu.sh.cn/CAS/login?service=https%3A%2F%2Fsmilelogin.shec.edu.cn%2Fsmile-login%2Fauth%2Fcas%2Flogin%3Ftarget%3Dhttps%3A%2F%2Fsmile.shec.edu.cn%2F%3Fpath%3DairClassroomPage";
int main()
{
    int HTTPResponseCode = 0;
    GetDataToFile(LoginURL, "Header.tmp", "Body.tmp", false, "", NULL, &HTTPResponseCode);
    if (HTTPResponseCode == 200)
    {
        GetDataToFile(LoginURL, "Header.tmp", "Body.tmp", true, "username=" + GetDataFromFileToString("../../Keys/IDCardNumber") + "&password=" + GetDataFromFileToString("../../Keys/CASPassword") + "&role=1001&openid=&execution=" + GetStringBetween(GetDataFromFileToString(), "<input type=\"hidden\" id=\"execution_id\" name=\"execution\" value=\"", "\"") + "&checkFlag=temp&_eventId=submit", NULL, &HTTPResponseCode, "application/x-www-form-urlencoded");
        if (HTTPResponseCode != 302)
        {
            cout << "登录失败，用户名或密码错误" << endl;
            return 0;
        }
    }
    string RedirectURL = Find302Location();
    GetDataToFile(RedirectURL);
    json ClassesRequest;
    ClassesRequest["start"] = 1;
    ClassesRequest["length"] = 1;
    ClassesRequest["showNotStudy"] = 1;
    ClassesRequest["sectionId"] = 2;
    ClassesRequest["smileSubjectId"] = "";
    ClassesRequest["gradeId"] = "8";
    ClassesRequest["semesterNo"] = "1";
    GetDataToFile("https://smile.shec.edu.cn/smile-index-service/api/index/registerResource/pageResource", "Header.tmp", "Body.tmp", true, ClassesRequest.dump());
    json Classes = json::parse(GetDataFromFileToString());
    ClassesRequest["length"] = atoi(Classes["data"]["total"].as_string().c_str());
    GetDataToFile("https://smile.shec.edu.cn/smile-index-service/api/index/registerResource/pageResource", "Header.tmp", "Body.tmp", true, ClassesRequest.dump());
    Classes = json::parse(GetDataFromFileToString());
    queue<pair<string, string>> VideoList;
    for (auto i : Classes["data"]["list"])
        VideoList.push(make_pair(i["subjectName"].as_string() + "_" + i["finalPremiereTime"].as_string() + "_" + i["unitName"].as_string() + "_" + i["name"].as_string() + ".mp4", i["encryptUrl"].as_string()));
    int Size = VideoList.size();
    while (!VideoList.empty())
    {
        if (Size - VideoList.size() > 80)
        {
            cout << Size - VideoList.size() << "/" << Size << endl
                 << endl
                 << VideoList.front().first << endl
                 << VideoList.front().second << endl;
            system(string("\"/mnt/c/Program Files (x86)/Internet Download Manager/idman.exe\" /d \"" + VideoList.front().second + "\" /p \"D:\" /f \"" + VideoList.front().first + "\"").c_str());
            sleep(13);
        }
        VideoList.pop();
        system("clear");
    }
    return 0;
}
