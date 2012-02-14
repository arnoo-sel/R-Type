#ifndef THREADWINDOWS
# define THREADWINDOWS

#include <windows.h>
#include <iostream>
#include "threads/iThread.hpp"

class ThreadWindows : public IThread
{
public:
  typedef DWORD WINAPI    (*winThreadFuncPtr)(LPVOID);
  
  ThreadWindows(threadFuncPtr, void *arg = NULL);
  ~ThreadWindows();
  int             join();
  
private:
    HANDLE          hThread;
    DWORD           id;
};

class MutexWindows : public IMutex
{
public:
    MutexWindows ();
    ~MutexWindows ();
    void lock();
    void release();
    bool state();

private:
    CRITICAL_SECTION _critSection;
    bool            locked;
};

typedef ThreadWindows	AbstractThread;
typedef MutexWindows	AbstractMutex;

#endif //THREADWINDOWS
