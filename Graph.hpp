#ifndef __GRAPH
#define __GRAPH

#include <ostream>
#include <list>
#include <vector>
#include "node.hpp"
#include "typedefs.hpp"

using std::ostream;
using std::vector;
using std::list;

typedef list<Node *> GraphPath;
typedef vector<GraphPath *> GraphPaths;

class Graph{
  Node *root;

  // A master index of all nodes.  Operate with the private manipulators, only!
  NodeVector nodes;

  void AddToIndex(Node *toAdd);
  void RemoveFromIndex(Node *toRemove);
  GraphPath *FindPaths(Node *node);

  public:
    Graph();
    ~Graph();

    Node *Root(void) const{return root;}
    const NodeVector &Index(void) const{return nodes;}

    void AddNode(Node *toAdd);
    void AddNode(Node *parent, Node *toAdd);

    Node *FindNode(const string &ID);
    Node *FindNode(const char *ID){
      return FindNode(string(ID));
    }

    GraphPaths *Paths(Node *node);

    // Insert node between two other nodes, patching up the route.
    void InsertNode(Node *parent, Node *toAdd, Node *child);
    // If patchGraph is true, route will be updated to pass through node.  
    // Otherwise all relationships are removed.
    void RemoveNode(Node *toRemove, bool patchGraph = false);

    friend ostream& operator<<(ostream& os, const Graph& graph);
};

#endif
