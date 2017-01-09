#pragma once
#include <vector>
#include <list>

namespace Algorithms {
  
  struct Graph 
  {
    //------------------------------------------------------------------------/
    // Representations
    //------------------------------------------------------------------------/
    struct AdjacencyMatrix {
      std::vector<std::vector<int>> Matrix;
      AdjacencyMatrix(int rows);
      AdjacencyMatrix operator*(AdjacencyMatrix lhs);
    private:
    };


    //------------------------------------------------------------------------/
    // Aliases
    //------------------------------------------------------------------------/
    using Edge = std::pair<int, int>;
    //using AdjacencyMatrix = std::vector<std::vector<int>>;
    using AdjacencyList = std::vector<std::list<int>>;
    using EdgeList = std::vector<Edge>;
    using Path = std::vector<unsigned>;

    //------------------------------------------------------------------------/
    // Properties
    //------------------------------------------------------------------------/
    AdjacencyMatrix Matrix;
    AdjacencyList List;
    bool Tracing;

    //------------------------------------------------------------------------/
    // Methods
    //------------------------------------------------------------------------/
    // Builds a matrix
    static AdjacencyMatrix BuildMatrix(int rows);
    // Builds an adjacency list
    static AdjacencyList BuildList(const AdjacencyMatrix& matrix);
    // Builds an edge list
    static EdgeList BuildEdgeList(const AdjacencyList& list);
    // Multiplies a matrix
    static AdjacencyMatrix Multiply(const AdjacencyMatrix& lhs, const AdjacencyMatrix& rhs);
    // Adds two matrices together
    static AdjacencyMatrix Add(const AdjacencyMatrix& lhs, const AdjacencyMatrix& rhs);
    // Prints the contents of a matrix
    std::string Print(const AdjacencyMatrix& matrix);
    std::string Print(const AdjacencyList& list);
    std::string Print(const EdgeList& edgeList);

    // Properties

    Graph(int vertices);
    void BuildList();

    // Prints the contents of the adjacency matrix
    void PrintAdjacencyMatrix() const { Trace(Print(Matrix)); }
    // Prints the contents of the adjacency list
    void PrintList() const { Trace(Print(List)); }
    // Finds whether this graph is connected or not
    bool IsConnected() const;
  };
}
