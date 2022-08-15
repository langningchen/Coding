#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#define SE                                                   \
    {                                                        \
        for (unsigned int i = 0; i < TestPoints.size(); i++) \
            TestPoints[i].Status = "SE";                     \
        Status = (Status == 3 ? 4 : 3);                      \
        return;                                              \
    }
using namespace std;
class JUDGE
{
private:
    int Status = 0;

public:
    struct TESTPOINT
    {
        string StanderdInput = "";
        string StanderdOutput = "";
        string UserOutput = "";
        int MemoryLimit = 128 * 1024;
        int MemoryUsed = 0;
        int TimeLimit = 1000;
        int TimeUsed = 0;
        string Status = "UKE";
    };
    int Score = 0;
    string SourceCode = "";
    string IOFileName = "";
    string JudegeFolderName = "";
    string StanderdInputFileName = "Answer.in";
    string StanderdOutputFileName = "Answer.ans";
    string UserOutputFileName = "Answer.out";
    string SourceCodeName = "main.cpp";
    vector<TESTPOINT> TestPoints;
    void Init();
    void Compile();
    void Judge();
    void Clean();
};
void JUDGE::Init()
{
    if (Status != 0)
        SE;
    struct timeval TimeVal;
    struct timezone TimeZone;
    if (gettimeofday(&TimeVal, &TimeZone) != 0)
        SE;
    JudegeFolderName = to_string(TimeVal.tv_sec * 1000000 + TimeVal.tv_usec);
    if (mkdir(JudegeFolderName.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) != 0)
        SE;
    if (chdir(JudegeFolderName.c_str()) != 0)
        SE;
    FILE *SourceOutputFilePointer = fopen(SourceCodeName.c_str(), "w");
    if (SourceOutputFilePointer == NULL)
        SE;
    if (fprintf(SourceOutputFilePointer, "%s", SourceCode.c_str()) < 0)
        SE;
    if (fclose(SourceOutputFilePointer) != 0)
        SE;
    Status = 1;
}
void JUDGE::Compile()
{
    if (Status != 1)
        SE;
    Status = 2;
}
void JUDGE::Judge()
{
    if (Status != 2)
        SE;
    for (unsigned int i = 0; i < TestPoints.size(); i++)
    {
        rlimit Limit;
        Limit.rlim_cur = TestPoints[i].MemoryLimit;
        Limit.rlim_max = TestPoints[i].MemoryLimit;
        if (setrlimit(RLIMIT_AS, &Limit) != 0)
            SE;
    }
    Status = 3;
}
void JUDGE::Clean()
{
    if (Status != 3)
        SE;
    if (remove(SourceCodeName.c_str()) != 0)
        SE;
    if (chdir("..") != 0)
        SE;
    if (rmdir(JudegeFolderName.c_str()) != 0)
        SE;
    Status = 4;
}
int main()
{
    FILE *fp = popen("ping www.baidu.com", "r");
    while (!feof(fp))
        cout << fgetc(fp);
    pclose(fp);
    return 0;
    JUDGE JudgeStatus;
    JudgeStatus.SourceCode = R"(#include <bits/stdc++.h>
using namespace std;
int main()
{
    cout << "Hello World" << endl;
    return 0;
})";
    JUDGE::TESTPOINT Temp;
    Temp.StanderdOutput = "Hello World";
    JudgeStatus.TestPoints.push_back(Temp);
    JudgeStatus.Init();
    JudgeStatus.Compile();
    JudgeStatus.Judge();
    JudgeStatus.Clean();
    for (unsigned int i = 0; i < JudgeStatus.TestPoints.size(); i++)
        cout << JudgeStatus.TestPoints[i].Status << " " << JudgeStatus.TestPoints[i].MemoryUsed << " " << JudgeStatus.TestPoints[i].TimeUsed << endl;
    return 0;
}