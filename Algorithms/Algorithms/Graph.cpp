#include "Graph.h"

namespace Algorithms
{
  namespace Graphs
  {
    Graph::Graph(int vertices) : Matrix(vertices)
    {
    }

    Graph::Graph(const AdjacencyMatrix & matrix) : Matrix(matrix), List(matrix),_Vertices(matrix.Rows()) 
    {

    }

    bool Graph::IsConnected() const
    {
      return false;
    }

    std::string Graph::Print() const
    {
      return std::string();
    }

  }
}