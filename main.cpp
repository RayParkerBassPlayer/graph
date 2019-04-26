#include <iostream>
#include "graph.hpp"

using namespace std;

int main(void){
  Graph *graph = new Graph();

  for(int i = 0; i < 100; i++)
    graph->AddNode(new Node());

  cout << *graph << endl;

  delete graph;

  return 0;
}
