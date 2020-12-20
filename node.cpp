#include <algorithm>
#include "global_includes.hpp"
#include "node.hpp"

using std::endl;

const Node NULL_NODE("NULL_NODE", "NULL");

void Node::AddChild(Node *toAdd){
  if(!HasChild(toAdd))
    children.push_back(toAdd);
}

void Node::AddParent(Node *toAdd){
  if(!HasParent(toAdd))
    parents.push_back(toAdd);
}

void Node::RemoveChild(Node *toRemove){
  NodeVector::iterator foundNode = find(children.begin(), children.end(), toRemove);

  if(foundNode != children.end())
    children.erase(foundNode);
}

void Node::RemoveParent(Node *toRemove){
  NodeVector::iterator foundNode = find(parents.begin(), parents.end(), toRemove);

  if(foundNode != parents.end())
    parents.erase(foundNode);
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

bool Node::HasParent(const Node *toFind) const{
  return find(parents.begin(), parents.end(), toFind) != parents.end();
}

bool Node::HasChild(const Node *toFind){
  return find(children.begin(), children.end(), toFind) != children.end();
}

