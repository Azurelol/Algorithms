#pragma once

#include "..\Algorithms\Sorting.h"
using namespace Algorithms;

namespace Tests
{
  // Print function
  template <typename T>
  void PrintSortingResult(const std::vector<T>& unsorted, const std::vector<T>& sorted, std::string message)
  {
    Trace("Sorting algorithm = " + message);
    std::cout << "Unsorted: ";
    Print(unsorted);
    std::cout << "Sorted: ";
    Print(sorted);
  }

  // Test function
  void TestSort(std::function<void(std::vector<int>)> sortFunc, std::string funcName, const std::vector<int>& array)
  {
    auto copy = array;
    sortFunc(copy);
    PrintSortingResult(array, copy, funcName);
  }

  template <typename T>
  void TestSort(std::function<void(std::vector<T>)> sortFunc, std::string funcName, const std::vector<T>& collection)
  {
    auto copy = collection;
    sortFunc(copy);
    PrintSortingResult(collection, copy, funcName);
  }

  // Input data
  std::vector<int> IntegersSmall{ 7, 8, 18, 4, 5, 9, 14, 3, 10, 1, 2 };


  void BubbleSort()
  {    
    TestSort(Sorting::BubbleSort<int>, "Bubble sort", IntegersSmall);
  }

  void SelectionSort()
  {
    TestSort(Sorting::SelectionSort<int>, "Selection Sort", IntegersSmall);
  }

  void MergeSort()
  {
    TestSort(Sorting::MergeSort, "Selection Sort", IntegersSmall);
  }

  void QuickSort()
  {
    TestSort(Sorting::QuickSort, "Selection Sort", IntegersSmall);
  }

}