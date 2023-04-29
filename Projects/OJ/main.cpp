#include "WebDataProceed.hpp"
#include "Socket.hpp"
#include "ProblemList.hpp"
#include "Submission.hpp"
#include "JudgingList.hpp"
#include "unistd.h"
#include "HTTPRequest.hpp"
#include "Utilities.hpp"

LOGGER Logger;

void AddProblem()
{
    PROBLEM TestProblem;
    std::vector<SAMPLE> SampleList;
    SampleList.push_back(SAMPLE("1 2", "3", ""));
    TestProblem.Update("1000", "Add", "Add two numbers", "two numbers", "one number", SampleList, "1<=a,b<=1000", "", "Add");
    std::vector<TEST_GROUP> TestGroups;
    TEST_GROUP TestGroup1;
    TestGroup1.AddTestCase("1 2", "3", 1000, 1024 * 1024 * 1024, 100);
    TestGroup1.AddTestCase("2 3", "5", 1000, 1024 * 1024 * 1024, 100);
    TestGroup1.AddTestCase("23 27", "50", 1000, 1024 * 1024 * 1024, 100);
    TestGroup1.AddTestCase("20 09", "29", 1000, 1024 * 1024 * 1024, 100);
    TestGroup1.AddTestCase("01 17", "18", 1000, 1024 * 1024 * 1024, 100);
    TestGroup1.AddTestCase("45 22", "67", 1000, 1024 * 1024 * 1024, 100);
    TestGroup1.AddTestCase("99 99", "198", 1000, 1024 * 1024 * 1024, 100);
    TestGroup1.AddTestCase("465 546", "1011", 1000, 1024 * 1024 * 1024, 100);
    TestGroup1.AddTestCase("123 456", "579", 1000, 1024 * 1024 * 1024, 100);
    TestGroup1.AddTestCase("877 479", "1356", 1000, 1024 * 1024 * 1024, 100);
    TestGroups.push_back(TestGroup1);
    TEST_GROUP TestGroup2;
    TestGroup2.AddTestCase("2147483648 2147483648", "4294967296", 1000, 1024 * 1024 * 1024, 100);
    TestGroup2.AddTestCase("6567867981 5617998756", "12185866737", 1000, 1024 * 1024 * 1024, 100);
    TestGroup2.AddTestCase("1234567890 9876543210", "11111111100", 1000, 1024 * 1024 * 1024, 100);
    TestGroup2.AddTestCase("1357924680 2468013579", "3825938259", 1000, 1024 * 1024 * 1024, 100);
    TestGroup2.AddTestCase("1122334455 6677889900", "7800224355", 1000, 1024 * 1024 * 1024, 100);
    TestGroups.push_back(TestGroup2);
    TEST_GROUP TestGroup3;
    TestGroup3.AddTestCase("1 -1", "0", 1000, 1024 * 1024 * 1024, 100);
    TestGroup3.AddTestCase("2 -3", "-1", 1000, 1024 * 1024 * 1024, 100);
    TestGroup3.AddTestCase("23 -27", "-4", 1000, 1024 * 1024 * 1024, 100);
    TestGroup3.AddTestCase("20 -09", "11", 1000, 1024 * 1024 * 1024, 100);
    TestGroup3.AddTestCase("01 -17", "-16", 1000, 1024 * 1024 * 1024, 100);
    TestGroup3.AddTestCase("45 -22", "23", 1000, 1024 * 1024 * 1024, 100);
    TestGroup3.AddTestCase("99 -99", "0", 1000, 1024 * 1024 * 1024, 100);
    TestGroup3.AddTestCase("465 -546", "-81", 1000, 1024 * 1024 * 1024, 100);
    TestGroup3.AddTestCase("123 -456", "-333", 1000, 1024 * 1024 * 1024, 100);
    TestGroup3.AddTestCase("877 -479", "398", 1000, 1024 * 1024 * 1024, 100);
    TestGroups.push_back(TestGroup3);
    TEST_GROUP TestGroup4;
    TestGroup4.AddTestCase("2147483647 -2147483647", "0", 1000, 1024 * 1024 * 1024, 100);
    TestGroup4.AddTestCase("6567867981 -5617998756", "949869225", 1000, 1024 * 1024 * 1024, 100);
    TestGroup4.AddTestCase("1234567890 -9876543210", "-8641975320", 1000, 1024 * 1024 * 1024, 100);
    TestGroup4.AddTestCase("1357924680 -2468013579", "-1110088899", 1000, 1024 * 1024 * 1024, 100);
    TestGroup4.AddTestCase("1122334455 -6677889900", "-5555555445", 1000, 1024 * 1024 * 1024, 100);
    TestGroups.push_back(TestGroup4);
    // TEST_GROUP TestGroup5; // WA
    // TestGroup5.AddTestCase("1 1", "3", 1000, 1024 * 1024 * 1024, 100);
    // TestGroups.push_back(TestGroup5);
    // TEST_GROUP TestGroup6; // TLE
    // TestGroup6.AddTestCase("1 2", "3", 1, 1024 * 1024 * 1024, 100);
    // TestGroups.push_back(TestGroup6);
    // TEST_GROUP TestGroup7; // MLE
    // TestGroup7.AddTestCase("1 2", "3", 1000, 1, 100);
    // TestGroups.push_back(TestGroup7);
    TestProblem.SetTestGroups(TestGroups);
    Logger.Debug(TestProblem.GetTestGroups()[0].GetTestCases()[0].GetInput());
    ProblemList.AddProblem(TestProblem);
}
void Test1()
{
    SUBMISSION(R"(#include <bits/stdc++.h>
// #include </etc/passwd>
using namespace std;
void HackUser()
{
    ifstream Temp("/etc/passwd");
    if (!Temp.is_open())
        exit(errno);
    string s;
    getline(Temp, s);
    cout << s << endl;
}
void HackSystem()
{
    system("pwd");
}
void NoFileIO()
{
    int a, b;
    cin >> a >> b;
    cout << a + b << endl;
}
void Normal()
{
    freopen("Add.in", "r", stdin);
    freopen("Add.out", "w", stdout);
    NoFileIO();
}
void StdError()
{
    Normal();
    cerr << "hhh" << endl;
}
int main()
{
    // HackUser();
    // HackSystem();
    // NoFileIO();
    // StdError();
    Normal();
    return 0;
})",
               "1000")
        .Judge();
}

int main()
{
    // Settings.CheckSettings();
    // PROBLEM Problem;
    // Problem.Load("1000");
    // ProblemList.Load();
    // AddProblem();
    // Settings.Save();
    // return 0;

    Settings.Load("Judger");
    Settings.CheckSettings();
    ProblemList.Load();
    JudgingList.Init();
    Utilities.Init();

    new SOCKET(
        [](std::string RequestHTTPData) -> std::string
        {
            WEB_DATA_PROCEED Data;
            return Data.Proceed(HTTP_REQUEST(RequestHTTPData)).Stringify();
        });
    return 0;
}

/*
clear;
rm -f Log.log;
make;
while true;
if [ (echo (sudo netstat -anp | grep ":80")) = "" ];
break;
end;
sleep 0.5;
end;
echo "Start running program...";
sudo ./main;
cat Log.log;
*/
