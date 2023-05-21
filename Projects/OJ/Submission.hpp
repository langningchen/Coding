#ifndef SUBMISSION_HPP
#define SUBMISSION_HPP

#include "TestGroup.hpp"
#include "Problem.hpp"
#include "Logger.hpp"
#include <vector>

class SUBMISSION
{
private:
    int ID = 0;
    int PID = 0;
    int Score = 0;
    int TestGroupsPassed = 0;
    std::string WorkDir;
    std::string Source;
    std::string ProblemID;
    PROBLEM Problem;
    JUDGE_RESULT Result = JUDGE_RESULT::UNKNOWN_ERROR;
    std::string Description;
    std::vector<TEST_GROUP> TestGroups;
    int ResultCount[JUDGE_RESULT::REJECTED] = {0};
    int Time = 0;
    int TimeSum = 0;
    int Memory = 0;
    bool EnableO2 = false;
    LOGGER Logger;

    RESULT UpdateWorkDir();
    void UpdateAllResults(JUDGE_RESULT Result);
    void CopyTestGroups();
    RESULT RedirectIO();
    RESULT SetupEnvrionment();
    RESULT RemoveEnvrionment();
    RESULT ChangeUser();
    RESULT SetLimits();
    RESULT ChildProcess();
    RESULT ParentProcess();
    RESULT CreateFiles();
    RESULT Compile();
    RESULT RunTestGroups();

    friend class WEB_DATA_PROCEED;
    friend class JUDGING_LIST;

public:
    SUBMISSION();
    ~SUBMISSION();

    RESULT Load(int ID);
    RESULT Save();
    RESULT Set(std::string Source, std::string ProblemID);
    RESULT Judge();
};

#endif
