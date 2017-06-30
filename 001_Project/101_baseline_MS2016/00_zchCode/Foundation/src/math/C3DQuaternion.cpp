#include "C3DQuaternion.h"
#include "C3DMatrix3.h"
#include "CMath.h"

	const	C3DQuaternion	C3DQuaternion::ZERO( 0.0f, 0.0f, 0.0f, 0.0f );
	const	C3DQuaternion	C3DQuaternion::IDENTITY( 0.0f, 0.0f, 0.0f, 1.0f );
	const	Float32			C3DQuaternion::EPSILON_VALUE	= 0.001f;

	C3DQuaternion::C3DQuaternion()
		: m_fX(0.0f)
		, m_fY(0.0f)
		, m_fZ(0.0f)
		, m_fW(1.0f)
	{
		;
	}

	C3DQuaternion::C3DQuaternion(const C3DQuaternion &src) 
		: m_fX(src.m_fX)
		, m_fY(src.m_fY)
		, m_fZ(src.m_fZ)
		, m_fW(src.m_fW)
	{
		;
	}

	C3DQuaternion::C3DQuaternion(const C3DMatrix3 &mat3)
	{
		fromRotationMatrix(mat3);
	}

	C3DQuaternion::C3DQuaternion(Float32 fX, Float32 fY, Float32 fZ, Float32 fW)
		: m_fX(fX)
		, m_fY(fY)
		, m_fZ(fZ)
		, m_fW(fW)
	{
		;
	}

	C3DQuaternion::C3DQuaternion(const C3DVector3 &vtAxis, Float32 fAngle)
	{
		fromAxisAngle(vtAxis, fAngle);
	}

	C3DQuaternion::C3DQuaternion(const C3DVector3 &vtAxisX, const C3DVector3 &vtAxisY, const C3DVector3 &vtAxisZ)
	{
		fromAxes(vtAxisX, vtAxisY, vtAxisZ);
	}

	C3DQuaternion::~C3DQuaternion()
	{
		;
	}

	C3DQuaternion C3DQuaternion::slerp(Float32 fT, const C3DQuaternion &qtnP, const C3DQuaternion &qtnQ, BOOLEAN bShortestPath)
	{
		Float32 fCos = qtnP.dotProduct(qtnQ);
        C3DQuaternion rkT;

        // Do we need to invert rotation?
        if (fCos < 0.0f && bShortestPath)
        {
            fCos = -fCos;
            rkT = -qtnQ;
        }
        else
        {
            rkT = qtnQ;
        }

        if (Math::abs(fCos) < 1 - EPSILON_VALUE)
        {
            // Standard case (slerp)
            Float32 fSin = Math::sqrt(1 - Math::sqr(fCos));
            Float32 fAngle = Math::atan2(fSin, fCos);
            Float32 fInvSin = 1.0f / fSin;
            Float32 fCoeff0 = Math::sin((1.0f - fT) * fAngle) * fInvSin;
            Float32 fCoeff1 = Math::sin(fT * fAngle) * fInvSin;
            return qtnP * fCoeff0 + rkT * fCoeff1;
        }
        else
        {
            // too near then linear slerp
            C3DQuaternion t = qtnP * (1.0f - fT)  + rkT * fT;
            // taking the complement requires renormalisation
            t.normalise();
            return t;
        }
	}

	C3DQuaternion C3DQuaternion::slerpExtraSpins(Float32 fT, const C3DQuaternion &qtnP, const C3DQuaternion &qtnQ, Int32 iExtraSpins)
	{
		Float32 fCos = qtnP.dotProduct(qtnQ);
        Float32 fAngle ( Math::acos(fCos) );

        if ( Math::abs(fAngle) < EPSILON_VALUE )
            return qtnP;

        Float32 fSin = Math::sin(fAngle);
        Float32 fPhase ( Math::PI*iExtraSpins*fT );
        Float32 fInvSin = 1.0f/fSin;
        Float32 fCoeff0 = Math::sin((1.0f-fT)*fAngle - fPhase)*fInvSin;
        Float32 fCoeff1 = Math::sin(fT*fAngle + fPhase)*fInvSin;
        return qtnP * fCoeff0 + qtnQ * fCoeff1;
	}

	void C3DQuaternion::intermediate(const C3DQuaternion &qtn0, const C3DQuaternion &qtn1, const C3DQuaternion &qtn2, C3DQuaternion &qtnA, C3DQuaternion &qtnB)
	{
		C3DQuaternion kQ0inv = qtn0.unitInverse();
        C3DQuaternion kQ1inv = qtn1.unitInverse();
        C3DQuaternion rkP0 = kQ0inv*qtn1;
        C3DQuaternion rkP1 = kQ1inv*qtn2;
        C3DQuaternion kArg = (qtn0.log()-qtn1.log()) * 0.25f;
        C3DQuaternion kMinusArg = -kArg;

        qtnA = qtn1*kArg.exp();
        qtnB = qtn1*kMinusArg.exp();
	}

	C3DQuaternion C3DQuaternion::squad(Float32 fT, const C3DQuaternion &qtnP, const C3DQuaternion &qtnA, const C3DQuaternion &qtnB, const C3DQuaternion &qtnQ, BOOLEAN bShortestPath)
	{
		Float32 fSlerpT = 2.0f*fT*(1.0f-fT);
        C3DQuaternion kSlerpP = slerp(fT, qtnP, qtnQ, bShortestPath);
        C3DQuaternion kSlerpQ = slerp(fT, qtnA, qtnB);
        return slerp(fSlerpT, kSlerpP ,kSlerpQ);
	}

	C3DQuaternion C3DQuaternion::nlerp(Float32 fT, const C3DQuaternion &qtnP, const C3DQuaternion &qtnQ, BOOLEAN bShortestPath)
	{
		C3DQuaternion result;
        Float32 fCos = qtnP.dotProduct(qtnQ);
		if (fCos < 0.0f && bShortestPath)
		{
			result = qtnP + ((-qtnQ) - qtnP) * fT;
		}
		else
		{
			result = qtnP + (qtnQ - qtnP) * fT;
		}
        result.normalise();
        return result;
	}

	void C3DQuaternion::fromRotationMatrix (const C3DMatrix3& kRot)
	{
		Float32 fTrace = kRot[0][0]+kRot[1][1]+kRot[2][2];
        Float32 fRoot;

        if ( fTrace > 0.0F )
        {
            // |m_fW| > 1/2, may as well choose m_fW > 1/2
            fRoot = Math::sqrt(fTrace + 1.0f);  // 2w
            m_fW = 0.5f*fRoot;
            fRoot = 0.5f/fRoot;  // 1/(4w)
            m_fX = -(kRot[2][1]-kRot[1][2])*fRoot;
            m_fY = -(kRot[0][2]-kRot[2][0])*fRoot;
            m_fZ = -(kRot[1][0]-kRot[0][1])*fRoot  ;
        }
        else
        {
            // |m_fW| <= 1/2
            static size_t s_iNext[3] = { 1, 2, 0 };
            size_t i = 0;
            if ( kRot[1][1] > kRot[0][0] )
                i = 1;
            if ( kRot[2][2] > kRot[i][i] )
                i = 2;
            size_t j = s_iNext[i];
            size_t k = s_iNext[j];

            fRoot = Math::sqrt(kRot[i][i]-kRot[j][j]-kRot[k][k] + 1.0f);
            Float32* apkQuat[3] = { &m_fX, &m_fY, &m_fZ };
            *apkQuat[i] = 0.5f*fRoot;
            fRoot = 0.5f/fRoot;
            m_fW = (kRot[j][k]-kRot[k][j])*fRoot;
            *apkQuat[j] = (kRot[j][i]+kRot[i][j])*fRoot;
            *apkQuat[k] = (kRot[k][i]+kRot[i][k])*fRoot;
        }
	}

    void C3DQuaternion::toRotationMatrix (C3DMatrix3& kRot) const
	{
		Float32 fTx  = m_fX+m_fX;
        Float32 fTy  = m_fY+m_fY;
        Float32 fTz  = m_fZ+m_fZ;
        Float32 fTwx = fTx*m_fW;
        Float32 fTwy = fTy*m_fW;
        Float32 fTwz = fTz*m_fW;
        Float32 fTxx = fTx*m_fX;
        Float32 fTxy = fTy*m_fX;
        Float32 fTxz = fTz*m_fX;
        Float32 fTyy = fTy*m_fY;
        Float32 fTyz = fTz*m_fY;
        Float32 fTzz = fTz*m_fZ;

        kRot[0][0] = 1.0f-(fTyy+fTzz);
        kRot[0][1] = fTxy+fTwz;
        kRot[0][2] = fTxz-fTwy;

        kRot[1][0] = fTxy-fTwz;
        kRot[1][1] = 1.0f-(fTxx+fTzz);
        kRot[1][2] = fTyz+fTwx;

        kRot[2][0] = fTxz+fTwy;
        kRot[2][1] = fTyz-fTwx;
        kRot[2][2] = 1.0f-(fTxx+fTyy);
	}

	void C3DQuaternion::fromAxisAngle(const C3DVector3 &rkAxis, Float32 fAngle)
	{
		// The quaternion representing the rotation is
        //   q = cos(A/2)+sin(A/2)*(m_fX*i+m_fY*j+m_fZ*k)
		Float32 fHalfAngle ( 0.5F*fAngle );
        Float32 fSin = Math::sin(fHalfAngle);
        m_fW = Math::cos(fHalfAngle);
        m_fX = fSin * rkAxis.m_fX;
        m_fY = fSin * rkAxis.m_fY;
        m_fZ = fSin * rkAxis.m_fZ;
	}

	void C3DQuaternion::toAxisAngle(C3DVector3 &vtAxis, Float32 &fAngle) const
	{
		// The quaternion representing the rotation is
        //   q = cos(A/2)+sin(A/2)*(m_fX*i+m_fY*j+m_fZ*k)

        Float32 fSqrLength = m_fX*m_fX+m_fY*m_fY+m_fZ*m_fZ;
        if ( fSqrLength > 0.0f )
        {
            fAngle = 2.0f*Math::acos(m_fW);
            Float32 fInvLength = Math::invSqrt(fSqrLength);
            vtAxis.m_fX = m_fX*fInvLength;
            vtAxis.m_fY = m_fY*fInvLength;
            vtAxis.m_fZ = m_fZ*fInvLength;
        }
        else
        {
            // angle is 0 (mod 2*pi), so any axis will do
            fAngle = Float32(0.0f);
            vtAxis.m_fX = 1.0f;
            vtAxis.m_fY = 0.0f;
            vtAxis.m_fZ = 0.0f;
        }
	}

	void C3DQuaternion::fromAxes(const C3DVector3 &vtAxisX, const C3DVector3 &vtAxisY, const C3DVector3 &vtAxisZ)
	{
		C3DMatrix3 kRot;

        kRot[0][0] = vtAxisX.m_fX;
        kRot[0][1] = vtAxisX.m_fY;
        kRot[0][2] = vtAxisX.m_fZ;

        kRot[1][0] = vtAxisY.m_fX;
        kRot[1][1] = vtAxisY.m_fY;
        kRot[1][2] = vtAxisY.m_fZ;

        kRot[2][0] = vtAxisZ.m_fX;
        kRot[2][1] = vtAxisZ.m_fY;
        kRot[2][2] = vtAxisZ.m_fZ;

        fromRotationMatrix(kRot);
	}

	void C3DQuaternion::toAxes(C3DVector3 &vtAxisX, C3DVector3 &vtAxisY, C3DVector3 &vtAxisZ) const
	{
		C3DMatrix3 kRot;

        toRotationMatrix(kRot);

        vtAxisX.m_fX = kRot[0][0];
        vtAxisX.m_fY = kRot[0][1];
        vtAxisX.m_fZ = kRot[0][2];

        vtAxisY.m_fX = kRot[1][0];
        vtAxisY.m_fY = kRot[1][1];
        vtAxisY.m_fZ = kRot[1][2];

        vtAxisZ.m_fX = kRot[2][0];
        vtAxisZ.m_fY = kRot[2][1];
        vtAxisZ.m_fZ = kRot[2][2];
	}

	C3DVector3 C3DQuaternion::xAxis() const
	{
		Float32 fTy  = 2.0f*m_fY;
        Float32 fTz  = 2.0f*m_fZ;
        Float32 fTwy = fTy*m_fW;
        Float32 fTwz = fTz*m_fW;
        Float32 fTxy = fTy*m_fX;
        Float32 fTxz = fTz*m_fX;
        Float32 fTyy = fTy*m_fY;
        Float32 fTzz = fTz*m_fZ;

        return C3DVector3(1.0f-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);
	}

	C3DVector3 C3DQuaternion::yAxis() const
	{
		Float32 fTx  = 2.0f*m_fX;
        Float32 fTy  = 2.0f*m_fY;
        Float32 fTz  = 2.0f*m_fZ;
        Float32 fTwx = fTx*m_fW;
        Float32 fTwz = fTz*m_fW;
        Float32 fTxx = fTx*m_fX;
        Float32 fTxy = fTy*m_fX;
        Float32 fTyz = fTz*m_fY;
        Float32 fTzz = fTz*m_fZ;

        return C3DVector3(fTxy-fTwz, 1.0f-(fTxx+fTzz), fTyz+fTwx);
	}

	C3DVector3 C3DQuaternion::zAxis() const
	{
		Float32 fTx  = 2.0f*m_fX;
        Float32 fTy  = 2.0f*m_fY;
        Float32 fTz  = 2.0f*m_fZ;
        Float32 fTwx = fTx*m_fW;
        Float32 fTwy = fTy*m_fW;
        Float32 fTxx = fTx*m_fX;
        Float32 fTxz = fTz*m_fX;
        Float32 fTyy = fTy*m_fY;
        Float32 fTyz = fTz*m_fY;

        return C3DVector3(fTxz+fTwy, fTyz-fTwx, 1.0f-(fTxx+fTyy));
	}

	void C3DQuaternion::fromHeadPitchRoll(Float32 fHead, Float32 fPitch, Float32 fRoll) 
	{
		C3DMatrix3 mat;
		mat.fromEulerAnglesYXZ(fHead, fPitch, fRoll);
		fromRotationMatrix(mat);
	}

	void C3DQuaternion::toHeadPitchRoll(Float32& fHead, Float32& fPitch, Float32& fRoll) const
	{
		C3DMatrix3 mat;
		toRotationMatrix(mat);
		mat.toEulerAnglesYXZ(fHead, fPitch, fRoll);
	}

	Float32 C3DQuaternion::dotProduct(const C3DQuaternion &qtn) const
	{
		return m_fX * qtn.m_fX + m_fY * qtn.m_fY + m_fZ * qtn.m_fZ + m_fW * qtn.m_fW;
	}

	Float32 C3DQuaternion::norm() const
	{
		return m_fX * m_fX + m_fY * m_fY + m_fZ * m_fZ + m_fW * m_fW;
	}

	Float32 C3DQuaternion::normalise()
	{
		Float32 fLen = norm();

		if (fLen > 0.0f)
		{
			Float32 fFactor = 1.0f / (Float32)Math::sqrt(fLen);
			m_fX *= fFactor;
			m_fY *= fFactor;
			m_fZ *= fFactor;
			m_fW *= fFactor;
		}

		return fLen;
	}

	C3DQuaternion C3DQuaternion::normalisedCopy() const
	{
		C3DQuaternion qtn = *this;
		qtn.normalise();
		return qtn;
	}

	C3DQuaternion C3DQuaternion::inverse() const
	{
		Float32 fNorm = m_fW*m_fW+m_fX*m_fX+m_fY*m_fY+m_fZ*m_fZ;
        if ( fNorm > 0.0f )
        {
            Float32 fInvNorm = 1.0f/fNorm;
            return C3DQuaternion(m_fW*fInvNorm,-m_fX*fInvNorm,-m_fY*fInvNorm,-m_fZ*fInvNorm);
        }
        else
        {
            // return an invalid result to flag the error
            return ZERO;
        }
	}

	C3DQuaternion C3DQuaternion::unitInverse() const
	{
		return C3DQuaternion(m_fW,-m_fX,-m_fY,-m_fZ);
	}

	C3DQuaternion C3DQuaternion::exp() const
	{
		Float32 fAngle ( Math::sqrt(m_fX*m_fX+m_fY*m_fY+m_fZ*m_fZ) );
        Float32 fSin = Math::sin(fAngle);

        C3DQuaternion kResult;
        kResult.m_fW = Math::cos(fAngle);

        if ( Math::abs(fSin) >= EPSILON_VALUE )
        {
            Float32 fCoeff = fSin/(fAngle);
            kResult.m_fX = fCoeff*m_fX;
            kResult.m_fY = fCoeff*m_fY;
            kResult.m_fZ = fCoeff*m_fZ;
        }
        else
        {
            kResult.m_fX = m_fX;
            kResult.m_fY = m_fY;
            kResult.m_fZ = m_fZ;
        }

        return kResult;
	}

	C3DQuaternion C3DQuaternion::log() const
	{
		C3DQuaternion kResult;
        kResult.m_fW = 0.0f;

        if ( Math::abs(m_fW) < 1.0f )
        {
            Float32 fAngle ( Math::acos(m_fW) );
            Float32 fSin = Math::sin(fAngle);
            if ( Math::abs(fSin) >= EPSILON_VALUE )
            {
                Float32 fCoeff = fAngle/fSin;
                kResult.m_fX = fCoeff*m_fX;
                kResult.m_fY = fCoeff*m_fY;
                kResult.m_fZ = fCoeff*m_fZ;
                return kResult;
            }
        }

        kResult.m_fX = m_fX;
        kResult.m_fY = m_fY;
        kResult.m_fZ = m_fZ;

        return kResult;
	}

	BOOLEAN C3DQuaternion::equals(const C3DQuaternion &qtn, Float32 fTolerance) const
	{
		Float32 fCos = dotProduct(qtn);
        Float32 angle = Math::acos(fCos);

		return (Math::abs(angle) <= fTolerance)
            || Math::isEqual(angle, Math::PI, fTolerance);

	}

	BOOLEAN C3DQuaternion::isNaN() const
	{
		return Math::isNaN(m_fX) || Math::isNaN(m_fY) || Math::isNaN(m_fZ) || Math::isNaN(m_fW);
	}

	C3DQuaternion& C3DQuaternion::operator =(const C3DQuaternion &src)
	{
		m_fX = src.m_fX;
		m_fY = src.m_fY;
		m_fZ = src.m_fZ;
		m_fW = src.m_fW;

		return *this;
	}

	BOOLEAN C3DQuaternion::operator ==(const C3DQuaternion &src) const
	{
		return	   Math::isZero(m_fX - src.m_fX) 
				&& Math::isZero(m_fY - src.m_fY) 
				&& Math::isZero(m_fZ - src.m_fZ)
				&& Math::isZero(m_fW - src.m_fW);
	}

	BOOLEAN C3DQuaternion::operator !=(const C3DQuaternion &src) const
	{
		return	!operator==(src);
	}

	C3DQuaternion C3DQuaternion::operator +(const C3DQuaternion &src) const
	{
		return C3DQuaternion(m_fX + src.m_fX, m_fY + src.m_fY, m_fZ + src.m_fZ, m_fZ + src.m_fW);
	}

	C3DQuaternion C3DQuaternion::operator -(const C3DQuaternion &src) const
	{
		return C3DQuaternion(m_fX - src.m_fX, m_fY - src.m_fY, m_fZ - src.m_fZ, m_fZ - src.m_fW);
	}

	C3DQuaternion C3DQuaternion::operator *(const C3DQuaternion &src) const
	{
		return C3DQuaternion
			(			
				m_fW * src.m_fX + m_fX * src.m_fW + m_fY * src.m_fZ - m_fZ * src.m_fY,
				m_fW * src.m_fY + m_fY * src.m_fW + m_fZ * src.m_fX - m_fX * src.m_fZ,
				m_fW * src.m_fZ + m_fZ * src.m_fW + m_fX * src.m_fY - m_fY * src.m_fX,
				m_fW * src.m_fW - m_fX * src.m_fX - m_fY * src.m_fY - m_fZ * src.m_fZ
			);
	}

	C3DQuaternion C3DQuaternion::operator *(Float32 fScalar) const
	{
		return C3DQuaternion(m_fX * fScalar, m_fY * fScalar, m_fZ * fScalar, m_fW * fScalar);
	}

	C3DQuaternion C3DQuaternion::operator +() const
	{
		return C3DQuaternion(m_fX, m_fY, m_fZ, m_fW);
	}

	C3DQuaternion C3DQuaternion::operator -() const
	{
		return C3DQuaternion(-m_fX, -m_fY, -m_fZ, -m_fW);
	}

	C3DVector3 operator *(const C3DVector3 &lhs, const C3DQuaternion& rhs)
	{
		C3DVector3 uvt, uuvt;
		C3DVector3 qvec(rhs.m_fX, rhs.m_fY, rhs.m_fZ);
		uvt = qvec.crossProduct(lhs);
		uuvt = qvec.crossProduct(uvt);
		uvt *= (2.0f * rhs.m_fW);
		uuvt *= 2.0f;

		return lhs + uvt + uuvt;
	}
