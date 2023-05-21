#ifndef PROBLEM_LIST_HPP
#define PROBLEM_LIST_HPP

#include "Problem.hpp"
#include <string>
#include <set>

class PROBLEM_LIST
{
private:
    std::set<PROBLEM> Problems;
    LOGGER Logger;

    bool GetProblemPointer(std::string ProblemID, std::set<PROBLEM>::iterator &Result);

    friend class WEB_DATA_PROCEED;

public:
    PROBLEM_LIST();
    ~PROBLEM_LIST();

    RESULT Load();
    RESULT Save();
    RESULT GetProblem(std::string ProblemID, PROBLEM &Result);
    RESULT AddProblem(PROBLEM Problem);
    RESULT RemoveProblem(std::string ProblemID);
    RESULT UpdateProblem(PROBLEM Problem);
};

extern PROBLEM_LIST ProblemList;

#endif
