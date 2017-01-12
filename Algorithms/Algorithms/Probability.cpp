#include "Probability.h"

namespace Algorithms {

  char FindMostFrequentLetter(const std::string & message, bool print) 
  {
    char mostFrequent = 'a';

    std::vector<int> frequencies;
    frequencies.reserve(26);

    for (int i = 0; i < 26; ++i) {
      frequencies.push_back(0);
    }

    for (char c : message) {
      ++frequencies.at(c - 'A');
    }

    if (print) {
      for (int i = 0; i < frequencies.size(); ++i) {
        Trace(static_cast<char>('A' + i) << ": " << frequencies[i] / static_cast<float>(message.size()));
      }
    }

    int highestFrequency = 0;
    for (unsigned i = 0; i < frequencies.size(); ++i) {
      if (frequencies.at(i) > highestFrequency) {
        highestFrequency = frequencies.at(i);
        mostFrequent = i + 'A';
      }
    }

    return mostFrequent;
  }

  std::string SmartShiftCipher(const std::string & message, char key) {
    std::string decodedMessage;

    int shiftValue = std::abs(key - 'E');

    for (unsigned i = 0; i < message.size(); ++i) {
      char c = message.at(i);
      decodedMessage += (((c + shiftValue) - 'A') % 26) + 'A';
    }

    return decodedMessage;
  }
}