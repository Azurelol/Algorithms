#pragma once

#include "..\Algorithms\Graphs.h"
using namespace Algorithms::Graphs;
//#include <experimental\>

namespace Tests
{
  //------------------------------------------------------------------------/
  // Data Sets
  //------------------------------------------------------------------------/
  Graph::AdjacencyMatrix::DynamicContainer Small = 
  {
    {0,3,1,0},
    {3,0,7,1},
    {1,7,0,0},
    {0,1,0,0}
  };

  //------------------------------------------------------------------------/
  // Print
  //------------------------------------------------------------------------/
  void PrintIsConnected(const Graph& graph)
  {
    Trace("-----------------------");
    Trace("The graph G:");
    Trace(graph.Print());
    if (graph.IsConnected())
      Trace("G is connected!");
    else
      Trace("G is not connected!");
    Trace("-----------------------");
  }

  void PrintShortestPath(const Graph& graph, Graph::Path::Function graphFunc, std::string algorithmName)
  {
    Trace("The graph G");
    Trace(graph.Print());
    auto path = graphFunc(graph);
    Trace("The shortest path for G using " << algorithmName << " of length = '" << path.Count() << "' is:");
    Trace(path.ToString());
  }

  void PrintMinimumSpanningTree(const Graph& graph, Graph::Path::Function graphFunc, std::string algorithmName)
  {
    Trace("The graph G");
    Trace(graph.Print());
    Trace("Finding the minimum spanning tree for G using " << algorithmName << ":");
    auto path = graphFunc(graph);
    Trace("The minimum spanning tree is formed by the vertices:");
  }


  //------------------------------------------------------------------------/
  // Tests
  //------------------------------------------------------------------------/
  void Connectivity()
  {
    auto a = Graph(Small);
    PrintIsConnected(a);
    //auto a = Graphs::Graph(4);
    //a.Matrix[0] = { 0,3,1,0 };
    //a.Matrix[1] = { 3,0,7,1 };
    //a.Matrix[2] = { 1,7,0,0 };
    //a.Matrix[3] = { 0,1,0,0 };
    //PrintIsConnected(a);
  }

  void Djikstra()
  {

  }

  void Prim()
  {

  }

  void Kruskal()
  {

  }

  // Define all available tests
  TestSuite::Test::Group GraphTests =
  {
    TestSuite::Test("Connectivity", Connectivity),
    TestSuite::Test("Djikstra", Djikstra),
    TestSuite::Test("Kruskal", Kruskal)
  };

}
