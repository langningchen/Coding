#include "Problem.hpp"
#include "ProblemList.hpp"
#include "Settings.hpp"
#include "Utilities.hpp"
#include <dirent.h>
#include <sys/stat.h>

bool PROBLEM_LIST::GetProblemPointer(std::string ProblemID, std::set<PROBLEM>::iterator &Result)
{
    for (auto i = Problems.begin(); i != Problems.end(); i++)
        if (i->ID == ProblemID)
        {
            Result = i;
            return true;
        }
    return false;
}

PROBLEM_LIST::PROBLEM_LIST() {}
PROBLEM_LIST::~PROBLEM_LIST() {}

RESULT PROBLEM_LIST::Load()
{
    Logger.SetLogFileName(Settings.GetBaseFolder() + "/ProblemList.log");
    DIR *Dir = opendir(Settings.GetProblemBaseFolder().c_str());
    if (Dir == nullptr)
    {
        Logger.Error("Problems load failed");
        CREATE_RESULT(false, "Problems load failed")
    }
    struct dirent *DirEntry;
    while ((DirEntry = readdir(Dir)) != nullptr)
    {
        if (DirEntry->d_type == DT_DIR)
        {
            std::string ProblemID = DirEntry->d_name;
            if (ProblemID == "." || ProblemID == "..")
                continue;
            PROBLEM Temp;
            RETURN_IF_FAILED(Temp.Load(ProblemID))
            Problems.insert(Temp);
        }
    }
    closedir(Dir);
        CREATE_RESULT(true, "Problems loaded")
}
RESULT PROBLEM_LIST::Save()
{
    for (auto i : Problems)
        RETURN_IF_FAILED(i.Save())
        CREATE_RESULT(true, "Problems saved")
}
RESULT PROBLEM_LIST::GetProblem(std::string ProblemID, PROBLEM &Result)
{
    std::set<PROBLEM>::iterator TempResult;
    if (!GetProblemPointer(ProblemID, TempResult))
    {
        Logger.Warning("Problem \"" + ProblemID + "\" not found");
        CREATE_RESULT(false, "Problem \"" + ProblemID + "\" not found")
    }
    Result = *TempResult;
        CREATE_RESULT(true, "Problem \"" + ProblemID + "\" found")
}
RESULT PROBLEM_LIST::AddProblem(PROBLEM Problem)
{
    std::set<PROBLEM>::iterator Temp;
    if (GetProblemPointer(Problem.ID, Temp))
    {
        Logger.Warning("Problem \"" + Problem.ID + "\" already exists");
        CREATE_RESULT(false, "Problem \"" + Problem.ID + "\" already exists")
    }
    Problems.insert(Problem);
        CREATE_RESULT(true, "Problem \"" + Problem.ID + "\" added")
}
RESULT PROBLEM_LIST::RemoveProblem(std::string ProblemID)
{
    std::set<PROBLEM>::iterator Problem;
    if (!GetProblemPointer(ProblemID, Problem))
    {
        Logger.Warning("Problem \"" + ProblemID + "\" not found");
        CREATE_RESULT(false, "Problem \"" + ProblemID + "\" not found")
    }
    Problems.erase(Problem);
        CREATE_RESULT(true, "Problem \"" + ProblemID + "\" removed")
}
RESULT PROBLEM_LIST::UpdateProblem(PROBLEM Problem)
{
    std::set<PROBLEM>::iterator Temp;
    if (!GetProblemPointer(Problem.ID, Temp))
    {
        Logger.Warning("Problem \"" + Problem.ID + "\" not found");
        CREATE_RESULT(false, "Problem \"" + Problem.ID + "\" not found")
    }
    Problems.erase(Temp);
    Problems.insert(Problem);
        CREATE_RESULT(true, "Problem \"" + Problem.ID + "\" updated")
}

PROBLEM_LIST ProblemList;
