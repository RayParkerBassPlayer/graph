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

    // Insert node between two other nodes, patching up the route.
    bool InsertNode(Node &parent, Node *toAdd, Node &child);

    // If patchGraph is true, route will be updated to pass through node.  Otherwise all relationships are removed.
    bool RemoveNode(Node *toRemove, bool patchGraph = false);

    friend ostream& operator<<(ostream& os, const Graph& graph);
};

#endif
