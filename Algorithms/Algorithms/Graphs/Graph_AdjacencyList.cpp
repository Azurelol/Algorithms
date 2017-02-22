#include "Graph.h"


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
          auto val = static_cast<ValueType>(matrix.Matrix[i][j]);
          // If there is a value at this cell, these two vertices make an edge
          if (matrix.Matrix[i][j] != 0)
          {
            List[i].push_back(AdjacencyNode(j, val));
          }
        }
      }
    }

    std::string Graph::AdjacencyList::ToString() const
    {
      std::stringstream builder;
      for (auto i = 0; i < List.size(); ++i)
      {
        builder << Alphabetize(i) << ": {";
        for (auto j = List[i].begin(); j != List[i].end(); ++j)
        {
          builder << " " << Alphabetize((*j).Destination);
        }
        builder << " }\n";
      }
      return builder.str();
    }



  }

}