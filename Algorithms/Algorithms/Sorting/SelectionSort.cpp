#include "../Sorting.h"

namespace Algorithms
{

  void Sorting::SelectionSort(Collection& array)
  {
    // During each pass, the unsorted element with the smallest
    // value is moved to its proper position in the array

    int minIndex;
    for (int i = 0; i < array.size() - 1; i++)
    {

      // We will start looking for the smallest element starting from
      // the current index
      minIndex = i;

      // We will iterate through the rest of the array from left to right,
      // looking for an element smaller than the current smallest
      for (int j = i + 1; j < array.size(); j++)
      {
        // If the element at the index is smaller than the current index
        // update the index
        if (array[j] < array[minIndex])
        {
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

}