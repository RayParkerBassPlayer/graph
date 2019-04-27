#ifndef __NODE
#define __NODE

#include <ostream>
#include <string>
#include "hexGenerator.hpp"
#include "typedefs.hpp"

using std::ostream;
using std::string;

class Node{
    NodeVector parents, children;
    IdList parentIds, childIds;

    string id, type, value;

    // Standardize ID generation.
    string GetId(void){
      return HexGenerator::generate_hex(16);
    }

    bool SetParent(Node *newParent);

  public:
    Node():id(GetId()){};
    Node(const string &type, const string &value = ""):id(GetId()), type(type), value(value){};

    bool Orphaned(void) const{return parents.size() == 0;}

    const string &ID(void){return id;}

    bool AddChild(Node *toAdd);

    bool operator ==(const Node &node);
    friend ostream& operator<<(ostream& os, const Node& node);
};

extern const Node NULL_NODE;

#endif
