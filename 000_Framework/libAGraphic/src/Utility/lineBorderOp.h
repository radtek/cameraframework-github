#ifndef __LINEBORDEROP_H__
#define __LINEBORDEROP_H__

#define PTELEMNUM 4
#define INPUTELEMENTNUM 2

#include "line2D.h"
class lineBorderOp
{
public:
	void CalLine2DBorder(float* input,int ptNum,float width,unsigned short startIndex,float* outpt,/*unsigned int* outIndex*/unsigned short* outIndex);
	void CalLine2DBorderPtNum(int ptNum,unsigned short& outPtElemNum/*unsigned int& outPtElemNum*/,unsigned short& outIndexNum/*unsigned int& outIndexNum*/);
	void CalLine2DBorder_Loop(float* input,int ptNum,float width,unsigned short startIndex,float* outpt,unsigned short* outIndex);
	void CalLine2DBorderPtNum_Loop(int ptNum,unsigned short& outPtElemNum,unsigned short& outIndexElemNum);
private:
	void CalStartPt2DBorderPts(const point2D& pt,const point2D& nextPt,float width,float* out);
	void CalMidPt2DBorderPts(const point2D& pt,const point2D& prevPt,const point2D& afterPt,float width,point2D& out1,point2D& out2);
	void CalMidPt2DBorderPts(const point2D& pt,const point2D& prevPt,const point2D& afterPt,float width,
							unsigned short startIndex,float* out,unsigned short* outIndex/*unsigned int* outIndex*/);
	void CalEndPt2DBorderPts(const point2D& pt,const point2D& prevPt,float width,float* out,unsigned short startIndex,
							/*unsigned int* outIndex*/unsigned short* outIndex);

	void Cal2DPtsAlongDir(const point2D& pt,const vector2D& dir,float width,point2D& out1,point2D& out2);

	void SetGen2DPoint(const point2D& pt,float texCoordX,float texCoordY,float* pOut);
	void SetGen2DPoints(point2D* pt, float coord1,float coord2,float* pOut);
	void SetGenTriangleIndex(unsigned short startIndex,unsigned short* pIndex/*unsigned int* pIndex*/);
};

#endif
