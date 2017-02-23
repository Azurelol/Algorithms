#include "Concurrency.h"

namespace Algorithms
{
  namespace Concurrency
  {
    //----------------------------------------------------------------------------/
    // Semaphore
    //----------------------------------------------------------------------------/

    Semaphore::Semaphore() : Count(1)
    {
    }


    Semaphore::Semaphore(int numThreads) : Count(numThreads)
    {
      //Trace("Created semaphore with '" << numThreads << "' maximum threads!");
    }


    void Semaphore::Initialize(int numThreads)
    {
      this->Count = numThreads;
    }


    void Semaphore::Wait()
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


    void Semaphore::Signal()
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