#ifdef WIN32

#include <math.h>
#include <windows.h>
#include <winnt.h>
#include <winbase.h>

double dtime()
{
  double q;
  static double f;
  static int    first_time = 1;
  static LARGE_INTEGER ticks_count;
  static LARGE_INTEGER liFrequency;

  if(first_time) {
    QueryPerformanceFrequency(&liFrequency);
    f = (double)liFrequency.HighPart * 4294967296.0 +
        (double)liFrequency.LowPart;
    f = 1.0 / f;
    first_time=0;
  }

  QueryPerformanceCounter(&ticks_count);
  q = (double)ticks_count.HighPart * 4294967296.0 +
      (double)ticks_count.LowPart;

  return(q*f);
}
/* --------------- */
__int64 readTSC (void)
/* --------------- */
{
  _int64 t;
  unsigned int a,b;
  unsigned int *c = (unsigned int *)&t;
  _asm {
    _emit 0x0f;
    _emit 0x31;
    mov a,eax;
    mov b,edx;
  }
  c[0]=a;c[1]=b;
  return t;
}
#endif // WIN32

#ifdef LINUX
long long readTSC (void)
{
  long long t;
  asm volatile (".byte 0x0f,0x31" : "=A" (t));

  return t;      
}
double dtime()
{
  return (double) readTSC();
}
#endif
