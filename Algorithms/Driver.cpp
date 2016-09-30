/******************************************************************************/
/*!
@file      Driver.cpp
@author    Christian Sagel
@par       email: ckpsm\@live.com
@date      9/29/2016
@brief     Main driver for my Algorithms demonstration.
@note      Hours spent: 3
*/
/******************************************************************************/
// Algorithms
#include "Sort.h"
#include "Strings.h"

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

int main(void) {

  TestStrings();

  

  Trace("Press any key to exit...");
  std::cin.get();

}

