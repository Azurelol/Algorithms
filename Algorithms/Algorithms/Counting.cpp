#include "Counting.h"

namespace Algorithms {

  int Counting::IntFactorialLimit = 20;


  int Counting::Factorial(int n) {

    if (n > IntFactorialLimit) {
      throw new std::exception("Cannot calculate factorials larger than 20 using integers!");
    }

    int factorial = 1;
    for (int i = 1; i <= n; ++i)
      factorial = factorial * i;
    
    return factorial;
  }

  
  int Counting::Combinations(int n, int k) {
    
    int combinations;
    if (n > IntFactorialLimit || k > IntFactorialLimit)
      throw new std::exception("Cannot calculate factorials larger than 20 using integers!");
      //combinations; // = (BigFactorial(n) / (BigFactorial(k) * BigFactorial(n - k))).ToInt();
    else
      combinations =  (Factorial(n) / (Factorial(k) * Factorial(n - k)));

    return combinations;
  }

  int Counting::Permutations(int n, int k) {
    int permutations = n;
    for (int i = 0; i < k - 1; ++i)
      permutations *= n;
    return permutations;
  }

  int Counting::DifferentOutcomesAtLeast(int outcomes, int rolls, int occurrences) {
    int diffOutcomes = outcomes;
    // Subtract the possiblity of the opposite
    for (int i = 0; i < occurrences; ++i)
      diffOutcomes -= Counting::Combinations(rolls, i);
    return diffOutcomes;
  }

  int Counting::DifferentOutcomesAtMost(int outcomes, int rolls, int occurrences) {
    int diffOutcomes = outcomes;
    // Subtract the possiblity of more than times
    for (int i = rolls; i > occurrences; --i)
      diffOutcomes -= Counting::Combinations(rolls, i);
    return diffOutcomes;
  }

  void Counting::Problems::TestSimple() {

    int coinFlips = 10, possibilities = 2;
    int differentOutcomes = Counting::Permutations(2, 10);
    int differentOutcomesLeast2Heads = DifferentOutcomesAtLeast(differentOutcomes, coinFlips, 2);
    int differentOutcomesatMost6Heads = DifferentOutcomesAtMost(differentOutcomes, coinFlips, 6);

    // Among 52 peolpe, at least how many were born in the same month
    int people = 52, months = 12;
    int bornInSameMonthAtLeast = static_cast<int>(std::ceilf(static_cast<float>(people) / static_cast<float>(months)));
    // Assuming that no one is born on Feb. 29 (leap day), how many people should be selected to guarantee that at least
    // 6 were born on the same day, not considering the year?
    int peopleSelectedAtLeast6BornOnSameDay = (5 * 365) + 1;

    

  }

}