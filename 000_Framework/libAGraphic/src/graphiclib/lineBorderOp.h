#ifndef __LINEBORDEROP_H__
#define __LINEBORDEROP_H__

#define PTELEMNUM 4
#define INPUTELEMENTNUM 2

//#include "line2D.h"
class point2D
{
public:
    point2D();
    point2D(float x1,float y1);
    point2D(const point2D& pt);
    void SetData(float x1,float y1);
    float x;
    float y;
};


class lineBorderOp
{
public:
    void CalLine2D(int index,float* outpt,unsigned short* outIndex,int posx, int posy, int width, int height);
    void CalLine2DBorderPtNum(int ptNum,unsigned short& outPtElemNum,unsigned short& outIndexNum);
    void CalLine2DBorder(float* input,int ptNum,/*float width,*/unsigned short startIndex,float* outpt,unsigned short* outIndex/*unsigned int* outIndex*/);
private:
    void CalStartPt2DBorderPts(const point2D& pt,const point2D& nextPt,float* out);
    void CalEndPt2DBorderPts(const point2D& pt,const point2D& prevPt,float width,float* out,unsigned short startIndex,unsigned short* outIndex);
    void SetGen2DPoint(const point2D& pt,float texCoordX,float texCoordY,float* pOut);
    void SetGenTriangleIndex(unsigned short startIndex,unsigned short* pIndex);


    void CalEndPt2DBorderPts(const point2D& pt,const point2D& prevPt,/*float width,*/float* out,unsigned short startIndex,
        /*unsigned int* outIndex*/unsigned short* outIndex);

public:
    void SetGen2DPoints(point2D* pt, float coord1,float coord2,float* pOut);
    //void SetGenTriangleIndex(unsigned short startIndex,unsigned short* pIndex/*unsigned int* pIndex*/);
};



#endif
