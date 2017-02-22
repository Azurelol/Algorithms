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

    // Checks whether a matrix is connected
    bool Graph::IsConnected() const
    {
      //auto n = Vertices();
      //auto n_matrix = AdjacencyMatrix(Matrix);
      //for (auto i = 0; i < n - 1; ++i)
      //{
      //  n_matrix = n_matrix * Matrix;
      //}
      //// Now get the matrix that visits all odds
      //auto n_plus1_matrix = Multiply

      return false;

    }

    std::string Graph::Print(Representation representation) const
    {
      switch (representation)
      {
        case Representation::AdjacencyMatrix:
          return Matrix.ToString();
        case Representation::AdjacencyList:
          return List.ToString();
      }

      throw ("Invalid graph representation used!");
    }

  }
}