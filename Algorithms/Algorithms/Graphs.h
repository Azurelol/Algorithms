#pragma once
#include <vector>
#include <list>
#include <Trace.h>

namespace Algorithms
{
  namespace Graphs
  {
    struct Graph
    {
      //------------------------------------------------------------------------/
      // Aliases
      //------------------------------------------------------------------------/ 
      // The value type used by the graph. Either an integer or float.
      using ValueType = int;

      using Path = std::vector<unsigned>;

      //------------------------------------------------------------------------/
      // Declarations
      //------------------------------------------------------------------------/
      struct AdjacencyMatrix
      {
        std::vector<std::vector<ValueType>> Matrix;

        AdjacencyMatrix(int rows);
        //ValueType& operator[](int index);
        //const ValueType& operator[](int index) const;
        AdjacencyMatrix operator*(AdjacencyMatrix other);
        AdjacencyMatrix operator+(AdjacencyMatrix other);

        int Rows() const { return static_cast<int>(Matrix.size()); }
        std::string ToString();
      };

      struct AdjacencyList
      {
        std::vector<std::list<int>> List;
        AdjacencyList(const AdjacencyMatrix& matrix);
        void Build(const AdjacencyMatrix& matrix);
        std::string ToString();
      };

      struct EdgeList
      {
        using Edge = std::pair<int, int>;
        std::vector<Edge> List;
        EdgeList(const AdjacencyList& list);
        std::string ToString();
      };

      //------------------------------------------------------------------------/
      // Fields
      //------------------------------------------------------------------------/
      AdjacencyMatrix Matrix;
      AdjacencyList List;
      int _Vertices;
      bool Tracing;

      //------------------------------------------------------------------------/
      // Properties
      //------------------------------------------------------------------------/
      int Vertices() { return _Vertices; }

      //------------------------------------------------------------------------/
      // Methods
      //------------------------------------------------------------------------/
      Graph(int vertices);
      bool IsConnected() const;
    };





  }

}
