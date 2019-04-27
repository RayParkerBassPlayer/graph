#include "global_includes.hpp"
#include "node.hpp"

using std::endl;

bool Node::AddChild(Node *toAdd){
  spdlog::debug("{:s} adding child {:s}.", this-> id, toAdd->id);

  children.push_back(toAdd);
  toAdd->SetParent(this);

  return true;
}

bool Node::SetParent(Node *newParent){
  parent = newParent;

  return true;
}

ostream &operator<<(ostream &os, const Node &node){
  os << "Node: id: " << node.id << " Type: " << node.type << " Value: " << node.value;

  if(node.children.size()){
    os << endl << "Children (" << node.children.size() << ")" << endl;

    for(Node *child:node.children)
      os << *child << endl;
  }

  return os;
}
