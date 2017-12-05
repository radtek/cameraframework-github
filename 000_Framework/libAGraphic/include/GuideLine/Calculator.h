#ifndef __HARMAN_ADAS_AFRAMEWORK_AGRAPGIC_CALCULATOR_H_
#define __HARMAN_ADAS_AFRAMEWORK_AGRAPGIC_CALCULATOR_H_

#include "GuideLineTypeDef.h"

using namespace std;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AGraphic {

class Calculator
{
public:
	void Init(guidelineinfo info);

	void Update(guidelineinfo info);

	Calculator();

	~Calculator();

private:
	void SetGuideLineColor();
	void FreeGMLineInfo();
	void FreeLinesData();
	void FreeGroupData(int index);

	void SetVehicleSteeringAngle(float Deg);
	void CalTrajectoryParam();

	void setCameraMatrix();
	void setExtrinsicMatrix();
	void setIntrinsicMatrix();
	void setProjectionMatrix();
	void setInvExtrinsicMatrix();

	void SetSWAUpdatePrecision(float delta);
	void SetWindowParam(int winWidth, int winHeight);
	void InitTrajectory(steer_params& param);
	void InitLineParam(int groupNum, float* sepDis, float* LSegExtendLength, float markStartDis,
				float markDeltaDis, float markThickDis, int markNum, float trackWidth, int lineWidth, GuideLineType type = eStaticGuideLine, bool bUnDistort = false);
	void SetSideLineParam(float* sepDis, float* tickLength);
	void SetDistLineParam(float startDis, float deltaDis, float thick, int lineNum);
	void MallocGroupLineData();
	void MallocGroupLineData(int index);
	void MallocGroupSideLineData(int index);
	void MallocGroupDistLineData(int index);
	void MallocGroupBorderData(int index);
	void CalLine2DBorderPtNum(int ptNum, unsigned short& outPtElemNum, unsigned short& outIndexNum);
	void CalGuideLineData();
	int CalSidePtNum(float startDis, float endDis);
	void CalGroupValue(int index);
	void Cal2SideLinesPts(int index);
	void CalDistLinePts(int index);
	void CalLineBorder(int index);
	void Cal2SideLineScreenPos(float dist, float* left, float* right);
	void CalDistLineScreenPos(float dist, int ptNum, float* pData);
	void Get2SideLineWorldPos(float dist, float& leftx, float& lefty, float& rightx, float& righty);
	void CalScreenPos(float x, float y, float& u, float& v);
	void world2Pixel_noDistort(const float x, const float y, const float z, float &u, float &v);
	void world2Cam(const float x, const float y, const float z, float &xCam, float &yCam, float &zCam);
	void cam2Pixel_noDistort(const float x, const float y, const float z, float &u, float &v);
	void world2Pixel(const float x, const float y, const float z, float &u, float &v);
	void cam2Pixel(const float x, const float y, const float z, float &u, float &v);
	void CalLine2DBackground(float* input, int ptNum, float width, unsigned short startIndex, float* outpt, unsigned short* outIndex);
	void CalStartPt2DBorderPts(const point2D& pt, const point2D& nextPt, float width, float* out);
	void SetGen2DPoints(point2D* pt, float coord1, float coord2, float* pOut);
	void SetGen2DPoint(const point2D& pt, float texCoordX, float texCoordY, float* pOut);
	void CalEndPt2DBorderPts(const point2D& pt, const point2D& prevPt, float width, float* out, unsigned short startIndex, unsigned short* outIndex);
	void SetGenTriangleIndex(unsigned short startIndex, unsigned short* pIndex);
	void CalLine2DBorder(float* input, int ptNum, float width, unsigned short startIndex, float* outpt, unsigned short* outIndex);

private:
	cameraPara_t cameraPara;
	PVRTMat4 m_ProjMatTranspose;
	PVRTMat4 m_ExtrinMatTranspose;

	GMVehicleInfo_t vehicle;
	bool m_bTurnRadiusSmall;
	float m_fHalfTrackWidth;

	float m_fMarkDeltaDis;
	int m_iMarkDeltaNum;
	float m_fTrackWidth_dist;
	float m_fTrackWidth_side;
	bool m_bDistortCorrection;
	GuideLineType m_GuideLineType;

	sideLineInfo* m_pSideLineInfo;
	distLineInfo* m_pDistLineInfo;

	float m_fUpdateDeltaAngleDeg;
	float m_fPrevSWADeg;

	float m_fFrontWheelAngle;
	float m_fRearWheelAngle;
	float m_fSteerWheelAngle;

	float m_fLeftStartX;
	float m_fLeftStartY;
	float m_fRightStartX;
	float m_fRightStartY;
	float m_fTurningCenterX;
	float m_fTurningCenterY;
	float m_fTurningTotalY;
	float m_fInvRadius;

public:
	linesData* m_pGroups;
	int m_iGroupNum;
	int m_iLinePixelWidth;
	int m_iScreenWidth;
	int m_iScreenHeight;
	GLuint pTexData[8][16];
	int LineTex_width;
	int LineTex_height;
};

}//namespace AGraphic
}//namespace AFramework
}//namespace Adas
}//namespace Harman

#endif  //__HARMAN_ADAS_AFRAMEWORK_AGRAPGIC_CALCULATOR_H_
