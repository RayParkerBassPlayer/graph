#include "graph.hpp"

using std::endl;

ostream &operator<<(ostream &os, const Graph &graph){
  os << "Root: " << *graph.root <<endl;

  os << "All Nodes: " << endl;
  for(NodeVector::const_iterator it = graph.nodes.begin(); it != graph.nodes.end(); it++)
    os << **it << endl;

  return os;
}

Graph::Graph(){
  root = new Node(string("system_root"));
  nodes.push_back(root);
}

Graph::~Graph(){
  for(NodeVector::iterator it = nodes.begin(); it != nodes.end(); it++)
    delete *it;
}

bool Graph::AddNode(Node *toAdd){
  root->AddChild(toAdd);
  nodes.push_back(toAdd);

  return true;
}

bool Graph::AddNode(Node &parent, Node *toAdd){
  parent.AddChild(toAdd);
  nodes.push_back(toAdd);

  return true;
}

