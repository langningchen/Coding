#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include "Sample.hpp"
#include "TestGroup.hpp"
#include "Logger.hpp"
#include <string>
#include <vector>

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
    std::string IOFileName;
    std::string WorkDir;
    LOGGER Logger;

    friend class PROBLEM_LIST;
    friend class WEB_DATA_PROCEED;

public:
    PROBLEM();
    ~PROBLEM();

    std::string GetID();
    std::string GetMD();
    std::vector<TEST_GROUP> GetTestGroups();

    bool Load(std::string ID);
    bool Save();
    bool LoadSamples(std::string ID);
    bool SaveSamples();
    bool LoadTestGroups(std::string ID);
    bool SaveTestGroups();
    void Update(std::string ID, std::string Title,
                std::string Description, std::string Input, std::string Output,
                std::vector<SAMPLE> Samples,
                std::string Range, std::string Hint, std::string IOFileName);
    void UpdateWorkDir();
    void SetTestGroups(std::vector<TEST_GROUP> TestGroups);

    bool operator<(const PROBLEM &Compare) const;
};

#endif
