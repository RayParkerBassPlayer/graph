#include <iostream>
#include "global_includes.hpp"
#include "Graph.hpp"

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;
using namespace sql;

int main(void){
  spdlog::set_level(spdlog::level::debug);

  spdlog::info("Graph starting up.");
  // Graph *graph = new Graph();
  //
  // spdlog::info("Loading graph...");
  //
  // for(int i = 0; i < 100; i++)
  //   graph->AddNode(new Node());
  //
  // spdlog::info("...finished loading Graph");
  //
  // delete graph;

  spdlog::info("Getting driver");
  sql::Driver *driver = get_driver_instance();

  spdlog::info("Connecting to db");
  sql::Connection *connection = driver->connect("tcp://localhost:3306", "graph", "password");

  sql::Statement *statement = connection->createStatement();
  statement->execute("use graph");
  statement->execute("drop table if exists test");
  statement->execute("CREATE TABLE test(id INT, label CHAR(1))");
  statement->execute("INSERT INTO test(id, label) VALUES (1, 'a')");

  spdlog::info("Closing DB connection.");
  delete connection;

  return 0;
}


