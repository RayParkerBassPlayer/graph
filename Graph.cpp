#include "global_includes.hpp"
#include "graph.hpp"

using std::endl;

ostream &operator<<(ostream &os, const Graph &graph){
  os << "Root: " << *graph.root <<endl;

  os << "All Nodes: " << endl;

  for(Node *node:graph.nodes)
    os << *node << endl;

  return os;
}

Graph::Graph(){
  root = new Node(string("system_root"));
  nodes.push_back(root);
}

Graph::~Graph(){
  for(Node *node:nodes)
    delete node;
}

bool Graph::AddNode(Node *toAdd){
  spdlog::debug("Graph adding node {:s}.", toAdd->ID());

  root->AddChild(toAdd);
  nodes.push_back(toAdd);

  return true;
}

bool Graph::AddNode(Node &parent, Node *toAdd){
  spdlog::debug("Graph adding node {:s} to {:s}.", toAdd->ID(), parent.ID());

  parent.AddChild(toAdd);
  nodes.push_back(toAdd);

  return true;
}

bool Graph::InsertNode(Node &parent, Node *toAdd, Node &child){
  return false;
}

bool Graph::RemoveNode(Node *toRemove, bool patchGraph){
  return false;
}
