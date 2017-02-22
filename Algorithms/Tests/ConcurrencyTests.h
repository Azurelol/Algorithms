#pragma once

#include "..\Algorithms\Concurrency.h"
using namespace Algorithms::Concurrency;

namespace Tests
{

  /// <summary>
  /// One thread sends a signal to another thread to indicate that something has happened
  /// In other words require that a1 happens before b2
  /// </summary>
  void Signaling()
  {
    Trace("Requires that 'a1' happens before 'b2'");

    Semaphore sem(1);

    auto t1 = std::thread( [&]()
    {
      AtomicTrace("a1");
      sem.signal();
      AtomicTrace("a2");
    }
    );

    auto t2 = std::thread([&]()
    {
      AtomicTrace("b1");
      sem.wait();
      AtomicTrace("b2");
    }
    );

    t1.join();
    t2.join();
  }

  /// <summary>
  /// Same as signaling, but symmetric
  /// </summary>
  void Rendezvous()
  {
    Trace("Requires that: ");
    Trace("- 'a1' happens before 'b2'");
    Trace("- 'b1' happens before 'a2'");

    Semaphore semA(0);
    Semaphore semB(0);

    auto t1 = std::thread([&]()
    {
      AtomicTrace("a1");
      semA.signal();
      semB.wait();
      AtomicTrace("a2");
    }
    );

    auto t2 = std::thread([&]()
    {
      AtomicTrace("b1");
      semB.signal();
      semA.wait();
      AtomicTrace("b2");
    }
    );

    t1.join();
    t2.join();
  }

  /// <summary>
  /// Allow multiple (up to a fix number N) of threads to execute a critical section
  /// at the same time. Possibly the most common pattern involving semaphores.
  /// </summary>
  void Multiplex()
  {
    // Number of threads
    auto n = 14; 
    // Number of threads allowed inside CS
    auto c = 5;

    Trace("Threads = '" << n << "', # allowed inside critical section = '" << c << "'");

    std::vector<std::thread> threads(n);   
    auto& sem = Semaphore(c);

    for (auto i = 0; i < n; ++i)
    {
      threads[i] = std::thread([&]()
      {
        auto id = i;
        sem.wait();
        AtomicTrace("Executing #" << id);
        sem.signal();
      });
    }

    for (auto i = 0; i < n; ++i)
    {
      threads[i].join();
    }

  }

  /// <summary>
  /// Rendezvous for more than 2 threads. The synchronization requirement is that no thread executes
  /// critical point until after all threads have executed rendezvous
  /// </summary>
  void Barrier()  
  {
    auto count = 0;
    auto& mutex = Semaphore(1);
    auto& barrier = Semaphore(0);

    auto n = 2;
    std::vector<std::thread> threads(n);

    for (auto i = 0; i < n; ++i)
    {
      threads[i] = std::thread([&]()
      {
        auto id = i;
        //AtomicTrace(id << " is waiting!");

        mutex.wait();
        count = count + 1;
        mutex.signal();

        if (count == n)
          barrier.signal();

        barrier.wait();
        AtomicTrace("#" << id << " has entered critical section!");

      });
    }

    for (auto i = 0; i < n; ++i)
      threads[i].join();

  }



  // Define all available tests
  TestSuite::Test::Group ConcurrencyTests =
  {
    TestSuite::Test("Signaling", Signaling),
    TestSuite::Test("Rendezvous", Rendezvous),
    TestSuite::Test("Multiplex", Multiplex),
    TestSuite::Test("Barrier", Barrier)
  };

}