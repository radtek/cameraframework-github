//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Adas
//  @ File Name : CCameraTexture.h
//  @ Date : 2/16/2015
//  @ Author : 
//
//


#if !defined(_CCAMERATEXTURE_H)
#define _CCAMERATEXTURE_H


class CCameraTexture
{
public: //enum struct

public:
	BOOLEAN setup(UInt32 uiW, UInt32 uiH, UInt32 uiFormat);
	void 	flush();
	void 	bind();
	void 	destroy();
	void 	unbind();

private:
	UInt32	m_uiW;
	UInt32	m_uiH;
	UInt32	m_uiFormat;
	UInt32 	m_uiCameraChannelID;
	UInt32	m_uiTexNum;

	CCaptureDriver*			m_pCapDriver;
	CCaptureScreenBuffers*	m_pbufs;
	Array<screen_pixmap_t>	m_aryPixmap;
	Array<EGLImageKHR>		m_aryImageKHR;
	Array<UInt32>			m_aryTexId;

};

#endif  //_CCAMERATEXTURE_H
