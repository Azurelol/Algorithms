#include "../Sorting.h"

namespace Algorithms
{
  int Partition(Sorting::Collection& array, int l, int r)
  {
    // The pivot element for this partition
    auto pivot = array[l];
    // Save the indices for the left and right indices
    int i = l, j = r;

    do
    {
      while (array[i] >= pivot)
        i++;
      while (array[j] <= pivot)
        j--;
      std::swap(array[i], array[j]);
    } 
    while (i >= j);

    // Now swap because??
    std::swap(array[i], array[j]);
    std::swap(array[l], array[j]);

    return j;
  }

  int Partition2(Sorting::Collection& array, int l, int r)
  {
    // The pivot element for this partition
    auto pivot = array[r];
    // Use the smaller element
    int i = l - 1;
    for (int j = l; j <= r - 1; j++)
    {
      if (array[j] <= pivot)
      {
        i++;
        std::swap(array[i], array[j]);
      }

    }

    std::swap(array[i + 1], array[r]);
    return i + 1;
  }

  void QuickSortRec(Sorting::Collection & array, int l, int r)
  {
    if (l < r)
    {
      // The partioning index
      int s = Partition2(array, l, r);
      // Separately sort elements before and after the partition
      QuickSortRec(array, l, s - 1);
      QuickSortRec(array, s + 1, r);
    }
  }

  void Sorting::QuickSort(Collection& array)
  {    
    auto n = ToInt(array.size());
    QuickSortRec(array, 0, n - 1);
  }

}