#include <iostream>
#include "global_includes.hpp"
#include "Graph.hpp"
#include "database.hpp"

using namespace std;
using namespace sql;
using namespace spdlog;

int main(void){
  set_level(level::debug);

  info("Graph starting up.");

  Database db;

  Graph *graph = new Graph();

  info("Loading graph...");

  for(int i = 0; i < 100; i++)
    graph->AddNode(new Node());

  info("...finished loading Graph");

  // cout << *graph << endl;

  delete graph;

  info("All done.");

  return 0;
}


