#include "threads/threadUnix.hpp"

ThreadUnix::ThreadUnix(threadFuncPtr ptr, void *arg) : hThread(0)
{
  if (pthread_create(&hThread, NULL, reinterpret_cast<unixThreadFuncPtr>(ptr), arg))
    throw new ThreadException("Can't create thread");
}

ThreadUnix::~ThreadUnix()
{
//  pthread_kill(hThread, SIGTERM);
}

int		ThreadUnix::join()
{
    int		res;

    if (pthread_join(hThread, reinterpret_cast<void**>(&res)))
        throw new ThreadException("Can't wait for thread");
    return (res);
}

MutexUnix::MutexUnix() : locked(false)
{
  pthread_mutex_init(&_mutex, NULL);
}

MutexUnix::~MutexUnix()
{
  pthread_mutex_destroy(&_mutex);
}

void MutexUnix::lock()
{
  pthread_mutex_lock(&_mutex);
  locked = true;
}

void MutexUnix::release()
{
  pthread_mutex_unlock(&_mutex);
  locked = false;
}

bool MutexUnix::state()
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
