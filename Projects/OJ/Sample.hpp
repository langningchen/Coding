#ifndef SAMPLE_HPP
#define SAMPLE_HPP

#include <string>

class SAMPLE
{
private:
    std::string Input;
    std::string Output;
    std::string Description;

    friend class WEB_DATA_PROCEED;
    friend class PROBLEM;

public:
    SAMPLE();
    SAMPLE(std::string Input, std::string Output, std::string Description);
    ~SAMPLE();

    std::string GetInput();
    std::string GetOutput();
    std::string GetDescription();
};

#endif
