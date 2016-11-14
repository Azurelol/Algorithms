#pragma once
#include <cmath>
#include <ttmath\ttmath.h>

namespace Algorithms {

  using BigInteger = ttmath::Int<8>;

  class Counting {    
    static int IntFactorialLimit;

  public:
    //static BigInteger BigFactorial(int n);
    static int Factorial(int n);
    // n total items, k occurrences
    static int Combinations(int n, int k);
    static int Permutations(int n, int k);
    static int DifferentOutcomesAtLeast(int outcomes, int rolls, int occurrences);
    static int DifferentOutcomesAtMost(int outcomes, int rolls, int occurrences);

    class Problems {
      static void TestSimple();
    };

  };


}