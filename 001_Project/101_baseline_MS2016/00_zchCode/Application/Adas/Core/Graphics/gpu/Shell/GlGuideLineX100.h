#ifndef __GL_GUIDELINE_X100_H__
#define __GL_GUIDELINE_X100_H__

#include "GlGuideLine.h"
#include "RVSGuideLineDefine.h"

typedef struct _sideLineInfo_x100
{
	int lineNum;    //side line num is fix to 2
	int linePtNum; //num of veterx on a segment of the side line  every part of the side line has more than 3 points
	int startPos[4];  //
	int endPos[4];
	bool bIsLSeg;   //if this part  of line is the L segment
	int LSegExtendLength; //the inside extend  length of L segment
}sideLineInfo_x100;


class GlGuideLineX100 : public GlLineGroup{
public:
	GlGuideLineX100();
	~GlGuideLineX100();

	void  InitTest();

	void InitTest_test(rvs_GuideLineCfg_t* pConfig);

	void UpdateGuideLineInfo(int groupNum,int** leftPos, int** rightPos);

	void UpdateGuideLineInfo_Left(int groupId, int leftStartPosX,int leftStartPosY, int leftEndPosX, int leftEndPosY);
	void UpdateGuideLineInfo_Right(int groupId, int rightStartPosX,int rightStartPosY, int rightEndPosX, int rightEndPosY);
	void UpdateGuideLineInfo(int groupId, int* leftPos, int* rightPos);

	void CalGuideLineData();

	void SetGroupColor();

	void SetWindowParam(int winWidth,int winHeight);

private:

	void MallocResources();
	void ReleaseResources();

	void MallocScreenPos();
	void ReleaseScreenPos();

	void SetScreenPos(int** leftPos, int** rightPos);
//	void ReSetScreenPos(int groupNum,int** leftPos, int** rightPos);
	void SetDefaultValue();
	void SetScreenDefaultValue();

	void MallocSideLineInfo();
	void ReleaseSideLineData();
	void SetSideLineParam(); //according to the screen position defined
	void UpdateSideLineParam(int groupId);
	/*
	* malloc m_pGroups space(according to m_pSideLineInfo and m_pDistLineInfo)
	*/
	void MallocGroupLineData();
//	void ReMallocGroupLineData(int groupNum);

	void MallocGroupLineData(int index);
	void MallocGroupSideLineData(int index);
	void MallocGroupBorderData(int index);


	void CalGroupValue(int index);
	void CalLineBorder(int index);
	void Cal2SideLinesPts(int index);

private:
//	int m_iGroupNum;
	int** m_iScreenLeftPos;
	int** m_iScreenRightPos;
	int m_iLineWidth;

//	int* m_iRenderPoints;
	sideLineInfo_x100* m_pSideLineInfo;
};

#endif
