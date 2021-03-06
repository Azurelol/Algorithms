/******************************************************************************/
/*!
@file      Sort.h
@author    Christian Sagel
@par       email: ckpsm\@live.com
@date      9/29/2016
@brief     Common sort algorithms.
*/
/******************************************************************************/
#pragma once

namespace Algorithms
{

  class Sorting
  {

  public:

    using DataType = int;
    using Collection = std::vector<DataType>;

    // Start at the beginning of the array and swap the first two elements if
    // the first is greater than the second. Then, we go to the next pair, and
    // so on, continuously making sweeps of the array until it is sorted.
    // Runtime: O(n^2), Memory: O(1)
    static void BubbleSort(Collection& array);

    // Finds the smallest element using a linear scan and move it to the front
    // (swapping it with the front element). Then we find the second smallest
    // element and move it, again doing a linear scan. We continue doing this
    // until all the elements are in place.
    // Runtime: O(n^2), Memory: O(1)    
    static void SelectionSort(Collection& array);

    // Divides the array in half, sorting each of those halves, then merging
    // them back together. Each of these halves has the same sorting algorithm
    // applied to it. Eventually we are merging single-element arrays.
    // Runtime: O(n log (n)), Memory: O(?)
    static void MergeSort(Collection& array);

    // Picks an element as a pivot and partitions the given array around
    // the picket pivot.
    static void QuickSort(Collection& array);

    static void InsertionSort(Collection& array);

    static void HeapSort(Collection& array);


    //------------------------------------------------------------------------/
    // Templated versions
    //------------------------------------------------------------------------/
    template <typename T>
    static void BubbleSort(std::vector<T>& collection);

    template <typename T>
    static void SelectionSort(std::vector<T>& collection);

  private:

  };



}

// Templates
#include "Sorting.hpp"