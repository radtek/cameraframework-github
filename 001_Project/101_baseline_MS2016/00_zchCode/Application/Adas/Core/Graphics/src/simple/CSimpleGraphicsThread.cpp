#include "CSimpleGraphicsThread.h"
#include "CEGL.h"
#include "CBaseGraphicsImpl.h"
#include "CCameraSysManager.h"

CSimpleGraphicsThread* CSimpleGraphicsThread::s_pInstance = NULL;

CSimpleGraphicsThread* CSimpleGraphicsThread::getInstance(CBaseGraphicsImpl* pGraphicsImpl)
{
	if(s_pInstance==NULL)
	{
	//	CBaseGraphicsImpl* pGraphicsImpl = getGraphicsImpl();
		s_pInstance = new CSimpleGraphicsThread("graphics Thread",pGraphicsImpl);
	}
	return s_pInstance;
}

CSimpleGraphicsThread::CSimpleGraphicsThread(const string& strName, CBaseGraphicsImpl* pGraphicsImpl)
: CGraphicsThread(strName,pGraphicsImpl)
, m_pWin(NULL)
{

}

CSimpleGraphicsThread::~CSimpleGraphicsThread()
{
	;
}

TRC_SCOPE_DEF(CSimpleGraphicsThread, CSimpleGraphicsThread, Initialize);
bool CSimpleGraphicsThread::initialize()
{
	TRC_SCOPE(CSimpleGraphicsThread, CSimpleGraphicsThread, Initialize);
	UInt32 iDisplayID = CCommandLineParser::getInstance()->getItemUInt("-iDisplayID");
    UInt32 uiGraphicPipeline = CCommandLineParser::getInstance()->getItemUInt("-uiGraphicPipeline");
    UInt32 uiGraphicUsage = CCommandLineParser::getInstance()->getItemUInt("-uiGraphicUsage");
    
	DBG_MSG(("CSimpleGraphics::initialize iDisplayID=%d\n",iDisplayID));

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
		DBG_MSG(("CSimpleGraphicsThread::initialize ---change m_config.iPipeline=%d\n",m_config.iPipeline));
	}

    if(0!=uiGraphicPipeline)
    {
		m_config.iPipeline = uiGraphicPipeline;
    }
    else
    {
        ;
    }
    if(0!=uiGraphicUsage)
    {
        ;
    }   
    else
    {
        uiGraphicUsage = SCREEN_USAGE_WRITE|SCREEN_USAGE_NATIVE;
    }
    //fprintf(stderr,"CSimpleGraphicsThread::initialize ---set m_config.iPipeline=%d uiGraphicUsage=%d\n",m_config.iPipeline,uiGraphicUsage);

	CRectangle rc(m_config.iWinPos[0], m_config.iWinPos[1], m_config.uiWinSize[0], m_config.uiWinSize[1]);
	if(! m_pWin->create(m_config.strWinName, m_config.iPipeline, rc,SCREEN_FORMAT_RGBA8888 , uiGraphicUsage) )
	{
		DBG_ERROR(("Init window failed!\n"));
		return FALSE;
	}

	m_pWin->createBuffer(m_config.uiWinSize[0], m_config.uiWinSize[1], m_config.uiBufNum);


	if(! CEGL::getInstance()->initialize(m_pWin->getWin()))
	{
		DBG_ERROR(("egl init failed!\n"));
		return FALSE;
	}

	if(!initGraphicRes())
	{
		DBG_ERROR(("initGraphicRes failed!\n"));
		return FALSE;
	}

	if( m_pGraphicsImpl )
		m_pGraphicsImpl->initialize(m_config.iWinPos[0], m_config.iWinPos[1], m_config.uiWinSize[0], m_config.uiWinSize[1]);

	m_bInitialized = TRUE;

   PostDummyWin();

	return TRUE;
}
TRC_SCOPE_DEF(ADAS, CSimpleGraphicsThread, unInitialize);
void CSimpleGraphicsThread::unInitialize()
{
	TRC_SCOPE(ADAS, CSimpleGraphicsThread, unInitialize);
	if(m_pGraphicsImpl)
	{
		m_pGraphicsImpl->unInitialize();
		delete m_pGraphicsImpl;
		m_pGraphicsImpl = NULL;
	}

	CEGL::getInstance()->unInitialize();
	CEGL::deleteInstance();

	if( m_pWin )
	{
		m_pWin->destroy();
		delete m_pWin;
		m_pWin = NULL;
	}

	m_bInitialized = FALSE;
	DBG_MSG(("CGraphicOverlayThread::unInitialize end!\n"));
}

void CSimpleGraphicsThread::beforeHandleMessageQueue()
{
	;
}
TRC_SCOPE_DEF(ADAS, CSimpleGraphicsThread, afterHandleMessageQueue);
void CSimpleGraphicsThread::afterHandleMessageQueue()
{
	updateGraphic();
	if(m_pGraphicsImpl->isCurPendingRequest())
	{
		m_pGraphicsImpl->onCurPendingRequest();
	}

	if( m_pWin )
	{
		m_pWin->waitVsync();
	}
    
    if(m_NeedReportIfLayerReady)
    {
        m_NeedReportIfLayerReady = FALSE;
        m_config.pLayerReadyCallback();
    }

	static BOOLEAN bFirstRender = TRUE;
	if( bFirstRender )
		{
		    TRC_SCOPE(ADAS, CSimpleGraphicsThread, afterHandleMessageQueue);
			bFirstRender = FALSE;
			UInt32 uiTime = getTickCount();
			DBG_MSG(("**************************first GRAPHICS render***************** %u\n", uiTime));
			//exit(0);
		}
}

BOOLEAN CSimpleGraphicsThread::initGraphicRes()
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);

	return true;
}
//TRC_SCOPE_DEF(ADAS, CSimpleGraphicsThread, updateGraphic);
BOOLEAN CSimpleGraphicsThread::updateGraphic()
{
	//TRC_SCOPE(ADAS, CSimpleGraphicsThread, updateGraphic);
	glViewport(0,0,800,480);
	glClear(GL_COLOR_BUFFER_BIT);

	if(m_pGraphicsImpl)
		m_pGraphicsImpl->update();

	CEGL::getInstance()->update();
    //DBG_MSG(("**************************Drawed  Graphic  data *****************\n"));
	return TRUE;
}

BOOLEAN CSimpleGraphicsThread::PostDummyWin()
{
	glViewport(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);

	CEGL::getInstance()->update();
	return TRUE;
}

/*
void onPause()
{
	glViewport(0,0,800,480);
	glClear(GL_COLOR_BUFFER_BIT);
	//glClearColor(0.0f,0.0f,0.0f,1.0f);
	CEGL::getInstance()->update();

	DBG_MSG(("Graphics::onPause: clear screen\n"));
}
*/
