#include "global_includes.hpp"
#include "node.hpp"

using std::endl;

const Node NULL_NODE("NULL_NODE", "NULL");

bool Node::AddChild(Node *toAdd){
  spdlog::debug("{:s} adding child {:s}.", this-> id, toAdd->id);

  children.push_back(toAdd);
  toAdd->SetParent(this);

  return true;
}

bool Node::SetParent(Node *newParent){
  parents.push_back(newParent);

  return true;
}

ostream &operator<<(ostream &os, const Node &node){
  os << "Node: id: " << node.id << " Type: " << node.type << " Value: " << node.value;

  if(node.parents.size()){
    os << endl << "Parents (" << node.parents.size() << ")" << endl;

    for(Node *parent:node.children)
      os << *parent << endl;
  }
  else
    os << "No Parents (Orphaned: " << node.Orphaned() << ")" << endl;

  if(node.children.size()){
    os << endl << "Children (" << node.children.size() << ")" << endl;

    for(Node *child:node.children)
      os << *child << endl;
  }
  else
    os << "No children." << endl;

  return os;
}

bool Node::operator ==(const Node &node){
  return id == node.id;
}
