#include "line2D.h"

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

void point2D::SetData(const point2D& pt)
{
	x = pt.x;
	y = pt.y;
}

point2D& point2D::operator= (const point2D& pt)
{
	this->x = pt.x;
	this->y = pt.y;
	return *this;
}

point2D point2D::operator+ (const point2D& pt)const
{
	point2D out;
	out.x = x + pt.x;
	out.y = y + pt.y;
	return out;
}

point2D point2D::operator- (const point2D& pt)const
{
	point2D out;
	out.x = x - pt.x;
	out.y = y - pt.y;
	return out;
}

float point2D::Distance(const point2D& pt)const
{
	float disX = x - pt.x;
	float disY = y - pt.y;
	float dis = disX*disX + disY*disY;
	dis = sqrt(dis);
	return dis;
}


vector2D::vector2D()
{
	;
}

vector2D::vector2D(float x,float y)
{
	float length = sqrt(x*x+y*y);
	dirx = x/length;
	diry = y/length;
}

vector2D::vector2D(const point2D& pt)
{
	float x = pt.x;
	float y = pt.y;
	float length = sqrt(x*x+y*y);
	dirx = x/length;
	diry = y/length;
}

vector2D::vector2D(const vector2D& vec)
{
	dirx = vec.dirx;
	diry = vec.diry;
	Normalize();
}

vector2D::vector2D(const point2D& sp,const point2D& ep)
{
	dirx = ep.x - sp.x;
	diry = ep.y - sp.y;
	Normalize();
}

vector2D& vector2D::operator= (const vector2D& v)
{
	this->dirx = v.dirx;
	this->diry = v.diry;
	return *this;
}

vector2D vector2D::operator+ (const vector2D& v)const
{
	vector2D tmp;
	tmp.dirx = dirx + v.dirx;
	tmp.diry = diry + v.diry;
	return tmp;
}

vector2D vector2D::operator- (const vector2D& v)const
{
	vector2D tmp;
	tmp.dirx = dirx - v.dirx;
	tmp.diry = diry - v.diry;
	return tmp;
}

vector2D vector2D::operator-()const
{
	vector2D res;
	res.dirx = -dirx;
	res.diry = -diry;
	return res;
}

vector2D& vector2D::operator+= (const vector2D& v)
{
	this->dirx = this->dirx + v.dirx;
	this->diry = this->diry + v.diry;
	return *this;
}

vector2D& vector2D::operator-= (const vector2D& v)
{
	this->dirx = this->dirx - v.dirx;
	this->diry = this->diry - v.diry;
	return *this;
}

point2D vector2D::operator* (const float scale) const
{
	point2D tmp;
	tmp.x = dirx*scale;
	tmp.y = diry*scale;
	return tmp;
}

void vector2D::SetEndPoints(const point2D& pt1,const point2D& pt2)
{
	dirx = pt2.x - pt1.x;
	diry = pt2.y - pt1.y;
	Normalize();
}

void vector2D::SetEndPoints(float x1,float y1,float x2,float y2)
{
	dirx = x2 - x1;
	diry = y2 - y1;
	Normalize();
}

void vector2D::Normalize()
{
	float length = sqrt(dirx*dirx+diry*diry);
	dirx = dirx/length;
	diry = diry/length;
}

vector2D vector2D::GetVerticalVec() const
{
	vector2D out;
	out.dirx = diry;
	out.diry = -dirx;
	return out;
}

float vector2D::angleRadWithVec(const vector2D& vec)
{
	float out;
	float dot = dirx*vec.dirx+diry*vec.diry;
	out = acos(dot);
	return out;
}

float vector2D::vecAngleRad()const
{
	float out;
	if(fabs(dirx)<LINEPRECISION)
		out = PI/2;
	else
		out = atan(diry/dirx);
	return out;
}

vector2D vector2D::RotateAngle(float angleRad)
{
	vector2D out;
	out.dirx = dirx*cos(angleRad)-diry*sin(angleRad);
	out.diry = diry*cos(angleRad)+dirx*sin(angleRad);
	return out;
}

bool vector2D::BClockWise(const vector2D& vec)
{
	bool res;
	float cross = dirx*vec.diry - diry*vec.dirx;
	res = cross>0 ? 0:1;
	return res;
}

line2D::line2D()
{
	;
}

line2D::line2D(float x1, float y1, float x2, float y2)
{
	m_Pt1.SetData(x1,y1);
	m_Pt2.SetData(x2,y2);
	m_LineDir.SetEndPoints(x1,y1,x2,y2);
	m_fSlope = m_LineDir.diry/m_LineDir.dirx;
	m_fOffset = y1 - m_fSlope * x1;
}

line2D::line2D(const point2D& pt1,const point2D& pt2)
{
	m_Pt1.SetData(pt1);
	m_Pt2.SetData(pt2);
	m_LineDir.SetEndPoints(pt1,pt2);
	m_fSlope = m_LineDir.diry/m_LineDir.dirx;
	m_fOffset = pt1.y - m_fSlope * pt1.x;
}

line2D::line2D(const point2D& pt1,const vector2D& dir)
{
	m_Pt2.SetData(pt1);
	m_Pt1 = m_Pt2 + dir*1.0;
	m_LineDir = dir;
	m_fSlope = m_LineDir.diry/m_LineDir.dirx;
	m_fOffset = pt1.y - m_fSlope * pt1.x;
}

line2D& line2D::operator= (const line2D& line2)
{
	this->m_Pt1 = line2.m_Pt1;
	this->m_Pt2 = line2.m_Pt2;
	this->m_LineDir = line2.m_LineDir;
	this->m_fSlope = line2.m_fSlope;
	this->m_fOffset = line2.m_fOffset;
	return *this;
}

void line2D::SetLine(float x1,float y1,float x2,float y2)
{
	m_Pt1.SetData(x1,y1);
	m_Pt2.SetData(x2,y2);
	m_LineDir.SetEndPoints(x1,y1,x2,y2);
	m_fSlope = m_LineDir.diry/m_LineDir.dirx;
	m_fOffset = y1 - m_fSlope * x1;
}

void line2D::SetLine(const point2D& pt1,const point2D& pt2)
{
	m_Pt1.SetData(pt1);
	m_Pt2.SetData(pt2);
	m_LineDir.SetEndPoints(pt1,pt2);
	m_fSlope = m_LineDir.diry/m_LineDir.dirx;
	m_fOffset = pt1.y - m_fSlope * pt1.x;
}

void line2D::SetLine(const point2D& pt,const vector2D& dir)
{
	m_Pt2.SetData(pt);
	m_Pt1 = m_Pt2 + dir*1.0;
	m_LineDir = dir;
	m_fSlope = m_LineDir.diry/m_LineDir.dirx;
	m_fOffset = pt.y - m_fSlope * pt.x;
}

bool line2D::IsPointOnLine(const point2D& pt)
{
	bool res = false;

	if(fabs(m_LineDir.dirx)<LINEPRECISION)
	{
		if(fabs(pt.x-m_Pt1.x)<LINEPRECISION)
			res = true;
	}
	else
	{
		float y = m_fSlope * pt.x + m_fOffset;
		if(fabs(y - pt.y)<LINEPRECISION)
			res = true;
	}
	return res;
}

bool line2D::IsPointOnLine(const point2D& pt,const point2D& commonPt)
{
	bool res = false;
	float dis = pt.Distance(commonPt);
	if(fabs(m_LineDir.dirx)<LINEPRECISION)
	{
		if(fabs((pt.x-commonPt.x)/dis)<LINEPRECISION)
			res = true;
	}
	else
	{
		float y = m_fSlope * pt.x + m_fOffset;
		if(fabs((y - pt.y)/dis)<LINEPRECISION)
			res = true;
	}
	return res;
}

bool line2D::intersection(const line2D& line2,point2D& outpt)
{
	bool res = true;

	if(fabs(m_LineDir.dirx)<LINEPRECISION)
	{
		if(fabs(line2.m_LineDir.dirx)<LINEPRECISION)
		{
//			printf("line1 and line2 dirx all small!\n");
			res = false;
		}
		else
		{
			outpt.x = m_Pt1.x;
			outpt.y = line2.m_fSlope*outpt.x + line2.m_fOffset;
		}
	}
	else
	{
		if(fabs(line2.m_LineDir.dirx)<LINEPRECISION)
		{
			outpt.x = line2.m_Pt1.x;
			outpt.y = m_fSlope*outpt.x + m_fOffset;
		}
		else
		{
			float slope2 = line2.m_fSlope;
			float offset2 = line2.m_fOffset;
			if(fabs(m_fSlope-slope2)<LINEPRECISION)
			{
//				printf("fabs(m_fSlope-slope2)<LINEPRECISION!\n");
				res = false;
			}
			else
			{
				if(fabs(m_fSlope)>LINEPRECISION)
				{
					outpt.y = (m_fSlope*offset2-slope2*m_fOffset)/(m_fSlope - slope2);
					outpt.x = (outpt.y - m_fOffset)/m_fSlope;
				}
				else
				{
					outpt.y = m_fOffset;
					outpt.x = (m_fOffset - offset2)/slope2;
				}
			}
		}
	}

	return res;
}

point3D::point3D()
{
	x = 0;
	y = 0;
	z = 0;
}

point3D::point3D(float x1, float y1, float z1)
{
	x = x1;
	y = y1;
	z = z1;
}

point3D::point3D(float x1, float y1)
{
	x = x1;
	y = y1;
	z = 0.0;
}

point3D::point3D(const point2D& p)
{
	x = p.x;
	y = p.y;
	z = 0.0;
}

point3D::point3D(const point3D& p)
{
	x = p.x;
	y = p.y;
	z = p.z;
}

void point3D::SetData(float x1, float y1, float z1)
{
	x = x1;
	y = y1;
	z = z1;
}

void point3D::SetData(const point3D& p)
{
	x = p.x;
	y = p.y;
	z = p.z;
}

void point3D::SetData(float x1, float y1)
{
	x = x1;
	y = y1;
	z = 0;
}

void point3D::SetData(const point2D& p)
{
	x = p.x;
	y = p.y;
	z = 0.0;
}

vector3D::vector3D()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

vector3D::vector3D(float x1, float y1, float z1)
{
	x = x1;
	y = y1;
	z = z1;
}

vector3D::vector3D(const vector3D& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

vector3D::vector3D(const vector2D& v)
{
	x = v.dirx;
	y = v.diry;
	z = 0;
}

vector3D::vector3D(const point3D& pt1,const point3D& pt2)//vector from pt1 to pt2
{
	x = pt2.x - pt1.x;
	y = pt2.y - pt1.y;
	z = pt2.z - pt1.z;
	Normalize();
}

void vector3D::SetData(float x1, float y1, float z1)
{
	x = x1;
	y = y1;
	z = z1;
}

void vector3D::SetData(const vector3D& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

void vector3D::SetData(const point3D& pt1,const point3D& pt2)
{
	x = pt2.x - pt1.x;
	y = pt2.y - pt1.y;
	z = pt2.z - pt1.z;
	Normalize();
}

void vector3D::Normalize()
{
	float length = sqrt(x*x + y*y + z*z);
	x = x/length;
	y = y/length;
	z = z/length;
}

vector3D vector3D::operator+ (const vector3D& v) const
{
	vector3D res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	//res.Normalize();
	return res;
}

vector3D vector3D::operator- (const vector3D& v) const
{
	vector3D res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	//res.Normalize();
	return res;
}

vector3D vector3D::operator-() const
{
	vector3D res;
	res.x = -x;
	res.y = -y;
	res.z = -z;
	return res;
}

vector3D vector3D::operator* (float scale) const
{
	vector3D res;
	res.x = x * scale;
	res.y = y * scale;
	res.z = z * scale;
	//res.Normalize();
	return res;
}

vector3D& vector3D::operator= (const vector3D& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return (*this);
}

vector3D& vector3D::operator+= (const vector3D& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	//Normalize();
	return (*this);
}

vector3D& vector3D::operator-= (const vector3D& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	//Normalize();
	return (*this);
}


void Cal2PtAlongDir(point2D& pt,vector2D& dir,float width,point2D& outpt1,point2D& outpt2)
{
	point2D tmpPt1,tmpPt2;
	float halfWidth = width/2;
	outpt1 = pt - dir*halfWidth;
	outpt2 = pt + dir*halfWidth;
}

void line2DSegBorderOp::CalLineSegBorder(float* input,int ptNum,float width,float* outpt)
{
	int index = 0;
	point2D out1,out2,pt3;
	point2D pt1(input[0],input[1]);
	point2D pt2(input[2],input[3]);
	CalStartSegEndPts(pt1,pt2,width,out1,out2);
	outpt[index++] = out1.x;
	outpt[index++] = out1.y;
	outpt[index++] = out2.x;
	outpt[index++] = out2.y;

	for(int i=1;i<ptNum-1;i++)
	{
		pt3.SetData(input[(i+1)*2],input[(i+1)*2+1]);
		CalPtBorderPts(pt2,pt1,pt3,width,out1,out2);
		outpt[index++] = out1.x;
		outpt[index++] = out1.y;
		outpt[index++] = out2.x;
		outpt[index++] = out2.y;
		pt1 = pt2;
		pt2 = pt3;
	}

	CalEndSegEndPts(pt2,pt1,width,out1,out2);
	outpt[index++] = out1.x;
	outpt[index++] = out1.y;
	outpt[index++] = out2.x;
	outpt[index++] = out2.y;
}

void line2DSegBorderOp::CalLineSegBorder_Loop(float* input,int ptNum,float width,float* outpt)
{
	int index = 0;
	point2D out1,out2;
	point2D pt1(input[(ptNum-1)*2],input[(ptNum-1)*2+1]);
	point2D pt2(input[0],input[1]);
	//point2D pt3(input[2],input[3]);
	point2D pt3;

	for(int i=0;i<ptNum;i++)
	{
		if(i==(ptNum-1))
			pt3.SetData(input[0],input[1]);
		else
			pt3.SetData(input[(i+1)*2],input[(i+1)*2+1]);
		CalPtBorderPts(pt2,pt1,pt3,width,out1,out2);
		outpt[index++] = out1.x;
		outpt[index++] = out1.y;
		outpt[index++] = out2.x;
		outpt[index++] = out2.y;
		pt1 = pt2;
		pt2 = pt3;
	}
}

void line2DSegBorderOp::CalStartSegEndPts(const point2D& pt,const point2D& afterPt,float width,point2D& out1,point2D& out2)
{
	line2D line(pt,afterPt);
	vector2D lineDir = line.m_LineDir;
	vector2D prepDir = lineDir.GetVerticalVec();
	Cal2PtAlongDir(pt,prepDir,width,out1,out2);
}

void line2DSegBorderOp::CalEndSegEndPts(const point2D& pt,const point2D& prevPt,float width,point2D& out1,point2D& out2)
{
	line2D line(prevPt,pt);
	vector2D lineDir = line.m_LineDir;
	vector2D prepDir = lineDir.GetVerticalVec();
	Cal2PtAlongDir(pt,prepDir,width,out1,out2);
}

void line2DSegBorderOp::CalPtBorderPts(const point2D& pt,const point2D& prevPt,const point2D& afterPt,float width,point2D& out1,point2D& out2)
{
	line2D line1(prevPt,pt);
	if(line1.IsPointOnLine(afterPt,pt))
	{
		vector2D prepDir = line1.m_LineDir.GetVerticalVec();
		Cal2PtAlongDir(pt,prepDir,width,out1,out2);
	}
	else
	{
		line2D line2(pt,afterPt);
		vector2D line1PrepDir,line2PrepDir;
		line1PrepDir = line1.m_LineDir.GetVerticalVec();
		line2PrepDir = line2.m_LineDir.GetVerticalVec();

		point2D outpt1,outpt2;
		Cal2PtAlongDir(prevPt,line1PrepDir,width,outpt1,outpt2);
		line2D line11(outpt1,line1.m_LineDir);
		line2D line12(outpt2,line1.m_LineDir);

		Cal2PtAlongDir(pt,line2PrepDir,width,outpt1,outpt2);
		line2D line21(outpt1,line2.m_LineDir);
		line2D line22(outpt2,line2.m_LineDir);

		line11.intersection(line21,out1);
		line12.intersection(line22,out2);

	}
}

void line2DSegBorderOp::CalPtBorderPts(const point2D& pt,const point2D& prevPt,const point2D& afterPt,
					float width,point2D& out1,point2D& out2,
					vector2D& outVec1,vector2D& outVec2)
{
	line2D line1(prevPt,pt);
	if(line1.IsPointOnLine(afterPt,pt))
	{
		vector2D prepDir = line1.m_LineDir.GetVerticalVec();
		Cal2PtAlongDir(pt,prepDir,width,out1,out2);
		outVec1 = -prepDir;
		outVec2 = prepDir;
	}
	else
	{
		line2D line2(pt,afterPt);
		vector2D line1PrepDir,line2PrepDir;
		line1PrepDir = line1.m_LineDir.GetVerticalVec();
		line2PrepDir = line2.m_LineDir.GetVerticalVec();

		point2D outpt1,outpt2;
		Cal2PtAlongDir(prevPt,line1PrepDir,width,outpt1,outpt2);
		line2D line11(outpt1,line1.m_LineDir);
		line2D line12(outpt2,line1.m_LineDir);

		Cal2PtAlongDir(pt,line2PrepDir,width,outpt1,outpt2);
		line2D line21(outpt1,line2.m_LineDir);
		line2D line22(outpt2,line2.m_LineDir);

		line11.intersection(line21,out1);
		line12.intersection(line22,out2);

		outVec2 = line1PrepDir + line2PrepDir;
		outVec1 = -outVec2;
	}
}

void line2DSegBorderOp::Cal2PtAlongDir(const point2D& pt,const vector2D& dir,float width,point2D& borderpt1,point2D& borderpt2)
{
	point2D tmpPt1,tmpPt2;
	float halfWidth = width/2;
	borderpt1 = pt - dir*halfWidth;
	borderpt2 = pt + dir*halfWidth;
}

void line2DSegBorderOp::CalStartSegPtAndIndex3D(const point2D& pt,const point2D& afterPt,float width,float height,float* outpt,unsigned int* outputIndex)
{
	point2D out1,out2;
	line2D line(pt,afterPt);
	vector2D lineDir = line.m_LineDir;
	vector2D prepDir = lineDir.GetVerticalVec();
	Cal2PtAlongDir(pt,prepDir,width,out1,out2);
	float z = height/2;
	int index = 0;
	outpt[index++] = out1.x;
	outpt[index++] = out1.y;
	outpt[index++] = z;

	outpt[index++] = out1.x;
	outpt[index++] = out1.y;
	outpt[index++] = -z;

	outpt[index++] = out2.x;
	outpt[index++] = out2.y;
	outpt[index++] = z;

	outpt[index++] = out2.x;
	outpt[index++] = out2.y;
	outpt[index++] = -z;

	index = 0;
	outputIndex[index++] = 0;
	outputIndex[index++] = 1;
	outputIndex[index++] = 2;
	outputIndex[index++] = 1;
	outputIndex[index++] = 3;
	outputIndex[index++] = 2;
}

void line2DSegBorderOp::CalStartSeg3DPtNormalIndex(const point2D& pt,const point2D& afterPt,float width,float height,float* outpt,unsigned int* outputIndex)
{
	point2D out1,out2;
	line2D line(pt,afterPt);
	vector2D lineDir = line.m_LineDir;
	vector2D prepDir = lineDir.GetVerticalVec();
	Cal2PtAlongDir(pt,prepDir,width,out1,out2);
	vector3D vec1(-prepDir);
	vector3D vec2(prepDir);
	vector3D vecZ(0.0,0.0,1.0);
	vector3D vec;
	vec1 = vec1 - lineDir;
	vec1.Normalize();
	vec2 = vec2 - lineDir;
	vec2.Normalize();

	float z = height/2;
	int index = 0;
	//pos
	outpt[index++] = out1.x;
	outpt[index++] = out1.y;
	outpt[index++] = z;
	//normal
	vec = vec1+vecZ;
	vec.Normalize();
	outpt[index++] = vec.x;
	outpt[index++] = vec.y;
	outpt[index++] = vec.z;

    //pos
	outpt[index++] = out1.x;
	outpt[index++] = out1.y;
	outpt[index++] = -z;
	//normal
	vec = vec1-vecZ;
	vec.Normalize();
	outpt[index++] = vec.x;
	outpt[index++] = vec.y;
	outpt[index++] = vec.z;

	//pos
	outpt[index++] = out2.x;
	outpt[index++] = out2.y;
	outpt[index++] = z;
	//normal
	vec = vec2 + vecZ;
	vec.Normalize();
	outpt[index++] = vec.x;
	outpt[index++] = vec.y;
	outpt[index++] = vec.z;

	//pos
	outpt[index++] = out2.x;
	outpt[index++] = out2.y;
	outpt[index++] = -z;
	//normal
	vec = vec2 - vecZ;
	vec.Normalize();
	outpt[index++] = vec.x;
	outpt[index++] = vec.y;
	outpt[index++] = vec.z;

	index = 0;
	outputIndex[index++] = 0;
	outputIndex[index++] = 1;
	outputIndex[index++] = 2;
	outputIndex[index++] = 1;
	outputIndex[index++] = 3;
	outputIndex[index++] = 2;
}

void line2DSegBorderOp::CalEndSeg3DPtNormalIndex(const point2D& pt,const point2D& prevPt,float width,float height,float* outpt,unsigned int startIndex,unsigned int* outputIndex)
{
	point2D out1,out2;
	line2D line(prevPt,pt);
	vector2D lineDir = line.m_LineDir;
	vector2D prepDir = lineDir.GetVerticalVec();
	Cal2PtAlongDir(pt,prepDir,width,out1,out2);
	vector3D vec1(-prepDir);
	vector3D vec2(prepDir);
	vector3D vecZ(0.0,0.0,1.0);
	vector3D vec;
	vec1 = vec1 + lineDir;
	vec1.Normalize();
	vec2 = vec2 + lineDir;
	vec2.Normalize();
	float z = height/2;
	int index = 0;
	//pos
	outpt[index++] = out1.x;
	outpt[index++] = out1.y;
	outpt[index++] = z;
	//normal
	vec = vec1+vecZ;
	vec.Normalize();
	outpt[index++] = vec.x;
	outpt[index++] = vec.y;
	outpt[index++] = vec.z;

    //pos
	outpt[index++] = out1.x;
	outpt[index++] = out1.y;
	outpt[index++] = -z;
	//normal
	vec = vec1-vecZ;
	vec.Normalize();
	outpt[index++] = vec.x;
	outpt[index++] = vec.y;
	outpt[index++] = vec.z;

	//pos
	outpt[index++] = out2.x;
	outpt[index++] = out2.y;
	outpt[index++] = z;
	//normal
	vec = vec2 + vecZ;
	vec.Normalize();
	outpt[index++] = vec.x;
	outpt[index++] = vec.y;
	outpt[index++] = vec.z;

	//pos
	outpt[index++] = out2.x;
	outpt[index++] = out2.y;
	outpt[index++] = -z;
	//normal
	vec = vec2 - vecZ;
	vec.Normalize();
	outpt[index++] = vec.x;
	outpt[index++] = vec.y;
	outpt[index++] = vec.z;

	index = 0;
	//up
	outputIndex[index++] = startIndex;
	outputIndex[index++] = startIndex-4;
	outputIndex[index++] = startIndex-2;
	outputIndex[index++] = startIndex;
	outputIndex[index++] = startIndex-2;
	outputIndex[index++] = startIndex+2;
	//down
	outputIndex[index++] = startIndex+1;
	outputIndex[index++] = startIndex+3;
	outputIndex[index++] = startIndex-1;
	outputIndex[index++] = startIndex+1;
	outputIndex[index++] = startIndex-1;
	outputIndex[index++] = startIndex-3;
	//left
	outputIndex[index++] = startIndex;
	outputIndex[index++] = startIndex+1;
	outputIndex[index++] = startIndex-4;
	outputIndex[index++] = startIndex+1;
	outputIndex[index++] = startIndex-3;
	outputIndex[index++] = startIndex-4;
	//right
	outputIndex[index++] = startIndex+2;
	outputIndex[index++] = startIndex-2;
	outputIndex[index++] = startIndex-1;
	outputIndex[index++] = startIndex-1;
	outputIndex[index++] = startIndex+3;
	outputIndex[index++] = startIndex+2;
	//last face
	outputIndex[index++] = startIndex;
	outputIndex[index++] = startIndex+2;
	outputIndex[index++] = startIndex+1;
	outputIndex[index++] = startIndex+2;
	outputIndex[index++] = startIndex+3;
	outputIndex[index++] = startIndex+1;
}

void line2DSegBorderOp::CalEndSeg3DBorderWithHead(const point2D& pt,const point2D& prevPt,float width,float height,float* outpt,unsigned int startIndex,unsigned int* outputIndex)
{
	point2D out1,out2;
	line2D line(prevPt,pt);
	vector2D lineDir = line.m_LineDir;
	vector2D prepDir = lineDir.GetVerticalVec();
	Cal2PtAlongDir(pt,prepDir,width,out1,out2);
	vector3D vec1(-prepDir);
	vector3D vec2(prepDir);
	vector3D vecZ(0.0,0.0,1.0);
	vector3D vec;
	vec1 = vec1 - lineDir;
	vec1.Normalize();
	vec2 = vec2 - lineDir;
	vec2.Normalize();
	float z = height/2;
	int index = 0;
	//pos
	outpt[index++] = out1.x;
	outpt[index++] = out1.y;
	outpt[index++] = z;
	//normal
	vec = vec1+vecZ;
	vec.Normalize();
	outpt[index++] = vec.x;
	outpt[index++] = vec.y;
	outpt[index++] = vec.z;

    //pos
	outpt[index++] = out1.x;
	outpt[index++] = out1.y;
	outpt[index++] = -z;
	//normal
	vec = vec1-vecZ;
	vec.Normalize();
	outpt[index++] = vec.x;
	outpt[index++] = vec.y;
	outpt[index++] = vec.z;

	//pos
	outpt[index++] = out2.x;
	outpt[index++] = out2.y;
	outpt[index++] = z;
	//normal
	vec = vec2 + vecZ;
	vec.Normalize();
	outpt[index++] = vec.x;
	outpt[index++] = vec.y;
	outpt[index++] = vec.z;

	//pos
	outpt[index++] = out2.x;
	outpt[index++] = out2.y;
	outpt[index++] = -z;
	//normal
	vec = vec2 - vecZ;
	vec.Normalize();
	outpt[index++] = vec.x;
	outpt[index++] = vec.y;
	outpt[index++] = vec.z;

	index = 0;
	//up
	outputIndex[index++] = startIndex;
	outputIndex[index++] = startIndex-4;
	outputIndex[index++] = startIndex-2;
	outputIndex[index++] = startIndex;
	outputIndex[index++] = startIndex-2;
	outputIndex[index++] = startIndex+2;
	//down
	outputIndex[index++] = startIndex+1;
	outputIndex[index++] = startIndex+3;
	outputIndex[index++] = startIndex-1;
	outputIndex[index++] = startIndex+1;
	outputIndex[index++] = startIndex-1;
	outputIndex[index++] = startIndex-3;
	//left
	outputIndex[index++] = startIndex;
	outputIndex[index++] = startIndex+1;
	outputIndex[index++] = startIndex-4;
	outputIndex[index++] = startIndex+1;
	outputIndex[index++] = startIndex-3;
	outputIndex[index++] = startIndex-4;
	//right
	outputIndex[index++] = startIndex+2;
	outputIndex[index++] = startIndex-2;
	outputIndex[index++] = startIndex-1;
	outputIndex[index++] = startIndex-1;
	outputIndex[index++] = startIndex+3;
	outputIndex[index++] = startIndex+2;
	//last face
	outputIndex[index++] = startIndex;
	outputIndex[index++] = startIndex+2;
	outputIndex[index++] = startIndex+1;
	outputIndex[index++] = startIndex+2;
	outputIndex[index++] = startIndex+3;
	outputIndex[index++] = startIndex+1;
}

void line2DSegBorderOp::CalLine3DSegBorderAndIndex(float* input,int ptNum,float width,float height,float* outpt,unsigned int* outputIndex)
{
	point2D pt1,pt2,pt3,out1,out2;
	pt1.SetData(input[0],input[1]);
	pt2.SetData(input[2],input[3]);

	CalStartSegPtAndIndex3D(pt1,pt2,width,height,outpt,outputIndex);
	float z = height/2;
	int index1,index2;
	for(int i=1;i<ptNum-1;i++)
	{
		pt3.SetData(input[(i+1)*2],input[(i+1)*2+1]);
		CalPtBorderPts(pt2,pt1,pt3,width,out1,out2);
		for(int j=0;j<2;j++)
		{
			index1 = 12*i+j*3;
			index2 = index1 + 6;
			outpt[index1] = out1.x;
			outpt[index1+1] = out1.y;
			outpt[index1+2] = z;

			outpt[index2] = out2.x;
			outpt[index2+1] = out2.y;
			outpt[index2+2] = -z;
		}

		index1 = 6+24*(i-1);
		index2 = i*4;
		//up face
		outputIndex[index1++] = index2-4;
		outputIndex[index1++] = index2-2;
		outputIndex[index1++] = index2;
		outputIndex[index1++] = index2-2;
		outputIndex[index1++] = index2+2;
		outputIndex[index1++] = index2;
		//down face
		outputIndex[index1++] = index2-3;
		outputIndex[index1++] = index2+1;
		outputIndex[index1++] = index2-1;
		outputIndex[index1++] = index2+1;
		outputIndex[index1++] = index2+3;
		outputIndex[index1++] = index2-1;
		//left face
		outputIndex[index1++] = index2-4;
		outputIndex[index1++] = index2;
		outputIndex[index1++] = index2-3;
		outputIndex[index1++] = index2;
		outputIndex[index1++] = index2+1;
		outputIndex[index1++] = index2-3;
		//right face
		outputIndex[index1++] = index2-2;
		outputIndex[index1++] = index2-1;
		outputIndex[index1++] = index2+2;
		outputIndex[index1++] = index2-1;
		outputIndex[index1++] = index2+3;
		outputIndex[index1++] = index2+2;

		pt1 = pt2;
		pt2 = pt3;
	}
	//last face
	//CalEndSeg3DPtNormalIndex(pt3,pt2,width,height,&outpt[(ptNum-1)*4],(ptNum-1)*4,&outputIndex[6+24*(ptNum-1)]);
	index1 = 6+24*(ptNum-1);
	index2 = (ptNum-1)*4;
	outputIndex[index1++] = index2;
	outputIndex[index1++] = index2+2;
	outputIndex[index1++] = index2+1;
	outputIndex[index1++] = index2+2;
	outputIndex[index1++] = index2+3;
	outputIndex[index1++] = index2+1;
}

void line2DSegBorderOp::CalLineSeg3DPtNormalIndex(float* input,int ptNum,float width,float height,float* outpt,unsigned int* outputIndex)
{
	point2D pt1,pt2,pt3,out[2];
	pt1.SetData(input[0],input[1]);
	pt2.SetData(input[2],input[3]);

	CalStartSeg3DPtNormalIndex(pt1,pt2,width,height,outpt,outputIndex);
	float z = height/2;
	int index1,index2;
	vector2D vec2d[2];
	vector3D vecZ(0.0,0.0,1.0);
	vector3D vec3d,vec;
	for(int i=1;i<ptNum-1;i++)
	{
		pt3.SetData(input[(i+1)*2],input[(i+1)*2+1]);
		CalPtBorderPts(pt2,pt1,pt3,width,out[0],out[1],vec2d[0],vec2d[1]);
		index1 = 24*i;
		for(int j=0;j<2;j++)
		{
			//pos
			outpt[index1++] = out[j].x;
			outpt[index1++] = out[j].y;
			outpt[index1++] = z;
			//normal
			vec3d.SetData(vec2d[j]);
			vec = vec3d + vecZ;
			vec.Normalize();
			outpt[index1++] = vec.x;
			outpt[index1++] = vec.y;
			outpt[index1++] = vec.z;

			//pos
			outpt[index1++] = out[j].x;
			outpt[index1++] = out[j].y;
			outpt[index1++] = -z;
			//normal
			vec = vec3d - vecZ;
			vec.Normalize();
			outpt[index1++] = vec.x;
			outpt[index1++] = vec.y;
			outpt[index1++] = vec.z;
		}

		index1 = 6+24*(i-1);
		index2 = i*4;
		//up face
		outputIndex[index1++] = index2-4;
		outputIndex[index1++] = index2-2;
		outputIndex[index1++] = index2;
		outputIndex[index1++] = index2-2;
		outputIndex[index1++] = index2+2;
		outputIndex[index1++] = index2;
		//down face
		outputIndex[index1++] = index2-3;
		outputIndex[index1++] = index2+1;
		outputIndex[index1++] = index2-1;
		outputIndex[index1++] = index2+1;
		outputIndex[index1++] = index2+3;
		outputIndex[index1++] = index2-1;
		//left face
		outputIndex[index1++] = index2-4;
		outputIndex[index1++] = index2;
		outputIndex[index1++] = index2-3;
		outputIndex[index1++] = index2;
		outputIndex[index1++] = index2+1;
		outputIndex[index1++] = index2-3;
		//right face
		outputIndex[index1++] = index2-2;
		outputIndex[index1++] = index2-1;
		outputIndex[index1++] = index2+2;
		outputIndex[index1++] = index2-1;
		outputIndex[index1++] = index2+3;
		outputIndex[index1++] = index2+2;

		pt1 = pt2;
		pt2 = pt3;
	}
	//last face
	index1 = (ptNum-2)*2;
	pt2.SetData(input[index1],input[index1+1]);
	pt3.SetData(input[index1+2],input[index1+3]);
	CalEndSeg3DPtNormalIndex(pt3,pt2,width,height,&outpt[(ptNum-1)*24],(ptNum-1)*4,&outputIndex[6+24*(ptNum-2)]);
	//index1 = 6+24*(ptNum-1);
	//index2 = (ptNum-1)*4;
	//outputIndex[index1++] = index2;
	//outputIndex[index1++] = index2+2;
	//outputIndex[index1++] = index2+1;
	//outputIndex[index1++] = index2+2;
	//outputIndex[index1++] = index2+3;
	//outputIndex[index1++] = index2+1;
}

void line2DSegBorderOp::CalLine3DBorderWithHead(float* input,int ptNum,float width,float height,float headWidth,float headLength,float* outpt,unsigned int* outputIndex)
{
	point2D pt1,pt2,pt3,out[2];
	pt1.SetData(input[0],input[1]);
	pt2.SetData(input[2],input[3]);

	CalStartSeg3DPtNormalIndex(pt1,pt2,width,height,outpt,outputIndex);
	float z = height/2;
	int index1,index2;
	vector2D vec2d[2];
	vector3D vecZ(0.0,0.0,1.0);
	vector3D vec3d,vec;
	for(int i=1;i<ptNum-1;i++)
	{
		pt3.SetData(input[(i+1)*2],input[(i+1)*2+1]);
		CalPtBorderPts(pt2,pt1,pt3,width,out[0],out[1],vec2d[0],vec2d[1]);
		index1 = 24*i;
		for(int j=0;j<2;j++)
		{
			//pos
			outpt[index1++] = out[j].x;
			outpt[index1++] = out[j].y;
			outpt[index1++] = z;
			//normal
			vec3d.SetData(vec2d[j]);
			vec = vec3d + vecZ;
			vec.Normalize();
			outpt[index1++] = vec.x;
			outpt[index1++] = vec.y;
			outpt[index1++] = vec.z;

			//pos
			outpt[index1++] = out[j].x;
			outpt[index1++] = out[j].y;
			outpt[index1++] = -z;
			//normal
			vec = vec3d - vecZ;
			vec.Normalize();
			outpt[index1++] = vec.x;
			outpt[index1++] = vec.y;
			outpt[index1++] = vec.z;
		}

		index1 = 6+24*(i-1);
		index2 = i*4;
		//up face
		outputIndex[index1++] = index2-4;
		outputIndex[index1++] = index2-2;
		outputIndex[index1++] = index2;
		outputIndex[index1++] = index2-2;
		outputIndex[index1++] = index2+2;
		outputIndex[index1++] = index2;
		//down face
		outputIndex[index1++] = index2-3;
		outputIndex[index1++] = index2+1;
		outputIndex[index1++] = index2-1;
		outputIndex[index1++] = index2+1;
		outputIndex[index1++] = index2+3;
		outputIndex[index1++] = index2-1;
		//left face
		outputIndex[index1++] = index2-4;
		outputIndex[index1++] = index2;
		outputIndex[index1++] = index2-3;
		outputIndex[index1++] = index2;
		outputIndex[index1++] = index2+1;
		outputIndex[index1++] = index2-3;
		//right face
		outputIndex[index1++] = index2-2;
		outputIndex[index1++] = index2-1;
		outputIndex[index1++] = index2+2;
		outputIndex[index1++] = index2-1;
		outputIndex[index1++] = index2+3;
		outputIndex[index1++] = index2+2;

		pt1 = pt2;
		pt2 = pt3;
	}
	//last face
	index1 = (ptNum-2)*2;
	pt2.SetData(input[index1],input[index1+1]);
	pt3.SetData(input[index1+2],input[index1+3]);
	CalEndSeg3DPtNormalIndex(pt3,pt2,width,height,&outpt[(ptNum-1)*24],(ptNum-1)*4,&outputIndex[6+24*(ptNum-2)]);
}

void line2DSegBorderOp::CalTriangle3DPtNormalIndex(const point2D& pt,const vector2D& dir,float width,float length,float height,float* outpt,unsigned int startIndex,unsigned int* outputIndex)
{
	point2D out[3];
	vector2D prepDir = dir.GetVerticalVec();
	Cal2PtAlongDir(pt,prepDir,width,out[0],out[1]);
	out[2] = pt + dir*length;

	vector2D dir21 = out[2] - out[1];
	vector2D prepDir21 = dir21.GetVerticalVec();

	vector2D dir02 = out[0] - out[2];
	vector2D prepDir02 = dir02.GetVerticalVec();

	vector3D vec[3],tmpVec;
	vec[0] = prepDir02 - dir;
	vec[1] = prepDir21 - dir;
	vec[2] = prepDir21 + prepDir02;
	vector3D vecZ(0.0,0.0,1.0);

	int index =0;
	float z = height/2;
	int tmp;
	for(int i=0;i<3;i++)
	{
		tmp = -1;
		for(int j=0;j<2;j++)
		{
			tmp = tmp*(-1);
			outpt[index++] = out[i].x;
			outpt[index++] = out[i].y;
			outpt[index++] = tmp*z;
			tmpVec = vec[i] + vecZ*tmp;
			tmpVec.Normalize();
			outpt[index++] = tmpVec.x;
			outpt[index++] = tmpVec.y;
			outpt[index++] = tmpVec.z;
		}
	}

	index = 0;
	//front
	//right
	//left
	int offset,offset1,offset2,offset3;
	for(int i=0;i<3;i++)
	{
		offset = i*2;
		offset1 = offset+1;
		offset2 = (offset+2)%6;
		offset3 = (offset+3)%6;
		outputIndex[index++] = startIndex + offset;
		outputIndex[index++] = startIndex + offset1;
		outputIndex[index++] = startIndex + offset2;
		outputIndex[index++] = startIndex + offset1;
		outputIndex[index++] = startIndex + offset3;
		outputIndex[index++] = startIndex + offset2;
	}
	//up
	outputIndex[index++] = startIndex ;
	outputIndex[index++] = startIndex + 2;
	outputIndex[index++] = startIndex + 4;
	//down
	outputIndex[index++] = startIndex + 1;
	outputIndex[index++] = startIndex + 5;
	outputIndex[index++] = startIndex + 3;
}
