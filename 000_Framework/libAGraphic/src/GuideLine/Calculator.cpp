#include "Calculator.h"


namespace Harman {
namespace Adas {
namespace AFramework {
namespace AGraphic {

Calculator::Calculator()
{
	m_pGroups = NULL;
	m_iGroupNum = 0;

	m_pSideLineInfo = NULL;
	m_pDistLineInfo = NULL;
	m_bDistortCorrection = false;
	m_GuideLineType = eStaticGuideLine;
	m_fPrevSWADeg = 0.0f;

	vehicle.wheelBase = 2.946;//l
	vehicle.rearAxleOffset = 1.21;
	vehicle.maxSteeringAngle = 560.0f;
	vehicle.inverseFrontRatio = 0.0582*R_PI / 180.0f;
	vehicle.inverseRearRatio = 0.0f;
	m_bTurnRadiusSmall = false;

	SetVehicleSteeringAngle(0);
}

Calculator::~Calculator()
{
	FreeGMLineInfo();
	FreeLinesData();
	for (int i = 0; i < 8; i++)
	{
		delete[] pTexData[i];
	}
}

int Calculator::Init(guidelineinfo info)
{
	int ret=0;
	cameraPara = info.camparam;
	setCameraMatrix();
	SetWindowParam(info.width, info.height);

	steer_params vechicleInfo;
	vechicleInfo.wheelBase = info.GUIDELINE_PARA.wheelbase;
	vechicleInfo.rearAxleOffset = info.GUIDELINE_PARA.rearspace;
	vechicleInfo.swaDeltaAngle = info.GUIDELINE_PARA.angle/2;

	if (vechicleInfo.wheelBase<0 || vechicleInfo.wheelBase >GUIDELINE_MAXWHEELBASE)
	{
		//printf("wheelbase out of range\n");
		return GUIDELINE_ERROR_WHEELBASEOUTOFRANGE;
	}

	if (vechicleInfo.swaDeltaAngle <-GUIDELINE_MAXANGEL || vechicleInfo.swaDeltaAngle>GUIDELINE_MAXANGEL)
	{
		//printf("Angel out of range\n");
		return GUIDELINE_ERROR_ANGELOUTOFRANGE;
	}

	InitTrajectory(vechicleInfo);
	int GuideLine_Type = info.GUIDELINE_PARA.dynamic;
	if (eStaticGuideLine == GuideLine_Type || info.GUIDELINE_PARA.angle == 0)
	{
		InitLineParam(GUIDELINE_GROUP_NUM, info.groupSeq, info.tickLength,
			GUIDELINE_MARKER_STARTDIS, OVLAY_DELTA_DIST_MARKS, OVLAY_THICK_DIST_MARKS,
			OVLAY_NUM_DIST_MARKS, OVLAY_TRACK_WIDTH, GUIDELINE_WIDTH, eStaticGuideLine, false);
	}
	else if (eDynamicGuideLine == GuideLine_Type)
	{
		InitLineParam(GUIDELINE_GROUP_NUM, info.groupSeq, info.tickLength,
			GUIDELINE_MARKER_STARTDIS, OVLAY_DELTA_DIST_MARKS, OVLAY_THICK_DIST_MARKS,
			OVLAY_NUM_DIST_MARKS, OVLAY_TRACK_WIDTH, GUIDELINE_WIDTH, eDynamicGuideLine, false);
	}
	SetSWAUpdatePrecision(STEERING_WHEEL_DELTA);
	return ret;
}

int Calculator::Update(guidelineinfo info)
{
	int ret=0;
	m_GuideLineType = eDynamicGuideLine;
	steer_params vechicleInfo;
	vechicleInfo.wheelBase = info.GUIDELINE_PARA.wheelbase;
	vechicleInfo.rearAxleOffset = info.GUIDELINE_PARA.rearspace;
	vechicleInfo.swaDeltaAngle = info.GUIDELINE_PARA.angle/2;
	if (vechicleInfo.wheelBase<0 || vechicleInfo.wheelBase >10)
	{
		//printf("wheelbase out of range\n");
		return GUIDELINE_ERROR_WHEELBASEOUTOFRANGE;
	}

	if (vechicleInfo.swaDeltaAngle <-45 || vechicleInfo.swaDeltaAngle>45)
	{
		//printf("Angel out of range\n");
		return GUIDELINE_ERROR_ANGELOUTOFRANGE;
	}
	InitTrajectory(vechicleInfo);
	SetVehicleSteeringAngle(info.GUIDELINE_PARA.angle);
	CalGuideLineData();
	return ret;
}

void Calculator::SetVehicleSteeringAngle(float Deg)
{
	if (Deg > vehicle.maxSteeringAngle)
		m_fSteerWheelAngle = vehicle.maxSteeringAngle;
	else if (Deg < -vehicle.maxSteeringAngle)
		m_fSteerWheelAngle = -vehicle.maxSteeringAngle;
	else
		m_fSteerWheelAngle = Deg;

	m_fFrontWheelAngle = vehicle.inverseFrontRatio * m_fSteerWheelAngle;
	m_fRearWheelAngle = vehicle.inverseRearRatio * m_fSteerWheelAngle;
	CalTrajectoryParam();
}

void Calculator::CalTrajectoryParam()
{
	if (fabs(m_fSteerWheelAngle) < STEER_WHEEL_ANGLE_PRECISION)
	{
		m_fTurningCenterX = 99999999.0;
		m_fTurningCenterY = 0.0;
	}
	else
	{
		float tmpCenter;
		if (fabs(vehicle.inverseRearRatio) < INVERSE_REAR_RATIO_PRECISION)
		{
			tmpCenter = vehicle.wheelBase / tan(m_fFrontWheelAngle);
			m_fTurningCenterX = tmpCenter;
			m_fTurningCenterY = 0.0;

		}
		else
		{
			tmpCenter = vehicle.wheelBase*cos(m_fFrontWheelAngle) / sin(m_fFrontWheelAngle + m_fRearWheelAngle);
			m_fTurningCenterX = tmpCenter*cos(m_fRearWheelAngle);
			m_fTurningCenterY = tmpCenter*sin(m_fRearWheelAngle);
		}
	}

	m_fTurningTotalY = m_fTurningCenterY - vehicle.rearAxleOffset;
	m_fInvRadius = 1.0 / sqrt((m_fTurningCenterX*m_fTurningCenterX) + (m_fTurningTotalY*m_fTurningTotalY));
	if (m_fInvRadius > 10.0)
	{
		m_bTurnRadiusSmall = true;
		printf("radius is too small(less than 0.1 meter);\n");
		return;
	}

	m_fLeftStartX = -m_fHalfTrackWidth - m_fTurningCenterX;
	m_fLeftStartY = -m_fTurningTotalY;
	m_fRightStartX = m_fHalfTrackWidth - m_fTurningCenterX;
	m_fRightStartY = -m_fTurningTotalY;

}



void Calculator::FreeLinesData()
{
	if (m_pGroups)
	{
		for (int i = 0; i < m_iGroupNum; i++)
			FreeGroupData(i);
		free(m_pGroups);
	}
}

void Calculator::FreeGroupData(int index)
{
	if (m_pGroups[index].pLinePtNums)
		free(m_pGroups[index].pLinePtNums);

	int lineNums = m_pGroups[index].lineNums;
	if (m_pGroups[index].pLineData)
	{
		for (int i = 0; i < lineNums; i++)
			free(m_pGroups[index].pLineData[i]);
		free(m_pGroups[index].pLineData);
	}

	if (m_pGroups[index].pBorderIndex)
		free(m_pGroups[index].pBorderIndex);
	if (m_pGroups[index].pBorderData)
		free(m_pGroups[index].pBorderData);
	if (m_pGroups[index].pLineBorderStartIndex)
		free(m_pGroups[index].pLineBorderStartIndex);
	if (m_pGroups[index].pLineIndexElemStartNum)
		free(m_pGroups[index].pLineIndexElemStartNum);
	if (m_pGroups[index].pLinePtElemStartNum)
		free(m_pGroups[index].pLinePtElemStartNum);
}

void Calculator::FreeGMLineInfo()
{
	if (m_pSideLineInfo)
		free(m_pSideLineInfo);
	if (m_pDistLineInfo)
	{
		for (int i = 0; i < m_iGroupNum; i++)
		{
			free(m_pDistLineInfo[i].dist);
		}
		free(m_pDistLineInfo);
	}
}




void Calculator::setCameraMatrix()
{
	setIntrinsicMatrix();
	setExtrinsicMatrix();
	setInvExtrinsicMatrix();
	setProjectionMatrix();

	m_ProjMatTranspose = cameraPara.mat.projection.transpose();
	m_ExtrinMatTranspose = cameraPara.mat.ex_all.transpose();
}

void Calculator::setIntrinsicMatrix()
{
	PVRTMat4* pMat = &cameraPara.mat.intrin;
	*pMat = PVRTMat4::Identity();
	float* pData = pMat->ptr();
	pData[0] = cameraPara.intrinsic.fx;
	pData[5] = cameraPara.intrinsic.fy;
	pData[8] = cameraPara.intrinsic.cx;
	pData[9] = cameraPara.intrinsic.cy;
}

void Calculator::setExtrinsicMatrix()
{
	float tx = -cameraPara.extrinsic.tx;
	float ty = -cameraPara.extrinsic.ty;
	float tz = -cameraPara.extrinsic.tz;

	PVRTMat4 transMat = PVRTMat4::Translation(tx, ty, tz);

	float rx = -R_Deg2Rad(cameraPara.extrinsic.rx);
	float ry = -R_Deg2Rad(cameraPara.extrinsic.ry);
	float rz = -R_Deg2Rad(cameraPara.extrinsic.rz);

	PVRTMat4 rotX = PVRTMat4::RotationX(rx);
	PVRTMat4 rotY = PVRTMat4::RotationY(ry);
	PVRTMat4 rotZ = PVRTMat4::RotationZ(rz);

	PVRTMat4 rotYZ = rotY*rotZ;
	PVRTMat4 rotXYZ = rotX*rotYZ;

	cameraPara.mat.ex_all = rotXYZ * transMat;

}

void Calculator::setInvExtrinsicMatrix()
{
	float tx = cameraPara.extrinsic.tx;
	float ty = cameraPara.extrinsic.ty;
	float tz = cameraPara.extrinsic.tz;

	PVRTMat4 transMat = PVRTMat4::Translation(tx, ty, tz);

	float rx = R_Deg2Rad(cameraPara.extrinsic.rx);
	float ry = R_Deg2Rad(cameraPara.extrinsic.ry);
	float rz = R_Deg2Rad(cameraPara.extrinsic.rz);

	PVRTMat4 rotX = PVRTMat4::RotationX(rx);
	PVRTMat4 rotY = PVRTMat4::RotationY(ry);
	PVRTMat4 rotZ = PVRTMat4::RotationZ(rz);

	PVRTMat4 rotZY = rotZ*rotY;
	PVRTMat4 rotZYX = rotZY*rotX;

	cameraPara.mat.ex_all_inv = transMat*rotZYX;

}

void Calculator::setProjectionMatrix()
{
	PVRTMat4 tmpMat = PVRTMat4::Identity();
	float* tmpPtr = tmpMat.ptr();
	tmpPtr[0] = -1.0;

	cameraPara.mat.projection = cameraPara.mat.intrin*tmpMat*cameraPara.mat.ex_all;
}

void Calculator::SetWindowParam(int winWidth, int winHeight)
{
	m_iScreenWidth = winWidth;
	m_iScreenHeight = winHeight;
}

void Calculator::InitTrajectory(steer_params& param)
{
	vehicle.wheelBase = param.wheelBase;
	vehicle.rearAxleOffset = param.rearAxleOffset;
	vehicle.maxSteeringAngle = param.saturationAngle;
	vehicle.inverseFrontRatio = param.invFrontRatio*R_PI / 180.0f;
	vehicle.inverseRearRatio = param.invRearRatio*R_PI / 180.0f;
	vehicle.vehicleAngle = param.swaDeltaAngle*R_PI / 180.0f;
	m_fHalfTrackWidth = param.trackWidth / 2;
	m_bTurnRadiusSmall = false;
}


void Calculator::InitLineParam(int groupNum, float* sepDis, float* LSegExtendLength, float markStartDis,
	float markDeltaDis, float markThickDis, int markNum, float trackWidth, int lineWidth, GuideLineType type, bool bUnDistort)
{

	m_iGroupNum = groupNum;
	m_fMarkDeltaDis = markDeltaDis;
	m_iMarkDeltaNum = markNum;
	m_fTrackWidth_dist = trackWidth;
	m_fTrackWidth_side = OVLAY_SIDE_WIDTH;
	m_iLinePixelWidth = lineWidth * 2;

	m_bDistortCorrection = bUnDistort;
	m_GuideLineType = type;

	SetSideLineParam(sepDis, LSegExtendLength);
	SetDistLineParam(markStartDis, markDeltaDis, markThickDis, markNum);
	MallocGroupLineData();
	SetGuideLineColor();


}

void Calculator::SetSideLineParam(float* sepDis, float* LSegExtendLength)
{
	m_pSideLineInfo = (sideLineInfo*)malloc(m_iGroupNum * sizeof(sideLineInfo));
	sideLineInfo* pLineInfo;
	for (int i = 0; i < m_iGroupNum; i++)
	{
		pLineInfo = &m_pSideLineInfo[i];
		//set start and end distance;
		pLineInfo->startDis = sepDis[2 * i];
		pLineInfo->endDis = sepDis[2 * i + 1];
		if (pLineInfo->endDis <= pLineInfo->startDis)
		{
			pLineInfo->lineNum = 0;
		}
		else
		{
			pLineInfo->lineNum = 2;
		}
		pLineInfo->LSegExtendLength = LSegExtendLength[i] * m_iScreenWidth;
		pLineInfo->linePtNum = CalSidePtNum(pLineInfo->startDis, pLineInfo->endDis);
		if (fabs(LSegExtendLength[i]) < 0.0001)
		{
			pLineInfo->bIsLSeg = false;
		}
		else
		{
			pLineInfo->bIsLSeg = true;
			pLineInfo->linePtNum += 1;//+1 point for L segment, it is a vertext point
		}
	}
}

int Calculator::CalSidePtNum(float startDis, float endDis)
{
	int outNum;
	float deltaDis = DIST_PER_POINT_CLOSE;
	float curDis = startDis;
	if (startDis > START_FAR_DIST)
		deltaDis = DIST_PER_POINT_FAR;
	if (startDis<START_FAR_DIST&&endDis>START_FAR_DIST)
	{
		outNum = 0;
		while (curDis <= endDis)
		{
			outNum++;
			curDis += deltaDis;
			if (fabs(curDis - START_FAR_DIST) < 0.01)
				deltaDis = DIST_PER_POINT_FAR;
		}
		if (fabs(endDis - curDis) < deltaDis - 0.01)
			outNum++;
	}
	else
	{
		outNum = (endDis - startDis) / deltaDis + 1;

	}

	return outNum * 2;
}

void Calculator::SetDistLineParam(float startDis, float deltaDis, float markThickDis, int MarklineNum)
{
	m_pDistLineInfo = (distLineInfo*)malloc(m_iGroupNum*MarklineNum * sizeof(distLineInfo));
	distLineInfo* pLineInfo = &m_pDistLineInfo[0];

	for (int i = 0; i < m_iGroupNum; i++)
	{
		pLineInfo = &m_pDistLineInfo[i];
		if ((i % 2) == 0 && i != (m_iGroupNum - 1))
		{
			pLineInfo->lineNum = 0;
		}
		else
		{
			pLineInfo->lineNum = MarklineNum;
		}

		if (i == (m_iGroupNum - 1))
		{
			pLineInfo->linePtNum = 4;
			pLineInfo->dist = (float*)malloc(MarklineNum * sizeof(float));
		}
		else
		{
			pLineInfo->linePtNum = DIST_LINE_PTNUM;
			pLineInfo->dist = (float*)malloc(MarklineNum * sizeof(float));
			for (int j = 0; j < MarklineNum; j++)
			{
				pLineInfo->dist[j] = startDis + j*markThickDis;
			}
			startDis = pLineInfo->dist[0] + deltaDis;
		}
	}
}

void Calculator::MallocGroupLineData()
{
	m_pGroups = (linesData*)malloc(m_iGroupNum * sizeof(linesData));
	for (int i = 0; i < m_iGroupNum; i++)
		MallocGroupLineData(i);
}

void Calculator::MallocGroupLineData(int index)
{
	linesData* curLineData = &m_pGroups[index];
	sideLineInfo sideLineInfo = m_pSideLineInfo[index];
	distLineInfo distLineInfo = m_pDistLineInfo[index];
	int totalLineNum = sideLineInfo.lineNum + distLineInfo.lineNum;
	curLineData->lineNums = totalLineNum;

	curLineData->pLineData = (float**)malloc(totalLineNum * sizeof(float*));
	curLineData->pLinePtNums = (int*)malloc(totalLineNum * sizeof(int));

	MallocGroupSideLineData(index);
	MallocGroupDistLineData(index);
	MallocGroupBorderData(index);
}

void Calculator::MallocGroupSideLineData(int index)
{
	sideLineInfo lineInfo = m_pSideLineInfo[index];
	linesData* curLineData = &m_pGroups[index];
	int sideLineNum = lineInfo.lineNum;
	int linePtNum = lineInfo.linePtNum;

	for (int i = 0; i < sideLineNum; i++)
	{
		curLineData->pLinePtNums[i] = linePtNum;
		curLineData->pLineData[i] = (float*)malloc(linePtNum * 2 * sizeof(float));
	}
}

void Calculator::MallocGroupDistLineData(int index)
{
	distLineInfo lineInfo = m_pDistLineInfo[index];
	linesData* curLineData = &m_pGroups[index];
	int distLineNum = lineInfo.lineNum;
	int linePtNum = lineInfo.linePtNum;

	int lineoffset = 0;//default has NO side line in this group

	if (OVLAY_SUM_LINE_PER_GROUP == curLineData->lineNums) lineoffset = 2;

	for (int i = 0; i < distLineNum; i++)
	{
		curLineData->pLinePtNums[lineoffset] = linePtNum;
		curLineData->pLineData[lineoffset] = (float*)malloc(linePtNum * 2 * sizeof(float));
		lineoffset++;
	}
}

void Calculator::MallocGroupBorderData(int index)
{
	linesData* curLineData = &m_pGroups[index];
	int lineNum = curLineData->lineNums;
	curLineData->pLinePtElemStartNum = (unsigned short*)malloc(lineNum * sizeof(unsigned short));
	curLineData->pLineIndexElemStartNum = (unsigned short*)malloc(lineNum * sizeof(unsigned short));
	curLineData->pLineBorderStartIndex = (unsigned short*)malloc(lineNum * sizeof(unsigned short));

	unsigned short tmpPtElemNum;
	unsigned short tmpIndexElemNum;
	unsigned short totalPtElemNum = 0;
	unsigned short totalIndexElemNum = 0;
	unsigned short curStartIndex = 0;

	for (int i = 0; i < lineNum; i++)
	{
		curLineData->pLinePtElemStartNum[i] = totalPtElemNum;
		curLineData->pLineIndexElemStartNum[i] = totalIndexElemNum;
		curLineData->pLineBorderStartIndex[i] = curStartIndex;
		CalLine2DBorderPtNum(curLineData->pLinePtNums[i] / 2, tmpPtElemNum, tmpIndexElemNum);
		totalPtElemNum += tmpPtElemNum;
		totalIndexElemNum += tmpIndexElemNum;
		curStartIndex += (tmpPtElemNum / PTELEMNUM);
	}
	curLineData->pBorderPtElemNum = totalPtElemNum;
	curLineData->pBorderIndexNum = totalIndexElemNum;
	curLineData->pBorderData = (float*)malloc(totalPtElemNum * sizeof(float));
	curLineData->pBorderIndex = (unsigned short*)malloc(totalIndexElemNum * sizeof(unsigned short));
}

void Calculator::CalLine2DBorderPtNum(int ptNum, unsigned short& outPtElemNum, unsigned short& outIndexNum)
{
	if (ptNum == 0)
	{
		outPtElemNum = 0;
		outIndexNum = 0;
		return;
	}
	outPtElemNum = ptNum * 2 * PTELEMNUM;
	outIndexNum = (ptNum - 1) * 6;
}

void Calculator::CalGuideLineData()
{

	for (int i = 0; i < m_iGroupNum; i++)
		CalGroupValue(i);
}

void Calculator::CalGroupValue(int index)
{

	Cal2SideLinesPts(index);
	CalDistLinePts(index);
	CalLineBorder(index);

}

void Calculator::Cal2SideLinesPts(int index)
{
	linesData* curLineData = &m_pGroups[index];
	sideLineInfo curInfo = m_pSideLineInfo[index];
	float startDis = curInfo.startDis;
	float endDis = curInfo.endDis;
	float deltaDis;
	deltaDis = DIST_PER_POINT_CLOSE;
	if (startDis >= START_FAR_DIST)deltaDis = DIST_PER_POINT_FAR;

	if (curInfo.lineNum == 2)
	{
		float* pLeftLine = curLineData->pLineData[0];
		float* pRightLine = curLineData->pLineData[1];
		int sideLinePtNum = curInfo.linePtNum;

		if (curInfo.bIsLSeg)sideLinePtNum = sideLinePtNum - 1;

		int curElemIndex = 0;
		float curDis = startDis;
		if (startDis<START_FAR_DIST&&endDis>START_FAR_DIST)
		{
			for (int i = 0; i < sideLinePtNum; i++)
			{
				Cal2SideLineScreenPos(curDis, &pLeftLine[curElemIndex], &pRightLine[curElemIndex]);
				curElemIndex += 4;
				curDis += deltaDis;
				if (curDis > endDis)
					curDis = endDis;
				if (curDis >= START_FAR_DIST)
					deltaDis = DIST_PER_POINT_FAR;
			}
		}
		else
		{
			for (int i = 0; i < sideLinePtNum / 2; i++)
			{
				Cal2SideLineScreenPos(curDis, &pLeftLine[curElemIndex], &pRightLine[curElemIndex]);
				curElemIndex += 4;
				curDis += deltaDis;
				if (curDis > endDis)
					curDis = endDis;
			}
		}

		if (curInfo.bIsLSeg)
		{
			float tickLength = curInfo.LSegExtendLength/**2.0/m_iScreenWidth*/;
			float leftx = pLeftLine[(sideLinePtNum - 1) * 2];
			float lefty = pLeftLine[(sideLinePtNum - 1) * 2 + 1];
			float rightx = pRightLine[(sideLinePtNum - 1) * 2];
			float righty = pRightLine[(sideLinePtNum - 1) * 2 + 1];
			float length = sqrt((leftx - rightx)*(leftx - rightx) + (lefty - righty)*(lefty - righty));
			float dirx = (rightx - leftx) / length;
			float diry = (righty - lefty) / length;
			pLeftLine[sideLinePtNum * 2] = leftx + dirx*tickLength;
			pLeftLine[sideLinePtNum * 2 + 1] = lefty + diry*tickLength;
			pRightLine[sideLinePtNum * 2] = rightx - dirx*tickLength;
			pRightLine[sideLinePtNum * 2 + 1] = righty - diry*tickLength;
		}
	}

}

void Calculator::CalDistLinePts(int index)
{
	distLineInfo lineInfo = m_pDistLineInfo[index];
	int lineNum = lineInfo.lineNum;
	if (lineNum == 0)return;
	linesData* curLineData = &m_pGroups[index];
	int offset = 0;
	if (OVLAY_SUM_LINE_PER_GROUP == curLineData->lineNums) offset = 2;
	for (int i = 0; i < lineNum; i++)
		CalDistLineScreenPos(lineInfo.dist[i], lineInfo.linePtNum, curLineData->pLineData[i + offset]);//output to pLineData
}

void Calculator::Cal2SideLineScreenPos(float dist, float* left, float* right)
{
	float leftx, lefty, rightx, righty;

	Get2SideLineWorldPos(dist, leftx, lefty, rightx, righty);
	CalScreenPos(leftx, lefty, left[0], left[1]);
	CalScreenPos(rightx, righty, right[0], right[1]);
	//second times
	leftx = leftx - DIST_LINE_WIDTH;
	rightx = rightx + DIST_LINE_WIDTH;
	CalScreenPos(leftx, lefty, left[2], left[3]);
	CalScreenPos(rightx, righty, right[2], right[3]);

}

void Calculator::CalDistLineScreenPos(float dist, int ptNum, float* pData)
{
	float halfWidth = m_fTrackWidth_dist / 2;
	int curSwa = m_fSteerWheelAngle;
	float leftx, lefty, rightx, righty;
	leftx = -halfWidth;
	lefty = dist;
	rightx = halfWidth;
	righty = dist;

	float dlefty, dleftx, drightx, drighty;
	float curX = leftx, curY = lefty, curYS = lefty + SIDE_LINE_WIDTH;
	ptNum = ptNum / 2;
	float deltaX = (rightx - leftx) / (ptNum - 1);
	float deltaY = (righty - lefty) / (ptNum - 1);
	int elemIndex = 0;
	float l = vehicle.wheelBase;
	float angle = vehicle.vehicleAngle;

	//static line
	if (eStaticGuideLine == m_GuideLineType || 0 == angle)
	{
		for (int i = 0; i < ptNum; i++)
		{

			CalScreenPos(curX, curY, pData[elemIndex], pData[elemIndex + 1]);
			CalScreenPos(curX, curYS, pData[elemIndex + 2], pData[elemIndex + 3]);
			elemIndex += 4;
			curX += deltaX;
		}

	}
	else//dynamic Calculator
	{
		for (int i = 0; i < ptNum; i++)
		{

			dlefty = (l*cos(angle) / sin(angle) - curX)*sin(sin(angle)*curY / l);
			dleftx = -(l*cos(angle) / sin(angle) - curX)*cos(sin(angle)*curY / l) + l*cos(angle) / sin(angle);
			CalScreenPos(dleftx, dlefty, pData[elemIndex], pData[elemIndex + 1]);

			drighty = (l*cos(angle) / sin(angle) - curX)*sin(sin(angle)*curYS / l);
			drightx = -(l*cos(angle) / sin(angle) - curX)*cos(sin(angle)*curYS / l) + l*cos(angle) / sin(angle);

			CalScreenPos(drightx, drighty, pData[elemIndex + 2], pData[elemIndex + 3]);

			elemIndex += 4;
			curX += deltaX;
			curY += deltaY;
		}

	}

}

void Calculator::Get2SideLineWorldPos(float dist, float& leftx, float& lefty, float& rightx, float& righty)
{
	float halfWidth = m_fTrackWidth_side / 2;
	float curSwa = vehicle.vehicleAngle;
	//static line
	if (eStaticGuideLine == m_GuideLineType || 0 == curSwa)
	{
		leftx = -halfWidth;
		lefty = dist;
		rightx = halfWidth;
		righty = dist;

	}
	else// dynamic line
	{
		float l = vehicle.wheelBase;
		float angle = vehicle.vehicleAngle;
		lefty = (l*cos(angle) / sin(angle) + halfWidth)*sin(sin(angle)*dist / l);
		leftx = -(l*cos(angle) / sin(angle) + halfWidth)*cos(sin(angle)*dist / l) + l*cos(angle) / sin(angle);

		righty = (l*cos(angle) / sin(angle) - halfWidth)*sin(sin(angle)*dist / l);
		rightx = -(l*cos(angle) / sin(angle) - halfWidth)*cos(sin(angle)*dist / l) + l*cos(angle) / sin(angle);
	}
}

void Calculator::CalScreenPos(float x, float y, float& u, float& v)
{
	float tmpU, tmpV;
	if (m_bDistortCorrection)
		world2Pixel_noDistort(x, y, 0.0, tmpU, tmpV);
	else
		world2Pixel(x, y, 0.0, tmpU, tmpV);

	u = tmpU * m_iScreenWidth;
	//v = (1 - tmpV)*m_iScreenHeight;
	v = (tmpV)*m_iScreenHeight;
}

void Calculator::world2Pixel_noDistort(const float x, const float y, const float z, float &u, float &v)
{
	float xCam, yCam, zCam;
	world2Cam(x, y, z, xCam, yCam, zCam);
	cam2Pixel_noDistort(xCam, yCam, zCam, u, v);
}

void Calculator::world2Cam(const float x, const float y, const float z, float &xCam, float &yCam, float &zCam)
{
	PVRTVec4 inVec(x, y, z, 1.0);

	PVRTVec4 outVec = cameraPara.mat.ex_all*inVec;

	float* pOut = outVec.ptr();

	xCam = pOut[0];
	yCam = pOut[1];
	zCam = pOut[2];

}

void Calculator::cam2Pixel_noDistort(const float x, const float y, const float z, float &u, float &v)
{
	float x1 = -x / z;
	float y1 = y / z;

	u = cameraPara.intrinsic.fx * x1 + cameraPara.intrinsic.cx;
	v = (cameraPara.intrinsic.fy * y1 + cameraPara.intrinsic.cy);
}

void Calculator::world2Pixel(const float x, const float y, const float z, float &u, float &v)
{
	float xCam, yCam, zCam;
	world2Cam(x, y, z, xCam, yCam, zCam);
	cam2Pixel(xCam, yCam, zCam, u, v);
}

void Calculator::cam2Pixel(const float x, const float y, const float z, float &u, float &v)
{
	float k1 = cameraPara.intrinsic.k1;
	float k2 = cameraPara.intrinsic.k2;

	float x1 = -x / z;
	float y1 = y / z;

	float r2 = x1 * x1 + y1 * y1;
	float r4 = r2 * r2;
	float scale = 1.0 + k1 * r2 + k2 * r4;

	float x2 = x1 * scale;
	float y2 = y1 * scale;

	u = cameraPara.intrinsic.fx * x2 + cameraPara.intrinsic.cx;
	v = (cameraPara.intrinsic.fy * y2 + cameraPara.intrinsic.cy);
}

void Calculator::CalLineBorder(int index)
{
	int lineNum = m_pGroups[index].lineNums;
	linesData* group = &m_pGroups[index];
	float** lineData = group->pLineData;
	int *linePtNum = group->pLinePtNums;
	unsigned short* lineStartIndex = group->pLineBorderStartIndex;
	unsigned short* linePtElemNum = group->pLinePtElemStartNum;
	unsigned short* lineIndexNum = group->pLineIndexElemStartNum;
	float* borderData = group->pBorderData;
	unsigned short* borderIndex = group->pBorderIndex;

	if (index == (m_iGroupNum - 1))
	{
		for (int i = 0; i < lineNum; i++)
		{
			CalLine2DBackground(lineData[i], linePtNum[i], m_iLinePixelWidth/*m_fRenderLineWidth*/, lineStartIndex[i],
				&borderData[linePtElemNum[i]], &borderIndex[lineIndexNum[i]]);
		}
	}
	else
	{
		for (int i = 0; i < lineNum; i++)
		{
			CalLine2DBorder(lineData[i], linePtNum[i], m_iLinePixelWidth/*m_fRenderLineWidth*/, lineStartIndex[i],
				&borderData[linePtElemNum[i]], &borderIndex[lineIndexNum[i]]);
		}
	}
}

void Calculator::CalLine2DBackground(float* input, int ptNum, float width, unsigned short startIndex, float* outpt, unsigned short* outIndex)
{
	point2D pt1(0.0, 0.0);//p0
	point2D pt2(m_iScreenWidth, 0.0);//p1
	point2D pt3(0.0, m_iScreenHeight), pt4(m_iScreenWidth, m_iScreenHeight);
	CalStartPt2DBorderPts(pt1, pt2, width, outpt);
	outpt[2] = 0.0;
	outpt[3] = 0.0;
	outpt[6] = 1.0;
	outpt[7] = 0.0;
	int ptElementNum = 2 * PTELEMNUM;
	int indexElementNum = 0;
	CalEndPt2DBorderPts(pt3, pt4, width, &outpt[ptElementNum], startIndex, &outIndex[indexElementNum]);
	outpt[10] = 0.0;
	outpt[11] = 1.0;
	outpt[14] = 1.0;
	outpt[15] = 1.0;
}

void Calculator::CalLine2DBorder(float* input, int ptNum, float width, unsigned short startIndex, float* outpt, unsigned short* outIndex)
{
	point2D pt1(input[0], input[1]);//0,1,2,3
	point2D pt2(input[INPUTELEMENTNUM], input[INPUTELEMENTNUM + 1]);//4,5,6,7
	point2D pt3, pt4;
	CalStartPt2DBorderPts(pt1, pt2, width, outpt);

	int ptElementNum = 2 * PTELEMNUM;
	int indexElementNum = 0;
	ptNum = ptNum / 2;
	for (int i = 1; i < ptNum; i++)
	{
		pt3.SetData(input[(2 * i)*INPUTELEMENTNUM], input[(2 * i)*INPUTELEMENTNUM + 1]);
		pt4.SetData(input[(2 * i)*INPUTELEMENTNUM + 2], input[(2 * i)*INPUTELEMENTNUM + 3]);
		CalEndPt2DBorderPts(pt3, pt4, width, &outpt[ptElementNum], startIndex, &outIndex[indexElementNum]);
		ptElementNum += 2 * PTELEMNUM;
		indexElementNum += 6;
		startIndex += 2;

	}

}

void Calculator::CalStartPt2DBorderPts(const point2D& pt, const point2D& nextPt, float width, float* out)
{
	int ptElemNum = 0;
	point2D tmpPt[2] = { pt,nextPt };

	SetGen2DPoints(tmpPt, -0.25, 0.75, &out[ptElemNum]);
}

void Calculator::SetGen2DPoints(point2D* pt, float coord1, float coord2, float* pOut)
{
	int ptElemNum = 0;
	SetGen2DPoint(pt[0], coord1, 0.5, pOut);
	ptElemNum += PTELEMNUM;
	SetGen2DPoint(pt[1], coord2, 0.5, &pOut[ptElemNum]);
}

void Calculator::SetGen2DPoint(const point2D& pt, float texCoordX, float texCoordY, float* pOut)
{
	int index = 0;
	pOut[index++] = pt.x;
	pOut[index++] = pt.y;
	pOut[index++] = texCoordX;
	pOut[index++] = texCoordY;
}

void Calculator::CalEndPt2DBorderPts(const point2D& pt, const point2D& prevPt, float width, float* out, unsigned short startIndex, unsigned short* outIndex)
{
	int ptElemNum = 0;
	point2D tmpPt[2] = { pt,prevPt };
	SetGen2DPoints(tmpPt, -0.25, 0.75, &out[ptElemNum]);
	SetGenTriangleIndex(startIndex, outIndex);
}

void Calculator::SetGenTriangleIndex(unsigned short startIndex, unsigned short* pIndex)
{
	pIndex[0] = startIndex;
	pIndex[1] = startIndex + 1;
	pIndex[2] = startIndex + 2;
	pIndex[3] = startIndex + 1;
	pIndex[4] = startIndex + 3;
	pIndex[5] = startIndex + 2;
}

void Calculator::SetSWAUpdatePrecision(float delta)
{
	m_fUpdateDeltaAngleDeg = delta;
}


void Calculator::SetGuideLineColor()
{
	LineTex_width = 4;
	LineTex_height = 4;
	for (int k = 0; k < (m_iGroupNum - 1); k++)
	{

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				GLuint col;
				if (k == 0)
				{
					//col = (GLuint) (0L<<24) + (0L<<16) + (255L<<8) + (255L);//yellow
					col = (GLuint)(0L << 24) + (0L << 16) + (0L << 8) + (255L);//red
				}
				else if (k == 1)
				{
					//col = (GLuint) (0L<<24) + (0L<<16) + (255L<<8) + (0L);//green
					//col = (GLuint)(0L << 24) + (0L << 16) + (255L << 8) + (255L);//yellow
					col = (GLuint)(0L << 24) + (0L << 16) + (0L << 8) + (255L);//red
				}
				else if (k == 2)
				{
					//col = (GLuint) (0L<<24) + (255L<<16) + (0L<<8) + (0L);//blue
					//col = (GLuint)(0L << 24) + (34L << 16) + (139L << 8) + (34L);//dark green
					col = (GLuint)(0L << 24) + (0L << 16) + (255L << 8) + (255L);
				}
				else if (k == 3)
				{
					col = (GLuint)(0L << 24) + (0L << 16) + (255L << 8) + (255L);
				}
				else
				{
					col = (GLuint)(0L << 24) + (34L << 16) + (139L << 8) + (34L);//dark green
				}
				pTexData[k][j*LineTex_width + i] = col;
			}
		}
	}
}



}//namespace AGraphic
}//namespace Adas
}//namespace AFramework
}//namespace Harman
