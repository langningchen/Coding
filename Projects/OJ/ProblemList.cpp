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

bool PROBLEM_LIST::Load()
{
    Logger.SetLogFileName(Settings.GetBaseFolder() + "/ProblemList.log");
    DIR *Dir = opendir(Settings.GetProblemBaseFolder().c_str());
    if (Dir == nullptr)
    {
        Logger.Error("Problems load failed");
        return false;
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
            if (Temp.Load(ProblemID))
                AddProblem(Temp);
        }
    }
    return true;
}
bool PROBLEM_LIST::GetProblem(std::string ProblemID, PROBLEM &Result)
{
    std::set<PROBLEM>::iterator TempResult;
    if (!GetProblemPointer(ProblemID, TempResult))
    {
        Logger.Warning("Problem \"" + ProblemID + "\" not found");
        return false;
    }
    Result = *TempResult;
    return true;
}
bool PROBLEM_LIST::AddProblem(PROBLEM Problem)
{
    std::set<PROBLEM>::iterator Temp;
    if (GetProblemPointer(Problem.ID, Temp))
    {
        Logger.Warning("Problem \"" + Problem.ID + "\" already exists");
        return false;
    }
    if (!Problem.Save())
        return false;
    Problems.insert(Problem);
    Logger.Info("Problem \"" + Problem.ID + "\" added");
    return true;
}
bool PROBLEM_LIST::RemoveProblem(std::string ProblemID)
{
    std::set<PROBLEM>::iterator Problem;
    if (!GetProblemPointer(ProblemID, Problem))
    {
        Logger.Warning("Problem \"" + ProblemID + "\" not found");
        return false;
    }
    if (!Utilities.RemoveDir(Settings.GetProblemBaseFolder() + "/" + ProblemID))
        return false;
    Problems.erase(Problem);
    Logger.Info("Problem \"" + ProblemID + "\" removed");
    return true;
}
bool PROBLEM_LIST::UpdateProblem(PROBLEM Problem)
{
    std::set<PROBLEM>::iterator Temp;
    if (!GetProblemPointer(Problem.ID, Temp))
    {
        Logger.Warning("Problem \"" + Problem.ID + "\" not found");
        return false;
    }
    RemoveProblem(Problem.ID);
    AddProblem(Problem);
    Logger.Info("Problem \"" + Problem.ID + "\" updated");
    return true;
}

PROBLEM_LIST ProblemList;
