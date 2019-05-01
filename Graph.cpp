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
  for(Node *node:nodes){
    delete node;   
  }
}

void Graph::AddNode(Node *toAdd){
  root->AddChild(toAdd);
  toAdd->AddParent(root);

  nodes.push_back(toAdd);
}

void Graph::AddNode(Node *parent, Node *toAdd){
  parent->AddChild(toAdd);
  toAdd->AddParent(parent);

  nodes.push_back(toAdd);
}

void Graph::InsertNode(Node *parent, Node *toAdd, Node *child){
  parent->AddChild(toAdd);
  toAdd->AddParent(parent);

  child->AddParent(toAdd);
  toAdd->AddChild(child);

  parent->RemoveChild(child);
  child->RemoveParent(parent);

  nodes.push_back(toAdd);
}

void Graph::RemoveNode(Node *toRemove, bool patchGraph){
}

Node *Graph::FindNode(const string &ID){
  return (Node *)&NULL_NODE;
}

PathVector *Graph::PathTo(const Node *toTrace) const{
  return 0;
}


