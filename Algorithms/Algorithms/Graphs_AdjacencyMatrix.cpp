#include "Graphs.h"

namespace Algorithms
{
  namespace Graphs
  {
    Graph::AdjacencyMatrix::AdjacencyMatrix(int rows) : Matrix(rows)
    {
      //Matrix.resize(rows);
      for (auto i = 0; i < rows; i++)
        Matrix[i].resize(rows);
    }

    Graph::AdjacencyMatrix Graph::AdjacencyMatrix::operator*(AdjacencyMatrix other)
    {
      int rows = other.Rows();
      if (this->Rows() != rows)
        throw ("These matrices are not of the same size!");


      auto result = AdjacencyMatrix(other.Rows());

      // For every row
      for (auto i = 0; i < rows; ++i)
      {
        // For every column, multiply it by every other column
        for (auto j = 0; j < rows; ++j)
        {
          auto sum = 0.0f;
          for (auto k = 0; k < rows; ++k)
          {
            sum += this->Matrix[i][k] * other.Matrix[k][j];
          }

          // Set the result on the appropiate slot on the result matrix
          result.Matrix[i][j] = sum;
        }
      }

      return result;
    }

    Graph::AdjacencyMatrix Graph::AdjacencyMatrix::operator+(AdjacencyMatrix other)
    {
      auto rows = other.Rows();
      auto result = AdjacencyMatrix(other.Rows());

      for (auto i = 0; i < rows; ++i)
      {
        for (auto j = 0; j < rows; ++j)
        {
          result.Matrix[i][j] = other.Matrix[i][j] + other.Matrix[i][j];
        }
      }
      return result;
    }

    std::string Graph::AdjacencyMatrix::ToString()
    {
      std::stringstream builder;

      // Add the top row
      builder << "   ";
      for (auto i = 0; i < Matrix.size(); ++i)
        builder << "  " << Alphabetize(i);
      builder << "\n";

      for (auto i = 0; i < Matrix.size(); ++i)
      {
        builder << Alphabetize(i) << " [";
        for (auto j = 0; j < Matrix.size(); ++j)
        {
          builder << "  " << Matrix[i][j];
        }
        builder << " ]\n";
      }
      return builder.str();
    }
  }


}