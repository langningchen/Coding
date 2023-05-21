#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "Logger.hpp"
#include "Result.hpp"

#define DEBUG_HERE                                                                                                    \
    {                                                                                                                 \
        Logger.Info(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " " + std::string(__PRETTY_FUNCTION__)); \
        std::cout << __FILE__ << ":" << __LINE__ << " " << __PRETTY_FUNCTION__ << std::endl;                          \
    }

class UTILITIES
{
private:
    static size_t UploadFunction(char *ptr, size_t size, size_t nmemb, void *userp);
    LOGGER Logger;

public:
    void Init();
    std::string StringReplaceAll(std::string Data, std::string Search, std::string Replace);
    // RESULT MakeDir(std::string Dir);
    RESULT MakeDir(std::string Dir);
    RESULT RemoveDir(std::string Dir);
    RESULT CopyFile(std::string Source, std::string Destination);
    RESULT CopyDir(std::string Source, std::string Destination);
    RESULT LoadFile(std::string FileName, std::string &Output);
    RESULT LoadFile(std::string FileName, int &Output);
    RESULT SaveFile(std::string FileName, std::string Data);
    RESULT SaveFile(std::string FileName, int Data);
    std::string RemoveSpaces(std::string Input);
    RESULT SendEmail(std::string To, std::string Subject, std::string Body);
};

extern UTILITIES Utilities;

#endif
