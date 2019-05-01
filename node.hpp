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

    string id, type, value;

    // Standardize ID generation.
    string GetId(void){
      return HexGenerator::generate_hex(16);
    }

  public:
    Node():id(GetId()){};
    Node(const string &type, const string &value = ""):id(GetId()), type(type), value(value){};

    const NodeVector &Parents(void) const{return parents;}
    bool HasParent(const Node *toFind) const;

    const NodeVector &Children(void) const{return children;}
    bool HasChild(const Node *toFind);
    

    bool Orphaned(void) const{return parents.size() == 0;}

    const string &ID(void) const{return id;}

    const string &Type(void) const{return type;}
    void SetType(const char *newType){type = newType;}
    void SetType(const string &newType){SetType(newType.c_str());}

    const string &Value(void) const{return value;}
    void SetValue(const char *newValue){value = newValue;}
    void SetValue(const string &newValue){SetValue(newValue.c_str());}

    void AddChild(Node *toAdd);
    void AddParent(Node *toAdd);

    void RemoveParent(Node *toRemove);
    void RemoveChild(Node *toRemove);

    bool operator ==(const Node &node);
    friend ostream& operator<<(ostream& os, const Node& node);
};

extern const Node NULL_NODE;

#endif
