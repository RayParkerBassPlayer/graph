#ifndef __SPEC_SUITE_HPP
#define __SPEC_SUITE_HPP

#include <string>
#include <list>
#include <sstream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#define STR(x) #x
#define expect(x) if (!(x)) { stringstream s; s << STR(x) << " not true at " << __FILE__ <<":"<< __LINE__; throw s.str(); } 

using std::list;
using std::string;
using std::stringstream;
using std::exception;
using std::pair;

typedef void (*TestMethod)(void);

typedef pair<TestMethod, string> TestEntry;
typedef list<TestEntry> TestList;

class SpecSuite {
  string name;
  TestList tests;

  public:
    SpecSuite(const char *Name):name(Name){}

    void Spec(const char *description, TestMethod method){
      tests.push_back(TestEntry(method, description));
    }

    void eq(bool condition, const char* file, int line){
      stringstream stream;
      stream << "Equality not met at " << file << ":" << line;

      if(!condition){
        throw stream.str();
      }
    }

    void Run(void) const{
      spdlog::info("SUITE: Starting run of '{:s}'", name);
      int numErrors = 0;

      for(TestEntry entry : tests){
        try{
          entry.first();
          spdlog::info("{:s}: Passed", entry.second);
        }
        catch(exception &e){
          spdlog::error("{:s} -- Exception caught: {:s}", entry.second, e.what());
          numErrors++;
        }
        catch(const string &message){
          spdlog::error("{:s}: {:s}", entry.second, message);
          numErrors++;
        }
        catch(const char *message){
          spdlog::error("{:s}: {:s}", entry.second, message);
          numErrors++;
        }
        catch(...){
          spdlog::error("{:s} -- Unknown exception caught.", entry.second);
          numErrors++;
        }

      }

      spdlog::info("SUITE: '{:s}' finished {:d} tests with {:d} error(s).", name, tests.size(), numErrors);
    }
};

#endif
