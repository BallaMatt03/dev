//#define WIN32
//#define LINUX


#ifdef WIN32
double dtime();
__int64 readTSC (void);
#endif

#ifdef LINUX
long long readTSC (void);
#endif
