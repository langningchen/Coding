#include <jdbc/mysql_connection.h>
#include <jdbc/mysql_driver.h>
#include <string>
#include <vector>
#include "Result.hpp"

class DATABASE
{
private:
    bool Connected;
    sql::Driver *Driver;
    sql::Connection *Connection;
    LOGGER Logger;

public:
    RESULT Init();
    RESULT Connect();
    ~DATABASE();
};

extern DATABASE Database;
