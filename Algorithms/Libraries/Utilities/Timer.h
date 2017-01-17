/******************************************************************************/
/*!
@file   Timer.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   2/21/2016
@copyright Copyright 2016, DigiPen Institute of Technology. All rights reserved.
*/
/******************************************************************************/
#pragma once
/* More references;
http://www.informit.com/articles/article.aspx?p=1881386&seqNum=2 */

// Libraries
#include <string>
#include <chrono>
#include <vector>
#include <iostream>
#include <map> // map
#include <algorithm> // find_if
#include <functional>

namespace Time
{


  //----------------------------------------------------------------------------/
  // A framework that relates a time point to real physical time
  using clock = std::chrono::high_resolution_clock;
  // A reference to a specific point in time, like one's birthday, etc
  //  high_resolution_clock is the clock with the shortest tick period
  using timePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
  using ms = std::chrono::milliseconds;
  using us = std::chrono::microseconds;
  //----------------------------------------------------------------------------/
  struct FunctionProfile
  {
    std::string Name;
    float Time;
    unsigned Calls;
    FunctionProfile(std::string name, float time) : Name(name), Time(time), Calls(1) {}
    void Print()
    {
      std::cout << "Function Name: '" << Name
        << "', Time: '" << Time
        << "', Calls: '" << Calls << "'\n";
    }
  };
  using FunctionProfileContainer = std::vector<FunctionProfile>;
  //----------------------------------------------------------------------------/
  struct FunctionProfileTimes
  {
    FunctionProfileContainer Previous;
    FunctionProfileContainer Current;

    // Adds a time, making sure its aggregated
    void Add(FunctionProfile profile)
    {
      // Attempt to look for a matching time slice in the container
      auto matchingTime = std::find_if(Current.begin(), Current.end(),
        [=](Time::FunctionProfile& t)
      {
        return t.Name == profile.Name;
      });
      // If it's there, add this time to it
      if (matchingTime != Current.end())
      {
        matchingTime->Time += profile.Time;
        matchingTime->Calls++;
      }
      // Else, add it to the container
      else
      {
        Current.push_back(profile);
      }
    }

    void Update()
    {
      Previous = Current;
      Current.clear();
    }

    FunctionProfileContainer& Time()
    {
      if (Previous.empty())
        return Current;
      return Previous;
    }

  };
  using FunctionProfilePair = std::pair<std::string, FunctionProfileTimes>;
  using FunctionProfileMap = std::map<std::string, FunctionProfileTimes>;
  //----------------------------------------------------------------------------/

  class Timer
  {
  public:
    enum class Mode
    {
      StopWatch,
      Countdown,
    };

    Timer(float duration, Mode mode, bool reset);
    bool Update();
    bool Update(float dt);
    float CurrentTime;

  private:
    float Duration;
    bool Reset;
    Mode CurrentMode;
  };

  // Durations measure time spans, like one minute, two hours, ten ms
  using floatSeconds = std::chrono::duration<float>;

  class ScopeTimer
  {

  private:
    Time::timePoint StartTime;
    Time::timePoint EndTime;
    float* ReturnValue;
    bool IsReturning;

  public:

    ScopeTimer(float* output) : StartTime(Time::clock::now()), ReturnValue(output), IsReturning(true) {}
    ScopeTimer() : StartTime(Time::clock::now()), IsReturning(false) {}

    // When the timer leaves the scope, gets the end time. It then
    // converts the duration to a float where 1.0f == 1 second.
    // It then stores the result in a pointer given at initialization.
    ~ScopeTimer()
    {
      // If a float reference was passed in, this timer will set it now
      if (IsReturning)
        *ReturnValue = Elapsed();
    }

    // Returns the time elapsed since this timer was created
    float Elapsed()
    {
      auto currentTime = Time::clock::now();
      Time::floatSeconds duration = currentTime - StartTime;
      return duration.count();
    }

  };


  /**************************************************************************/
  /*!
  @class FunctionTimer Times a function, invoking a report method on the
  destructor.
  */
  /**************************************************************************/
  class FunctionTimer
  {
  public:
    FunctionTimer() : StartTime(Time::clock::now()) {}
    void Record();
    virtual void Report() = 0;
    float ElapsedTime;

  private:
    Time::timePoint StartTime;
    Time::timePoint EndTime;
  };

}
