#include "Utilities.hpp"
#include "Logger.hpp"
#include "TestGroup.hpp"
#include <string>
#include <algorithm>
#include <dirent.h>

TEST_GROUP::TEST_GROUP() {}
TEST_GROUP::TEST_GROUP(const TEST_GROUP &Other)
{
    ID = Other.ID;
    Score = Other.Score;
    Result = Other.Result;
    SubmissionID = Other.SubmissionID;
    TestCases = Other.TestCases;
    TestCasesPassed = Other.TestCasesPassed;
    IOFileName = Other.IOFileName;
    WorkDir = Other.WorkDir;
    for (int i = JUDGE_RESULT::UNKNOWN_ERROR; i <= JUDGE_RESULT::REJECTED; i++)
        ResultCount[i] = Other.ResultCount[i];
    Time = Other.Time;
    TimeSum = Other.TimeSum;
    Memory = Other.Memory;
    Logger = Other.Logger;
}
TEST_GROUP::~TEST_GROUP() {}

int TEST_GROUP::GetID() { return ID; }
int TEST_GROUP::GetScore() { return Score; }
JUDGE_RESULT TEST_GROUP::GetResult() { return Result; }
std::string TEST_GROUP::GetSubmissionID() { return SubmissionID; }
std::vector<TEST_CASE> TEST_GROUP::GetTestCases() { return TestCases; }
int TEST_GROUP::GetTestCasesPassed() { return TestCasesPassed; }
std::string TEST_GROUP::GetIOFileName() { return IOFileName; }
JUDGE_RESULT TEST_GROUP::GetJudgeResult() { return Result; }
int TEST_GROUP::GetTime() { return Time; }
int TEST_GROUP::GetTimeSum() { return TimeSum; }
int TEST_GROUP::GetMemory() { return Memory; }

bool TEST_GROUP::LoadFromSubmission(std::string SubmissionID, std::string ID)
{
    this->SubmissionID = SubmissionID;
    this->ID = atoi(ID.c_str());
    UpdateWorkDir();
    if (!Utilities.LoadFile(WorkDir + "/Score", Score) ||
        !Utilities.LoadFile(WorkDir + "/Result", (int &)Result) ||
        !Utilities.LoadFile(WorkDir + "/TestCasesPassed", TestCasesPassed) ||
        !Utilities.LoadFile(WorkDir + "/Time", Time) ||
        !Utilities.LoadFile(WorkDir + "/TimeSum", TimeSum) ||
        !Utilities.LoadFile(WorkDir + "/Memory", Memory))
    {
        Logger.Warning("Submission " + SubmissionID + " test group " + ID + " load failed1");
        return false;
    }
    DIR *Dir = opendir(WorkDir.c_str());
    if (Dir == nullptr)
    {
        Logger.Warning("Submission " + SubmissionID + " test group " + ID + " load failed2");
        return false;
    }
    struct dirent *DirEntry;
    while ((DirEntry = readdir(Dir)) != nullptr)
    {
        if (DirEntry->d_type == DT_DIR)
        {
            std::string TestCaseID = DirEntry->d_name;
            if (TestCaseID == "." || TestCaseID == ".." || (TestCaseID != "0" && atoi(TestCaseID.c_str()) == 0))
                continue;
            TEST_CASE TestCase;
            if (!TestCase.LoadFromSubmission(SubmissionID, ID, TestCaseID))
                return false;
            TestCases.push_back(TestCase);
        }
    }
    closedir(Dir);
    Logger.Info("Submission " + SubmissionID + " test group " + ID + " loaded");
    return true;
}
bool TEST_GROUP::LoadFromProblem(std::string ProblemID, std::string ID)
{
    std::string CurrentTestGroupBaseFolder = Settings.GetProblemBaseFolder() + "/" + ProblemID + "/TestGroups/" + ID;
    DIR *Dir = opendir(CurrentTestGroupBaseFolder.c_str());
    if (Dir == nullptr)
    {
        Logger.Warning("Problem \"" + ProblemID + "\" test group " + ID + " load failed");
        return false;
    }
    struct dirent *DirEntry;
    while ((DirEntry = readdir(Dir)) != nullptr)
    {
        if (DirEntry->d_type == DT_DIR)
        {
            std::string TestCaseID = DirEntry->d_name;
            if (TestCaseID == "." || TestCaseID == ".." || (TestCaseID != "0" && atoi(TestCaseID.c_str()) == 0))
                continue;
            TEST_CASE TestCase;
            if (!TestCase.LoadFromProblem(ProblemID, ID, TestCaseID))
                return false;
            TestCases.push_back(TestCase);
        }
    }
    closedir(Dir);
    Logger.Info("Problem \"" + ProblemID + "\" test groups loaded");
    return true;
}
bool TEST_GROUP::SaveToSubmission()
{
    Utilities.MakeDir(WorkDir);
    if (!Utilities.SaveFile(WorkDir + "/Score", Score) ||
        !Utilities.SaveFile(WorkDir + "/Result", Result) ||
        !Utilities.SaveFile(WorkDir + "/TestCasesPassed", TestCasesPassed) ||
        !Utilities.SaveFile(WorkDir + "/Time", Time) ||
        !Utilities.SaveFile(WorkDir + "/TimeSum", TimeSum) ||
        !Utilities.SaveFile(WorkDir + "/Memory", Memory))
    {
        Logger.Warning("Submission " + SubmissionID + " test group " + std::to_string(ID) + " save failed");
        return false;
    }
    for (auto i : TestCases)
        if (!i.SaveToSubmission())
            return false;
    Logger.Info("Submission " + SubmissionID + " test group " + std::to_string(ID) + " saved");
    return true;
}
bool TEST_GROUP::SaveToProblem(std::string ProblemID)
{
    std::string CurrentTestGroupBaseFolder = Settings.GetProblemBaseFolder() + "/" + ProblemID + "/TestGroups/" + std::to_string(ID);
    if (!Utilities.MakeDir(CurrentTestGroupBaseFolder))
        return false;
    for (auto i : TestCases)
        if (!i.SaveToProblem(ProblemID, std::to_string(ID)))
        {
            Logger.Warning("Problem \"" + ProblemID + "\" test group " + std::to_string(ID) + " test case " + std::to_string(i.ID) + " save failed");
            return false;
        }
    Logger.Info("Problem \"" + ProblemID + "\" test groups saved");
    return true;
}
void TEST_GROUP::AddTestCase(std::string Input, std::string Answer, int TimeLimit, int MemoryLimit, int Score)
{
    TEST_CASE TestCase(TestCases.size(), std::to_string(ID), Input, Answer, IOFileName, SubmissionID, TimeLimit, MemoryLimit, Score);
    TestCases.push_back(TestCase);
}
void TEST_GROUP::UpdateWorkDir()
{
    WorkDir = Settings.GetSubmissionBaseFolder() + "/" + SubmissionID + "/" + std::to_string(ID);
    if (!Utilities.MakeDir(WorkDir))
        Logger.Error("Can not remake work dir \"" + WorkDir + "\"");
    else
        Logger.SetLogFileName(WorkDir + "/Log.log");
    Logger.Info("Test group " + std::to_string(ID) + " of submission " + SubmissionID + " working directory updated to \"" + WorkDir + "\"");

    for (size_t i = 0; i < TestCases.size(); i++)
    {
        TestCases[i].SubmissionID = SubmissionID;
        TestCases[i].TestGroupID = std::to_string(ID);
        TestCases[i].UpdateWorkDir();
    }
}
void TEST_GROUP::UpdateIOFileName()
{
    for (size_t i = 0; i < TestCases.size(); i++)
        TestCases[i].IOFileName = IOFileName;
}
void TEST_GROUP::UpdateAllResults(JUDGE_RESULT Result)
{
    this->Result = Result;
    for (size_t i = 0; i < TestCases.size(); i++)
        TestCases[i].Result = Result;
}

void TEST_GROUP::RunTestCases()
{
    for (size_t i = 0; i < TestCases.size(); i++)
    {
        Logger.Info("Test case " + std::to_string(i + 1) + " of " + std::to_string(TestCases.size()));
        TestCases[i].Judge();
        if (TestCases[i].GetResult() == JUDGE_RESULT::ACCEPTED)
            TestCasesPassed++;
        Score += TestCases[i].GetScore();
        ResultCount[TestCases[i].GetResult()]++;
        Logger.Info("Result: " + GetJudgeResultColorString(TestCases[i].GetResult()) + "  " + TestCases[i].GetDescription() + "  " + std::to_string(TestCases[i].GetTime()) + "ms  " + std::to_string(TestCases[i].GetMemory()) + "b");
        Time = std::max(Time, TestCases[i].GetTime());
        TimeSum += TestCases[i].GetTime();
        Memory = std::max(Memory, TestCases[i].GetMemory());
    }

    int MaxCount = 0;
    JUDGE_RESULT MaxResult = JUDGE_RESULT::UNKNOWN_ERROR;
    int SecondMaxCount = 0;
    JUDGE_RESULT SecondMaxResult = JUDGE_RESULT::UNKNOWN_ERROR;
    for (size_t i = 0; i < JUDGE_RESULT::REJECTED; i++)
        if (ResultCount[i] > MaxCount)
        {
            SecondMaxCount = MaxCount;
            SecondMaxResult = MaxResult;
            MaxCount = ResultCount[i];
            MaxResult = (JUDGE_RESULT)i;
        }
        else if (ResultCount[i] > SecondMaxCount)
        {
            SecondMaxCount = ResultCount[i];
            SecondMaxResult = (JUDGE_RESULT)i;
        }
    Result = (SecondMaxCount == 0 || MaxResult != JUDGE_RESULT::ACCEPTED) ? MaxResult : SecondMaxResult;
    Logger.Debug("Max result: " + GetJudgeResultColorString(MaxResult) + "  " + std::to_string(MaxCount));
    Logger.Debug("Second max result: " + GetJudgeResultColorString(SecondMaxResult) + "  " + std::to_string(SecondMaxCount));
}

void TEST_GROUP::Judge()
{
    if (!Utilities.MakeDir(WorkDir))
    {
        for (size_t i = 0; i < TestCases.size(); i++)
        {
            UpdateAllResults(JUDGE_RESULT::SYSTEM_ERROR);
            TestCases[i].Description = "Can not remake working directory";
        }
        goto Exit;
    }

    Logger.Info("Start judging test group " + std::to_string(ID) + " of submission " + SubmissionID);
    RunTestCases();
    Logger.Info("");
    Logger.Info("Pass count: " + std::to_string(TestCasesPassed));
    Logger.Info("Score: " + std::to_string(Score));
    Logger.Info("Judge result: " + GetJudgeResultColorString(Result));
    Logger.Info("Time: " + std::to_string(Time) + "ms");
    Logger.Info("Time sum: " + std::to_string(TimeSum) + "ms");
    Logger.Info("Memory: " + std::to_string(Memory) + "b");

Exit:
    SaveToSubmission();
}
