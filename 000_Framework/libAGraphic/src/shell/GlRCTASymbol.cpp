/*
 * GlRCTASymbol1.cpp
 *
 *  Created on: 2012-5-10
 *      Author: QiLiu
 */

#include "GlRCTASymbol.h"

#define NORMALIZE(x) x*2.0-1.0

GlRCTASymbol::GlRCTASymbol()
{
	m_fColor[0] = 1.0;
	m_fColor[1] = 0.0;
	m_fColor[2] = 0.0;
	m_fSize = 0.0f;
	m_screenWidth = 0;
	m_screenHeight = 0;
}

GlRCTASymbol::~GlRCTASymbol()
{
	;
}

void GlRCTASymbol::Init(float size,float leftPosX,float leftPosY,float rightPosX,float rightPosY,const char** texFileName,int flashRate,int screenWidth,int screenHeight)
{
//	m_AlphaTriangle.Init(texFileName[0]);
//	m_AlphaHand.Init(texFileName[1]);
//	printf("GlRCTASymbol init!\n");
	m_LeftIcon.Init(texFileName[0],screenWidth,screenHeight);
	m_RightIcon.Init(texFileName[1],screenWidth,screenHeight);

	m_fSize = size;
	m_fLeftPosX = leftPosX*2.0-1.0;
	m_fLeftPosY = leftPosY*2.0-1.0;
	m_fRightPosX = rightPosX*2.0-1.0;
	m_fRightPosY = rightPosY*2.0-1.0;

	m_FrqCntl.SetParam(flashRate,0);
}

int GlRCTASymbol::Init(rvs_rcta_params& rctaPos,const char** texFileName,int flashRate,int screenWidth,int screenHeight)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
//	printf("GlRCTASymbol init!\n");
	if(m_LeftIcon.Init(texFileName[0],screenWidth,screenHeight))
		return -1;
	if(m_RightIcon.Init(texFileName[1],screenWidth,screenHeight))
		return -1;

	screenPos* pos;
	pos = (screenPos*)&rctaPos.pixel[0];
	m_fRightPosX = pos->u*2.0-1.0;
	m_fRightPosY = pos->v*2.0-1.0;
	pos++;
	m_fLeftPosX = pos->u*2.0-1.0;
	m_fLeftPosY = pos->v*2.0-1.0;

	m_FrqCntl.SetParam(flashRate,0);
	return 0;
}

int GlRCTASymbol::Init(float size,rvs_rcta_params& rctaPos,const char** texFileName,int flashRate,int screenWidth,int screenHeight)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_fSize = size;

//	printf("GlRCTASymbol init!\n");
	if(m_LeftIcon.Init(texFileName[0],screenWidth,screenHeight))
		return -1;
	if(m_RightIcon.Init(texFileName[1],screenWidth,screenHeight))
		return -1;

	screenPos* pos;
	pos = (screenPos*)&rctaPos.pixel[0];
	m_fRightPosX = pos->u*2.0-1.0;
	m_fRightPosY = pos->v*2.0-1.0;
	pos++;
	m_fLeftPosX = pos->u*2.0-1.0;
	m_fLeftPosY = pos->v*2.0-1.0;

	m_FrqCntl.SetParam(flashRate,0);
	return 0;
}

void GlRCTASymbol::Update(PVRTMat4& PVMat,rvs_RCTAState_t left, rvs_RCTAState_t right)
{
	int leftRender = left.RCTAIndication&0x01;
	int rightRender = right.RCTAIndication&0x01;
	rvs_RCTAIndicationCtl_t leftFlash = left.RCTAIndicationControl;
	rvs_RCTAIndicationCtl_t rightFlash = right.RCTAIndicationControl;

	if(leftRender&&!leftFlash)
		leftRender = 0;
	if(rightRender&&!rightFlash)
		rightRender = 0;

	if(leftRender)
	{
		if(leftFlash == eRVS_RCTA_CONTINUOUS_INDICATION)
			RenderSolidLeft(PVMat);
		else if(leftFlash == eRVS_RCTA_FLASHING_INDICATION)
			RenderFlashLeft(PVMat);
	}

	if(rightRender)
	{
		if(rightFlash == eRVS_RCTA_CONTINUOUS_INDICATION)
			RenderSolidRight(PVMat);
		else if(rightFlash == eRVS_RCTA_FLASHING_INDICATION)
			RenderFlashRight(PVMat);
	}

}

void GlRCTASymbol::RenderSolidLeft(PVRTMat4& PVMat)
{
//	m_LeftIcon.Render(PVMat,m_fSize,m_fLeftPosX,m_fLeftPosY,m_fColor);
	m_LeftIcon.RenderWithNoScale(PVMat,m_fLeftPosX,m_fLeftPosY,m_fColor);
}

void GlRCTASymbol::RenderSolidRight(PVRTMat4& PVMat)
{
//	m_RightIcon.Render(PVMat,m_fSize,m_fRightPosX,m_fRightPosY,m_fColor);
	m_RightIcon.RenderWithNoScale(PVMat,m_fRightPosX,m_fRightPosY,m_fColor);
}

void GlRCTASymbol::RenderFlashLeft(PVRTMat4& PVMat)
{
	if(m_FrqCntl.EvenInterval())
		RenderSolidLeft(PVMat);
}

void GlRCTASymbol::RenderFlashRight(PVRTMat4& PVMat)
{
	if(m_FrqCntl.EvenInterval())
		RenderSolidRight(PVMat);
}
