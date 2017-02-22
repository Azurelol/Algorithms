#pragma once

namespace ADT
{
  struct HashFunction
  {
    using ReturnType = unsigned;
    using Ptr = std::unique_ptr<HashFunction>;

    ReturnType operator()(const char* key, unsigned tableSize) { return GetHash(key, tableSize); }
    ReturnType operator()(const std::string& key, unsigned tableSize) { return GetHash(key.c_str(), tableSize); }
    ReturnType GetHash(const std::string& key, unsigned tableSize) { return GetHash(key.c_str(), tableSize); }
        
    // The hash function to be implemented
    virtual ReturnType GetHash(const char* key, unsigned TableSize) = 0;
  };

  struct SimpleHash : HashFunction
  {
    // Inherited via HashFunction
    virtual ReturnType GetHash(const char * key, unsigned tableSize) override
    {
      // Initial value of the hash
      ReturnType hash = 0;
      // Process each character in the string
      while (*key)
      {
        // Add in the current character
        hash += static_cast<unsigned>(*key);
        // Iterate
        key++;
      }

      // Modulo so the hash is within the table
      return hash % tableSize;
    }
  };

  struct RSHash : HashFunction
  {
    // Inherited via HashFunction
    virtual ReturnType GetHash(const char * key, unsigned tableSize) override
    {
      // Initial value of the hash
      ReturnType hash = 0;
      // Prevents anomalies (?)
      unsigned multiplier = 127;
      // Process each character in the string
      while (*key)
      {
        // Adjust the hash total
        hash = hash * multiplier;
        // Add in the current character and mod the result
        hash = (hash + static_cast<ReturnType>(*key)) & tableSize;
        // Iterate
        key++;
      }

      // The hash will be within 0 to table size
      return hash;
    }

  };





}