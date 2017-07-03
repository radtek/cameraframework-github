/*
 * GlParkSymbol.h
 *
 *  Created on: 2012-4-10
 *      Author: QiLiu
 */

#ifndef GLPARKSYMBOL_H_
#define GLPARKSYMBOL_H_

//#include "GlShell.h"
#include "GlAlphaTexRect.h"
#include "Rosal.h"
//#include "RVSDef.h"
#include "RVSDefine.h"
#include "LCommon.h"

#define PARK_SYMBOL_REGION 3
#define PARK_SYMBOL_ZONE 4

enum EParkSymbolPos{
	RVS_PARKSYMBOL_POS1,
	RVS_PARKSYMBOL_POS2,
	RVS_PARKSYMBOL_POS3,
	RVS_PARKSYMBOL_POS4,
	RVS_PARKSYMBOL_POS5,
	RVS_PARKSYMBOL_POS6,
	RVS_PARKSYMBOL_POS7,
	RVS_PARKSYMBOL_POS8,
	RVS_PARKSYMBOL_POS9,
	RVS_PARKSYMBOL_POS10,
	RVS_PARKSYMBOL_POS11,
	RVS_PARKSYMBOL_POS12,
	eParkSymbolPosNum
};

enum PARearRegion
{
	RVS_PA_REAR_REGION_1,
	RVS_PA_REAR_REGION_2,
	RVS_PA_REAR_REGION_3,
	ePARearRegionNum
};

enum PARearZone
{
	RVS_PA_REAR_ZONE0,
	RVS_PA_REAR_ZONE1,
	RVS_PA_REAR_ZONE2,
	RVS_PA_REAR_ZONE3,
	RVS_PA_REAR_ZONE4,
	ePARearZoneNum
};

enum PASymbolColor
{
	RVS_PA_SYMBOL_RED,
	RVS_PA_SYMBOL_ORANGE,
	ePASymbolColorNum
};

//struct ParkSymbolInfo{
//	EParkSymbolPos epos;
//	float size;
//	float posX;
//	float posY;
//	PASymbolColor color;
//};

struct ScreenPosition{
	float posX;
	float posY;
};

class GlParkSymbol : public GlShellApp
{
public:
	GlParkSymbol();
	~GlParkSymbol();

	void Init(const char* fileName,float* symbolPos,float* symbolSize,PASymbolColor* symbolColor,
			int flashRate,int flashDuration,int screenWidth,int screenHeight,int UPAType = 0);

	int Init(const char* fileName,rvs_parkAssist_params upaParam,float* symbolSize,
			PASymbolColor* symbolColor,int flashRate,int flashDuration,
			int screenWidth,int screenHeight/*,int UPAType = 0*/);

	void Render(PVRTMat4& pvMat,int* pPAInfo);

private:
	void Render(PVRTMat4& pvMat,int index);
	int GetCurRenderIndex(const int* pPAInfo);
	void InitRenderInfo(const float* symbolPos,const float* symbolSize,const PASymbolColor* symbolColor);
	void InitRenderInfo(const rvs_parkAssist_params& upaPos,const float* symbolSize,const PASymbolColor* symbolColor);

	void PreprocessZoneData(int* pPAInfo);

private:

	GlAlphaTexRect m_ParkSymbol;
	int m_iPrevRenderIndex;
	float m_fColor[ePASymbolColorNum][3];

	ScreenPosition m_SymbolPos[eParkSymbolPosNum];
	float m_SymbolSize[ePARearZoneNum];
	PASymbolColor m_SymbolColor[ePARearZoneNum];
	int m_iCurrentZone;

	FrequencyCntl m_FrqCntl;
	bool m_bOverTime;

	//UPA Type: @0--4 zone UPA, @1--8 zone UPA
	int m_iUPAType;
};

#endif /* GLPARKSYMBOL_H_ */
