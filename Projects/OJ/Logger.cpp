#include "Logger.hpp"
#include <sys/time.h>
#include <string.h>

LOGGER::LOGGER() { SetLogFileName("Log.log"); }
LOGGER::LOGGER(const LOGGER &Other) { SetLogFileName(Other.LogFileName); }
LOGGER::~LOGGER() { fclose(LogFile); }
void LOGGER::operator=(const LOGGER &Other) { SetLogFileName(Other.LogFileName); }

void LOGGER::SetLogFileName(std::string LogFileName)
{
    LogFile = fopen(LogFileName.c_str(), "a+");
    if (LogFile == nullptr)
    {
        LogFile = stdout;
        this->LogFileName = "";
        Error("Failed to open log file: " + LogFileName);
    }
    else
        this->LogFileName = LogFileName;
}

std::string LOGGER::GetLogFileName() { return LogFileName; }

void LOGGER::Output(std::string Type, std::string Style, std::string Data)
{
    if (LogFile == nullptr)
        LogFile = stdout;

    struct timeval CurrentSecond;
    gettimeofday(&CurrentSecond, nullptr);
    int MilliSecond = CurrentSecond.tv_usec / 1000;

    char CurrentTime[80] = {0};
    struct tm TempTime;
    localtime_r(&CurrentSecond.tv_sec, &TempTime);
    strftime(CurrentTime, sizeof(CurrentTime), "%Y%m%d%H%M%S", &TempTime);

    OutputMutex.lock();
    fprintf(LogFile, "\033[%sm[%7s] [%s%03d] %s\033[0m\n",
            Style.c_str(), Type.c_str(),
            CurrentTime, MilliSecond,
            Data.c_str());
    fflush(LogFile);

    errno = 0;
    OutputMutex.unlock();
}

void LOGGER::Debug(std::string Data)
{
    Output("DEBUG", "36", Data);
}
void LOGGER::Info(std::string Data) { Output("INFO", "32", Data); }
void LOGGER::Warning(std::string Data) { Output("WARNING", "33", Data); }
void LOGGER::Error(std::string Data) { Output("ERROR", "31", Data + ", " + std::to_string(errno) + ": " + std::string(strerror(errno))); }
void LOGGER::Fetal(std::string Data)
{
    Output("FETAL", "1;4;5;31", Data);
    exit(1);
}
