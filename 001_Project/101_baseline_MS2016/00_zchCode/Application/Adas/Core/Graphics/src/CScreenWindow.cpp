#include "CScreenWindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CScreenBufferArray.h"

TRC_SCOPE_DEF(CScreenWindow, CScreenWindow, create);
TRC_SCOPE_DEF(CScreenWindow, CScreenWindow, destroy);
TRC_SCOPE_DEF(CScreenWindow, CScreenWindow, update);
TRC_SCOPE_DEF(CScreenWindow, CScreenWindow, setZOrder);


CScreenWindow::CScreenWindow(screen_context_t screenCtx,screen_display_t screenDisp)
: m_pWindow(NULL)
, m_pBufferArray(NULL)
, screen_ctx(screenCtx)
, screen_disp(screenDisp)
, m_iZOrder(-1)
, m_iPipeline(-1)
, m_iInterval(0)
, m_uiFormat(0)
, m_uiCurPostBufIndex(0)
{
	;
}

CScreenWindow::~CScreenWindow()
{
	destroy();

}
TRC_SCOPE_DEF(ADAS, CScreenWindow, CScreenWindow);
BOOLEAN CScreenWindow::create(const string& strName, Int32 iPipeline, const CRectangle& rect, UInt32 uiFormat, UInt32 uiUsage)
{
	TRC_SCOPE(ADAS, CScreenWindow, CScreenWindow);

	m_rc = rect;
	m_iPipeline = iPipeline;
	m_uiFormat = uiFormat;

    Int32 rc = screen_create_window(&m_pWindow, screen_ctx);
	if (rc) {
		DBG_ERROR(( "screen_create_window failed: %s!\n",strerror(errno)));
		return FALSE;
	}

	DBG_MSG(("CScreenWin::CreateWindow 2\n"));
	//set display to this window
	rc = screen_set_window_property_pv(m_pWindow, SCREEN_PROPERTY_DISPLAY, (void **)&(screen_disp));
	if (rc) {
		DBG_ERROR(("screen_set_window_property_ptr(SCREEN_PROPERTY_DISPLAY): %s!\n",strerror(errno)));
		return FALSE;
	}

	DBG_MSG(("CScreenWin::CreateWindow 3\n"));
	//usage of this window
	Int32 iUsage = uiUsage;
	rc = screen_set_window_property_iv(m_pWindow, SCREEN_PROPERTY_USAGE, (Int32*)&(iUsage));
	if (rc) {
		DBG_ERROR(( "screen_set_window_property_iv(SCREEN_PROPERTY_USAGE):%s\n",strerror(errno)));
		return FALSE;
	}

	//set the pixel format of this window
	DBG_MSG(("CScreenWin::CreateWindow format=%d\n", uiFormat));
	Int32 iFormat = uiFormat;
	rc = screen_set_window_property_iv(m_pWindow, SCREEN_PROPERTY_FORMAT, (Int32*)&(iFormat));
	if (rc) {
		DBG_ERROR(( "screen_set_window_property_iv(SCREEN_PROPERTY_FORMAT):%s\n",strerror(errno)));
		return FALSE;
	}

	DBG_MSG(("CScreenWin::CreateWindow size=%d,%d\n", m_rc.getWidth(), m_rc.getHeight()));
	Int32 isize[2];
	isize[0] = m_rc.getWidth();
	isize[1] = m_rc.getHeight();
	//set window size
	rc = screen_set_window_property_iv(m_pWindow, SCREEN_PROPERTY_SIZE, isize);
	if (rc) {
		DBG_ERROR(( "screen_set_window_property_iv(SCREEN_PROPERTY_SIZE):%s\n",strerror(errno)));
		return FALSE;
	}

	//set window position
	Int32 ipos[2];
	ipos[0] = m_rc.getX();
	ipos[1] = m_rc.getY();
	rc = screen_set_window_property_iv(m_pWindow, SCREEN_PROPERTY_POSITION, ipos);
	if (rc) {
		DBG_ERROR(("screen_set_window_property_iv(SCREEN_PROPERTY_POSITION):%s\n",strerror(errno)));
		return FALSE;
	}

	rc = screen_set_window_property_cv(m_pWindow, SCREEN_PROPERTY_ID_STRING, strName.size(),strName.c_str());
	if(rc){
		DBG_ERROR(("screen_set_window_property_iv(SCREEN_PROPERTY_ID_STRING): %s!\n",strerror(errno)));
		return FALSE;
	}

    DBG_ERROR(("screen_set_window_property_iv(SCREEN_PROPERTY_PIPELINE): %d !\n",iPipeline));
	rc = screen_set_window_property_iv(m_pWindow, SCREEN_PROPERTY_PIPELINE, &(iPipeline));
	if(rc){
		DBG_ERROR(("screen_set_window_property_iv(SCREEN_PROPERTY_PIPELINE): %s!\n",strerror(errno)));
		return FALSE;
	}
	rc = screen_flush_context(screen_ctx,SCREEN_WAIT_IDLE);
	if(rc){
		DBG_ERROR(("screen_flush_context%s!\n",strerror(errno)));
		return FALSE;
	}	

	return TRUE;
}

void CScreenWindow::destroy()
{
	if(m_pWindow)
	{
		screen_destroy_window(m_pWindow);
		m_pWindow = NULL;
	}

	if( NULL != m_pBufferArray )
	{
		m_pBufferArray->release();
		m_pBufferArray = NULL;
	}
}

void CScreenWindow::createBuffer(UInt32 uiW, UInt32 uiH, UInt32 uiNum, BOOLEAN bContigous)
{
	CScreenBufferArray* pBufArray = new CScreenBufferArray(this);
	pBufArray->setup(uiW,uiH, uiNum,bContigous);

	m_pBufferArray = pBufArray;
	
}
TRC_SCOPE_DEF(ADAS, CScreenWindow, update);
bool CScreenWindow::update()
{
	if(m_pWindow && m_pBufferArray )
	{
		//TRC_SCOPE(ADAS, CScreenWindow, update);
		Int32 iRect[4];
		iRect[0] = m_rc.getX();
		iRect[1] = m_rc.getY();
		iRect[2] = m_rc.getRight();
		iRect[3] = m_rc.getBottom();
		int rc = screen_post_window( m_pWindow, m_pBufferArray->getBuffer(m_uiCurPostBufIndex), 1, iRect, 0 );
		if(rc)
		{
			TRC_SCOPE(ADAS, CScreenWindow, update);
			DBG_ERROR(("screen_post_window error!\n"));
			return FALSE;
		}
        //DBG_MSG(("**************************Flash with Capture  data *****************\n"));
	}
	return TRUE;
}
TRC_SCOPE_DEF(ADAS, CScreenWindow, postDummyWin);
bool CScreenWindow::postDummyWin()
{
	if(m_pWindow && m_pBufferArray )
	{
		Int32 iRect[4];
		iRect[0] = 0;
		iRect[1] = 0;
		iRect[2] = 0;
		iRect[3] = 0;
		int rc = screen_post_window( m_pWindow, m_pBufferArray->getBuffer(m_uiCurPostBufIndex), 1, iRect, 0 );
		if(rc)
		{
			TRC_SCOPE(ADAS, CScreenWindow, postDummyWin);
			DBG_ERROR(("screen_post_window error!\n"));
			return FALSE;
		}
	}
	return TRUE;
}
//TRC_SCOPE_DEF(ADAS, CScreenWindow, waitVsync);
bool CScreenWindow::waitVsync()
{
    //TRC_SCOPE(ADAS, CScreenWindow, waitVsync);
	if(m_pWindow&&screen_disp)
	{
		screen_wait_vsync(screen_disp);
        //DBG_MSG(("**************************waitVsync**********************\n"));
	}
	return true;
}

void CScreenWindow::draw(unsigned char* pData)
{
	m_pBufferArray->fill(m_uiCurPostBufIndex, pData);
	update();
}

//for performance: draw last predifined buffer
TRC_SCOPE_DEF(ADAS, CScreenWindow, drawDummyImage);
void CScreenWindow::drawDummyImage()
{
    //TRC_SCOPE(ADAS, CScreenWindow, drawDummyImage);
	if(m_pWindow && m_pBufferArray )
	{
		
		Int32 iRect[4];
		iRect[0] = m_rc.getX();
		iRect[1] = m_rc.getY();
		iRect[2] = m_rc.getRight();
		iRect[3] = m_rc.getBottom();
		int rc = screen_post_window( m_pWindow, m_pBufferArray->getBuffer(m_pBufferArray->getBufferNum()-1), 1, iRect, 0 );
		if(rc)
		{
			TRC_SCOPE(ADAS, CScreenWindow, drawDummyImage);
			DBG_ERROR(("screen_post_window error@drawDummyImage!\n"));
		}
        //DBG_MSG(("**************************FlushDummyData**********************\n"));
	}
}
TRC_SCOPE_DEF(ADAS, CScreenWindow, setZOrder);
BOOLEAN CScreenWindow::setZOrder(int zorder)
{
	TRC_SCOPE(ADAS, CScreenWindow, setZOrder);
	if( m_pWindow == NULL )
		return FALSE;

	if(zorder == m_iZOrder)
		return TRUE;

	m_iZOrder = zorder;

	int rc = screen_set_window_property_iv(m_pWindow, SCREEN_PROPERTY_ZORDER, &m_iZOrder);
	if (rc) {
		DBG_ERROR(("screen_set_window_property_iv(SCREEN_PROPERTY_ZORDER): %s!\n",strerror(errno)));
		return FALSE;
	}
	return TRUE;
}
TRC_SCOPE_DEF(ADAS, CScreenWindow, setPos);
void CScreenWindow::setPos(Int32 iX, Int32 iY)
{
	TRC_SCOPE(ADAS, CScreenWindow, setPos);
	if( m_pWindow == NULL)
		return;

	if( m_rc.getX() == iX && m_rc.getY() == iY )
		return;

	m_rc.setX(iX);
	m_rc.setY(iY);
	Int32 iPos[2];
	iPos[0] = iX;
	iPos[1] = iY;
	int	rc = screen_set_window_property_iv(m_pWindow, SCREEN_PROPERTY_POSITION, iPos);
	if (rc) {
		DBG_ERROR(("screen_set_window_property_iv(SCREEN_PROPERTY_POSITION):%s\n",strerror(errno)));

	}
}
TRC_SCOPE_DEF(ADAS, CScreenWindow, setSize);
void CScreenWindow::setSize(UInt32 uiW, UInt32 uiH)
{
	if( m_pWindow == NULL )
		return;

	if( m_rc.getWidth() == uiW && m_rc.getHeight() == uiH )
			return;

	m_rc.setWidth(uiW);
	m_rc.setHeight(uiH);
	UInt32 iSize[2];
	iSize[0] = uiW;
	iSize[1] = uiH;
	int rc = screen_set_window_property_iv(m_pWindow, SCREEN_PROPERTY_SIZE, (Int32*)iSize);
	if (rc) {
		TRC_SCOPE(ADAS, CScreenWindow, setSize);
		DBG_ERROR(( "screen_set_window_property_iv(SCREEN_PROPERTY_SIZE):%s\n",strerror(errno)));
	}

}

bool CScreenWindow::setCurPostBufIndex(UInt32 index)
{
	if( index >= m_pBufferArray->getBufferNum() )
	{
		return FALSE;
	}
	else
	{
		m_uiCurPostBufIndex = index;
	}
	return true;
}

TRC_SCOPE_DEF(CScreenWindow, CScreenWindow, setCurInterlaceField);
bool CScreenWindow::setCurInterlaceField(int interlaced)
{
	int rc = screen_set_buffer_property_iv(m_pBufferArray->getBuffer(m_uiCurPostBufIndex), SCREEN_PROPERTY_INTERLACED, &interlaced);
	if (rc) {
        TRC_SCOPE(CScreenWindow, CScreenWindow, setCurInterlaceField);
		DBG_ERROR(( "screen_set_buffer_property_iv(SCREEN_PROPERTY_INTERLACED),%s\n",strerror(errno)));
		return false;
	}
	return true;
}


