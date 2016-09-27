#pragma once
#include <vector>

namespace Algorithms {

  class Sorting {
    enum class Type {
      QuickSort,
      MergeSort
    };

  public:
    void Sort(std::vector<int> array, Type type = Type::QuickSort);

  private:




  };

}