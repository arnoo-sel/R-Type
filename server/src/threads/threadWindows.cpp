#include "threads/threadWindows.hpp"

ThreadWindows::ThreadWindows(threadFuncPtr ptr, void *arg) : hThread(0)
{
    hThread = CreateThread(NULL, 0, reinterpret_cast<winThreadFuncPtr>(ptr), arg, 0, &id);
    if (hThread == NULL)
        throw new ThreadException("Can't create thread");
}

ThreadWindows::~ThreadWindows()
{
    //if (TerminateThread(hThread, 1) == 0)
    //    throw new ThreadException("Can't kill thread");
    CloseHandle(hThread);
}

int            ThreadWindows::join()
{
    DWORD      res;

    if (WaitForSingleObject(hThread, -1) == 0xFFFFFFFF)
        throw new ThreadException("Can't wait for thread");
    if (GetExitCodeThread(hThread, &res) == 0)
        throw new ThreadException("Can't get exit code for thread");
    return (res);
}

MutexWindows::MutexWindows() : locked(false)
{
    InitializeCriticalSection(& _critSection);
}

MutexWindows::~MutexWindows()
{
    DeleteCriticalSection(& _critSection);
}

void MutexWindows::lock()
{
    EnterCriticalSection(& _critSection);
    locked = true;
}

void MutexWindows::release()
{
    LeaveCriticalSection(& _critSection);
    locked = false;
}

bool MutexWindows::state()
{
    return locked;
}

Lock::Lock(IMutex& mutex) : _mutex(mutex)
{
    _mutex.lock();
}

Lock::Lock(IMutex* mutex) : _mutex(*mutex)
{
    _mutex.lock();
}

Lock::~Lock()
{
    _mutex.release();
}
