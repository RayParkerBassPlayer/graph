#include "node.hpp"

bool Node::AddChild(Node *toAdd){
  children.push_back(toAdd);

  return true;
}

ostream &operator<<(ostream &os, const Node &node){
  return os << "Node: id: " << node.id << " Type: " << node.type << " Value: " << node.value;
}
