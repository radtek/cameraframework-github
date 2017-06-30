/*
 * GlGuideLine_new.cpp
 *
 *  Created on: 2012-6-8
 *      Author: QiLiu
 */
#include "GlGuideLine.h"

GlGuideLine::GlGuideLine()
{
	pLCamera = NULL;
	//pTrajectory = NULL;

	m_pSideLineInfo = NULL;
	m_pDistLineInfo = NULL;

	m_bDistortCorrection = false;
	m_GuideLineType = eStaticGuideLine;
	//m_fSWADeg = 0.0;
	m_fPrevSWADeg = 0.0f;

}

GlGuideLine::~GlGuideLine()
{
	FreeGMLineInfo();
//	FreeGroupLineData();
//	FreeLinesData();
}

void GlGuideLine::SetWindowParam(int winWidth,int winHeight)
{
	m_iScreenWidth = winWidth;
	m_iScreenHeight = winHeight;
//	printf("winWidth = %d,winHeight=%d\n",winWidth,winHeight);
}


void GlGuideLine::InitLineParam(int groupNum,float* sepDis,float* LSegExtendLength,color3* groupColor,float markStartDis,
	float markDeltaDis,int markNum,float trackWidth,int lineWidth,LCamera* pCam,trajectory traj,
	GuideLineType type,bool bUnDistort)
{
	m_iGroupNum = groupNum;

	m_fMarkDeltaDis = markDeltaDis;
	m_iMarkDeltaNum = markNum;
	m_fTrackWidth = trackWidth;

	m_iLinePixelWidth = lineWidth*2;

	m_bDistortCorrection = bUnDistort;
	m_GuideLineType = type;

	pLCamera = pCam;
	m_Trajectory = traj;
	m_Trajectory.SetTrackWidth(trackWidth);
	m_Trajectory.SetVehicleSteeringAngle(0);

	SetSideLineParam(sepDis,LSegExtendLength);
	SetDistLineParam(markStartDis,markDeltaDis,markNum);
	MallocGroupLineData();
	SetGroupColor(groupColor);
	CalGuideLineData();
	InitView();
}

void GlGuideLine::InitLineParam(int groupNum,float* sepDis,float* LSegExtendLength,
		color3* groupColor,float markStartDis,rvs_steer_params steerParam,int lineWidth,
		LCamera* pCam,GuideLineType type,bool bUnDistort)
{
	m_iGroupNum = groupNum;
	m_fMarkDeltaDis = steerParam.deltaDistMarks;
	m_iMarkDeltaNum = steerParam.numDistMarks;
	m_fTrackWidth = steerParam.trackWidth;

	m_iLinePixelWidth = lineWidth*2;
//	printf("linePixelWidth=%d\n",m_iLinePixelWidth);

	m_bDistortCorrection = bUnDistort;
	m_GuideLineType = type;

	pLCamera = pCam;
	m_Trajectory.Init(steerParam);

	SetSideLineParam(sepDis,LSegExtendLength);
	SetDistLineParam(markStartDis,m_fMarkDeltaDis,m_iMarkDeltaNum);
	MallocGroupLineData();
	SetGroupColor(groupColor);
	CalGuideLineData();
	InitView();
}

void GlGuideLine::SetSWAUpdatePrecision(f32_t delta)
{
	m_fUpdateDeltaAngleDeg = delta;
}

void GlGuideLine::Update(f32_t swaDeg,bool bForceUpdate)
{
	if(bForceUpdate)
	{
		CalGuideLineData();
	}
	else if(fabs(swaDeg - m_fPrevSWADeg)>m_fUpdateDeltaAngleDeg)
	{
		m_Trajectory.SetVehicleSteeringAngle(swaDeg);
		CalGuideLineData();
		m_fPrevSWADeg = swaDeg;
	}
}

void GlGuideLine::ForceUpdate()
{
	CalGuideLineData();
}

void GlGuideLine::UpdateTrackWidth(float width)
{
	m_fTrackWidth = width;
	m_Trajectory.UpdateTrackWidth(width);
}


void GlGuideLine::SetGroupColor(color3* pColor)
{
	for(int i=0;i<m_iGroupNum;i++)
	{
		for(int j=0;j<3;j++)
			m_pGroups[i].color[j] = pColor[i][j];
	}
}

void GlGuideLine::FreeGMLineInfo()
{
	if(m_pSideLineInfo)
		free(m_pSideLineInfo);
	if(m_pDistLineInfo)
	{
		for(int i=0;i<m_iGroupNum;i++)
		{
			free(m_pDistLineInfo[i].dist);
		}
		free(m_pDistLineInfo);
	}
}

void GlGuideLine::MallocGroupLineData()
{
	m_pGroups = (linesData*)malloc(m_iGroupNum*sizeof(linesData));
	for(int i=0;i<m_iGroupNum;i++)
		MallocGroupLineData(i);
}

//void GlGuideLine::FreeGroupLineData()
//{
//	if(m_pGroups)
//	{
//		for(int i=0;i<m_iGroupNum;i++)
//			FreeGroupData(i);
//		free(m_pGroups);
//	}
//}

int GlGuideLine::CalSidePtNum(float startDis,float endDis,bool bTick)
{
	int outNum;
	float deltaDis = DIST_PER_POINT_CLOSE;
	float curDis = startDis;
	if(startDis>START_FAR_DIST)
		deltaDis = DIST_PER_POINT_FAR;
	if(startDis<START_FAR_DIST&&endDis>START_FAR_DIST)
	{
		outNum = 0;
		while(curDis<=endDis)
		{
			outNum++;
			curDis += deltaDis;
			if(fabs(curDis -START_FAR_DIST)<0.01)
				deltaDis = DIST_PER_POINT_FAR;
		}
		if(fabs(endDis - curDis)<deltaDis-0.01)
			outNum ++;
	}
	else
	{
		outNum = (endDis-startDis)/deltaDis+1;
		//curDis = startDis + outNum * deltaDis;
	}
	if(bTick)
		outNum++;

	return outNum;
}

void GlGuideLine::MallocGroupLineData(int index)
{
	linesData* curLineData = &m_pGroups[index];
	sideLineInfo sideLineInfo = m_pSideLineInfo[index];
	distLineInfo distLineInfo = m_pDistLineInfo[index];
	int totalLineNum = sideLineInfo.lineNum + distLineInfo.lineNum;
	curLineData->lineNums = totalLineNum;
//	curLineData->pLineBorderData = (float**)malloc(totalLineNum*sizeof(float*));
//	curLineData->pLineBorderIndex = (unsigned short**)malloc(totalLineNum*sizeof(unsigned short*));
//	curLineData->pLineBorderIndexNum = (unsigned short*)malloc(totalLineNum*sizeof(unsigned short*));
	curLineData->pLineData = (float**)malloc(totalLineNum*sizeof(float*));
	curLineData->pLinePtNums = (int*)malloc(totalLineNum*sizeof(int));

	MallocGroupSideLineData(index);
	MallocGroupDistLineData(index);
	MallocGroupBorderData(index);
}

void GlGuideLine::MallocGroupSideLineData(int index)
{
	sideLineInfo lineInfo = m_pSideLineInfo[index];
	linesData* curLineData = &m_pGroups[index];
	int sideLineNum = lineInfo.lineNum;
	int linePtNum = lineInfo.linePtNum;
//	unsigned short tmpPtElemNum;
//	unsigned short tmpIndexElemNum;
//	lineBorderOp borderOp;
//	borderOp.CalLine2DBorderPtNum(linePtNum,tmpPtElemNum,tmpIndexElemNum);
	for(int i=0;i<sideLineNum;i++)
	{
		curLineData->pLinePtNums[i] = linePtNum;
		curLineData->pLineData[i] = (float*)malloc(linePtNum*2*sizeof(float));
//		curLineData->pLineBorderIndexNum[i]= tmpIndexElemNum;
//		curLineData->pLineBorderData[i] = (float*)malloc(tmpPtElemNum*sizeof(float));
//		curLineData->pLineBorderIndex[i] = (unsigned short*)malloc(tmpIndexElemNum*sizeof(unsigned short));
	}
}

void GlGuideLine::MallocGroupDistLineData(int index)
{
	distLineInfo lineInfo = m_pDistLineInfo[index];
	linesData* curLineData = &m_pGroups[index];
	int distLineNum = lineInfo.lineNum;
	int linePtNum = lineInfo.linePtNum;
//	unsigned short tmpPtElemNum;
//	unsigned short tmpIndexElemNum;
//	lineBorderOp borderOp;
//	borderOp.CalLine2DBorderPtNum(linePtNum,tmpPtElemNum,tmpIndexElemNum);
	int curLineIndex=2;
	for(int i=0;i<distLineNum;i++)
	{
		curLineData->pLinePtNums[curLineIndex] = linePtNum;
		curLineData->pLineData[curLineIndex] = (float*)malloc(linePtNum*2*sizeof(float));
//		curLineData->pLineBorderIndexNum[curLineIndex]= tmpIndexElemNum;
//		curLineData->pLineBorderData[curLineIndex] = (float*)malloc(tmpPtElemNum*sizeof(float));
//		curLineData->pLineBorderIndex[curLineIndex] = (unsigned short*)malloc(tmpIndexElemNum*sizeof(unsigned short));
		curLineIndex++;
	}
}

void GlGuideLine::MallocGroupBorderData(int index)
{
	linesData* curLineData = &m_pGroups[index];
	int lineNum = curLineData->lineNums;
	curLineData->pLinePtElemStartNum = (unsigned short*)malloc(lineNum*sizeof(unsigned short));
	curLineData->pLineIndexElemStartNum = (unsigned short*)malloc(lineNum*sizeof(unsigned short));
	curLineData->pLineBorderStartIndex = (unsigned short*)malloc(lineNum*sizeof(unsigned short));

	unsigned short tmpPtElemNum;
	unsigned short tmpIndexElemNum;
	unsigned short totalPtElemNum=0;
	unsigned short totalIndexElemNum = 0;
	unsigned short curStartIndex = 0;
	lineBorderOp borderOp;
	for(int i=0;i<lineNum;i++)
	{
		curLineData->pLinePtElemStartNum[i] = totalPtElemNum;
		curLineData->pLineIndexElemStartNum[i] = totalIndexElemNum;
		curLineData->pLineBorderStartIndex[i] = curStartIndex;
		borderOp.CalLine2DBorderPtNum(curLineData->pLinePtNums[i],tmpPtElemNum,tmpIndexElemNum);
		totalPtElemNum += tmpPtElemNum;
		totalIndexElemNum += tmpIndexElemNum;
		curStartIndex += (tmpPtElemNum/PTELEMNUM);
	}
	curLineData->pBorderPtElemNum = totalPtElemNum;
	curLineData->pBorderIndexNum = totalIndexElemNum;
	curLineData->pBorderData = (float*)malloc(totalPtElemNum*sizeof(float));
	curLineData->pBorderIndex = (unsigned short*)malloc(totalIndexElemNum*sizeof(unsigned short));
}

void GlGuideLine::CalGuideLineData()
{
	for(int i=0;i<m_iGroupNum;i++)
		CalGroupValue(i);
}

void GlGuideLine::CalGroupValue(int index)
{
	//Cal2SideLinesPts(index);
	Cal2SideLinesPts(index);
	//CalDistLinePts(index);
	CalDistLinePts(index);
	CalLineBorder(index);
}


void GlGuideLine::Cal2SideLinesPts(int index)
{
	linesData* curLineData = &m_pGroups[index];
	sideLineInfo curInfo = m_pSideLineInfo[index];
	float startDis = curInfo.startDis;
	float endDis = curInfo.endDis;
	float deltaDis;

	deltaDis = DIST_PER_POINT_CLOSE;
	if(startDis>=START_FAR_DIST )
		deltaDis = DIST_PER_POINT_FAR;

	if(curInfo.lineNum == 2)
	{
		float* pLeftLine = curLineData->pLineData[0];
		float* pRightLine = curLineData->pLineData[1];
		int sideLinePtNum = curInfo.linePtNum;
		if(curInfo.bIsLSeg)
			sideLinePtNum = sideLinePtNum-1;
		int curElemIndex = 0;
		float curDis = startDis;
		if(startDis<START_FAR_DIST&&endDis>START_FAR_DIST)
		{
			for(int i=0;i<sideLinePtNum;i++)
			{
				Cal2SideLineScreenPos(curDis,&pLeftLine[curElemIndex],&pRightLine[curElemIndex]);
				curElemIndex += 2;
				curDis += deltaDis;
				if(curDis>endDis)
					curDis = endDis;
				if(curDis>=START_FAR_DIST)
					deltaDis = DIST_PER_POINT_FAR;
			}
		}
		else
		{
			for(int i=0;i<sideLinePtNum;i++)
			{
				Cal2SideLineScreenPos(curDis,&pLeftLine[curElemIndex],&pRightLine[curElemIndex]);
				curElemIndex += 2;
				curDis += deltaDis;
				if(curDis>endDis)
					curDis = endDis;
			}
		}

		if(curInfo.bIsLSeg)
		{
			float tickLength = curInfo.LSegExtendLength/**2.0/m_iScreenWidth*/;
			float leftx = pLeftLine[(sideLinePtNum-1)*2];
			float lefty = pLeftLine[(sideLinePtNum-1)*2+1];
			float rightx = pRightLine[(sideLinePtNum-1)*2];
			float righty = pRightLine[(sideLinePtNum-1)*2+1];
			float length = sqrt((leftx-rightx)*(leftx-rightx)+(lefty-righty)*(lefty-righty));
			float dirx = (rightx-leftx)/length;
			float diry = (righty-lefty)/length;
			pLeftLine[sideLinePtNum*2] = leftx+dirx*tickLength;
			pLeftLine[sideLinePtNum*2+1] = lefty + diry*tickLength;
			pRightLine[sideLinePtNum*2] = rightx - dirx*tickLength;
			pRightLine[sideLinePtNum*2+1] = righty - diry*tickLength;
		}
	}

}

void GlGuideLine::CalDistLinePts(int index)
{
	distLineInfo lineInfo = m_pDistLineInfo[index];
	int lineNum = lineInfo.lineNum;//lineNum = 0 or 5
	if(lineNum == 0)
		return;
//tbd:  dependency--->coordinate of linedata  vs m_pDistLineInfo. lineNum
	linesData* curLineData = &m_pGroups[index];
	for(int i=0;i<lineNum;i++)//5 distance mark lines ,20 vertex on each mark line
		CalDistLineScreenPos(lineInfo.dist[i],lineInfo.linePtNum,curLineData->pLineData[2+i]);//output to pLineData
}


void GlGuideLine::CalScreenPos(float x,float y,float& u,float& v)
{
	float tmpU,tmpV;
	if(m_bDistortCorrection)
		pLCamera->world2Pixel_noDistort(x,y,0.0,tmpU,tmpV);
	else
		pLCamera->world2Pixel(x,y,0.0,tmpU,tmpV);

	u = tmpU * m_iScreenWidth;
	v = (1-tmpV)*m_iScreenHeight;
}

void GlGuideLine::Get2SideLineWorldPos(float dist,float& leftx,float& lefty,float& rightx,float& righty)
{
	float halfWidth = m_fTrackWidth/2;
	int curSwa = m_Trajectory.GetVehicleSteerWheelAngle();
	if(eStaticGuideLine == m_GuideLineType||0 == curSwa)
	{
		leftx = -halfWidth;
		lefty = dist;
		rightx = halfWidth;
		righty = dist;
	}
	else
	{
		float invRadius = m_Trajectory.GetInvRadius();
		float theta = dist*invRadius;
		float turnCenterX = m_Trajectory.GetTurnCenterX();
		if(turnCenterX<0.0)
			theta = -theta;
		m_Trajectory.GetLeftPosition(theta,leftx,lefty);
		m_Trajectory.GetRightPosition(theta,rightx,righty);
	}
}

void GlGuideLine::Cal2SideLineScreenPos(float dist,float* left,float* right)
{
	float leftx,lefty,rightx,righty;
	Get2SideLineWorldPos(dist,leftx,lefty,rightx,righty);
	CalScreenPos(leftx,lefty,left[0],left[1]);
	CalScreenPos(rightx,righty,right[0],right[1]);
//	printf("dist=%f,leftx=%f,lefty=%f,rightx=%f,righty=%f\n",dist,leftx,lefty,rightx,righty);
//	printf("screenLeftx=%f,screenLefty=%f,screenRightx=%f,screenRighty=%f\n",left[0],left[1],right[0],right[1]);
}

void GlGuideLine::CalDistLineScreenPos(float dist,int ptNum,float* pData)
{
	float halfWidth = m_fTrackWidth/2;
	int curSwa = m_Trajectory.GetVehicleSteerWheelAngle();
	float leftx,lefty,rightx,righty;
	if(eStaticGuideLine == m_GuideLineType||0 == curSwa)
	{
		leftx = -halfWidth;
		lefty = dist;
		rightx = halfWidth;
		righty = dist;
	}
	else
	{
		float invRadius = m_Trajectory.GetInvRadius();
		float theta = dist*invRadius;
		float turnCenterX = m_Trajectory.GetTurnCenterX();
		if(turnCenterX<0.0)
			theta = -theta;
		m_Trajectory.GetLeftPosition(theta,leftx,lefty);
		m_Trajectory.GetRightPosition(theta,rightx,righty);
	}
	float curX=leftx,curY=lefty;
	float deltaX = (rightx - leftx)/(ptNum-1);
	float deltaY = (righty - lefty)/(ptNum-1);
	int elemIndex = 0;
	for(int i=0;i<ptNum;i++)
	{
		CalScreenPos(curX,curY,pData[elemIndex],pData[elemIndex+1]);
		elemIndex += 2;
		curX += deltaX;
		curY += deltaY;
	}
}

void GlGuideLine::CalLineBorder(int index)
{
	int lineNum = m_pGroups[index].lineNums;
	lineBorderOp borderOp;
	linesData* group = &m_pGroups[index];
	float** lineData = group->pLineData;
	int *linePtNum = group->pLinePtNums;
	unsigned short* lineStartIndex = group->pLineBorderStartIndex;
	unsigned short* linePtElemNum = group->pLinePtElemStartNum;
	unsigned short* lineIndexNum = group->pLineIndexElemStartNum;
	float* borderData = group->pBorderData;
	unsigned short* borderIndex = group->pBorderIndex;
	for(int i=0;i<lineNum;i++)
	{
//		borderOp.CalLine2DBorder(group->pLineData[i],group->pLinePtNums[i],m_fRenderLineWidth,0,group->pLineBorderData[i],group->pLineBorderIndex[i]);
		borderOp.CalLine2DBorder(lineData[i],linePtNum[i],m_iLinePixelWidth/*m_fRenderLineWidth*/,lineStartIndex[i],
				&borderData[linePtElemNum[i]],&borderIndex[lineIndexNum[i]]);

//		int ptNum = linePtNum[i];
//		float* data = lineData[i];
//		point2D pt(data[(ptNum-1)*2],data[(ptNum-1)*2+1]);
//		float* bData = &borderData[linePtElemNum[i]];
//		unsigned short curPtNum = group->pLinePtNums[i];
//		point2D bPt1(bData[(curPtNum-1)*8],bData[(curPtNum-1)*8+1]);
//		point2D bPt2(bData[(curPtNum-1)*8+4],bData[(curPtNum-1)*8+5]);
//		float dis1 = bPt1.Distance(pt);
//		float dis2 = bPt2.Distance(pt);
//		if((i>1)&&(dis1>m_iLinePixelWidth/2||dis2>m_iLinePixelWidth/2))
//		{
//			int swa = m_Trajectory.GetVehicleSteerWheelAngle();
//			printf("Error!: index = %d, i = %d, swa = %d, dis1=%d, dis2=%d,width = %d\n",index,i,swa,dis1,dis2,m_iLinePixelWidth);
//			printf("pt.x=%f,pt.y=%f,pt1.x=%f,pt1.y=%f,pt2.x=%d,pt2.y=%f\n",pt.x,pt.y,bPt1.x,bPt1.y,bPt2.x,bPt2.y);
//		}

	}
//	if(index==1)
//	{
//		int lineIndex = 5;
//		int tmpNum = linePtNum[lineIndex];
//		printf("lineData:\n");
//		for(int i=0;i<tmpNum;i++)
//		{
//			printf("x=%f,y=%f\n",lineData[5][i*2],lineData[5][i*2+1]);
//		}
//		int startPtElem = linePtElemNum[lineIndex];
//		printf("lineBorder:\n");
//		for(int i=0;i<tmpNum;i++)
//		{
//			printf("x1=%f,y1=%f,x2=%f,y2=%f\n",borderData[startPtElem+i*2*8],borderData[startPtElem+i*2*8+1],
//					borderData[startPtElem+(i*2+1)*8],borderData[startPtElem+(i*2+1)*8+1]);
//		}
//	}


//	unsigned short tmpDataNum;
//	unsigned short tmpIndexNum;
//	unsigned short totalDataNum = 0;
//	unsigned short totalIndexNum = 0;
////	int tmpNum = lineNum>2?3:2;
//	for(int i=0;i<lineNum;i++)
//	{
//		borderOp.CalLine2DBorderPtNum(group->pLinePtNums[i],tmpDataNum,tmpIndexNum);
//		totalDataNum += tmpDataNum;
//		totalIndexNum += tmpIndexNum;
//	}
////	if(m_pGroups[index].pTestLineBorderData)
////		free(m_pGroups[index].pTestLineBorderData);
////	if(m_pGroups[index].pTestLineBorderIndex)
////		free(m_pGroups[index].pTestLineBorderIndex);
//
//	m_pGroups[index].pTestIndexNum = totalIndexNum;
//	m_pGroups[index].pTestLineBorderData = (float*)malloc(totalDataNum*sizeof(float));
//	m_pGroups[index].pTestLineBorderIndex = (unsigned short*)malloc(totalIndexNum*sizeof(unsigned short));
//	unsigned short curIndex = 0;
//	unsigned short curPtElemNum=0;
//	unsigned short curIndexElemNum = 0;
//	for(int i=0;i<lineNum;i++)
//	{
////		printf("i = %d,curPtElemNum=%d,curIndexElemNum=%d,curIndex=%d\n",i,curPtElemNum,curIndexElemNum,curIndex);
//		borderOp.CalLine2DBorder(group->pLineData[i],group->pLinePtNums[i],m_fRenderLineWidth,
//				curIndex,&group->pTestLineBorderData[curPtElemNum],&group->pTestLineBorderIndex[curIndexElemNum]);
//		borderOp.CalLine2DBorderPtNum(group->pLinePtNums[i],tmpDataNum,tmpIndexNum);
//		curPtElemNum += tmpDataNum;
//		curIndexElemNum += tmpIndexNum;
//		curIndex += (tmpDataNum/4);
//	}

}

void GlGuideLine::SetDistLineParam(float startDis,float deltaDis,int MarklineNum)
{
	//actually only 2 group in all
	m_pDistLineInfo = (distLineInfo*)malloc(m_iGroupNum*sizeof(distLineInfo));
	if(m_pSideLineInfo[0].endDis>startDis)//m_pSideLineInfo[1].startDis = m_pSideLineInfo[0].endDis
	{
		fprintf(stderr,"info: L segment line override the Distance Mark line!!");
	}
	if(m_pSideLineInfo[1].endDis<startDis)
	{
		fprintf(stderr,"info: distance of the first Distance Mark line is out of Side line limit!!");
	}
	if(m_pSideLineInfo[1].endDis<(startDis+deltaDis*(MarklineNum-1)))
	{
		fprintf(stderr,"info: distance of the last Distance Mark line is out of Side line limit!!");
	}	

	distLineInfo* pLineInfo= &m_pDistLineInfo[0];
	//first group is "L segment line" in GM, begin at 0,end at 0.5M
	pLineInfo->lineNum = 0;//no mark line in first group 
	pLineInfo->linePtNum = DIST_LINE_PTNUM;
	pLineInfo->dist = NULL;

	pLineInfo = &m_pDistLineInfo[1];
	//second group is "Distance Mark for 1M" , begin at 1M,end at 5.0M	
	pLineInfo->lineNum = MarklineNum;
	pLineInfo->linePtNum = DIST_LINE_PTNUM;
	pLineInfo->dist = (float*)malloc(MarklineNum*sizeof(float));
	for(int j=0;j<MarklineNum;j++)
	{
		pLineInfo->dist[j] = startDis + j*deltaDis;
	}
}

void GlGuideLine::SetSideLineParam(float* sepDis,float* LSegExtendLength)
{
	m_pSideLineInfo = (sideLineInfo*)malloc(m_iGroupNum*sizeof(sideLineInfo));
	sideLineInfo* pLineInfo;
	for(int i=0;i<m_iGroupNum;i++)
	{
		pLineInfo = &m_pSideLineInfo[i];
		//set start and end distance;
		pLineInfo->startDis = sepDis[i];
		pLineInfo->endDis = sepDis[i+1];
		pLineInfo->lineNum = 2;
		pLineInfo->LSegExtendLength = LSegExtendLength[i]*m_iScreenWidth;
		if(fabs(LSegExtendLength[i])<0.0001)
		{
			pLineInfo->bIsLSeg = false;
			pLineInfo->linePtNum = CalSidePtNum(sepDis[i],sepDis[i+1],false);
		}
		else
		{
			pLineInfo->bIsLSeg = true;
			pLineInfo->linePtNum = CalSidePtNum(sepDis[i],sepDis[i+1],true);
		}
	}
}
