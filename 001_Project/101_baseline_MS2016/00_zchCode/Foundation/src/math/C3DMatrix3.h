
#pragma once

#include "common/TypeDefine.h"
#include "common/CCRef.h"
#include "C3DVector3.h"

	class C3DMatrix3
	{
	public:// const define	
		static	const	C3DMatrix3	ZERO;
		static	const	C3DMatrix3	ZEROAFFINE;
		static	const	C3DMatrix3	IDENTITY;
        static	const	C3DMatrix3	CLIPSPACE2DTOIMAGESPACE;

	private:// const define

	public:// embed class or struct or enum

	private:// embed class or struct or enum

	public:// method
		C3DMatrix3();
		C3DMatrix3(const Float32 arr[3][3]);
		C3DMatrix3(const C3DMatrix3 &src);
		C3DMatrix3(	Float32 f00, Float32 f01, Float32 f02,
					Float32 f10, Float32 f11, Float32 f12,
					Float32 f20, Float32 f21, Float32 f22);
		~C3DMatrix3();

		void		swap(C3DMatrix3& other);
		Float32*	operator[] (UInt32 uiRow) const;
		C3DVector3	getColumn (UInt32 uiCol) const;
		void		setColumn(UInt32 uiCol, const C3DVector3& vec);
        
		C3DMatrix3& operator= (const C3DMatrix3& rkMatrix);
		BOOLEAN		operator== (const C3DMatrix3& rkMatrix) const;
		BOOLEAN		operator!= (const C3DMatrix3& rkMatrix) const;
        C3DMatrix3	operator+ (const C3DMatrix3& rkMatrix) const;
        C3DMatrix3	operator- (const C3DMatrix3& rkMatrix) const;
        C3DMatrix3	operator* (const C3DMatrix3& rkMatrix) const;
		C3DMatrix3	operator* (const C3DQuaternion &qtn) const;
        C3DMatrix3	operator- () const;

		C3DVector3	operator* (const C3DVector3& rkVector) const;
        C3DMatrix3	operator* (Float32 fScalar) const;
      
        // utilities
        C3DMatrix3	transpose () const;
        BOOLEAN		inverse (C3DMatrix3& rkInverse, Float32 fTolerance = 1e-06) const;
        C3DMatrix3	inverse (Float32 fTolerance = 1e-06) const;
        Float32		determinant () const;

		void		fromAxes(const C3DVector3& xAxis, const C3DVector3& yAxis, const C3DVector3& zAxis);
		void		fromAxisAngle (const C3DVector3& rkAxis, const Float32& fRadians);
		void		toAxisAngle (C3DVector3& rkAxis, Float32& rfAngle) const;
		
        // The matrix must be orthonormal.  The decomposition is yaw*pitch*roll
        // where yaw is rotation about the Up vector, pitch is rotation about the
        // Right axis, and roll is rotation about the Direction axis.
		BOOLEAN		toEulerAnglesYXZ (Float32& rfYAngle, Float32& rfPAngle, Float32& rfRAngle) const;
        void		fromEulerAnglesYXZ (Float32 fYAngle, Float32 fPAngle, Float32 fRAngle);
       
		BOOLEAN		hasScale() const;

	protected:// method

	private:// method
		
	public: //property
		Float32	m_f[3][3];
		
	protected:// property

	private:// property
		
	};
