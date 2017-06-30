#ifndef _TYPEDEF_H
#define _TYPEDEF_H

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <utility>

//#ifdef PLATFORM_QNX
//#include <screen/screen.h>
#include <Poco/HashMap.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#endif

using std::string;
using std::map;
using std::queue;
using std::vector;
#define Array		 std::vector
#define makePair	 std::make_pair

using Poco::HashMap;

//typedef XrDataStruct::Hashmap		Hashmap;
//typedef XrDataStruct::CArray		Array;
#define STRING_NULL		string("")


typedef unsigned int			UInt32;
typedef bool				BOOLEAN;
typedef int				Int32;
typedef unsigned short			USHORT;
typedef float				Float32;
typedef	unsigned	char		BYTE;

#endif
