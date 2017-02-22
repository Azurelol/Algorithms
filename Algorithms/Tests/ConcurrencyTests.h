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

    auto t1 = std::thread([&]()
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

    auto n = 5;
    std::vector<std::thread> threads(n);
    Trace("Threads = '" << n << "'");

    for (auto i = 0; i < n; ++i)
    {
      threads[i] = std::thread([&]()
      {
        auto id = i;

        AtomicTrace("#" << id << " is waiting!");
        mutex.wait();
        count = count + 1;
        mutex.signal();
        AtomicTrace("#" << id << " has signaled!");

        if (count == n)
        {
          //AtomicTrace("#" << id << " has matched the count. It has signaled!");
          barrier.signal();
        }
        else
        {
          //AtomicTrace("count(" << count << ") != n(" << n << ")");
        }

        AtomicTrace("#" << id << " is waiting!");

        // Turnstile: Rapid sequence of wait-signal that lets all thread to
        // continue after nth thread arrives.
        barrier.wait();
        barrier.signal();

        AtomicTrace("#" << id << " has entered critical section!");

      });
    }

    for (auto i = 0; i < n; ++i)
      threads[i].join();
  }
  
  /// <summary>
  /// In many applications the thread will be running a while-loop
  /// with a barrier inside. We need to implement logic that locks barrier
  /// for the next iteration.
  /// </summary>
  void ReusableBarrier()
  {
    enum class Solution { Attempt1, Attempt2, CorrectSolution };

    auto count = 0;
    auto& mutex = Semaphore(1);
    auto& turnstile1 = Semaphore(0);
    auto& turnstile2 = Semaphore(1);

    auto n = 5;
    std::vector<std::thread> threads(n);
    auto k = 3;
    Trace("Threads = '" << n << "', Iterations = '" << k << "'");

    auto algorithm = Solution::Attempt2;

    for (auto i = 0; i < n; ++i)
    {
      threads[i] = std::thread([&]()
      {
        auto id = i;
        auto iterations = k;
        while (iterations > 0)
        {
          AtomicTrace("#" << id << " is starting an iteration!");

          // ATTEMPT 1
          if (algorithm == Solution::Attempt1)
          {
            mutex.wait();
            count = count + 1;
            mutex.signal();

            if (count == n) turnstile1.signal();

            // First turnstile          
            turnstile1.wait();
            turnstile1.signal();
            AtomicTrace("#" << id << " has entered critical section!");

            mutex.wait();
            count = count - 1;
            mutex.signal();

            if (count == 0) turnstile1.wait();
          }
          // ATTEMPT 2
          else if (algorithm == Solution::Attempt2)
          {
            mutex.wait();
            count = count + 1;
            if (count == n) turnstile1.signal();
            mutex.signal();

            turnstile1.wait();
            turnstile1.signal();
            AtomicTrace("#" << id << " has entered critical section!");

            mutex.wait();
            count = count - 1;
            if (count == 0) turnstile1.wait();
            mutex.signal();
          }
          // SOLUTION
          else if (algorithm == Solution::CorrectSolution)
          {
            // Rendezvous
            mutex.wait();
            count = count + 1;
            if (count == n)
            {
              turnstile2.wait();
              turnstile1.signal();
            }
            mutex.signal();

            // First turnstile          
            turnstile1.wait();          
            turnstile1.signal();

            AtomicTrace("#" << id << " has entered critical section!");

            mutex.wait();
            count = count - 1;
            if (count == 0)
            {              
              turnstile1.wait();
              turnstile2.signal();
            }
            mutex.signal();
            
            // Second turnstile
            turnstile2.wait();
            turnstile2.signal();
          }

          iterations--;
          AtomicTrace("#" << id << " has crossed the barrier. Iterations left = " << iterations);
        }
      });
    }

    for (auto i = 0; i < n; ++i)
      threads[i].join();

  }

  void ReadersWriters()
  {

  }

  void DiningPhilosophers()
  {

  }

  void CigaretteSmokers()
  {

  }

  void DiningSavages()
  {

  }




  // Define all available tests
  TestSuite::Test::Group ConcurrencyTests =
  {
    TestSuite::Test("Signaling", Signaling),
    TestSuite::Test("Rendezvous", Rendezvous),
    TestSuite::Test("Multiplex", Multiplex),
    TestSuite::Test("Barrier", Barrier),
    TestSuite::Test("ReusableBarrier", ReusableBarrier),
    TestSuite::Test("ReadersWriters", ReadersWriters),
    TestSuite::Test("DiningPhilosophers", DiningPhilosophers),
    TestSuite::Test("CigaretteSmokers", CigaretteSmokers),
    TestSuite::Test("DiningSavages", DiningSavages)

  };

}