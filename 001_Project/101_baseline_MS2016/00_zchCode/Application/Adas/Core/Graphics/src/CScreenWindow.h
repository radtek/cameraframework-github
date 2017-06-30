#ifndef CSCREENWINDOW_HPP_
#define CSCREENWINDOW_HPP_

#include <screen/screen.h>
#include "foundation.h"

#define DefaultWinWidth     800
#define DefaultWinHeight    480
#define DefaultWinPosX      0
#define DefaultWinPosY      0
#define DefaultBufferWidth  720
#define DefaultBufferHeight 480
#define WIN_NAME_MAXLENGTH 256


class CScreenBufferArray;

class CScreenWindow
{

public:
	CScreenWindow(screen_context_t screenCtx,screen_display_t screenDisp);
	virtual ~CScreenWindow();


	BOOLEAN create(const string& strName, Int32 iPipeline, const CRectangle& rc, UInt32 uiformat, UInt32 uiUsage);
	void	destroy();
	void	createBuffer(UInt32 uiW, UInt32 uiH, UInt32 uiNum, BOOLEAN bContinous = FALSE);
	void	attachBuffer(CScreenBufferArray* pBufArray);
	BOOLEAN	update();
	BOOLEAN waitVsync();
	void	draw(unsigned char* pData);

	bool setZOrder(int zorder);
	void setPos(Int32 iX, Int32 iY);
	void setSize(UInt32 uiW, UInt32 uiH);

	bool setCurPostBufIndex(UInt32 index);
	bool setCurInterlaceField(int interlaced);

	screen_window_t getWin() 			{ return m_pWindow;		}
	int 			getInterval()		{ return m_iInterval;	}
	int 			getZOrder()			{ return m_iZOrder;		}
	int 			getPipeline()		{ return m_iPipeline;	}
	UInt32			getFormat() const	{ return m_uiFormat;	}
	CScreenBufferArray*	getScreenBufferArray() { return m_pBufferArray;	}
	bool  postDummyWin();
    void  InitDummyImage();
    void  drawDummyImage();
protected: // method
	CScreenWindow(const CScreenWindow& win)				{}
	CScreenWindow& operator= (const CScreenWindow& win)	{ return (*this); }

protected: // data

	screen_window_t      	m_pWindow;
	CScreenBufferArray*		m_pBufferArray;

	screen_context_t  	screen_ctx;
	screen_display_t 	screen_disp;

	int 		m_iZOrder;
	int 		m_iPipeline;
	int 		m_iInterval;
	UInt32		m_uiFormat;

	UInt32 		m_uiCurPostBufIndex;
	CRectangle 	m_rc;
};


#endif /* CSCREENWINDOW_HPP_ */

