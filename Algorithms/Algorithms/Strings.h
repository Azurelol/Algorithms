/******************************************************************************/
/*!
@file      Strings.h
@author    Christian Sagel
@par       email: ckpsm\@live.com
@date      9/29/2016
@brief     Common string manipulation algorithms
*/
/******************************************************************************/
#pragma once
#include <string>
#include <algorithm>
#include <cctype>
#include <map>

// Tracing


namespace Algorithms
{

  class String
  {

  public:

    // Determines if a string has all unique characters
    static bool Unique(const std::string& string);

    enum class ReverseAlgorithm { Manual, Swap, Reverse };
    // Reverses a C-style null-terminated string
    static void Reverse(char* string, ReverseAlgorithm algorithm = ReverseAlgorithm::Manual);

    enum class PermutationAlgorithm { Sorting, CharCount };
    // Checks if a string is a permutation of another
    static bool Permutation(const std::string& left, const std::string& right, bool caseSensitive = false,
      PermutationAlgorithm algorithm = PermutationAlgorithm::CharCount);

    enum class PalindromeAlgorithm { CompareHalves, CompareHalvesEqual, Reverse };
    // Checks if a string is a palindrome
    static bool Palindrome(const std::string& string, PalindromeAlgorithm algorithm = PalindromeAlgorithm::CompareHalvesEqual);

    enum class PrintDuplicatesAlgorithm { CharArray, Map };
    // Prints the occurrence of duplicates in a string
    static void PrintDuplicates(const std::string& string, PrintDuplicatesAlgorithm algorithm = PrintDuplicatesAlgorithm::Map);

    enum class OccurrencesAlgorithm { STDCount };
    // Finds the occurrence of the specified character in a string
    static int Occurrences(const std::string& string, char character, OccurrencesAlgorithm algorithm = OccurrencesAlgorithm::STDCount);

    enum class SubstringAlgorithm { Iterative, Recursive, STDFind };
    static bool Substring(const std::string& string, const std::string& substring, SubstringAlgorithm algorithm = SubstringAlgorithm::STDFind);

  private:
    static std::string Sort(const std::string& string, bool caseSensitive = true);







  };
}