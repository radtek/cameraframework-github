#ifndef _CSCREEN_BUFFER_H
#define _CSCREEN_BUFFER_H

#ifdef PLATFORM_QNX
#include <screen/screen.h>
#include "foundation.h"


class CScreenBufferArray : public Ref
{
public:
	CScreenBufferArray(class CScreenWindow* pWindow);
	virtual ~CScreenBufferArray();

	BOOLEAN 			setup(UInt32 uiW, UInt32 uiH, UInt32 uiNum, BOOLEAN bContinous = FALSE);
	void				destroy();

	unsigned char**		getVirtualAddr() 		{ return m_pVirtualAddr; }
	screen_buffer_t*	getBuffers() 			{ return m_pBuf;		}
	screen_buffer_t		getBuffer(UInt32 uidx)	{ return m_pBuf[uidx];	}
	UInt32				getBufferNum() const	{ return m_uiBufNum;	}
	UInt32				getFormat() const		{ return m_uiFormat;	}
	UInt32				getStride() const		{ return m_uiStride;	}
	UInt32				getWidth() const		{ return m_uiW;			}
	UInt32				getHeight() const		{ return m_uiH;			}

	//the size of pData must be the same as screen buffer
	void				fill(UInt32 uidx, unsigned char* pData);
	BOOLEAN 			getContiguousBufAddress();

protected://method
    void                SetupDummyBuffer();

private:
	CScreenWindow*			m_pParent;
	screen_buffer_t*   		m_pBuf;
	long long*				m_pPhysicalAddr;
	unsigned char*	*		m_pVirtualAddr;
	UInt32					m_uiBufNum;
	UInt32					m_uiFormat;
	UInt32					m_uiStride;
	UInt32					m_uiW;
	UInt32					m_uiH;
};

#endif

#endif
