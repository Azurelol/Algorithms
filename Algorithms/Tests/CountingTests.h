#pragma once

#include "..\Algorithms\Counting.h"
using namespace Algorithms;

namespace Tests
{
  //intmax_t Factorial(int n)
  //{
  //
  //  intmax_t factorial = 1;
  //  for (int i = 1; i <= n; ++i)
  //    factorial = factorial * i;
  //
  //  return factorial;
  //}

  void CombinationsOf(int n, int k)
  {
    Trace("Combinations of " << n << " and " << k << " = " << Counting::Combinations(n, k));
  }


}
