#include "../Sorting.h"

namespace Algorithms
{

  void Sorting::BubbleSort(Collection& array)
  {
    // Set the flag to true for the first pass
    bool continueSorting = true;

    for (int i = 0; i < array.size() && continueSorting; i++)
    {
      // If there is no swaps on this iteration, do not continue
      continueSorting = false;

      // Now iterate through the array from start to end looking for swaps
      // [array.size() - 1] is used because we are 0-index ho!
      for (int j = 0; j < array.size() - 1; j++)
      {
        // If the next element is lesser than the current one
        if (array[j + 1] < array[j])
        {
          auto temp = array[j];
          array[j] = array[j + 1];
          array[j + 1] = temp;
          continueSorting = true;
        }
      }
    }
  }





}