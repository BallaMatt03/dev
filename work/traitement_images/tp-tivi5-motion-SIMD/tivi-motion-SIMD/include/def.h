/* ------------- */
/* --- def.h --- */
/* ------------- */

/*
 */

#ifndef __DEF_H__
#define __DEF_H__

typedef unsigned char BOOL;
#define TRUE 1
#define FALSE 0

typedef unsigned char byte;

typedef unsigned char uint8;
typedef   signed char sint8;

typedef unsigned short uint16;
typedef   signed short sint16;

typedef unsigned int uint32;
typedef   signed int sint32;

typedef float         float32;
typedef double        float64;
typedef struct { byte r; byte g; byte b;} rgb8;

#endif // __DEF_H__