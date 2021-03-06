#pragma once

namespace Algorithms {

  static unsigned PossibleShiftValues = 26;

  char FindMostFrequentLetter(const std::string& message, bool print = false);
  std::string SmartShiftCipher(const std::string& message, char key);

}