#pragma once
#include "Graphs\Graph.h"

namespace Algorithms
{
  namespace Graphs
  {
    Graph::Path Dijkstra(const Graph& graph);
    Graph::Path Prim(const Graph& graph);
    Graph::Path Kruskal(const Graph& graph);
  }

}