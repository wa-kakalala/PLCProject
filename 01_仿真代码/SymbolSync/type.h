#ifndef _TYPE_H_
#define _TYPE_H_

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef float          float32;
typedef double         float64;

#define POINT_TYPE     u16
#define WIN_LEN        1024
#define abs(x)         ( x < 0 ? -x : x )
#define FRAME_THRESH   0.6


u8 frame_sync(POINT_TYPE point);
u8 symbol_sync(POINT_TYPE point);

#endif 
