#pragma once
#include <iostream>

// Simple trace
#define Trace(message) std::cout << message << "\n"
// Add a new line
#define Newline(lines) std::cout; for (int i = 0; i < lines; ++i) std::cout << "\n"