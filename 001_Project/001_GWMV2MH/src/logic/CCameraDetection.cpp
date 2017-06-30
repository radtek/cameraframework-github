
#include "CCameraDetection.hpp"
#include "CAdasCtrl.hpp"

#define ONE_SECOND_DELAY (1000000)
CCameraDetection * CCameraDetection::m_pInstance = NULL;

CCameraDetection* CCameraDetection::getInstance()
{
   if(m_pInstance == NULL)
   {
      m_pInstance = new CCameraDetection();
   }
   return m_pInstance;
}

void CCameraDetection::delInstance()
{
   if(m_pInstance != NULL)
   {
      delete m_pInstance;
      m_pInstance = NULL;
   }
}

CCameraDetection::~CCameraDetection()
{
   ;
}

CCameraDetection::CCameraDetection()
:CRunnable("Thread_CCameraDetection",NULL)
{
    for(int i = 0;i<(int)CCamera::eCameraNum;i++)
    {
        m_eCammeraConnected[i]=eUnknown;
    }
}
TRC_SCOPE_DEF(ADAS, CCameraDetection, vCB_CamDetection);
void CCameraDetection::vCB_CamDetection(BOOLEAN bSigState, int CamPos)
{
	TRC_SCOPE(ADAS, CCameraDetection, vCB_CamDetection);
	m_eCammeraConnected[CamPos] = bSigState?eConnected:eDisconnected;
    //if unknow && no user request now then start task1 
   	CCameraCtrl* pCameraCtrl = CAdasCtrl::getInstance()->getCameraCtrl();
	if( pCameraCtrl == NULL )
	{
	  //DBG_MSG(("error: CCameraCtrl==NULL \n "));
	  return ;
	} 
	//not receive cam sig but already active by user, just exit, let usr to close it
	if(!pCameraCtrl->isAllCamerasOff())
	{
	  return ;
	} 
	//if camera not reuqest by usr but actived, than we shall close it
	//this callback is queued in main loop , it sync with adas state update, it will not run in the middle of adas state transfer
	if(CCameraSysManager::getInstance()->isActive())
	{
		DBG_MSG(("-------------------vCB_CamDetection------------Disable capture on %d-----------------\n",CamPos));
		CCameraSysManager::getInstance()->setCameraState(FALSE);
		CCameraSysManager::getInstance()->pause();
	} 	 
}

Int32 s_CamIdx[2] = {0,1};
static int iLastChkChan = -1;
TRC_SCOPE_DEF(ADAS, CCameraDetection, bTask1_InitCamState);
BOOLEAN CCameraDetection::bTask1_InitCamState()
{
	if(-2==iLastChkChan) return TRUE;
	TRC_SCOPE(ADAS, CCameraDetection, bTask1_InitCamState);
	int iCheckCam = -1;
    for(int i = 0;i<(int)CCamera::eCameraNum;i++)
    {
        if(eUnknown == m_eCammeraConnected[i])
        {
        	iCheckCam = i;
			break;
        }
    }
	DBG_MSG(("CCameraDetection is going to check channel %d [%d-%d]-----------------\n",iCheckCam,m_eCammeraConnected[0],m_eCammeraConnected[1]));
	if(-1==iCheckCam)
	{
		//task one done, return true
		DBG_MSG(("CCameraDetection bTask1_InitCamState done:  [%d-%d]-----------------\n",m_eCammeraConnected[0],m_eCammeraConnected[1]));
		char str[] = "CCameraDetection-update-sig-after10seconds";
		CAdasCtrl::getInstance()->onGetCameraStateDiag((void *)str);
		iLastChkChan = -2;
		return TRUE;
	}
	else
	{
	    //if unknow && no user request now then start task1 
   		CCameraCtrl* pCameraCtrl = CAdasCtrl::getInstance()->getCameraCtrl();
		if( pCameraCtrl == NULL )
		{
			//DBG_MSG(("error: CCameraCtrl==NULL \n "));
			return FALSE;
		} 
		//not receive cam sig but already active by user, just exit
		if(!pCameraCtrl->isAllCamerasOff())
		{
			DBG_MSG(("CCameraDetection stop open channel %d for user reqeust already one-----------------\n",iCheckCam));
			return FALSE;
		} 
		//if camera not reuqest by usr but actived, than we shall wait the callback of cam sig and close it
		//int the callback, check the usr  request and close the camsysmanager if necessary
		if(CCameraSysManager::getInstance()->isActive())
		{
			DBG_MSG(("CCameraDetection stop open channel %d for last checking is not finished-----------------\n",iCheckCam));
			if(iLastChkChan == iCheckCam)
			{
				//signal call back is not received, for it can be received only on enable a channle or a signal change event
				//next check loop will enable it again to check it
				DBG_MSG(("CCameraDetection is going to re-check channel %d, close it now -----------------\n",iCheckCam));
				CCameraSysManager::getInstance()->setCameraState(FALSE);
				CCameraSysManager::getInstance()->pause();
			}		
			return FALSE;
		} 
	    //enable camera state at background
		CCameraSysManager::getInstance()->resume();
		CCameraSysManager::getInstance()->setCameraSourceIndex(s_CamIdx[iCheckCam]);
		iLastChkChan = iCheckCam;
		DBG_MSG(("CCameraDetection have send request to open channel %d-----------------\n",s_CamIdx[iCheckCam]));
	}
    return FALSE;
}
BOOLEAN CCameraDetection::bTask2_RuntimeCamState()
{
	return FALSE;
}
BOOLEAN CCameraDetection::bGetCameraConnection(CCamera::EPos ePos)
{
    return (eConnected == m_eCammeraConnected[int(ePos)]);
}
//delay self for 10 seconds to avoid racing with early camera request
TRC_SCOPE_DEF(ADAS, CCameraDetection, initialize);
BOOLEAN CCameraDetection::initialize()
{
	TRC_SCOPE(ADAS, CCameraDetection, initialize);
    usleep(10*ONE_SECOND_DELAY);
	for(int i = 0;i<(int)CCamera::eCameraNum;i++)
    {
        m_eCammeraConnected[i]=eUnknown;
    }
	DBG_MSG(("CCameraDetection initialize  done ----------------\n"));
    return TRUE;
}

//static int iDetectCnt=0;
void CCameraDetection::update()
{
    //check if no user request then enable camera at background
    //if both camera state checked once then go to task2
	if(bTask1_InitCamState())
    {
        bTask2_RuntimeCamState();
    }
	usleep(4*ONE_SECOND_DELAY);
}


