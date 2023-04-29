#include "Problem.hpp"
#include "TestGroup.hpp"
#include "Utilities.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

using namespace std::literals::string_literals;

PROBLEM::PROBLEM() {}
PROBLEM::~PROBLEM() {}

std::string PROBLEM::GetID() { return ID; }
std::string PROBLEM::GetMD()
{
    auto FixLeadingAndTrailingSpaces = [](std::string Data) -> std::string
    {
        while (Data[0] == ' ' || Data[0] == '\t' || Data[0] == '\r' || Data[0] == '\n')
            Data.erase(Data.begin());
        while (Data[Data.size() - 1] == ' ' || Data[Data.size() - 1] == '\t' || Data[Data.size() - 1] == '\r' || Data[Data.size() - 1] == '\n')
            Data.erase(Data.end() - 1);
        return Data;
    };
    std::string OutputString = "# " + ID + " " + Title + "\n" +
                               "\n" +
                               "## Description\n" +
                               "\n" +
                               FixLeadingAndTrailingSpaces(Description) + "\n" +
                               "\n" +
                               "## Input\n" +
                               "\n" +
                               FixLeadingAndTrailingSpaces(Input) + "\n" +
                               "\n" +
                               "## Output\n" +
                               "\n" +
                               FixLeadingAndTrailingSpaces(Output) + "\n" +
                               "\n" +
                               "## Samples\n" +
                               "\n";
    int SampleCount = 0;
    for (auto Sample : Samples)
    {
        SampleCount++;
        OutputString += "### Sample " + std::to_string(SampleCount) + "\n" +
                        "\n" +
                        "#### Input\n" +
                        "\n" +
                        "```\n" +
                        FixLeadingAndTrailingSpaces(Sample.GetInput()) + "\n" +
                        "```\n" +
                        "\n" +
                        "#### Output\n" +
                        "\n" +
                        "```\n" +
                        FixLeadingAndTrailingSpaces(Sample.GetOutput()) + "\n" +
                        "```\n" +
                        "\n";
        if (Sample.GetDescription() != "")
            OutputString += "#### Description\n" +
                            FixLeadingAndTrailingSpaces(Sample.GetDescription()) + "\n" +
                            "\n";
    }
    if (Range != "")
        OutputString += "## Range\n"s +
                        "\n" +
                        FixLeadingAndTrailingSpaces(Range) + "\n" +
                        "\n";
    if (Hint != "")
        OutputString += "## Hint\n"s +
                        "\n" +
                        FixLeadingAndTrailingSpaces(Hint) + "\n" +
                        "\n";
    return OutputString;
}
std::vector<TEST_GROUP> PROBLEM::GetTestGroups()
{
    return TestGroups;
}

bool PROBLEM::Load(std::string ID)
{
    this->ID = ID;
    UpdateWorkDir();
    if (!Utilities.LoadFile(WorkDir + "/Title", Title) ||
        !Utilities.LoadFile(WorkDir + "/Description", Description) ||
        !Utilities.LoadFile(WorkDir + "/Input", Input) ||
        !Utilities.LoadFile(WorkDir + "/Output", Output) ||
        !Utilities.LoadFile(WorkDir + "/Range", Range) ||
        !Utilities.LoadFile(WorkDir + "/Hint", Hint) ||
        !LoadSamples(ID) ||
        !LoadTestGroups(ID))
    {
        Logger.Error("Problem \"" + ID + "\" load failed");
        return false;
    }

    this->ID = ID;
    UpdateWorkDir();
    Logger.Info("Problem \"" + ID + "\" loaded");
    return true;
}
bool PROBLEM::Save()
{
    if (!Utilities.MakeDir(WorkDir.c_str()))
        return false;
    if (!Utilities.SaveFile(WorkDir + "/Title", Title) ||
        !Utilities.SaveFile(WorkDir + "/Description", Description) ||
        !Utilities.SaveFile(WorkDir + "/Input", Input) ||
        !Utilities.SaveFile(WorkDir + "/Output", Output) ||
        !Utilities.SaveFile(WorkDir + "/Range", Range) ||
        !Utilities.SaveFile(WorkDir + "/Hint", Hint) ||
        !SaveSamples() ||
        !SaveTestGroups())
    {
        Logger.Error("Problem \"" + ID + "\" save failed");
        return false;
    }
    Logger.Info("Problem \"" + ID + "\" saved");
    return true;
}
bool PROBLEM::LoadSamples(std::string ID)
{
    std::string CurrentSampleBaseFolder = Settings.GetProblemBaseFolder() + "/" + ID + "/Samples";
    DIR *Dir = opendir(CurrentSampleBaseFolder.c_str());
    if (Dir == nullptr)
    {
        Logger.Warning("Problem \"" + ID + "\" samples load failed");
        return false;
    }
    struct dirent *DirEntry;
    while ((DirEntry = readdir(Dir)) != nullptr)
    {
        if (DirEntry->d_type == DT_DIR)
        {
            std::string SampleID = DirEntry->d_name;
            if (SampleID == "." || SampleID == ".." || (SampleID != "0" && atoi(SampleID.c_str()) == 0))
                continue;
            SAMPLE Sample;
            if (!Utilities.LoadFile(CurrentSampleBaseFolder + "/" + SampleID + "/Input", Sample.Input) ||
                !Utilities.LoadFile(CurrentSampleBaseFolder + "/" + SampleID + "/Output", Sample.Output) ||
                !Utilities.LoadFile(CurrentSampleBaseFolder + "/" + SampleID + "/Description", Sample.Description))
            {
                Logger.Warning("Problem \"" + ID + "\" sample \"" + SampleID + "\" load failed");
                return false;
            }
        }
    }
    closedir(Dir);
    Logger.Info("Problem \"" + ID + "\" samples loaded");
    return true;
}
bool PROBLEM::SaveSamples()
{
    std::string CurrentSampleBaseFolder = Settings.GetProblemBaseFolder() + "/" + ID + "/Samples";
    if (!Utilities.MakeDir(CurrentSampleBaseFolder))
        return false;
    DIR *Dir = opendir(CurrentSampleBaseFolder.c_str());
    if (Dir == nullptr)
    {
        Logger.Warning("Problem \"" + ID + "\" samples save failed");
        return false;
    }
    struct dirent *DirEntry;
    while ((DirEntry = readdir(Dir)) != nullptr)
    {
        if (DirEntry->d_type == DT_DIR)
        {
            std::string SampleID = DirEntry->d_name;
            if (SampleID == "." || SampleID == ".." || (SampleID != "0" && atoi(SampleID.c_str()) == 0))
                continue;
            SAMPLE Sample;
            if (!Utilities.SaveFile(CurrentSampleBaseFolder + "/" + SampleID + "/Input", Sample.Input) ||
                !Utilities.SaveFile(CurrentSampleBaseFolder + "/" + SampleID + "/Output", Sample.Output) ||
                !Utilities.SaveFile(CurrentSampleBaseFolder + "/" + SampleID + "/Description", Sample.Description))
            {
                Logger.Warning("Problem \"" + ID + "\" sample \"" + SampleID + "\" load failed");
                return false;
            }
            Logger.Debug("Problem \"" + ID + "\" sample \"" + SampleID + "\" loaded");
        }
    }
    closedir(Dir);
    Logger.Info("Problem \"" + ID + "\" samples saved");
    return true;
}
bool PROBLEM::LoadTestGroups(std::string ID)
{
    std::string CurrentTestGroupBaseFolder = Settings.GetProblemBaseFolder() + "/" + ID + "/TestGroups";
    DIR *Dir = opendir(CurrentTestGroupBaseFolder.c_str());
    if (Dir == nullptr)
    {
        Logger.Warning("Problem \"" + ID + "\" test groups load failed");
        return false;
    }
    struct dirent *DirEntry;
    while ((DirEntry = readdir(Dir)) != nullptr)
    {
        if (DirEntry->d_type == DT_DIR)
        {
            std::string TestGroupID = DirEntry->d_name;
            if (TestGroupID == "." || TestGroupID == ".." || (TestGroupID != "0" && atoi(TestGroupID.c_str()) == 0))
                continue;
            TEST_GROUP TestGroup;
            if (!TestGroup.LoadFromProblem(ID, TestGroupID))
                return false;
            TestGroups.push_back(TestGroup);
        }
    }
    closedir(Dir);
    Logger.Info("Problem \"" + ID + "\" test groups loaded");
    return true;
}
bool PROBLEM::SaveTestGroups()
{
    std::string CurrentTestGroupBaseFolder = Settings.GetProblemBaseFolder() + "/" + ID + "/TestGroups";
    if (!Utilities.MakeDir(CurrentTestGroupBaseFolder))
        return false;
    for (auto i : TestGroups)
    {
        if (!i.SaveToProblem(ID))
        {
            Logger.Warning("Problem \"" + ID + "\" test group " + std::to_string(i.ID) + " save failed");
            return false;
        }
    }
    Logger.Info("Problem \"" + ID + "\" test groups saved");
    return true;
}
void PROBLEM::Update(std::string ID, std::string Title, std::string Description, std::string Input, std::string Output, std::vector<SAMPLE> Samples, std::string Range, std::string Hint, std::string IOFileName)
{
    this->ID = ID;
    this->Title = Title;
    this->Description = Description;
    this->Input = Input;
    this->Output = Output;
    this->Samples = Samples;
    this->Range = Range;
    this->Hint = Hint;
    this->IOFileName = IOFileName;
    UpdateWorkDir();
}
void PROBLEM::UpdateWorkDir()
{
    WorkDir = Settings.GetProblemBaseFolder() + "/" + ID;
    Utilities.MakeDir(WorkDir);
    Logger.SetLogFileName(WorkDir + "/Log.log");
    Logger.Info("Problem \"" + ID + "\" work dir updated");
}
void PROBLEM::SetTestGroups(std::vector<TEST_GROUP> TestGroups)
{
    for (size_t i = 0; i < TestGroups.size(); i++)
    {
        TestGroups[i].ID = i;
        TestGroups[i].IOFileName = IOFileName;
        TestGroups[i].UpdateIOFileName();
    }
    this->TestGroups = TestGroups;
    Logger.Info("Problem \"" + ID + "\" test groups updated");
}

bool PROBLEM::operator<(const PROBLEM &Compare) const
{
    return ID < Compare.ID;
}
