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
    bool active = true;
    while (active)
    {
      // Pick a category
      Trace("------------------------------");
      auto category = PickCategory();
      Newline(1);
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
    Trace("- Select a category:");
    // Display all categories
    auto numCategories = ToInt(Categories.size());
    for (auto i = 0; i < numCategories; ++i)
    {
      auto& category = Categories[i];
      Trace(i + 1 << ". " << category.Name);
    }
    // Pick
    auto option = ReadNumberFromConsole("> Input the category number and press enter: ", 1, numCategories);
    return Categories[option - 1];
  }

  TestSuite::Test TestSuite::PickTest(const TestSuite::Test::Category& category)
  {    
    Trace("- Select a test:");
    auto& tests = category.Tests;
    auto numTests = ToInt(tests.size());

    for (auto i = 0; i < numTests; ++i)
    {
      auto& test = tests[i];
      Trace(i + 1 << ". " << test.Description);
    }
    // Pick
    auto option = ReadNumberFromConsole("> Input the test number and press enter: ", 1, numTests);
    return tests[option - 1];
  }

}