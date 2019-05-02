#include "SpecSuite.hpp"
#include "../node.hpp"
#include "../graph.hpp"

int main(void){
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
        Graph graph;
        Node *childNode = new Node("2nd Level", "Some Value");
        string childID = childNode->ID();

        graph.AddNode(childNode);
        
        expect(graph.Root()->Children().size() == 1);
        expect(graph.Root()->Children().front()->ID() == childID);
      });

  graphSpecs.Spec("Inserts a node between two others", [](){
        Graph graph;
        Node *olderNode = new Node("OldNode"),
             *newerNode = new Node("Newer Node");

        graph.AddNode(olderNode);
        graph.InsertNode(graph.Root(), newerNode, olderNode);

        expect(graph.Root()->Children().size() == 1);
        expect(graph.Root()->Children().front() == newerNode);
        expect(olderNode->Children().size() == 0);
        expect(olderNode->Parents().front() == newerNode);
      });

  graphSpecs.Spec("Properly adds an node to the mother index only once", [](){
        Graph graph;

        expect(graph.Index().size() == 1);

        Node *addManyTimes = new Node(),
             *anotherNode = new Node();

        graph.AddNode(addManyTimes);
        expect(graph.Index().size() == 2);

        graph.AddNode(anotherNode);
        expect(graph.Index().size() == 3);

        // Adding node to Graph again with different relationships, 
        // but it's already in the index and should not be added to the index again.
        graph.AddNode(anotherNode, addManyTimes);
        expect(graph.Index().size() == 3);
      });

  graphSpecs.Spec("Finds a node in its index", [](){
        Graph graph;
        Node *toFind = new Node();

        expect(graph.FindNode(toFind->ID()) == &NULL_NODE);

        graph.AddNode(toFind);
        expect(graph.FindNode(toFind->ID()) == toFind);
      });

  graphSpecs.Spec("Returns a path for a simple path", [](){
        Graph graph;
        Node *level2 = new Node(), 
             *level3 = new Node(), 
             *level4 = new Node();

        graph.AddNode(level2);
        graph.AddNode(level2, level3);
        graph.AddNode(level3, level4);

        GraphPaths *paths = graph.Paths(level4);

        expect(paths != NULL);
        expect(paths->size() == 1);
        expect(paths->front()->size() == 4);

        delete paths;
      });

  // graphSpecs.Spec("Returns expected path for a 2-level graph", [](){
  //       Graph graph;
  //       Node *secondLevel = new Node("2nd Level"),
  //            *thirdLevel = new Node("3rd Level");
  //
  //       graph.AddNode(secondLevel);
  //       graph.AddNode(secondLevel, thirdLevel);
  //
  //       paths = graph.PathTo(thirdLevel);
  //
  //     });

  graphSpecs.Run();
  return 0;
}
