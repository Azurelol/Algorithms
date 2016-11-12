#include "Sort.h"

namespace Algorithms {

  void Sorting::BubbleSort(std::vector<int>& array)
  {
    // Set the flag to true for the first pass
    bool continueSorting = true;

    for (int i = 0; i < array.size() && continueSorting; i++) 
    {
      // If there is no swaps on this iteration, do not continue
      continueSorting = false;

      // Now iterate through the array from start to end looking for swaps
      // [array.size() - 1] is used because we are 0-index ho!
      for (int j = 0; j < array.size() - 1; j++) {
        // If the next element is lesser than the current one
        if (array[j+1] < array[j]) {
          auto temp = array[j];
          array[j] = array[j + 1];
          array[j + 1] = temp;
          continueSorting = true;
        }
      }


    }
  }

  void Sorting::SelectionSort(std::vector<int>& array)
  {
    // During each pass, the unsorted element with the smallest
    // value is moved to its proper position in the array
    
    int minIndex;
    for (int i = 0; i < array.size() - 1; i++) {

      // We will start looking for the smallest element starting from
      // the current index
      minIndex = i;

      // We will iterate through the rest of the array from left to right,
      // looking for an element smaller than the current smallest
      for (int j = i + 1; j < array.size(); j++) {        
        // If the element at the index is smaller than the current index
        // update the index
        if (array[j] < array[minIndex]) {
          minIndex = j;
        }
      }

      // Now let's place the element with the smallest index at this position.
      // This will be done by swapping.
      auto tmp = array[i];
      array[i] = array[minIndex];
      array[minIndex] = tmp;
    }
    
  }

  void Merge(int array[], int helper[], int low, int high) 
  {

  }

  void Sorting::MergeSort(std::vector<int> array) 
  {
    //int helper[array.size()];
  }

}