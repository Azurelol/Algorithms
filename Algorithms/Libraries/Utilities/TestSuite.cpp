#include "TestSuite.h"

namespace Tests
{
  TestSuite::TestSuite() 
  {
  }

  inline int TestSuite::ReadNumberFromConsole(std::string prompt, int min, int max)
  {
    std::string line;
    int num;

    while ((std::cout << prompt) && std::getline(std::cin, line))
    {
      std::istringstream is{ line };
      if ((is >> num) && !(is >> line) && (num >= min) && (num <= max))
      {
        break;
      }
      std::cerr << "Invalid input, try again." << std::endl;
    }

    return num;
  }


  // Adds a test category
  void TestSuite::Add(std::string name, Test::Group group)
  {
    Categories.push_back(Test::Category(name, group));
  }

  void TestSuite::Display()
  {
    // If there's no categories, throw!
    if (Categories.empty())
      throw ("No categories available!");

    bool active = true;
    while (active)
    {
      Trace("------------------------------");
      // Pick a category
      auto category = PickCategory();
      
      // Pick a test
      auto test = PickTest(category);
      // Now call the test function
      Newline(1);
      test.Invoke();
      Newline(1);

    }
  }

  TestSuite::Test::Category TestSuite::PickCategory()
  {    
    // If there's only one category, just return it
    if (Categories.size() == 1)
      return Categories[0];

    Trace("- Select a category:");
    Newline(1);
    // Display all categories
    auto numCategories = ToInt(Categories.size());
    for (auto i = 0; i < numCategories; ++i)
    {
      auto& category = Categories[i];
      Trace(i + 1 << ". " << category.Name);
    }
    // Pick
    Newline(1);
    auto option = ReadNumberFromConsole("> Input the category number and press enter: ", 1, numCategories);
    Newline(1);
    return Categories[option - 1];
  }

  TestSuite::Test TestSuite::PickTest(const TestSuite::Test::Category& category)
  {    
    Trace("- Select a test:");
    Newline(1);
    auto& tests = category.Tests;
    auto numTests = ToInt(tests.size());

    for (auto i = 0; i < numTests; ++i)
    {
      auto& test = tests[i];
      Trace(i + 1 << ". " << test.Description);
    }
    // Pick
    Newline(1);
    auto option = ReadNumberFromConsole("> Input the test number and press enter: ", 1, numTests);
    return tests[option - 1];
  }

}