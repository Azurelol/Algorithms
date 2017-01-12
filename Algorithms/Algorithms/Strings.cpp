#include "Strings.h"

namespace Algorithms {

  //------------------------------------------------------------------------/
  // Unique
  //------------------------------------------------------------------------/
  // Determines if a string has all unique characters
  // Time complexity O(n), Space complexity O(1)
  bool String::Unique(const std::string & string)
  {
    auto strLen = string.length();

    // If the string is greater than the number of unique characters in the alphabet, return false
    if (strLen > 256)
      return false;

    // We can use an array of bools or a map of <char,bool> to check. For this implementation,
    // I will be using an array of bools      
    bool characterSet[256] = { false };
    for (int i = 0; i < strLen; ++i) {
      int character = string[i];

      // If the character was already found at this location
      if (characterSet[character]) {
        //Trace("Character = " + std::to_string(character));
        return false;
      }
      // Set the index to found
      characterSet[character] = true;
    }

    // No duplicates were found
    return true;
  }

  //------------------------------------------------------------------------/
  // Reverse
  //------------------------------------------------------------------------/
  void String::Reverse(char * string, ReverseAlgorithm algorithm) {

    // If the string is null, do nothing
    if (!string)
      return;

    // Find the length of the string
    auto stringLength = strlen(string);

    if (algorithm == ReverseAlgorithm::Manual) {

      // We will walk from the beginning to the middle of the string
      for (int i = 0; i < stringLength / 2; i++) {
        auto character = string[i];
        string[i] = string[stringLength - i - 1];
        string[stringLength - i - 1] = character;
      }
    }
    else if (algorithm == ReverseAlgorithm::Swap) {
      // Modern with std::swap
      for (auto i = 0; i < stringLength / 2; i++)
        std::swap(string[i], string[stringLength - i - 1]);
    }
    else if (algorithm == ReverseAlgorithm::Reverse) {
      // Even better with reverse
      std::reverse(string, string + stringLength);
    }

  }

  //------------------------------------------------------------------------/
  // Permutation
  //------------------------------------------------------------------------/
  bool String::Permutation(const std::string & left, const std::string & right, bool caseSensitive, 
                                   PermutationAlgorithm algorithm) {
    // Validate input
    if (left.size() != right.size())
      return false;

    // If two strings are anagrams we know they have the same characters,
    // but in different orders. Sorting the strings will put the characters from
    // both anagrams into the same order. Then we can compare the sorted version.
    if (algorithm == PermutationAlgorithm::Sorting)
    {
      bool isEqual = Sort(left, caseSensitive) == Sort(right, caseSensitive);
      return isEqual;
    }
    else if (algorithm == PermutationAlgorithm::CharCount)
    {
      int leftCount = 0, rightCount = 0;

      for (int i = 0; i < left.size(); i++) {
        leftCount += left[i];
        rightCount += right[i];
      }

      bool isEqual = leftCount == rightCount;
      return isEqual;
    }

    return false;

  }

  //------------------------------------------------------------------------/
  // Palindrome
  //------------------------------------------------------------------------/
  bool String::Palindrome(const std::string & string, PalindromeAlgorithm algorithm) {

    // Compare the left side with the right side
    if (algorithm == PalindromeAlgorithm::CompareHalves) {
      auto strLen = string.length();
      for (int i = 0; i < string.length(); i++) {
        if (string[i] != string[strLen - i - 1])
          return false;
        // All elements were equal
        return true;
      }
    }
    // Compare the first half of the string with the latter half in reverse
    else if (algorithm == PalindromeAlgorithm::CompareHalvesEqual) {
      return std::equal(string.begin(), string.begin() + string.size() / 2, string.begin());
    }
    if (algorithm == PalindromeAlgorithm::Reverse) {
      std::string reverse(string.rbegin(), string.rend());
      return reverse == string;
    }

    return false;
  }

  //------------------------------------------------------------------------/
  // Print Duplicates
  //------------------------------------------------------------------------/
  void String::PrintDuplicates(const std::string & string, PrintDuplicatesAlgorithm algorithm)
  {
    if (!string.size())
      return;

    if (algorithm == PrintDuplicatesAlgorithm::Map) {
      std::map<char, int> Duplicates;

      // Count all the duplicates
      for (auto& c : string) {
        // If it already inserted, increment the count
        if (Duplicates.count(c)) {
          Duplicates[c]++;
          continue;
        }
        Duplicates.insert(std::pair<char, int>(c, 1));
      }
      // Now print them all
      Trace("Duplicates found in '" + string + "' :");
      for (auto& c : Duplicates) {
        std::cout << c.first << ": " << c.second << "\n";
      }

    }
    else if (algorithm == PrintDuplicatesAlgorithm::CharArray) {

    }

  }

  //------------------------------------------------------------------------/
  // Occurrences of a character in a string
  //------------------------------------------------------------------------/
  int String::Occurrences(const std::string & string, char character, OccurrencesAlgorithm algorithm) {

    if (!string.size())
      return 0;

    if (algorithm == OccurrencesAlgorithm::STDCount) {
      
      return static_cast<int>(std::count(string.begin(), string.end(), character));
    }

    throw new std::exception("No string given!");

  }

  //------------------------------------------------------------------------/
  // Substring
  //------------------------------------------------------------------------/
  bool String::Substring(const std::string & string, const std::string & substring, SubstringAlgorithm algorithm)
  {
    if (string.empty() || substring.empty())
      return false;

    if (algorithm == SubstringAlgorithm::Iterative) {
      int j = 0;
      for (int i = 0; i < string.length() && j < substring.length(); i++) {
        if (string[j] == substring[i])
          j++;
      }
    }
    else if (algorithm == SubstringAlgorithm::STDFind) {
      return (string.find(substring) != std::string::npos);
    }

    return false;
  }

  // Sorts a string, returning a copy. 
  std::string String::Sort(const std::string& string, bool caseSensitive) {
    auto copy = string;
    if (!caseSensitive)
      std::transform(copy.begin(), copy.end(), copy.begin(), ::toupper);
    std::sort(copy.begin(), copy.end());
    return copy;
  }







}