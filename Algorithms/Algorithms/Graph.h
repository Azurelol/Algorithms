#pragma once

namespace Algorithms
{
  namespace Graphs
  {    
    class Graph
    {
    public:

      //------------------------------------------------------------------------/
      // Aliases
      //------------------------------------------------------------------------/ 
      // The type of vertex. Usually a char or an unsigned integer.
      using VertexType = unsigned;
      // The value type used by the graph. Either an unsigned integer or float.
      using ValueType = float;

      using Path = std::vector<unsigned>;

      //------------------------------------------------------------------------/
      // Declarations
      //------------------------------------------------------------------------/      
      //struct Vertex
      //{
      //  VertexType ID;
      //  std::vector<Vertex> Neighbors;
      //  Vertex(VertexType id) : ID(id) {}
      //};

      
      struct AdjacencyMatrix
      {
        std::vector<std::vector<ValueType>> Matrix;

        AdjacencyMatrix(int rows);
        AdjacencyMatrix operator*(AdjacencyMatrix other);
        AdjacencyMatrix operator+(AdjacencyMatrix other);

        int Rows() const { return static_cast<int>(Matrix.size()); }
        std::string ToString();
      };

      struct AdjacencyNode
      {
        VertexType Destination;
        ValueType Weight;
        AdjacencyNode(VertexType dest, ValueType weight) : Destination(dest), Weight(weight) {}
      };

      struct AdjacencyList
      {
        std::vector<std::list<AdjacencyNode>> List;
        AdjacencyList(const AdjacencyMatrix& matrix);
        AdjacencyList() {}
        void Build(const AdjacencyMatrix& matrix);
        std::string ToString();
      };
      
      struct Edge
      {
        VertexType Source;
        VertexType Destination;
        ValueType Weight;
        Edge(VertexType source, VertexType destination, ValueType weight)
          : Source(source), Destination(destination), Weight(weight)
        {
        }
      };

      struct EdgeList
      {
        enum class EdgeType
        {
          Directed,
          Undirected
        };

        std::vector<Edge> List;

        EdgeList(const AdjacencyList& list);
        EdgeList() {}
        void AddEdge(VertexType source, VertexType destination, ValueType weight, EdgeType type);
        std::string ToString();
      };


    private:

      //------------------------------------------------------------------------/
      // Fields
      //------------------------------------------------------------------------/
      AdjacencyMatrix Matrix;
      AdjacencyList List;
      int _Vertices;
      bool Tracing;
      

    public:

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
