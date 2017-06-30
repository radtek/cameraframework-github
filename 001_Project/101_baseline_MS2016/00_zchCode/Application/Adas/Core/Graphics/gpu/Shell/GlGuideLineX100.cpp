#include "GlGuideLineX100.h"
#include "lineBorderOp.h"

#define GROUPSTEP 4
#define POINTSTEP 2

#define LEFTINDEX 0
#define RIGHTINDEX 1

GlGuideLineX100::GlGuideLineX100()
{
	m_iScreenLeftPos = NULL;
	m_iScreenRightPos = NULL;
	m_pSideLineInfo = NULL;
}

GlGuideLineX100::~GlGuideLineX100()
{
	ReleaseScreenPos();
	ReleaseSideLineData();
}

void GlGuideLineX100::InitTest()
{
	InitView();
	SetDefaultValue();
	MallocGroupLineData();
	CalGuideLineData();
	SetGroupColor();
}

void GlGuideLineX100::InitTest_test(rvs_GuideLineCfg_t* pConfig)
{
	InitView();
	m_iGroupNum = pConfig->groupNum;
	m_iLineWidth = 10;
	m_iLinePixelWidth = 10;
//	printf("MallocResources begin!\n");
	MallocResources();
//	printf("MallocResources end!\n");

	SetScreenPos(pConfig->m_iLeftPos, pConfig->m_iRightPos);

//	printf("SetScreenPos end!\n");
	SetSideLineParam();
//	printf("SetSideLineParam end!\n");
	MallocGroupLineData();
	SetGroupColor();
//	printf("MallocGroupLineData end!\n");
	CalGuideLineData();
//	printf("CalGuideLineData end!\n");
}

void GlGuideLineX100::MallocResources()
{
	MallocScreenPos();
	MallocSideLineInfo();
//	MallocGroupLineData();
}

void GlGuideLineX100::ReleaseResources()
{
	ReleaseScreenPos();
	ReleaseSideLineData();
	FreeLinesData();
}

void GlGuideLineX100::SetWindowParam(int winWidth,int winHeight)
{
	m_iScreenWidth = winWidth;
	m_iScreenHeight = winHeight;
}

void GlGuideLineX100::SetGroupColor()
{
//	m_pGroups[0].color[0] = 1.0;
//	m_pGroups[0].color[1] = 1.0;
//	m_pGroups[0].color[2] = 0.0;
//
//	m_pGroups[1].color[0] = 1.0;
//	m_pGroups[1].color[1] = 0.6;
//	m_pGroups[1].color[2] = 0.0705;
//
//	m_pGroups[2].color[0] = 1.0;
//	m_pGroups[2].color[1] = 0.0;
//	m_pGroups[2].color[2] = 0.0;

	for(int i=0;i<=3;i++)
	{
		m_pGroups[i].color[0] = 1.0;
		m_pGroups[i].color[1] = 1.0;
		m_pGroups[i].color[2] = 0.0;
	}

	m_pGroups[4].color[0] = 1.0;
	m_pGroups[4].color[1] = 0.6;
	m_pGroups[4].color[2] = 0.0705;

	m_pGroups[5].color[0] = 1.0;
	m_pGroups[5].color[1] = 0.0;
	m_pGroups[5].color[2] = 0.0;

}

void GlGuideLineX100::SetDefaultValue()
{
	m_iGroupNum = 3;
	m_iLineWidth = 10;
	m_iLinePixelWidth = 10;
	MallocScreenPos();

	m_iScreenLeftPos[0][0] = 300;
	m_iScreenLeftPos[0][1] = m_iScreenHeight -1 - 60;

	m_iScreenLeftPos[0][2] = 300-50;
	m_iScreenLeftPos[0][3] = m_iScreenHeight -1-(60+50);

//	m_iScreenLeftPos[0][0] = 27;
//	m_iScreenLeftPos[0][1] = 420;
//
//	m_iScreenLeftPos[0][2] = 136;//300-50;
//	m_iScreenLeftPos[0][3] = 299;//m_iScreenHeight -1-(60+50);

	m_iScreenRightPos[0][0] = 420;
	m_iScreenRightPos[0][1] = m_iScreenHeight -1-60;

	m_iScreenRightPos[0][2] = 420+50;
	m_iScreenRightPos[0][3] = m_iScreenHeight -1-(60+50);

	for(int i=1;i<m_iGroupNum;i++)
	{
		m_iScreenLeftPos[i][0] = m_iScreenLeftPos[i-1][2] - 30;
		m_iScreenLeftPos[i][1] = m_iScreenLeftPos[i-1][3] - 30;

		m_iScreenLeftPos[i][2] = m_iScreenLeftPos[i][0] - 50;
		m_iScreenLeftPos[i][3] = m_iScreenLeftPos[i][1] - 50;

		m_iScreenRightPos[i][0] = m_iScreenRightPos[i-1][2] + 30;
		m_iScreenRightPos[i][1] = m_iScreenRightPos[i-1][3] - 30;

		m_iScreenRightPos[i][2] = m_iScreenRightPos[i][0] + 50;
		m_iScreenRightPos[i][3] = m_iScreenRightPos[i][1] - 50;
	}

	MallocSideLineInfo();
	SetSideLineParam();
}

void GlGuideLineX100::SetScreenDefaultValue()
{
	m_iScreenLeftPos[0][0] = 300;
	m_iScreenLeftPos[0][1] = m_iScreenHeight -1-60;

	m_iScreenLeftPos[0][2] = 300-50;
	m_iScreenLeftPos[0][3] = m_iScreenHeight -1-(60+50);

	m_iScreenRightPos[0][0] = 420;
	m_iScreenRightPos[0][1] = m_iScreenHeight -1- 60;

	m_iScreenRightPos[0][2] = 420+50;
	m_iScreenRightPos[0][3] = m_iScreenHeight -1- (60+50);

	for(int i=1;i<m_iGroupNum;i++)
	{
		m_iScreenLeftPos[i][0] = m_iScreenLeftPos[i-1][2] - 30;
		m_iScreenLeftPos[i][1] = m_iScreenLeftPos[i-1][3] - 30;

		m_iScreenLeftPos[i][2] = m_iScreenLeftPos[i][0] - 50;
		m_iScreenLeftPos[i][3] = m_iScreenLeftPos[i][1] - 50;

		m_iScreenRightPos[i][0] = m_iScreenRightPos[i-1][2] + 30;
		m_iScreenRightPos[i][1] = m_iScreenRightPos[i-1][3] - 30;

		m_iScreenRightPos[i][2] = m_iScreenRightPos[i][0] + 50;
		m_iScreenRightPos[i][3] = m_iScreenRightPos[i][1] - 50;
	}
}

void GlGuideLineX100::SetScreenPos(int** leftPos, int** rightPos)
{
	for(int i=0;i<m_iGroupNum;i++)
	{
		for(int j=0;j<GROUPSTEP;j++)
		{
			m_iScreenLeftPos[i][j] = leftPos[i][j];
			m_iScreenRightPos[i][j] = rightPos[i][j];
		}
		m_iScreenLeftPos[i][1] = m_iScreenHeight-1-m_iScreenLeftPos[i][1];
		m_iScreenLeftPos[i][3] = m_iScreenHeight-1-m_iScreenLeftPos[i][3];
		m_iScreenRightPos[i][1] = m_iScreenHeight-1-m_iScreenRightPos[i][1];
		m_iScreenRightPos[i][3] = m_iScreenHeight-1-m_iScreenRightPos[i][3];

	}
}

void GlGuideLineX100::MallocScreenPos()
{
	if(m_iGroupNum == 0)
		return;

	m_iScreenLeftPos = (int**)malloc(m_iGroupNum*sizeof(int*));
	m_iScreenRightPos = (int**)malloc(m_iGroupNum*sizeof(int*));
	for(int i=0;i<m_iGroupNum;i++)
	{
		m_iScreenLeftPos[i] = (int*)malloc(GROUPSTEP*sizeof(int));
		m_iScreenRightPos[i] = (int*)malloc(GROUPSTEP*sizeof(int));
	}

}

void GlGuideLineX100::ReleaseScreenPos()
{
	if(m_iScreenLeftPos)
	{
		for(int i=0;i<m_iGroupNum;i++)
			free(m_iScreenLeftPos[i]);
		free(m_iScreenLeftPos);
	}

	if(m_iScreenRightPos)
	{
		for(int i=0;i<m_iGroupNum;i++)
			free(m_iScreenRightPos[i]);
		free(m_iScreenRightPos);
	}
}

//void GlGuideLineX100::ReSetScreenPos(int groupNum,int** leftPos, int** rightPos)
//{
//	if(groupNum == 0)
//		return;
//	if(groupNum != m_iGroupNum)
//	{
//		if(m_iScreenLeftPos)
//		{
//			for(int i=0;i<m_iGroupNum;i++)
//				free(m_iScreenLeftPos[i]);
//			free(m_iScreenLeftPos);
//		}
//
//		if(m_iScreenRightPos)
//		{
//			for(int i=0;i<m_iGroupNum;i++)
//				free(m_iScreenRightPos[i]);
//			free(m_iScreenRightPos);
//		}
//
//		m_iScreenLeftPos = (int**)malloc(groupNum*sizeof(int*));
//		m_iScreenRightPos = (int**)malloc(groupNum*sizeof(int*));
//		for(int i=0;i<groupNum;i++)
//		{
//			m_iScreenLeftPos[i] = (int*)malloc(GROUPSTEP*sizeof(int));
//			m_iScreenRightPos[i] = (int*)malloc(GROUPSTEP*sizeof(int));
//		}
//	}
//
//	for(int i=0;i<groupNum;i++)
//	{
//		for(int j=0;j<GROUPSTEP;j++)
//		{
//			m_iScreenLeftPos[i][j] = leftPos[i][j];
//			m_iScreenRightPos[i][j] = rightPos[i][j];
//		}
//	}
//}

//void ReleaseScreenPos();

void GlGuideLineX100::MallocSideLineInfo()
{
	if(m_pSideLineInfo)
	{
		free(m_pSideLineInfo);
	}
	m_pSideLineInfo = (sideLineInfo_x100*)malloc(m_iGroupNum*sizeof(sideLineInfo_x100));
}

void GlGuideLineX100::SetSideLineParam()
{
	sideLineInfo_x100* pLineInfo;
	for(int i=0;i<m_iGroupNum;i++)
	{
		pLineInfo = &m_pSideLineInfo[i];
		//set start and end distance;
		pLineInfo->startPos[0] = m_iScreenLeftPos[i][0];
		pLineInfo->startPos[1] = m_iScreenLeftPos[i][1];
		pLineInfo->startPos[2] = m_iScreenRightPos[i][0];
		pLineInfo->startPos[3] = m_iScreenRightPos[i][1];

		pLineInfo->endPos[0] = m_iScreenLeftPos[i][2];
		pLineInfo->endPos[1] = m_iScreenLeftPos[i][3];
		pLineInfo->endPos[2] = m_iScreenRightPos[i][2];
		pLineInfo->endPos[3] = m_iScreenRightPos[i][3];

		pLineInfo->lineNum = 2;
		pLineInfo->LSegExtendLength = 20;//LSegExtendLength[i]*m_iScreenWidth;
		pLineInfo->bIsLSeg = true;
		pLineInfo->linePtNum = 3;
	}

	for(int i=0;i<3;i++)
	{
		pLineInfo = &m_pSideLineInfo[i];
		pLineInfo->LSegExtendLength = 0;//LSegExtendLength[i]*m_iScreenWidth;
		pLineInfo->bIsLSeg = false;
		pLineInfo->linePtNum = 2;
	}
}

void GlGuideLineX100::UpdateSideLineParam(int groupId)
{
	sideLineInfo_x100* pLineInfo = &m_pSideLineInfo[groupId];
	//set start and end distance;
	pLineInfo->startPos[0] = m_iScreenLeftPos[groupId][0];
	pLineInfo->startPos[1] = m_iScreenLeftPos[groupId][1];
	pLineInfo->startPos[2] = m_iScreenRightPos[groupId][0];
	pLineInfo->startPos[3] = m_iScreenRightPos[groupId][1];

	pLineInfo->endPos[0] = m_iScreenLeftPos[groupId][2];
	pLineInfo->endPos[1] = m_iScreenLeftPos[groupId][3];
	pLineInfo->endPos[2] = m_iScreenRightPos[groupId][2];
	pLineInfo->endPos[3] = m_iScreenRightPos[groupId][3];
}

void GlGuideLineX100::ReleaseSideLineData()
{
	if(m_pSideLineInfo)
	{
		free(m_pSideLineInfo);
		m_pSideLineInfo = NULL;
	}
}

void GlGuideLineX100::MallocGroupLineData()
{
	m_pGroups = (linesData*)malloc(m_iGroupNum*sizeof(linesData));
	for(int i=0;i<m_iGroupNum;i++)
	{
		MallocGroupLineData(i);
	}
}

//void GlGuideLineX100::ReMallocGroupLineData(int groupNum)
//{
//	if(m_iGroupNum == groupNum || groupNum==0)
//		return;
//	FreeLinesData();
//	m_iGroupNum = groupNum;
//
//	m_pGroups = (linesData*)malloc(groupNum*sizeof(linesData));
//	for(int i=0;i<groupNum;i++)
//	{
//		MallocGroupLineData(i);
//	}
//}

void GlGuideLineX100::MallocGroupLineData(int index)
{
	linesData* curLineData = &m_pGroups[index];
	sideLineInfo_x100 sideLineInfo = m_pSideLineInfo[index];
	int totalLineNum = sideLineInfo.lineNum ;
	curLineData->lineNums = totalLineNum;
	curLineData->pLineData = (float**)malloc(totalLineNum*sizeof(float*));
	curLineData->pLinePtNums = (int*)malloc(totalLineNum*sizeof(int));

	MallocGroupSideLineData(index);
	MallocGroupBorderData(index);
}
void GlGuideLineX100::MallocGroupSideLineData(int index)
{
	sideLineInfo_x100 lineInfo = m_pSideLineInfo[index];
	linesData* curLineData = &m_pGroups[index];
	int sideLineNum = lineInfo.lineNum;
	int linePtNum = lineInfo.linePtNum;
	for(int i=0;i<sideLineNum;i++)
	{
		curLineData->pLinePtNums[i] = linePtNum;
		if(linePtNum == 3 && lineInfo.bIsLSeg)
			curLineData->pLineData[i] = (float*)malloc((linePtNum)*2*sizeof(float));
		else
			curLineData->pLineData[i] = (float*)malloc(linePtNum*2*sizeof(float));
	}
}
void GlGuideLineX100::MallocGroupBorderData(int index)
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
//	lineBorderOp borderOp;
	for(int i=0;i<lineNum;i++)
	{
		curLineData->pLinePtElemStartNum[i] = totalPtElemNum;
		curLineData->pLineIndexElemStartNum[i] = totalIndexElemNum;
		curLineData->pLineBorderStartIndex[i] = curStartIndex;
//		borderOp.CalLine2DBorderPtNum(curLineData->pLinePtNums[i],tmpPtElemNum,tmpIndexElemNum);
		tmpPtElemNum = curLineData->pLinePtNums[i]*2*PTELEMNUM;
		tmpIndexElemNum = (curLineData->pLinePtNums[i]-1)*6;
		totalPtElemNum += tmpPtElemNum;
		totalIndexElemNum += tmpIndexElemNum;
		curStartIndex += (tmpPtElemNum/PTELEMNUM);
	}
	curLineData->pBorderPtElemNum = totalPtElemNum;
	curLineData->pBorderIndexNum = totalIndexElemNum;
	curLineData->pBorderData = (float*)malloc(totalPtElemNum*sizeof(float));
	curLineData->pBorderIndex = (unsigned short*)malloc(totalIndexElemNum*sizeof(unsigned short));
//	printf("curLineData->pBorderPtElemNum=%d,curLineData->pBorderIndexNum=%d\n",curLineData->pBorderPtElemNum,curLineData->pBorderIndexNum);
}

void GlGuideLineX100::CalGuideLineData()
{
	for(int i=0;i<m_iGroupNum;i++)
		CalGroupValue(i);
}

void GlGuideLineX100::CalGroupValue(int index)
{
//	printf("Cal2SideLinesPts %d\n",index);
	Cal2SideLinesPts(index);
//	printf("CalLineBorder %d\n",index);
	CalLineBorder(index);
//	printf("CalLineBorder %d end!\n",index);
}

void GlGuideLineX100::CalLineBorder(int index)
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
		borderOp.CalLine2DBorder(lineData[i],linePtNum[i],m_iLinePixelWidth,lineStartIndex[i],
				&borderData[linePtElemNum[i]],&borderIndex[lineIndexNum[i]]);

//		printf("[%f,%f],[%f,%f],[%f,%f],[%f,%f]\n",lineData[i][0],lineData[i][1],lineData[i][2],lineData[i][3],lineData[i][4],lineData[i][5]);
//		for(int k=0;k<linePtNum[i]*2;k++)
//		{
//			printf("[%f,%f]\t",borderData[linePtElemNum[i]+k*4],lineData[i][linePtElemNum[i]+k*4+1]);
//		}
//		printf("\n");
	}
}

void GlGuideLineX100::Cal2SideLinesPts(int index)
{
	linesData* curLineData = &m_pGroups[index];
	sideLineInfo_x100 curInfo = m_pSideLineInfo[index];

	if(curInfo.bIsLSeg)
	{
		if(curInfo.lineNum == 2)
		{
			float* pLeftLine = curLineData->pLineData[0];
			float* pRightLine = curLineData->pLineData[1];
	//		int sideLinePtNum = curInfo.linePtNum;
	//		printf("pLeftLine=%p,pRightLine=%p\n",pLeftLine,pRightLine);

			pLeftLine[2] =curInfo.startPos[0];
			pLeftLine[3] =curInfo.startPos[1];
			pLeftLine[4] = curInfo.endPos[0];
			pLeftLine[5] = curInfo.endPos[1];

			pRightLine[2] =curInfo.startPos[2];
			pRightLine[3] =curInfo.startPos[3];
			pRightLine[4] = curInfo.endPos[2];
			pRightLine[5] = curInfo.endPos[3];

			if(curInfo.bIsLSeg)
			{
				float tickLength = curInfo.LSegExtendLength/**2.0/m_iScreenWidth*/;
				float leftx = pLeftLine[2];
				float lefty = pLeftLine[3];
				float rightx = pRightLine[2];
				float righty = pRightLine[3];
				float length = sqrt((leftx-rightx)*(leftx-rightx)+(lefty-righty)*(lefty-righty));
				float dirx = (rightx-leftx)/length;
				float diry = (righty-lefty)/length;
				pLeftLine[0] = leftx+dirx*tickLength;
				pLeftLine[1] = lefty + diry*tickLength;
				pRightLine[0] = rightx - dirx*tickLength;
				pRightLine[1] = righty - diry*tickLength;
			}
	//		printf("line0: [%f,%f],[%f,%f],[%f,%f]\n",pLeftLine[0],pLeftLine[1],pLeftLine[2],pLeftLine[3],pLeftLine[4],pLeftLine[5]);
	//		printf("line1: [%f,%f],[%f,%f],[%f,%f]\n",pRightLine[0],pRightLine[1],pRightLine[2],pRightLine[3],pRightLine[4],pRightLine[5]);
		}
	}
	else
	{
		float* pLeftLine = curLineData->pLineData[0];
		float* pRightLine = curLineData->pLineData[1];

		pLeftLine[0] =curInfo.startPos[0];
		pLeftLine[1] =curInfo.startPos[1];
		pLeftLine[2] = curInfo.endPos[0];
		pLeftLine[3] = curInfo.endPos[1];

		pRightLine[0] =curInfo.startPos[2];
		pRightLine[1] =curInfo.startPos[3];
		pRightLine[2] = curInfo.endPos[2];
		pRightLine[3] = curInfo.endPos[3];
	}

}

void GlGuideLineX100::UpdateGuideLineInfo_Left(int groupId, int leftStartPosX,int leftStartPosY, int leftEndPosX, int leftEndPosY)
{
	if(groupId >= m_iGroupNum)
	{
		return;
	}

	m_iScreenLeftPos[groupId][0] = leftStartPosX;
	m_iScreenLeftPos[groupId][1] = m_iScreenHeight-1-leftStartPosY;

	m_iScreenLeftPos[groupId][2] = leftEndPosX;
	m_iScreenLeftPos[groupId][3] = m_iScreenHeight-1-leftEndPosY;

	UpdateSideLineParam(groupId);

	CalGroupValue(groupId);
}

void GlGuideLineX100::UpdateGuideLineInfo_Right(int groupId, int rightStartPosX,int rightStartPosY, int rightEndPosX, int rightEndPosY)
{
	if(groupId >= m_iGroupNum)
	{
		return;
	}

	m_iScreenRightPos[groupId][0] = rightStartPosX;
	m_iScreenRightPos[groupId][1] = m_iScreenHeight-1-rightStartPosY;

	m_iScreenRightPos[groupId][2] = rightEndPosX;
	m_iScreenRightPos[groupId][3] = m_iScreenHeight-1-rightEndPosY;

	UpdateSideLineParam(groupId);

	CalGroupValue(groupId);
}

void GlGuideLineX100::UpdateGuideLineInfo(int groupId, int* leftPos, int* rightPos)
{
	if(groupId >= m_iGroupNum)
	{
		return;
	}

	for(int i=0;i<4;i++)
	{
		m_iScreenLeftPos[groupId][i] = leftPos[i];
		m_iScreenRightPos[groupId][i] = rightPos[i];
	}
	m_iScreenLeftPos[groupId][1] = m_iScreenHeight-1-m_iScreenLeftPos[groupId][1];
	m_iScreenLeftPos[groupId][3] = m_iScreenHeight-1-m_iScreenLeftPos[groupId][3];
	m_iScreenRightPos[groupId][1] = m_iScreenHeight-1-m_iScreenRightPos[groupId][1];
	m_iScreenRightPos[groupId][3] = m_iScreenHeight-1-m_iScreenRightPos[groupId][3];

	UpdateSideLineParam(groupId);
	CalGroupValue(groupId);
}

void GlGuideLineX100::UpdateGuideLineInfo(int groupNum,int** leftPos, int** rightPos)
{
	if(groupNum == m_iGroupNum)
	{
		for(int i=0;i<m_iGroupNum;i++)
		{
			UpdateGuideLineInfo(i,leftPos[i],rightPos[i]);
		}
	}
	else{
		ReleaseResources();
		m_iGroupNum = groupNum;
		MallocResources();
		SetScreenPos(leftPos,rightPos);
		SetSideLineParam();
		MallocGroupLineData();
		CalGuideLineData();
	}
}
