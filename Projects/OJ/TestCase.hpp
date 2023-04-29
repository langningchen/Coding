#ifndef TEST_CASE_HPP
#define TEST_CASE_HPP

#include "Settings.hpp"
#include "JudgeResult.hpp"
#include "Logger.hpp"
#include <string>

class TEST_CASE
{
private:
    int ID = 0;
    pid_t PID = 0;
    std::string Input;
    std::string Output;
    std::string Answer;
    std::string StandardOutput;
    std::string StandardError;
    std::string IOFileName;
    std::string SubmissionID;
    std::string TestGroupID;
    std::string WorkDir;
    JUDGE_RESULT Result = JUDGE_RESULT::UNKNOWN_ERROR;
    std::string Description;
    int Time = 0;
    int TimeLimit = 0;
    int Memory = 0;
    int MemoryLimit = 0;
    int Score = 0;
    int SystemCallCount[Settings.SystemCallCount] = {0};
    LOGGER Logger;

    bool RedirectIO();
    bool SetupEnvrionment();
    bool RemoveEnvrionment();
    bool ChangeUser();
    bool SetLimits();
    void ChildProcess();
    bool CheckSignal();
    bool CheckMemory();
    bool CheckSystemCall();
    void ParentProcess();
    void Run();
    void Compare();

    friend class TEST_GROUP;
    friend class WEB_DATA_PROCEED;

public:
    TEST_CASE();
    TEST_CASE(const TEST_CASE &Copy);
    TEST_CASE(int ID, std::string TestGroupID,
              std::string Input, std::string Answer,
              std::string IOFileName, std::string SubmissionID,
              int TimeLimit, int MemoryLimit, int Score);
    ~TEST_CASE();

    JUDGE_RESULT GetResult();
    std::string GetDescription();
    std::string GetInput();
    std::string GetAnswer();
    int GetTime();
    int GetMemory();
    int GetScore();

    bool LoadFromSubmission(std::string SubmissionID, std::string TestGroupID, std::string ID);
    bool LoadFromProblem(std::string ProblemID, std::string TestGroupID, std::string ID);
    bool SaveToSubmission();
    bool SaveToProblem(std::string ProblemID, std::string TestGroupID);
    void UpdateWorkDir();
    void Judge();
};

struct TEST_CASE_DATA
{
    JUDGE_RESULT Result = JUDGE_RESULT::UNKNOWN_ERROR;
    char Description[256] = {0};
    int Time = 0;
    int TimeLimit = 0;
    int Memory = 0;
    int MemoryLimit = 0;
    int Score = 0;
};

#endif
