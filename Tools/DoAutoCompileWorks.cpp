#include <iostream>
#include <fstream>
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
set<string> ExcludeFolderName;
int ThreadFinish;
bool IsFileExists(string FileName)
{
    struct stat Temp;
    return stat(FileName.c_str(), &Temp) == 0;
}
void StringReplaceAll(string &Data, string Before, string After)
{
    size_t FindPos = 0;
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
        FILE *PipePointer = popen(string("gcc " + SourceFileName + " -o " + DestFileName + " -O2 -lstdc++ -lm -lpthread 2>&1").c_str(), "r");
        while (!feof(PipePointer))
            CompileOutput.push_back(fgetc(PipePointer));
        while (CompileOutput.size() != 0 && (CompileOutput[CompileOutput.size() - 1] == '\r' || CompileOutput[CompileOutput.size() - 1] == '\n' || CompileOutput[CompileOutput.size() - 1] == 0 || CompileOutput[CompileOutput.size() - 1] == -1))
            CompileOutput.erase(CompileOutput.size() - 1, 1);
        if (!IsFileExists(DestFileName))
        {
            SumaryList.push_back("### File " + SourceFileName + " compile failed!");
            SumaryList.push_back("");
            SumaryList.push_back("<pre><code>");
            SumaryList.push_back(CompileOutput);
            SumaryList.push_back("</code></pre>");
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
            if (ExcludeFolderName.count(FolderName) == 0)
            {
                set<string> Temp = GetFiles(Path + "/" + DirentPointer->d_name);
                FileList.insert(Temp.begin(), Temp.end());
            }
        }
    }
    closedir(DirPointer);
    return FileList;
}
void Init()
{
    ExcludeFolderName.insert(".");
    ExcludeFolderName.insert("..");
    ExcludeFolderName.insert(".git");
    ExcludeFolderName.insert(".github");
    ExcludeFolderName.insert(".vscode");
    ExcludeFolderName.insert("lib");
    ExcludeFolderName.insert("Tools");
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
    Init();
    int BufferSize = 1024;
    char *Buffer = new char[BufferSize];
    readlink("/proc/self/exe", Buffer, BufferSize);
    string CurrentDir = Buffer;
    delete Buffer;
    CurrentDir.erase(CurrentDir.find_last_of("/"), CurrentDir.npos);
    CurrentDir.erase(CurrentDir.find_last_of("/"), CurrentDir.npos);
    set<string> FileList = GetFiles(CurrentDir);
    int Counter = 0;
    for (set<string>::iterator sit = FileList.begin(); sit != FileList.end(); sit++)
    {
        size_t PointPos;
        if ((PointPos = sit->find_last_of(".")) == sit->npos || PointPos == 0)
            remove(sit->c_str());
        else
        {
            string AfterPoint = sit->substr(PointPos + 1, sit->npos);
            if (AfterPoint == "cpp" && *sit != "./DoAutoCompileWorks.cpp" && *sit != "./Tool.cpp" && *sit != "./gugugu.cpp" && *sit != "./Captcha.cpp")
            {
                CompileList.insert(*sit);
                ThreadCompileList[Counter % ThreadCount].insert(*sit);
                Counter++;
            }
            else if ((sit->find("Etiger") != sit->npos && (AfterPoint == "in" || AfterPoint == "out" || AfterPoint == "md")) ||
                     (sit->find("Luogu") != sit->npos && (AfterPoint == "md")))
                remove(sit->c_str());
        }
    }

    if (system(string("find " + CurrentDir + " -wholename \"" + CurrentDir + "/Etiger/*.cpp\" -print | zip " + CurrentDir + "/Etiger -@").c_str()))
        cout << "\"zip\" Error!" << endl;
    if (system(string("find " + CurrentDir + " -wholename \"" + CurrentDir + "/Luogu/*.cpp\" -print | zip " + CurrentDir + "/Luogu -@").c_str()))
        cout << "\"zip\" Error!" << endl;

    for (int i = 0; i < ThreadCount; i++)
        ThreadList[i] = thread(Compile, i);
    do
    {
        cout << "(" << (CompiledList.size() - CompileFailList.size()) << "+" << CompileFailList.size() << "=" << CompiledList.size() << ")/" << CompileList.size() << "=" << fixed << setprecision(3) << CompiledList.size() * 100.0 / CompileList.size() << "%" << endl;
        usleep(1000000);
    } while (ThreadFinish != ThreadCount);
    for (int i = 0; i < ThreadCount; i++)
        ThreadList[i].join();

    if (system("git config --global user.email \"langningc2009@163.com\""))
        cout << "\"git config\" Error!" << endl;
    if (system("git config --global user.name \"Langning Chen\""))
        cout << "\"git config\" Error!" << endl;

    if (system("git add ."))
        cout << "\"git add\" Error!" << endl;
    if (system("git commit -m \"Auto Commit By Auto Compile Script\""))
        cout << "\"git commit\" Error!" << endl;
    if (system("git push"))
        cout << "\"git push\" Error!" << endl;

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
        OutputSumary(*sit + "|" + (CompiledList.count(*sit) ? "Yes" : "**❌No❌**") + "|" + (!CompileFailList.count(*sit) ? "Yes" : "**❌No❌**"));
    OutputSumary("");

    ofstream OutputMailStream("mail.txt");
    OutputMailStream << "Action Runs End, Tips From Github Actions" << endl;
    for (vector<string>::iterator vit = SumaryList.begin(); vit != SumaryList.end(); vit++)
        OutputMailStream << *vit << endl;
    OutputMailStream.close();
    return 0;
}
