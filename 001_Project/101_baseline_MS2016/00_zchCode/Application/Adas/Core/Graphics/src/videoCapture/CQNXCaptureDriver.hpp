#ifndef CQNXCAPTUREDRIVER_HPP_
#define CQNXCAPTUREDRIVER_HPP_


#include "CCaptureDriver.hpp"
#include "CaptureDriverConfig.h"
#define CAPTURE_NEED_SEQNO


class CQNXCaptureDriver : public CCaptureDriver
{
public:
	CQNXCaptureDriver();
	~CQNXCaptureDriver();

	virtual BOOLEAN bCapInit(void* pConfig);
	virtual BOOLEAN bCapInit(void** pBufPtr, int bufNum, int width, int height, int stride);
	virtual void 	vCapRelease();
	virtual BOOLEAN bSetCapBuffer(void** pBufPtr, int bufNum, int width, int height, int stride);

	virtual BOOLEAN bCapEnable();
	virtual BOOLEAN bCapDisable();
	virtual BOOLEAN bCapUpdate();
	virtual BOOLEAN bCapUpdate(int& bufIndex, int& interlaceField);
	virtual void 	checkVSYNC(BOOLEAN bFormatChk);

	virtual void vSetContrast(int contrast) 	{;}
	virtual void vSetBrightness(int brightness) {;}
	virtual void vSetSaturation(int saturation) {;}
	virtual void vSetHue(int hue) 				{;}

	Int32 iGetBufferIndex() const		{return m_iBufIndex;}
	Int32 iGetInterlaceField() const	{return m_iInterlaceField;}

	void  setSourceIndex(Int32 idx);
    Int32 getSourceIndex() const         {return m_curSourceIdx;};
    BOOLEAN bIfCapEnabled() const		     {return m_bCapEnabled;}
    BOOLEAN bIfCapActiveReady() const		     {return m_bCapActiveReady;}
    void onCapEnableTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus);
protected:
	BOOLEAN bConfigCaptureParam();

protected:
	tagQNXCaptureDriverConfig* m_pConfig;

	capture_context_t 	m_CapContext;
	int 				m_iBufIndex;
	int 				m_iPrevBufIndex;
	int 				m_iInterlaceField;

	int					m_curSourceIdx;
    BOOLEAN             m_bCapEnabled;
    BOOLEAN             m_bCapActiveReady;
	uint64_t *			frame_timestamp;
	uint32_t *			frame_flags;

#ifdef CAPTURE_NEED_SEQNO
	uint32_t *			frame_seqno;
#endif
};


#endif /* CQNXCAPTUREDRIVER_HPP_ */
