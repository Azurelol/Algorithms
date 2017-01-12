#include "Graphs.h"

namespace Algorithms
{
  namespace Graphs
  {
    Graph::AdjacencyList::AdjacencyList(const AdjacencyMatrix& matrix)
    {
      Build(matrix);
    }

    void Graph::AdjacencyList::Build(const AdjacencyMatrix & matrix)
    {
      int rows = matrix.Rows();
      List.resize(rows);
      for (auto i = 0; i < rows; ++i)
      {
        for (auto j = 0; j < rows; ++j)
        {
          // If there is a value at this cell, these two vertices make an edge
          if (matrix.Matrix[i][j] != 0)
          {
            List[i].push_back(j);

          }
        }
      }
    }

    std::string Graph::AdjacencyList::ToString()
    {
      std::stringstream builder;
      for (auto i = 0; i < List.size(); ++i)
      {
        builder << Alphabetize(i) << ": {";
        for (auto j = List[i].begin(); j != List[i].end(); ++j)
        {
          builder << " " << Alphabetize(*j);
        }
        builder << " }\n";
      }
      return builder.str();
    }

    Graph::EdgeList::EdgeList(const AdjacencyList & list)
    {
      for (auto i = 0; i < list.List.size(); ++i)
        for (auto j = list.List[i].begin(); j != list.List[i].end(); ++j)
          List.push_back(Edge(i, *j));
    }

    std::string Graph::EdgeList::ToString()
    {
      std::stringstream builder;
      for (auto i = 0; i < List.size(); ++i)
      {
        auto& edge = List[i];
        builder << "{" << Alphabetize(edge.first) << "," << Alphabetize(edge.second) << "}\n";
      }
      return builder.str();
    }
  }

}