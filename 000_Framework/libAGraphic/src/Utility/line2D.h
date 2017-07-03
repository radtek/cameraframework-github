#ifndef __LINE_2D__
#define __LINE_2D__
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define LINEPRECISION 0.0001
#define PI 3.1415926

class point2D
{
public:
	point2D();
	point2D(float x1,float y1);
	point2D(const point2D& pt);
	void SetData(float x1,float y1);
	void SetData(const point2D& pt);
	point2D& operator= (const point2D& pt);
	point2D operator+ (const point2D& pt) const;
	point2D operator- (const point2D& pt) const;

	float Distance(const point2D& pt)const;

	float x;
	float y;
};

class vector2D
{
public:
	vector2D();
	vector2D(float x,float y);
	vector2D(const point2D& pt);
	vector2D(const vector2D& vec);
	vector2D(const point2D& sp,const point2D& ep);

	vector2D& operator= (const vector2D& v);
	vector2D operator+ (const vector2D& v)const;
	vector2D operator- (const vector2D& v)const;
	vector2D operator-()const;
	vector2D& operator+= (const vector2D& v);
	vector2D& operator-= (const vector2D& v);
	point2D operator* (const float scale) const;

	void SetEndPoints(const point2D& pt1,const point2D& pt2);
	void SetEndPoints(float x1,float y1,float x2,float y2);
	void Normalize();
	vector2D GetVerticalVec() const;

	float angleRadWithVec(const vector2D& vec);
	float vecAngleRad()const;
	vector2D RotateAngle(float angleRad);//anti-clockwise
	bool BClockWise(const vector2D& vec);


	float dirx;
	float diry;
};

class line2D
{
	friend class line2DSegBorderOp;
	friend class lineBorderOp;
public:
	line2D();
	line2D(float x1,float y1,float x2,float y2);
	line2D(const point2D& pt1,const point2D& pt2);
	line2D(const point2D& pt1,const vector2D& dir);

	bool intersection(const line2D& line2,point2D& outpt);
	void SetLine(float x1,float y1,float x2,float y2);
	void SetLine(const point2D& pt1,const point2D& pt2);
	void SetLine(const point2D& pt, const vector2D& dir);
	line2D& operator= (const line2D& line2);

	bool IsPointOnLine(const point2D& pt);
	bool IsPointOnLine(const point2D& pt,const point2D& commonPt);

private:
	vector2D m_LineDir;
	point2D m_Pt1;
	point2D m_Pt2;
	float m_fSlope;
	float m_fOffset;
};

class point3D
{
public:
	point3D();
	point3D(float x1, float y1, float z1);
	point3D(float x1, float y1);
	point3D(const point2D& p);
	point3D(const point3D& p);

	void SetData(float x1, float y1, float z1);
	void SetData(const point3D& p);
	void SetData(float x1, float y1);
	void SetData(const point2D& p);

	float x;
	float y;
	float z;
};

class vector3D
{
public:
	vector3D();
	vector3D(float x, float y, float z);
	vector3D(const vector3D& v);
	vector3D(const point3D& pt1,const point3D& pt2);//vector from pt1 to pt2
	vector3D(const vector2D& v);

	void SetData(float x, float y, float z);
	void SetData(const vector3D& v);
	void SetData(const point3D& pt1,const point3D& pt2);
	void Normalize();

	vector3D operator+ (const vector3D& v) const;
	vector3D operator- (const vector3D& v) const;
	vector3D operator-()const;
	vector3D& operator= (const vector3D& v);
	vector3D& operator+= (const vector3D& v);
	vector3D& operator-= (const vector3D& v);
	vector3D operator* (float scale) const;

	float x;
	float y;
	float z;
};

class line2DSegBorderOp
{
public:	
	void CalLineSegBorder(float* input,int ptNum,float width,float* outpt);
	void CalLineSegBorder_Loop(float* input,int ptNum,float width,float* outpt);
	void CalPtBorderPts(const point2D& pt,const point2D& prevPt,const point2D& afterPt,float width,point2D& out1,point2D& out2);
	void CalStartSegEndPts(const point2D& pt,const point2D& afterPt,float width,point2D& out1,point2D& out2);
	void CalEndSegEndPts(const point2D& pt,const point2D& prevPt,float width,point2D& out1,point2D& out2);
	void Cal2PtAlongDir(const point2D& pt,const vector2D& dir,float width,point2D& borderpt1,point2D& borderpt2);
	///
	void Cal2PtAlongDir(const point2D& pt,const vector2D& dir,float width,
		               point2D& outpt1,vector2D& outDir1,
					    point2D& outpt2,vector2D& outDir2);
	void CalPtBorderPts(const point2D& pt,const point2D& prevPt,const point2D& afterPt,
						float width,point2D& out1,point2D& out2,
						vector2D& outVec1,vector2D& outVec2);

	///
	void CalLine3DSegBorderAndIndex(float* input,int ptNum,float width,float height,float* outpt,unsigned int* outputIndex);
	void CalStartSegPtAndIndex3D(const point2D& pt,const point2D& afterPt,float width,float height,float* outpt,unsigned int* outputIndex);

	//outpt: stride 6(3 for pos, 3 for Normal)
	void CalStartSeg3DPtNormalIndex(const point2D& pt,const point2D& afterPt,float width,float height,float* outpt,unsigned int* outputIndex);
	void CalLineSeg3DPtNormalIndex(float* input,int ptNum,float width,float height,float* outpt,unsigned int* outputIndex);
	void CalEndSeg3DPtNormalIndex(const point2D& pt,const point2D& prevPt,float width,float height,float* outpt,unsigned int startIndex,unsigned int* outputIndex);

	void CalTriangle3DPtNormalIndex(const point2D& pt,const vector2D& dir,float width,float length,float height,float* outpt,unsigned int startIndex,unsigned int* outputIndex);

	void CalEndSeg3DBorderWithHead(const point2D& pt,const point2D& prevPt,float width,float height,float* outpt,unsigned int startIndex,unsigned int* outputIndex);
	void CalLine3DBorderWithHead(float* input,int ptNum,float width,float height,float headWidth,float headLength,float* outpt,unsigned int* outputIndex);

};

void Cal2PtAlongDir(point2D& pt,vector2D& dir,float width,point2D& borderpt1,point2D& borderpt2);

#endif
