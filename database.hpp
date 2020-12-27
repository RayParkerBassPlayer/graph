#ifndef __DATABASE
#define __DATABASE

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "global_includes.hpp"

class Database{
  sql::Driver *driver;
  sql::Connection *connection;

  public:
    Database();
    ~Database();

    void InitializeDb(void);
};

#endif
