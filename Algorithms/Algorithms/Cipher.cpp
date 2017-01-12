#include "Cipher.h"

namespace Algorithms {

  // The number of possible shift values for the english alphabet
  unsigned Cipher::PossibleShiftValues = 26;

  std::string Cipher::Shift(const std::string& message, int key) {

    std::string decodedMessage;
    key = key % PossibleShiftValues;
    static int uppercaseOffset = 65;
    static int lowerCaseOffset = 97;
    for (auto& c : message) {
      if (isupper(c))
        decodedMessage += static_cast<char>(static_cast<int>(c + key - uppercaseOffset) % PossibleShiftValues + uppercaseOffset);
      else
        decodedMessage += static_cast<char>(static_cast<int>(c + key - lowerCaseOffset) % PossibleShiftValues + lowerCaseOffset);
    }
    return decodedMessage;
  }


}

