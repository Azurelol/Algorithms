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
// Problems
//#include "Problems.h"
//using namespace Problems;


void Test(bool result, std::string success, std::string failure)
{
  if (result)
    Trace(success);
  else
    Trace(failure);
}

void PrintIsA(bool result, std::string subject, std::string identity)
{
  std::string print;
  if (result)
    Trace(subject + " is " + identity);
  else
    Trace(subject + " is not " + identity);
}

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

void PrintSort(const std::vector<int>& unsorted, const std::vector<int>& sorted, std::string message)
{
  Trace("Sorting algorithm = " + message);
  std::cout << "Unsorted: ";
  Print(unsorted);
  std::cout << "Sorted: ";
  Print(sorted);
}

void TestStrings()
{
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

void TestSort(std::function<void(std::vector<int>)> sortFunc, std::string funcName, const std::vector<int>& array)
{
  auto copy = array;
  sortFunc(copy);
  PrintSort(array, copy, funcName);
}

void TestSorting()
{

  // 1. Simple sorting of integers
  std::vector<int> integersSmall{ 7, 8, 18, 4, 5, 9, 14, 3 };
  Sorting::BubbleSort(integersSmall);
  TestSort(Sorting::BubbleSort, "Bubble sort", integersSmall);
  TestSort(Sorting::SelectionSort, "Selection Sort", integersSmall);
}

void TestCipher()
{
  std::string encodedMessage = "DOFKVFVBSPRLNHTLZ";

  Trace("1. Shift Cipher: Decoding '" + encodedMessage + "'. Possible values:");
  for (unsigned i = 0; i < Cipher::PossibleShiftValues; ++i)
  {
    Trace("Shift value = " << i << ", decoded message = " << Cipher::Shift(encodedMessage, i));
  }
}

void CombinationsOf(int n, int k)
{
  Trace("Combinations of " << n << " and " << k << " = " << Counting::Combinations(n, k));
}

intmax_t Factorial(int n)
{

  intmax_t factorial = 1;
  for (int i = 1; i <= n; ++i)
    factorial = factorial * i;

  return factorial;
}

int main(void)
{
  try
  {

  }
  catch (std::string msg)
  {
    Trace(msg);
  }
  std::cin.get();
}

  //TestStrings();
  //TestSorting();
  //TestCipher();

  //auto hoho = Factorial(52);

//  // A standard deck of cards consists of four suits (clubs, diamonds, hearts, and spades), with each suit containing 13 cards 
//  // (ace, two through ten, jack, queen, and king) for a total of 52 cards in all. 
//  //int cards = 52, suit = 13;
//  //int cardsThatAreJackorHeart = Counting::Combinations(cards, 4) + Counting::Combinations(cards, 4);
//
//  // The CEO of a company has a table in his office which can seat 4 employees. 
//  // How many seating arrangements are possible if 4 out the 12 employees sit at the table? 
//int seatingArrangements = Counting::Factorial(12) / Counting::Factorial(8);
//Trace("Press any key to exit...");
//
//// A company received a shipment of 33 laser printers, including 5 that are defective. 
//// 3 of these printers are selected to be used in the copy room. 
//// (a) How many selections can be made?
////int selectionsMade = Counting::Combinations(33, 3);
////// (b) How many of these selections will contain no defective printers? 
////int selectionsWithoutDefectivePrinters = Counting::Combinations(28, 3);
//
//// You are a participant in a peace conference with 10 participants. Everybody shakes everybody else's hand. 
//// There are handshakes altogether. 
//int participants = 10, handshakes = 0;
//for (int i = 1; i < participants; ++i)
//  handshakes += i;
//
//// A school dance committee is to consist of 2 freshmen, 3 sophomores, 4 juniors, and 5 seniors. 
//// If 6 freshmen, 7 sophomores, 8 juniors, and 9 seniors are eligible to be on the committee, in how many ways can the committee be chosen? 
//int fr = 6, so = 7, jr = 8, sr = 9;
//int students = fr + so + jr + sr;
//int committeeVariations = Counting::Combinations(fr, 2) * Counting::Combinations(so, 3)
//* Counting::Combinations(jr, 4) * Counting::Combinations(sr, 5);
//