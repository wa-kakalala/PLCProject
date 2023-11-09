#ifndef _TYPE_H_
#define _TYPE_H_

#include <stdio.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            int32;
typedef float          float32;
typedef double         float64;


typedef   int32        POINT_TYPE;
#define WIN_LEN        1024
#define abs(x)         ( x < 0 ? -x : x )


u8 frame_sync(POINT_TYPE point_new,POINT_TYPE point_old);
u8 symbol_sync(POINT_TYPE point);

#endif 
