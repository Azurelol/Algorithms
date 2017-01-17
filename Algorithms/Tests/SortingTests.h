#pragma once

#include "..\Algorithms\Sorting.h"
using namespace Algorithms;

#include "TestSuite.h"

namespace Tests
{
  // Print function
  template <typename T>
  void PrintSortingResult(const std::vector<T>& unsorted, const std::vector<T>& sorted, std::string message, float timeElapsed)
  {
    Trace("- Sorting algorithm: " + message);
    //Newline(1);
    Trace("Unsorted");
    Print(unsorted);
    Newline(1);
    Trace("Sorted [" << timeElapsed << "]");
    Print(sorted);
  }

  // Test function
  void TestSort(std::function<void(Sorting::Collection&)> sortFunc, std::string funcName, Sorting::Collection unsorted)
  {
    // Make a copy, which we will be sorting
    auto sorted = unsorted;

    auto timer = Time::ScopeTimer();
    sortFunc(sorted);
    auto timeElapsed = timer.Elapsed();

    PrintSortingResult(unsorted, sorted, funcName, timeElapsed);
  }

  //template <typename T>
  //void TestSort(std::function<void(std::vector<T>)> sortFunc, std::string funcName,  std::vector<T> input)
  //{
  //  auto sorted = input;
  //  sortFunc(sorted);
  //  PrintSortingResult(input, sorted, funcName);
  //}

  // Input data
  Sorting::Collection IntegersSmall{ 7, 8, 18, 4, 5, 9, 14, 3, 10, 2 };

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
    TestSort(Sorting::MergeSort, "Merge Sort", IntegersSmall);
  }

  void QuickSort()
  {
    TestSort(Sorting::QuickSort, "Quick Sort", IntegersSmall);
  }

  // Define all available tests
  TestSuite::Test::Group SortingTests = 
  {
    TestSuite::Test("Bubble Sort", BubbleSort),     
    TestSuite::Test("Selection Sort", SelectionSort),
    TestSuite::Test("Merge Sort", MergeSort),
    TestSuite::Test("Quick Sort", QuickSort),
  };




}