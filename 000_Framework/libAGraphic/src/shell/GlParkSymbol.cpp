/*
 * GlParkSymbol.cpp
 *
 *  Created on: 2012-4-10
 *      Author: QiLiu
 */
#include "GlParkSymbol.h"

GlParkSymbol::GlParkSymbol()
{
	m_iPrevRenderIndex = 0;

	m_fColor[RVS_PA_SYMBOL_RED][0] = 1.0;
	m_fColor[RVS_PA_SYMBOL_RED][1] = 0.0;
	m_fColor[RVS_PA_SYMBOL_RED][2] = 0.0;

	m_fColor[RVS_PA_SYMBOL_ORANGE][0] = 1.0;
	m_fColor[RVS_PA_SYMBOL_ORANGE][1] = 0.5;
	m_fColor[RVS_PA_SYMBOL_ORANGE][2] = 0.0;

//	m_SymbolPosition[0][0].x = RVS_UPA_CENTER_U_PIXEL_12*2-1.0;
//	m_SymbolPosition[0][0].y = 1.0 - RVS_UPA_CENTER_V_PIXEL_12*2;
//	m_SymbolPosition[0][1].x = RVS_UPA_CENTER_U_PIXEL_9*2-1.0;
//	m_SymbolPosition[0][1].y = 1.0 - RVS_UPA_CENTER_V_PIXEL_9*2;
//	m_SymbolPosition[0][2].x = RVS_UPA_CENTER_U_PIXEL_6*2-1.0;
//	m_SymbolPosition[0][2].y = 1.0 - RVS_UPA_CENTER_V_PIXEL_6*2;
//	m_SymbolPosition[0][3].x = RVS_UPA_CENTER_U_PIXEL_3*2-1.0;
//	m_SymbolPosition[0][3].y = 1.0 - RVS_UPA_CENTER_V_PIXEL_3*2;
//
//	m_SymbolPosition[1][0].x = RVS_UPA_CENTER_U_PIXEL_11*2-1.0;
//	m_SymbolPosition[1][0].y = 1.0 - RVS_UPA_CENTER_V_PIXEL_11*2;
//	m_SymbolPosition[1][1].x = RVS_UPA_CENTER_U_PIXEL_8*2-1.0;
//	m_SymbolPosition[1][1].y = 1.0 - RVS_UPA_CENTER_V_PIXEL_8*2;
//	m_SymbolPosition[1][2].x = RVS_UPA_CENTER_U_PIXEL_5*2-1.0;
//	m_SymbolPosition[1][2].y = 1.0 - RVS_UPA_CENTER_V_PIXEL_5*2;
//	m_SymbolPosition[1][3].x = RVS_UPA_CENTER_U_PIXEL_2*2-1.0;
//	m_SymbolPosition[1][3].y = 1.0 - RVS_UPA_CENTER_V_PIXEL_2*2;
//
//	m_SymbolPosition[2][0].x = RVS_UPA_CENTER_U_PIXEL_10*2-1.0;
//	m_SymbolPosition[2][0].y = 1.0 - RVS_UPA_CENTER_V_PIXEL_10*2;
//	m_SymbolPosition[2][1].x = RVS_UPA_CENTER_U_PIXEL_7*2-1.0;
//	m_SymbolPosition[2][1].y = 1.0 - RVS_UPA_CENTER_V_PIXEL_7*2;
//	m_SymbolPosition[2][2].x = RVS_UPA_CENTER_U_PIXEL_4*2-1.0;
//	m_SymbolPosition[2][2].y = 1.0 - RVS_UPA_CENTER_V_PIXEL_4*2;
//	m_SymbolPosition[2][3].x = RVS_UPA_CENTER_U_PIXEL_1*2-1.0;
//	m_SymbolPosition[2][3].y = 1.0 - RVS_UPA_CENTER_V_PIXEL_1*2;
//
//	m_fSymbolColor[0][0] = 1.0;
//	m_fSymbolColor[0][1] = 0.0;
//	m_fSymbolColor[0][2] = 0.0;
//
//	m_fSymbolColor[1][0] = 1.0;
//	m_fSymbolColor[1][1] = 0.0;
//	m_fSymbolColor[1][2] = 0.0;
//
//	m_fSymbolColor[2][0] = 1.0;
//	m_fSymbolColor[2][1] = 0.5;
//	m_fSymbolColor[2][2] = 0.0;
//
//	m_fSymbolColor[3][0] = 1.0;
//	m_fSymbolColor[3][1] = 0.5;
//	m_fSymbolColor[3][2] = 0.0;
//
//	m_fSymbolSize[0] = 0.225;
//	m_fSymbolSize[1] = 0.1875;
//	m_fSymbolSize[2] = 0.15;
//	m_fSymbolSize[3] = 0.1125;
}

GlParkSymbol::~GlParkSymbol()
{
	;
}

//void GlParkSymbol::Init(const char *fileName, ParkSymbolInfo* pInfo, int flashRate,int flashDuration,int screenWidth, int screenHeight)
//{
//	m_screenWidth = screenWidth;
//	m_screenHeight = screenHeight;
//	m_ParkSymbol.Init(fileName);
//
//	InitRenderInfo(pInfo);
//	m_FrqCntl.SetParam(flashRate,flashDuration);
//	m_FrqCntl.Reset();
//	m_iPrevRenderIndex = 0;
//}

void GlParkSymbol::Init(const char* fileName,float* symbolPos,float* symbolSize,PASymbolColor* symbolColor,
		int flashRate,int flashDuration,int screenWidth,int screenHeight,int UPAType)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
//	printf("GlParkSymbol init!\n");
	m_ParkSymbol.Init(fileName,screenWidth,screenHeight);

	InitRenderInfo(symbolPos,symbolSize,symbolColor);
	m_FrqCntl.SetParam(flashRate,flashDuration);
	m_FrqCntl.Reset();
	m_iPrevRenderIndex = 0;

	m_iUPAType = UPAType;
}

int GlParkSymbol::Init(const char* fileName,rvs_parkAssist_params upaParam,float* symbolSize,
		PASymbolColor* symbolColor,int flashRate,int flashDuration,
		int screenWidth,int screenHeight/*,int UPAType*/)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
//	printf("GlParkSymbol init!\n");
	if(m_ParkSymbol.Init(fileName,screenWidth,screenHeight))
		return -1;

	InitRenderInfo(upaParam,symbolSize,symbolColor);

	m_FrqCntl.SetParam(flashRate,flashDuration);
	m_FrqCntl.Reset();
	m_iPrevRenderIndex = 0;

	m_iUPAType = upaParam.upaType;

	return 0;
}

void GlParkSymbol::Render(PVRTMat4& pvMat,int index)
{
	float scale = m_SymbolSize[m_iCurrentZone];
	float posX = m_SymbolPos[index].posX;
	float posY = m_SymbolPos[index].posY;
	int color = m_SymbolColor[m_iCurrentZone];

	m_ParkSymbol.Render(pvMat,scale,posX,posY,m_fColor[color]);
}

void GlParkSymbol::Render(PVRTMat4& pvMat,int* pPAInfo)
{
//	printf("Render!\n");
	PreprocessZoneData(pPAInfo);
	int index = GetCurRenderIndex(pPAInfo);
//	printf("index = %d\n",index);
	if(index >= eParkSymbolPosNum)
		return;
	if(index != m_iPrevRenderIndex)
	{
		m_FrqCntl.Reset();
		Render(pvMat,index);
		m_iPrevRenderIndex = index;
		m_bOverTime = false;
	}
	else
	{
		if(m_bOverTime)
		{
			//overTime, render solid;
			Render(pvMat,index);
		}
		else
		{
			if(!(m_bOverTime = m_FrqCntl.Overtime())&&m_FrqCntl.EvenInterval())
			{
				Render(pvMat,index);
			}
		}
	}
}

int GlParkSymbol::GetCurRenderIndex(const int* pPAInfo)
{
	int ret = eParkSymbolPosNum;
	int lowestZone = ePARearZoneNum;
	int renderRegion = 0;
	for(int i=0;i<ePARearRegionNum;i++)
	{
		if(pPAInfo[i])
		{
			if(pPAInfo[i]<lowestZone)
			{
				lowestZone = pPAInfo[i];
				renderRegion = i;
			}
			else if(pPAInfo[i] == lowestZone)
			{
				renderRegion = RVS_PA_REAR_REGION_2;
			}
		}

	}
	m_iCurrentZone = lowestZone;
	if(lowestZone == ePARearZoneNum)
		return ret;

//	ret = (ePARearZoneNum-1 - lowestZone)*ePARearRegionNum + (ePARearRegionNum - renderRegion) - 1;
	ret = (ePARearZoneNum-1 - lowestZone)*ePARearRegionNum + renderRegion;

	return ret;
}

void GlParkSymbol::PreprocessZoneData(int* pPAInfo)
{
	int curZoneData;
	if(m_iUPAType == 1)
	{
		//8 zone type
		for(int i=0;i<ePARearRegionNum;i++)
		{
			curZoneData = pPAInfo[i];
			if(curZoneData>=9)
				pPAInfo[i] = 0;
			else if(curZoneData==8)
				pPAInfo[i] = 4;
			else if(curZoneData>=2)
				pPAInfo[i] = curZoneData/2+1;
		}
	}
	else if(m_iUPAType == 0)
	{
		//4 zone type
		for(int i=0;i<ePARearRegionNum;i++)
		{
			curZoneData = pPAInfo[i];
			if(curZoneData>=5)
				pPAInfo[i] = 0;
		}
	}
}


//void GlParkSymbol::InitRenderInfo(ParkSymbolInfo* pInfo)
//{
//	int index;
//	for(int i=0;i<eParkSymbolPosNum;i++)
//	{
//		index = pInfo[i].epos;
//		m_RenderInfo[index].size = pInfo[i].size;
//		m_RenderInfo[index].posX = pInfo[i].posX*2.0-1.0;
//		m_RenderInfo[index].posY = 1.0 - pInfo[i].posY*2.0;
//		m_RenderInfo[index].color = pInfo[i].color;
//	}
//	m_iPrevRenderIndex = eParkSymbolPosNum;
//}

void GlParkSymbol::InitRenderInfo(const float* symbolPos,const float* symbolSize,const PASymbolColor* symbolColor)
{
	int index = 0;
	for(int i=0;i<eParkSymbolPosNum;i++)
	{
		m_SymbolPos[i].posX = symbolPos[index++]*2.0-1.0;
		m_SymbolPos[i].posY = 1.0 - symbolPos[index++]*2.0;
	}
	for(int i=0;i<ePARearZoneNum;i++)
	{
		m_SymbolSize[i] = symbolSize[i];
		m_SymbolColor[i] = symbolColor[i];
	}
}

void GlParkSymbol::InitRenderInfo(const rvs_parkAssist_params& upaPos,const float* symbolSize,
		const PASymbolColor* symbolColor)
{
	screenPos pos;
	for(int i=0;i<eParkSymbolPosNum;i++)
	{
		pos = upaPos.pixel[i];
		m_SymbolPos[i].posX = pos.u*2.0-1.0;
		m_SymbolPos[i].posY = 1.0 - pos.v*2.0;
//		printf("pos %d: %f,%f\n",i,m_SymbolPos[i].posX,m_SymbolPos[i].posY);
	}
	for(int i=0;i<ePARearZoneNum;i++)
	{
		m_SymbolSize[i] = symbolSize[i];
		m_SymbolColor[i] = symbolColor[i];
	}
}

//void GlParkSymbol::CalRenderPosition(int* pPAInfo)
//{
//	m_iPrevRenderZone = m_iRenderZone;
//	m_iPrevRenderRegion = m_iRenderRegion;
//	m_iPrevRenderSymbol = m_iPrevRenderSymbol;
//
//	int minRegion,minZoneRegionNum=0;
//	int minZone = PARK_SYMBOL_ZONE;
//	int zone;
//	for(int i=0;i<PARK_SYMBOL_REGION;i++)
//	{
//		zone = pPAInfo[i];
//		if(zone)
//		{
//			if(zone<minZone)
//			{
//				minZone = zone;
//				minZoneRegionNum = 1;
//				minRegion = i;
//			}
//			else if(zone == minZone)
//			{
//				minZoneRegionNum ++;
//			}
//		}
//	}
//	if(minZoneRegionNum==1)
//	{
//		m_iRenderSymbol = 1;
//		m_iRenderZone = minZone;
//		m_iRenderRegion = minRegion;
//	}
//	else if(minZoneRegionNum>1)
//	{
//		m_iRenderSymbol = 1;
//		m_iRenderZone = minZone;
//		m_iRenderRegion = 1;
//	}
//	else
//	{
//		//minZoneRegionNum = 0;
//		m_iRenderSymbol = 0;
//	}
//}
