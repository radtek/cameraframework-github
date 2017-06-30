#include "C3DVector3.h"
#include "CMath.h"

    const	C3DVector3	C3DVector3::ZERO( 0.0f, 0.0f, 0.0f );
    const	C3DVector3	C3DVector3::UNIT_X( 1.0f, 0.0f, 0.0f );
    const	C3DVector3	C3DVector3::UNIT_Y( 0.0f, 1.0f, 0.0f );
    const	C3DVector3	C3DVector3::UNIT_Z( 0.0f, 0.0f, 1.0f );
    const	C3DVector3	C3DVector3::NEGATIVE_UNIT_X( -1.0f, 0.0f, 0.0f );
    const	C3DVector3	C3DVector3::NEGATIVE_UNIT_Y( 0.0f, -1.0f, 0.0f );
    const	C3DVector3	C3DVector3::NEGATIVE_UNIT_Z( 0.0f,  0.0f, -1.0f );
    const	C3DVector3	C3DVector3::UNIT_SCALE( 1.0f, 1.0f, 1.0f );

	C3DVector3::C3DVector3()
		: m_fX(0.0f)
		, m_fY(0.0f)
		, m_fZ(0.0f)
	{
		;
	}

	C3DVector3::C3DVector3(const C3DVector3 &src) 
		: m_fX(src.m_fX)
		, m_fY(src.m_fY)
		, m_fZ(src.m_fZ)
	{
		;
	}

	C3DVector3::C3DVector3(Float32 fX, Float32 fY, Float32 fZ)
		: m_fX(fX)
		, m_fY(fY)
		, m_fZ(fZ)
	{
		;
	}

	C3DVector3::~C3DVector3()
	{
		;
	}

	Float32 C3DVector3::length() const
	{
		return (Float32)Math::sqrt( m_fX * m_fX + m_fY * m_fY + m_fZ * m_fZ );
	}

	Float32 C3DVector3::squaredLength() const
	{
		return m_fX * m_fX + m_fY * m_fY + m_fZ * m_fZ;
	}

	BOOLEAN C3DVector3::isZeroLength() const
	{
		return Math::isZero(squaredLength());
	}

	Float32 C3DVector3::distance(const C3DVector3& vt) const
	{
		return (*this - vt).length();
	}

	Float32 C3DVector3::squaredDistance(const C3DVector3& vt) const
	{
		return (*this - vt).squaredLength();
	}

	Float32 C3DVector3::normalise()
	{
		Float32 fLength = length();

		if ( fLength > 0.0f )
		{
			Float32 fInvLength = 1.0f / fLength;
			m_fX *= fInvLength;
			m_fY *= fInvLength;
			m_fZ *= fInvLength;
		}

		return fLength;
	}

	C3DVector3 C3DVector3::normalisedCopy() const
	{
		C3DVector3 vt = *this;
		vt.normalise();
		return vt;
	}

	Float32 C3DVector3::dotProduct(const C3DVector3& vt) const
	{
		 return m_fX * vt.m_fX + m_fY * vt.m_fY + m_fZ * vt.m_fZ;
	}

	Float32 C3DVector3::absDotProduct(const C3DVector3 &vt) const
	{
		 return Math::abs(m_fX * vt.m_fX) + Math::abs(m_fY * vt.m_fY) + Math::abs(m_fZ * vt.m_fZ);
	}

	C3DVector3 C3DVector3::crossProduct(const C3DVector3& vt) const
	{
		return C3DVector3(	m_fY * vt.m_fZ - m_fZ * vt.m_fY,
							m_fZ * vt.m_fX - m_fX * vt.m_fZ,
							m_fX * vt.m_fY - m_fY * vt.m_fX   );
	}

	C3DVector3 C3DVector3::midPoint(const C3DVector3 &vt) const
	{
		return C3DVector3(	( m_fX + vt.m_fX ) * 0.5f,
							( m_fY + vt.m_fY ) * 0.5f,
							( m_fZ + vt.m_fZ ) * 0.5f );
	}

	void C3DVector3::makeFloor(const C3DVector3 &vt)
	{
		if ( vt.m_fX < m_fX )
		{
			m_fX = vt.m_fX;
		}

		if ( vt.m_fY < m_fY )
		{
			m_fY = vt.m_fY;
		}

		if ( vt.m_fZ < m_fZ )
		{
			m_fZ = vt.m_fZ;
		}
	}

	void C3DVector3::makeCeil(const C3DVector3 &vt)
	{
		if ( vt.m_fX > m_fX )
		{
			m_fX = vt.m_fX;
		}

		if ( vt.m_fY > m_fY )
		{
			m_fY = vt.m_fY;
		}

		if ( vt.m_fZ > m_fZ )
		{
			m_fZ = vt.m_fZ;
		}
	}

	C3DVector3 C3DVector3::perpendicular() const
	{
		C3DVector3 vPerp = this->crossProduct( C3DVector3::UNIT_X );

		// Check length
		if ( Math::isZero(vPerp.squaredLength()))
		{
			// This vector is the Y axis multiplied by a scalar, so we have to use another axis.
			vPerp = this->crossProduct( C3DVector3::UNIT_Y );
		}

		vPerp.normalise();

		return vPerp;
	}

	C3DVector3 C3DVector3::reflect(const C3DVector3& vtNormal) const
	{
		return C3DVector3( *this - ( vtNormal * (this->dotProduct(vtNormal) * 2) ) );
	}

	C3DVector3 C3DVector3::primaryAxis() const
	{
		Float32 fAbsX = Math::abs(m_fX);
		Float32 fAbsY = Math::abs(m_fY);
		Float32 fAbsZ = Math::abs(m_fZ);

		if (fAbsX > fAbsY)
		{
			if (fAbsX > fAbsZ)
			{
				return m_fX > 0 ? C3DVector3::UNIT_X : C3DVector3::NEGATIVE_UNIT_X;
			}
			else
			{
				return m_fZ > 0 ? C3DVector3::UNIT_Z : C3DVector3::NEGATIVE_UNIT_Z;
			}
		}
		else
		{
			if (fAbsY > fAbsZ)
			{
				return m_fY > 0 ? C3DVector3::UNIT_Y : C3DVector3::NEGATIVE_UNIT_Y;
			}
			else
			{
				return m_fZ > 0 ? C3DVector3::UNIT_Z : C3DVector3::NEGATIVE_UNIT_Z;
			}
		}
	}

	Float32 C3DVector3::angleBetween(const C3DVector3 &vtDest) const
	{
		Float32 lenProduct = length() * vtDest.length();

		// Divide by zero check
		if(lenProduct < 1e-6f)
			lenProduct = 1e-6f;

		Float32 f = dotProduct(vtDest) / lenProduct;

		f = Math::clamp(f, -1.0f, 1.0f);
		return Math::acos(f);
	}

	C3DQuaternion C3DVector3::getRotationTo(const C3DVector3 &vtDest, const C3DVector3& vtFallbackAxis) const
	{
		// Based on Stan Melax's article in Game Programming Gems
        C3DQuaternion q;
        // Copy, since cannot modify local
        C3DVector3 v0 = *this;
        C3DVector3 v1 = vtDest;
        v0.normalise();
        v1.normalise();

        Float32 d = v0.dotProduct(v1);
        // If dot == 1, vectors are the same
        if (d >= 1.0f)
        {
            return C3DQuaternion::IDENTITY;
        }
		if (d < (1e-6f - 1.0f))
		{
			if (vtFallbackAxis != C3DVector3::ZERO)
			{
				// rotate 180 degrees about the fallback axis
				q.fromAxisAngle(vtFallbackAxis,Math::PI);
			}
			else
			{
				// Generate an axis
				C3DVector3 axis = C3DVector3::UNIT_X.crossProduct(*this);
				if (axis.isZeroLength()) // pick another if colinear
					axis = C3DVector3::UNIT_Y.crossProduct(*this);
				axis.normalise();
				q.fromAxisAngle(axis, Math::PI);
			}
		}
		else
		{
            Float32 s = Math::sqrt( (1+d)*2 );
            Float32 invs = 1 / s;

			C3DVector3 c = v0.crossProduct(v1);

	        q.m_fX = c.m_fX * invs;
    	    q.m_fY = c.m_fY * invs;
        	q.m_fZ = c.m_fZ * invs;
        	q.m_fW = s * 0.5f;
			q.normalise();
		}
        return q;
	}

	BOOLEAN C3DVector3::positionEquals(const C3DVector3 &vt, Float32 fTolerance) const
	{
		return Math::isEqual(m_fX, vt.m_fX, fTolerance) &&
				Math::isEqual(m_fY, vt.m_fY, fTolerance) &&
				Math::isEqual(m_fZ, vt.m_fZ, fTolerance);

	}

	BOOLEAN C3DVector3::positionCloses(const C3DVector3 &vt, Float32 fTolerance) const
	{
		return squaredDistance(vt) <=
                (squaredLength() + vt.squaredLength()) * fTolerance;
		
	}

	BOOLEAN C3DVector3::directionEquals(const C3DVector3 &vt, Float32 fTolerance) const
	{
		Float32 fDot = dotProduct(vt);
		Float32 fAngle = Math::acos(fDot);

		return Math::abs(fAngle) <= fTolerance;

	}

	BOOLEAN C3DVector3::isNaN() const
	{
		return Math::isNaN(m_fX) || Math::isNaN(m_fY) || Math::isNaN(m_fZ);
	}

	C3DVector3& C3DVector3::operator =(const C3DVector3 &src)
	{
		m_fX = src.m_fX;
		m_fY = src.m_fY;
		m_fZ = src.m_fZ;

		return *this;
	}

	BOOLEAN C3DVector3::operator ==(const C3DVector3 &rhs) const
	{
		return	   Math::isZero(m_fX - rhs.m_fX) 
				&& Math::isZero(m_fY - rhs.m_fY) 
				&& Math::isZero(m_fZ - rhs.m_fZ);
	}

	BOOLEAN C3DVector3::operator !=(const C3DVector3 &rhs) const
	{
		return	!operator==(rhs);
	}

	BOOLEAN C3DVector3::operator < ( const C3DVector3& rhs ) const
    {
        if( m_fX < rhs.m_fX && m_fY < rhs.m_fY && m_fZ < rhs.m_fZ )
		{
            return TRUE;
		}

        return FALSE;
    }
       
    BOOLEAN C3DVector3::operator > ( const C3DVector3& rhs ) const
    {
        if( m_fX > rhs.m_fX && m_fY > rhs.m_fY && m_fZ > rhs.m_fZ )
		{
            return TRUE;
		}

        return FALSE;
    }

	C3DVector3 C3DVector3::operator +(const C3DVector3 &src) const
	{
		return C3DVector3(m_fX + src.m_fX, m_fY + src.m_fY, m_fZ + src.m_fZ);
	}

	C3DVector3 C3DVector3::operator -(const C3DVector3 &src) const
	{
		return C3DVector3(m_fX - src.m_fX, m_fY - src.m_fY, m_fZ - src.m_fZ);
	}

	C3DVector3 C3DVector3::operator *(const C3DVector3 &src) const
	{
		return C3DVector3(m_fX * src.m_fX, m_fY * src.m_fY, m_fZ * src.m_fZ);
	}

	C3DVector3 C3DVector3::operator *(Float32 fScalar) const
	{
		return C3DVector3(m_fX * fScalar, m_fY * fScalar, m_fZ * fScalar);
	}

	C3DVector3 C3DVector3::operator /(Float32 fScalar) const
	{
		Float32 fTemp = 1.0f / fScalar;
		return C3DVector3(m_fX * fTemp, m_fY * fTemp, m_fZ * fTemp);
	}

	C3DVector3 C3DVector3::operator +() const
	{
		return C3DVector3(m_fX, m_fY, m_fZ);
	}

	C3DVector3 C3DVector3::operator -() const
	{
		return C3DVector3(-m_fX, -m_fY, -m_fZ);
	}

	C3DVector3& C3DVector3::operator +=(const C3DVector3 &src)
	{
		m_fX += src.m_fX;
		m_fY += src.m_fY;
		m_fZ += src.m_fZ;

		return *this;
	}

	C3DVector3& C3DVector3::operator -=(const C3DVector3 &src)
	{
		m_fX -= src.m_fX;
		m_fY -= src.m_fY;
		m_fZ -= src.m_fZ;

		return *this;
	}
	
	C3DVector3 C3DVector3::operator *=(const C3DVector3 &src)
	{
		m_fX *= src.m_fX;
        m_fY *= src.m_fY;
        m_fZ *= src.m_fZ;

        return *this;
	}

	C3DVector3& C3DVector3::operator *=(Float32 fScalar)
	{
		m_fX *= fScalar;
		m_fY *= fScalar;
		m_fZ *= fScalar;

		return *this;
	}

	C3DVector3& C3DVector3::operator /=(Float32 fScalar)
	{
		Float32 fTemp = 1.0f / fScalar;

		m_fX *= fTemp;
		m_fY *= fTemp;
		m_fZ *= fTemp;

		return *this;
	}
