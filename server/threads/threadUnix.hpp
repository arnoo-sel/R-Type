#ifndef THREADUNIX
# define THREADUNIX

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "threads/iThread.hpp"

class ThreadUnix : public IThread
{
public:
  typedef void*		(*unixThreadFuncPtr)(void*);

  ThreadUnix(threadFuncPtr, void *arg = NULL);
  virtual ~ThreadUnix();
  int             join();
  
private:
  pthread_t	hThread;
  bool		opened;
};

class MutexUnix : public IMutex
{
public:
  MutexUnix();
  virtual ~MutexUnix();
  void lock();
  void release();
  bool state();
  
private:
  pthread_mutex_t	_mutex;
  bool			locked;
};

typedef ThreadUnix	AbstractThread;
typedef MutexUnix	AbstractMutex;

#endif //THREADUNIX
