#include "C3DMatrix4.h"
#include "C3DMatrix3.h"
#include "CMath.h"


	const C3DMatrix4 C3DMatrix4::ZERO(
						0, 0, 0, 0,
						0, 0, 0, 0,
						0, 0, 0, 0,
						0, 0, 0, 0 );

	const C3DMatrix4 C3DMatrix4::ZEROAFFINE(
						0, 0, 0, 0,
						0, 0, 0, 0,
						0, 0, 0, 0,
						0, 0, 0, 1 );

	const C3DMatrix4 C3DMatrix4::IDENTITY(
						1, 0, 0, 0,
						0, 1, 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1 );

	const C3DMatrix4 C3DMatrix4::CLIPSPACE2DTOIMAGESPACE(
					  0.5f,    0,  0, 0.5f, 
						0, -0.5f,  0, 0.5f, 
						0,    0,  1,   0,
						0,    0,  0,   1);

#define VERTTYPEMUL(op1, op2)		((op1) * (op2))

	C3DMatrix4::C3DMatrix4()
	{
		m_pf = &m_f[0][0];

		for (Int32 i = 0; i < 16; i++)
		{
			m_pf[i] = 0.0f;
		}
	}

	C3DMatrix4::C3DMatrix4(const C3DMatrix4 &src)
	{
		m_pf = &m_f[0][0];

		for (Int32 i = 0; i < 16; i++)
		{
			m_pf[i] = src.m_pf[i];
		}
	}

	C3DMatrix4::C3DMatrix4(	Float32 f00, Float32 f01, Float32 f02, Float32 f03,
							Float32 f10, Float32 f11, Float32 f12, Float32 f13,
							Float32 f20, Float32 f21, Float32 f22, Float32 f23,
							Float32 f30, Float32 f31, Float32 f32, Float32 f33)
	{
		m_pf = &m_f[0][0];

		m_f[0][0] = f00;
		m_f[0][1] = f01;
		m_f[0][2] = f02;
		m_f[0][3] = f03;
		m_f[1][0] = f10;
		m_f[1][1] = f11;
		m_f[1][2] = f12;
		m_f[1][3] = f13;
		m_f[2][0] = f20;
		m_f[2][1] = f21;
		m_f[2][2] = f22;
		m_f[2][3] = f23;
		m_f[3][0] = f30;
		m_f[3][1] = f31;
		m_f[3][2] = f32;
		m_f[3][3] = f33;
	}

	C3DMatrix4::~C3DMatrix4()
	{
		;
	}	

	void C3DMatrix4::setTrans( const C3DVector3 &vt)
	{
		m_f[3][0] = vt.getX();
		m_f[3][1] = vt.getY();
		m_f[3][2] = vt.getZ();
	}

	void C3DMatrix4::setTrans( Float32 fX, Float32 fY, Float32 fZ)
	{
		m_f[3][0] = fX;
		m_f[3][1] = fY;
		m_f[3][2] = fZ;
	}

	C3DVector3 C3DMatrix4::getTrans() const
	{
		return C3DVector3(m_f[3][0], m_f[3][1], m_f[3][2]);
	}

	void C3DMatrix4::makeTrans( const C3DVector3 &vt)
	{
		makeTrans(vt.getX(), vt.getY(), vt.getZ());
	}

	void C3DMatrix4::makeTrans( Float32 fX, Float32 fY, Float32 fZ)
	{
		m_f[0][0] = 1.0; m_f[0][1] = 0.0; m_f[0][2] = 0.0; m_f[0][3] = 0.0;
		m_f[1][0] = 0.0; m_f[1][1] = 1.0; m_f[1][2] = 0.0; m_f[1][3] = 0.0;
		m_f[2][0] = 0.0; m_f[2][1] = 0.0; m_f[2][2] = 1.0; m_f[2][3] = 0.0;
		m_f[3][0] = fX;  m_f[3][1] = fY;  m_f[3][2] = fZ;  m_f[3][3] = 1.0;
	}

	void C3DMatrix4::setScale( const C3DVector3 &vt)
	{
		m_f[0][0] = vt.getX();
		m_f[1][1] = vt.getY();
		m_f[2][2] = vt.getZ();
	}

	void C3DMatrix4::setScale( Float32 fX, Float32 fY, Float32 fZ)
	{
		m_f[0][0] = fX;
		m_f[1][1] = fY;
		m_f[2][2] = fZ;
	}

	C3DVector3 C3DMatrix4::getScale() const
	{
		return C3DVector3(m_f[0][0], m_f[1][1], m_f[2][2]);
	}

	void C3DMatrix4::makeScale( const C3DVector3 &vt)
	{
		makeScale(vt.getX(), vt.getY(), vt.getZ());
	}

	void C3DMatrix4::makeScale( Float32 fX, Float32 fY, Float32 fZ)
	{
		m_f[0][0] = fX;  m_f[0][1] = 0.0; m_f[0][2] = 0.0; m_f[0][3] = 0.0;
		m_f[1][0] = 0.0; m_f[1][1] = fY;  m_f[1][2] = 0.0; m_f[1][3] = 0.0;
		m_f[2][0] = 0.0; m_f[2][1] = 0.0; m_f[2][2] = fZ;  m_f[2][3] = 0.0;
		m_f[3][0] = 0.0; m_f[3][1] = 0.0; m_f[3][2] = 0.0; m_f[3][3] = 1.0;
	}

	BOOLEAN C3DMatrix4::hasScale() const
	{
		Float32 fTemp = m_f[0][0] * m_f[0][0] + m_f[1][0] * m_f[1][0] + m_f[2][0] * m_f[2][0];
		if (!Math::isZero(fTemp - 1.0f))
		{
			return TRUE;
		}

		fTemp = m_f[0][1] * m_f[0][1] + m_f[1][1] * m_f[1][1] + m_f[2][1] * m_f[2][1];
		if (!Math::isZero(fTemp - 1.0f))
		{
			return TRUE;
		}

		fTemp = m_f[0][2] * m_f[0][2] + m_f[1][2] * m_f[1][2] + m_f[2][2] * m_f[2][2];
		if (!Math::isZero(fTemp - 1.0f))
		{
			return TRUE;
		}

		return FALSE;
	}

	BOOLEAN C3DMatrix4::hasNegativeScale() const
	{
		return determinant() < 0;
	}

	void C3DMatrix4::rotateX(const Float32 fAngle)
	{
		Float32 fCosine, fSine;

		fCosine = (Float32)Math::cos(fAngle);
		fSine   = (Float32)Math::sin(fAngle);

		/* Create the trigonometric matrix corresponding to X Rotation */
		m_f[0][0] = 1.0f;		m_f[0][1] = 0.0f;		m_f[0][2] = 0.0f;		m_f[0][3] = 0.0f;
		m_f[1][0] = 0.0f;	    m_f[1][1] = fCosine;	m_f[1][2] = fSine;		m_f[1][3] = 0.0f;
		m_f[2][0] = 0.0f;		m_f[2][1] = -fSine;		m_f[2][2] = fCosine;	m_f[2][3] = 0.0f;
		m_f[3][0] = 0.0f;		m_f[3][1] = 0.0f;		m_f[3][2] = 0.0f;		m_f[3][3] = 1.0f;
	}

	void C3DMatrix4::rotateY(const Float32 fAngle)
	{
		Float32 fCosine, fSine;
		
		fCosine = (Float32)Math::cos(fAngle);
		fSine   = (Float32)Math::sin(fAngle);

		/* Create the trigonometric matrix corresponding to Y Rotation */
		m_f[0][0] = fCosine;	m_f[0][1] = 0.0f;		m_f[0][2] = -fSine;		m_f[0][3] = 0.0f;
		m_f[1][0] = 0.0f;	    m_f[1][1] = 1.0f;		m_f[1][2] = 0.0f;		m_f[1][3] = 0.0f;
		m_f[2][0] = fSine;		m_f[2][1] = 0.0f;		m_f[2][2] = fCosine;	m_f[2][3] = 0.0f;
		m_f[3][0] = 0.0f;		m_f[3][1] = 0.0f;		m_f[3][2] = 0.0f;		m_f[3][3] = 1.0f;
	}

	void C3DMatrix4::rotateZ(const Float32 fAngle)
	{
		Float32 fCosine, fSine;
		
		fCosine = (Float32)Math::cos(fAngle);
		fSine   = (Float32)Math::sin(fAngle);

		/* Create the trigonometric matrix corresponding to Z Rotation */
		m_f[0][0] = fCosine;	m_f[0][1] = fSine;		m_f[0][2] = 0.0f;		m_f[0][3] = 0.0f;
		m_f[1][0] = -fSine;	    m_f[1][1] = fCosine;    m_f[1][2] = 0.0f;		m_f[1][3] = 0.0f;
		m_f[2][0] = 0.0f;		m_f[2][1] = 0.0f;		m_f[2][2] = 1.0f;		m_f[2][3] = 0.0f;
		m_f[3][0] = 0.0f;		m_f[3][1] = 0.0f;		m_f[3][2] = 0.0f;		m_f[3][3] = 1.0f;
	}

	void C3DMatrix4::extract3x3Matrix(C3DMatrix3& mat3x3) const
	{
		mat3x3.m_f[0][0] = m_f[0][0];
        mat3x3.m_f[0][1] = m_f[0][1];
        mat3x3.m_f[0][2] = m_f[0][2];
        mat3x3.m_f[1][0] = m_f[1][0];
        mat3x3.m_f[1][1] = m_f[1][1];
        mat3x3.m_f[1][2] = m_f[1][2];
        mat3x3.m_f[2][0] = m_f[2][0];
        mat3x3.m_f[2][1] = m_f[2][1];
        mat3x3.m_f[2][2] = m_f[2][2];
	}

	C3DQuaternion C3DMatrix4::extractQuaternion() const
	{
		C3DMatrix3 m3x3;
		extract3x3Matrix(m3x3);
		return C3DQuaternion(m3x3);
	}

	BOOLEAN C3DMatrix4::isAffine() const
	{
		return m_f[0][3] == 0 && m_f[1][3] == 0 && m_f[2][3] == 0 && m_f[3][3] == 1;
	}

	void C3DMatrix4::makeLookAt(const C3DVector3 &eye, const C3DVector3 &target, const C3DVector3 &up)
	{
		C3DVector3 xAxis;
		C3DVector3 yAxis;
		C3DVector3 zAxis = eye - target;

		zAxis.normalise();

		xAxis = up.crossProduct(zAxis);
		xAxis.normalise();

		yAxis = zAxis.crossProduct(xAxis);
		yAxis.normalise();
	 
		m_f[0][0] = xAxis.getX();
		m_f[1][0] = xAxis.getY();
		m_f[2][0] = xAxis.getZ();
		m_f[3][0] = -xAxis.dotProduct(eye);

		m_f[0][1] = yAxis.getX();
		m_f[1][1] = yAxis.getY();
		m_f[2][1] = yAxis.getZ();
		m_f[3][1] = -yAxis.dotProduct(eye);

		m_f[0][2] = zAxis.getX();
		m_f[1][2] = zAxis.getY();
		m_f[2][2] = zAxis.getZ();    
		m_f[3][2] = -zAxis.dotProduct(eye);

		m_f[0][3] = 0.0f;
		m_f[1][3] = 0.0f;
		m_f[2][3] = 0.0f;
		m_f[3][3] = 1.0f;
	}

	void C3DMatrix4::makePerspective(Float32 fovx, Float32 aspect, Float32 znear, Float32 zfar)
	{
		Float32 e = 1.0f / Math::tan( Math::toRadian(fovx) / 2.0f);
		Float32 aspectInv = 1.0f / aspect;
		Float32 fovy = 2.0f * Math::atan(aspectInv / e);
		Float32 xScale = 1.0f / Math::tan(0.5f * fovy);
		Float32 yScale = xScale / aspectInv;

		m_f[0][0] = xScale;
		m_f[0][1] = 0.0f;
		m_f[0][2] = 0.0f;
		m_f[0][3] = 0.0f;

		m_f[1][0] = 0.0f;
		m_f[1][1] = yScale;
		m_f[1][2] = 0.0f;
		m_f[1][3] = 0.0f;

		m_f[2][0] = 0.0f;
		m_f[2][1] = 0.0f;
		m_f[2][2] = (zfar + znear) / (znear - zfar);
		m_f[2][3] = -1.0f;

		m_f[3][0] = 0.0f;
		m_f[3][1] = 0.0f;
		m_f[3][2] = (2.0f * zfar * znear) / (znear - zfar);
		m_f[3][3] = 0.0f;
	}

	void C3DMatrix4::makePerspective(Float32 l, Float32 r, Float32 t, Float32 b, Float32 n, Float32 f)
	{
		m_f[0][0] = 2.0f * n/(r-l);
		m_f[0][1] = 0.0f;
		m_f[0][2] = 0.0f;
		m_f[0][3] = 0.0f;

		m_f[1][0] = 0.0f;
		m_f[1][1] = 2.0f * n/(t-b);
		m_f[1][2] = 0.0f;
		m_f[1][3] = 0.0f;

		m_f[2][0] = 0.0f;
		m_f[2][1] = 0.0f;
		m_f[2][2] = (f + n) / (n - f);
		m_f[2][3] = -1.0f;

		m_f[3][0] = 0.0f;
		m_f[3][1] = 0.0f;
		m_f[3][2] = (2.0f * f * n) / (n - f);
		m_f[3][3] = 0.0f;
	}

	void C3DMatrix4::makeOrthognal(Float32 l, Float32 r, Float32 t, Float32 b, Float32 n, Float32 f)
	{
		m_f[0][0] = 2.0f / (r - l);
		m_f[0][1] = 0.0f;
		m_f[0][2] = 0.0f;
		m_f[0][3] = 0.0f;

		m_f[1][0] = 0.0f;
		m_f[1][1] = 2.0f / (t - b);
		m_f[1][2] = 0.0f;
		m_f[1][3] = 0.0f;

		m_f[2][0] = 0.0f;
		m_f[2][1] = 0.0f;
		m_f[2][2] = -2.0f / (f - n);
		m_f[2][3] = 0.0f;

		
		m_f[3][0] = -(r + l) / (r - l);
		m_f[3][1] = -(t + b) / (t - b);
		m_f[3][2] =  -(f + n) / (f - n);
		m_f[3][3] = 1.0f;
	}

	C3DMatrix4 C3DMatrix4::concatenate(const C3DMatrix4 &mat2) const
	{
		C3DMatrix4 mat;

		mat.m_f[0][0] = m_f[0][0] * mat2.m_f[0][0] + m_f[0][1] * mat2.m_f[1][0] + m_f[0][2] * mat2.m_f[2][0] + m_f[0][3] * mat2.m_f[3][0];
		mat.m_f[0][1] = m_f[0][0] * mat2.m_f[0][1] + m_f[0][1] * mat2.m_f[1][1] + m_f[0][2] * mat2.m_f[2][1] + m_f[0][3] * mat2.m_f[3][1];
		mat.m_f[0][2] = m_f[0][0] * mat2.m_f[0][2] + m_f[0][1] * mat2.m_f[1][2] + m_f[0][2] * mat2.m_f[2][2] + m_f[0][3] * mat2.m_f[3][2];
		mat.m_f[0][3] = m_f[0][0] * mat2.m_f[0][3] + m_f[0][1] * mat2.m_f[1][3] + m_f[0][2] * mat2.m_f[2][3] + m_f[0][3] * mat2.m_f[3][3];

		mat.m_f[1][0] = m_f[1][0] * mat2.m_f[0][0] + m_f[1][1] * mat2.m_f[1][0] + m_f[1][2] * mat2.m_f[2][0] + m_f[1][3] * mat2.m_f[3][0];
		mat.m_f[1][1] = m_f[1][0] * mat2.m_f[0][1] + m_f[1][1] * mat2.m_f[1][1] + m_f[1][2] * mat2.m_f[2][1] + m_f[1][3] * mat2.m_f[3][1];
		mat.m_f[1][2] = m_f[1][0] * mat2.m_f[0][2] + m_f[1][1] * mat2.m_f[1][2] + m_f[1][2] * mat2.m_f[2][2] + m_f[1][3] * mat2.m_f[3][2];
		mat.m_f[1][3] = m_f[1][0] * mat2.m_f[0][3] + m_f[1][1] * mat2.m_f[1][3] + m_f[1][2] * mat2.m_f[2][3] + m_f[1][3] * mat2.m_f[3][3];

		mat.m_f[2][0] = m_f[2][0] * mat2.m_f[0][0] + m_f[2][1] * mat2.m_f[1][0] + m_f[2][2] * mat2.m_f[2][0] + m_f[2][3] * mat2.m_f[3][0];
		mat.m_f[2][1] = m_f[2][0] * mat2.m_f[0][1] + m_f[2][1] * mat2.m_f[1][1] + m_f[2][2] * mat2.m_f[2][1] + m_f[2][3] * mat2.m_f[3][1];
		mat.m_f[2][2] = m_f[2][0] * mat2.m_f[0][2] + m_f[2][1] * mat2.m_f[1][2] + m_f[2][2] * mat2.m_f[2][2] + m_f[2][3] * mat2.m_f[3][2];
		mat.m_f[2][3] = m_f[2][0] * mat2.m_f[0][3] + m_f[2][1] * mat2.m_f[1][3] + m_f[2][2] * mat2.m_f[2][3] + m_f[2][3] * mat2.m_f[3][3];

		mat.m_f[3][0] = m_f[3][0] * mat2.m_f[0][0] + m_f[3][1] * mat2.m_f[1][0] + m_f[3][2] * mat2.m_f[2][0] + m_f[3][3] * mat2.m_f[3][0];
		mat.m_f[3][1] = m_f[3][0] * mat2.m_f[0][1] + m_f[3][1] * mat2.m_f[1][1] + m_f[3][2] * mat2.m_f[2][1] + m_f[3][3] * mat2.m_f[3][1];
		mat.m_f[3][2] = m_f[3][0] * mat2.m_f[0][2] + m_f[3][1] * mat2.m_f[1][2] + m_f[3][2] * mat2.m_f[2][2] + m_f[3][3] * mat2.m_f[3][2];
		mat.m_f[3][3] = m_f[3][0] * mat2.m_f[0][3] + m_f[3][1] * mat2.m_f[1][3] + m_f[3][2] * mat2.m_f[2][3] + m_f[3][3] * mat2.m_f[3][3];

		return mat;
	}

	C3DMatrix4 C3DMatrix4::transpose() const
	{
		return C3DMatrix4(	m_f[0][0], m_f[1][0], m_f[2][0], m_f[3][0],
							m_f[0][1], m_f[1][1], m_f[2][1], m_f[3][1],
							m_f[0][2], m_f[1][2], m_f[2][2], m_f[3][2],
							m_f[0][3], m_f[1][3], m_f[2][3], m_f[3][3]);
	}	

	C3DMatrix4 C3DMatrix4::adjoint() const
	{
		return C3DMatrix4(	myMinor(1, 2, 3, 1, 2, 3),
							-myMinor(0, 2, 3, 1, 2, 3),
							myMinor(0, 1, 3, 1, 2, 3),
							-myMinor(0, 1, 2, 1, 2, 3),

							-myMinor(1, 2, 3, 0, 2, 3),
							myMinor(0, 2, 3, 0, 2, 3),
							-myMinor(0, 1, 3, 0, 2, 3),
							myMinor(0, 1, 2, 0, 2, 3),

							myMinor(1, 2, 3, 0, 1, 3),
							-myMinor(0, 2, 3, 0, 1, 3),
							myMinor(0, 1, 3, 0, 1, 3),
							-myMinor(0, 1, 2, 0, 1, 3),

							-myMinor(1, 2, 3, 0, 1, 2),
							myMinor(0, 2, 3, 0, 1, 2),
							-myMinor(0, 1, 3, 0, 1, 2),
							myMinor(0, 1, 2, 0, 1, 2)   );
	}

	Float32 C3DMatrix4::determinant() const
	{
		return	m_f[0][0] * myMinor(1, 2, 3, 1, 2, 3) -
				m_f[0][1] * myMinor(1, 2, 3, 0, 2, 3) +
				m_f[0][2] * myMinor(1, 2, 3, 0, 1, 3) -
				m_f[0][3] * myMinor(1, 2, 3, 0, 1, 2);
	}

	C3DMatrix4 C3DMatrix4::inverse() const
	{
		Float32 m00 = m_f[0][0], m01 = m_f[0][1], m02 = m_f[0][2], m03 = m_f[0][3];
		Float32 m10 = m_f[1][0], m11 = m_f[1][1], m12 = m_f[1][2], m13 = m_f[1][3];
		Float32 m20 = m_f[2][0], m21 = m_f[2][1], m22 = m_f[2][2], m23 = m_f[2][3];
		Float32 m30 = m_f[3][0], m31 = m_f[3][1], m32 = m_f[3][2], m33 = m_f[3][3];

		Float32 v0 = m20 * m31 - m21 * m30;
		Float32 v1 = m20 * m32 - m22 * m30;
		Float32 v2 = m20 * m33 - m23 * m30;
		Float32 v3 = m21 * m32 - m22 * m31;
		Float32 v4 = m21 * m33 - m23 * m31;
		Float32 v5 = m22 * m33 - m23 * m32;

		Float32 t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
		Float32 t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
		Float32 t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
		Float32 t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

		Float32 invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

		Float32 d00 = t00 * invDet;
		Float32 d10 = t10 * invDet;
		Float32 d20 = t20 * invDet;
		Float32 d30 = t30 * invDet;

		Float32 d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
		Float32 d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
		Float32 d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
		Float32 d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		v0 = m10 * m31 - m11 * m30;
		v1 = m10 * m32 - m12 * m30;
		v2 = m10 * m33 - m13 * m30;
		v3 = m11 * m32 - m12 * m31;
		v4 = m11 * m33 - m13 * m31;
		v5 = m12 * m33 - m13 * m32;

		Float32 d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
		Float32 d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
		Float32 d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
		Float32 d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		v0 = m21 * m10 - m20 * m11;
		v1 = m22 * m10 - m20 * m12;
		v2 = m23 * m10 - m20 * m13;
		v3 = m22 * m11 - m21 * m12;
		v4 = m23 * m11 - m21 * m13;
		v5 = m23 * m12 - m22 * m13;

		Float32 d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
		Float32 d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
		Float32 d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
		Float32 d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		return C3DMatrix4(	d00, d01, d02, d03,
							d10, d11, d12, d13,
							d20, d21, d22, d23,
							d30, d31, d32, d33);
	}

	C3DMatrix4 C3DMatrix4::inverseAffine() const
	{
		if (!isAffine())
		{
			return C3DMatrix4();
		}

		Float32 m10 = m_f[1][0], m11 = m_f[1][1], m12 = m_f[1][2];
		Float32 m20 = m_f[2][0], m21 = m_f[2][1], m22 = m_f[2][2];

		Float32 t00 = m22 * m11 - m21 * m12;
		Float32 t10 = m20 * m12 - m22 * m10;
		Float32 t20 = m21 * m10 - m20 * m11;

		Float32 m00 = m_f[0][0], m01 = m_f[0][1], m02 = m_f[0][2];

		Float32 invDet = 1 / (m00 * t00 + m01 * t10 + m02 * t20);

		t00 *= invDet; t10 *= invDet; t20 *= invDet;

		m00 *= invDet; m01 *= invDet; m02 *= invDet;

		Float32 r00 = t00;
		Float32 r01 = m02 * m21 - m01 * m22;
		Float32 r02 = m01 * m12 - m02 * m11;

		Float32 r10 = t10;
		Float32 r11 = m00 * m22 - m02 * m20;
		Float32 r12 = m02 * m10 - m00 * m12;

		Float32 r20 = t20;
		Float32 r21 = m01 * m20 - m00 * m21;
		Float32 r22 = m00 * m11 - m01 * m10;

		Float32 m03 = m_f[0][3], m13 = m_f[1][3], m23 = m_f[2][3];

		Float32 r03 = - (r00 * m03 + r01 * m13 + r02 * m23);
		Float32 r13 = - (r10 * m03 + r11 * m13 + r12 * m23);
		Float32 r23 = - (r20 * m03 + r21 * m13 + r22 * m23);

		return C3DMatrix4(	r00, r01, r02, r03,
							r10, r11, r12, r13,
							r20, r21, r22, r23,
							0,   0,   0,   1);
	}

	void C3DMatrix4::identity()
	{
		*this = C3DMatrix4::IDENTITY;
	}

	void C3DMatrix4::makeTransform(const C3DVector3 &vtPosition, const C3DVector3 &vtScale, const C3DQuaternion &qtnOrientation)
	{
		C3DMatrix3 rot3x3;
		qtnOrientation.toRotationMatrix(rot3x3);

        m_f[0][0] = vtScale.m_fX * rot3x3[0][0]; m_f[0][1] = vtScale.m_fY * rot3x3[0][1]; m_f[0][2] = vtScale.m_fZ * rot3x3[0][2]; m_f[0][3] = 0.0f;
        m_f[1][0] = vtScale.m_fX * rot3x3[1][0]; m_f[1][1] = vtScale.m_fY * rot3x3[1][1]; m_f[1][2] = vtScale.m_fZ * rot3x3[1][2]; m_f[1][3] = 0.0f;
        m_f[2][0] = vtScale.m_fX * rot3x3[2][0]; m_f[2][1] = vtScale.m_fY * rot3x3[2][1]; m_f[2][2] = vtScale.m_fZ * rot3x3[2][2]; m_f[2][3] = 0.0f;

        m_f[3][0] = vtPosition.m_fX; m_f[3][1] = vtPosition.m_fY; m_f[3][2] = vtPosition.m_fZ; m_f[3][3] = 1;
	}

	void C3DMatrix4::makeInverseTransform(const C3DVector3& position, const C3DVector3& scale, const C3DQuaternion &qtnOrientation)
	{
        C3DVector3 invTranslate = -position;
        C3DVector3 invScale(1 / scale.m_fX, 1 / scale.m_fY, 1 / scale.m_fZ);
        C3DQuaternion invRot = qtnOrientation.inverse();

        invTranslate = invTranslate * invRot ; // rotate
        invTranslate *= invScale; // scale

        C3DMatrix3 rot3x3;
        invRot.toRotationMatrix(rot3x3);

        m_f[0][0] = invScale.m_fX * rot3x3[0][0]; m_f[0][1] = invScale.m_fX * rot3x3[0][1]; m_f[0][2] = invScale.m_fX * rot3x3[0][2]; m_f[0][3] = 0.0f;
        m_f[1][0] = invScale.m_fY * rot3x3[1][0]; m_f[1][1] = invScale.m_fY * rot3x3[1][1]; m_f[1][2] = invScale.m_fY * rot3x3[1][2]; m_f[1][3] = 0.0f;
        m_f[2][0] = invScale.m_fZ * rot3x3[2][0]; m_f[2][1] = invScale.m_fZ * rot3x3[2][1]; m_f[2][2] = invScale.m_fZ * rot3x3[2][2]; m_f[2][3] = 0.0f;		

        m_f[3][0] = invTranslate.m_fX; m_f[3][1] = invTranslate.m_fY; m_f[3][2] = invTranslate.m_fZ; m_f[3][3] = 1;
    
	}

	C3DMatrix4 C3DMatrix4::concatenateAffine(const C3DMatrix4 &mat2) const
	{
		if (!isAffine() || !mat2.isAffine())
		{
			return C3DMatrix4();
		}

		return C3DMatrix4(
					m_f[0][0] * mat2.m_f[0][0] + m_f[0][1] * mat2.m_f[1][0] + m_f[0][2] * mat2.m_f[2][0],
					m_f[0][0] * mat2.m_f[0][1] + m_f[0][1] * mat2.m_f[1][1] + m_f[0][2] * mat2.m_f[2][1],
					m_f[0][0] * mat2.m_f[0][2] + m_f[0][1] * mat2.m_f[1][2] + m_f[0][2] * mat2.m_f[2][2],
					0,

					m_f[1][0] * mat2.m_f[0][0] + m_f[1][1] * mat2.m_f[1][0] + m_f[1][2] * mat2.m_f[2][0],
					m_f[1][0] * mat2.m_f[0][1] + m_f[1][1] * mat2.m_f[1][1] + m_f[1][2] * mat2.m_f[2][1],
					m_f[1][0] * mat2.m_f[0][2] + m_f[1][1] * mat2.m_f[1][2] + m_f[1][2] * mat2.m_f[2][2],
					0,

					m_f[2][0] * mat2.m_f[0][0] + m_f[2][1] * mat2.m_f[1][0] + m_f[2][2] * mat2.m_f[2][0],
					m_f[2][0] * mat2.m_f[0][1] + m_f[2][1] * mat2.m_f[1][1] + m_f[2][2] * mat2.m_f[2][1],
					m_f[2][0] * mat2.m_f[0][2] + m_f[2][1] * mat2.m_f[1][2] + m_f[2][2] * mat2.m_f[2][2],
					0,

					m_f[3][0] * mat2.m_f[0][0] + m_f[3][1] * mat2.m_f[1][0] + m_f[3][2] * mat2.m_f[2][0],
					m_f[3][0] * mat2.m_f[0][1] + m_f[3][1] * mat2.m_f[1][1] + m_f[3][2] * mat2.m_f[2][1],
					m_f[3][0] * mat2.m_f[0][2] + m_f[3][1] * mat2.m_f[1][2] + m_f[3][2] * mat2.m_f[2][2],
					1);
	}

	C3DVector3 C3DMatrix4::transformAffine(const C3DVector3 &vt) const
	{
		if (!isAffine())
		{
			return C3DVector3::ZERO;
		}

		return C3DVector3(	m_f[0][0] * vt.getX() + m_f[1][0] * vt.getY() + m_f[2][0] * vt.getZ() + m_f[3][0], 
							m_f[0][1] * vt.getX() + m_f[1][1] * vt.getY() + m_f[2][1] * vt.getZ() + m_f[3][1],
							m_f[0][2] * vt.getX() + m_f[1][2] * vt.getY() + m_f[2][2] * vt.getZ() + m_f[3][2]);
	}

	C3DMatrix4&	C3DMatrix4::operator =(const C3DMatrix3 &mat3)
	{
		m_f[0][0] = mat3.m_f[0][0]; m_f[0][1] = mat3.m_f[0][1]; m_f[0][2] = mat3.m_f[0][2];
        m_f[1][0] = mat3.m_f[1][0]; m_f[1][1] = mat3.m_f[1][1]; m_f[1][2] = mat3.m_f[1][2];
        m_f[2][0] = mat3.m_f[2][0]; m_f[2][1] = mat3.m_f[2][1]; m_f[2][2] = mat3.m_f[2][2];

		m_f[3][0] = 0; m_f[3][1] = 0; m_f[3][2] = 0; m_f[3][3] = 1;

		return (*this);
	}

	C3DMatrix4& C3DMatrix4::operator =(const C3DMatrix4 &src)
	{
		for (Int32 i = 0; i < 16; i++)
		{
			m_pf[i] = src.m_pf[i];
		}

		return *this;
	}

	BOOLEAN C3DMatrix4::operator ==(const C3DMatrix4 &src) const
	{
		for (Int32 i = 0; i < 16; i++)
		{
			if (!Math::isZero(m_pf[i] - src.m_pf[i]))
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	BOOLEAN C3DMatrix4::operator !=(const C3DMatrix4 &src) const
	{
		return	!operator==(src);
	}

	C3DMatrix4 C3DMatrix4::operator +(const C3DMatrix4 &src) const
	{
		C3DMatrix4 mtx;

		for (Int32 i = 0; i < 16; i++)
		{
			mtx.m_pf[i] = m_pf[i] + src.m_pf[i];
		}

		return mtx;
	}

	C3DMatrix4 C3DMatrix4::operator -(const C3DMatrix4 &src) const
	{
		C3DMatrix4 mtx;

		for (Int32 i = 0; i < 16; i++)
		{
			mtx.m_pf[i] = m_pf[i] - src.m_pf[i];
		}

		return mtx;
	}

	C3DMatrix4 C3DMatrix4::operator *(Float32 fScalar) const
	{
		C3DMatrix4 mtx;

		for (Int32 i = 0; i < 16; i++)
		{
			mtx.m_pf[i] = m_pf[i] * fScalar;
		}

		return mtx;
	}


/*	C3DMatrix4 C3DMatrix4::operator *(const C3DMatrix3 &mat3x3) const
	{
		C3DMatrix4 mat;

		mat.m_f[0][0] = m_f[0][0] * mat3x3.m_f[0][0] + m_f[0][1] * mat3x3.m_f[1][0] + m_f[0][2] * mat3x3.m_f[2][0] ;
		mat.m_f[0][1] = m_f[0][0] * mat3x3.m_f[0][1] + m_f[0][1] * mat3x3.m_f[1][1] + m_f[0][2] * mat3x3.m_f[2][1] ;
		mat.m_f[0][2] = m_f[0][0] * mat3x3.m_f[0][2] + m_f[0][1] * mat3x3.m_f[1][2] + m_f[0][2] * mat3x3.m_f[2][2] ;
		mat.m_f[0][3] = m_f[0][0] * mat3x3.m_f[0][3] + m_f[0][1] * mat3x3.m_f[1][3] + m_f[0][2] * mat3x3.m_f[2][3];

		mat.m_f[1][0] = m_f[1][0] * mat3x3.m_f[0][0] + m_f[1][1] * mat3x3.m_f[1][0] + m_f[1][2] * mat3x3.m_f[2][0] ;
		mat.m_f[1][1] = m_f[1][0] * mat3x3.m_f[0][1] + m_f[1][1] * mat3x3.m_f[1][1] + m_f[1][2] * mat3x3.m_f[2][1] ;
		mat.m_f[1][2] = m_f[1][0] * mat3x3.m_f[0][2] + m_f[1][1] * mat3x3.m_f[1][2] + m_f[1][2] * mat3x3.m_f[2][2] ;
		mat.m_f[1][3] = m_f[1][0] * mat3x3.m_f[0][3] + m_f[1][1] * mat3x3.m_f[1][3] + m_f[1][2] * mat3x3.m_f[2][3] ;

		mat.m_f[2][0] = m_f[2][0] * mat3x3.m_f[0][0] + m_f[2][1] * mat3x3.m_f[1][0] + m_f[2][2] * mat3x3.m_f[2][0] ;
		mat.m_f[2][1] = m_f[2][0] * mat3x3.m_f[0][1] + m_f[2][1] * mat3x3.m_f[1][1] + m_f[2][2] * mat3x3.m_f[2][1] ;
		mat.m_f[2][2] = m_f[2][0] * mat3x3.m_f[0][2] + m_f[2][1] * mat3x3.m_f[1][2] + m_f[2][2] * mat3x3.m_f[2][2] ;
		mat.m_f[2][3] = m_f[2][0] * mat3x3.m_f[0][3] + m_f[2][1] * mat3x3.m_f[1][3] + m_f[2][2] * mat3x3.m_f[2][3] ;

		mat.m_f[3][0] = m_f[3][0];
		mat.m_f[3][1] = m_f[3][1];
		mat.m_f[3][2] = m_f[3][2];
		mat.m_f[3][3] = m_f[3][3];

		return mat;
	}*/

	C3DMatrix4 C3DMatrix4::operator *(const C3DMatrix4 &src) const
	{
		return concatenate(src);
	}

	C3DMatrix4	C3DMatrix4::operator *(const C3DQuaternion &qtn) const
	{
		C3DMatrix3 mat3;
		qtn.toRotationMatrix(mat3);
		return (*this) * (mat3);
	}

	C3DMatrix4& C3DMatrix4::operator*=(const C3DMatrix4 &mat2)
	{
		C3DMatrix4 mat(*this);

		m_f[0][0] = mat.m_f[0][0] * mat2.m_f[0][0] + mat.m_f[0][1] * mat2.m_f[1][0] + mat.m_f[0][2] * mat2.m_f[2][0] + mat.m_f[0][3] * mat2.m_f[3][0];
		m_f[0][1] = mat.m_f[0][0] * mat2.m_f[0][1] + mat.m_f[0][1] * mat2.m_f[1][1] + mat.m_f[0][2] * mat2.m_f[2][1] + mat.m_f[0][3] * mat2.m_f[3][1];
		m_f[0][2] = mat.m_f[0][0] * mat2.m_f[0][2] + mat.m_f[0][1] * mat2.m_f[1][2] + mat.m_f[0][2] * mat2.m_f[2][2] + mat.m_f[0][3] * mat2.m_f[3][2];
		m_f[0][3] = mat.m_f[0][0] * mat2.m_f[0][3] + mat.m_f[0][1] * mat2.m_f[1][3] + mat.m_f[0][2] * mat2.m_f[2][3] + mat.m_f[0][3] * mat2.m_f[3][3];

		m_f[1][0] = mat.m_f[1][0] * mat2.m_f[0][0] + mat.m_f[1][1] * mat2.m_f[1][0] + mat.m_f[1][2] * mat2.m_f[2][0] + mat.m_f[1][3] * mat2.m_f[3][0];
		m_f[1][1] = mat.m_f[1][0] * mat2.m_f[0][1] + mat.m_f[1][1] * mat2.m_f[1][1] + mat.m_f[1][2] * mat2.m_f[2][1] + mat.m_f[1][3] * mat2.m_f[3][1];
		m_f[1][2] = mat.m_f[1][0] * mat2.m_f[0][2] + mat.m_f[1][1] * mat2.m_f[1][2] + mat.m_f[1][2] * mat2.m_f[2][2] + mat.m_f[1][3] * mat2.m_f[3][2];
		m_f[1][3] = mat.m_f[1][0] * mat2.m_f[0][3] + mat.m_f[1][1] * mat2.m_f[1][3] + mat.m_f[1][2] * mat2.m_f[2][3] + mat.m_f[1][3] * mat2.m_f[3][3];

		m_f[2][0] = mat.m_f[2][0] * mat2.m_f[0][0] + mat.m_f[2][1] * mat2.m_f[1][0] + mat.m_f[2][2] * mat2.m_f[2][0] + mat.m_f[2][3] * mat2.m_f[3][0];
		m_f[2][1] = mat.m_f[2][0] * mat2.m_f[0][1] + mat.m_f[2][1] * mat2.m_f[1][1] + mat.m_f[2][2] * mat2.m_f[2][1] + mat.m_f[2][3] * mat2.m_f[3][1];
		m_f[2][2] = mat.m_f[2][0] * mat2.m_f[0][2] + mat.m_f[2][1] * mat2.m_f[1][2] + mat.m_f[2][2] * mat2.m_f[2][2] + mat.m_f[2][3] * mat2.m_f[3][2];
		m_f[2][3] = mat.m_f[2][0] * mat2.m_f[0][3] + mat.m_f[2][1] * mat2.m_f[1][3] + mat.m_f[2][2] * mat2.m_f[2][3] + mat.m_f[2][3] * mat2.m_f[3][3];

		m_f[3][0] = mat.m_f[3][0] * mat2.m_f[0][0] + mat.m_f[3][1] * mat2.m_f[1][0] + mat.m_f[3][2] * mat2.m_f[2][0] + mat.m_f[3][3] * mat2.m_f[3][0];
		m_f[3][1] = mat.m_f[3][0] * mat2.m_f[0][1] + mat.m_f[3][1] * mat2.m_f[1][1] + mat.m_f[3][2] * mat2.m_f[2][1] + mat.m_f[3][3] * mat2.m_f[3][1];
		m_f[3][2] = mat.m_f[3][0] * mat2.m_f[0][2] + mat.m_f[3][1] * mat2.m_f[1][2] + mat.m_f[3][2] * mat2.m_f[2][2] + mat.m_f[3][3] * mat2.m_f[3][2];
		m_f[3][3] = mat.m_f[3][0] * mat2.m_f[0][3] + mat.m_f[3][1] * mat2.m_f[1][3] + mat.m_f[3][2] * mat2.m_f[2][3] + mat.m_f[3][3] * mat2.m_f[3][3];

		return (*this);
	}

	C3DVector4 operator*(const C3DVector4 &lhs, const C3DMatrix4 &rhs)
	{
		return C3DVector4(
			(lhs.m_fX * rhs.m_f[0][0]) + (lhs.m_fY * rhs.m_f[1][0]) + (lhs.m_fZ * rhs.m_f[2][0]) + (lhs.m_fW * rhs.m_f[3][0]),
			(lhs.m_fX * rhs.m_f[0][1]) + (lhs.m_fY * rhs.m_f[1][1]) + (lhs.m_fZ * rhs.m_f[2][1]) + (lhs.m_fW * rhs.m_f[3][1]),
			(lhs.m_fX * rhs.m_f[0][2]) + (lhs.m_fY * rhs.m_f[1][2]) + (lhs.m_fZ * rhs.m_f[2][2]) + (lhs.m_fW * rhs.m_f[3][2]),
			(lhs.m_fX * rhs.m_f[0][3]) + (lhs.m_fY * rhs.m_f[1][3]) + (lhs.m_fZ * rhs.m_f[2][3]) + (lhs.m_fW * rhs.m_f[3][3]));
	}

	C3DVector3 operator*(const C3DVector3 &lhs, const C3DMatrix4 &rhs)
	{
		return C3DVector3(
			(lhs.m_fX * rhs.m_f[0][0]) + (lhs.m_fY * rhs.m_f[1][0]) + (lhs.m_fZ * rhs.m_f[2][0]),
			(lhs.m_fX * rhs.m_f[0][1]) + (lhs.m_fY * rhs.m_f[1][1]) + (lhs.m_fZ * rhs.m_f[2][1]),
			(lhs.m_fX * rhs.m_f[0][2]) + (lhs.m_fY * rhs.m_f[1][2]) + (lhs.m_fZ * rhs.m_f[2][2]));
	}

	Float32 C3DMatrix4::myMinor(BYTE r0, BYTE r1, BYTE r2, BYTE c0, BYTE c1, BYTE c2) const
	{
		return	m_f[r0][c0] * (m_f[r1][c1] * m_f[r2][c2] - m_f[r2][c1] * m_f[r1][c2]) -
				m_f[r0][c1] * (m_f[r1][c0] * m_f[r2][c2] - m_f[r2][c0] * m_f[r1][c2]) +
				m_f[r0][c2] * (m_f[r1][c0] * m_f[r2][c1] - m_f[r2][c0] * m_f[r1][c1]);
	}
