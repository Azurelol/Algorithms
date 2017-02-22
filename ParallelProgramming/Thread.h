#pragma once
#include "pthreads\pthread.h"

namespace Threading
{
  class Thread
  {
    typedef void *(*ThreadedRoutine) (void *);

    pthread_t Reference;
    int ID;
    ThreadedRoutine Routine;
    void* Argument;
    bool IsRunning;

    public:
    Thread() : ID(-1), Routine(NULL), Argument(NULL), IsRunning(false)
    {
    }

    Thread(int id, ThreadedRoutine routine, void* argument)
      : ID(id), Routine(routine), Argument(argument), IsRunning(false)
    {
    }

    ~Thread()
    {
      if (IsRunning)
        End();
      //delete Argument;
    }

    void Initialize(int id, ThreadedRoutine routine, void* argument)
    {
      ID = id;
      Routine = routine;
      Argument = argument;
    }

    void Start()
    {
      pthread_create(&Reference, NULL, Routine, Argument);
      IsRunning = true;
    }

    void End()
    {
      pthread_join(Reference, NULL);
      IsRunning = false;
    }


  };
}