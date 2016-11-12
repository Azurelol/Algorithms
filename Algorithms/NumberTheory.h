#pragma once

#include <vector>

namespace Algorithms {

  class NumberTheory {

  public:
    using IntegerPair = std::pair<int, int>;
    int SolveSystemOfCongruences(std::vector<IntegerPair> pairs);
    static unsigned GCD(unsigned a, unsigned b);
    int ModularInverse(unsigned a, unsigned m);


  };

}
