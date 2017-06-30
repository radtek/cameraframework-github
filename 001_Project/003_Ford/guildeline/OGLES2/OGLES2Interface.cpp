/*
 * OGLES2Interface.cpp
 *
 *  Created on: 2012-4-27
 *      Author: QiLiu
 */

#include <stdio.h>
#include <errno.h>


#include "OGLES2Interface.h"

#include "..\..\..\..\002_UserStory\002_Ford\pdc\graphiclib\GraphicVPAFord.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480
GraphicVPAFord* s_GraphicVPAFord=NULL; 
int OGLES2Init(void* eglDisplay)
{
	//GlGMRVS::getInstance()->Init(640,480);
	s_GraphicVPAFord = new GraphicVPAFord();
	s_GraphicVPAFord->vInit(SCREEN_WIDTH, SCREEN_HEIGHT);
	s_GraphicVPAFord->init();//thread not start,but call init
    s_GraphicVPAFord->bSetVDTState(5,1,1000,1000);
    s_GraphicVPAFord->bSetVDTLeftBottom(SCREEN_WIDTH>>1,SCREEN_HEIGHT>>1);
    s_GraphicVPAFord->bSetVDTSize(SCREEN_WIDTH,SCREEN_HEIGHT,1);
    s_GraphicVPAFord->bSetVDTEnable();
	return 0;
}

void vGuideline_ForwardPositive(int shortR, int LongR)
{
	s_GraphicVPAFord->bSetVDTState(GraphicVDT::eForward,GraphicVDT::ePositive,shortR,LongR);
}
void vGuideline_ForwardNagetive(int shortR, int LongR)
{
	s_GraphicVPAFord->bSetVDTState(GraphicVDT::eForward,GraphicVDT::eNegative,shortR,LongR);
}
void vGuideline_BackwardPositive(int shortR, int LongR)
{
	s_GraphicVPAFord->bSetVDTState(GraphicVDT::eRearward,GraphicVDT::ePositive,shortR,LongR);
}
void vGuideline_BackwardNagetive(int shortR, int LongR)
{
	s_GraphicVPAFord->bSetVDTState(GraphicVDT::eRearward,GraphicVDT::eNegative,shortR,LongR);
}

#define DIFFLEN 90

void OGLES2Draw()
{
	static unsigned int testshortR =50;
	static unsigned int testLongR = testshortR+DIFFLEN;
	testshortR +=1;
	testLongR = testshortR+DIFFLEN;
	vGuideline_BackwardNagetive(testshortR%256,testLongR%256);
	/*if(testshortR<=1000)
	{
		vGuideline_ForwardNagetive(testshortR%1000,testLongR%1000);
	}

	else if(testshortR<=2000)
	{
		vGuideline_ForwardNagetive(testshortR%1000,testLongR%1000);
	}
	else if(testshortR<=3000)
	{
		vGuideline_BackwardPositive(testshortR%1000,testLongR%1000);
	}
	else if(testshortR<=4000)
	{
		vGuideline_BackwardNagetive(testshortR%1000,testLongR%1000);
	}
	else
	{
		testshortR =0;
	}
*/
    s_GraphicVPAFord->Render();
	Sleep(50);
}

void OGLES2TouchEvent(int x, int y,int eventType)
{
	;
}

