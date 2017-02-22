#pragma once

#include "HashTable\HashFunction.h"

namespace ADT
{
  template <typename T>
  class HashTable
  {
  public:

    //using FreeProcedure = 

    struct Config
    {
      unsigned InitialTableSize;
      HashFunction::Ptr HashFunction;
      double MaxLoadFactor;
      double GrowthFactor;

    };

  };
}