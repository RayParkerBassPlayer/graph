#include <iostream>
#include <string>
#include <list>
#include <utility>
#include "../global_includes.hpp"

#include "../node.hpp"

using namespace std;

typedef bool (*TestMethod)(void);

typedef pair<TestMethod, string> TestEntry;
typedef list<TestEntry> TestList;

TestList tests;

bool NodeFields(void){
  string type = "generic",
         value = "Some Value";
  Node node(type, value);

  if(node.Type() != type)
    return false;

  if(node.Value() != value)
    return false;

  return true;
}

int main(void){
  spdlog::info("Starting tests...");
  tests.push_back(TestEntry(&NodeFields, "Node fields work as expected."));

  for(TestEntry entry:tests){
    if(entry.first())
      spdlog::info(entry.second);
    else
      spdlog::error(entry.second);
  }

  spdlog::info("Tada!");
  return 0;
}
