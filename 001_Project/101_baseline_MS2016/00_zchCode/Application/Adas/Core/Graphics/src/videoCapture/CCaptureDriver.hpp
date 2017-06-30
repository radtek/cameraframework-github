#ifndef CCAPTUREDRIVER_HPP_
#define CCAPTUREDRIVER_HPP_

#include "foundation.h"
#include <vcapture/capture.h>


#ifdef CAPTURE_J5
#include <vcapture/capture-j5-ext.h>
#endif
#ifdef CAPTURE_OMAP4_5
#include <vcapture/capture-omap4-5-ext.h>
#endif
#ifdef CAPTURE_ADV
#include <vcapture/capture-adv-ext.h>
#endif
#ifdef CAPTURE_IMX6X
#include <vcapture/capture-imx6x-ext.h>
#endif
#ifdef HD_DEC_CLIENT
#include "hd-dec-client.h"
#endif

#define INTERLACE_FIELD_VALUE_INVALID (-1)
#define BUFFER_INDEX_VALUE_INVALID (-1)

#include "foundation.h"
#include "CScreenWindow.h"

class CCaptureDriver
{
public://enum
	enum ESignalState
	{
		eSignalState_Valid,
		eSignalState_Invalid,
	};

public:
	CCaptureDriver()
	: m_eSignalState(eSignalState_Valid)
	{
		m_iBufferNum = -1;
		m_bInit = false;
	}

	virtual ~CCaptureDriver()
	{
		;
	}

public:
	virtual bool bCapInit(void* pConfig) = 0;
	virtual void vCapRelease() = 0;
	virtual bool bCapEnable() = 0;
	virtual bool bCapDisable() = 0;
	virtual bool bSetCapBuffer(void** pBufPtr, int bufNum, int width, int height, int stride) = 0;
	virtual void vSetContrast(int contrast) = 0;
	virtual void vSetBrightness(int brightness) = 0;
	virtual void vSetSaturation(int saturation) = 0;
	virtual void vSetHue(int hue) = 0;

	virtual BOOLEAN bCapUpdate() = 0;
	virtual BOOLEAN bCapUpdate(Int32& bufIndex, Int32& interlaceField) = 0;
    virtual Int32   getSourceIndex() const		{return 0;}
    virtual BOOLEAN bIfCapEnabled() const		{return FALSE;}
	//!!!need be used before bCapInit
	void 			vSetCapBufferNum(int num)	{ m_iBufferNum = num;		}
	Int32 			iGetCapBufferNum()			{ return m_iBufferNum;		}

	virtual void 	checkVSYNC(BOOLEAN bFormatChk) = 0;
	ESignalState 	getVSYNC() const			{ return m_eSignalState;	}
    //add for qnx driver avtive delay too long time
    virtual BOOLEAN bIfCapActiveReady() const		{return FALSE;}
protected:
	Int32 			m_iBufferNum;
	BOOLEAN			m_bInit;
	ESignalState	m_eSignalState;
};

#endif /* CCAPTUREDRIVER_HPP_ */
