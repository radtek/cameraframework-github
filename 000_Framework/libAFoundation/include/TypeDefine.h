
#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_TYPEDEF_H__
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_TYPEDEF_H__

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using std::string;
using std::map;
using std::queue;
using std::vector;
//#define Array      std::vector
//#define makePair   std::make_pair

// namespace Harman {
// namespace Adas {
// namespace AFramework {
// namespace AFoundation {

#define STRING_NULL     string("")

#define ASSERT(x) assert(x);
//#define ASSERT(x) ;

#ifdef TRUE
#undef	TRUE
#endif

#ifdef FALSE
#undef	FALSE
#endif

#define TRUE	true
#define FALSE	false
#define makePair     std::make_pair

typedef unsigned int            UInt32;
typedef unsigned long           UInt64;
typedef bool                    BOOLEAN;
typedef int                     Int32;
typedef unsigned short          USHORT;
typedef float                   Float32;
typedef unsigned char           BYTE;
typedef char                    CHAR;
typedef void                    VOID;

typedef Int32 ECode;

typedef enum a_status
{
    OK,  // everything is well
    NO_INIT, //init failed
    BAD_VALUE,  //param bad or return type bad
    ALREADY_EXISTS, //obj already is exists
    TIME_OUT,
    WOULD_BLOCK ,

    AVAILABEL,
    INAVAILABEL,

    UNKNOWN_ERROR       = 0x80000000
} Enum_Astatus;

typedef struct
{
    Int32 x;
    Int32 y;
}posXY;

typedef struct
{
    Int32       width;
    Int32       height;
    posXY      viewPos;
    Int32       layer;
}viewInfo;

typedef enum gpio_value
{
    REVERSE_GEAR_HAS_GONE = 0,
    REVERSE_GEAR_COME_ON = 1,

    REVERSE_GEAR_UNKNOWN_ACTION = 2
} Enum_Reserve_GPIO_Value;

typedef enum gpio_num
{
    REVERSE_GEAR_GPIO_NUM = 465
} Enum_GPIO_Num;

// } // namespace AFoundation
// } // namespace AFramework
// } // namespace Adas
// } // namespace Harman

#endif // __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_TYPEDEF_H__