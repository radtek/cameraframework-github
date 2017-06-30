#include "CSimpleCaptureThread.h"
#include "SimpleMessageDefine.h"


CSimpleCaptureThread::CSimpleCaptureThread(const string& strName)
: CCaptureThread(strName)
, m_pWin(NULL)
, m_uiCheckSignalFrame(0)
, m_iReqChannelIndex(-1)
, m_iLastActiveCamera(-1)
, m_bReqDriverState(eNoPending)
, m_bAckChannelIndex(TRUE)
, m_bAckDriverState(TRUE)
, m_bAckRCPos(TRUE)
, m_eLastSync(CCaptureDriver::eSignalState_Valid)//dtc report issure for active response cnount
, m_needReportLayerReady(FALSE)
, m_bReadyToRender(FALSE)
, m_debugSkipFrame(0)
{
    m_sRCPos.iX=0;
    m_sRCPos.iY=0;
    m_sRCPos.uiWidth=0;
    m_sRCPos.uiHeight=0;
    m_sRCPos.bPending = FALSE;
    m_sRCPos.bDefault = TRUE;
    
}

CSimpleCaptureThread::~CSimpleCaptureThread()
{
	;
}
void CSimpleCaptureThread::setCameraSourceIndex(int index)
{
    if(m_bAckChannelIndex)
    {
    	tagCameraSource tagsrc;
    	tagsrc._iCameraSrcIndex = index;
    	tagsrc._pCaptureDriver = m_pCaptureDriver;
        tagsrc._pSimpleCaptureThread= this;
    	pushMessage(tagsrc, sizeof(tagCameraSource));
        m_iReqChannelIndex = -1;
    }
    else
    {
        //in the middle of handle of cap que it is possible to interrupt by this push request
        //so claer this ack state only afterhandleMessage of the thread is finished
    	m_iReqChannelIndex = index;//keep last intented request channel 
    }
    m_bAckChannelIndex = FALSE;
}
TRC_SCOPE_DEF(ADAS, CSimpleCaptureThread, setScreenPosAndSize);
void CSimpleCaptureThread::setScreenPosAndSize(Int32 x, Int32 y, UInt32 uiW, UInt32 uiH)
{
    TRC_SCOPE(ADAS, CSimpleCaptureThread, setScreenPosAndSize);
    if((m_sRCPos.iX == x)&&(m_sRCPos.iY==y)&&(m_sRCPos.uiWidth==uiW)&&(m_sRCPos.uiHeight==uiH)&&(!m_sRCPos.bDefault))
    {
        DBG_MSG(("setScreenPosAndSize not change ,so return /n"));
        m_sRCPos.bPending =  FALSE;
        return;
    }
        
    if(m_bAckRCPos)
    {
    	tagCapturePosAndSize tagRC;
    	tagRC._rc.set(x,y,uiW,uiH);
    	tagRC._pSimpleCaptureThread = this;

    	pushMessage(tagRC, sizeof(tagRC));
        m_sRCPos.bPending =  FALSE;
    }
    else
    {
        m_sRCPos.bPending =  TRUE;
    }
	m_sRCPos.iX =  x;
    m_sRCPos.iY =  y;
    m_sRCPos.uiWidth =  uiW;
    m_sRCPos.uiHeight = uiH;
    m_sRCPos.bDefault = FALSE;
    m_bAckRCPos=  FALSE;
}

void CSimpleCaptureThread::setCameraState(BOOLEAN bEnable)
{
    if(m_bAckDriverState)
    {
    	tagCameraState tagEnable;
    	tagEnable._bCameraState = bEnable;
    	tagEnable._pCaptureDriver = m_pCaptureDriver;
        tagEnable._pSimpleCaptureThread= this;
    	pushMessage(tagEnable, sizeof(tagCameraState));
        m_bReqDriverState = eNoPending;
    }
    else
    {
        //in the middle of handle of cap que it is possible to interrupt by this push request
        //so claer this ack state only afterhandleMessage of the thread is finished
    	m_bReqDriverState = bEnable?eEnableDriver:eDisableDriver;//keep last intented request channel 
    }
    m_bAckDriverState = FALSE;
}
TRC_SCOPE_DEF(ADAS, CSimpleCaptureThread, initialize);
BOOLEAN CSimpleCaptureThread::initialize()
{
	TRC_SCOPE(ADAS, CSimpleCaptureThread, initialize);
	DBG_MSG(("CSimpleCaptureThread::initialize begin!\n"));
	
	UInt32 iDisplayID = CCommandLineParser::getInstance()->getItemUInt("-iDisplayID");
    UInt32 uiCapturePipeline = CCommandLineParser::getInstance()->getItemUInt("-uiCapturePipeline");
    UInt32 uiCaptureUsage = CCommandLineParser::getInstance()->getItemUInt("-uiCaptureUsage");
	DBG_MSG(("CSimpleCaptureThread::initialize iDisplayID=%d\n",iDisplayID));

	if( !CCaptureThread::initialize() )
		return FALSE;

	DBG_MSG(("CSimpleCaptureThread::initialize begin 1 !\n"));
	m_pWin = new CScreenWindow( CCameraSysManager::getInstance()->getScreenCtx(),
									CCameraSysManager::getInstance()->getScreenDisplay(iDisplayID));
	if( m_pWin == NULL )
	{
		DBG_ERROR(("window malloc failed!\n"));
		return FALSE;
	}

   if(1==iDisplayID)
   {
		m_config.iPipeline = 4;
		DBG_MSG(("CSimpleCaptureThread::initialize ---change m_config.iPipeline=%d\n",m_config.iPipeline));
	}
    if(0!=uiCapturePipeline)
    {
		m_config.iPipeline = uiCapturePipeline;
    }
    else
    {
        ;
    }
    if(0!=uiCaptureUsage)
    {
        ;
    }   
    else
    {
        uiCaptureUsage = SCREEN_USAGE_WRITE|SCREEN_USAGE_NATIVE;
    }
    //fprintf(stderr,"CSimpleCaptureThread::initialize ---set m_config.iPipeline=%d uiCaptureUsage=%d\n",m_config.iPipeline,uiCaptureUsage);

	CRectangle rc(m_config.iWinPos[0], m_config.iWinPos[1], m_config.uiWinSize[0], m_config.uiWinSize[1]);
	if(! m_pWin->create(m_config.strWinName, m_config.iPipeline, rc, m_config.uiFormat , uiCaptureUsage) )
	{
		DBG_ERROR(("Init window failed!\n"));
		return FALSE;
	}

	m_pWin->createBuffer(m_config.uiBufSize[0], m_config.uiBufSize[1], m_config.uiBufNum, TRUE);

    //m_pWin->postDummyWin();
	m_pWin->drawDummyImage();
	//fprintf(stderr,"$$$$$$$$$$$-post BLACK DATA cam $$$$$$$$$$$$$$$$$$$ /n");

	m_pCaptureBufArray = m_pWin->getScreenBufferArray();

	if(!initialize_capture(m_pCaptureDriverCfg, m_config.eDriverType))
	{
		DBG_ERROR(("Init capture failed!\n"));
		return FALSE;
	}

	DBG_MSG(("CSimpleCaptureThread::initialize end!\n"));
	return TRUE;
}

void CSimpleCaptureThread::unInitialize()
{
	if( m_pWin )
	{
		delete m_pWin;
		m_pWin = NULL;
	}

	CCaptureThread::unInitialize();
}

void CSimpleCaptureThread::beforeHandleMessageQueue()
{
    //todo why capture enable is ture defaultly?
/*   	if( !m_bCaptureEnable )
	{
		DBG_MSG(("Enable capture - ver1\n"));
		m_pCaptureDriver->bCapEnable();
		m_bCaptureEnable = TRUE;
   	}*/
 
}
//HMI text lable and camera signal state dependens on this delay, but layer is show in advance
//#define SIKP_FRAMES_FOR_SIG_DETECTION_NOT_VALID  60

//static Int32 s_Chanidx[2] = {0,1}; -- map logic index to decorder register value
Int32 s_LogicChanidx[2] = {0,1}; 

TRC_SCOPE_DEF(ADAS, CSimpleCaptureThread, afterHandleMessageQueue);
void CSimpleCaptureThread::afterHandleMessageQueue()
{
	int bufIndex = BUFFER_INDEX_VALUE_INVALID;
	int interlaceField = INTERLACE_FIELD_VALUE_INVALID;
    BOOLEAN bNeedToCheck = FALSE;
    static BOOLEAN bNoNeedToEmitState = FALSE;
    BOOLEAN bFirstSignalDetectionReady = FALSE;
    static int iRestartSigChk= m_config.uiSkipFramesForSigDelay;
    BOOLEAN bIfCapEnabled = m_pCaptureDriver->bIfCapEnabled();
    int currentActivedCamera = m_pCaptureDriver->getSourceIndex();
    //static BOOLEAN bFirstCheckAfterEnable[2] = {TRUE,TRUE};
    static unsigned int uilastSigLostChkCnt= 0;
    static unsigned int uilastSigLostChkCntStart= 0;
    
    m_bAckChannelIndex= TRUE;
    m_bAckDriverState= TRUE;
    m_bAckRCPos= TRUE;
    if(bNoCurPendingRequest()&&m_needReportLayerReady)
    {
        m_needReportLayerReady = FALSE;
        bNeedToCheck = TRUE; 
        bNoNeedToEmitState= TRUE; 
        m_uiCheckSignalFrame =0;
        iRestartSigChk = m_config.uiSkipFramesForSigDelay;
        TRC_SCOPE(ADAS, CSimpleCaptureThread, afterHandleMessageQueue);
        DBG_MSG(("Last sig lost on startup is = %d , in detection is %d, pos is %d, sig check delay is %d \n",uilastSigLostChkCntStart,uilastSigLostChkCnt,m_iLastActiveCamera,iRestartSigChk));
        uilastSigLostChkCnt = 0;
        uilastSigLostChkCntStart = 0;
        //assume good signal on a new channel for fast transfer camera state but camera signal detection is slow
        m_eLastSync = CCaptureDriver::eSignalState_Valid;
    }
#if 0        
    //todo use case for one channel
    if((0==currentActivedCamera)&&bFirstCheckAfterEnable[0]&&bIfCapEnabled)
    {
         bNeedToCheck = TRUE;   
         bFirstCheckAfterEnable[0] = FALSE;
         bFirstCheckAfterEnable[1] = TRUE;
         
    }
    else if((1==currentActivedCamera)&&bFirstCheckAfterEnable[1]&&bIfCapEnabled)
    {
         bNeedToCheck = TRUE;   
         bFirstCheckAfterEnable[0] = TRUE;    
         bFirstCheckAfterEnable[1] = FALSE;
    }
    else if(!bIfCapEnabled)
    {
         bFirstCheckAfterEnable[0] = TRUE;
         bFirstCheckAfterEnable[1] = TRUE;
         TRC_SCOPE(ADAS, CSimpleCaptureThread, afterHandleMessageQueue);
         DBG_MSG(("reset checked on new channel pos-%d \n",currentActivedCamera));
         m_uiCheckSignalFrame =0;
    }
    
    if(bNeedToCheck)
    {
       TRC_SCOPE(ADAS, CSimpleCaptureThread, afterHandleMessageQueue);
       DBG_MSG(("setup checked on new channel pos-%d \n",currentActivedCamera));
    }
#endif      
    if(bIfCapEnabled)
    {
        m_pCaptureDriver->bCapUpdate(bufIndex,interlaceField);
    }
	else
	{
		//reset to disble state
		m_iLastActiveCamera = -1;
	}
    //show camera without block on capture -- skip frames to avoid flicker 
	render(bufIndex, interlaceField,bNeedToCheck);

    if(m_pCaptureDriver->bIfCapActiveReady())
    {
        if(( m_uiCheckSignalFrame >= m_config.uiCheckSignal && m_config.pSignalCallback )/*|| bNeedToCheck*/)
    	{
    		m_pCaptureDriver->checkVSYNC(FALSE);
    		CCaptureDriver::ESignalState eSync = m_pCaptureDriver->getVSYNC();
            //if(bNeedToCheck) 
            //{
            //	TRC_SCOPE(ADAS, CSimpleCaptureThread, afterHandleMessageQueue);
            //    DBG_MSG(("first signal checked on new channel pos-%d is %d \n",currentActivedCamera,eSync));
            //}		
            //special check for first and second dectection
            //keep driver working what camera is enabled, so delay is removed but signal is wrong if not enough delay before first checking
            //make first camera signal updated only after several frames    
            if((( eSync != m_eLastSync )||(currentActivedCamera != m_iLastActiveCamera))/*&&( !bNeedToCheck)*/)
    		{
    			if( eSync == CCaptureDriver::eSignalState_Invalid )
    			{
                     uilastSigLostChkCnt++;
                    if(bNoNeedToEmitState)
                    {
                        if(0==s_LogicChanidx[currentActivedCamera]) 
							m_config.pSignalCallback(eSignal1InitInvalid);
						else
							m_config.pSignalCallback(eSignal2InitInvalid);
                    }
                    else
                    {
	                    if(0==s_LogicChanidx[currentActivedCamera]) 
							m_config.pSignalCallback(eSignal1Invalid);
						else
							m_config.pSignalCallback(eSignal2Invalid);
                    } 			
                }
    			else
    			{
      
                    if(bNoNeedToEmitState)
                    {
	                    if(0==s_LogicChanidx[currentActivedCamera]) 
	                        m_config.pSignalCallback(eSignal1InitValid);
						else
							m_config.pSignalCallback(eSignal2InitValid);
                    }
                    else
                    {
						if(0==s_LogicChanidx[currentActivedCamera]) 
							m_config.pSignalCallback(eSignal1Valid);
						else
							m_config.pSignalCallback(eSignal2Valid);
                    }
                    
    			}
                			
                m_eLastSync = eSync;
    			m_iLastActiveCamera = currentActivedCamera;
    		}
    		m_uiCheckSignalFrame = 0;
            if(bNoNeedToEmitState)
            {
                TRC_SCOPE(ADAS, CSimpleCaptureThread, afterHandleMessageQueue);
                DBG_MSG(("first delayed signal checked on new channel pos-%d is %d \n",currentActivedCamera, eSync));
                bFirstSignalDetectionReady = TRUE;
                bNoNeedToEmitState = FALSE;
            }
    	}
        if(0<=iRestartSigChk)
        {
            iRestartSigChk--;
            m_pCaptureDriver->checkVSYNC(TRUE);
            CCaptureDriver::ESignalState eSynctmp = m_pCaptureDriver->getVSYNC();

            if( eSynctmp == CCaptureDriver::eSignalState_Invalid )
            {
                 uilastSigLostChkCntStart++;
            }			
        }
        else
        {
            ++m_uiCheckSignalFrame;
        }
    }
    
    //camera view changed fast but camera state decteciton is not valid after long dealy
    if(bFirstSignalDetectionReady)
    {
        m_config.pLayerReadyCallback();
    }
}

void CSimpleCaptureThread::_setScreenPosAndSize(void *pData)
{
	tagCapturePosAndSize* pPosSize = (tagCapturePosAndSize*)pData;
	if(m_pWin)
	{
		//DBG_MSG(("CVideoCaptureThread::_setScreenPosAndSize %d %d %d %d\n",pPosSize->_rc,pPosSize[1],pPosSize[2],pPosSize[3]));
		m_pWin->setPos(pPosSize->_rc.getX(), pPosSize->_rc.getY());
		m_pWin->setSize(pPosSize->_rc.getWidth(), pPosSize->_rc.getHeight());
	}
}
struct timespec TimeStampFirstDraw;
TRC_SCOPE_DEF(ADAS, CSimpleCaptureThread, render);
void CSimpleCaptureThread::render(Int32 bufferIdx, Int32 interlace, BOOLEAN bReActived)
{
	static BOOLEAN bFirstTiming = TRUE;

    static Int32   iSkipFrames = -1;
    static Int32   iSetLayerTiming = 0;
    static Int32   iAppThreadSyncMAXFrames = 10;
	if(BUFFER_INDEX_VALUE_INVALID!=bufferIdx)
	{
		//DBG_MSG(("render bufferIdx=%d\n", bufferIdx));
		m_iCurCapBufIndex = bufferIdx;
		m_pWin->setCurPostBufIndex(bufferIdx);
	}

	if(INTERLACE_FIELD_VALUE_INVALID != interlace)
	{
		m_iCurCapField = interlace;
		m_pWin->setCurInterlaceField(interlace);
	}
    if(bReActived)
    {
    	TRC_SCOPE(ADAS, CSimpleCaptureThread, render);
        //if skip frame is 0 then wrong camera state will send out for no dealy on callback trigger emit 
        iSkipFrames = (0==m_debugSkipFrame)?m_config.uiSkipFrames:m_debugSkipFrame;
        if(bFirstTiming)
        {
            iSkipFrames = 6;
            iSetLayerTiming = 2;
        }
        m_bReadyToRender = TRUE;
        iAppThreadSyncMAXFrames = 10;
        DBG_MSG(("----->skipped frames cnt is  %d\n", iSkipFrames));
        //fprintf(stderr,"############## iSkipFrames = %d #############\n",iSkipFrames);
    }

    //there is dealy between main and cap thread, m_bReadyToRender is mean to sync this delay
    //it could show balck view on old channel
    if((!m_bReadyToRender)&&(iAppThreadSyncMAXFrames>0))
    {
        iAppThreadSyncMAXFrames --;
        TRC_SCOPE(ADAS, CSimpleCaptureThread, render);
        m_pWin->drawDummyImage();
        //DBG_MSG(("##############flush with drawDummyImage for m_bReadyToRender##############\n"));
        //fprintf(stderr,"############## iAppThreadSyncMAXFrames #############\n");
    }
    else if(iSkipFrames>=1)
    {
    	TRC_SCOPE(ADAS, CSimpleCaptureThread, render);
        m_pWin->drawDummyImage();
        iSkipFrames --;
        //DBG_MSG(("##############skipped frames cnt is  %d##############\n", iSkipFrames));
        //fprintf(stderr,"##############skipped frames cnt is  %d##############\n", iSkipFrames);
        if((iSkipFrames==iSetLayerTiming)&&bFirstTiming)
        {
           //fprintf(stderr,"############## remove set layer in cap thread for QNX long delay issue ##############\n");
           //m_config.pSetLayerReqCallback();
        }
    }    
    else
    {
        if(m_pCaptureDriver->bIfCapEnabled())
        {
            if(interlace ==SCREEN_INTERLACED_BOTTOM_FIELD)
			//SCREEN_INTERLACED_TOP_FIELD;)
            {
                m_pWin->update();
            }
            else
            {
				;
            }
            
            if(bFirstTiming)
            {
                bFirstTiming = FALSE;
                clock_gettime(CLOCK_MONOTONIC, &TimeStampFirstDraw);
                fprintf(stderr,"\n##############ADAS first camera image post ----> %ld MS###########\n", (TimeStampFirstDraw.tv_sec)*1000 + ((TimeStampFirstDraw.tv_nsec)/(1000000L)));
            }
         }
        else
        {
        	TRC_SCOPE(ADAS, CSimpleCaptureThread, render);
            m_pWin->drawDummyImage();
            //DBG_MSG(("############## m_pCaptureDriver not enabled but run update process ##############\n"));
            //fprintf(stderr,"############## !bIfCapEnabled #############\n");
        }      
    }
	m_pWin->waitVsync();
    if(0==iSkipFrames)
    {
        m_bReadyToRender = TRUE;
        iSkipFrames = -1;
    }
    
}

TRC_SCOPE_DEF(ADAS, CSimpleCaptureThread, FlushDummyDate);
void CSimpleCaptureThread::FlushDummyData()
{
    if(m_pWin)
    {
    	TRC_SCOPE(ADAS, CSimpleCaptureThread, FlushDummyDate);
        m_pWin->drawDummyImage();   
        m_pWin->waitVsync();
    }
}
TRC_SCOPE_DEF(ADAS, CSimpleCaptureThread, EnablePostData);
void CSimpleCaptureThread::EnablePostData()
{
	TRC_SCOPE(ADAS, CSimpleCaptureThread, EnablePostData);
	DBG_MSG(("**************************CSimpleCaptureThread EnablePostData*****************\n"));
	m_bReadyToRender = TRUE;
};
TRC_SCOPE_DEF(ADAS, CSimpleCaptureThread, DisablePostData);
void CSimpleCaptureThread::DisablePostData()
{
	TRC_SCOPE(ADAS, CSimpleCaptureThread, DisablePostData);
	DBG_MSG(("**************************CSimpleCaptureThread DisablePostData*****************\n"));
	m_bReadyToRender = FALSE;
};

void CSimpleCaptureThread::asyncPause(CFunctorArg0* pCALLBACK)
{
	tagAsyncPause tagAsyncPause;
	tagAsyncPause._pCapThread = this;
    tagAsyncPause._pAsyncPauseCALLBACK = pCALLBACK;
	pushMessage(tagAsyncPause, sizeof(tagAsyncPause));
}
//removed now
void CSimpleCaptureThread::asyncSetReportLayerReady()
{
	tagReportLayerReady tReportLayerReady;
	tReportLayerReady._pCapThread = (void*)this;
	pushMessage(tReportLayerReady, sizeof(tagReportLayerReady));
}
TRC_SCOPE_DEF(ADAS, CSimpleCaptureThread, CheckCurPendingRequest);
BOOLEAN CSimpleCaptureThread::bNoCurPendingRequest()
{
    BOOLEAN bNoPendActiveRequest = TRUE;
    //pending : update by last request and saved in the buffer while ack is not cleared ,if no new request coming up this request will pending
    //so we need monitor this pending requset and clear it once thread is not busy
    if((m_bAckChannelIndex)&&(-1!=m_iReqChannelIndex))
    {
        TRC_SCOPE(ADAS, CSimpleCaptureThread, CheckCurPendingRequest);
        DBG_MSG(("xxxxxxxxxxxxx processed pending msg of set chananle index to %d  xxxxxxxxxxxxxxxx\n", m_iReqChannelIndex));
        //only send camera state for last request channel
        m_needReportLayerReady =  FALSE;
        setCameraSourceIndex(m_iReqChannelIndex);   
        bNoPendActiveRequest =  FALSE;
    }
    if((m_bAckDriverState)&&(eNoPending!=m_bReqDriverState))
    {        
        TRC_SCOPE(ADAS, CSimpleCaptureThread, CheckCurPendingRequest);
        BOOLEAN bState=(eEnableDriver == m_bReqDriverState)?TRUE:FALSE;
        DBG_MSG(("xxxxxxxxxxxxx processed pending msg of setCameraState to %d  xxxxxxxxxxxxxxxx\n", bState));
        m_needReportLayerReady =  FALSE;
        setCameraState(bState);   
        bNoPendActiveRequest =  FALSE;
    } 
    if((m_bAckRCPos)&&(m_sRCPos.bPending))
    {        
        TRC_SCOPE(ADAS, CSimpleCaptureThread, CheckCurPendingRequest);
        DBG_MSG(("xxxxxxxxxxxxx processed pending msg of setScreenPosAndSize  xxxxxxxxxxxxxxxx\n"));
        setScreenPosAndSize(m_sRCPos.iX,m_sRCPos.iY,m_sRCPos.uiWidth,m_sRCPos.uiHeight);
    }    
    return bNoPendActiveRequest;
}

