/*
 * GlGMRVS.h
 *
 *  Created on: 2012-4-6
 */

#ifndef GLGMRVS_H_
#define GLGMRVS_H_


#include "LCommon.h"
#include "trajectory.h"

//#include "GlDynamicGdLine.h"
//#include "GlFont.h"
#include "GlParkSymbol.h"
#include "GlRCTASymbol.h"
//#include "GlImage.h"
#include "RVSDefine.h"
#include "GlGuideLine.h"
//#include "RVSPPSInit.h"

#define CAM_NEAR 1.0f
#define CAM_FAR 2000.0f

struct RVSParam_t{
	rvs_RCTAState leftRCTAState;
	rvs_RCTAState rightRCTAState;
	int ParkingSymbolZone[ePARearRegionNum];
	float SteeringAngleRad;
};

class GlGMRVS
{
public:
	static GlGMRVS* getInstance();
	~GlGMRVS();
	int Init(int screenWidth, int screenHeight, void* pDisplayContext=NULL);
	int Update();
	void OnMouseTouch(int x,int y){;}
	void OnMouseMove(int x,int y){;}
	void OnMouseRelease(int x, int y){;}

	bool IsContinue2Draw(){ return m_bContinue2Draw;}
	void setContinueDraw(int draw){ m_bContinue2Draw = draw;}

	void Update_EnableState();
	void Update_DisableState(rvs_ctx_t* ctx);

private:
	static GlGMRVS* instance;
	GlGMRVS();

protected:

	int InitParamFromPPS(rvs_ctx_t* ctx,int screenWidth,int screenHeight);

	int InitCamParamFromPPS(rvs_ctx_t* ctx,LCamera* pCam);
	int InitUPAParamFromPPS(rvs_ctx_t* ctx,int screenWidth,int screenHeight);
	int InitRCTAParamFromPPS(rvs_ctx_t* ctx);
	int InitGuideLineParamFromPPS(rvs_ctx_t* ctx,int screenWidth,int screenHeight,LCamera* pCam);
//	int InitFontParamFromPPS(rvs_ctx_t* ctx,int screenWidth,int screenHeight);

	int m_ParkingSymbolZone[ePARearRegionNum];
	LCamera m_LCamera;
	GlParkSymbol m_ParkSymbol;
	GlRCTASymbol m_RCTASymbol;
	GlGuideLine m_GuideLine;

	PVRTMat4 m_mView;
	PVRTMat4 m_mProj;
	PVRTMat4 m_mPVMat;

	int m_iScreenWidth;
	int m_iScreenHeight;

	bool m_bContinue2Draw;

	void*  pEglDisplay;
};

#endif /* GLGMRVS_H_ */
