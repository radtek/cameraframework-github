
#ifndef _ADAS_MATH_H
#define _ADAS_MATH_H

#include "common/TypeDefine.h"
#include "common/CCRef.h"

#include <math.h>


	/**
	* @class	Math	
	*			It is a arithmetic class. It defines math formula.
	*/
	class Math
	{
	public:// const define

	private:// const define

	public:// embed class or struct or enum

	private:// embed class or struct or enum

	public:// method
		static	Int32	abs(Int32 iValue)			{ return iValue < 0 ? -iValue : iValue; }
		static	Float32	abs(Float32 fValue)		{ return fValue < 0 ? -fValue : fValue; }
		
		static	Int32	getMin(Int32 iA, Int32 iB)			{ return iA < iB ? iA : iB; }
		static	UInt32	getMin(UInt32 uiA, UInt32 uiB)		{ return uiA < uiB ? uiA : uiB; }
		static	Float32	getMin(Float32 fA, Float32 fB)		{ return fA < fB ? fA : fB; }
		
		static	Int32	getMax(Int32 iA, Int32 iB)			{ return iA > iB ? iA : iB; }
		static	UInt32	getMax(UInt32 uiA, UInt32 uiB)		{ return uiA > uiB ? uiA : uiB; }
		static	Float32	getMax(Float32 fA, Float32 fB)		{ return fA > fB ? fA : fB; }
		
		static  Float32	clamp(Float32 fVal, Float32 fMinval, Float32 fMaxval);

		static	void	swapAtMinMax(Int32 &iA, Int32 &iB);
		static	void	swapAtMinMax(UInt32 &uiA, UInt32 &uiB);
		static	void	swapAtMinMax(Float32 &fA, Float32 &fB);
		//static	void	swapAtMinMax(DOUBLE &dA, DOUBLE &dB);

		static	void	swap(Float32 &fA, Float32 &fB);

		static	Int32		pow(Int32 iValue, UInt32 uiCount);
		static	Float32	pow(Float32 fValue, UInt32 uiCount);
		
		static  Float32	sqr(Float32 fValue);

		static  Float32	sqrt(Float32 fValue);

		static	Float32	invSqrt(Float32 fValue);

		static	Float32	toAngle(Float32 fRadian)	{ return fRadian * 57.29583f; }
		static	Float32	toRadian(Float32 fAngle)	{ return fAngle * 3.141593f / 180; }

		static	BOOLEAN	isZero(Float32 fValue)	{ return abs(fValue) < 1.0E-4 ? TRUE : FALSE; }

		static  BOOLEAN isEqual(Float32 f1, Float32 f2, Float32 fdis = Float32(1.0E-4) ) { return abs(f1-f2) < fdis ? TRUE : FALSE; }	

		static	BOOLEAN	isNaN(Float32 fValue)		{ return fValue != fValue; }


		static  Int32	sign (Float32 fValue);

///////////////////////////////////////////////////////////////////////////////////////////////
		// you must use radian when you use trigonometric functions.
		
		static	Float32	sin(Float32 dValue)		{ return std::sin(dValue); }
		static	Float32	cos(Float32 dValue)		{ return std::cos(dValue); }
		static	Float32	tan(Float32 dValue)		{ return std::tan(dValue); }

		static	Float32	asin(Float32 dValue)		{ return std::asin(dValue); }
		static	Float32	acos(Float32 dValue)		{ return std::acos(dValue); }
		static	Float32	atan(Float32 dValue)		{ return std::atan(dValue); }
		static	Float32	atan2(Float32 dValue1,Float32 dValue2)		{ return std::atan2(dValue1,dValue2); }

		static	Float32	sinh(Float32 dValue)		{ return std::sinh(dValue); }
		static	Float32	cosh(Float32 dValue)		{ return std::cosh(dValue); }
		static	Float32	tanh(Float32 dValue)		{ return std::tanh(dValue); }

		static	Float32	log(Float32 dValue)		{ return std::log(dValue); }
		static	Float32	log10(Float32 dValue)		{ return std::log10(dValue); }

		static	Float32	exp(Float32 dValue)		{ return std::exp(dValue); }

	protected:// method
		Math(){}
		Math(const Math&){}
		virtual ~Math(){}
		Math& operator =(const Math&){return *this;}

	private:// method

	public:// property
		static Float32 POS_INFINITY;
		static Float32 PI;
		static Float32 HALF_PI;
		static Float32 EPSILON;	        /* smallest such that 1.0+FLT_EPSILON != 1.0 */
		
	protected:// property

	private:// property

	};

#endif
