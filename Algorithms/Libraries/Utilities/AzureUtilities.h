/******************************************************************************/
/*!
@file      AzureUtilities.h
@author    Christian Sagel
@par       email: ckpsm\@live.com
@note      Simple tracing functions.
*/
/******************************************************************************/
#pragma once
#include <iostream>
#include <sstream>
#include <vector>

// Simple trace
#define Trace(message) std::cout << message << "\n"
// Add a new line
#define Newline(lines) std::cout; for (int i = 0; i < lines; ++i) std::cout << "\n"

namespace Utilities
{
  char Alphabetize(int i);

  void PrintResult(bool result, std::string success, std::string failure);
  void PrintIsA(bool result, std::string subject, std::string identity);

  template <typename Array>
  void Print(Array array)
  {
    std::cout << "{";
    for (auto& element : array)
    {
      std::cout << element << " ";
    }
    std::cout << "}\n";
  }

}