#pragma once

#include "..\Algorithms\Strings.h"
using namespace Algorithms;

namespace Tests
{
  void Unique()
  {
    // 1. Determines if a string has all unique characters
    std::string uniqueString = "research";
    bool isUnique = Algorithms::String::Unique(uniqueString);
    PrintIsA(isUnique, uniqueString, "unique!");
  }

  void Reverse()
  {
    // 2. Reverses a nul-terminated string
    char reversedString[] = "Bienvenido!";
    Trace("Reversing '" + std::string(reversedString) + "'");
    Algorithms::String::Reverse(reversedString);
    Trace("It is now '" + std::string(reversedString) + "'");
  }

  void Anagram()
  {
    // 3. Given two strings, decide if one is a permutation of the other
    // By default set to not be case-sensitive
    std::string anagramLeft = "Dog";
    std::string anagramRight = "God";
    bool isAnagram = Algorithms::String::Permutation(anagramLeft, anagramRight);
    PrintResult(isAnagram, anagramLeft + " is an anagram of " + anagramRight,
      anagramLeft + " is not an anagram of " + anagramRight);
  }

  void Palindrome()
  {
    // 4. Check if a string is a palindrome
    std::string palindromeString = "lol";
    bool isPalindrome = Algorithms::String::Palindrome(palindromeString);
    PrintIsA(isPalindrome, palindromeString, "a palindrome!");
  }

  void Duplicate()
  {
    // 5. Print the duplicate characters in the string, with count
    std::string duplicatePrint = "HeyHeyHey";
    Algorithms::String::PrintDuplicates(duplicatePrint);
  }

  void Occurrences()
  {
    // 6. Print the occurrences of a character in a string
    std::string str = "research";
    char character = 'e';
    std::cout << "The character '" << character << "' is found " <<
      std::to_string(Algorithms::String::Occurrences(str, character))
      << " times in the string " << str << "\n";
  }

  void Substring()
  {
    // 7. Find if a string is a substring of another
    std::string parent = "Megaboss", child = "boss";
    PrintIsA(Algorithms::String::Substring(parent, child), child, " a substring of '" + parent + "'");
  }

}