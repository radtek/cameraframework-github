#ifndef _CCAMERA_DETECTION_HPP_
#define _CCAMERA_DETECTION_HPP_

#include "svs.h"
#include "CCamera.hpp"
#include "CAdasMsgQueDefine.hpp"
#include "CCameraSysManager.h"
//start detection thread after 10 sec service launched
//check camera connection trigger by this thread at background or by user request
//task1 : get init camera connection state
//task2 : update runtime camera connection state only after camera enabled for 3 sec
class CCameraDetection : public CRunnable
{
public: // method
	enum ECameraDete
	{
		eUnknown,
		eDisconnected,
		eConnected,
	};
    static CCameraDetection* getInstance();
    static void delInstance();
    virtual ~CCameraDetection();
    BOOLEAN bGetCameraConnection(CCamera::EPos ePos);
	void vCB_CamDetection(BOOLEAN bCamState, int CamPos);

protected:
	virtual BOOLEAN initialize();
	//virtual void 	unInitialize()	{}
	virtual void 	update();
protected:// data

private:// data
	CCameraDetection();
    BOOLEAN bTask1_InitCamState();
    BOOLEAN bTask2_RuntimeCamState();
    
    static CCameraDetection* m_pInstance;
    ECameraDete	             m_eCammeraConnected[CCamera::eCameraNum];
};

#endif  

