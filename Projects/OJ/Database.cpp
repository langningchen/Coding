#include "Database.hpp"
#include "Settings.hpp"

RESULT DATABASE::Init()
{
    Logger.SetLogFileName(Settings.GetBaseFolder() + "/Database.log");
    RETURN_IF_FAILED(Connect())
    CREATE_RESULT(true, "Initialized")
}

RESULT DATABASE::Connect()
{
    if (Connected)
        CREATE_RESULT(true, "Already connected")
    Connected = false;
    // mysql_init(&DatabaseConnection);
    // if (mysql_real_connect(&DatabaseConnection,
    //                        Settings.DatabaseSettings.GetHost().c_str(),
    //                        Settings.DatabaseSettings.GetUsername().c_str(),
    //                        Settings.DatabaseSettings.GetPassword().c_str(),
    //                        Settings.DatabaseSettings.GetDatabaseName().c_str(),
    //                        Settings.DatabaseSettings.GetPort(),
    //                        nullptr,
    //                        0) == nullptr)
    //     CREATE_RESULT(false, mysql_error(&DatabaseConnection))
    Driver = sql::mysql::get_mysql_driver_instance();
    Connection = Driver->connect(Settings.DatabaseSettings.GetHost().c_str(),
                                 Settings.DatabaseSettings.GetUsername().c_str(),
                                 Settings.DatabaseSettings.GetPassword().c_str());
    if (Connection == nullptr)
        CREATE_RESULT(false, "Failed to connect to database")
    Connection->setSchema(Settings.DatabaseSettings.GetDatabaseName().c_str());
    Connected = true;
    CREATE_RESULT(true, "Connected")
}

DATABASE::~DATABASE()
{
    if (!Connected)
        return;
    // mysql_close(&DatabaseConnection);
    Connection->close();
    delete Connection;
}

DATABASE Database;

/*
sudo mkdir /var/run/mysqld/
sudo chown mysql:mysql /var/run/mysqld/
sudo mysqld --user=root
*/
