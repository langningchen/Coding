#include <stdexcept>
using namespace std;
#define TRIGGER_ERROR(ErrorDetail)                             \
    throw CLNException("Error! \n" +                           \
                       string(ErrorDetail) + "\n" +            \
                       "\n" +                                  \
                       "File: " + __FILE__ + "\n" +            \
                       "Line: " + to_string(__LINE__) + "\n" + \
                       "Function: " + __func__ + "\n" +        \
                       "Errno: " + to_string(errno))
#define TRIGGER_ERROR_WITH_CODE(ErrorDetail, ErrorCode)          \
    throw CLNException("Error! " + to_string(ErrorCode) + "\n" + \
                       string(ErrorDetail) + "\n" +              \
                       "\n" +                                    \
                       "File: " + __FILE__ + "\n" +              \
                       "Line: " + to_string(__LINE__) + "\n" +   \
                       "Function: " + __func__ + "\n" +          \
                       "Errno: " + to_string(errno))
#define TRIGGER_ERROR_WITH_CODE_AND_MESSAGE(ErrorDetail, ErrorCode, ErrorMessage)      \
    throw CLNException("Error! " + to_string(ErrorCode) + ": " + ErrorMessage + "\n" + \
                       string(ErrorDetail) + "\n" +                                    \
                       "\n" +                                                          \
                       "File: " + __FILE__ + "\n" +                                    \
                       "Line: " + to_string(__LINE__) + "\n" +                         \
                       "Function: " + __func__ + "\n" +                                \
                       "Errno: " + to_string(errno))
#define CLN_TRY \
    try         \
    {
#ifdef TEST
#define CLN_CATCH                                       \
    }                                                   \
    catch (CLNException & Exception)                    \
    {                                                   \
        cerr << Exception.what() << endl;               \
        OutputSummary("```log\n" +                      \
                      string(Exception.what()) + "\n" + \
                      "```");                           \
        exit(0);                                        \
    }
#else
#define CLN_CATCH                         \
    }                                     \
    catch (CLNException & Exception)      \
    {                                     \
        cerr << Exception.what() << endl; \
        exit(0);                          \
    }
#endif
class CLNException : public runtime_error
{
public:
    CLNException(const string &message) : runtime_error(message) {}
};
