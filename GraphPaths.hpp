#ifndef __GRAPH_PATHS_HPP
#define __GRAPH_PATHS_HPP

#include <list>
#include "node.hpp"

using std::list;

typedef list<Node *> GraphPath;

class GraphPaths : public list<GraphPath *>{
  public:
    ~GraphPaths(){
      for(GraphPath *path : *this){
        delete path;
      }
    }
};

#endif
