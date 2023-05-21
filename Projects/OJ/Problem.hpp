#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include "Sample.hpp"
#include "TestGroup.hpp"

class PROBLEM
{
private:
    std::string ID;
    std::string Title;
    std::string Description;
    std::string Input;
    std::string Output;
    std::vector<SAMPLE> Samples;
    std::vector<TEST_GROUP> TestGroups;
    std::string Range;
    std::string Hint;
    std::string WorkDir;
    LOGGER Logger;

    friend class PROBLEM_LIST;
    friend class WEB_DATA_PROCEED;
    friend class SUBMISSION;

public:
    PROBLEM();
    ~PROBLEM();

    RESULT Load(std::string ID);
    RESULT Save();
    RESULT LoadSamples(std::string ID);
    RESULT SaveSamples();
    RESULT LoadTestGroups(std::string ID);
    RESULT SaveTestGroups();
    void Update(std::string ID, std::string Title,
                std::string Description, std::string Input, std::string Output,
                std::vector<SAMPLE> Samples,
                std::string Range, std::string Hint);
    RESULT UpdateWorkDir();
    void SetTestGroups(std::vector<TEST_GROUP> TestGroups);

    bool operator<(const PROBLEM &Compare) const;
};

#endif
