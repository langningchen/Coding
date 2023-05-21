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

RESULT PROBLEM::Load(std::string ID)
{
    this->ID = ID;
    UpdateWorkDir();
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Title", Title))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Description", Description))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Input", Input))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Output", Output))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Range", Range))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Hint", Hint))
    RETURN_IF_FAILED(LoadSamples(ID))
    RETURN_IF_FAILED(LoadTestGroups(ID))

    this->ID = ID;
    RETURN_IF_FAILED(UpdateWorkDir())

    CREATE_RESULT(true, "Problem \"" + ID + "\" loaded")
}
RESULT PROBLEM::Save(){
    RETURN_IF_FAILED(UpdateWorkDir())
        RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Title", Title))
            RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Description", Description))
                RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Input", Input))
                    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Output", Output))
                        RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Range", Range))
                            RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Hint", Hint))
                                RETURN_IF_FAILED(SaveSamples())
                                    RETURN_IF_FAILED(SaveTestGroups())
                                        CREATE_RESULT(true, "Problem \"" + ID + "\" saved")} RESULT PROBLEM::LoadSamples(std::string ID)
{
    std::string CurrentSampleBaseFolder = Settings.GetProblemBaseFolder() + "/" + ID + "/Samples";
    DIR *Dir = opendir(CurrentSampleBaseFolder.c_str());
    if (Dir == nullptr)
    {
        Logger.Error("Problem \"" + ID + "\" samples load failed");
        CREATE_RESULT(false, "Problem \"" + ID + "\" samples load failed")
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
            RETURN_IF_FAILED(Utilities.LoadFile(CurrentSampleBaseFolder + "/" + SampleID + "/Input", Sample.Input))
            RETURN_IF_FAILED(Utilities.LoadFile(CurrentSampleBaseFolder + "/" + SampleID + "/Output", Sample.Output))
            RETURN_IF_FAILED(Utilities.LoadFile(CurrentSampleBaseFolder + "/" + SampleID + "/Description", Sample.Description))
            Samples.push_back(Sample);
        }
    }
    closedir(Dir);
    CREATE_RESULT(true, "Problem \"" + ID + "\" samples loaded")
}
RESULT PROBLEM::SaveSamples()
{
    std::string CurrentSampleBaseFolder = Settings.GetProblemBaseFolder() + "/" + ID + "/Samples";
    RETURN_IF_FAILED(Utilities.MakeDir(CurrentSampleBaseFolder))
    DIR *Dir = opendir(CurrentSampleBaseFolder.c_str());
    if (Dir == nullptr)
    {
        Logger.Error("Problem \"" + ID + "\" samples save failed");
        CREATE_RESULT(false, "Problem \"" + ID + "\" samples save failed")
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
            RETURN_IF_FAILED(Utilities.LoadFile(CurrentSampleBaseFolder + "/" + SampleID + "/Input", Sample.Input))
            RETURN_IF_FAILED(Utilities.LoadFile(CurrentSampleBaseFolder + "/" + SampleID + "/Output", Sample.Output))
            RETURN_IF_FAILED(Utilities.LoadFile(CurrentSampleBaseFolder + "/" + SampleID + "/Description", Sample.Description))
            Samples.push_back(Sample);
        }
    }
    closedir(Dir);
    CREATE_RESULT(true, "Problem \"" + ID + "\" samples saved")
}
RESULT PROBLEM::LoadTestGroups(std::string ID)
{
    std::string CurrentTestGroupBaseFolder = Settings.GetProblemBaseFolder() + "/" + ID + "/TestGroups";
    DIR *Dir = opendir(CurrentTestGroupBaseFolder.c_str());
    if (Dir == nullptr)
    {
        Logger.Warning("Problem \"" + ID + "\" test groups load failed");
        CREATE_RESULT(false, "Problem \"" + ID + "\" test groups load failed")
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
            RETURN_IF_FAILED(TestGroup.LoadFromProblem(ID, TestGroupID))
            TestGroups.push_back(TestGroup);
        }
    }
    closedir(Dir);
    CREATE_RESULT(true, "Problem \"" + ID + "\" test groups loaded")
}
RESULT PROBLEM::SaveTestGroups()
{
    std::string CurrentTestGroupBaseFolder = Settings.GetProblemBaseFolder() + "/" + ID + "/TestGroups";
    for (auto i : TestGroups)
        RETURN_IF_FAILED(i.SaveToProblem(ID))
    CREATE_RESULT(true, "Problem \"" + ID + "\" test groups saved")
}
void PROBLEM::Update(std::string ID, std::string Title, std::string Description, std::string Input, std::string Output, std::vector<SAMPLE> Samples, std::string Range, std::string Hint)
{
        this->ID = ID;
        this->Title = Title;
        this->Description = Description;
        this->Input = Input;
        this->Output = Output;
        this->Samples = Samples;
        this->Range = Range;
        this->Hint = Hint;
        UpdateWorkDir();
}
RESULT PROBLEM::UpdateWorkDir()
{
        WorkDir = Settings.GetProblemBaseFolder() + "/" + ID;
        RETURN_IF_FAILED(Utilities.MakeDir(WorkDir))
        Logger.SetLogFileName(WorkDir + "/Log.log");
        CREATE_RESULT(true, "Problem \"" + ID + "\" work dir updated");
}
void PROBLEM::SetTestGroups(std::vector<TEST_GROUP> TestGroups)
{
        for (size_t i = 0; i < TestGroups.size(); i++)
        TestGroups[i].ID = i;
        this->TestGroups = TestGroups;
}

bool PROBLEM::operator<(const PROBLEM &Compare) const
{
    return ID < Compare.ID;
}
