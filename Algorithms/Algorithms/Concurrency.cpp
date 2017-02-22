#include "Concurrency.h"

namespace Algorithms
{
  namespace Concurrency
  {
    //----------------------------------------------------------------------------/
    // Semaphore
    //----------------------------------------------------------------------------/

    /// <summary>
    /// Semaphore constructor, which sets the maximum amount of threads.
    /// </summary>
    /// <param name="numThreads"></param>
    Semaphore::Semaphore(int numThreads) : Count(numThreads)
    {
      //Trace("Created semaphore with '" << numThreads << "' maximum threads!");
    }

    /// <summary>
    /// Decrements the value of this semaphore by one. 
    /// If the value is zero, then this will block the thread until
    /// the value becoems greater than zero.
    /// </summary>
    void Semaphore::wait()
    {
      // This RAII object will lock the mutex until we exit scope
      //Trace("About to lock mutex!");
      std::unique_lock<std::mutex> lock(this->Mutex);
      // If the count is at 0, wait
      this->ConditionalVariable.wait(lock, [this]()
      {
        return this->Count > 0;
      });
      //while (this->Count == 0) {}
      this->Count--;

      //Trace("Wait: Count at " << Count);

    }

    /// <summary>
    /// Increments the value of the semaphore by one.
    /// </summary>
    void Semaphore::signal()
    {
      std::unique_lock<std::mutex> lock(this->Mutex);
      //Trace("Trying to signal!");

      //while (this->Count == 0)
      //{
      //  this->ConditionalVariable.wait(lock);
      //}
      this->Count++;
      this->ConditionalVariable.notify_one();
      //Trace("Signal: Count at " << Count);
    }


    // Calculates the program speed up 
    float Amdahls(float p, float s)
    {
      return 1.0f / 1.0f - p + (p / s);
    }

  }

}