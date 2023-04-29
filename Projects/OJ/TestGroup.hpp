#ifndef TEST_GROUP_HPP
#define TEST_GROUP_HPP

#include "TestCase.hpp"
#include "Logger.hpp"
#include <vector>
#include <map>

class TEST_GROUP
{
private:
    int ID = 0;
    int Score = 0;
    JUDGE_RESULT Result = JUDGE_RESULT::UNKNOWN_ERROR;
    std::string SubmissionID;
    std::vector<TEST_CASE> TestCases;
    int TestCasesPassed = 0;
    std::string IOFileName;
    std::string WorkDir;
    int ResultCount[JUDGE_RESULT::REJECTED] = {0};
    int Time = 0;
    int TimeSum = 0;
    int Memory = 0;
    LOGGER Logger;

    friend class WEB_DATA_PROCEED;
    friend class PROBLEM;
    friend class SUBMISSION;

public:
    TEST_GROUP();
    TEST_GROUP(const TEST_GROUP &Other);
    ~TEST_GROUP();

    int GetID();
    int GetScore();
    JUDGE_RESULT GetResult();
    std::string GetSubmissionID();
    std::vector<TEST_CASE> GetTestCases();
    int GetTestCasesPassed();
    std::string GetIOFileName();
    JUDGE_RESULT GetJudgeResult();
    int GetTime();
    int GetTimeSum();
    int GetMemory();

    bool LoadFromSubmission(std::string SubmissionID, std::string ID);
    bool LoadFromProblem(std::string ProblemID, std::string ID);
    bool SaveToSubmission();
    bool SaveToProblem(std::string ProblemID);
    void AddTestCase(std::string Input, std::string Answer, int TimeLimit, int MemoryLimit, int Score);
    void UpdateWorkDir();
    void UpdateIOFileName();
    void UpdateAllResults(JUDGE_RESULT Result);

    void RunTestCases();

    void Judge();
};

#endif
