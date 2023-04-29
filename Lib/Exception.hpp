#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP
#include <stdexcept>
#include <string>
#include <execinfo.h>
#include <iostream>
using namespace std;

#ifdef TEST
const bool WhetherDefineTest = true;
#else
const bool WhetherDefineTest = false;
#endif

#define TRIGGER_ERROR(ErrorDetail)                             \
    throw CLNException("an error! \n"s +                       \
                       "\n" +                                  \
                       string(ErrorDetail) + "\n" +            \
                       "File: " + __FILE__ + "\n" +            \
                       "Line: " + to_string(__LINE__) + "\n" + \
                       "Function: " + __func__ + "\n" +        \
                       "Errno: " + to_string(errno))
#define TRIGGER_ERROR_WITH_CODE(ErrorDetail, ErrorCode)             \
    throw CLNException("an error! " + to_string(ErrorCode) + "\n" + \
                       "\n" +                                       \
                       string(ErrorDetail) + "\n" +                 \
                       "File: " + __FILE__ + "\n" +                 \
                       "Line: " + to_string(__LINE__) + "\n" +      \
                       "Function: " + __func__ + "\n" +             \
                       "Errno: " + to_string(errno))
#define TRIGGER_ERROR_WITH_CODE_AND_MESSAGE(ErrorDetail, ErrorCode, ErrorMessage)         \
    throw CLNException("an error! " + to_string(ErrorCode) + ": " + ErrorMessage + "\n" + \
                       "\n" +                                                             \
                       string(ErrorDetail) + "\n" +                                       \
                       "File: " + __FILE__ + "\n" +                                       \
                       "Line: " + to_string(__LINE__) + "\n" +                            \
                       "Function: " + __func__ + "\n" +                                   \
                       "Errno: " + to_string(errno))

#define CLN_TRY \
    try         \
    {           \
        try     \
        {
#define CLN_CATCH                                                        \
    }                                                                    \
    catch (const configor::configor_exception &Exception)                \
    {                                                                    \
        TRIGGER_ERROR("a JSON error: "s + Exception.what());             \
    }                                                                    \
    catch (const logic_error &Exception)                                 \
    {                                                                    \
        TRIGGER_ERROR("a standard logic error: "s + Exception.what());   \
    }                                                                    \
    catch (const runtime_error &Exception)                               \
    {                                                                    \
        TRIGGER_ERROR("a standard runtime error: "s + Exception.what()); \
    }                                                                    \
    catch (const exception &Exception)                                   \
    {                                                                    \
        TRIGGER_ERROR("a standard error: "s + Exception.what());         \
    }                                                                    \
    }                                                                    \
    catch (const CLNException &Exception)                                \
    {                                                                    \
        cerr << Exception.what() << endl;                                \
        if (WhetherDefineTest)                                           \
        {                                                                \
            OutputSummary("```log\n" +                                   \
                          Exception.what() + "\n" +                      \
                          "```");                                        \
        }                                                                \
        exit(1);                                                         \
    }

string GetStackTrace();

class CLNException
{
private:
    string Content = "";

public:
    CLNException();
    CLNException(const string &message);
    string what() const;
    ~CLNException();
};
#endif
