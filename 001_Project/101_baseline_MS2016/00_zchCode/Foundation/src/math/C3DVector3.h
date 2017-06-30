
#pragma once

#include "common/TypeDefine.h"
#include "common/CCRef.h"
#include "C3DQuaternion.h"


	class C3DVector3
	{
	public:// const define
		static	const	C3DVector3	ZERO;
		static	const	C3DVector3	UNIT_X;
		static	const	C3DVector3	UNIT_Y;
		static	const	C3DVector3	UNIT_Z;
		static	const	C3DVector3	NEGATIVE_UNIT_X;
		static	const	C3DVector3	NEGATIVE_UNIT_Y;
		static	const	C3DVector3	NEGATIVE_UNIT_Z;
		static	const	C3DVector3	UNIT_SCALE;

	private:// const define

	public:// embed class or struct or enum

	private:// embed class or struct or enum

	public:// method
		C3DVector3();
		C3DVector3(const C3DVector3 &src);
		C3DVector3(Float32 fX, Float32 fY, Float32 fZ);
		~C3DVector3();

		void			set(Float32 fx, Float32 fy, Float32 fz)	{ m_fX = fx; m_fY = fy; m_fZ = fz;	}
		void			setX(Float32 fValue)					{ m_fX = fValue; }
		Float32			getX() const						{ return m_fX; }
		void			setY(Float32 fValue)					{ m_fY = fValue; }
		Float32			getY() const						{ return m_fY; }
		void			setZ(Float32 fValue)					{ m_fZ = fValue; }
		Float32			getZ() const						{ return m_fZ; }

		Float32			length() const;
		Float32			squaredLength() const;
		BOOLEAN			isZeroLength() const;
		Float32			distance(const C3DVector3 &vt) const;
		Float32			squaredDistance(const C3DVector3 &vt) const;

		Float32			normalise();
		C3DVector3		normalisedCopy() const;

		Float32			dotProduct(const C3DVector3 &vt) const;
		Float32			absDotProduct(const C3DVector3 &vt) const;
		C3DVector3		crossProduct(const C3DVector3 &vt) const;

		C3DVector3		midPoint(const C3DVector3 &vt) const;
		void			makeFloor(const C3DVector3 &vt);
		void			makeCeil(const C3DVector3 &vt);

		C3DVector3		perpendicular() const;
		C3DVector3		reflect(const C3DVector3 &vtNormal) const;
		C3DVector3		primaryAxis() const;

		Float32			angleBetween(const C3DVector3 &vtDest) const;
		C3DQuaternion	getRotationTo(const C3DVector3 &vtDest, const C3DVector3& vtFallbackAxis = C3DVector3::ZERO) const;
		BOOLEAN			positionEquals(const C3DVector3 &vt, Float32 fTolerance = 0.001) const;
		BOOLEAN			positionCloses(const C3DVector3 &vt, Float32 fTolerance = 0.001) const;
		BOOLEAN			directionEquals(const C3DVector3 &vt, Float32 fTolerance) const;
		
		BOOLEAN			isNaN() const;

		C3DVector3&	operator =(const C3DVector3 &src);
		BOOLEAN		operator ==(const C3DVector3 &rhs) const;
		BOOLEAN		operator !=(const C3DVector3 &rhs) const;
		BOOLEAN		operator >(const C3DVector3 &rhs) const;
		BOOLEAN		operator <(const C3DVector3 &rhs) const;

		C3DVector3	operator +(const C3DVector3 &src) const;
		C3DVector3	operator -(const C3DVector3 &src) const;
		C3DVector3	operator *(const C3DVector3 &src) const;
		C3DVector3	operator *(Float32 fScalar) const;
		C3DVector3	operator /(Float32 fScalar) const;

		C3DVector3	operator +() const;
		C3DVector3	operator -() const;

		C3DVector3&	operator +=(const C3DVector3 &src);
		C3DVector3&	operator -=(const C3DVector3 &src);
		C3DVector3	operator *=(const C3DVector3 &src);
		C3DVector3&	operator *=(Float32 fScalar);
		C3DVector3&	operator /=(Float32 fScalar);

		inline Float32  operator [] (UInt32 i) const		{  return *(&m_fX+i);	}
		inline Float32& operator [] (UInt32 i )				{  return *(&m_fX+i);	}
		Float32*	ptr()									{  return &m_fX;		}

	protected:// method

	private:// method

	public: //property
		Float32	m_fX;
		Float32	m_fY;
		Float32	m_fZ;

	protected:// property

	private:// property
		
	};
