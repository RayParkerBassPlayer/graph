#include "SpecSuite.hpp"
#include "../node.hpp"
#include "../Graph.hpp"

Graph *graph;

int main(void){
  graph = new Graph();
  SpecSuite nodeSuite("Node structure and validation");

  nodeSuite.Spec("Setters and getters properly store values.", [](){
        string type = "SomeType", value = "Some Value";
        Node node(type, value);

        expect(node.Value() != type);
        expect(node.Type() == type);
        expect(node.Value() == value);
      });


  nodeSuite.Run();

  SpecSuite graphSpecs("Graph manipulation");

  graphSpecs.Spec("Adds a node below the root", [](){
        Node *childNode = new Node("2nd Level", "Some Value");
        string childID = childNode->ID();

        graph->AddNode(childNode);
        
        expect(graph->Root()->Children().size() == 1);
        expect(graph->Root()->Children().front()->ID() == childID);
      });

  graphSpecs.Spec("Inserts a node between two others", [](){
        Node *olderNode = new Node("OldNode"),
             *newerNode = new Node("Newer Node");
             NodeVector::size_type initialRootChildren = graph->Root()->Children().size();

        graph->AddNode(olderNode);
        graph->InsertNode(graph->Root(), newerNode, olderNode);

        expect(graph->Root()->Children().size() == initialRootChildren + 1);
        // Can't depend on location here.  Index is sorted.
        expect(graph->Root()->Children().back() == newerNode);
        expect(olderNode->Children().size() == 0);
        expect(olderNode->Parents().front() == newerNode);
      });

  graphSpecs.Spec("Properly adds an node to the mother index only once", [](){
        int initialSize = graph->Index().size();

        Node *addManyTimes = new Node(),
             *anotherNode = new Node();

        graph->AddNode(addManyTimes);
        expect(graph->Index().size() == initialSize + 1);

        graph->AddNode(anotherNode);
        expect(graph->Index().size() == initialSize + 2);

        // Adding node to Graph again with different relationships, 
        // but it's already in the index and should not be added to the index again.
        graph->AddNode(anotherNode, addManyTimes);
        expect(graph->Index().size() == initialSize + 2);
      });

  graphSpecs.Spec("Finds a node in its index", [](){
        Node *toFind = new Node();

        expect(graph->FindNode(toFind->ID()) == &NULL_NODE);

        graph->AddNode(toFind);
        expect(graph->FindNode(toFind->ID()) == toFind);
      });

  graphSpecs.Spec("Returns a path for a simple path", [](){
        Node *level2 = new Node(), 
             *level3 = new Node(), 
             *level4 = new Node();

        graph->AddNode(level2);
        graph->AddNode(level2, level3);
        graph->AddNode(level3, level4);

        GraphPaths *paths = graph->Paths(level4);

        expect(paths != NULL);
        expect(paths->size() == 1);
        expect(paths->front()->size() == 4);

        GraphPath &onlyPath = *paths->front();
        vector<string> ids;

        ids.push_back(level4->ID());
        ids.push_back(level3->ID());
        ids.push_back(level2->ID());
        ids.push_back(graph->Root()->ID());

        int o = 0;

        for(Node *node : onlyPath){
          expect(node->ID() == ids[o]);
          o++;
        }

        delete paths;
      });

  graphSpecs.Spec("Returns paths for a multiple paths", [](){
        Node *level2 = new Node(), 
             *level3 = new Node(), 
             *level4 = new Node();

        graph->AddNode(level2);
        graph->AddNode(level2, level3);
        graph->AddNode(level3, level4);

        GraphPaths *paths = graph->Paths(level4);

        expect(paths != NULL);
        expect(paths->size() == 1);
        expect(paths->front()->size() == 4);

        delete paths;
      });

  graphSpecs.Spec("Returns siblings for a node in the simple case", [](){
        Node *sibling1 = new Node(),
             *sibling2 = new Node(),
             *sibling3 = new Node();

        graph->AddNode(sibling1);
        graph->AddNode(sibling2);
        graph->AddNode(sibling3);

        NodeList list;

        // Put siblings in a list for DRYer checking of return from graph.
        list.push_back(sibling1);
        list.push_back(sibling2);
        list.push_back(sibling3);

        NodeList *siblings = graph->Siblings(sibling1);

        // Go through all siblings and make sure that they are returned from the graph, including sibling1.
        for(Node *sibling : list){
          expect(find_if(siblings->begin(), siblings->end(), [&](Node *toCompare){
                  return sibling->ID() == toCompare->ID();
                }) != siblings->end());
        }

        delete siblings;
      });

  graphSpecs.Spec("Returns siblings for a node in a multi-parent case", [](){
        Node *sibling1 = new Node(),
             *sibling2 = new Node(),
             *sibling3 = new Node(),
             *sibling4 = new Node(),
             *sibling5 = new Node(),
             *sibling6 = new Node(),
             *parent1 = new Node(),
             *parent2 = new Node();

        graph->AddNode(parent1);     
        graph->AddNode(parent2);     

        graph->AddNode(parent1, sibling1);
        graph->AddNode(parent1, sibling2);
        graph->AddNode(parent1, sibling3);

        graph->AddNode(parent2, sibling4);
        graph->AddNode(parent2, sibling5);
        graph->AddNode(parent2, sibling6);

        // This is the connection -- siblings are all connected by sibling1 having common parents with all other siblings.
        sibling1->AddParent(parent2);

        NodeList list;

        // Put siblings in a list for DRYer checking of return from graph.
        list.push_back(sibling1);
        list.push_back(sibling2);
        list.push_back(sibling3);
        list.push_back(sibling4);
        list.push_back(sibling5);
        list.push_back(sibling6);

        NodeList *siblings = graph->Siblings(sibling1);

        expect(siblings->size() == 6);

        // Go through all siblings and make sure that they are returned from the graph, including sibling1.
        for(Node *sibling : list){
          expect(find_if(siblings->begin(), siblings->end(), [&](Node *toCompare){
                  return sibling->ID() == toCompare->ID();
                }) != siblings->end());
        }

        delete siblings;
      });
  // graphSpecs.Spec("Returns expected path for a 2-level graph", [](){
  //       Graph graph;
  //       Node *secondLevel = new Node("2nd Level"),
  //            *thirdLevel = new Node("3rd Level");
  //
  //       graph->AddNode(secondLevel);
  //       graph->AddNode(secondLevel, thirdLevel);
  //
  //       paths = graph->PathTo(thirdLevel);
  //
  //     });

  graphSpecs.Run();
  return 0;
}
