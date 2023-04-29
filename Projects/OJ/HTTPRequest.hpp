#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include "Logger.hpp"
#include <string>
#include <map>

class HTTP_REQUEST
{
private:
    std::string Version;
    std::string Verb;
    std::string Path;
    std::map<std::string, std::string> Headers;
    std::string Body;
    LOGGER Logger;

public:
    HTTP_REQUEST(std::string Data);
    ~HTTP_REQUEST();

    std::string GetVersion();
    std::string GetVerb();
    std::string GetPath();
    std::string GetHeader(std::string Name);
    std::string GetBody();
};

#endif
