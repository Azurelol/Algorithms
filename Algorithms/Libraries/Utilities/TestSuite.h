#pragma once

namespace Tests
{
  class TestSuite
  {
  public:

    struct Test
    {
      using Function = std::function<void()>;
      using Group = std::vector<Test>;

      std::string Description;
      Function Function_;
      Test(std::string desc, Function func) : Description(desc), Function_(func) {}
      void Invoke() { Function_(); }

      struct Category
      {
        std::string Name;
        Group Tests;

        Category(std::string name, Group& tests) : Name(name), Tests(tests) {}
        Category& operator=(Group& tests) { Tests = tests; }
        void Add(std::string name, Function test) { Tests.push_back(Test(name, test)); }
      };

      //struct TestingUnit
      //{
      //  using MemberFunction = std::function<void(TestingUnit&)>;
      //
      //  TestingUnit(TestSuite::Test::Group& group)
      //  {
      //    MemberFunction fn = &Run;
      //    //group.push_back(this);
      //  }
      //  virtual std::string Name() = 0;
      //  virtual void Run() = 0;
      //};

    };

    using TestCategory = std::map<int, Test>;
    using TestAddress = std::pair<int, Test>;
    using CategoryAddress = std::pair<std::string, Test::Category>;

    // Methods
    TestSuite();
    //void Add(std::string name, Test::Function test);
    void Add(std::string name, Test::Group category);
    void Display();

  private:
    //TestCategory Tests;
    //int NumberOfTests;
    Test::Category PickCategory();
    Test PickTest(const TestSuite::Test::Category& category);
    std::vector<Test::Category> Categories;
    int ReadNumberFromConsole(std::string prompt, int min = INT_MIN, int max = INT_MAX);

  };
}