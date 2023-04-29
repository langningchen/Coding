#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "Logger.hpp"
#include <string>

#define DEBUG_HERE \
    Logger.Debug(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " " + std::string(__func__));

class UTILITIES
{
private:
    static size_t UploadFunction(char *ptr, size_t size, size_t nmemb, void *userp);
    LOGGER Logger;

public:
    void Init();
    std::string StringReplaceAll(std::string Data, std::string Search, std::string Replace);
    // bool MakeDir(std::string Dir);
    bool MakeDir(std::string Dir);
    bool RemoveDir(std::string Dir);
    bool CopyFile(std::string Source, std::string Destination);
    bool CopyDir(std::string Source, std::string Destination);
    bool LoadFile(std::string FileName, std::string &Output);
    bool LoadFile(std::string FileName, int &Output);
    bool SaveFile(std::string FileName, std::string Data);
    bool SaveFile(std::string FileName, int Data);
    std::string RemoveSpaces(std::string Input);
    bool SendEmail(std::string To, std::string Subject, std::string Body);
};

extern UTILITIES Utilities;

#endif
