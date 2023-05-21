#include "HTTPRequest.hpp"
#include "Utilities.hpp"
#include "Settings.hpp"

HTTP_REQUEST::HTTP_REQUEST(std::string Data)
{
    Logger.SetLogFileName(Settings.GetBaseFolder() + "/HTTPRequest.log");
    Data = Utilities.StringReplaceAll(Data, "\r", "");

    size_t VerbStartPosition = 0;
    size_t VerbEndPosition = Data.find(" ", VerbStartPosition);
    Verb = Data.substr(VerbStartPosition, VerbEndPosition - VerbStartPosition);

    size_t PathStartPosition = VerbEndPosition + 1;
    size_t PathEndPosition = Data.find(" ", PathStartPosition);
    Path = Data.substr(PathStartPosition, PathEndPosition - PathStartPosition);

    size_t VersionStartPosition = PathEndPosition + 1;
    size_t VersionEndPosition = Data.find("\n", VersionStartPosition);
    Version = Data.substr(VersionStartPosition, VersionEndPosition - VersionStartPosition);

    std::string Line;
    for (size_t i = PathEndPosition + 1; i < Data.length(); i++)
    {
        if (Data[i] == '\n')
        {
            if (Line == "")
            {
                Body = Data.substr(i);
                break;
            }
            size_t NameStartPosition = 0;
            size_t NameEndPosition = Line.find(": ", NameStartPosition);
            std::string Name = Line.substr(NameStartPosition, NameEndPosition - NameStartPosition);

            size_t ValueStartPosition = NameEndPosition + 2;
            size_t ValueEndPosition = Line.size();
            std::string Value = Line.substr(ValueStartPosition, ValueEndPosition - ValueStartPosition);

            Headers[Name] = Value;

            Line = "";
        }
        else
            Line.push_back(Data[i]);
    }
}
HTTP_REQUEST::~HTTP_REQUEST() {}

std::string HTTP_REQUEST::GetVersion() { return Version; }
std::string HTTP_REQUEST::GetVerb() { return Verb; }
std::string HTTP_REQUEST::GetPath() { return Path; }
std::string HTTP_REQUEST::GetHeader(std::string Name) { return Headers[Name]; }
std::string HTTP_REQUEST::GetBody() { return Body; }
