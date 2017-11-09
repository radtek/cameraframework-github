#include "GuideLineTypeDef.h"

using namespace std;


PVRTVec3::PVRTVec3(const PVRTVec4& vec4)
{
	x = vec4.x; y = vec4.y; z = vec4.z;
}

PVRTVec3 PVRTVec3::operator*(const PVRTMat3& rhs) const
{
	PVRTVec3 out;

	out.x = VERTTYPEMUL(x,rhs.f[0])+VERTTYPEMUL(y,rhs.f[1])+VERTTYPEMUL(z,rhs.f[2]);
	out.y = VERTTYPEMUL(x,rhs.f[3])+VERTTYPEMUL(y,rhs.f[4])+VERTTYPEMUL(z,rhs.f[5]);
	out.z = VERTTYPEMUL(x,rhs.f[6])+VERTTYPEMUL(y,rhs.f[7])+VERTTYPEMUL(z,rhs.f[8]);

	return out;
}

PVRTVec3& PVRTVec3::operator*=(const PVRTMat3& rhs)
{
	VERTTYPE tx = VERTTYPEMUL(x,rhs.f[0])+VERTTYPEMUL(y,rhs.f[1])+VERTTYPEMUL(z,rhs.f[2]);
	VERTTYPE ty = VERTTYPEMUL(x,rhs.f[3])+VERTTYPEMUL(y,rhs.f[4])+VERTTYPEMUL(z,rhs.f[5]);
	z = VERTTYPEMUL(x,rhs.f[6])+VERTTYPEMUL(y,rhs.f[7])+VERTTYPEMUL(z,rhs.f[8]);
	x = tx;
	y = ty;

	return *this;
}

PVRTVec4 PVRTVec4::operator*(const PVRTMat4& rhs) const
{
	PVRTVec4 out;
	out.x = VERTTYPEMUL(x,rhs.f[0])+VERTTYPEMUL(y,rhs.f[1])+VERTTYPEMUL(z,rhs.f[2])+VERTTYPEMUL(w,rhs.f[3]);
	out.y = VERTTYPEMUL(x,rhs.f[4])+VERTTYPEMUL(y,rhs.f[5])+VERTTYPEMUL(z,rhs.f[6])+VERTTYPEMUL(w,rhs.f[7]);
	out.z = VERTTYPEMUL(x,rhs.f[8])+VERTTYPEMUL(y,rhs.f[9])+VERTTYPEMUL(z,rhs.f[10])+VERTTYPEMUL(w,rhs.f[11]);
	out.w = VERTTYPEMUL(x,rhs.f[12])+VERTTYPEMUL(y,rhs.f[13])+VERTTYPEMUL(z,rhs.f[14])+VERTTYPEMUL(w,rhs.f[15]);
	return out;
}

PVRTVec4& PVRTVec4::operator*=(const PVRTMat4& rhs)
{
	VERTTYPE tx = VERTTYPEMUL(x,rhs.f[0])+VERTTYPEMUL(y,rhs.f[1])+VERTTYPEMUL(z,rhs.f[2])+VERTTYPEMUL(w,rhs.f[3]);
	VERTTYPE ty = VERTTYPEMUL(x,rhs.f[4])+VERTTYPEMUL(y,rhs.f[5])+VERTTYPEMUL(z,rhs.f[6])+VERTTYPEMUL(w,rhs.f[7]);
	VERTTYPE tz = VERTTYPEMUL(x,rhs.f[8])+VERTTYPEMUL(y,rhs.f[9])+VERTTYPEMUL(z,rhs.f[10])+VERTTYPEMUL(w,rhs.f[11]);
	w = VERTTYPEMUL(x,rhs.f[12])+VERTTYPEMUL(y,rhs.f[13])+VERTTYPEMUL(z,rhs.f[14])+VERTTYPEMUL(w,rhs.f[15]);
	x = tx;
	y = ty;
	z = tz;
	return *this;
}


PVRTMat4 PVRTMat4::operator*(const PVRTMat4& rhs) const
{
	PVRTMat4 out;
	// col 1
	out.f[0] =	VERTTYPEMUL(f[0],rhs.f[0])+VERTTYPEMUL(f[4],rhs.f[1])+VERTTYPEMUL(f[8],rhs.f[2])+VERTTYPEMUL(f[12],rhs.f[3]);
	out.f[1] =	VERTTYPEMUL(f[1],rhs.f[0])+VERTTYPEMUL(f[5],rhs.f[1])+VERTTYPEMUL(f[9],rhs.f[2])+VERTTYPEMUL(f[13],rhs.f[3]);
	out.f[2] =	VERTTYPEMUL(f[2],rhs.f[0])+VERTTYPEMUL(f[6],rhs.f[1])+VERTTYPEMUL(f[10],rhs.f[2])+VERTTYPEMUL(f[14],rhs.f[3]);		out.f[3] =	VERTTYPEMUL(f[3],rhs.f[0])+VERTTYPEMUL(f[7],rhs.f[1])+VERTTYPEMUL(f[11],rhs.f[2])+VERTTYPEMUL(f[15],rhs.f[3]);

		// col 2
	out.f[4] =	VERTTYPEMUL(f[0],rhs.f[4])+VERTTYPEMUL(f[4],rhs.f[5])+VERTTYPEMUL(f[8],rhs.f[6])+VERTTYPEMUL(f[12],rhs.f[7]);
	out.f[5] =	VERTTYPEMUL(f[1],rhs.f[4])+VERTTYPEMUL(f[5],rhs.f[5])+VERTTYPEMUL(f[9],rhs.f[6])+VERTTYPEMUL(f[13],rhs.f[7]);
	out.f[6] =	VERTTYPEMUL(f[2],rhs.f[4])+VERTTYPEMUL(f[6],rhs.f[5])+VERTTYPEMUL(f[10],rhs.f[6])+VERTTYPEMUL(f[14],rhs.f[7]);
	out.f[7] =	VERTTYPEMUL(f[3],rhs.f[4])+VERTTYPEMUL(f[7],rhs.f[5])+VERTTYPEMUL(f[11],rhs.f[6])+VERTTYPEMUL(f[15],rhs.f[7]);

		// col3
	out.f[8] =	VERTTYPEMUL(f[0],rhs.f[8])+VERTTYPEMUL(f[4],rhs.f[9])+VERTTYPEMUL(f[8],rhs.f[10])+VERTTYPEMUL(f[12],rhs.f[11]);
	out.f[9] =	VERTTYPEMUL(f[1],rhs.f[8])+VERTTYPEMUL(f[5],rhs.f[9])+VERTTYPEMUL(f[9],rhs.f[10])+VERTTYPEMUL(f[13],rhs.f[11]);
	out.f[10] =	VERTTYPEMUL(f[2],rhs.f[8])+VERTTYPEMUL(f[6],rhs.f[9])+VERTTYPEMUL(f[10],rhs.f[10])+VERTTYPEMUL(f[14],rhs.f[11]);
	out.f[11] =	VERTTYPEMUL(f[3],rhs.f[8])+VERTTYPEMUL(f[7],rhs.f[9])+VERTTYPEMUL(f[11],rhs.f[10])+VERTTYPEMUL(f[15],rhs.f[11]);

		// col3
	out.f[12] =	VERTTYPEMUL(f[0],rhs.f[12])+VERTTYPEMUL(f[4],rhs.f[13])+VERTTYPEMUL(f[8],rhs.f[14])+VERTTYPEMUL(f[12],rhs.f[15]);
	out.f[13] =	VERTTYPEMUL(f[1],rhs.f[12])+VERTTYPEMUL(f[5],rhs.f[13])+VERTTYPEMUL(f[9],rhs.f[14])+VERTTYPEMUL(f[13],rhs.f[15]);
	out.f[14] =	VERTTYPEMUL(f[2],rhs.f[12])+VERTTYPEMUL(f[6],rhs.f[13])+VERTTYPEMUL(f[10],rhs.f[14])+VERTTYPEMUL(f[14],rhs.f[15]);
	out.f[15] =	VERTTYPEMUL(f[3],rhs.f[12])+VERTTYPEMUL(f[7],rhs.f[13])+VERTTYPEMUL(f[11],rhs.f[14])+VERTTYPEMUL(f[15],rhs.f[15]);
	return out;
}

PVRTMat4 PVRTMat4::inverse() const
{
	PVRTMat4 out;
	VERTTYPE	det_1;
	VERTTYPE	pos, neg, temp;

	/* Calculate the determinant of submatrix A and determine if the
	the matrix is singular as limited by the double precision
	floating-point data representation. */
	pos = neg = f2vt(0.0);
	temp = VERTTYPEMUL(VERTTYPEMUL(f[0], f[5]), f[10]);
	if (temp >= 0) pos += temp; else neg += temp;
	temp = VERTTYPEMUL(VERTTYPEMUL(f[4], f[9]), f[2]);
	if (temp >= 0) pos += temp; else neg += temp;
	temp = VERTTYPEMUL(VERTTYPEMUL(f[8], f[1]), f[6]);
	if (temp >= 0) pos += temp; else neg += temp;
	temp = VERTTYPEMUL(VERTTYPEMUL(-f[8], f[5]), f[2]);
	if (temp >= 0) pos += temp; else neg += temp;
	temp = VERTTYPEMUL(VERTTYPEMUL(-f[4], f[1]), f[10]);
	if (temp >= 0) pos += temp; else neg += temp;
	temp = VERTTYPEMUL(VERTTYPEMUL(-f[0], f[9]), f[6]);
	if (temp >= 0) pos += temp; else neg += temp;
	det_1 = pos + neg;

	/* Is the submatrix A singular? */
	if (det_1 == f2vt(0.0)) //|| (VERTTYPEABS(det_1 / (pos - neg)) < 1.0e-15)
	{
		/* Matrix M has no inverse */
		//_RPT0(_CRT_WARN, "Matrix has no inverse : singular matrix\n");
	}
	else
	{
		/* Calculate inverse(A) = adj(A) / det(A) */
		//det_1 = 1.0 / det_1;
		det_1 = VERTTYPEDIV(f2vt(1.0f), det_1);
		out.f[0] = VERTTYPEMUL((VERTTYPEMUL(f[5], f[10]) - VERTTYPEMUL(f[9], f[6])), det_1);
		out.f[1] = -VERTTYPEMUL((VERTTYPEMUL(f[1], f[10]) - VERTTYPEMUL(f[9], f[2])), det_1);
		out.f[2] = VERTTYPEMUL((VERTTYPEMUL(f[1], f[6]) - VERTTYPEMUL(f[5], f[2])), det_1);
		out.f[4] = -VERTTYPEMUL((VERTTYPEMUL(f[4], f[10]) - VERTTYPEMUL(f[8], f[6])), det_1);
		out.f[5] = VERTTYPEMUL((VERTTYPEMUL(f[0], f[10]) - VERTTYPEMUL(f[8], f[2])), det_1);
		out.f[6] = -VERTTYPEMUL((VERTTYPEMUL(f[0], f[6]) - VERTTYPEMUL(f[4], f[2])), det_1);
		out.f[8] = VERTTYPEMUL((VERTTYPEMUL(f[4], f[9]) - VERTTYPEMUL(f[8], f[5])), det_1);
		out.f[9] = -VERTTYPEMUL((VERTTYPEMUL(f[0], f[9]) - VERTTYPEMUL(f[8], f[1])), det_1);
		out.f[10] = VERTTYPEMUL((VERTTYPEMUL(f[0], f[5]) - VERTTYPEMUL(f[4], f[1])), det_1);

		/* Calculate -C * inverse(A) */
		out.f[12] = -(VERTTYPEMUL(f[12], out.f[0]) + VERTTYPEMUL(f[13], out.f[4]) + VERTTYPEMUL(f[14], out.f[8]));
		out.f[13] = -(VERTTYPEMUL(f[12], out.f[1]) + VERTTYPEMUL(f[13], out.f[5]) + VERTTYPEMUL(f[14], out.f[9]));
		out.f[14] = -(VERTTYPEMUL(f[12], out.f[2]) + VERTTYPEMUL(f[13], out.f[6]) + VERTTYPEMUL(f[14], out.f[10]));

		/* Fill in last row */
		out.f[3] = f2vt(0.0f);
		out.f[7] = f2vt(0.0f);
		out.f[11] = f2vt(0.0f);
		out.f[15] = f2vt(1.0f);
	}

	return out;
}


PVRTMat4 PVRTMat4::RotationX(VERTTYPE angle)
{
	PVRTMat4 out;
	PVRTMatrixRotationX(out,angle);
	return out;
}

PVRTMat4 PVRTMat4::RotationY(VERTTYPE angle)
{
	PVRTMat4 out;
	PVRTMatrixRotationY(out,angle);
	return out;
}

PVRTMat4 PVRTMat4::RotationZ(VERTTYPE angle)
{
	PVRTMat4 out;
	PVRTMatrixRotationZ(out,angle);
	return out;
}




PVRTMat3::PVRTMat3(const PVRTMat4& mat)
{
	VERTTYPE *dest = (VERTTYPE*)f, *src = (VERTTYPE*)mat.f;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			(*dest++) = (*src++);
		}
		src++;
	}
}

PVRTMat3 PVRTMat3::RotationX(VERTTYPE angle)
{
	PVRTMat4 out;
	PVRTMatrixRotationX(out, angle);
	return PVRTMat3(out);
}

PVRTMat3 PVRTMat3::RotationY(VERTTYPE angle)
{
	PVRTMat4 out;
	PVRTMatrixRotationY(out, angle);
	return PVRTMat3(out);
}

PVRTMat3 PVRTMat3::RotationZ(VERTTYPE angle)
{
	PVRTMat4 out;
	PVRTMatrixRotationZ(out, angle);
	return PVRTMat3(out);
}

void PVRTLinearEqSolve(VERTTYPE * const pRes, VERTTYPE ** const pSrc, const int nCnt)
{
	int			i, j, k;
	VERTTYPE	f;

	if (nCnt == 1)
	{
		assert(pSrc[0][1] != 0);
		pRes[0] = VERTTYPEDIV(pSrc[0][0], pSrc[0][1]);
		return;
	}

	// Loop backwards in an attempt avoid the need to swap rows
	i = nCnt;
	while (i)
	{
		--i;

		if (pSrc[i][nCnt] != f2vt(0.0f))
		{
			// Row i can be used to zero the other rows; let's move it to the bottom
			if (i != (nCnt - 1))
			{
				for (j = 0; j <= nCnt; ++j)
				{
					// Swap the two values
					f = pSrc[nCnt - 1][j];
					pSrc[nCnt - 1][j] = pSrc[i][j];
					pSrc[i][j] = f;
				}
			}

			// Now zero the last columns of the top rows
			for (j = 0; j < (nCnt - 1); ++j)
			{
				assert(pSrc[nCnt - 1][nCnt] != f2vt(0.0f));
				f = VERTTYPEDIV(pSrc[j][nCnt], pSrc[nCnt - 1][nCnt]);

				// No need to actually calculate a zero for the final column
				for (k = 0; k < nCnt; ++k)
				{
					pSrc[j][k] -= VERTTYPEMUL(f, pSrc[nCnt - 1][k]);
				}
			}

			break;
		}
	}

	// Solve the top-left sub matrix
	PVRTLinearEqSolve(pRes, pSrc, nCnt - 1);

	// Now calc the solution for the bottom row
	f = pSrc[nCnt - 1][0];
	for (k = 1; k < nCnt; ++k)
	{
		f -= VERTTYPEMUL(pSrc[nCnt - 1][k], pRes[k - 1]);
	}
	assert(pSrc[nCnt - 1][nCnt] != f2vt(0));
	f = VERTTYPEDIV(f, pSrc[nCnt - 1][nCnt]);
	pRes[nCnt - 1] = f;
}

void PVRTMatrixRotationXF(PVRTMATRIX &mOut,const float fAngle)
{
	float	fCosine, fSine;

    /* Precompute cos and sin */
#if defined(BUILD_DX9) || defined(BUILD_D3DM) || defined(BUILD_DX10)
	fCosine	= (float)PVRTFCOS(-fAngle);
    fSine	= (float)PVRTFSIN(-fAngle);
#else
	fCosine	= (float)PVRTFCOS(fAngle);
    fSine	= (float)PVRTFSIN(fAngle);
#endif

	/* Create the trigonometric matrix corresponding to X Rotation */
	mOut.f[ 0]=1.0f;	mOut.f[ 4]=0.0f;	mOut.f[ 8]=0.0f;	mOut.f[12]=0.0f;
	mOut.f[ 1]=0.0f;	mOut.f[ 5]=fCosine;	mOut.f[ 9]=fSine;	mOut.f[13]=0.0f;
	mOut.f[ 2]=0.0f;	mOut.f[ 6]=-fSine;	mOut.f[10]=fCosine;	mOut.f[14]=0.0f;
	mOut.f[ 3]=0.0f;	mOut.f[ 7]=0.0f;	mOut.f[11]=0.0f;	mOut.f[15]=1.0f;
}

void PVRTMatrixRotationYF(PVRTMATRIX &mOut,const float fAngle)
{
	float	fCosine, fSine;

	/* Precompute cos and sin */
#if defined(BUILD_DX9) || defined(BUILD_D3DM) || defined(BUILD_DX10)
	fCosine	= (float)PVRTFCOS(-fAngle);
    fSine	= (float)PVRTFSIN(-fAngle);
#else
	fCosine	= (float)PVRTFCOS(fAngle);
    fSine	= (float)PVRTFSIN(fAngle);
#endif

	/* Create the trigonometric matrix corresponding to Y Rotation */
	mOut.f[ 0]=fCosine;		mOut.f[ 4]=0.0f;	mOut.f[ 8]=-fSine;		mOut.f[12]=0.0f;
	mOut.f[ 1]=0.0f;		mOut.f[ 5]=1.0f;	mOut.f[ 9]=0.0f;		mOut.f[13]=0.0f;
	mOut.f[ 2]=fSine;		mOut.f[ 6]=0.0f;	mOut.f[10]=fCosine;		mOut.f[14]=0.0f;
	mOut.f[ 3]=0.0f;		mOut.f[ 7]=0.0f;	mOut.f[11]=0.0f;		mOut.f[15]=1.0f;
}

void PVRTMatrixRotationZF(PVRTMATRIX &mOut,const float fAngle)
{
	float	fCosine, fSine;

	/* Precompute cos and sin */
#if defined(BUILD_DX9) || defined(BUILD_D3DM) || defined(BUILD_DX10)
	fCosine =	(float)PVRTFCOS(-fAngle);
    fSine =		(float)PVRTFSIN(-fAngle);
#else
	fCosine =	(float)PVRTFCOS(fAngle);
    fSine =		(float)PVRTFSIN(fAngle);
#endif

	/* Create the trigonometric matrix corresponding to Z Rotation */
	mOut.f[ 0]=fCosine;		mOut.f[ 4]=fSine;	mOut.f[ 8]=0.0f;	mOut.f[12]=0.0f;
	mOut.f[ 1]=-fSine;		mOut.f[ 5]=fCosine;	mOut.f[ 9]=0.0f;	mOut.f[13]=0.0f;
	mOut.f[ 2]=0.0f;		mOut.f[ 6]=0.0f;	mOut.f[10]=1.0f;	mOut.f[14]=0.0f;
	mOut.f[ 3]=0.0f;		mOut.f[ 7]=0.0f;	mOut.f[11]=0.0f;	mOut.f[15]=1.0f;
}

point2D::point2D()
{
	x = 0.0;
	y = 0.0;
}

point2D::point2D(float x1, float y1)
{
	x = x1;
	y = y1;
}

point2D::point2D(const point2D& pt)
{
	x = pt.x;
	y = pt.y;
}

void point2D::SetData(float x1, float y1)
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

