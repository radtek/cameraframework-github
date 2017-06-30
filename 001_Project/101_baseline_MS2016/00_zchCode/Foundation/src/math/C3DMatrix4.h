
#pragma once

#include "common/TypeDefine.h"
#include "common/CCRef.h"
#include "C3DMatrix3.h"
#include "C3DVector3.h"
#include "C3DVector4.h"
#include "C3DQuaternion.h"


	class C3DMatrix4
	{
	public:// const define	
		static	const	C3DMatrix4	ZERO;
		static	const	C3DMatrix4	ZEROAFFINE;
		static	const	C3DMatrix4	IDENTITY;
        static	const	C3DMatrix4	CLIPSPACE2DTOIMAGESPACE;

	private:// const define

	public:// embed class or struct or enum

	private:// embed class or struct or enum

	public:// method
		C3DMatrix4();
		C3DMatrix4(const C3DMatrix4 &src);
		C3DMatrix4(	Float32 f00, Float32 f01, Float32 f02, Float32 f03,
					Float32 f10, Float32 f11, Float32 f12, Float32 f13,
					Float32 f20, Float32 f21, Float32 f22, Float32 f23,
					Float32 f30, Float32 f31, Float32 f32, Float32 f33);
		~C3DMatrix4();

		void			setTrans( const C3DVector3 &vt);
		void			setTrans( Float32 fX, Float32 fY, Float32 fZ);
		C3DVector3		getTrans() const;
		void			makeTrans( const C3DVector3 &vt);
		void			makeTrans( Float32 fX, Float32 fY, Float32 fZ);

		void			setScale( const C3DVector3 &vt);
		void			setScale( Float32 fX, Float32 fY, Float32 fZ);
		C3DVector3		getScale() const;
		void			makeScale( const C3DVector3 &vt);
		void			makeScale( Float32 fX, Float32 fY, Float32 fZ);
		BOOLEAN			hasScale() const;
		BOOLEAN			hasNegativeScale() const;

		void	        rotateX(const Float32 fAngle);
		void            rotateY(const Float32 fAngle);
		void     		rotateZ(const Float32 fAngle);

		void			extract3x3Matrix(C3DMatrix3& m3x3) const;
		C3DQuaternion	extractQuaternion() const;

		BOOLEAN			isAffine() const;

		void			makeLookAt(const C3DVector3 &eye, const C3DVector3 &target, const C3DVector3 &up);
		void			makePerspective(Float32 fovx, Float32 aspect, Float32 znear, Float32 zfar);
		void			makePerspective(Float32 l, Float32 r, Float32 t, Float32 b, Float32 n, Float32 f);
		void			makeOrthognal(Float32 l, Float32 r, Float32 t, Float32 b, Float32 n, Float32 f);

		C3DMatrix4		concatenate(const C3DMatrix4 &mat2) const;
		C3DMatrix4		transpose() const;		
		C3DMatrix4		adjoint() const;
		Float32			determinant() const;
		C3DMatrix4		inverse() const;
		C3DMatrix4		inverseAffine() const;

		void			identity();

		void			makeTransform(const C3DVector3 &vtPosition, const C3DVector3 &vtScale, const C3DQuaternion &qtnOrientation);
		void			makeInverseTransform(const C3DVector3& position, const C3DVector3& scale, const C3DQuaternion &qtnOrientation);
		C3DMatrix4		concatenateAffine(const C3DMatrix4 &mat2) const;
		C3DVector3		transformAffine(const C3DVector3 &vt) const;

		C3DMatrix4&		operator =(const C3DMatrix3 &rhs);
		C3DMatrix4&		operator =(const C3DMatrix4 &rhs);
		BOOLEAN			operator ==(const C3DMatrix4 &rhs) const;
		BOOLEAN			operator !=(const C3DMatrix4 &rhs) const;

		C3DMatrix4		operator +(const C3DMatrix4 &rhs) const;
		C3DMatrix4		operator -(const C3DMatrix4 &rhs) const;
		C3DMatrix4		operator *(Float32 fScalar) const;
	//	C3DMatrix4		operator *(const C3DMatrix3 &rhs) const;
		C3DMatrix4		operator *(const C3DMatrix4 &rhs) const;
		C3DMatrix4		operator *(const C3DQuaternion &rhs) const;
		C3DMatrix4&		operator*=(const C3DMatrix4 &rhs);

		inline Float32 *operator[](UInt32 row)
		{
			return m_f[row];
		}

		inline const Float32 *operator[](UInt32 row) const
		{
			return m_f[row];
		}
		
		Float32*		ptr() const	{ return m_pf;	}

		friend C3DVector4 operator*(const C3DVector4 &lhs, const C3DMatrix4 &rhs);
		friend C3DVector3 operator*(const C3DVector3 &lhs, const C3DMatrix4 &rhs);
		//friend C3DMatrix4 operator*(float scalar, const C3DMatrix4 &rhs);

	protected:// method

	private:// method
		Float32	myMinor(BYTE r0, BYTE r1, BYTE r2, BYTE c0, BYTE c1, BYTE c2) const;

	public: //property
		Float32	m_f[4][4];
		Float32	*m_pf;

	protected:// property

	private:// property
		
	};
