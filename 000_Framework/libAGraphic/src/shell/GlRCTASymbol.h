/*
 * GlRCTASymbol1.h
 *
 *  Created on: 2012-5-10
 *      Author: QiLiu
 */

#ifndef GLRCTASYMBOL_H_
#define GLRCTASYMBOL_H_

#include "GlShell.h"
#include "GlAlphaTexRect.h"
#include "RVSDefine.h"
#include "LCommon.h"


class GlRCTASymbol : public GlShellApp
{
public:
	GlRCTASymbol();
	~GlRCTASymbol();

	//size: the ratio is to the screenSize
	void Init(float size,float leftPosX,float leftPosY,float rightPosX,float rightPosY,const char** texFileName,int flashRate,int screenWidth,int screenHeight);
	int Init(rvs_rcta_params& rctaPos,const char** texFileName,int flashRate,int screenWidth,int screenHeight);
	int Init(float size,rvs_rcta_params& rctaPos,const char** texFileName,int flashRate,int screenWidth,int screenHeight);
	void Update(PVRTMat4& PVMat,rvs_RCTAState_t left, rvs_RCTAState_t right);

private:

	void RenderSolidLeft(PVRTMat4& PVMat);
	void RenderSolidRight(PVRTMat4& PVMat);
	void RenderFlashLeft(PVRTMat4& PVMat);
	void RenderFlashRight(PVRTMat4& PVMat);

private:
	FrequencyCntl m_FrqCntl;
	GlAlphaTexRect m_LeftIcon;
	GlAlphaTexRect m_RightIcon;

	float m_fSize;
	float m_fColor[3];

	float m_fLeftPosX;
	float m_fLeftPosY;
	float m_fRightPosX;
	float m_fRightPosY;
};

#endif /* GlRCTASymbol_H_ */
