#include "AzureUtilities.h"

namespace Utilities
{
  char Alphabetize(int i)
  {
    return static_cast<char>('A' + i);
  }

  void PrintResult(bool result, std::string success, std::string failure)
  {
    if (result)
      Trace(success);
    else
      Trace(failure);
  }

  void PrintSortingResult(const std::vector<int>& unsorted, const std::vector<int>& sorted, std::string message)
  {
    Trace("Sorting algorithm = " + message);
    std::cout << "Unsorted: ";
    Print(unsorted);
    std::cout << "Sorted: ";
    Print(sorted);
  }

  void PrintIsA(bool result, std::string subject, std::string identity)
  {
    std::string print;
    if (result)
      Trace(subject + " is " + identity);
    else
      Trace(subject + " is not " + identity);
  }


}