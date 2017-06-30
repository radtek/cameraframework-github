/*
 * GlGuideLine_new.h
 *
 *  Created on: 2012-6-8
 *      Author: QiLiu
 */

#ifndef GLGUIDELINE_NEW_H_
#define GLGUIDELINE_NEW_H_

#include "GlShell.h"
#include "LCommon.h"
#include "lineBorderOp.h"
#include "trajectory.h"
//#include "RVSDefine.h"
#include "GlLineGroup.h"

#define DIST_PER_POINT_CLOSE	0.25
#define DIST_PER_POINT_FAR		0.5
#define	START_FAR_DIST			2.0		// distance per point is doubled at this range---desided by camera?
#define DIST_LINE_PTNUM         20

//define the middle line of two side lines 
typedef struct _sideLineInfo
{
	int lineNum;    //side line num is fix to 2
	int linePtNum; //num of veterx on a segment of the side line  every part of the side line has more than 3 points 
	float startDis;  
	float endDis;
	bool bIsLSeg;   //if this part  of line is the L segment
	float LSegExtendLength; //the inside extend  length of L segment
}sideLineInfo;

//define the Mark line between two side lines
typedef struct _distLineInfo
{
	int lineNum;  //num of lines in a group ,which mark the distance set by app
	int linePtNum;//fix to 20 vertex on a mark line between two side lines
	float* dist;  //coordinater of line which mark the" x m" length in the realworld,---depends on the startDis/endDis of sideline and lineNum of disLine
	//float* lineLength;
}distLineInfo;


typedef enum{
	eStaticGuideLine,
	eDynamicGuideLine,
} GuideLineType;

class GlGuideLine : public GlLineGroup
{
public:
	GlGuideLine();
	~GlGuideLine();


	void SetWindowParam(int winWidth,int winHeight);

	void InitLineParam(int groupNum,float* sepDis,float* tickLength,color3* groupColor,float markStartDis,
		float markDeltaDis,int markNum,float trackWidth,int lineWidth,LCamera* pCam,trajectory pTraj,
		GuideLineType type=eStaticGuideLine,bool bUnDistort=false);

	void InitLineParam(int groupNum,float* sepDis,float* tickLength,color3* groupColor,float markStartDis,rvs_steer_params steerParam,
			int lineWidth,LCamera* pCam,GuideLineType type=eStaticGuideLine,bool bUnDistort=false);

	void SetSWAUpdatePrecision(f32_t delta);
	/*
	 * add trajectory parameter initialization
	 */
	void SetSteerParam();
	void Update(f32_t swaDeg,bool bForceUpdate = false);
	void ForceUpdate();

	void UpdateTrackWidth(float width);

	void SetLineUndistort(bool bUnDistort){m_bDistortCorrection = bUnDistort;}

private:
	/*
	* @ brief: malloc and set m_pDistLineInfo
	*/
	void SetDistLineParam(float startDis,float deltaDis,int lineNum);

	/*
	*  @ brief: malloc and set m_pSideLineInfo
	*  @ sepDis: distance that separate groups, groupNum+1 elements,first element is the start distance
	*  @ tickLength: the length of tick in group ends, if 0, no tick. groupNum elements
	*/
	void SetSideLineParam(float* sepDis,float* tickLength);

	/*
	* malloc m_pGroups space(according to m_pSideLineInfo and m_pDistLineInfo)
	*/
	void MallocGroupLineData();
	/*
	* malloc and set m_pSideLineInfo and m_pDistLineInfo(according to the input data)
	*/
	//void InitGMLineInfo(float* groupSep,bool* bGroupTick,float* tickLength);
	void FreeGMLineInfo();

	//can be find in lineGroup
//	void FreeGroupLineData();


	void SetGroupColor(color3* pColor);
	void CalGuideLineData();
	//void UpdateGuideLineData();

private:
	/*
	 *  malloc spaces for linesData,(according to m_pSideLineInfo and m_pDistLineInfo)
	 */
	void MallocGroupLineData(int index);
	void MallocGroupSideLineData(int index);
	void MallocGroupDistLineData(int index);
	void MallocGroupBorderData(int index);

	void CalGroupValue(int index);
	void Cal2SideLinesPts(int index);
	void CalDistLinePts(int index);

private:
    /*
     * depend on the project demands
     */
	void Cal2SideLineScreenPos(float dist,float* left,float* right);
	void CalDistLineScreenPos(float dist,int ptNum,float* pData);
	void Get2SideLineWorldPos(float dist,float& leftx,float& lefty,float& rightx,float& righty);

private:
	/*
	 * basic algorithm
	 */
	void CalScreenPos(float x,float y,float& u,float& v);
	void CalLineBorder(int index);
	int CalSidePtNum(float startDis,float endDis,bool bTick);

private:
	LCamera* pLCamera;
	trajectory m_Trajectory;
	bool m_bDistortCorrection;
	GuideLineType m_GuideLineType;

	//float m_fSWADeg;
	f32_t m_fPrevSWADeg;//steering wheel angle
	f32_t m_fUpdateDeltaAngleDeg;

	sideLineInfo* m_pSideLineInfo;   //two type of line in GM:0.5red  and 1.0orange, and side line has right and left ,save midline as info
	distLineInfo* m_pDistLineInfo;

	//render info
//	float m_fRenderLineWidth;

	float m_fMarkDeltaDis;
	int m_iMarkDeltaNum;
	float m_fTrackWidth;  //define the width of the distance line 
};


#endif /* GLGUIDELINE_NEW_H_ */
