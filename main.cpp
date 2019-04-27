#include <iostream>
#include "global_includes.hpp"
#include "graph.hpp"

using namespace std;

int main(void){
  spdlog::set_level(spdlog::level::debug);

  spdlog::info("Graph starting up.");
  Graph *graph = new Graph();

  spdlog::info("Loading graph...");

  for(int i = 0; i < 100; i++)
    graph->AddNode(new Node());

  spdlog::info("...finished loading Graph");

  delete graph;

  return 0;
}
