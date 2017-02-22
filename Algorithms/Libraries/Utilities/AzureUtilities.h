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
#include "Timer.h"

// Simple trace
//extern bool IsLogging = false;
#define Trace(message)                 \
        std::cout << message << "\n"

// Add a specified number of new lines
#define Newline(lines) std::cout; for (int i = 0; i < lines; ++i) std::cout << "\n"

///// <summary>
///// A simple RAII switch that will flip the value of the boolean when the scope exits
///// </summary>
//class ScopeBooleanSwitch
//{
//  bool& Reference;
//  public:
//  ~ScopeBooleanSwitch() { Reference = !Reference; }
//  ScopeBooleanSwitch(bool& reference) : Reference(reference) { Reference = true; }
//};
//
//#define LogThisScope auto scopeLogger = ScopeBooleanSwitch(IsLogging)

namespace Utilities
{
  char Alphabetize(int i);
  int ToInt(size_t i);

  void PrintResult(bool result, std::string success, std::string failure);
  void PrintIsA(bool result, std::string subject, std::string identity);

  template <typename T>
  void PrintTransformation(std::string algorithm, const T& before, const T& after)
  {
    Trace(algorithm);
    Trace("Before:");
    Trace(before);
    Trace("After:");
    Trace(after);
  }

  class StringBuilder
  {
    std::stringstream Stream;

  public:

    template <typename T>
    void Append(T obj)
    {
      Stream << obj;
    }

    template <typename T>
    void AppendLine(T obj)
    {
      Append(obj << "\n");
    }

    std::string ToString()
    {
      return Stream.str();
    }

  };

  // Prints the contents of an array
  template <typename Array>
  void PrintArray(const Array& array)
  {
    std::cout << "{";
    for (auto& element : array)
    {
      std::cout << element << " ";
    }
    std::cout << "}\n";
  }





}