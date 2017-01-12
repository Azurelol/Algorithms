#pragma once
#include <string>

namespace Algorithms {

  class Cipher {
  public:

    static unsigned PossibleShiftValues;

    static std::string Shift(const std::string& message, int key);

  };


}
