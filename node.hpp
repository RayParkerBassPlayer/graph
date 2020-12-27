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
    DB_ID dbId = 0;
    bool dirty = false;

    // Standardize ID generation.
    string GetId(void){
      return HexGenerator::generate_hex(16);
    }

    bool SetDirty(const bool dirtyState = true);
    bool SetClean(void);

  public:
    Node():id(GetId()), dirty(true){};
    Node(const string &type, const string &value = ""):id(GetId()), type(type), value(value), dirty(true){};

    const NodeVector &Parents(void) const{return parents;}

    bool Dirty(void) const{return dirty;}
    
    // Test that node has given node as a parent.
    bool HasParent(const Node *toFind) const;

    const NodeVector &Children(void) const{return children;}
    // Test that node has a given node as a direct child
    bool HasChild(const Node *toFind);

    bool Orphaned(void) const{return parents.size() == 0;}

    const string &ID(void) const{return id;}
    DB_ID DbId(void) const {return dbId;}

    const string &Type(void) const{return type;}
    void SetType(const char *newType);
    void SetType(const string &newType);

    const string &Value(void) const{return value;}
    void SetValue(const char *newValue);
    void SetValue(const string &newValue);

    void AddChild(Node *toAdd);
    void AddParent(Node *toAdd);

    void RemoveParent(Node *toRemove);
    void RemoveChild(Node *toRemove);

    bool Write(void);
    bool Read(void);

    bool operator ==(const Node &node);
    friend ostream& operator<<(ostream& os, const Node& node);
};

extern const Node NULL_NODE;

#endif
