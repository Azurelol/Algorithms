#pragma once

#include "..\Algorithms\Concurrency.h"
using namespace Algorithms::Concurrency;

namespace Tests
{
  ///// <summary>
  ///// Calls this function among the specified number of threads
  ///// </summary>
  ///// <param name="threads"></param>
  ///// <param name="func"></param>
  //template <typename ... Arguments>
  //void RunThreaded(int n, std::function<void(Arguments)> func)
  //{
  //  std::vector<std::thread> threads(n);
  //  for (auto i = 0; i < n; ++i)
  //  {
  //    threads[i] = std::thread([&]()
  //    {
  //      func(i);
  //    });
  //  }
  //}

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
      sem.Signal();
      AtomicTrace("a2");
    }
    );

    auto t2 = std::thread([&]()
    {
      AtomicTrace("b1");
      sem.Wait();
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
      semA.Signal();
      semB.Wait();
      AtomicTrace("a2");
    }
    );

    auto t2 = std::thread([&]()
    {
      AtomicTrace("b1");
      semB.Signal();
      semA.Wait();
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
        sem.Wait();
        AtomicTrace("Executing #" << id);
        sem.Signal();
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

        Trace("#" << id << " is waiting!");
        mutex.Wait();
        count = count + 1;
        mutex.Signal();
        Trace("#" << id << " has signaled!");

        if (count == n)
        {
          //AtomicTrace("#" << id << " has matched the count. It has signaled!");
          barrier.Signal();
        }
        else
        {
          //AtomicTrace("count(" << count << ") != n(" << n << ")");
        }

        Trace("#" << id << " is waiting!");

        // Turnstile: Rapid sequence of wait-signal that lets all thread to
        // continue after nth thread arrives.
        barrier.Wait();
        barrier.Signal();

        Trace("#" << id << " has entered critical section!");

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
    enum class Solution { Attempt1, Attempt2, Correct };
    auto algorithm = Solution::Correct;

    auto count = 0;
    auto& mutex = Semaphore(1);
    auto& turnstile1 = Semaphore(0);
    auto& turnstile2 = Semaphore(1);

    auto n = 3;
    std::vector<std::thread> threads(n);
    auto k = 2;
    Trace("Threads = '" << n << "', Iterations = '" << k << "'");



    for (auto i = 0; i < n; ++i)
    {
      threads[i] = std::thread([&]()
      {
        auto id = i;
        auto iterations = k;
        while (iterations > 0)
        {
          Trace("(#" << id << ": START)");

          // ATTEMPT 1
          if (algorithm == Solution::Attempt1)
          {
            mutex.Wait();
            count = count + 1;
            mutex.Signal();

            if (count == n) turnstile1.Signal();

            // First turnstile          
            turnstile1.Wait();
            turnstile1.Signal();
            Trace("(#" << id << ": CS)");

            mutex.Wait();
            count = count - 1;
            mutex.Signal();

            if (count == 0) turnstile1.Wait();
          }
          // ATTEMPT 2
          else if (algorithm == Solution::Attempt2)
          {
            mutex.Wait();
            count = count + 1;
            if (count == n) turnstile1.Signal();
            mutex.Signal();

            turnstile1.Wait();
            turnstile1.Signal();
            Trace("(#" << id << ": CS)");

            mutex.Wait();
            count = count - 1;
            if (count == 0) turnstile1.Wait();
            mutex.Signal();
          }
          // SOLUTION
          else if (algorithm == Solution::Correct)
          {
            // Rendezvous
            mutex.Wait();
            count = count + 1;
            if (count == n)
            {
              turnstile2.Wait();
              turnstile1.Signal();
            }
            mutex.Signal();

            // First turnstile          
            turnstile1.Wait();          
            turnstile1.Signal();

            Trace("(#" << id << ": CS)");

            mutex.Wait();
            count = count - 1;
            if (count == 0)
            {              
              turnstile1.Wait();
              turnstile2.Signal();
            }
            mutex.Signal();
            
            // Second turnstile
            turnstile2.Wait();
            turnstile2.Signal();
          }

          iterations--;
          Trace("(#" << id << ": END)");
        }
      });
    }

    for (auto i = 0; i < n; ++i)
      threads[i].join();

  }

  void ReadersWriters()
  {

  }

  /// <summary>
  /// n philosophers sit at a round table with a bowl of food in the middle. There are n chopsticks,
  /// so that there is exactly 1 chopstick between each of the neighboring philosophers. To be able to eat,
  /// a philosopher needs both chopsticks that are on his left and right. While a philosopher is eating, the
  /// two neighboring philosophers cannot eat.
  /// Problem: Synchronization algorithm that produces no starvation.
  /// </summary>
  void DiningPhilosophers()
  {
    enum class Solution { Attempt1, NthIsRightHanded, Tanenbaum };
    auto solution = Solution::NthIsRightHanded;
    enum class State { Thinking, Hungry, Eating };

    auto n = 3;
    std::vector<Semaphore> forkMutex(n);
    std::vector<std::thread> threads(n);

    for (auto t = 0; t < n; ++t)
    {
      threads[t] = std::thread([&]()
      {
        auto tid = t;

        // Problem: All n philosophers grab left fork and wait for the right.
        // Observation: Deadlock occurs when all n philosophers grab the left fork first
        if (solution == Solution::Attempt1)
        {
          // Get left fork
          forkMutex[tid].Wait();
          Trace(tid << " has grabbed left fork!");
          // Get right fork
          forkMutex[(tid + 1) % n].Wait();
          Trace(tid << " has grabbed right fork!");

          Trace(tid << " is now eating!");

          // Release right fork
          forkMutex[(tid + 1) % n].Signal();
          Trace(tid << " has released right fork!");
          // Release left fork
          forkMutex[tid].Signal();
          Trace(tid << " has released left fork!");
        }
        else if (solution == Solution::NthIsRightHanded)
        {
          // The nth philosopher is right handed
          if (tid == n - 1)
          {
            // Get right fork
            forkMutex[(tid + 1) % n].Wait();
            // Get left fork
            forkMutex[tid].Wait();
            Trace(tid << " has grabbed left fork!");
            Trace(tid << " has grabbed right fork!");

            Trace(tid << " is now eating!");

            // Release left fork
            forkMutex[tid].Signal();
            Trace(tid << " has released left fork!");
            // Release right fork
            forkMutex[(tid + 1) % n].Signal();
            Trace(tid << " has released right fork!");
          }
          // All other philosophers use code from the previous example
          else
          {
            // Get left fork
            forkMutex[tid].Wait();
            Trace(tid << " has grabbed left fork!");
            // Get right fork
            forkMutex[(tid + 1) % n].Wait();
            Trace(tid << " has grabbed right fork!");

            Trace(tid << " is now eating!");

            // Release right fork
            forkMutex[(tid + 1) % n].Signal();
            Trace(tid << " has released right fork!");
            // Release left fork
            forkMutex[tid].Signal();
            Trace(tid << " has released left fork!");
          }
        }
        else if (solution == Solution::Tanenbaum)
        {

        }

      });
    }

    for (auto i = 0; i < n; ++i)
      threads[i].join();

  }

  void CigaretteSmokers()
  {

  }

  /// <summary>
  /// There are n savages with 1 pot of food and 1 cook. Savages are doing whatever savages do,
  /// but when hungry they stop by the pot and eat. When the pot becomes empty they notify cook
  /// who can replenish the food (and go back to sleep).
  /// Savage will generate an error if attempting to eat from an empty pot, cook will generate
  /// an error if trying to add food to a pot that is not empty.
  /// </summary>
  void DiningSavages()
  {
    auto servings = 2;
    auto servingsLeft = 0;
    auto savages = 3;    

    auto timesSavagesWillEat = 6;
    auto savagesLeftEating = savages;

    auto& mutex = Semaphore();
    auto& emptyPot = Semaphore(0);
    auto& fullPot = Semaphore(0);

    Trace("Savages = " << savages << ", Servings on pot = " << servings);

    // Cook thread
    std::thread cookThread([&]()
    {
      while (savagesLeftEating > 0)
      {
        emptyPot.Wait();
        Trace("Cook is now putting " << servings << " servings into pot!");
        servingsLeft = servings;
        fullPot.Signal();
      }
      Trace("Cook is done serving!");
    });

    // Savage threads
    std::vector<std::thread> threads(savages);
    for (auto t = 0; t < savages; ++t)
    {
      threads[t] = std::thread([&]()
      {
        auto tid = t;

        for (auto i = 0; i < timesSavagesWillEat; ++i)
        {
          mutex.Wait();
          // Wait on servings
          if (servingsLeft == 0)
          {
            emptyPot.Signal();
            Trace(tid << " is waiting on serving from pot!");
            fullPot.Wait();     
          }
          // Eat
          servingsLeft -= 1;
          Trace(tid << " is getting serving from pot. Servings = " << servingsLeft);
          mutex.Signal();
          //Trace(tid << " is eating!");
        }

        savagesLeftEating--;
        if (savagesLeftEating == 0)
          emptyPot.Signal();
        Trace(tid << " is finished eating!");


      });
    }



    // Clean up
    for (auto i = 0; i < threads.size(); ++i)
      threads[i].join();
    cookThread.join();

  }

  /// <summary>
  /// Performn random swaps of elements of the array using multiple threads.
  /// </summary>
  void ParallelShuffle()
  {
    enum class Solution { Attempt1, Attempt2, Attempt3, Correct };
    auto algorithm = Solution::Correct;

    std::vector<int> a{ 1, 2, 3, 4, 5, 6, 7 };
    auto shuffles = 100;

    // Number of threads
    auto n = 3;
    std::vector<std::thread> threads(n);

    // Attempt 2
    std::vector<Semaphore> sems(n);
    for (auto& s : sems)
      s.Initialize(1);

    // Correct
    auto& sem = Semaphore(n);
    auto& mutex = std::mutex();

    Trace("Pre-shuffle array:");
    PrintArray(a);

    for (auto t = 0; t < n; ++t)
    {
      threads[t] = std::thread([&]()
      {        
        auto id = t;

        // Data Race: Depending on T1 or T2 first, the result will be different
        if (algorithm == Solution::Attempt1)
        {
          for (auto k = 0; k < shuffles; ++k)
          {
            int i = rand() % n;
            int j = rand() % n;

            auto temp = a[i];
            a[i] = a[j];
            a[j] = temp;
          }
        }
        // Deadlock: Similar to smokers. 
        else if (algorithm == Solution::Attempt2)
        {
          for (auto k = 0; k < shuffles; ++k)
          {            
            int i = rand() % n;
            int j = rand() % n;
            
            sems[i].Wait();
            sems[j].Wait();

            auto temp = a[i];
            a[i] = a[j];
            a[j] = temp;

            sems[j].Signal();
            sems[i].Signal();
          }
        }
        // Progress: Correct, but inefficient. Onoly one thread can work at a time.
        else if (algorithm == Solution::Attempt3)
        {
          for (auto k = 0; k < shuffles; ++k)
          {
            int i = rand() % n;
            int j = rand() % n;

            sem.Wait();
            
            auto temp = a[i];
            a[i] = a[j];
            a[j] = temp;

            sem.Signal();
          }
        }
        else if (algorithm == Solution::Correct)
        {
          for (auto k = 0; k < shuffles; ++k)
          {
            // Enforce ordering to prevent deadlocks
            int i = rand() % n;
            int j = rand() % (n - 1);
            if (j == i) j++;
            if (i > j) std::swap(i, j);

            //Trace(t << " is waiting.");
            mutex.lock();
            sems[i].Wait();
            sems[j].Wait();
            mutex.unlock();
            //Trace(t << " has signaled.");

            std::swap(a[i], a[j]);

            //auto temp = a[i];
            //a[i] = a[j];
            //a[j] = temp;
            
            sems[j].Signal();
            sems[i].Signal();
          }
        }


      });
    }

    for (auto i = 0; i < n; ++i)
      threads[i].join();

    Trace("Post-shuffle array:");
    PrintArray(a);

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
    TestSuite::Test("DiningSavages", DiningSavages),
    TestSuite::Test("ParallelShuffle", ParallelShuffle)

  };

}