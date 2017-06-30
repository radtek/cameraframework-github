
#pragma once

#include "common/TypeDefine.h"
#include "common/CCRef.h"


	class C3DVector3;
	class C3DMatrix3;
	class C3DQuaternion
	{
	public:// const define
		static	const	C3DQuaternion	ZERO;
		static	const	C3DQuaternion	IDENTITY;

	private:// const define
		static	const	Float32	EPSILON_VALUE;

	public:// embed class or struct or enum

	private:// embed class or struct or enum

	public:// method
		C3DQuaternion();
		C3DQuaternion(const C3DQuaternion &src);
		C3DQuaternion(const C3DMatrix3 &mat3);
		C3DQuaternion(Float32 fX, Float32 fY, Float32 fZ, Float32 fW);
		C3DQuaternion(const C3DVector3 &vtAxis, Float32 fAngle);
		C3DQuaternion(const C3DVector3 &vtAxisX, const C3DVector3 &vtAxisY, const C3DVector3 &vtAxisZ);
		virtual ~C3DQuaternion();

		static	C3DQuaternion	slerp(Float32 fT, const C3DQuaternion &qtnP, const C3DQuaternion &qtnQ, BOOLEAN bShortestPath = FALSE);
		static	C3DQuaternion	slerpExtraSpins(Float32 fT, const C3DQuaternion &qtnP, const C3DQuaternion &qtnQ, Int32 iExtraSpins);
		static	void			intermediate(const C3DQuaternion &qtn0, const C3DQuaternion &qtn1, const C3DQuaternion &qtn2, C3DQuaternion &qtnA, C3DQuaternion &qtnB);
		static	C3DQuaternion	squad(Float32 fT, const C3DQuaternion &qtnP, const C3DQuaternion &qtnA, const C3DQuaternion &qtnB, const C3DQuaternion &qtnQ, BOOLEAN bShortestPath = FALSE);
		static	C3DQuaternion	nlerp(Float32 fT, const C3DQuaternion &qtnP, const C3DQuaternion &qtnQ, BOOLEAN bShortestPath = FALSE);

		void			fromRotationMatrix (const C3DMatrix3& kRot);
        void			toRotationMatrix (C3DMatrix3& kRot) const;

		void			fromAxisAngle(const C3DVector3 &vtAxis, Float32 fAngle);
		void			toAxisAngle(C3DVector3 &vtAxis, Float32 &fAngle) const;
		void			fromAxes(const C3DVector3 &vtAxisX, const C3DVector3 &vtAxisY, const C3DVector3 &vtAxisZ);
		void			toAxes(C3DVector3 &vtAxisX, C3DVector3 &vtAxisY, C3DVector3 &vtAxisZ) const;

		C3DVector3		xAxis() const;
		C3DVector3		yAxis() const;
		C3DVector3		zAxis() const;

		void			fromHeadPitchRoll(Float32 fHead, Float32 fPitch, Float32 fRoll) ;
		void			toHeadPitchRoll(Float32& fHead, Float32& fPitch, Float32& fRoll) const;

		Float32			dotProduct(const C3DQuaternion &qtn) const;
		Float32			norm() const;

		Float32			normalise(); 
		C3DQuaternion	normalisedCopy() const;

		C3DQuaternion	inverse() const;
		C3DQuaternion	unitInverse() const;
		C3DQuaternion	exp() const;
		C3DQuaternion	log() const;

		BOOLEAN			equals(const C3DQuaternion &qtn, Float32 fTolerance) const;

		BOOLEAN			isNaN() const;

		C3DQuaternion&	operator =(const C3DQuaternion &src);
		BOOLEAN			operator ==(const C3DQuaternion &src) const;
		BOOLEAN			operator !=(const C3DQuaternion &src) const;

		C3DQuaternion	operator +(const C3DQuaternion &src) const;
		C3DQuaternion	operator -(const C3DQuaternion &src) const;
		C3DQuaternion	operator *(const C3DQuaternion &src) const;
		C3DQuaternion	operator *(Float32 fScalar) const;
		
		C3DQuaternion	operator +() const;
		C3DQuaternion	operator -() const;

		friend C3DVector3 operator *(const C3DVector3 &lhs, const C3DQuaternion& rhs);

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
