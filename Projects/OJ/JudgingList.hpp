#ifndef JUDGING_LIST_HPP
#define JUDGING_LIST_HPP

#include <queue>
#include "Logger.hpp"
#include "Submission.hpp"

class JUDGING_LIST
{
private:
    std::queue<int> JudgingList;
    LOGGER Logger;

public:
    JUDGING_LIST();
    ~JUDGING_LIST();

    void Init();
    RESULT Add(SUBMISSION Submission, int &SubmissionID);
};

extern JUDGING_LIST JudgingList;

#endif
