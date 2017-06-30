#include "lineBorderOp.h"


void lineBorderOp::CalLine2DBorder(float* input,int ptNum,float width,unsigned short startIndex,float* outpt,unsigned short* outIndex/*unsigned int* outIndex*/)
{
	point2D pt1(input[0],input[1]);//0,1,2,3
	point2D pt2(input[INPUTELEMENTNUM],input[INPUTELEMENTNUM+1]);//4,5,6,7
	point2D pt3;
	CalStartPt2DBorderPts(pt1,pt2,width,outpt);

	int ptElementNum = 2*PTELEMNUM;
	int indexElementNum = 0;
	for(int i=1;i<ptNum-1;i++)
	{
		pt3.SetData(input[(i+1)*INPUTELEMENTNUM],input[(i+1)*INPUTELEMENTNUM+1]);
		CalMidPt2DBorderPts(pt2,pt1,pt3,width,startIndex,&outpt[ptElementNum],&outIndex[indexElementNum]);
		ptElementNum += 2*PTELEMNUM;
		indexElementNum += 6;
		startIndex += 2;
		pt1 = pt2;
		pt2 = pt3;
	}
	CalEndPt2DBorderPts(pt2,pt1,width,&outpt[ptElementNum],startIndex,&outIndex[indexElementNum]);
}
//ptnum-->vertex num on a segment of the guide line
void lineBorderOp::CalLine2DBorderPtNum(int ptNum,unsigned short& outPtElemNum/*unsigned int& outPtElemNum*/,unsigned short& outIndexNum/*unsigned int& outIndexNum*/)
{
	if(ptNum == 0)
	{
		outPtElemNum = 0;
		outIndexNum = 0;
		return;
	}
	outPtElemNum = ptNum*2*PTELEMNUM;
	outIndexNum = (ptNum-1)*6;
}

void lineBorderOp::CalLine2DBorderPtNum_Loop(int ptNum,unsigned short& outPtElemNum,unsigned short& outIndexElemNum)
{
	outPtElemNum = (ptNum+1)*PTELEMNUM;
	outIndexElemNum = ptNum*6;
}

void lineBorderOp::CalLine2DBorder_Loop(float* input,int ptNum,float width,unsigned short startIndex,float* outpt,unsigned short* outIndex)
{
	unsigned short index = 0;
	unsigned short ptElementNum = 0;
	unsigned short indexElementNum = 0;

	//ptElementNum = 16;
	point2D pt1(input[(ptNum-1)*INPUTELEMENTNUM],input[(ptNum-1)*INPUTELEMENTNUM+1]);
	point2D pt2(input[0],input[1]);
	point2D pt3(input[INPUTELEMENTNUM],input[INPUTELEMENTNUM+1]);
	CalMidPt2DBorderPts(pt2,pt1,pt3,width,startIndex,&outpt[ptElementNum],&outIndex[indexElementNum]);
	ptElementNum += 8;
	indexElementNum += 6;
	startIndex += 2;

	for(int i=1;i<ptNum;i++)
	{
		pt1 = pt2;
		pt2 = pt3;
		if(i==(ptNum-1))
			pt3.SetData(input[0],input[1]);
		else
			pt3.SetData(input[(i+1)*INPUTELEMENTNUM],input[(i+1)*INPUTELEMENTNUM+1]);

		//CalMidPt2DAlphaBorderPts(pt2,pt1,pt3,curDepth,width,curAlpha,&outpt[ptElementNum],startIndex,&outIndex[indexElementNum]);
		CalMidPt2DBorderPts(pt2,pt1,pt3,width,startIndex,&outpt[ptElementNum],&outIndex[indexElementNum]);
		ptElementNum += 8;
		startIndex += 2;
		indexElementNum += 6;
	}
	index = ptNum*8;
	for(int j=0;j<8;j++)
	{
		outpt[index+j] = outpt[j];
	}
}

void lineBorderOp::CalStartPt2DBorderPts(const point2D& pt,const point2D& nextPt,float width,float* out)
{
	int ptElemNum = 0;
	point2D tmpPt[2];
	line2D line(pt,nextPt);
	vector2D lineDir = line.m_LineDir;
	vector2D prepDir = lineDir.GetVerticalVec();
	Cal2DPtsAlongDir(pt,prepDir,width,tmpPt[0],tmpPt[1]);
	SetGen2DPoints(tmpPt,-0.25,0.75,&out[ptElemNum]);
}

void lineBorderOp::CalMidPt2DBorderPts(const point2D& pt,const point2D& prevPt,const point2D& afterPt,float width,point2D& out1,point2D& out2)
{
	line2D line1(prevPt,pt);
	if(line1.IsPointOnLine(afterPt,pt))
	{
		vector2D prepDir = line1.m_LineDir.GetVerticalVec();
		Cal2DPtsAlongDir(pt,prepDir,width,out1,out2);
	}
	else
	{
		line2D line2(pt,afterPt);
		vector2D line1PrepDir,line2PrepDir;
		line1PrepDir = line1.m_LineDir.GetVerticalVec();
		line2PrepDir = line2.m_LineDir.GetVerticalVec();

		point2D outpt1,outpt2;
		Cal2DPtsAlongDir(prevPt,line1PrepDir,width,outpt1,outpt2);
		line2D line11(outpt1,line1.m_LineDir);
		line2D line12(outpt2,line1.m_LineDir);

		Cal2DPtsAlongDir(pt,line2PrepDir,width,outpt1,outpt2);
		line2D line21(outpt1,line2.m_LineDir);
		line2D line22(outpt2,line2.m_LineDir);

		bool bInterSect1 = line11.intersection(line21,out1);
		bool bInterSect2 = line12.intersection(line22,out2);
		if(!bInterSect1||!bInterSect2)
		{
			vector2D prepDir = line1.m_LineDir.GetVerticalVec();
			Cal2DPtsAlongDir(pt,prepDir,width,out1,out2);
//			printf("pt:x=%f,y=%f,prevPt:x=%f,y=%f,nextPt:x=%f,y=%f\n",pt.x,pt.y,prevPt.x,prevPt.y,afterPt.x,afterPt.y);
		}
	}
}

void lineBorderOp::CalMidPt2DBorderPts(const point2D& pt,const point2D& prevPt,const point2D& afterPt,float width,
						unsigned short startIndex,float* out,unsigned short* outIndex/*unsigned int* outIndex*/)
{
	point2D sidePt[2];
	CalMidPt2DBorderPts(pt,prevPt,afterPt,width,sidePt[0],sidePt[1]);
	//SetGen2DElements(sidePt,depth,alpha,outTexV,out,startIndex,outIndex);
	SetGen2DPoints(sidePt, -0.25,0.75,out);
	SetGenTriangleIndex(startIndex,outIndex);
}

void lineBorderOp::CalEndPt2DBorderPts(const point2D& pt,const point2D& prevPt,float width,float* out,unsigned short startIndex,
						/*unsigned int* outIndex*/unsigned short* outIndex)
{
	int ptElemNum = 0;
	point2D tmpPt[2];
	line2D line(prevPt,pt);
	vector2D lineDir = line.m_LineDir;
	vector2D prepDir = lineDir.GetVerticalVec();
	Cal2DPtsAlongDir(pt,prepDir,width,tmpPt[0],tmpPt[1]);
	SetGen2DPoints(tmpPt,-0.25,0.75,&out[ptElemNum]);
	SetGenTriangleIndex(startIndex,outIndex);
}


void lineBorderOp::Cal2DPtsAlongDir(const point2D& pt,const vector2D& dir,float width,point2D& out1,point2D& out2)
{
	float halfWidth = width/2;
	out1 = pt - dir*halfWidth;
	out2 = pt + dir*halfWidth;
}

void lineBorderOp::SetGen2DPoint(const point2D& pt,float texCoordX,float texCoordY,float* pOut)
{
	int index = 0;
	pOut[index++] = pt.x;
	pOut[index++] = pt.y;
	pOut[index++] = texCoordX;
	pOut[index++] = texCoordY;
}

void lineBorderOp::SetGen2DPoints(point2D* pt, float coord1,float coord2,float* pOut)
{
	int ptElemNum = 0;
	SetGen2DPoint(pt[0],coord1,0.5,pOut);
	ptElemNum += PTELEMNUM;
	SetGen2DPoint(pt[1],coord2,0.5,&pOut[ptElemNum]);
}

void lineBorderOp::SetGenTriangleIndex(unsigned short startIndex,unsigned short* pIndex/*unsigned int* pIndex*/)
{
	pIndex[0] = startIndex;
	pIndex[1] = startIndex+1;
	pIndex[2] = startIndex+2;
	pIndex[3] = startIndex+1;
	pIndex[4] = startIndex+3;
	pIndex[5] = startIndex+2;
}
