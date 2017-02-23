#pragma once
//#include "pthreads\pthread.h"
#include "pthreads\semaphore.h"

namespace Threading
{
  /// <summary>
  /// Allows processes and threads to synchronize their actions. A semaphore is
  /// an integer whose value is never allowed to fall below zero. Two operations
  /// can be performed on them. Increment the semaphore value by one (Post) 
  /// and decrement the semaphore value by one (Wait). 
  /// If the value of the semaphore is currently zero, then 'Wait' will block
  /// until the value becomes greater than zero.
  /// </summary>
  class Semaphore
  {
    sem_t Reference;

    public:
    /// <summary>
    /// Default constructor. Does not initialize the semaphore.
    /// </summary>
    Semaphore()
    {

    }

    /// <summary>
    /// Constructs the semaphore
    /// </summary>
    /// <param name="initialValue"></param>
    Semaphore(int initialValue)
    {
      this->Initialize(initialValue);
    }

    /// <summary>
    /// Initializes the semaphore
    /// </summary>
    /// <param name="initialValue"></param>
    void Initialize(int initialValue)
    {
      sem_init(&Reference, 0, initialValue);
    }

    /// <summary>
    /// Decrements the value of the semaphore by one. If it the value is zero,
    /// then this will block the thread until the value becomes greater than zero.
    /// </summary>
    void Wait()
    {
      sem_wait(&Reference);
    }
    /// <summary>
    /// Increments the value by the semaphore by one.
    /// </summary>
    void Signal()
    {
      sem_post(&Reference);
    }

    /// <summary>
    /// Increments the value by a specified amount of times
    /// </summary>
    /// <param name="times"></param>
    void Signal(int times)
    {
      for (int i = 0; i < times; ++i)
        Signal();
    }
  };
}