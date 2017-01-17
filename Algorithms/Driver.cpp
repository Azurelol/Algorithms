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
  // Add all tests
  auto testSuite = Tests::TestSuite();
  testSuite.Add("Sorting", Tests::SortingTests);


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