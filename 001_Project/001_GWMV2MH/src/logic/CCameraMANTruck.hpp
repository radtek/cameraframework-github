#ifndef _CADAS_CTRL_CAMAERASTATE_MANTRUCK_HPP_
#define _CADAS_CTRL_CAMAERASTATE_MANTRUCK_HPP_

#include "CCamera.hpp"

class CReverseCameraMT : public CCamera
{
public:
	CReverseCameraMT(EPos ePos);
	virtual ~CReverseCameraMT();

	virtual BOOLEAN 		canAutoActivated() ;
	virtual BOOLEAN 		canManualActivated() ;
	virtual BOOLEAN			canManualDeactivated() ;
	virtual void			deactivate();
    virtual BOOLEAN         isStandbyWakeUp()    const  { return ((m_eAutoActiveType == eType_CAN_REVERSE)&&isAutoActivated());}
    virtual BOOLEAN			isInReverse() ; //reverse gear will overide by hard key
    virtual BOOLEAN	        isNotInReverse();
    static void             SetSpeedRestrictValid() {m_bIsSpeedRestrictValid=TRUE;};
    static void             SetSpeedRestrictInvalid() {m_bIsSpeedRestrictValid=FALSE;};
    static void             vSetDirectlyCancelRearCam();
    static void             vCancelDirectlyCancelRearCam();
    static BOOLEAN          bDirectlyCancelledRearCam();
protected:
	BOOLEAN					isSpeedHigh();
    BOOLEAN					isEitherHardPinActived();
private:
    BOOLEAN                 m_bLsatIsReverseState;
    //add one new state to support customer new request
    static BOOLEAN          m_bIsSpeedRestrictValid;
    static BOOLEAN          m_bDirectlyCancelRearCam[CCamera::eCameraNum];
};

class CGeneralCameraMT : public CCamera
{
public:
	CGeneralCameraMT(EPos ePos);
	virtual ~CGeneralCameraMT();

	virtual BOOLEAN 		canAutoActivated();
	virtual BOOLEAN 		canManualActivated() ;
	virtual BOOLEAN			canManualDeactivated() ;
protected:
    BOOLEAN	                isSpeedHigh();
    BOOLEAN					isEitherHardPinActived();
};

#endif  

