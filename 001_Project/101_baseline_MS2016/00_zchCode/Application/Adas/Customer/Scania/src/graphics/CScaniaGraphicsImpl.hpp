#ifndef _CSCANIA_GRAPHICS_IMPL_HPP
#define _CSCANIA_GRAPHICS_IMPL_HPP

#include "CCameraSysManager.h"
#include "CAdasMsgQueDefine.hpp"
#include "GraphicsMessageDefine.h"

struct tagGraphicPosBuf
{
	tagGraphicPosBuf()
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

class CScaniaGraphicsImpl : public CBaseGraphicsImpl
{
public: // typedef enum struct

public: // method
	static CScaniaGraphicsImpl* getInstance();
	static void deleteInstance();

	virtual ~CScaniaGraphicsImpl();

	DECLARE_DISPATCH

	virtual void initialize(Int32 x, Int32 y, UInt32 uiW, UInt32 uiH  );
	virtual void unInitialize();

	virtual void update();
	virtual BOOLEAN isCurPendingRequest();
	virtual void onCurPendingRequest();

	void		asynshowStartUpImage(Int32 idx, BOOLEAN bShowStartUpImage);
	void		showStartUpImage(void* pData);

	void		asynShowGuideLine(Int32 idx);
	void		showGuideLine(void* pData);

	void 		asynSetPosAndSize(const CRectangle& rc);
	void		setPosAndSize(void* pData);
//    void        NotifyGraphicReady(void* pData);

protected:// method
	CScaniaGraphicsImpl();

private: // method
	void setReqShowStartUpImageStatus(BOOLEAN bStatus);
	void setReqShowGuideLineStatus(BOOLEAN bStatus);
	void setGraphicPosPendingStatus(BOOLEAN bStatus);

protected: // data

private:// data
	static CScaniaGraphicsImpl*	s_pInstance;
    BOOLEAN bNotifyGraphicIsReady;

    tagshowStartUpImage m_sLastShowStartUpImage;
    BOOLEAN m_bShowStartUpImageAck;
    BOOLEAN m_bReqShowStartUpImage;

    int m_iGuideLineOldId;
    BOOLEAN m_bShowGuideLineAck;
	BOOLEAN m_bReqShowGuideLine;

	tagGraphicPosBuf	m_sRCPos;
    BOOLEAN m_bRCPosAck;

    Mutex m_mutex_ack;
    Mutex m_mutex_req;
};

#endif
