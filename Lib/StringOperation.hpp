#include <string>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <assert.h>
#include "Exception.hpp"
#ifdef TEST
#define VAR_DUMP(e) cout << #e << "=" << e << endl
#define SPILT_LINE cout << endl                                     \
                        << "------------------------------" << endl \
                        << endl
#define REPORT_POSITION                         \
    cout << "Report current position: " << endl \
         << "File: " << __FILE__ << endl        \
         << "Line: " << __LINE__ << endl        \
         << "Function: " << __func__ << endl;
#endif
using namespace std;
string CurrentDir;
void GetCurrentDir()
{
    int BufferSize = 1024;
    char *Buffer = new char[BufferSize];
    memset(Buffer, 0, sizeof(char) * BufferSize);
    if (readlink("/proc/self/exe", Buffer, BufferSize) == 0)
    {
        TRIGGER_ERROR("Can not read current file location");
    }
    CurrentDir = Buffer;
    delete Buffer;
    CurrentDir.erase(CurrentDir.find("Coding/") + 7, string::npos);
}
string StringReplaceAll(string Data, string Before, string After)
{
    size_t Index = 0;
    while ((Index = Data.find(Before)) != string::npos)
        Data.replace(Index, Before.size(), After);
    return Data;
}
string StringReplaceAllNoLoop(string Data, string Before, string After)
{
    string Identifier = "${TEMP" + to_string(time(NULL)) + "}";
    Data = StringReplaceAll(Data, Before, Identifier);
    Data = StringReplaceAll(Data, Identifier, After);
    return Data;
}
string GetStringBetween(string Data, string Start, string End)
{
    int StartPos = Data.find(Start);
    if (StartPos == -1)
        return "";
    StartPos += Start.size();
    int EndPos = Data.find(End, StartPos + 1);
    if (EndPos == -1)
        return "";
    return Data.substr(StartPos, EndPos - StartPos);
}
vector<string> StringSpilt(string Input, string Seperator)
{
    Input += Seperator;
    vector<string> Output;
    size_t Last = 0;
    for (size_t i = 0; i < Input.size() - Seperator.size() + 1; i++)
        if (Input.substr(i, Seperator.size()) == Seperator)
        {
            Output.push_back(Input.substr(Last, i - Last));
            i += Seperator.size();
            Last = i;
            i--;
        }
    return Output;
}
bool IfFileExist(string FileName)
{
    if (CurrentDir == "")
        GetCurrentDir();
    ifstream InputFileStream(CurrentDir + FileName);
    if (InputFileStream.bad() || !InputFileStream.is_open())
        return false;
    InputFileStream.close();
    return true;
}
string GetDataFromFileToString(string FileName = "Body.tmp")
{
    if (CurrentDir == "")
        GetCurrentDir();
    string Data = "";
    FILE *FilePointer = fopen((CurrentDir + FileName).c_str(), "r");
    if (FilePointer == NULL)
    {
        TRIGGER_ERROR("Cannot open input file: " + FileName);
    }
    while (!feof(FilePointer))
        Data.push_back(fgetc(FilePointer));
    fclose(FilePointer);
    while (Data.size() > 0 && (Data[Data.size() - 1] == 0x00 || Data[Data.size() - 1] == 0xFF || Data[Data.size() - 1] == -1 || Data[Data.size() - 1] == '\r' || Data[Data.size() - 1] == '\n'))
        Data.erase(Data.size() - 1);
    return Data;
}
void SetDataFromStringToFile(string FileName, string Data)
{
    if (CurrentDir == "")
        GetCurrentDir();
    FILE *FilePointer = fopen((CurrentDir + FileName).c_str(), "w");
    if (FilePointer == NULL)
    {
        TRIGGER_ERROR("Cannot open output file: " + FileName);
    }
    for (auto i : Data)
        fputc(i, FilePointer);
    fclose(FilePointer);
}
string FixString(string Data)
{
    return (Data[Data.size() - 1] == '\n' || Data[Data.size() - 1] == '\r' || Data[Data.size() - 1] == ' ' ? FixString(Data.erase(Data.size() - 1, 1)) : Data);
}
void OutputSummary(string Data)
{
    Data = StringReplaceAll(Data, "\n", "\\n");
    Data = StringReplaceAll(Data, "\t", "\\t");
    Data = StringReplaceAll(Data, "\r", "\\r");
    Data = StringReplaceAllNoLoop(Data, "`", "\\`");
    Data = StringReplaceAllNoLoop(Data, "\"", "\\\"");
    if (system(string("echo \"" + Data + "\" >> $GITHUB_STEP_SUMMARY").c_str()))
    {
        TRIGGER_ERROR("Output Github summary failed");
    }
}
