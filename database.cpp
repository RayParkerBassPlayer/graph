#include <exception>
#include "database.hpp"

using namespace spdlog;
using namespace std;
using namespace sql;

Database::Database(){
  info("Creating database connection");

  debug("Getting driver");

  driver = get_driver_instance();

  if(!driver){
    error("Error getting MySql driver");
    return;
  }

  connection = driver->connect("tcp://localhost:3306", "", "");
  InitializeDb();
}

Database::~Database(){
  info("Destroying database connection");

  if(connection){
    connection->close();
  }
}


void Database::InitializeDb(void){
  Statement *statement = connection->createStatement();

  info("Creating database");
  statement->execute("create database if not exists graph");

  info("Using test database");
  statement->execute("use graph");

  info("Dropping test table if there.");
  statement->execute("drop table if exists nodes");

  info("Creating test table");
  statement->execute("CREATE TABLE nodes(id INT, label CHAR(1))");

  // info("Inserting data into test table");
  // statement->execute("INSERT INTO test(id, label) VALUES (1, 'a')");
}
