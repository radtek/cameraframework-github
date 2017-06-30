#include "CMath.h"


	Float32 Math::POS_INFINITY = -10000.0f;
	Float32 Math::PI = 3.1415F;
	Float32 Math::HALF_PI = 1.5707F;
	Float32 Math::EPSILON = 1.192092896e-07F;

	Float32 Math::clamp(Float32 fVal, Float32 fMinval, Float32 fMaxval)
	{
		return getMax( getMin( fVal, fMaxval), fMinval);
	}

	void Math::swapAtMinMax(Int32 &iA, Int32 &iB)
	{
		if (iA > iB)
		{
			Int32 iTemp = iA;
			iA = iB;
			iB = iTemp;
		}
	}

	void Math::swapAtMinMax(UInt32 &uiA, UInt32 &uiB)
	{
		if (uiA > uiB)
		{
			UInt32 uiTemp = uiA;
			uiA = uiB;
			uiB = uiTemp;
		}
	}

	void Math::swapAtMinMax(Float32 &fA, Float32 &fB)
	{
		if (fA > fB)
		{
			Float32 fTemp = fA;
			fA = fB;
			fB = fTemp;
		}
	}

	void Math::swap(Float32 &fA, Float32 &fB)
	{
		Float32 fTemp = fA;
		fA = fB;
		fB = fTemp;
	}

	Int32 Math::pow(Int32 iValue, UInt32 uiCount)
	{
		Int32 iRet = 1;
		for (UInt32 i = 0; i < uiCount; i++)
		{
			iRet *= iValue;
		}

		return iRet;
	}

	Float32 Math::pow(Float32 fValue, UInt32 uiCount)
	{
		Float32 fRet = 1;
		for (UInt32 i = 0; i < uiCount; i++)
		{
			fRet *= fValue;
		}

		return fRet;
	}

	Float32 Math::sqr(Float32 fValue)
	{
		return fValue * fValue;
	}

	Float32 Math::sqrt(Float32 fValue)
	{
		Float32 fEpsilonNum,fGuessNum;
		fEpsilonNum = (Float32)1.0E-5;
		fGuessNum = 1.0f;

		while( abs(fGuessNum * fGuessNum - abs(fValue)) >= fEpsilonNum )
		{
			fGuessNum = (Float32)((abs(fValue) / fGuessNum + fGuessNum) / 2.0f);
		}

		return fGuessNum;
	}

	Float32 Math::invSqrt(Float32 fValue)
	{
		return 1.0f/fValue;
	}

	Int32 Math::sign (Float32 fValue)
    {
        if ( fValue > 0.0f )
            return 1;

        if ( fValue < 0.0f )
            return -1;

        return 0;
    }
