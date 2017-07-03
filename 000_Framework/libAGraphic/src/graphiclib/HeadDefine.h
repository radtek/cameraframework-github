#ifndef _HEAD_DEFINE_H__
#define _HEAD_DEFINE_H__

#include "..\..\..\..\001_Project\libappcore\TraceMacros.h"
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
#define CFG_PATH  "/usr/share/pdcusr.cfg"

typedef struct _planesData{
	char* tex; 
	float* pBorderData;//two for vertex and two for TEXCOORD,so stride is 4
	float* pArrayData;//two for vertex and two for TEXCOORD,so stride is 4
	unsigned short* pBorderIndex;
	unsigned short pBorderIndexNum;
	unsigned short pBorderPtElemNum;
}planesData;

typedef struct _linesData{
    //char* tex;
    float* pLineData;
    float* pArrayData;
    unsigned short startIndex;
    unsigned short* pLineIndex;
    unsigned short pLineIndexNum;
    unsigned short pLinePtElemNum;
}linesData;


typedef struct _groupMap{
	int planeNum;//total plane number
	int beginHead;//begin line
	int showPlaneNum;// how many plans need to show
	int planeSeq[10];// which one or multiple
} groupMap;




#endif