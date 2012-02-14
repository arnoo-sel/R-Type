#include "math/time.hpp"

#ifdef WIN32
#include <windows.h>

LARGE_INTEGER GetFrequency()
{
  LARGE_INTEGER freq;
  QueryPerformanceFrequency(&freq);
  return freq;
}

Seconds  now()
{


  LARGE_INTEGER tick, freq;
  Seconds res;

  freq = GetFrequency();
  QueryPerformanceCounter(&tick);
  res = (Seconds)tick.QuadPart / (Seconds)freq.QuadPart;
  return res;
}

void    sleep(int len)
{
    Sleep(len);
}

#else
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

Seconds  now()
{
  struct timeval        tv;
  Seconds                res;

  gettimeofday(&tv, NULL);
  res = tv.tv_sec + tv.tv_usec / 1000000.;
  return (res);
}

void    sleep(int len)
{
    usleep(len * 1000);
}

#endif
