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

      //using Path = std::vector<VertexType>;

      //------------------------------------------------------------------------/
      // Declarations
      //------------------------------------------------------------------------/      
      //struct Vertex
      //{
      //  VertexType ID;
      //  std::vector<Vertex> Neighbors;
      //  Vertex(VertexType id) : ID(id) {}
      //};

      struct Path
      {
        std::vector<VertexType> Vertices;

        int Count() { return ToInt(Vertices.size()); }
        void Add(VertexType v) { Vertices.push_back(v); }
        std::string ToString()
        {
          StringBuilder builder;
          for (auto& p : Vertices)
            builder.Append(p);
          return builder.ToString();
        }

        using Function = std::function<Path(const Graph&)>;
      };
      
      //template <typename Size>
      //struct StaticMatrix {
      //  std::array<std::array<int, Size>, Size> Damn;
      //};

      struct AdjacencyMatrix
      {
        using DynamicContainer = std::vector<std::vector<VertexType>>;
        DynamicContainer Matrix;

        //AdjacencyMatrix(std)
        AdjacencyMatrix(int rows);
        AdjacencyMatrix(DynamicContainer mtx) : Matrix(mtx) {}
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
      bool IsLogging;
      

    public:

      //------------------------------------------------------------------------/
      // Properties
      //------------------------------------------------------------------------/
      int Vertices() { return _Vertices; }

      //------------------------------------------------------------------------/
      // Methods
      //------------------------------------------------------------------------/
      Graph(int vertices);
      Graph(const AdjacencyMatrix& matrix);
      Graph(const AdjacencyList& list);
      bool IsConnected() const;
      std::string Print() const;
      
    };





  }

}
