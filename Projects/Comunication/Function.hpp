#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

#define ERROR(Message) ERROR_FUNCTION(__FILE__, __LINE__, Message)
#define ASSERT(expression) ((expression) ? void(0) : ERROR(string("Assert Failed! Expression: \"") + string(#expression) + string("\" Error Number: ") + string(to_string(errno))))
void ERROR_FUNCTION(string File, int Line, string Message)
{
    cout << "File " << File << " Line " << Line << ": " << Message << endl;
    exit(-1);
}

const int SERVER_PORT = 1474;
const int StringSize = 1024;

struct Message
{
    enum
    {
        TEXT,
        HELLO,
        GOODBYE
    } DataType;
    union
    {
        char TextData[StringSize];
    } Data;
};