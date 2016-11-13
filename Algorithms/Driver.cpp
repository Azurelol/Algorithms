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
// Function pointers, ho!
#include <functional>

// Algorithms
#include "Algorithms.h"
using namespace Algorithms;


void Test(bool result, std::string success, std::string failure) {
  if (result) 
    Trace(success);  
  else
    Trace(failure);
}

void PrintIsA(bool result, std::string subject, std::string identity) {
  std::string print;
  if (result)
    Trace(subject + " is " + identity);
  else
    Trace(subject + " is not " + identity);
}

template <typename Array>
void Print(Array array) {
  std::cout << "{";
  for (auto& element : array) {
    std::cout << element << " ";
  }
  std::cout << "}\n";
}

void PrintSort(const std::vector<int>& unsorted, const std::vector<int>& sorted, std::string message) {
  Trace("Sorting algorithm = " + message);
  std::cout << "Unsorted: ";
  Print(unsorted);
  std::cout << "Sorted: ";
  Print(sorted);
}

void TestStrings() {
  Trace("------------------------------");
  Trace("STRING MANIPULATION ALGORITHMS");
  Trace("------------------------------");
  // 1. Determines if a string has all unique characters
  std::string uniqueString = "research";
  bool isUnique = Algorithms::String::Unique(uniqueString);
  PrintIsA(isUnique, uniqueString, "unique!");
  // 2. Reverses a nul-terminated string
  char reversedString[] = "Bienvenido!";
  Trace("Reversing '" + std::string(reversedString) + "'");
  Algorithms::String::Reverse(reversedString);
  Trace("It is now '" + std::string(reversedString) + "'");
  // 3. Given two strings, decide if one is a permutation of the other
  // By default set to not be case-sensitive
  std::string anagramLeft = "Dog";
  std::string anagramRight = "God";
  bool isAnagram = Algorithms::String::Permutation(anagramLeft, anagramRight);
  Test(isAnagram, anagramLeft + " is an anagram of " + anagramRight, 
                  anagramLeft + " is not an anagram of " + anagramRight);
  // 4. Check if a string is a palindrome
  std::string palindromeString = "lol";
  bool isPalindrome = Algorithms::String::Palindrome(palindromeString);
  PrintIsA(isPalindrome, palindromeString, "a palindrome!");
  // 5. Print the duplicate characters in the string, with count
  std::string duplicatePrint = "HeyHeyHey";
  Algorithms::String::PrintDuplicates(duplicatePrint);
  // 6. Print the occurrences of a character in a string
  char character = 'e';
  std::cout << "The character '" << character << "' is found " <<
            std::to_string(Algorithms::String::Occurrences(uniqueString, character))
            << " times in the string " << uniqueString << "\n";
  // 7. Find if a string is a substring of another
  std::string parent = "Megaboss", child = "boss";
  PrintIsA(Algorithms::String::Substring(parent, child), child, " a substring of '" + parent + "'");

}

void TestSort(std::function<void(std::vector<int>)> sortFunc, std::string funcName, const std::vector<int>& array) {
  auto copy = array;
  sortFunc(copy);
  PrintSort(array, copy, funcName);
}

void TestSorting() {

  // 1. Simple sorting of integers
  std::vector<int> integersSmall{ 7, 8, 18, 4, 5, 9, 14, 3 };
  Sorting::BubbleSort(integersSmall);
  TestSort(Sorting::BubbleSort, "Bubble sort", integersSmall);
  TestSort(Sorting::SelectionSort, "Selection Sort", integersSmall);
}

void TestCipher() {
  std::string encodedMessage = "DOFKVFVBSPRLNHTLZ";

  Trace("1. Shift Cipher: Decoding '" + encodedMessage + "'. Possible values:");
  for (unsigned i = 0; i < Cipher::PossibleShiftValues; ++i) {
    Trace("Shift value = " << i << ", decoded message = " << Cipher::Shift(encodedMessage, i));
  }
}

void CombinationsOf(int n, int k) {
  Trace("Combinations of " << n << " and " << k << " = " << Counting::Combinations(n, k));
}

void DifferentOutcomesOf(int n, int k) {
  //Trace("Different outcome " << n << " and " << k << " = " << Counting::Combinations(n, k));/
}

int DifferentOutcomesAtLeast(int outcomes, int rolls, int occurrences) {
  int diffOutcomes = outcomes;
  // Subtract the possiblity of the opposite
  for (int i = 0; i < occurrences; ++i)
    diffOutcomes -= Counting::Combinations(rolls, i);
  return diffOutcomes;
}

int DifferentOutcomesAtMost(int outcomes, int rolls, int occurrences) {
  int diffOutcomes = outcomes;
  // Subtract the possiblity of more than times
  for (int i = rolls; i > occurrences; --i)
    diffOutcomes -= Counting::Combinations(rolls, i);
  return diffOutcomes;
}

int main(void) {

  //TestStrings();
  //TestSorting();
  //TestCipher();
  
  CombinationsOf(10, 2);

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
  
  // A standard deck of cards consists of four suits (clubs, diamonds, hearts, and spades), with each suit containing 13 cards 
  // (ace, two through ten, jack, queen, and king) for a total of 52 cards in all. 
  int cards = 52;


  Trace("Press any key to exit...");
  std::cin.get();

}

