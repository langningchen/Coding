#include "Sample.hpp"
#include "Settings.hpp"
#include "Utilities.hpp"
#include <dirent.h>
#include <string>
#include <fstream>

SAMPLE::SAMPLE() {}
SAMPLE::SAMPLE(std::string Input, std::string Output, std::string Description)
{
    this->Input = Input;
    this->Output = Output;
    this->Description = Description;
}
SAMPLE::~SAMPLE() {}

std::string SAMPLE::GetInput() { return Input; }
std::string SAMPLE::GetOutput() { return Output; }
std::string SAMPLE::GetDescription() { return Description; }
