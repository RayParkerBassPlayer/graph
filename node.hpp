#ifndef __NODE
#define __NODE

#include <ostream>
#include <string>
#include "hexGenerator.hpp"
#include "typedefs.hpp"

using std::ostream;
using std::string;

class Node{
    Node *parent = 0;
    string id, type, value;
    NodeVector children;

    // Standardize ID generation.
    string GetId(void){
      return HexGenerator::generate_hex(16);
    }

    bool SetParent(Node *newParent);

  public:
    Node():id(GetId()){};
    Node(const string &type, const string &value = ""):id(GetId()), type(type), value(value){};

    const string &ID(void){return id;}

    bool AddChild(Node *toAdd);

    friend ostream& operator<<(ostream& os, const Node& node);
};

#endif
