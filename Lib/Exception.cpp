#include "Exception.hpp"
string GetStackTrace()
{
    void *BackTrace[100];
    int BackTraceSize = backtrace(BackTrace, 100);
    char **BackTraceSymbols = backtrace_symbols(BackTrace, BackTraceSize);
    string Output = "";
    for (int i = 0; i < BackTraceSize; i++)
        Output += BackTraceSymbols[i] + "\n"s;
    free(BackTraceSymbols);
    return Output;
}
CLNException::CLNException()
{
}
CLNException::CLNException(const string &message)
{
    Content = "We're sorry but this program occurred " + message + "\n" +
              "\n" +
              GetStackTrace() +
              "\n" +
              "Please try to run this program again later, if this error still occurred, contact the developer for help! Thanks! \n";
}
string CLNException::what() const
{
    return Content;
}
CLNException::~CLNException()
{
}
