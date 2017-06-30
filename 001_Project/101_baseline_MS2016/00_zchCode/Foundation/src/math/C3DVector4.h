
#pragma once

#include "common/TypeDefine.h"
#include "common/CCRef.h"


	class C3DVector4 
	{
	public:// const define

	private:// const define

	public:// embed class or struct or enum

	private:// embed class or struct or enum

	public:// method
		C3DVector4();
		C3DVector4(const C3DVector4 &src);
		C3DVector4(Float32 fX, Float32 fY, Float32 fZ,Float32 fW);
		virtual ~C3DVector4();

		void			set(Float32 fx, Float32 fy, Float32 fz, Float32 fw)	{ m_fX = fx; m_fY = fy; m_fZ = fz; m_fW = fw; }
		void			setX(Float32 fValue)	{ m_fX = fValue; }
		Float32			getX() const		{ return m_fX; }
		void			setY(Float32 fValue)	{ m_fY = fValue; }
		Float32			getY() const		{ return m_fY; }
		void			setZ(Float32 fValue)	{ m_fZ = fValue; }
		Float32			getZ() const		{ return m_fZ; }
		void			setW(Float32 fValue)	{ m_fW = fValue; }
		Float32			getW() const		{ return m_fW;	}

		Float32			length() const;
		Float32			squaredLength() const;
		BOOLEAN			isZeroLength() const;
		Float32			distance(const C3DVector4 &vt) const;
		Float32			squaredDistance(const C3DVector4 &vt) const;

		Float32			normalise();
		C3DVector4		normalisedCopy() const;

		Float32			dotProduct(const C3DVector4 &vt) const;

		BOOLEAN			isNaN() const;

		C3DVector4&	operator =(const C3DVector4 &src);
		BOOLEAN		operator ==(const C3DVector4 &src) const;
		BOOLEAN		operator !=(const C3DVector4 &src) const;

		C3DVector4	operator +(const C3DVector4 &src) const;
		C3DVector4	operator -(const C3DVector4 &src) const;
		C3DVector4	operator *(Float32 fScalar) const;
		C3DVector4	operator /(Float32 fScalar) const;

		C3DVector4	operator +() const;
		C3DVector4	operator -() const;

		C3DVector4&	operator +=(const C3DVector4 &src);
		C3DVector4&	operator -=(const C3DVector4 &src);
		C3DVector4&	operator *=(Float32 fScalar);
		C3DVector4&	operator /=(Float32 fScalar);

		Float32*	ptr()	{ return &m_fX;	}

	protected:// method

	private:// method

	public: //property
		Float32	m_fX;
		Float32	m_fY;
		Float32	m_fZ;
		Float32	m_fW;

	protected:// property

	private:// property
		
	};
