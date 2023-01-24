#include <bits/stdc++.h>
#include <sys/stat.h>
#include "StringOperation.hpp"
using namespace std;
vector<string> ProjectsList = {
    "Achieve3000Download",
    "AirClassroomDownload",
    // "LuoguPlaybackDownloader",
    "MicrosoftShowsDownloader",
    "OJTool" /*,
     "Weather"*/
};
int main()
{
    GetCurrentDir();
    chdir(CurrentDir.c_str());
    OutputSummary("# Test Projects");
    OutputSummary("");
    chdir("Projects");
    for (auto i : ProjectsList)
    {
        cout << "Testing " << i << "... " << endl;
        OutputSummary("### " + i);
        if (chdir(i.c_str()))
        {
            TRIGGER_ERROR("Change dir failed");
        }
        if (system("rm -rf build"))
        {
            TRIGGER_ERROR("Remove dir failed");
        }
        if (mkdir("build", 0755))
        {
            TRIGGER_ERROR("Create dir failed");
        }
        if (chdir("build"))
        {
            TRIGGER_ERROR("Change dir failed");
        }
        system(("cmake -D CMAKE_CXX_FLAGS=-DTEST .. 1> /dev/null 2>" + CurrentDir + "Pipe.out").c_str());
        if (!IfFileExist("Projects/" + i + "/build/Makefile"))
        {
            cout << "CMake failed" << endl;
            OutputSummary("**CMake failed**");
            OutputSummary("```bash");
            OutputSummary(GetDataFromFileToString("Pipe.out"));
            OutputSummary("```");
            OutputSummary("");
            chdir("../..");
            continue;
        }
        system(("make 1> /dev/null 2>" + CurrentDir + "Pipe.out").c_str());
        if (!IfFileExist("Projects/" + i + "/build/main"))
        {
            cout << "Make failed" << endl;
            OutputSummary("**Make failed**");
            OutputSummary("```bash");
            OutputSummary(GetDataFromFileToString("Pipe.out"));
            OutputSummary("```");
            OutputSummary("");
            chdir("../..");
            continue;
        }
        system("./main");
        chdir("../..");
    }
    remove((CurrentDir + "Pipe.out").c_str());
    return 0;
}
// set -gx GITHUB_STEP_SUMMARY "/workspaces/Coding/Test.md"
