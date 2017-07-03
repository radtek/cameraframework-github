#include <math.h>

#ifndef __ROSAL_H__
#define __ROSAL_H__
#define CMV_MAX_BUF 1024

#define R_EPSILON 0.000001f
#define R_PI      3.1415926f
#define R_Deg2Rad(angle) ((float)( angle * R_PI / 180.0f ))
#define R_Rad2Deg(angle) ((float)( angle * 180.0f / R_PI ))

#define R_MAX(x1, x2)     (x1)>(x2)?(x1):(x2)
#define R_MIN(x1, x2)     (x1)<(x2)?(x1):(x2)

typedef unsigned char   u8_t;
typedef char            s8_t;
typedef unsigned short  u16_t;
typedef short           s16_t;
typedef unsigned long   u32_t;
typedef long            s32_t;
typedef float           f32_t;
typedef double          f64_t;

//typedef struct frame
//{
//   u32_t w;
//   u32_t h;
//   u32_t stride;
//   u8_t  *data;
//}frame_t;

typedef struct pos{
	f32_t x;
	f32_t y;
} Position2D;



#endif //__OSAL_H__
