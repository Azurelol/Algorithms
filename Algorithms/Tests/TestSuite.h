#pragma once

namespace Tests
{
  class TestSuite
  {

  private:
    //------------------------------------------------------------------------/
    // Declarations
    //------------------------------------------------------------------------/
    using TestFunction = std::function<void()>;
    struct Test
    {
      std::string Description;
      TestFunction Function;
      Test(std::string desc, TestFunction func)
        : Description(desc), Function(func)
      {
      }

    };

    //------------------------------------------------------------------------/
    // Methods
    //------------------------------------------------------------------------/
    int ReadNumberFromConsole(std::string prompt, int min = INT_MIN, int max = INT_MAX)
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

    using TestAddress = std::pair<int, Test>;
    std::map<int, Test> Tests;
    int NumberOfTests;

  public:

    TestSuite() : NumberOfTests(1)
    {
    }

    void Add(std::string name, TestFunction test)
    {
      Tests.insert(TestAddress(NumberOfTests++, Test(name, test)));
    }

    void Display()
    {
      bool active = true;
      while (active)
      {
        // Print all tests
        Trace("------------------------------");
        Trace("Select an test:");
        Trace("------------------------------");
        for (auto& test : Tests)
        {
          Trace(test.first << "." << test.second.Description);
        }
        Newline(1);

        // Accept an option
        int option;
        option = ReadNumberFromConsole("Input the test number and press enter: ", 1, NumberOfTests);

        // Now call the test function
        Newline(1);
        Trace("{");
        auto& func = Tests.at(option).Function;
        func();
        Trace("}");
        Newline(1);

      }
    }


  };
}