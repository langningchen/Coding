#ifndef PROBLEM_LIST_HPP
#define PROBLEM_LIST_HPP

#include "Logger.hpp"
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

    bool Load();
    bool GetProblem(std::string ProblemID, PROBLEM &Result);
    bool AddProblem(PROBLEM Problem);
    bool RemoveProblem(std::string ProblemID);
    bool UpdateProblem(PROBLEM Problem);
};

extern PROBLEM_LIST ProblemList;

#endif
