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
      /// <summary>
      /// Default constructor. Sets the default value to 1 (Acting as a mutex).
      /// </summary>
      Semaphore();
      /// <summary>
      /// Semaphore constructor, which sets the maximum amount of threads.
      /// </summary>
      /// <param name="numThreads"></param>
      Semaphore(int numThreads);
      /// <summary>
      /// Initializes the semaphore with a given value.
      /// </summary>
      /// <param name="initialValue"></param>
      void Initialize(int numThreads);
      /// <summary>
      /// Decrements the value of this semaphore by one. 
      /// If the value is zero, then this will block the thread until
      /// the value becoems greater than zero.
      /// </summary>
      void Wait();
      /// <summary>
      /// Increments the value of the semaphore by one.
      /// </summary>
      void Signal();
      private:
      int Count;
      std::mutex Mutex;
      std::condition_variable ConditionalVariable;

    };

    class Lightswitch
    {
      public:
      Lightswitch()
      void Enter();
      void Leave();

      private:
      int Count;
      Semaphore M;
    };


  }

}

#define AtomicTrace(message) AtomicWriter() << message << "\n"
