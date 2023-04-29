#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <mutex>

class LOGGER
{
private:
    std::string LogFileName;
    FILE *LogFile = NULL;
    std::mutex OutputMutex;
    void Output(std::string Type, std::string Style, std::string Data);

    friend class WEB_DATA_PROCEED;

public:
    LOGGER();
    LOGGER(const LOGGER &Other);
    ~LOGGER();
    void operator=(const LOGGER &Other);

    void SetLogFileName(std::string LogFileName);

    std::string GetLogFileName();

    void Debug(std::string Data);
    void Info(std::string Data);
    void Warning(std::string Data);
    void Error(std::string Data);
    void Fetal(std::string Data);
};

#endif
