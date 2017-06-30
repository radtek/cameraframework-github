#ifndef CCAPTURETHREAD_HPP_
#define CCAPTURETHREAD_HPP_

#include "CScreenBufferArray.h"
#include "CCaptureDriver.hpp"
#include "CQNXCaptureDriver.hpp"
#include "CCaptureThread.h"
#include "foundation.h"
#include "CScreenWindow.h"

struct tagCameraPosBuf
{
	tagCameraPosBuf()
	{
        Int32		iX =0;
        Int32		iY =0;
        UInt32	    uiWidth =0;
        UInt32	    uiHeight =0; 
        BOOLEAN     bPending = FALSE;
        BOOLEAN     bDefault = TRUE;

	}
    Int32		iX;
	Int32		iY;
	UInt32	    uiWidth;
	UInt32	    uiHeight; 
    BOOLEAN     bPending;
    BOOLEAN     bDefault;
};

class CSimpleCaptureThread : public CCaptureThread
{
    
public:
    enum EPendingDriverState
	{
        eNoPending		    = 0,
		eEnableDriver	    = 1,
		eDisableDriver		= 2,
	};
	CSimpleCaptureThread(const string& strName);
	virtual ~CSimpleCaptureThread();

	void setCameraSourceIndex(int index);
	void setCameraState(BOOLEAN bEnable);

	void setScreenPosAndSize(Int32 x, Int32 y, UInt32 uiW, UInt32 uiH);

	void _setScreenPosAndSize(void* pData);
    void asyncPause(CFunctorArg0* pcallback);
    void asyncSetReportLayerReady();
    void setReportLayerReady() {m_needReportLayerReady = TRUE;};
    void FlushDummyData();
    void EnablePostData();
    void DisablePostData();
    //test
    void setSkipFrames(int cnt) {m_debugSkipFrame=cnt;};

protected:
	virtual BOOLEAN initialize() ;
	virtual void 	unInitialize() ;
	virtual void beforeHandleMessageQueue();
	virtual void afterHandleMessageQueue();

	void render(Int32 bufferIdx, Int32 interlace, BOOLEAN bReActived);

protected:
	CScreenWindow* 	m_pWin;
	int 			m_iCurCapBufIndex;
	int 			m_iCurCapField;
	UInt32			m_uiCheckSignalFrame;
		
	int 			m_iReqChannelIndex;
	int				m_iLastActiveCamera;
    EPendingDriverState             m_bReqDriverState; //threen state
    BOOLEAN         m_bAckChannelIndex;
    BOOLEAN         m_bAckDriverState;
    BOOLEAN         m_bAckRCPos;
    BOOLEAN         bNoCurPendingRequest();

private:
    CCaptureDriver::ESignalState	m_eLastSync;
    BOOLEAN m_needReportLayerReady;
    BOOLEAN m_bReadyToRender;
    tagCameraPosBuf	m_sRCPos;
    int   m_debugSkipFrame;
};

#endif /* CCAPTURETHREAD_HPP_ */
