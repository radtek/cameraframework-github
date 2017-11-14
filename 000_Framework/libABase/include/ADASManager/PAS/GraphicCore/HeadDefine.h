
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_HEADDEFINE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_HEADDEFINE_H__

#include "TraceMacros.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

//2 circle
//4 debug line
#define LINE_PTN_NUM 300
#define PLANE_SEG 2
#define R_PI      3.1415926f
#define CFG_PATH  "/usr/bin/pdcusr.cfg"

typedef struct _planesData{
	char* tex;
	float* pBorderData;//two for vertex and two for TEXCOORD,so stride is 4
	float* pArrayData;//two for vertex and two for TEXCOORD,so stride is 4
	unsigned short* pBorderIndex;
	unsigned short pBorderIndexNum;
	unsigned short pBorderPtElemNum;
}planesData;

typedef struct __linesData{
    //char* tex;
    float* pLineData;
    float* pArrayData;
    unsigned short startIndex;
    unsigned short* pLineIndex;
    unsigned short pLineIndexNum;
    unsigned short pLinePtElemNum;
}paslinesData;

typedef struct _groupMap{
	int planeNum;//total plane number
	int beginHead;//begin line
	int showPlaneNum;// how many plans need to show
	int planeSeq[10];// which one or multiple
} groupMap;

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_HEADDEFINE_H__