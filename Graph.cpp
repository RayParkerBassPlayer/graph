#include "global_includes.hpp"
#include "graph.hpp"

using namespace std;

ostream &operator<<(ostream &os, const Graph &graph){
  os << "Root: " << *graph.root <<endl;

  os << "All Nodes: " << endl;

  for(Node *node:graph.nodes)
    os << *node << endl;

  return os;
}

Graph::Graph(){
  root = new Node(string("system_root"));
  AddToIndex(root);
}

Graph::~Graph(){
  for(Node *node:nodes){
    delete node;   
  }
}

// Everything is done with Node.ID().
void Graph::AddToIndex(Node *toAdd){
  NodeVector::iterator it = find_if(nodes.begin(), nodes.end(), [&](const Node *currentNode){
        return currentNode->ID() == toAdd->ID();
      });

  // Only add to index if it doesn't exist.
  if(it == nodes.end()){
    nodes.push_back(toAdd);
    sort(nodes.begin(), nodes.end(), [](const Node *left, const Node *right){
          return left->ID() < right->ID();
        });
  }
}

void Graph::RemoveFromIndex(Node *toRemove){
  throw "Write me!";
}

void Graph::AddNode(Node *toAdd){
  root->AddChild(toAdd);
  toAdd->AddParent(root);

  AddToIndex(toAdd);
}

void Graph::AddNode(Node *parent, Node *toAdd){
  parent->AddChild(toAdd);
  toAdd->AddParent(parent);

  AddToIndex(toAdd);
}

void Graph::InsertNode(Node *parent, Node *toAdd, Node *child){
  parent->AddChild(toAdd);
  toAdd->AddParent(parent);

  child->AddParent(toAdd);
  toAdd->AddChild(child);

  parent->RemoveChild(child);
  child->RemoveParent(parent);

  AddToIndex(toAdd);
}

void Graph::RemoveNode(Node *toRemove, bool patchGraph){
}

Node *Graph::FindNode(const string &ID){
  NodeVector::iterator it = find_if(nodes.begin(), nodes.end(), [&](const Node *currentNode){
        return currentNode->ID() == ID;
      });

  if(it == nodes.end())
    return (Node *)&NULL_NODE;

  return *it;
}

GraphPath *Graph::FindPaths(Node *node){
  if(node->Orphaned() && node != root)
    return 0;

  GraphPath *path = new GraphPath();

  if(node == root){
    path->push_front(node);

    return path;
  }

  GraphPath *foundPath = FindPaths(node->Parents()[0]);

  if(foundPath){
    path->push_front(node);
    path->splice(path->end(), *foundPath);
    delete foundPath;

    return path;
  }

  return 0;
}

GraphPaths *Graph::Paths(Node *node){
  GraphPaths *paths = new GraphPaths();

  GraphPath *path = FindPaths(node->Parents()[0]);

  if(path){
    path->push_front(node);
    paths->push_back(path);
  }

  return paths;
}
