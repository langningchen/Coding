#include <iostream>
#include <iomanip>
#include <string>
#include <set>
#include <thread>
#include <vector>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
using namespace std;
const int ThreadCount = 16;
set<string> ThreadCompileList[ThreadCount];
thread ThreadList[ThreadCount];
set<string> CompileList;
set<string> CompiledList;
set<string> CompileFailList;
vector<string> SumaryList;
int ThreadFinish;
bool IsFileExists(string FileName)
{
    struct stat Temp;
    return stat(FileName.c_str(), &Temp) == 0;
}
void StringReplaceAll(string &Data, string Before, string After)
{
    int FindPos = 0;
    while ((FindPos = Data.find(Before)) != Data.npos)
        Data.replace(FindPos, Before.size(), After);
}
void Compile(int ID)
{
    while (!ThreadCompileList[ID].empty())
    {
        string SourceFileName = *ThreadCompileList[ID].begin();
        ThreadCompileList[ID].erase(ThreadCompileList[ID].begin());
        string DestFileName = SourceFileName.substr(0, SourceFileName.size() - 4);
        string CompileOutput = "";
        FILE *PipePointer = popen(string("gcc " + SourceFileName + " -o " + DestFileName + " -O2 -lstdc++ -lm 2>&1").c_str(), "r");
        while (!feof(PipePointer))
            CompileOutput.push_back(fgetc(PipePointer));
        while (CompileOutput.size() != 0 && (CompileOutput[CompileOutput.size() - 1] == '\r' || CompileOutput[CompileOutput.size() - 1] == '\n' || CompileOutput[CompileOutput.size() - 1] == 0 || CompileOutput[CompileOutput.size() - 1] == -1))
            CompileOutput.erase(CompileOutput.size() - 1, 1);
        if (!IsFileExists(DestFileName))
        {
            SumaryList.push_back("### File " + SourceFileName + " compile failed!");
            SumaryList.push_back("");
            SumaryList.push_back("```");
            SumaryList.push_back(CompileOutput);
            SumaryList.push_back("```");
            SumaryList.push_back("");
            CompileFailList.insert(SourceFileName);
        }
        CompiledList.insert(SourceFileName);
    }
    ThreadFinish++;
}
set<string> GetFiles(string Path)
{
    set<string> FileList;
    DIR *DirPointer = opendir(Path.c_str());
    dirent *DirentPointer = NULL;
    while ((DirentPointer = readdir(DirPointer)) != NULL)
    {
        if (DirentPointer->d_type == DT_REG)
        {
            FileList.insert(Path + "/" + DirentPointer->d_name);
        }
        else if (DirentPointer->d_type == DT_DIR)
        {
            string FolderName = DirentPointer->d_name;
            if (FolderName != "." && FolderName != ".." && FolderName != "lib" && FolderName != "unfinish" && FolderName[0] != '.' && FolderName != "Tools")
            {
                set<string> Temp = GetFiles(Path + "/" + DirentPointer->d_name);
                FileList.insert(Temp.begin(), Temp.end());
            }
        }
    }
    closedir(DirPointer);
    return FileList;
}
void OutputSumary(string Data)
{
    StringReplaceAll(Data, "\n", "\\n");
    StringReplaceAll(Data, "\t", "\\t");
    StringReplaceAll(Data, "\r", "\\r");
    if (system(string("echo \"" + Data + "\" >> $GITHUB_STEP_SUMMARY").c_str()))
        cout << "Output Error" << endl;
}
int main()
{
    set<string> FileList = GetFiles(".");
    int Counter = 0;
    for (set<string>::iterator sit = FileList.begin(); sit != FileList.end(); sit++)
    {
        int PointPos;
        if ((PointPos = sit->find_last_of(".")) == sit->npos || PointPos == 0)
            remove(sit->c_str());
        else
        {
            string AfterPoint = sit->substr(PointPos + 1, sit->npos);
            if (AfterPoint == "cpp" && *sit != "./DoAutoCompileWorks.cpp")
            {
                CompileList.insert(*sit);
                ThreadCompileList[Counter % ThreadCount].insert(*sit);
                Counter++;
            }
            else if ((AfterPoint == "in" || AfterPoint == "out" || AfterPoint == "txt") && sit->find("Etiger") != sit->npos)
                remove(sit->c_str());
        }
    }
    for (int i = 0; i < ThreadCount; i++)
        ThreadList[i] = thread(Compile, i);
    do
    {
        cout << "(" << (CompiledList.size() - CompileFailList.size()) << "+" << CompileFailList.size() << "=" << CompiledList.size() << ")/" << CompileList.size() << "=" << fixed << setprecision(3) << CompiledList.size() * 100.0 / CompileList.size() << "%" << endl;
        usleep(1000000);
    } while (ThreadFinish != ThreadCount);
    for (int i = 0; i < ThreadCount; i++)
        ThreadList[i].join();

    OutputSumary("# Work Sumary");
    OutputSumary("");

    OutputSumary("## Size");
    OutputSumary("");
    OutputSumary("- Compile Size: " + to_string(CompileList.size()));
    OutputSumary("- Compiled Size: " + to_string(CompiledList.size()));
    OutputSumary("- Compile Success Size: " + to_string(CompiledList.size() - CompileFailList.size()));
    OutputSumary("- Compile Failed Size: " + to_string(CompileFailList.size()));
    OutputSumary("");

    OutputSumary("## Errors");
    for (vector<string>::iterator vit = SumaryList.begin(); vit != SumaryList.end(); vit++)
        OutputSumary(*vit);
    if (SumaryList.size() == 0)
        OutputSumary("None");
    OutputSumary("");

    OutputSumary("## Detail");
    OutputSumary("");
    OutputSumary("FileName|Compiled|Success");
    OutputSumary(":---|:---:|:---:");
    for (set<string>::iterator sit = CompileList.begin(); sit != CompileList.end(); sit++)
        OutputSumary(*sit + "|" + (CompiledList.count(*sit) ? "Yes" : "<font color=\"red\">**No**</font>") + "|" + (!CompileFailList.count(*sit) ? "Yes" : "<font color=\"red\">**No**</font>"));
    OutputSumary("");
    return 0;
}
