#include "../Sorting.h"

namespace Algorithms
{
  // Merges two sorted arrays (b, c) into one (a)
  void Merge(Sorting::Collection& b, Sorting::Collection& c, Sorting::Collection& a)
  {
    // The sizes of arrays b and c
    auto p = b.size();
    auto q = c.size();
    // Resize a to fit elements of both b and c
    a.resize(p + q);
    // Initialize pointers (array indices) to point to the first elements of the
    // arrays being merged
    int i = 0, j = 0, k = 0;
    while (i < p && j < q)
    {
      // Compare elements from arrays b and c,
      // inserting the smaller element of either into array a and
      // increment its index
      if (b[i] <= c[j])
        a[k] = b[i++];
      else
        a[k] = c[j++];

      // Obviously, also increment the index of the destination array
      // now that an element has been placed on it.
      k++;
    }

    // Copy the remaining elements of the other array to the end
    // of the new array
    if (i == p)
      std::copy(c.begin() + j, c.end(), a.begin() + k);
    else
      std::copy(b.begin() + i, b.end(), a.begin() + k);


  }

  void Sorting::MergeSort(Collection& array)
  {
    auto& a = array;    
    auto n = a.size();

    if (n < 2)
      return;
        
    // Copies each half of the array into two subarrays
    auto b = Collection(a.begin(), a.begin() + (n / 2));
    auto c = Collection(a.begin() + (n / 2), a.end());
    // Call the merge function recursively on each sub-array
    MergeSort(b);
    MergeSort(c);
    // Now merge both halves back into a
    Merge(b, c, a);
  }


}