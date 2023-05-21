#include "Utilities.hpp"
#include "Logger.hpp"
#include "TestGroup.hpp"
#include <string>
#include <thread>
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

int TEST_GROUP::GetScore() { return Score; }
JUDGE_RESULT TEST_GROUP::GetResult() { return Result; }
int TEST_GROUP::GetTime() { return Time; }
int TEST_GROUP::GetMemory() { return Memory; }

RESULT TEST_GROUP::LoadFromSubmission(std::string SubmissionID, std::string ID)
{
    this->SubmissionID = SubmissionID;
    this->ID = atoi(ID.c_str());
    UpdateWorkDirFromSubmission();
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Score", Score))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Result", (int &)Result))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/TestCasesPassed", TestCasesPassed))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Time", Time))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/TimeSum", TimeSum))
    RETURN_IF_FAILED(Utilities.LoadFile(WorkDir + "/Memory", Memory))
    DIR *Dir = opendir(WorkDir.c_str());
    if (Dir == nullptr)
        CREATE_RESULT(false, "Submission " + SubmissionID + " test group " + ID + " load failed")
    struct dirent *DirEntry;
    while ((DirEntry = readdir(Dir)) != nullptr)
    {
        if (DirEntry->d_type == DT_DIR)
        {
            std::string TestCaseID = DirEntry->d_name;
            if (TestCaseID == "." || TestCaseID == ".." || (TestCaseID != "0" && atoi(TestCaseID.c_str()) == 0))
                continue;
            TEST_CASE TestCase;
            RETURN_IF_FAILED(TestCase.LoadFromSubmission(SubmissionID, ID, TestCaseID))
            TestCases.push_back(TestCase);
        }
    }
    closedir(Dir);
    CREATE_RESULT(true, "Submission " + SubmissionID + " test group " + ID + " loaded")
}
RESULT TEST_GROUP::LoadFromProblem(std::string ProblemID, std::string ID)
{
    this->ProblemID = ProblemID;
    this->ID = atoi(ID.c_str());
    UpdateWorkDirFromProblem();
    DIR *Dir = opendir(WorkDir.c_str());
    if (Dir == nullptr)
        CREATE_RESULT(false, "Problem \"" + ProblemID + "\" test group " + ID + " load failed")
    struct dirent *DirEntry;
    while ((DirEntry = readdir(Dir)) != nullptr)
    {
        if (DirEntry->d_type == DT_DIR)
        {
            std::string TestCaseID = DirEntry->d_name;
            if (TestCaseID == "." || TestCaseID == ".." || (TestCaseID != "0" && atoi(TestCaseID.c_str()) == 0))
                continue;
            TEST_CASE TestCase;
            RETURN_IF_FAILED(TestCase.LoadFromProblem(ProblemID, ID, TestCaseID))
            TestCases.push_back(TestCase);
        }
    }
    closedir(Dir);
    CREATE_RESULT(true, "Problem \"" + ProblemID + "\" test group " + ID + " loaded")
}
RESULT TEST_GROUP::SaveToSubmission()
{
    UpdateWorkDirFromSubmission();
    Utilities.MakeDir(WorkDir);
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Score", Score))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Result", Result))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/TestCasesPassed", TestCasesPassed))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Time", Time))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/TimeSum", TimeSum))
    RETURN_IF_FAILED(Utilities.SaveFile(WorkDir + "/Memory", Memory))
    for (auto i : TestCases)
        RETURN_IF_FAILED(i.SaveToSubmission())
    CREATE_RESULT(true, "Submission " + SubmissionID + " test group " + std::to_string(ID) + " saved")
    // if (!Utilities.SaveFile(WorkDir + "/Score", Score) ||
    //     !Utilities.SaveFile(WorkDir + "/Result", Result) ||
    //     !Utilities.SaveFile(WorkDir + "/TestCasesPassed", TestCasesPassed) ||
    //     !Utilities.SaveFile(WorkDir + "/Time", Time) ||
    //     !Utilities.SaveFile(WorkDir + "/TimeSum", TimeSum) ||
    //     !Utilities.SaveFile(WorkDir + "/Memory", Memory))
    // {
    //     Logger.Error("Submission " + SubmissionID + " test group " + std::to_string(ID) + " save failed");
    //     return false;
    // }
    // for (auto i : TestCases)
    //     if (!i.SaveToSubmission())
    //         return false;
    //     // return true;
}
RESULT TEST_GROUP::SaveToProblem(std::string ProblemID)
{
    this->ProblemID = ProblemID;
    UpdateWorkDirFromProblem();
    RETURN_IF_FAILED(Utilities.MakeDir(WorkDir))
    for (auto i : TestCases)
        RETURN_IF_FAILED(i.SaveToProblem(ProblemID, std::to_string(ID)))
    CREATE_RESULT(true, "Problem \"" + ProblemID + "\" test group " + std::to_string(ID) + " saved")
}
void TEST_GROUP::AddTestCase(std::string Input, std::string Answer, int TimeLimit, int MemoryLimit, int Score)
{
    TEST_CASE TestCase(TestCases.size(), std::to_string(ID), Input, Answer, IOFileName, SubmissionID, TimeLimit, MemoryLimit, Score);
    TestCases.push_back(TestCase);
}
RESULT TEST_GROUP::UpdateWorkDirFromSubmission()
{
    WorkDir = Settings.GetSubmissionBaseFolder() + "/" + SubmissionID + "/" + std::to_string(ID);
    RETURN_IF_FAILED(Utilities.MakeDir(WorkDir))
    Logger.SetLogFileName(WorkDir + "/Log.log");
    for (size_t i = 0; i < TestCases.size(); i++)
    {
        TestCases[i].SubmissionID = SubmissionID;
        TestCases[i].TestGroupID = std::to_string(ID);
        RETURN_IF_FAILED(TestCases[i].UpdateWorkDirFromSubmission())
    }
    CREATE_RESULT(true, "Submission " + SubmissionID + " test group " + std::to_string(ID) + " working directory updated")
}
RESULT TEST_GROUP::UpdateWorkDirFromProblem()
{
    WorkDir = Settings.GetProblemBaseFolder() + "/" + ProblemID + "/TestGroups/" + std::to_string(ID);
    RETURN_IF_FAILED(Utilities.MakeDir(WorkDir))
    Logger.SetLogFileName(WorkDir + "/Log.log");
    for (size_t i = 0; i < TestCases.size(); i++)
    {
        TestCases[i].ProblemID = ProblemID;
        TestCases[i].TestGroupID = std::to_string(ID);
        TestCases[i].UpdateWorkDirFromProblem();
    }
    CREATE_RESULT(true, "Problem \"" + ProblemID + "\" test group " + std::to_string(ID) + " working directory updated")
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
    std::mutex Mutex;
    // std::vector<std::thread> Threads;
    for (size_t i = 0; i < TestCases.size(); i++)
    {
        // Threads.push_back(std::thread(
        // [this, i, &Mutex]()
        // {
        TestCases[i].Judge();
        // Mutex.lock();
        if (TestCases[i].GetResult() == JUDGE_RESULT::ACCEPTED)
            TestCasesPassed++;
        Score += TestCases[i].GetScore();
        ResultCount[TestCases[i].GetResult()]++;
        Time = std::max(Time, TestCases[i].GetTime());
        TimeSum += TestCases[i].GetTime();
        Memory = std::max(Memory, TestCases[i].GetMemory());
        // Mutex.unlock();
        // }));
    }
    // for (size_t i = 0; i < Threads.size(); i++)
    //     Threads[i].join();

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
}

RESULT TEST_GROUP::Judge()
{
    RETURN_IF_FAILED(Utilities.MakeDir(WorkDir))

    RunTestCases();

    CREATE_RESULT(true, "Test group " + std::to_string(ID) + " of submission " + SubmissionID + " judged")
}
