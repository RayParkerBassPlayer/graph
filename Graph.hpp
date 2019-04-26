#ifndef __GRAPH
#define __GRAPH

#include <ostream>
#include "node.hpp"
#include "typedefs.hpp"

using std::ostream;

class Graph{
  Node *root = 0;
  NodeVector nodes;

  public:
    Graph();
    ~Graph();

    bool AddNode(Node *toAdd);
    bool AddNode(Node &parent, Node *toAdd);

    friend ostream& operator<<(ostream& os, const Graph& graph);
};

#endif
