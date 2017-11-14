#ifndef __HARMAN_ADAS_AFRAMEWORK_AGRAPGICS_GUIDELINETYPEYDEFINE_H_
#define __HARMAN_ADAS_AFRAMEWORK_AGRAPGICS_GUIDELINETYPEYDEFINE_H_
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#define	PVRTCOS(x)	PVRTFCOS(x)
#define	PVRTSIN(x)	PVRTFSIN(x)
#define	PVRTTAN(x)	PVRTFTAN(x)
#define	PVRTACOS(x)	PVRTFACOS(x)
#define	PVRTFCOS(x)	((float)cos(x))
#define	PVRTFSIN(x)	((float)sin(x))
#define	PVRTFTAN(x)	((float)tan(x))
#define	PVRTFACOS(x)	((float)acos(x))
#define VERTTYPEMUL(a,b) ((float)((a)*(b)))
#define VERTTYPEDIV(a,b) ((float)((a)/(b)))
#define VERTTYPEABS(a)	 ((float)(fabs(a)))
#define f2vt(x)						(x)
#define vt2f(x)						(x)
#define R_PI      3.1415926f
#define R_Deg2Rad(angle) ((float)( angle * R_PI / 180.0f ))
#define STEERING_WHEEL_DELTA 5
#define GUIDELINE_GROUP_NUM         9     //number of groups
#define GUIDELINE_WIDTH             (10) //the width in pixels of the line displayed
#define COLOR_RED                   {1.0,0.0,0.0}
#define COLOR_YELLOW                {1.0,1.0,0.0}
#define COLOR_GREEN                {0.0,1.0,0.0}
#define COLOR_PINK                {1.0,0.0,1.0}
#define COLOR_LIGNTBLUE                {0.1,0.69,0.78}
#define OVLAY_THICK_DIST_MARKS 0.08   //distance between two distance line which belong one group
#define OVLAY_NUM_DIST_MARKS 1  // the number of distance line of each group 
#define OVLAY_NUM_SIDE_LINE   2  //side line numbers
#define OVLAY_SUM_LINE_PER_GROUP   (OVLAY_NUM_DIST_MARKS + OVLAY_NUM_SIDE_LINE) 
#define OVLAY_TRACK_WIDTH 0.73 // length of each distance line
#define OVLAY_SIDE_WIDTH 0.72 //distance between two side lines
#define GUIDELINE_MARKER_STARTDIS    0.23    //start location of first distance line
#define OVLAY_DELTA_DIST_MARKS 0.3   // distance between two distance lines
#define DIST_PER_POINT_CLOSE	0.01
#define DIST_PER_POINT_FAR		0.5
#define	START_FAR_DIST			30		// distance per point is doubled at this range---desided by camera?
#define DIST_LINE_PTNUM         40
#define DIST_LINE_WIDTH         0.015 //side line thickness
#define SIDE_LINE_WIDTH         0.02//distance line thickness
#define PTELEMNUM 4
#define INPUTELEMENTNUM 2
#define INVERSE_REAR_RATIO_PRECISION 0.001
#define STEER_WHEEL_ANGLE_PRECISION 0.01
#define VERTTYPE float
#define PVRTMatrixRotationX	PVRTMatrixRotationXF
#define PVRTMatrixRotationY	PVRTMatrixRotationYF
#define PVRTMatrixRotationZ	PVRTMatrixRotationZF
#define VERTEX_ARRAY 0
#define TEXCOORD_ARRAY 1
#define glscreen_width 1280
#define glscreen_height 720

using namespace std;

typedef unsigned char  BYTE;

struct PVRTVec4;
struct PVRTVec3;
struct PVRTMat3;
struct PVRTMat4;


class PVRTMATRIX
{
public:
	float* operator [] (const int Row)
	{
		return &f[Row << 2];
	}
	float f[16];	/*!< Array of float */
};

void PVRTLinearEqSolve(VERTTYPE * const pRes, VERTTYPE ** const pSrc, const int nCnt);
void PVRTMatrixRotationXF(PVRTMATRIX &mOut,const float fAngle);
void PVRTMatrixRotationYF(PVRTMATRIX &mOut,const float fAngle);
void PVRTMatrixRotationZF(PVRTMATRIX &mOut,const float fAngle);


typedef struct
{
	float x;	/*!< x coordinate */
	float y;	/*!< y coordinate */
	float z;	/*!< z coordinate */
} PVRTVECTOR3;

typedef struct
{
	float x;	/*!< x coordinate */
	float y;	/*!< y coordinate */
	float z;	/*!< z coordinate */
	float w;	/*!< w coordinate */
} PVRTVECTOR4;

struct PVRTVec3 : public PVRTVECTOR3
{
	PVRTVec3() {}
	
	PVRTVec3(float fX, float fY, float fZ)
	{
		x = fX;	y = fY;	z = fZ;
	}
	
	PVRTVec3(const float fValue)
	{
		x = fValue; y = fValue; z = fValue;
	}
	
	PVRTVec3(const float* pVec)
	{
		x = (*pVec++); y = (*pVec++); z = *pVec;
	}
	
	PVRTVec3(const PVRTVec4& vec4);
	
	PVRTVec3 operator+(const PVRTVec3& rhs) const
	{
		PVRTVec3 out;
		out.x = x + rhs.x;
		out.y = y + rhs.y;
		out.z = z + rhs.z;
		return out;
	}
	
	PVRTVec3 operator-(const PVRTVec3& rhs) const
	{
		PVRTVec3 out;
		out.x = x - rhs.x;
		out.y = y - rhs.y;
		out.z = z - rhs.z;
		return out;
	}

	PVRTVec3& operator+=(const PVRTVec3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	
	PVRTVec3& operator-=(const PVRTVec3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	
	friend PVRTVec3 operator - (const PVRTVec3& rhs) { return PVRTVec3(rhs) *= f2vt(-1); }

	
	friend PVRTVec3 operator*(const float lhs, const PVRTVec3&  rhs)
	{
		PVRTVec3 out;
		out.x = VERTTYPEMUL(lhs, rhs.x);
		out.y = VERTTYPEMUL(lhs, rhs.y);
		out.z = VERTTYPEMUL(lhs, rhs.z);
		return out;
	}

	friend PVRTVec3 operator/(const float lhs, const PVRTVec3&  rhs)
	{
		PVRTVec3 out;
		out.x = VERTTYPEDIV(lhs, rhs.x);
		out.y = VERTTYPEDIV(lhs, rhs.y);
		out.z = VERTTYPEDIV(lhs, rhs.z);
		return out;
	}

	PVRTVec3 operator*(const PVRTMat3& rhs) const;
	
	
	
	PVRTVec3& operator*=(const PVRTMat3& rhs);
	
	
	PVRTVec3 operator*(const float& rhs) const
	{
		PVRTVec3 out;
		out.x = VERTTYPEMUL(x, rhs);
		out.y = VERTTYPEMUL(y, rhs);
		out.z = VERTTYPEMUL(z, rhs);
		return out;
	}

	
	PVRTVec3& operator*=(const float& rhs)
	{
		x = VERTTYPEMUL(x, rhs);
		y = VERTTYPEMUL(y, rhs);
		z = VERTTYPEMUL(z, rhs);
		return *this;
	}

	
	PVRTVec3 operator/(const float& rhs) const
	{
		PVRTVec3 out;
		out.x = VERTTYPEDIV(x, rhs);
		out.y = VERTTYPEDIV(y, rhs);
		out.z = VERTTYPEDIV(z, rhs);
		return out;
	}

	
	PVRTVec3& operator/=(const float& rhs)
	{
		x = VERTTYPEDIV(x, rhs);
		y = VERTTYPEDIV(y, rhs);
		z = VERTTYPEDIV(z, rhs);
		return *this;
	}

	bool operator==(const PVRTVec3& rhs) const
	{
		if (x != rhs.x) return false;
		if (y != rhs.y) return false;
		if (z != rhs.z) return false;
		return true;
	}

	bool operator!=(const PVRTVec3& rhs) const
	{
		if (x == rhs.x)
			return false;

		return true;
	}
	
	float lenSqr() const
	{
		return VERTTYPEMUL(x, x) + VERTTYPEMUL(y, y) + VERTTYPEMUL(z, z);
	}

	float length() const
	{
		return (float)f2vt(sqrt(vt2f(x)*vt2f(x) + vt2f(y)*vt2f(y) + vt2f(z)*vt2f(z)));
	}

	PVRTVec3 normalize()
	{
#if defined(PVRT_FIXED_POINT_ENABLE)
		// Scale vector by uniform value
		int n = PVRTABS(x) + PVRTABS(y) + PVRTABS(z);
		x = VERTTYPEDIV(x, n);
		y = VERTTYPEDIV(y, n);
		z = VERTTYPEDIV(z, n);

		// Calculate x2+y2+z2/sqrt(x2+y2+z2)
		int f = dot(*this);
		f = VERTTYPEDIV(PVRTF2X(1.0f), PVRTF2X(sqrt(PVRTX2F(f))));

		// Multiply vector components by f
		x = PVRTXMUL(x, f);
		y = PVRTXMUL(y, f);
		z = PVRTXMUL(z, f);
#else
		float len = length();
		x = VERTTYPEDIV(x, len);
		y = VERTTYPEDIV(y, len);
		z = VERTTYPEDIV(z, len);
#endif
		return *this;
	}

	PVRTVec3 normalized() const
	{
		PVRTVec3 out;
#if defined(PVRT_FIXED_POINT_ENABLE)
		// Scale vector by uniform value
		int n = PVRTABS(x) + PVRTABS(y) + PVRTABS(z);
		out.x = VERTTYPEDIV(x, n);
		out.y = VERTTYPEDIV(y, n);
		out.z = VERTTYPEDIV(z, n);

		// Calculate x2+y2+z2/sqrt(x2+y2+z2)
		int f = out.dot(out);
		f = VERTTYPEDIV(PVRTF2X(1.0f), PVRTF2X(sqrt(PVRTX2F(f))));

		// Multiply vector components by f
		out.x = PVRTXMUL(out.x, f);
		out.y = PVRTXMUL(out.y, f);
		out.z = PVRTXMUL(out.z, f);
#else
		float len = length();
		out.x = VERTTYPEDIV(x, len);
		out.y = VERTTYPEDIV(y, len);
		out.z = VERTTYPEDIV(z, len);
#endif
		return out;
	}

	float dot(const PVRTVec3& rhs)
	{
		return VERTTYPEMUL(x, rhs.x) + VERTTYPEMUL(y, rhs.y) + VERTTYPEMUL(z, rhs.z);
	}

	PVRTVec3 cross(const PVRTVec3& rhs)
	{
		PVRTVec3 out;
		out.x = VERTTYPEMUL(y, rhs.z) - VERTTYPEMUL(z, rhs.y);
		out.y = VERTTYPEMUL(z, rhs.x) - VERTTYPEMUL(x, rhs.z);
		out.z = VERTTYPEMUL(x, rhs.y) - VERTTYPEMUL(y, rhs.x);
		return out;
	}


	float *ptr() { return (float*)this; }
};



struct PVRTVec4 : public PVRTVECTOR4
{
	PVRTVec4() {}

	PVRTVec4(const float vec)
	{
		x = vec; y = vec; z = vec; w = vec;
	}

	PVRTVec4(float fX, float fY, float fZ, float fW)
	{
		x = fX;	y = fY;	z = fZ;	w = fW;
	}

	PVRTVec4(const PVRTVec3& vec3, float fW)
	{
		x = vec3.x;	y = vec3.y;	z = vec3.z;	w = fW;
	}


	PVRTVec4(float fX, const PVRTVec3& vec3)
	{
		x = fX;	y = vec3.x;	z = vec3.y;	w = vec3.z;
	}

	
	PVRTVec4(const float* pVec)
	{
		x = (*pVec++); y = (*pVec++); z = (*pVec++); w = *pVec;
	}

	PVRTVec4 operator+(const PVRTVec4& rhs) const
	{
		PVRTVec4 out;
		out.x = x + rhs.x;
		out.y = y + rhs.y;
		out.z = z + rhs.z;
		out.w = w + rhs.w;
		return out;
	}

	PVRTVec4 operator-(const PVRTVec4& rhs) const
	{
		PVRTVec4 out;
		out.x = x - rhs.x;
		out.y = y - rhs.y;
		out.z = z - rhs.z;
		out.w = w - rhs.w;
		return out;
	}

	PVRTVec4& operator+=(const PVRTVec4& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	PVRTVec4& operator-=(const PVRTVec4& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	PVRTVec4 operator*(const PVRTMat4& rhs) const;

	
	PVRTVec4& operator*=(const PVRTMat4& rhs);
	

	PVRTVec4 operator*(const float& rhs) const
	{
		PVRTVec4 out;
		out.x = VERTTYPEMUL(x, rhs);
		out.y = VERTTYPEMUL(y, rhs);
		out.z = VERTTYPEMUL(z, rhs);
		out.w = VERTTYPEMUL(w, rhs);
		return out;
	}

	PVRTVec4& operator*=(const float& rhs)
	{
		x = VERTTYPEMUL(x, rhs);
		y = VERTTYPEMUL(y, rhs);
		z = VERTTYPEMUL(z, rhs);
		w = VERTTYPEMUL(w, rhs);
		return *this;
	}

	PVRTVec4 operator/(const float& rhs) const
	{
		PVRTVec4 out;
		out.x = VERTTYPEDIV(x, rhs);
		out.y = VERTTYPEDIV(y, rhs);
		out.z = VERTTYPEDIV(z, rhs);
		out.w = VERTTYPEDIV(w, rhs);
		return out;
	}

	PVRTVec4& operator/=(const float& rhs)
	{
		x = VERTTYPEDIV(x, rhs);
		y = VERTTYPEDIV(y, rhs);
		z = VERTTYPEDIV(z, rhs);
		w = VERTTYPEDIV(w, rhs);
		return *this;
	}

	friend PVRTVec4 operator*(const float lhs, const PVRTVec4&  rhs)
	{
		PVRTVec4 out;
		out.x = VERTTYPEMUL(lhs, rhs.x);
		out.y = VERTTYPEMUL(lhs, rhs.y);
		out.z = VERTTYPEMUL(lhs, rhs.z);
		out.w = VERTTYPEMUL(lhs, rhs.w);
		return out;
	}

	bool operator==(const PVRTVec4& rhs) const
	{
		if (x != rhs.x) return false;
		if (y != rhs.y) return false;
		if (z != rhs.z) return false;
		if (w != rhs.w) return false;
		return true;
	}

	bool operator!=(const PVRTVec3& rhs) const
	{
		if (x == rhs.x)
			return false;

		return true;
	}

	float lenSqr() const
	{
		return VERTTYPEMUL(x, x) + VERTTYPEMUL(y, y) + VERTTYPEMUL(z, z) + VERTTYPEMUL(w, w);
	}

	float length() const
	{
		return (float)f2vt(sqrt(vt2f(x)*vt2f(x) + vt2f(y)*vt2f(y) + vt2f(z)*vt2f(z) + vt2f(w)*vt2f(w)));
	}

	PVRTVec4 normalize()
	{
		float len = length();
		x = VERTTYPEDIV(x, len);
		y = VERTTYPEDIV(y, len);
		z = VERTTYPEDIV(z, len);
		w = VERTTYPEDIV(w, len);
		return *this;
	}
	
	PVRTVec4 normalized() const
	{
		PVRTVec4 out;
		float len = length();
		out.x = VERTTYPEDIV(x, len);
		out.y = VERTTYPEDIV(y, len);
		out.z = VERTTYPEDIV(z, len);
		out.w = VERTTYPEDIV(w, len);
		return out;
	}

	float dot(const PVRTVec4& rhs)
	{
		return VERTTYPEMUL(x, rhs.x) + VERTTYPEMUL(y, rhs.y) + VERTTYPEMUL(z, rhs.z) + VERTTYPEMUL(w, rhs.w);
	}

	
	float *ptr() { return (float*)this; }
};



struct PVRTMat4 : public PVRTMATRIX
{
	PVRTMat4() {}
	
	PVRTMat4(float m0, float m1, float m2, float m3,
		float m4, float m5, float m6, float m7,
		float m8, float m9, float m10, float m11,
		float m12, float m13, float m14, float m15)
	{
		f[0] = m0; f[1] = m1; f[2] = m2; f[3] = m3;
		f[4] = m4; f[5] = m5; f[6] = m6; f[7] = m7;
		f[8] = m8; f[9] = m9; f[10] = m10; f[11] = m11;
		f[12] = m12; f[13] = m13; f[14] = m14; f[15] = m15;
	}
	
	PVRTMat4(const float* mat)
	{
		float* ptr = f;
		for (int i = 0; i<16; i++)
		{
			(*ptr++) = (*mat++);
		}
	}

	float& operator()(const int r, const int c)
	{
		return f[c * 4 + r];
	}

	
	const float& operator()(const int r, const int c) const
	{
		return f[c * 4 + r];
	}

	PVRTMat4 operator*(const PVRTMat4& rhs) const;

	
	PVRTMat4 operator+(const PVRTMat4& rhs) const
	{
		PVRTMat4 out;
		float const *lptr = f, *rptr = rhs.f;
		float *outptr = out.f;
		for (int i = 0; i<16; i++)
		{
			(*outptr++) = (*lptr++) + (*rptr++);
		}
		return out;
	}

	PVRTMat4 operator-(const PVRTMat4& rhs) const
	{
		PVRTMat4 out;
		for (int i = 0; i<16; i++)
		{
			out.f[i] = f[i] - rhs.f[i];
		}
		return out;
	}

	PVRTMat4& operator+=(const PVRTMat4& rhs)
	{
		float *lptr = f;
		float const *rptr = rhs.f;
		for (int i = 0; i<16; i++)
		{
			(*lptr++) += (*rptr++);
		}
		return *this;
	}


	PVRTMat4& operator-=(const PVRTMat4& rhs)
	{
		float *lptr = f;
		float const *rptr = rhs.f;
		for (int i = 0; i<16; i++)
		{
			(*lptr++) -= (*rptr++);
		}
		return *this;
	}


	PVRTMat4& operator*=(const PVRTMat4& rhs)
	{
		PVRTMat4 result;
		// col 0
		result.f[0] = VERTTYPEMUL(f[0], rhs.f[0]) + VERTTYPEMUL(f[4], rhs.f[1]) + VERTTYPEMUL(f[8], rhs.f[2]) + VERTTYPEMUL(f[12], rhs.f[3]);
		result.f[1] = VERTTYPEMUL(f[1], rhs.f[0]) + VERTTYPEMUL(f[5], rhs.f[1]) + VERTTYPEMUL(f[9], rhs.f[2]) + VERTTYPEMUL(f[13], rhs.f[3]);
		result.f[2] = VERTTYPEMUL(f[2], rhs.f[0]) + VERTTYPEMUL(f[6], rhs.f[1]) + VERTTYPEMUL(f[10], rhs.f[2]) + VERTTYPEMUL(f[14], rhs.f[3]);
		result.f[3] = VERTTYPEMUL(f[3], rhs.f[0]) + VERTTYPEMUL(f[7], rhs.f[1]) + VERTTYPEMUL(f[11], rhs.f[2]) + VERTTYPEMUL(f[15], rhs.f[3]);

		// col 1
		result.f[4] = VERTTYPEMUL(f[0], rhs.f[4]) + VERTTYPEMUL(f[4], rhs.f[5]) + VERTTYPEMUL(f[8], rhs.f[6]) + VERTTYPEMUL(f[12], rhs.f[7]);
		result.f[5] = VERTTYPEMUL(f[1], rhs.f[4]) + VERTTYPEMUL(f[5], rhs.f[5]) + VERTTYPEMUL(f[9], rhs.f[6]) + VERTTYPEMUL(f[13], rhs.f[7]);
		result.f[6] = VERTTYPEMUL(f[2], rhs.f[4]) + VERTTYPEMUL(f[6], rhs.f[5]) + VERTTYPEMUL(f[10], rhs.f[6]) + VERTTYPEMUL(f[14], rhs.f[7]);
		result.f[7] = VERTTYPEMUL(f[3], rhs.f[4]) + VERTTYPEMUL(f[7], rhs.f[5]) + VERTTYPEMUL(f[11], rhs.f[6]) + VERTTYPEMUL(f[15], rhs.f[7]);

		// col 2
		result.f[8] = VERTTYPEMUL(f[0], rhs.f[8]) + VERTTYPEMUL(f[4], rhs.f[9]) + VERTTYPEMUL(f[8], rhs.f[10]) + VERTTYPEMUL(f[12], rhs.f[11]);
		result.f[9] = VERTTYPEMUL(f[1], rhs.f[8]) + VERTTYPEMUL(f[5], rhs.f[9]) + VERTTYPEMUL(f[9], rhs.f[10]) + VERTTYPEMUL(f[13], rhs.f[11]);
		result.f[10] = VERTTYPEMUL(f[2], rhs.f[8]) + VERTTYPEMUL(f[6], rhs.f[9]) + VERTTYPEMUL(f[10], rhs.f[10]) + VERTTYPEMUL(f[14], rhs.f[11]);
		result.f[11] = VERTTYPEMUL(f[3], rhs.f[8]) + VERTTYPEMUL(f[7], rhs.f[9]) + VERTTYPEMUL(f[11], rhs.f[10]) + VERTTYPEMUL(f[15], rhs.f[11]);

		// col 3
		result.f[12] = VERTTYPEMUL(f[0], rhs.f[12]) + VERTTYPEMUL(f[4], rhs.f[13]) + VERTTYPEMUL(f[8], rhs.f[14]) + VERTTYPEMUL(f[12], rhs.f[15]);
		result.f[13] = VERTTYPEMUL(f[1], rhs.f[12]) + VERTTYPEMUL(f[5], rhs.f[13]) + VERTTYPEMUL(f[9], rhs.f[14]) + VERTTYPEMUL(f[13], rhs.f[15]);
		result.f[14] = VERTTYPEMUL(f[2], rhs.f[12]) + VERTTYPEMUL(f[6], rhs.f[13]) + VERTTYPEMUL(f[10], rhs.f[14]) + VERTTYPEMUL(f[14], rhs.f[15]);
		result.f[15] = VERTTYPEMUL(f[3], rhs.f[12]) + VERTTYPEMUL(f[7], rhs.f[13]) + VERTTYPEMUL(f[11], rhs.f[14]) + VERTTYPEMUL(f[15], rhs.f[15]);

		*this = result;
		return *this;
	}

	PVRTMat4& operator*(const float rhs)
	{
		for (int i = 0; i<16; ++i)
		{
			f[i] *= rhs;
		}
		return *this;
	}

	PVRTMat4& operator*=(const float rhs)
	{
		for (int i = 0; i<16; ++i)
		{
			f[i] *= rhs;
		}
		return *this;
	}


	PVRTMat4& operator=(const PVRTMat4& rhs)
	{
		for (int i = 0; i<16; ++i)
		{
			f[i] = rhs.f[i];
		}
		return *this;
	}
	
	PVRTVec4 operator*(const PVRTVec4& rhs) const
	{
		PVRTVec4 out;
		out.x = VERTTYPEMUL(rhs.x, f[0]) + VERTTYPEMUL(rhs.y, f[4]) + VERTTYPEMUL(rhs.z, f[8]) + VERTTYPEMUL(rhs.w, f[12]);
		out.y = VERTTYPEMUL(rhs.x, f[1]) + VERTTYPEMUL(rhs.y, f[5]) + VERTTYPEMUL(rhs.z, f[9]) + VERTTYPEMUL(rhs.w, f[13]);
		out.z = VERTTYPEMUL(rhs.x, f[2]) + VERTTYPEMUL(rhs.y, f[6]) + VERTTYPEMUL(rhs.z, f[10]) + VERTTYPEMUL(rhs.w, f[14]);
		out.w = VERTTYPEMUL(rhs.x, f[3]) + VERTTYPEMUL(rhs.y, f[7]) + VERTTYPEMUL(rhs.z, f[11]) + VERTTYPEMUL(rhs.w, f[15]);

		return out;
	}

	
	PVRTVec4 operator*=(const PVRTVec4& rhs) const
	{
		PVRTVec4 out;
		out.x = VERTTYPEMUL(rhs.x, f[0]) + VERTTYPEMUL(rhs.y, f[4]) + VERTTYPEMUL(rhs.z, f[8]) + VERTTYPEMUL(rhs.w, f[12]);
		out.y = VERTTYPEMUL(rhs.x, f[1]) + VERTTYPEMUL(rhs.y, f[5]) + VERTTYPEMUL(rhs.z, f[9]) + VERTTYPEMUL(rhs.w, f[13]);
		out.z = VERTTYPEMUL(rhs.x, f[2]) + VERTTYPEMUL(rhs.y, f[6]) + VERTTYPEMUL(rhs.z, f[10]) + VERTTYPEMUL(rhs.w, f[14]);
		out.w = VERTTYPEMUL(rhs.x, f[3]) + VERTTYPEMUL(rhs.y, f[7]) + VERTTYPEMUL(rhs.z, f[11]) + VERTTYPEMUL(rhs.w, f[15]);

		return out;
	}

	PVRTMat4 inverse() const;

	PVRTMat4 inverseEx() const
	{
		PVRTMat4 out;
		float 		*ppRows[4];
		float 		pRes[4];
		float 		pIn[20];
		int				i, j;

		for (i = 0; i < 4; ++i)
			ppRows[i] = &pIn[i * 5];

		/* Solve 4 sets of 4 linear equations */
		for (i = 0; i < 4; ++i)
		{
			for (j = 0; j < 4; ++j)
			{
				ppRows[j][0] = PVRTMat4::Identity().f[i + 4 * j];
				memcpy(&ppRows[j][1], &f[j * 4], 4 * sizeof(float));
			}

			PVRTLinearEqSolve(pRes, (float**)ppRows, 4);

			for (j = 0; j < 4; ++j)
			{
				out.f[i + 4 * j] = pRes[j];
			}
		}

		return out;
	}

	PVRTMat4 transpose() const
	{
		PVRTMat4 out;
		out.f[0] = f[0];		out.f[1] = f[4];		out.f[2] = f[8];		out.f[3] = f[12];
		out.f[4] = f[1];		out.f[5] = f[5];		out.f[6] = f[9];		out.f[7] = f[13];
		out.f[8] = f[2];		out.f[9] = f[6];		out.f[10] = f[10];		out.f[11] = f[14];
		out.f[12] = f[3];		out.f[13] = f[7];		out.f[14] = f[11];		out.f[15] = f[15];
		return out;
	}


	PVRTMat4& postTranslate(float tx, float ty, float tz)
	{
		f[12] += VERTTYPEMUL(tx, f[0]) + VERTTYPEMUL(ty, f[4]) + VERTTYPEMUL(tz, f[8]);
		f[13] += VERTTYPEMUL(tx, f[1]) + VERTTYPEMUL(ty, f[5]) + VERTTYPEMUL(tz, f[9]);
		f[14] += VERTTYPEMUL(tx, f[2]) + VERTTYPEMUL(ty, f[6]) + VERTTYPEMUL(tz, f[10]);
		f[15] += VERTTYPEMUL(tx, f[3]) + VERTTYPEMUL(ty, f[7]) + VERTTYPEMUL(tz, f[11]);

		//			col(3) += tx * col(0) + ty * col(1) + tz * col(2);
		return *this;
	}


	PVRTMat4& postTranslate(const PVRTVec3& tvec)
	{
		return postTranslate(tvec.x, tvec.y, tvec.z);
	}

	
	PVRTMat4& preTranslate(float tx, float ty, float tz)
	{
		f[0] += VERTTYPEMUL(f[3], tx);	f[4] += VERTTYPEMUL(f[7], tx);	f[8] += VERTTYPEMUL(f[11], tx);	f[12] += VERTTYPEMUL(f[15], tx);
		f[1] += VERTTYPEMUL(f[3], ty);	f[5] += VERTTYPEMUL(f[7], ty);	f[9] += VERTTYPEMUL(f[11], ty);	f[13] += VERTTYPEMUL(f[15], ty);
		f[2] += VERTTYPEMUL(f[3], tz);	f[6] += VERTTYPEMUL(f[7], tz);	f[10] += VERTTYPEMUL(f[11], tz);	f[14] += VERTTYPEMUL(f[15], tz);

		//			row(0) += tx * row(3);
		//			row(1) += ty * row(3);
		//			row(2) += tz * row(3);
		return *this;
	}


	PVRTMat4& preTranslate(const PVRTVec3& tvec)
	{
		return preTranslate(tvec.x, tvec.y, tvec.z);
	}

	float *ptr() { return (float*)&f; }

	
	static PVRTMat4 Identity()
	{
		PVRTMat4 out;
		out.f[0] = f2vt(1); out.f[1] = 0; out.f[2] = 0; out.f[3] = 0;
		out.f[4] = 0; out.f[5] = f2vt(1); out.f[6] = 0; out.f[7] = 0;
		out.f[8] = 0; out.f[9] = 0; out.f[10] = f2vt(1); out.f[11] = 0;
		out.f[12] = 0; out.f[13] = 0; out.f[14] = 0; out.f[15] = f2vt(1);
		return out;
	}

	static PVRTMat4 RotationX(VERTTYPE angle);
	
	static PVRTMat4 RotationY(VERTTYPE angle);
	
	static PVRTMat4 RotationZ(VERTTYPE angle);

	
	static PVRTMat4 Scale(const float fx, const float fy, const float fz)
	{
		return PVRTMat4(fx, 0, 0, 0,
			0, fy, 0, 0,
			0, 0, fz, 0,
			0, 0, 0, f2vt(1));
	}

	static PVRTMat4 Translation(const float tx, const float ty, const float tz)
	{
		return PVRTMat4(f2vt(1), 0, 0, 0,
			0, f2vt(1), 0, 0,
			0, 0, f2vt(1), 0,
			tx, ty, tz, f2vt(1));
	}

	enum eClipspace { OGL, D3D };

	
	static PVRTMat4 Ortho(float left, float top, float right,
		float bottom, float nearPlane, float farPlane, const eClipspace cs, bool bRotate = false)
	{
		float rcplmr = VERTTYPEDIV(float(1), (left - right));
		float rcpbmt = VERTTYPEDIV(float(1), (bottom - top));
		float rcpnmf = VERTTYPEDIV(float(1), (nearPlane - farPlane));

		PVRTMat4 result;

		if (bRotate)
		{
			result.f[0] = 0;		result.f[4] = VERTTYPEMUL(2, rcplmr); result.f[8] = 0; result.f[12] = VERTTYPEMUL(-(right + left), rcplmr);
			result.f[1] = VERTTYPEMUL(-2, rcpbmt);	result.f[5] = 0;		result.f[9] = 0;	result.f[13] = VERTTYPEMUL((top + bottom), rcpbmt);
		}
		else
		{
			result.f[0] = VERTTYPEMUL(-2, rcplmr);	result.f[4] = 0; result.f[8] = 0; result.f[12] = VERTTYPEMUL(right + left, rcplmr);
			result.f[1] = 0;		result.f[5] = VERTTYPEMUL(-2, rcpbmt);	result.f[9] = 0;	result.f[13] = VERTTYPEMUL((top + bottom), rcpbmt);
		}
		if (cs == D3D)
		{
			result.f[2] = 0;	result.f[6] = 0;	result.f[10] = -rcpnmf;	result.f[14] = VERTTYPEMUL(nearPlane, rcpnmf);
		}
		else
		{
			result.f[2] = 0;	result.f[6] = 0;	result.f[10] = VERTTYPEMUL(-2, rcpnmf);	result.f[14] = VERTTYPEMUL(nearPlane + farPlane, rcpnmf);
		}
		result.f[3] = 0;	result.f[7] = 0;	result.f[11] = 0;	result.f[15] = 1;

		return result;
	}


	static PVRTMat4 LookAtRH(const PVRTVec3& vEye, const PVRTVec3& vAt, const PVRTVec3& vUp)
	{
		return LookAt(vEye, vAt, vUp, true);
	}
	
	static PVRTMat4 LookAtLH(const PVRTVec3& vEye, const PVRTVec3& vAt, const PVRTVec3& vUp)
	{
		return LookAt(vEye, vAt, vUp, false);
	}


	static PVRTMat4 PerspectiveRH(float width, float height, float nearPlane,float farPlane, const eClipspace cs, bool bRotate = false)
	{
		return Perspective(width, height, nearPlane, farPlane, cs, true, bRotate);
	}

	
	static PVRTMat4 PerspectiveLH(float width, float height, float nearPlane, float farPlane, const eClipspace cs, bool bRotate = false)
	{
		return Perspective(width, height, nearPlane, farPlane, cs, false, bRotate);
	}

	
	static PVRTMat4 PerspectiveFloatDepthRH(float width, float height, float nearPlane, const eClipspace cs, bool bRotate = false)
	{
		return PerspectiveFloatDepth(width, height, nearPlane, cs, true, bRotate);
	}

	
	static PVRTMat4 PerspectiveFloatDepthLH(float width, float height, float nearPlane, const eClipspace cs, bool bRotate = false)
	{
		return PerspectiveFloatDepth(width, height, nearPlane, cs, false, bRotate);
	}

	
	static PVRTMat4 PerspectiveFovRH(float fovy, float aspect, float nearPlane, float farPlane, const eClipspace cs, bool bRotate = false)
	{
		return PerspectiveFov(fovy, aspect, nearPlane, farPlane, cs, true, bRotate);
	}
	
	static PVRTMat4 PerspectiveFovLH(float fovy, float aspect, float nearPlane, float farPlane, const eClipspace cs, bool bRotate = false)
	{
		return PerspectiveFov(fovy, aspect, nearPlane, farPlane, cs, false, bRotate);
	}

	
	static PVRTMat4 PerspectiveFovFloatDepthRH(float fovy, float aspect, float nearPlane, const eClipspace cs, bool bRotate = false)
	{
		return PerspectiveFovFloatDepth(fovy, aspect, nearPlane, cs, true, bRotate);
	}
	
	static PVRTMat4 PerspectiveFovFloatDepthLH(float fovy, float aspect, float nearPlane, const eClipspace cs, bool bRotate = false)
	{
		return PerspectiveFovFloatDepth(fovy, aspect, nearPlane, cs, false, bRotate);
	}

	
	static PVRTMat4 LookAt(const PVRTVec3& vEye, const PVRTVec3& vAt, const PVRTVec3& vUp, bool bRightHanded)
	{
		PVRTVec3 vForward, vUpNorm, vSide;
		PVRTMat4 result;

		vForward = (bRightHanded) ? vEye - vAt : vAt - vEye;

		vForward.normalize();
		vUpNorm = vUp.normalized();
		vSide = vUpNorm.cross(vForward);
		vUpNorm = vForward.cross(vSide);

		result.f[0] = vSide.x;	result.f[4] = vSide.y;	result.f[8] = vSide.z;		result.f[12] = 0;
		result.f[1] = vUpNorm.x;	result.f[5] = vUpNorm.y;	result.f[9] = vUpNorm.z;		result.f[13] = 0;
		result.f[2] = vForward.x; result.f[6] = vForward.y;	result.f[10] = vForward.z;	result.f[14] = 0;
		result.f[3] = 0;			result.f[7] = 0;			result.f[11] = 0;				result.f[15] = f2vt(1);


		result.postTranslate(-vEye);
		return result;
	}

	
	static PVRTMat4 Perspective(
		float width, float height,
		float nearPlane, float farPlane,
		const eClipspace cs,
		bool bRightHanded,
		bool bRotate = false)
	{
		float n2 = VERTTYPEMUL(f2vt(2), nearPlane);
		float rcpnmf = VERTTYPEDIV(f2vt(1), (nearPlane - farPlane));

		PVRTMat4 result;
		if (bRotate)
		{
			result.f[0] = 0;	result.f[4] = VERTTYPEDIV(-n2, width);	result.f[8] = 0;	result.f[12] = 0;
			result.f[1] = VERTTYPEDIV(n2, height);	result.f[5] = 0;	result.f[9] = 0;	result.f[13] = 0;
		}
		else
		{
			result.f[0] = VERTTYPEDIV(n2, width);	result.f[4] = 0;	result.f[8] = 0;	result.f[12] = 0;
			result.f[1] = 0;	result.f[5] = VERTTYPEDIV(n2, height);	result.f[9] = 0;	result.f[13] = 0;
		}
		if (cs == D3D)
		{
			result.f[2] = 0;	result.f[6] = 0;	result.f[10] = VERTTYPEMUL(farPlane, rcpnmf);	result.f[14] = VERTTYPEMUL(VERTTYPEMUL(farPlane, rcpnmf), nearPlane);
		}
		else
		{
			result.f[2] = 0;	result.f[6] = 0;	result.f[10] = VERTTYPEMUL(farPlane + nearPlane, rcpnmf);	result.f[14] = VERTTYPEMUL(VERTTYPEMUL(farPlane, rcpnmf), n2);
		}
		result.f[3] = 0;	result.f[7] = 0;	result.f[11] = f2vt(-1);	result.f[15] = 0;

		if (!bRightHanded)
		{
			result.f[10] = VERTTYPEMUL(result.f[10], f2vt(-1));
			result.f[11] = f2vt(1);
		}

		return result;
	}

	
	static PVRTMat4 PerspectiveFloatDepth(
		float width, float height,
		float nearPlane,
		const eClipspace cs,
		bool bRightHanded,
		bool bRotate = false)
	{
		float n2 = VERTTYPEMUL(2, nearPlane);

		PVRTMat4 result;
		if (bRotate)
		{
			result.f[0] = 0;	result.f[4] = VERTTYPEDIV(-n2, width);	result.f[8] = 0;	result.f[12] = 0;
			result.f[1] = VERTTYPEDIV(n2, height);	result.f[5] = 0;	result.f[9] = 0;	result.f[13] = 0;
		}
		else
		{
			result.f[0] = VERTTYPEDIV(n2, width);	result.f[4] = 0;	result.f[8] = 0;	result.f[12] = 0;
			result.f[1] = 0;	result.f[5] = VERTTYPEDIV(n2, height);	result.f[9] = 0;	result.f[13] = 0;
		}
		if (cs == D3D)
		{
			result.f[2] = 0;	result.f[6] = 0;	result.f[10] = 0;	result.f[14] = nearPlane;
		}
		else
		{
			result.f[2] = 0;	result.f[6] = 0;	result.f[10] = (bRightHanded ? (float)1 : (float)-1);	result.f[14] = n2;
		}
		result.f[3] = (float)0;	result.f[7] = (float)0;	result.f[11] = (bRightHanded ? (float)-1 : (float)1);	result.f[15] = (float)0;

		return result;
	}

	static PVRTMat4 PerspectiveFov(
		float fovy, float aspect,
		float nearPlane, float farPlane,
		const eClipspace cs,
		bool bRightHanded,
		bool bRotate = false)
	{
		float height = VERTTYPEMUL(VERTTYPEMUL(f2vt(2.0f), nearPlane), PVRTTAN(VERTTYPEMUL(fovy, f2vt(0.5f))));
		if (bRotate) return Perspective(height, VERTTYPEDIV(height, aspect), nearPlane, farPlane, cs, bRightHanded, bRotate);
		return Perspective(VERTTYPEMUL(height, aspect), height, nearPlane, farPlane, cs, bRightHanded, bRotate);
	}

	
	static PVRTMat4 PerspectiveFovFloatDepth(
		float fovy, float aspect,
		float nearPlane,
		const eClipspace cs,
		bool bRightHanded,
		bool bRotate = false)
	{
		float height = VERTTYPEMUL(VERTTYPEMUL(2, nearPlane), PVRTTAN(VERTTYPEMUL(fovy, 0.5)));
		if (bRotate) return PerspectiveFloatDepth(height, VERTTYPEDIV(height, aspect), nearPlane, cs, bRightHanded, bRotate);
		return PerspectiveFloatDepth(VERTTYPEMUL(height, aspect), height, nearPlane, cs, bRightHanded, bRotate);
	}
};


class PVRTMATRIX3
{
public:
	float* operator [] (const int Row)
	{
		return &f[Row * 3];
	}
	float f[9];	/*!< Array of float */
};

struct PVRTMat3 : public PVRTMATRIX3
{
	PVRTMat3() {}
	
	PVRTMat3(const float* pMat)
	{
		float* ptr = f;
		for (int i = 0; i<9; i++)
		{
			(*ptr++) = (*pMat++);
		}
	}

	PVRTMat3(float m0, float m1, float m2,
		float m3, float m4, float m5,
		float m6, float m7, float m8)
	{
		f[0] = m0; f[1] = m1; f[2] = m2;
		f[3] = m3; f[4] = m4; f[5] = m5;
		f[6] = m6; f[7] = m7; f[8] = m8;
	}

	
	PVRTMat3(const PVRTMat4& mat);

	float& operator()(const int row, const int column)
	{
		return f[column * 3 + row];
	}
	
	const float& operator()(const int row, const int column) const
	{
		return f[column * 3 + row];
	}

	
	PVRTMat3 operator*(const PVRTMat3& rhs) const
	{
		PVRTMat3 out;
		// col 1
		out.f[0] = VERTTYPEMUL(f[0], rhs.f[0]) + VERTTYPEMUL(f[3], rhs.f[1]) + VERTTYPEMUL(f[6], rhs.f[2]);
		out.f[1] = VERTTYPEMUL(f[1], rhs.f[0]) + VERTTYPEMUL(f[4], rhs.f[1]) + VERTTYPEMUL(f[7], rhs.f[2]);
		out.f[2] = VERTTYPEMUL(f[2], rhs.f[0]) + VERTTYPEMUL(f[5], rhs.f[1]) + VERTTYPEMUL(f[8], rhs.f[2]);

		// col 2
		out.f[3] = VERTTYPEMUL(f[0], rhs.f[3]) + VERTTYPEMUL(f[3], rhs.f[4]) + VERTTYPEMUL(f[6], rhs.f[5]);
		out.f[4] = VERTTYPEMUL(f[1], rhs.f[3]) + VERTTYPEMUL(f[4], rhs.f[4]) + VERTTYPEMUL(f[7], rhs.f[5]);
		out.f[5] = VERTTYPEMUL(f[2], rhs.f[3]) + VERTTYPEMUL(f[5], rhs.f[4]) + VERTTYPEMUL(f[8], rhs.f[5]);

		// col3
		out.f[6] = VERTTYPEMUL(f[0], rhs.f[6]) + VERTTYPEMUL(f[3], rhs.f[7]) + VERTTYPEMUL(f[6], rhs.f[8]);
		out.f[7] = VERTTYPEMUL(f[1], rhs.f[6]) + VERTTYPEMUL(f[4], rhs.f[7]) + VERTTYPEMUL(f[7], rhs.f[8]);
		out.f[8] = VERTTYPEMUL(f[2], rhs.f[6]) + VERTTYPEMUL(f[5], rhs.f[7]) + VERTTYPEMUL(f[8], rhs.f[8]);
		return out;
	}

	
	PVRTMat3 operator+(const PVRTMat3& rhs) const
	{
		PVRTMat3 out;
		float const *lptr = f, *rptr = rhs.f;
		float *outptr = out.f;
		for (int i = 0; i<9; i++)
		{
			(*outptr++) = (*lptr++) + (*rptr++);
		}
		return out;
	}

	PVRTMat3 operator-(const PVRTMat3& rhs) const
	{
		PVRTMat3 out;
		float const *lptr = f, *rptr = rhs.f;
		float *outptr = out.f;
		for (int i = 0; i<9; i++)
		{
			(*outptr++) = (*lptr++) - (*rptr++);
		}
		return out;
	}

	PVRTMat3& operator+=(const PVRTMat3& rhs)
	{
		float *lptr = f;
		float const *rptr = rhs.f;
		for (int i = 0; i<9; i++)
		{
			(*lptr++) += (*rptr++);
		}
		return *this;
	}

	PVRTMat3& operator-=(const PVRTMat3& rhs)
	{
		float *lptr = f;
		float const *rptr = rhs.f;
		for (int i = 0; i<9; i++)
		{
			(*lptr++) -= (*rptr++);
		}
		return *this;
	}

	PVRTMat3& operator*=(const PVRTMat3& rhs)
	{
		PVRTMat3 out;
		// col 1
		out.f[0] = VERTTYPEMUL(f[0], rhs.f[0]) + VERTTYPEMUL(f[3], rhs.f[1]) + VERTTYPEMUL(f[6], rhs.f[2]);
		out.f[1] = VERTTYPEMUL(f[1], rhs.f[0]) + VERTTYPEMUL(f[4], rhs.f[1]) + VERTTYPEMUL(f[7], rhs.f[2]);
		out.f[2] = VERTTYPEMUL(f[2], rhs.f[0]) + VERTTYPEMUL(f[5], rhs.f[1]) + VERTTYPEMUL(f[8], rhs.f[2]);

		// col 2
		out.f[3] = VERTTYPEMUL(f[0], rhs.f[3]) + VERTTYPEMUL(f[3], rhs.f[4]) + VERTTYPEMUL(f[6], rhs.f[5]);
		out.f[4] = VERTTYPEMUL(f[1], rhs.f[3]) + VERTTYPEMUL(f[4], rhs.f[4]) + VERTTYPEMUL(f[7], rhs.f[5]);
		out.f[5] = VERTTYPEMUL(f[2], rhs.f[3]) + VERTTYPEMUL(f[5], rhs.f[4]) + VERTTYPEMUL(f[8], rhs.f[5]);

		// col3
		out.f[6] = VERTTYPEMUL(f[0], rhs.f[6]) + VERTTYPEMUL(f[3], rhs.f[7]) + VERTTYPEMUL(f[6], rhs.f[8]);
		out.f[7] = VERTTYPEMUL(f[1], rhs.f[6]) + VERTTYPEMUL(f[4], rhs.f[7]) + VERTTYPEMUL(f[7], rhs.f[8]);
		out.f[8] = VERTTYPEMUL(f[2], rhs.f[6]) + VERTTYPEMUL(f[5], rhs.f[7]) + VERTTYPEMUL(f[8], rhs.f[8]);
		*this = out;
		return *this;
	}

	PVRTMat3& operator*(const float rhs)
	{
		for (int i = 0; i<9; ++i)
		{
			f[i] *= rhs;
		}
		return *this;
	}

	PVRTMat3& operator*=(const float rhs)
	{
		for (int i = 0; i<9; ++i)
		{
			f[i] *= rhs;
		}
		return *this;
	}

	PVRTVec3 operator*(const PVRTVec3& rhs) const
	{
		PVRTVec3 out;
		out.x = VERTTYPEMUL(rhs.x, f[0]) + VERTTYPEMUL(rhs.y, f[3]) + VERTTYPEMUL(rhs.z, f[6]);
		out.y = VERTTYPEMUL(rhs.x, f[1]) + VERTTYPEMUL(rhs.y, f[4]) + VERTTYPEMUL(rhs.z, f[7]);
		out.z = VERTTYPEMUL(rhs.x, f[2]) + VERTTYPEMUL(rhs.y, f[5]) + VERTTYPEMUL(rhs.z, f[8]);

		return out;
	}

	float determinant() const
	{
		return VERTTYPEMUL(f[0], (VERTTYPEMUL(f[4], f[8]) - VERTTYPEMUL(f[7], f[5])))
			- VERTTYPEMUL(f[3], (VERTTYPEMUL(f[1], f[8]) - VERTTYPEMUL(f[7], f[2])))
			+ VERTTYPEMUL(f[6], (VERTTYPEMUL(f[1], f[5]) - VERTTYPEMUL(f[4], f[2])));
	}

	PVRTMat3 inverse() const
	{
		PVRTMat3 out;


		float recDet = determinant();
		assert(recDet != 0);
		recDet = VERTTYPEDIV(f2vt(1.0f), recDet);


		out.f[0] = VERTTYPEMUL(f[4], f[8]) - VERTTYPEMUL(f[5], f[7]);
		out.f[1] = VERTTYPEMUL(f[2], f[7]) - VERTTYPEMUL(f[1], f[8]);
		out.f[2] = VERTTYPEMUL(f[1], f[5]) - VERTTYPEMUL(f[2], f[4]);

		out.f[3] = VERTTYPEMUL(f[5], f[6]) - VERTTYPEMUL(f[3], f[8]);
		out.f[4] = VERTTYPEMUL(f[0], f[8]) - VERTTYPEMUL(f[2], f[6]);
		out.f[5] = VERTTYPEMUL(f[2], f[3]) - VERTTYPEMUL(f[0], f[5]);

		out.f[6] = VERTTYPEMUL(f[3], f[7]) - VERTTYPEMUL(f[4], f[6]);
		out.f[7] = VERTTYPEMUL(f[1], f[6]) - VERTTYPEMUL(f[0], f[7]);
		out.f[8] = VERTTYPEMUL(f[0], f[4]) - VERTTYPEMUL(f[1], f[3]);

		out *= recDet;
		return out;
	}

	
	PVRTMat3 transpose() const
	{
		PVRTMat3 out;
		out.f[0] = f[0];	out.f[3] = f[1];	out.f[6] = f[2];
		out.f[1] = f[3];	out.f[4] = f[4];	out.f[7] = f[5];
		out.f[2] = f[6];	out.f[5] = f[7];	out.f[8] = f[8];
		return out;
	}

	
	float *ptr() { return (float*)&f; }

	
	static PVRTMat3 Identity()
	{
		PVRTMat3 out;
		out.f[0] = 1; out.f[1] = 0; out.f[2] = 0;
		out.f[3] = 0; out.f[4] = 1; out.f[5] = 0;
		out.f[6] = 0; out.f[7] = 0; out.f[8] = 1;
		return out;
	}

	
	static PVRTMat3 RotationX(VERTTYPE angle);

	
	static PVRTMat3 RotationY(VERTTYPE angle);

	
	static PVRTMat3 RotationZ(VERTTYPE angle);

	
	static PVRTMat3 Scale(const float fx, const float fy, const float fz)
	{
		return PVRTMat3(fx, 0, 0,
			0, fy, 0,
			0, 0, fz);
	}

	static PVRTMat3 Translation(const float tx, const float ty)
	{
		return PVRTMat3(f2vt(1), 0, 0,
			0, f2vt(1), 0,
			tx, ty, f2vt(1));
	}

};




typedef struct camera_intrinsic {
	float          fx;           /**< focal length in x */
	float          fy;           /**< focal length in y */
	float          cx;           /**< offset of principle point in x */
	float          cy;           /**< offset of principle point in y */
	float          k1;           /**< radial distortion parameter */
	float          k2;           /**< radial distortion parameter */

}camera_intrinsic_t;

typedef struct camera_extrinsic {
	float          tx;           /**< translation - x */
	float          ty;           /**< translation - y */
	float          tz;           /**< translation - z */
	float          rx;           /**<  rotation - x  */
	float          ry;           /**<  rotation - y  */
	float          rz;           /**<  rotation - z  */
}camera_extrinsic_t;

typedef struct dynamic_para {
	int          dynamic;
	float        angle;
	float        rearspace;
	float        wheelbase;
	float		 vichelSpeed;
	float		forcastTime;
}dynamic_para_t;

typedef struct camera_matrix
{	
	PVRTMat4          intrin;

	PVRTMat4          ex_all;

	PVRTMat4          ex_all_inv;

	PVRTMat4          projection;

}camera_matrix_t;

typedef struct camera_para
{
	camera_intrinsic_t intrinsic;
	camera_extrinsic_t extrinsic;
	camera_matrix_t    mat;
}cameraPara_t;




typedef float color3[3];

typedef struct _linesData {
	int lineNums;  
	int* pLinePtNums;  
	float** pLineData;  
	unsigned short* pLinePtElemStartNum;
	unsigned short* pLineIndexElemStartNum;
	unsigned short* pLineBorderStartIndex;

	float* pBorderData;
	unsigned short* pBorderIndex;
	unsigned short pBorderIndexNum;
	unsigned short pBorderPtElemNum;
	color3 color;
}linesData;

typedef struct steer_params_t
{
	float trackWidth;
	float deltaDistMarks;
	int numDistMarks;
	float rearAxleOffset;
	float invFrontRatio;
	float invRearRatio;
	float wheelBase;
	float saturationAngle;
	float swaDeltaAngle;
	float vichelSpeed;
	float forcastTime;
}steer_params;

typedef struct GMVehicleInfo
{
	float wheelBase;
	float rearAxleOffset;
	float maxSteeringAngle; 
	float inverseFrontRatio;
	float inverseRearRatio;
	float vehicleAngle;
}GMVehicleInfo_t;

typedef enum {
	eStaticGuideLine,
	eDynamicGuideLine,
} GuideLineType;

typedef struct _sideLineInfo
{
	int lineNum;   
	int linePtNum; 
	float startDis;
	float endDis;
	bool bIsLSeg;   
	float LSegExtendLength; 
}sideLineInfo;

typedef struct _distLineInfo
{
	int lineNum;  
	int linePtNum;
	float* dist;  
}distLineInfo;


class point2D
{
public:
	point2D();
	point2D(float x1, float y1);
	point2D(const point2D& pt);
	void SetData(float x1, float y1);
	void SetData(const point2D& pt);
	point2D& operator= (const point2D& pt);
	point2D operator+ (const point2D& pt) const;
	point2D operator- (const point2D& pt) const;

	float Distance(const point2D& pt)const;

	float x;
	float y;
};

typedef struct _guidelineinfo
{
	int width; 
	int height;
	int startX;
	int startY; 
	cameraPara_t camparam;
	dynamic_para_t GUIDELINE_PARA;
	float* groupSeq;
	color3* color;
	float* tickLength;
}guidelineinfo;


#endif// __HARMAN_ADAS_AFRAMEWORK_AGRAPGICS_GUIDELINETYPEYDEFINE_H_