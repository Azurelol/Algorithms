/******************************************************************************/
/*!
@file      Trace.h
@author    Christian Sagel
@par       email: ckpsm\@live.com
@note      Simple tracing functions.
*/
/******************************************************************************/
#pragma once
#include <iostream>
#include <sstream>

// Simple trace
#define Trace(message) std::cout << message << "\n"
// Add a new line
#define Newline(lines) std::cout; for (int i = 0; i < lines; ++i) std::cout << "\n"

char Alphabetize(int i)
{
  return static_cast<char>('A' + i);
}