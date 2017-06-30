#include "C3DMatrix3.h"
#include "CMath.h"
#include <memory.h>

    const C3DMatrix3 C3DMatrix3::ZERO(0.0F, 0.0F, 0.0F, 
									  0.0F, 0.0F, 0.0F,
									  0.0F, 0.0F, 0.0F);
    const C3DMatrix3 C3DMatrix3::IDENTITY( 1.0F, 0.0F, 0.0F, 
										   0.0F, 1.0F, 0.0F,
										   0.0F, 0.0F, 1.0F);

	C3DMatrix3::C3DMatrix3()
	{
		;
	}

	C3DMatrix3::C3DMatrix3(const Float32 arr[3][3])
	{
		memcpy(m_f,arr,9*sizeof(Float32));
	}

	C3DMatrix3::C3DMatrix3(const C3DMatrix3 &src)
	{
		memcpy(m_f, src.m_f, sizeof(m_f));
	}

	C3DMatrix3::C3DMatrix3(	Float32 f00, Float32 f01, Float32 f02,
					Float32 f10, Float32 f11, Float32 f12,
					Float32 f20, Float32 f21, Float32 f22)
	{
		m_f[0][0] = f00;
		m_f[0][1] = f01;
		m_f[0][2] = f02;
		m_f[1][0] = f10;
		m_f[1][1] = f11;
		m_f[1][2] = f12;
		m_f[2][0] = f20;
		m_f[2][1] = f21;
		m_f[2][2] = f22;
	}

	C3DMatrix3::~C3DMatrix3()
	{
	}

	void C3DMatrix3::swap(C3DMatrix3& other)
	{
		Math::swap(m_f[0][0], other.m_f[0][0]);
		Math::swap(m_f[0][1], other.m_f[0][1]);
		Math::swap(m_f[0][2], other.m_f[0][2]);
		Math::swap(m_f[1][0], other.m_f[1][0]);
		Math::swap(m_f[1][1], other.m_f[1][1]);
		Math::swap(m_f[1][2], other.m_f[1][2]);
		Math::swap(m_f[2][0], other.m_f[2][0]);
		Math::swap(m_f[2][1], other.m_f[2][1]);
		Math::swap(m_f[2][2], other.m_f[2][2]);
	}

	Float32* C3DMatrix3::operator[] (UInt32 uiRow) const
	{
		return (Float32*)m_f[uiRow];
	}

	C3DVector3 C3DMatrix3::getColumn (UInt32 uiCol) const
	{
		 return C3DVector3(m_f[0][uiCol],m_f[1][uiCol],
            m_f[2][uiCol]);
	}

	void C3DMatrix3::setColumn(UInt32 uiCol, const C3DVector3& vec)
	{
		m_f[0][uiCol] = vec.m_fX;
        m_f[1][uiCol] = vec.m_fY;
        m_f[2][uiCol] = vec.m_fZ;
	}
        
	C3DMatrix3& C3DMatrix3::operator= (const C3DMatrix3& rkMatrix)
	{
		memcpy(m_f, rkMatrix.m_f, sizeof(m_f));
		return *this;
	}

	BOOLEAN	C3DMatrix3::operator== (const C3DMatrix3& rkMatrix) const
	{
		for (UInt32 uiRow = 0; uiRow < 3; ++uiRow)
        {
            for (UInt32 uiCol = 0; uiCol < 3; ++uiCol)
            {
				if ( !Math::isEqual( m_f[uiRow][uiCol], rkMatrix.m_f[uiRow][uiCol]) )
                    return FALSE;
            }
        }

        return TRUE;
	}

	BOOLEAN C3DMatrix3::operator!= (const C3DMatrix3& rkMatrix) const
	{
		return !operator==(rkMatrix);
	}

    C3DMatrix3 C3DMatrix3::operator+ (const C3DMatrix3& rkMatrix) const
	{
		C3DMatrix3 kSum;
        for (UInt32 uiRow = 0; uiRow < 3; ++uiRow)
        {
            for (UInt32 uiCol = 0; uiCol < 3; ++uiCol)
            {
                kSum.m_f[uiRow][uiCol] = m_f[uiRow][uiCol] +
                    rkMatrix.m_f[uiRow][uiCol];
            }
        }
        return kSum;
	}

    C3DMatrix3 C3DMatrix3::operator- (const C3DMatrix3& rkMatrix) const
	{
		C3DMatrix3 kDiff;
        for (UInt32 uiRow = 0; uiRow < 3; ++uiRow)
        {
            for (UInt32 uiCol = 0; uiCol < 3; ++uiCol)
            {
                kDiff.m_f[uiRow][uiCol] = m_f[uiRow][uiCol] -
                    rkMatrix.m_f[uiRow][uiCol];
            }
        }
        return kDiff;
	}

    C3DMatrix3 C3DMatrix3::operator* (const C3DMatrix3& rkMatrix) const
	{
		C3DMatrix3 kProd;
        for (UInt32 uiRow = 0; uiRow < 3; ++uiRow)
        {
            for (UInt32 uiCol = 0; uiCol < 3; ++uiCol)
            {
                kProd.m_f[uiRow][uiCol] =
                   m_f[uiRow][0] * rkMatrix.m_f[0][uiCol] +
                   m_f[uiRow][1] * rkMatrix.m_f[1][uiCol] +
                   m_f[uiRow][2] * rkMatrix.m_f[2][uiCol];
            }
        }
        return kProd;
	}

	C3DMatrix3 C3DMatrix3::operator* (const C3DQuaternion &qtn) const
	{
		C3DMatrix3 mat3;
		qtn.toRotationMatrix(mat3);
		return (*this) * (mat3);
	}

    C3DMatrix3 C3DMatrix3::operator- () const
	{
		C3DMatrix3 kDiff;
       for (UInt32 uiRow = 0; uiRow < 3; ++uiRow)
        {
            for (UInt32 uiCol = 0; uiCol < 3; ++uiCol)
            {
                kDiff.m_f[uiRow][uiCol] = -m_f[uiRow][uiCol];
            }
        }
        return kDiff;
	}

	C3DVector3 C3DMatrix3::operator* (const C3DVector3& rkVector) const
	{
		C3DVector3 kProd;
        for (UInt32 uiRow = 0; uiRow < 3; ++uiRow)
        {
            kProd[uiRow] =
                m_f[uiRow][0]*rkVector[0] +
                m_f[uiRow][1]*rkVector[1] +
                m_f[uiRow][2]*rkVector[2];
        }
        return kProd;
	}

    C3DMatrix3 C3DMatrix3::operator* (Float32 fScalar) const
	{
		C3DMatrix3 kProd;
        for (UInt32 uiRow = 0; uiRow < 3; ++uiRow)
        {
            for (UInt32 uiCol = 0; uiCol < 3; ++uiCol)
                kProd[uiRow][uiCol] = fScalar*m_f[uiRow][uiCol];
        }
        return kProd;
	}

    // utilities
    C3DMatrix3 C3DMatrix3::transpose () const
	{
		C3DMatrix3 kTranspose;
        for (UInt32 uiRow = 0; uiRow < 3; ++uiRow)
        {
            for (UInt32 uiCol = 0; uiCol < 3; ++uiCol)
                kTranspose[uiRow][uiCol] = m_f[uiCol][uiRow];
        }
        return kTranspose;
	}

    BOOLEAN C3DMatrix3::inverse (C3DMatrix3& rkInverse, Float32 fTolerance /*= 1e-06*/) const
	{
		rkInverse[0][0] = m_f[1][1]*m_f[2][2] -
            m_f[1][2]*m_f[2][1];
        rkInverse[0][1] = m_f[0][2]*m_f[2][1] -
            m_f[0][1]*m_f[2][2];
        rkInverse[0][2] = m_f[0][1]*m_f[1][2] -
            m_f[0][2]*m_f[1][1];
        rkInverse[1][0] = m_f[1][2]*m_f[2][0] -
            m_f[1][0]*m_f[2][2];
        rkInverse[1][1] = m_f[0][0]*m_f[2][2] -
            m_f[0][2]*m_f[2][0];
        rkInverse[1][2] = m_f[0][2]*m_f[1][0] -
            m_f[0][0]*m_f[1][2];
        rkInverse[2][0] = m_f[1][0]*m_f[2][1] -
            m_f[1][1]*m_f[2][0];
        rkInverse[2][1] = m_f[0][1]*m_f[2][0] -
            m_f[0][0]*m_f[2][1];
        rkInverse[2][2] = m_f[0][0]*m_f[1][1] -
            m_f[0][1]*m_f[1][0];

        Float32 fDet =
            m_f[0][0]*rkInverse[0][0] +
            m_f[0][1]*rkInverse[1][0]+
            m_f[0][2]*rkInverse[2][0];

        if ( Math::abs(fDet) <= fTolerance )
            return FALSE;

        Float32 fInvDet = 1.0f/fDet;
        for (UInt32 uiRow = 0; uiRow < 3; ++uiRow)
        {
            for (UInt32 uiCol = 0; uiCol < 3; ++uiCol)
                rkInverse[uiRow][uiCol] *= fInvDet;
        }

        return TRUE;
	}

    C3DMatrix3 C3DMatrix3::inverse (Float32 fTolerance) const
	{
		C3DMatrix3 kInverse = C3DMatrix3::ZERO;
        inverse(kInverse,fTolerance);
        return kInverse;
	}

    Float32 C3DMatrix3::determinant () const
	{
		Float32 fCofactor00 = m_f[1][1]*m_f[2][2] -
            m_f[1][2]*m_f[2][1];
        Float32 fCofactor10 = m_f[1][2]*m_f[2][0] -
            m_f[1][0]*m_f[2][2];
        Float32 fCofactor20 = m_f[1][0]*m_f[2][1] -
            m_f[1][1]*m_f[2][0];

        Float32 fDet =
            m_f[0][0]*fCofactor00 +
            m_f[0][1]*fCofactor10 +
            m_f[0][2]*fCofactor20;

        return fDet;
	}

	void C3DMatrix3::fromAxes(const C3DVector3& xAxis, const C3DVector3& yAxis, const C3DVector3& zAxis)
	{
		setColumn(0,xAxis);
        setColumn(1,yAxis);
        setColumn(2,zAxis);
	}

	void C3DMatrix3::fromAxisAngle (const C3DVector3& rkAxis, const Float32& fRadians)
	{
		Float32 fCos = Math::cos(fRadians);
        Float32 fSin = Math::sin(fRadians);
        Float32 fOneMinusCos = 1.0f-fCos;
        Float32 fX2 = rkAxis.m_fX*rkAxis.m_fX;
        Float32 fY2 = rkAxis.m_fY*rkAxis.m_fY;
        Float32 fZ2 = rkAxis.m_fZ*rkAxis.m_fZ;
        Float32 fXYM = rkAxis.m_fX*rkAxis.m_fY*fOneMinusCos;
        Float32 fXZM = rkAxis.m_fX*rkAxis.m_fZ*fOneMinusCos;
        Float32 fYZM = rkAxis.m_fY*rkAxis.m_fZ*fOneMinusCos;
        Float32 fXSin = rkAxis.m_fX*fSin;
        Float32 fYSin = rkAxis.m_fY*fSin;
        Float32 fZSin = rkAxis.m_fZ*fSin;

        m_f[0][0] = fX2*fOneMinusCos+fCos;
        m_f[0][1] = fXYM+fZSin;
        m_f[0][2] = fXZM-fYSin;

        m_f[1][0] = fXYM-fZSin;
        m_f[1][1] = fY2*fOneMinusCos+fCos;
        m_f[1][2] = fYZM+fXSin;

        m_f[2][0] = fXZM+fYSin;
        m_f[2][1] = fYZM-fXSin;
        m_f[2][2] = fZ2*fOneMinusCos+fCos;
	}

	void C3DMatrix3::toAxisAngle (C3DVector3& rkAxis, Float32& rfRadians) const
	{
		// Let (x,y,z) be the unit-length axis and let A be an angle of rotation.
        // The rotation matrix is R = I + sin(A)*P + (1-cos(A))*P^2 where
        // I is the identity and
        //
        //       +-        -+
        //   P = |  0 -z +y |
        //       | +z  0 -x |
        //       | -y +x  0 |
        //       +-        -+
        //
        // If A > 0, R represents a counterclockwise rotation about the axis in
        // the sense of looking from the tip of the axis vector towards the
        // origin.  Some algebra will show that
        //
        //   cos(A) = (trace(R)-1)/2  and  R - R^t = 2*sin(A)*P
        //
        // In the event that A = pi, R-R^t = 0 which prevents us from extracting
        // the axis through P.  Instead note that R = I+2*P^2 when A = pi, so
        // P^2 = (R-I)/2.  The diagonal entries of P^2 are x^2-1, y^2-1, and
        // z^2-1.  We can solve these for axis (x,y,z).  Because the angle is pi,
        // it does not matter which sign you choose on the square roots.

        Float32 fTrace = m_f[0][0] + m_f[1][1] + m_f[2][2];
        Float32 fCos = 0.5f*(fTrace-1.0f);
        rfRadians = Math::acos(fCos);  // in [0,PI]

        if ( rfRadians > 0.0f )
        {
            if ( rfRadians < Math::PI )
            {
                rkAxis.m_fX = m_f[2][1]-m_f[1][2];
                rkAxis.m_fY = m_f[0][2]-m_f[2][0];
                rkAxis.m_fZ =  m_f[1][0]- m_f[0][1];
                rkAxis.normalise();
            }
            else
            {
                // angle is PI
                float fHalfInverse;
                if (  m_f[0][0] >=  m_f[1][1] )
                {
                    // r00 >= r11
                    if (  m_f[0][0] >=  m_f[2][2] )
                    {
                        // r00 is maximum diagonal term
                        rkAxis.m_fX = 0.5f * Math::sqrt( m_f[0][0] -
                             m_f[1][1] -  m_f[2][2] + 1.0f);
                        fHalfInverse = 0.5f/rkAxis.m_fX;
                        rkAxis.m_fY = fHalfInverse *  m_f[0][1];
                        rkAxis.m_fZ = fHalfInverse *  m_f[0][2];
                    }
                    else
                    {
                        // r22 is maximum diagonal term
                        rkAxis.m_fZ = 0.5f * Math::sqrt( m_f[2][2] -
                             m_f[0][0] -  m_f[1][1] + 1.0f);
                        fHalfInverse = 0.5f/rkAxis.m_fZ;
                        rkAxis.m_fX = fHalfInverse *  m_f[0][2];
                        rkAxis.m_fY = fHalfInverse *  m_f[1][2];
                    }
                }
                else
                {
                    // r11 > r00
                    if (  m_f[1][1] >=  m_f[2][2] )
                    {
                        // r11 is maximum diagonal term
                        rkAxis.m_fY = 0.5f*Math::sqrt( m_f[1][1] -
                             m_f[0][0] -  m_f[2][2] + 1.0f);
                        fHalfInverse  = 0.5f/rkAxis.m_fY;
                        rkAxis.m_fX = fHalfInverse* m_f[0][1];
                        rkAxis.m_fZ = fHalfInverse* m_f[1][2];
                    }
                    else
                    {
                        // r22 is maximum diagonal term
                        rkAxis.m_fZ = 0.5f*Math::sqrt( m_f[2][2] -
                             m_f[0][0] -  m_f[1][1] + 1.0f);
                        fHalfInverse = 0.5f/rkAxis.m_fZ;
                        rkAxis.m_fX = fHalfInverse* m_f[0][2];
                        rkAxis.m_fY = fHalfInverse* m_f[1][2];
                    }
                }
            }
        }
        else
        {
            rkAxis.m_fX = 1.0f;
            rkAxis.m_fY = 0.0f;
            rkAxis.m_fZ = 0.0f;
        }
	}

    BOOLEAN C3DMatrix3::toEulerAnglesYXZ (Float32& rfYAngle, Float32& rfPAngle, Float32& rfRAngle) const
	{
		// rot =  cy*cz+sx*sy*sz  cz*sx*sy-cy*sz  cx*sy
        //        cx*sz           cx*cz          -sx
        //       -cz*sy+cy*sx*sz  cy*cz*sx+sy*sz  cx*cy

        rfPAngle = Math::asin(m_f[1][2]);
        if ( rfPAngle < Math::HALF_PI )
        {
            if ( rfPAngle > -Math::HALF_PI )
            {
                rfYAngle = Math::atan2( -m_f[0][2], m_f[2][2]);
                rfRAngle = Math::atan2( -m_f[1][0], m_f[1][1]);
                return TRUE;
            }
            else
            {
                Float32 fRmY = - Math::atan2(m_f[2][0], m_f[0][0]);
                //rfRAngle = 0.0F;  // any angle works
               // rfYAngle = rfRAngle - fRmY;
				rfRAngle = fRmY;
                rfYAngle = 0.0f;
                return FALSE;
            }
        }
        else
        {
            Float32 fRpY = Math::atan2(m_f[2][0], m_f[0][0]);
            rfRAngle = fRpY;
            rfYAngle = 0.0f;
            return FALSE;
        }
	}

    void C3DMatrix3::fromEulerAnglesYXZ (Float32 fYAngle, Float32 fPAngle, Float32 fRAngle)
	{
		Float32 fCos, fSin;

        fCos = Math::cos(fYAngle);
        fSin = Math::sin(fYAngle);
        C3DMatrix3 kYMat(fCos,0.0f,-fSin,0.0f,1.0f,0.0f,fSin,0.0f,fCos);

        fCos = Math::cos(fPAngle);
        fSin = Math::sin(fPAngle);
        C3DMatrix3 kXMat(1.0f,0.0f,0.0f,0.0f,fCos,fSin,0.0f,-fSin,fCos);

        fCos = Math::cos(fRAngle);
        fSin = Math::sin(fRAngle);
        C3DMatrix3 kZMat(fCos,fSin,0.0f,-fSin,fCos,0.0f,0.0f,0.0f,1.0f);

        *this = kYMat*(kXMat*kZMat);
	}

	BOOLEAN C3DMatrix3::hasScale() const
	{
		// check magnitude of column vectors (==local axes)
		Float32 t =  m_f[0][0] *  m_f[0][0] +  m_f[1][0] *  m_f[1][0] +  m_f[2][0] *  m_f[2][0];
		if (!Math::isEqual(t, 1.0, (Float32)1e-04))
			return TRUE;
		t =  m_f[0][1] *  m_f[0][1] +  m_f[1][1] * m_f[1][1] + m_f[2][1] * m_f[2][1];
		if (!Math::isEqual(t, 1.0, (Float32)1e-04))
			return TRUE;
		t = m_f[0][2] * m_f[0][2] + m_f[1][2] * m_f[1][2] + m_f[2][2] * m_f[2][2];
		if (!Math::isEqual(t, 1.0, (Float32)1e-04))
			return TRUE;

		return FALSE;
	}
