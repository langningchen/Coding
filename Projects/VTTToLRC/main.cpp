#include "../../Lib/Curl.hpp"
#include <dirent.h>
string VTTToLRC(string Input)
{
    vector<string> Lines = StringSpilt(Input, "\n");
    bool SkipOne = false;
    string Output = "";
    for (auto i : Lines)
    {
        if (i == "")
            continue;
        if (SkipOne)
        {
            SkipOne = false;
            continue;
        }
        if (i == "WEBVTT")
        {
            SkipOne = true;
            continue;
        }
        if (i.find("-->") != string::npos)
            Output += "[" + GetStringBetween(i, "", " --> ") + "]";
        else
            Output += i + "\n";
    }
    return Output;
}
int main()
{
    const string Path = "/mnt/d/05_coding/03_github/2022universe/Day2";
    DIR *DirPointer = opendir(Path.c_str());
    dirent *DirentPointer = NULL;
    while ((DirentPointer = readdir(DirPointer)) != NULL)
    {
        if (DirentPointer->d_type == DT_REG)
        {
            string FileName = DirentPointer->d_name;
            size_t tmp = FileName.find_last_of(".");
            if (tmp == string::npos)
                continue;
            if (FileName.substr(tmp + 1) == "vtt")
            {
                FileName = FileName.substr(0, tmp);
                SetDataFromStringToFile("../../../.." + Path + "/" + FileName + ".lrc",
                                        VTTToLRC(GetDataFromFileToString("../../../.." + Path + "/" + FileName + ".vtt")));
                cout << FileName << endl;
            }
        }
    }
    closedir(DirPointer);
    return 0;
}