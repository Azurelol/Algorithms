/******************************************************************************/
/*!
@file      Driver.cpp
@author    Christian Sagel
@par       email: ckpsm\@live.com
@date      11/12/2016
@brief     Main driver for my Algorithms demonstration.
@note      Hours spent: 7
*/
/******************************************************************************/
// Tests
#include "TestsInclude.h"

int main(void)
{
  auto testSuite = Tests::TestSuite();
  testSuite.Add("Bubble Sort", Tests::BubbleSort);
  testSuite.Add("Selection Sort", Tests::SelectionSort);
  testSuite.Add("Nerge Sort", Tests::MergeSort);
  testSuite.Add("Quick Sort", Tests::QuickSort);

  try
  {
    testSuite.Display();
  }

  catch (std::string msg)
  {
    Trace(msg);
  }

  Trace("Press any key to exit...");
  std::cin.get();
}