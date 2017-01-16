#pragma once

#include "..\Algorithms\Cipher.h"
using namespace Algorithms;

namespace Tests
{
  void TestCipher()
  {
    std::string encodedMessage = "DOFKVFVBSPRLNHTLZ";

    Trace("1. Shift Cipher: Decoding '" + encodedMessage + "'. Possible values:");
    for (unsigned i = 0; i < Cipher::PossibleShiftValues; ++i)
    {
      Trace("Shift value = " << i << ", decoded message = " << Cipher::Shift(encodedMessage, i));
    }
  }
}