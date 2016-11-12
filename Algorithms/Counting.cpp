#include "Counting.h"

namespace Algorithms {

  int Counting::Factorial(int n) {    
    int factorial = 1;
    for (int i = 1; i <= n; ++i)
      factorial = factorial * i;
    return factorial;
  }

  int Counting::Combinations(int n, int k) {
    int combinations = Factorial(n) / (Factorial(k) * Factorial(n - k));
    return combinations;
  }

  int Counting::Permutations(int n, int k) {
    int permutations = n;
    for (int i = 0; i < k - 1; ++i)
      permutations *= n;
    return permutations;
  }

}