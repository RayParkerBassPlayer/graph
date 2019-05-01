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

typedef list<Node *> Path;
typedef vector<Path> PathVector;

class Graph{
  Node *root;
  NodeVector nodes;

  public:
    Graph();
    ~Graph();

    Node *Root(void) const{return root;}

    void AddNode(Node *toAdd);
    void AddNode(Node *parent, Node *toAdd);

    Node *FindNode(const string &ID);
    Node *FindNode(const char *ID){
      return FindNode(string(ID));
    }

    // Insert node between two other nodes, patching up the route.
    void InsertNode(Node *parent, Node *toAdd, Node *child);
    // If patchGraph is true, route will be updated to pass through node.  
    // Otherwise all relationships are removed.
    void RemoveNode(Node *toRemove, bool patchGraph = false);

    PathVector *PathTo(const Node *toTrace) const;

    friend ostream& operator<<(ostream& os, const Graph& graph);
};

#endif
