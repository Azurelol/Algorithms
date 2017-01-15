#include "Graph.h"


namespace Algorithms
{
  namespace Graphs
  {
    Graph::EdgeList::EdgeList(const AdjacencyList & list)
    {
      for (auto i = 0; i < list.List.size(); ++i)
        for (auto j = list.List[i].begin(); j != list.List[i].end(); ++j)
        {
          auto& adjNode = *j;
          List.push_back(Edge(i, adjNode.Destination, adjNode.Weight));
        }
    }

    void Graph::EdgeList::AddEdge(VertexType source, VertexType destination, ValueType weight, Graph::EdgeList::EdgeType type)
    {
      //List.push_back(Edge())
    }

    std::string Graph::EdgeList::ToString()
    {
      std::stringstream builder;
      for (auto i = 0; i < List.size(); ++i)
      {
        auto& edge = List[i];
        builder << "{" << Alphabetize(edge.Source) << "," << Alphabetize(edge.Destination) << "}\n";
      }
      return builder.str();
    }




  }
}