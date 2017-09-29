#ifndef ITHREAD
# define ITHREAD

#include "threads/threadException.hpp"

class IThread
{
public:
  typedef int     (*threadFuncPtr)(void*);

  virtual ~IThread() {};
  virtual int     join() = 0;
};

class IMutex
{
  friend class ILock;
public:
  virtual ~IMutex() {};

  virtual void lock() = 0;
  virtual void release() = 0;
  virtual bool state() = 0;
};

class Lock
{
public:
  Lock(IMutex& mutex);
  Lock(IMutex* mutex);
  ~Lock();
  
private:
  IMutex&  _mutex;
};

#ifdef WIN32
  #include "threads/threadWindows.hpp"
#else
  #include "threads/threadUnix.hpp"
#endif

#endif //ITHREAD
