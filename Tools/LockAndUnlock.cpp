#include <iostream>
#include <dirent.h>
#include <string>
using namespace std;
#define KEY 0x7F
string Locked = ".encrypted";
void LockAndUnlock(string InputFileName)
{
    string OutputFileName;
    if (InputFileName.substr(InputFileName.size() - Locked.size(), InputFileName.npos) == Locked)
        OutputFileName = InputFileName.substr(0, InputFileName.size() - Locked.size());
    else
        OutputFileName = InputFileName + Locked;
    cout << InputFileName << " --> " << OutputFileName << " ...   ";
    FILE *InputFilePointer = fopen(InputFileName.c_str(), "rb");
    if (InputFilePointer == NULL)
    {
        cout << "\33[91m[\33[4;91mERROR\33[0;91m]\33[0m" << endl;
        cout << "\33[91mCan not open input file \"" << InputFileName << "\"\33[0m" << endl;
        return;
    }
    FILE *OutputFilePointer = fopen(OutputFileName.c_str(), "wb");
    if (OutputFilePointer == NULL)
    {
        cout << "\33[91m[\33[4;91mERROR\33[0;91m]\33[0m" << endl;
        cout << "\33[91mCan not open output file \"" << OutputFileName << "\"\33[0m" << endl;
        fclose(InputFilePointer);
        return;
    }
    char Temp;
    Temp = fgetc(InputFilePointer);
    while (!feof(InputFilePointer))
    {
        fputc(Temp, OutputFilePointer);
        Temp = fgetc(InputFilePointer) ^ KEY;
    }
    fclose(InputFilePointer);
    fclose(OutputFilePointer);
    remove(InputFileName.c_str());
    cout << "\33[92m[\33[4;92mOK\33[0;92m]\33[0m" << endl;
}
void GetFiles(string Path)
{
    DIR *DirPointer = opendir(Path.c_str());
    if (DirPointer == NULL)
    {
        cout << "Can not open the dir " << Path << endl;
        return;
    }
    dirent *DirentPointer = readdir(DirPointer);
    while (DirentPointer != NULL)
    {
        if (DirentPointer->d_type == DT_REG)
            LockAndUnlock(Path + "/" + DirentPointer->d_name);
        else if (DirentPointer->d_type == DT_DIR)
            if (string(DirentPointer->d_name) != "." && string(DirentPointer->d_name) != "..")
                GetFiles(Path + "/" + DirentPointer->d_name);
        DirentPointer = readdir(DirPointer);
    }
    closedir(DirPointer);
}
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        cout << "Please input a folder name: ";
        string s;
        cin >> s;
        GetFiles(s);
    }
    else if (argc > 1)
        for (int i = 1; i < argc; i++)
            LockAndUnlock(argv[i]);
    cout << "Finish" << endl;
    return 0;
}