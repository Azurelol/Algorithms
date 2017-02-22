#pragma once
#include "Semaphore.h"

namespace Threading
{
  /// <summary>
  /// A synchronization algorithm that ensures no threads executes a critical point
  /// until all threads have executed rendezvous.
  /// </summary>
  class Barrier
  {
    int Threads;
    int Count;
    Semaphore Mutex;
    Semaphore Turnstile;
    Semaphore Turnstile2;

    public:
    bool Verbose;
    Barrier() : Count(0), Mutex(1), Turnstile(0), Turnstile2(0), Verbose(false)
    {
    }

    Barrier(int threads) : Threads(threads), Count(0), Mutex(1), Turnstile(0), Turnstile2(0), Verbose(false)
    {
    }

    void Initialize(int threads)
    {
      Threads = threads;
    }

    void Phase1()
    {
      Mutex.Wait();
      Count++;
      if (Count == Threads)
        Turnstile.Signal(Threads);
      Mutex.Signal();
      Turnstile.Wait();
    }

    void Phase2()
    {
      Mutex.Wait();
      Count--;
      if (Count == 0)
        Turnstile2.Signal(Threads);
      Mutex.Signal();
      Turnstile2.Wait();
    }

    void Wait()
    {
      //if (Verbose)
      //  Log("Barrier locked!");
      Phase1();
      Phase2();
      //if (Verbose)
      //  Log("Barrier unlocked!");
    }
  };
}
