#include "lineBorderOp.h"
#include <iostream>

using namespace std;

void lineBorderOp::CalLine2D(int index,float* outpt,unsigned short* outIndex,int posx,int posy, int width, int height)
{
    point2D pt1(posx,posy);
    point2D pt2(posx+width-1,posy);
    point2D pt3(posx,posy+height-1);
    point2D pt4(posx+width-1,posy+height-1);
    CalStartPt2DBorderPts(pt1,pt2,outpt);
    int ptElementNum = 2*PTELEMNUM;
    int indexElementNum = 0;
    CalEndPt2DBorderPts(pt3,pt4,0,&outpt[ptElementNum],0,&outIndex[indexElementNum]);

}


void lineBorderOp::CalLine2DBorderPtNum(int ptNum,unsigned short& outPtElemNum,unsigned short& outIndexNum)
{
    outPtElemNum = ptNum*2*PTELEMNUM;
    outIndexNum = (ptNum-1)*6;

}


void lineBorderOp::CalStartPt2DBorderPts(const point2D& pt,const point2D& nextPt,float* out)
{
    point2D tmpPt[2]={pt,nextPt};
    SetGen2DPoint(tmpPt[0],0.0,1.0,out);
    SetGen2DPoint(tmpPt[1],1.0,1.0,&out[PTELEMNUM]);

}


void lineBorderOp::CalEndPt2DBorderPts(const point2D& pt,const point2D& prevPt,float width,float* out,unsigned short startIndex,unsigned short* outIndex)
{
    point2D tmpPt[2] = {pt,prevPt};
    SetGen2DPoint(tmpPt[0],0.0,0.0,out);
    SetGen2DPoint(tmpPt[1],1.0,0.0,&out[PTELEMNUM]);
    SetGenTriangleIndex(startIndex,outIndex);

}


void lineBorderOp::SetGen2DPoint(const point2D& pt,float texCoordX,float texCoordY,float* pOut)
{
    int index = 0;
    pOut[index++] = pt.x;
    pOut[index++] = pt.y;
    pOut[index++] = texCoordX;
    pOut[index++] = texCoordY;

}


void lineBorderOp::SetGenTriangleIndex(unsigned short startIndex,unsigned short* pIndex)
{
    pIndex[0] = startIndex;
    pIndex[1] = startIndex+1;
    pIndex[2] = startIndex+2;
    pIndex[3] = startIndex+1;
    pIndex[4] = startIndex+3;
    pIndex[5] = startIndex+2;

}


point2D::point2D()
{
    x = 0.0;
    y = 0.0;
}

point2D::point2D(float x1,float y1)
{
    x = x1;
    y = y1;
}

point2D::point2D(const point2D& pt)
{
    x = pt.x;
    y = pt.y;
}

void point2D::SetData(float x1,float y1)
{
    x = x1;
    y = y1;
}

void lineBorderOp::CalLine2DBorder(float* input,int ptNum,/*float width,*/unsigned short startIndex,float* outpt,unsigned short* outIndex/*unsigned int* outIndex*/)
{
    point2D pt1(input[0],input[1]);//0,1,2,3
    point2D pt2(input[2],input[3]);//4,5,6,7
    point2D pt3,pt4;
    //CalStartPt2DBorderPts(pt1,pt2,outpt);
    point2D tmpPt[2]={pt1,pt2};
    //SetGen2DPoints(tmpPt,-0.25,0.75,outpt);
    SetGen2DPoint(tmpPt[0],-0.25,0.5,outpt);
    SetGen2DPoint(tmpPt[1],0.75,0.5,&outpt[PTELEMNUM]);

    int ptElementNum = 2*PTELEMNUM;
    int indexElementNum = 0;
    ptNum = ptNum/8;
    for(int i=1;i<ptNum;i++)
    {
        pt3.SetData(input[(2*i)*INPUTELEMENTNUM],input[(2*i)*INPUTELEMENTNUM+1]);
        pt4.SetData(input[(2*i)*INPUTELEMENTNUM+2],input[(2*i)*INPUTELEMENTNUM+3]);
        CalEndPt2DBorderPts(pt3,pt4,/*width,*/&outpt[ptElementNum],startIndex,&outIndex[indexElementNum]);
        ptElementNum += 2*PTELEMNUM;
        indexElementNum += 6;
        startIndex += 2;
    }

}


void lineBorderOp::CalEndPt2DBorderPts(const point2D& pt,const point2D& prevPt,/*float width,*/float* out,unsigned short startIndex,
                                       /*unsigned int* outIndex*/unsigned short* outIndex)
{
    int ptElemNum = 0;
    point2D tmpPt[2] = {pt,prevPt};
    SetGen2DPoints(tmpPt,-0.25,0.75,&out[ptElemNum]);
    SetGenTriangleIndex(startIndex,outIndex);
}

void lineBorderOp::SetGen2DPoints(point2D* pt, float coord1,float coord2,float* pOut)
{
    int ptElemNum = 0;
    SetGen2DPoint(pt[0],coord1,0.5,pOut);
    ptElemNum += PTELEMNUM;
    SetGen2DPoint(pt[1],coord2,0.5,&pOut[ptElemNum]);
}



