#include "CScaniaGraphicsImpl.hpp"
#include "foundation.h"
#include "CEOL.hpp"

static CRenderImage* pImageStartUp = NULL;
static CRenderImage* s_pImageGuideLine = NULL;
static CRenderUtility utility;
static CRenderContainer container;
const static string strImage1("/fs/etfs/adas/image/camera1.png");
const static string strImage2("/fs/etfs/adas/image/camera2.png");
static Array<CRenderContainer*> aryContainer;

Array<string>	s_aryGuideLinePath;

CScaniaGraphicsImpl*	CScaniaGraphicsImpl::s_pInstance = NULL;

CScaniaGraphicsImpl* CScaniaGraphicsImpl::getInstance()
{
	if( s_pInstance == NULL )
	{
		s_pInstance = new CScaniaGraphicsImpl();
	}

	return s_pInstance;
}

void CScaniaGraphicsImpl::deleteInstance()
{
	if( s_pInstance != NULL )
	{
		delete s_pInstance;
		s_pInstance = NULL;
	}
}

CScaniaGraphicsImpl::CScaniaGraphicsImpl()
: bNotifyGraphicIsReady(FALSE)
{
    m_sRCPos.iX=0;
    m_sRCPos.iY=0;
    m_sRCPos.uiWidth=0;
    m_sRCPos.uiHeight=0;
    m_sRCPos.bPending = FALSE;
    m_sRCPos.bDefault = TRUE;
    m_bRCPosAck = TRUE;

    m_sLastShowStartUpImage.idx = -1;
    m_sLastShowStartUpImage.bShowStartUpImage = FALSE;
    m_bShowStartUpImageAck = TRUE;
    m_bReqShowStartUpImage = FALSE;

    m_iGuideLineOldId = -1;
    m_bReqShowGuideLine = FALSE;
    m_bShowGuideLineAck = TRUE;

	s_aryGuideLinePath.push_back("/fs/etfs/adas/image/guideLine1.png");
	s_aryGuideLinePath.push_back("/fs/etfs/adas/image/guideLine2.png");
	s_aryGuideLinePath.push_back("/fs/etfs/adas/image/guideLine3.png");
	s_aryGuideLinePath.push_back("/fs/etfs/adas/image/guideLine4.png");
	s_aryGuideLinePath.push_back("/fs/etfs/adas/image/guideLine5.png");
	s_aryGuideLinePath.push_back("/fs/etfs/adas/image/guideLine6.png");
	s_aryGuideLinePath.push_back("/fs/etfs/adas/image/guideLine7.png");
	s_aryGuideLinePath.push_back("/fs/etfs/adas/image/guideLine8.png");
	s_aryGuideLinePath.push_back("/fs/etfs/adas/image/guideLine9.png");
	s_aryGuideLinePath.push_back("/fs/etfs/adas/image/guideLine10.png");

}

CScaniaGraphicsImpl::~CScaniaGraphicsImpl()
{
	s_pInstance = NULL;
}
TRC_SCOPE_DEF(ADAS, CScaniaGraphicsImpl, initialize);
void CScaniaGraphicsImpl::initialize(Int32 x, Int32 y, UInt32 uiW, UInt32 uiH)
{
    TRC_SCOPE(ADAS, CScaniaGraphicsImpl, initialize);
	utility.initialize();

//	if( !EOL::getInitCapture() )
	if((EOL::getCameraStartupTime(CCamera::eCamera1)!= 0)||(EOL::getCameraStartupTime(CCamera::eCamera2)!= 0))
	{
		DBG_MSG(("CScaniaGraphicsImpl::initialize\n"));
		pImageStartUp = new CRenderImage();
		//pImageStartUp->setTexture(CTexturePool::getInstance()->getExternalTexture(strImage1));
		pImageStartUp->setProgram(CProgramPool::getInstance()->getProgram(EPRG_UI_DEFAULT));
		pImageStartUp->set(x,y,uiW,uiH);
		pImageStartUp->setTexture(NULL);
		container.addRenderElement(pImageStartUp);
        CTexturePool::getInstance()->getExternalTexture(strImage1);
	}

	DBG_MSG(("CScaniaGraphicsImpl::initialize %d %d %u %u\n", x,y, uiW,uiH));
	s_pImageGuideLine = new CRenderImage();
	s_pImageGuideLine->setProgram(CProgramPool::getInstance()->getProgram(EPRG_UI_DEFAULT));
	s_pImageGuideLine->set(x,y,uiW,uiH);
	s_pImageGuideLine->setTexture(NULL);

	CTexturePool::getInstance()->getExternalTexture(strImage2);


	container.addRenderElement(s_pImageGuideLine);
	container.setRectangle(x,y,uiW,uiH);

	aryContainer.push_back(&container);
}

TRC_SCOPE_DEF(ADAS, CScaniaGraphicsImpl, unInitialize);
void CScaniaGraphicsImpl::unInitialize()
{
    TRC_SCOPE(ADAS, CScaniaGraphicsImpl, unInitialize);
	DBG_MSG(("CScaniaGraphicsImpl::unInitialize\n"));
    
    if(pImageStartUp)
    {
        pImageStartUp->setTexture(NULL);
    }
	
	if( pImageStartUp )
	{
		pImageStartUp->release();
		pImageStartUp = NULL;
	}
    
    if(s_pImageGuideLine)
    {
        s_pImageGuideLine->setTexture(NULL);
    }

	if( s_pImageGuideLine )
	{
		s_pImageGuideLine->release();
		s_pImageGuideLine = NULL;
	}

	container.clear();
	utility.unInitialize();
}

void CScaniaGraphicsImpl::update()
{
	utility.render(aryContainer);


}

BEGIN_DISPATCH(CScaniaGraphicsImpl)
	DISPATCH_EVENT(eGraphicsMsgID_GuideLine, showGuideLine)
	DISPATCH_EVENT(eGraphicsMsgID_PosSize, setPosAndSize)
	DISPATCH_EVENT(eGraphicsMsgID_ShowStartUpImage, showStartUpImage)
//	DISPATCH_EVENT(eGraphicsMsgID_NotifyGraphicReady, NotifyGraphicReady)
END_DISPATCH

TRC_SCOPE_DEF(ADAS, CScaniaGraphicsImpl, asynshowStartUpImage);
void CScaniaGraphicsImpl::asynshowStartUpImage(Int32 idx, BOOLEAN bShowStartUpImage)
{
    TRC_SCOPE(ADAS, CScaniaGraphicsImpl, asynshowStartUpImage);
    if(m_sLastShowStartUpImage.idx == idx && m_sLastShowStartUpImage.bShowStartUpImage == bShowStartUpImage)
    {
    	TRC_SCOPE(ADAS, CScaniaGraphicsImpl, asynshowStartUpImage);
    	DBG_MSG(("Graphics asynshowStartUpImage not change ,so return /n"));

    	setReqShowStartUpImageStatus(FALSE);
    	return;
    }
	/*if( EOL::getInitCapture() )
		return;

	//ADAS_DBG_MSG("asynShowCamera\n");
	CCommonMessage::CFunctor* pFunctor = makeFunctor(this,&CScaniaGraphicsImpl::showCamera);
	CCommonMessage* pMsg = new CCommonMessage(pFunctor);
	pMsg->setUserData((void*)uidx);
	CCameraSysManager::getInstance()->pushGraphicsMessage(pMsg);*/
	if(idx >= 0 && m_bShowStartUpImageAck)
	{
		DBG_MSG(("---->CScaniaGraphicsImpl::asynshowStartUpImage camera %d state %d\n",idx, bShowStartUpImage));
		tagshowStartUpImage tag;
		tag.idx = idx;
		tag.bShowStartUpImage = bShowStartUpImage;
		CCameraSysManager::getInstance()->pushGraphicsMessage(tag, sizeof(tagshowStartUpImage));

		setReqShowStartUpImageStatus(FALSE);
	}
    else
    {
    	DBG_MSG(("---->CScaniaGraphicsImpl::asynshowStartUpImage camera index wrong!\n"));
    	/////if need to record last req
    	setReqShowStartUpImageStatus(TRUE);
    }

	m_sLastShowStartUpImage.idx = idx;
	m_sLastShowStartUpImage.bShowStartUpImage = bShowStartUpImage;

	Mutex::ScopedLock lock(m_mutex_ack);
	m_bShowStartUpImageAck = FALSE;
}

TRC_SCOPE_DEF(ADAS, CScaniaGraphicsImpl, showStartUpImage);
void CScaniaGraphicsImpl::showStartUpImage(void* pData)
{	
    TRC_SCOPE(ADAS, CScaniaGraphicsImpl, showStartUpImage);
//	DBG_MSG(("CScaniaGraphicsImpl::showCamera\n"));
	tagshowStartUpImage* pTag = (tagshowStartUpImage*)(pData);
	if( !pTag ) return;
	DBG_MSG(("CScaniaGraphicsImpl::showStartUpImage %d state %d\n", pTag->idx, pTag->bShowStartUpImage));

	if( pTag->idx == 0 && pTag->bShowStartUpImage)
	{
		if( pImageStartUp )
			pImageStartUp->setTexture(CTexturePool::getInstance()->getExternalTexture(strImage1));
	}
	else if(pTag->idx == 1 && pTag->bShowStartUpImage)
	{
		if( pImageStartUp )
			pImageStartUp->setTexture(CTexturePool::getInstance()->getExternalTexture(strImage2));
	}
	else
	{
		if( pImageStartUp )
			pImageStartUp->setTexture(NULL);
	}

	Mutex::ScopedLock lock(m_mutex_ack);
	m_bShowStartUpImageAck = TRUE;
}
#if 0
void CScaniaGraphicsImpl::asynNotifyGraphicReady()
{
	tagNotifyIfGraphicReady tag ;
	tag.bNeedToNotifyLayerReady =  TRUE;
	CCameraSysManager::getInstance()->pushGraphicsMessage(tag, sizeof(tagNotifyIfGraphicReady));
}

void CScaniaGraphicsImpl::NotifyGraphicReady(void* pData)
{
    DBG_MSG(("CScaniaGraphicsImpl::NotifyGraphicReady\n"));
    setNeedReportLayerReady();
    
}
#endif
TRC_SCOPE_DEF(ADAS, CScaniaGraphicsImpl, asynShowGuideLine);
void CScaniaGraphicsImpl::asynShowGuideLine(int idx)
{
    TRC_SCOPE(ADAS, CScaniaGraphicsImpl, asynShowGuideLine);
    DBG_MSG(("CScaniaGraphicsImpl::asynShowGuideLine idx = %d m_bShowGuideLineAck = %d\n", idx, m_bShowGuideLineAck));
	if(idx >= 0 && m_bShowGuideLineAck)
	{
		tagGuideLine tag;
		tag._uidx = idx;
		CCameraSysManager::getInstance()->pushGraphicsMessage(tag, sizeof(tagGuideLine));

		setReqShowGuideLineStatus(FALSE);
	}
	else
	{
		DBG_MSG(("CScaniaGraphicsImpl::asynShowGuideLine -1\n"));
		setReqShowGuideLineStatus(TRUE);
	}

	m_iGuideLineOldId = idx;

	Mutex::ScopedLock lock(m_mutex_ack);
	m_bShowGuideLineAck = FALSE;
}

TRC_SCOPE_DEF(ADAS, CScaniaGraphicsImpl, showGuideLine);
void CScaniaGraphicsImpl::showGuideLine(void* pData)
{
    TRC_SCOPE(ADAS, CScaniaGraphicsImpl, showGuideLine);
	tagGuideLine* pTag = (tagGuideLine*)(pData);
	if( !pTag ) return;
	DBG_MSG(("showGuideLine %d\n", pTag->_uidx));
	if( pTag->_uidx < EOL::getOff_GuideLineNum() )
	{
		DBG_MSG(("CScaniaGraphicsImpl::showGuideLine %u\n",(UInt32)s_pImageGuideLine->getTexture()));
		s_pImageGuideLine->setTexture(CTexturePool::getInstance()->getExternalTexture(s_aryGuideLinePath[pTag->_uidx]));
	}
	else
	{
		DBG_MSG(("CScaniaGraphicsImpl::showGuideLine NULL\n"));
		s_pImageGuideLine->setTexture(NULL);
	}

	Mutex::ScopedLock lock(m_mutex_ack);
	m_bShowGuideLineAck = TRUE;
}

TRC_SCOPE_DEF(ADAS, CScaniaGraphicsImpl, asynSetPosAndSize);
void CScaniaGraphicsImpl::asynSetPosAndSize(const CRectangle& rc)
{
	tagGraphicsPosSize tag;
	tag._rc = rc;
    if((m_sRCPos.iX == tag._rc.m_iX)&&(m_sRCPos.iY==tag._rc.m_iY)&&(m_sRCPos.uiWidth==tag._rc.m_uiWidth)&&(m_sRCPos.uiHeight==tag._rc.m_uiHeight)&&(!m_sRCPos.bDefault))
    {
    	TRC_SCOPE(ADAS, CScaniaGraphicsImpl, asynSetPosAndSize);
        DBG_MSG(("Graphics asynSetPosAndSize not change ,so return /n"));
        setGraphicPosPendingStatus(FALSE);
        return;
    }
	m_sRCPos.iX =  tag._rc.m_iX;
    m_sRCPos.iY =  tag._rc.m_iX;
    m_sRCPos.uiWidth =  tag._rc.m_uiWidth;
    m_sRCPos.uiHeight = tag._rc.m_uiHeight;
    m_sRCPos.bDefault = FALSE;
    if(m_bRCPosAck)
    {
    	CCameraSysManager::getInstance()->pushGraphicsMessage(tag, sizeof(tag));
    	setGraphicPosPendingStatus(FALSE);
    }
    else
    {
    	TRC_SCOPE(ADAS, CScaniaGraphicsImpl, asynSetPosAndSize);
    	DBG_MSG(("CScaniaGraphicsImpl::asynShowGuideLine -1\n"));
    	setGraphicPosPendingStatus(TRUE);
    }

    Mutex::ScopedLock lock(m_mutex_ack);
    m_bRCPosAck = FALSE;
}
TRC_SCOPE_DEF(ADAS, CScaniaGraphicsImpl, setPosAndSize);
void CScaniaGraphicsImpl::setPosAndSize(void* pData)
{
	tagGraphicsPosSize* pRC = (tagGraphicsPosSize*)pData;
	if( pRC )
	{
		CRectangle& rc = pRC->_rc;
		TRC_SCOPE(ADAS, CScaniaGraphicsImpl, setPosAndSize);
		ADAS_DBG_MSG("setPosAndSize\n");
		if( pImageStartUp )
			pImageStartUp->set(rc.getX(), rc.getY(), rc.getWidth(), rc.getHeight());

		if( s_pImageGuideLine )
			s_pImageGuideLine->set(rc.getX(), rc.getY(), rc.getWidth(), rc.getHeight());

	}

	Mutex::ScopedLock lock(m_mutex_ack);
	m_bRCPosAck = TRUE;
}

TRC_SCOPE_DEF(ADAS, CScaniaGraphicsImpl, isCurPendingRequest);
BOOLEAN CScaniaGraphicsImpl::isCurPendingRequest()
{
	return (m_bReqShowStartUpImage || m_bReqShowGuideLine || m_sRCPos.bPending);
}

TRC_SCOPE_DEF(ADAS, CScaniaGraphicsImpl, onCurPendingRequest);
void CScaniaGraphicsImpl::onCurPendingRequest()
{
	if(m_bReqShowStartUpImage && m_bShowStartUpImageAck)
	{
		TRC_SCOPE(ADAS, CScaniaGraphicsImpl, onCurPendingRequest);
		DBG_MSG(("---->CScaniaGraphicsImpl::onCurPendingRequest camera %d state %d\n", m_sLastShowStartUpImage.idx, m_sLastShowStartUpImage.bShowStartUpImage));
		tagshowStartUpImage tag;
		tag.idx = m_sLastShowStartUpImage.idx;
		tag.bShowStartUpImage = m_sLastShowStartUpImage.bShowStartUpImage;
		CCameraSysManager::getInstance()->pushGraphicsMessage(tag, sizeof(tagshowStartUpImage));

		setReqShowStartUpImageStatus(FALSE);
		Mutex::ScopedLock lock(m_mutex_ack);
		m_bShowStartUpImageAck = FALSE;
	}
	if(m_bReqShowGuideLine && m_bShowGuideLineAck)
	{
		TRC_SCOPE(ADAS, CScaniaGraphicsImpl, onCurPendingRequest);
		DBG_MSG(("---->CScaniaGraphicsImpl::onCurPendingRequest guideLine id = %d\n", m_iGuideLineOldId));
		tagGuideLine tag;
		tag._uidx = m_iGuideLineOldId;
		CCameraSysManager::getInstance()->pushGraphicsMessage(tag, sizeof(tagGuideLine));

		setReqShowGuideLineStatus(FALSE);
		Mutex::ScopedLock lock(m_mutex_ack);
		m_bShowGuideLineAck = FALSE;
	}
	if(m_sRCPos.bPending && m_bRCPosAck)
	{
		TRC_SCOPE(ADAS, CScaniaGraphicsImpl, onCurPendingRequest);
		DBG_MSG(("---->CScaniaGraphicsImpl::onCurPendingRequest RCPos \n"));
		tagGraphicsPosSize tag;
		tag._rc.m_iX = m_sRCPos.iX;
		tag._rc.m_iX = m_sRCPos.iY;
		tag._rc.m_uiWidth = m_sRCPos.uiWidth;
		tag._rc.m_uiHeight = m_sRCPos.uiHeight;
		CCameraSysManager::getInstance()->pushGraphicsMessage(tag, sizeof(tag));
		m_sRCPos.bDefault = FALSE;

		setGraphicPosPendingStatus(FALSE);
		Mutex::ScopedLock lock(m_mutex_ack);
		m_bRCPosAck = FALSE;
	}
}

void CScaniaGraphicsImpl::setReqShowStartUpImageStatus(BOOLEAN bStatus)
{
	Mutex::ScopedLock lock(m_mutex_req);
	m_bReqShowStartUpImage = bStatus;
}

void CScaniaGraphicsImpl::setReqShowGuideLineStatus(BOOLEAN bStatus)
{
	Mutex::ScopedLock lock(m_mutex_req);
	m_bReqShowGuideLine = bStatus;
}

void CScaniaGraphicsImpl::setGraphicPosPendingStatus(BOOLEAN bStatus)
{
	Mutex::ScopedLock lock(m_mutex_req);
	m_sRCPos.bPending =  bStatus;
}
