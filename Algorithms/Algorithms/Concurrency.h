#pragma once

namespace Algorithms
{
  namespace Concurrency
  {
    class AtomicWriter
    {
      std::ostringstream st;
      std::ostream &stream;
      public:
      AtomicWriter(std::ostream &s = std::cout) :stream(s) {}
      template <typename T>
      AtomicWriter& operator<<(T const& t)
      {
        st << t;
        return *this;
      }
      AtomicWriter& operator<<(std::ostream&(*f)(std::ostream&))
      {
        st << f;
        return *this;
      }
      ~AtomicWriter() { stream << st.str(); }
    };

    // Calculates the program speed up 
    float Amdahls(float p, float s);

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
      public:
      Semaphore(int numThreads);
      void wait();
      void signal();
      private:
      int Count;
      std::mutex Mutex;
      std::condition_variable ConditionalVariable;

    };


  }

}

#define AtomicTrace(message) AtomicWriter() << message << "\n"
