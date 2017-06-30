#ifndef __GL_SHELL_H__
#define __GL_SHELL_H__
#include "GlHeaders.h"
#include <stdlib.h>
#include <stdio.h>
#include "fileloader.h"
#include "OGLES2Tools.h"
//#include "RVSDefine.h"

typedef struct tagUIVertex{
	float x;
	float y;
	float u;
	float v;
} UIVertex;

enum prefNameIntEnum
{
	prefEGLMajorVersion,	/*!< EGL: returns the major version as returned by eglInitialize() */
	prefEGLMinorVersion,	/*!< EGL: returns the minor version as returned by eglInitialize() */
	prefWidth,				/*!< Width of render target */
	prefHeight,				/*!< Height of render target */
//	prefPositionX,			/*!< X position of the window */
//	prefPositionY,			/*!< Y position of the window */
//	prefQuitAfterFrame,		/*!< Shell will quit after this number of frames (-1 to disable) */
//	prefSwapInterval,		/*!< 0 to preventing waiting for monitor vertical syncs */
//	prefInitRepeats,		/*!< Number of times to reinitialise (if >0 when app returns false from RenderScene(), shell will ReleaseView(), InitView() then re-enter RenderScene() loop). Decrements on each initialisation. */
//	prefFSAAMode,			/*!< Set to: 0 to disable full-screen anti-aliasing; 1 for 2x; 2 for 4x. */
//	prefCommandLineOptNum,	/*!< Returns the length of the array returned by prefCommandLineOpts */
//	prefColorBPP,			/*!< Allows you to specify a desired color buffer size e.g. 16, 32. */
//	prefRotateKeys,			/*!< Allows you to specify and retrieve how the keyboard input is transformed */
//	prefButtonState,		/*!< pointer button state */
//	prefCaptureFrameStart,	/*!< The frame to start capturing screenshots from */
//	prefCaptureFrameStop,   /*!< The frame to stop capturing screenshots at */
//	prefPriority,			/*!< EGL: If supported will set the egl context priority; 0 for low, 1 for med and 2 for high. */
//	prefConfig				/*!< EGL: Force the shell to use a particular EGL config. */
};

enum prefNameConstPtrEnum
{
	prefAppName,			/*!< ptrValue is char* */
	prefReadPath,			/*!< ptrValue is char*; will include a trailing slash */
	prefWritePath,			/*!< ptrValue is char*; will include a trailing slash */
	prefCommandLine,		/*!< used to retrieve the entire application command line */
	prefCommandLineOpts,	/*!< ptrValue is SCmdLineOpt*; retrieves an array of arg/value pairs (parsed from the command line) */
	prefExitMessage,		/*!< ptrValue is char*; gives the shell a message to show on exit, typically an error */
	prefVersion				/*!< ptrValue is char* */
};

class GlShellApp
{
public:
	GlShellApp();
	~GlShellApp();

	int ShellAppInit(int param1, int param2, void* pContext,void* pScreenCtx);
	virtual int Init();
	virtual int Update(int param1, int param2);
	virtual int Draw(PVRTMat4& view, PVRTMat4& proj);

	virtual bool LoadTextures(CPVRTString* pErrorStr);
	virtual bool LoadShaders(CPVRTString* pErrorStr);
	virtual bool LoadMeshes(CPVRTString* pErrorStr);

	void PVRShellSet(const prefNameConstPtrEnum prefName, const void * const ptrValue) { }
	int PVRShellGet(const prefNameIntEnum prefName);
	unsigned long PVRShellGetTime();

	virtual void OnMouseDown(int x, int y);
	virtual void OnMouseUp(int x, int y);
	virtual void OnMouseMove(int x, int y);
	virtual void OnKeyPressed(unsigned char keyCode);
	virtual void OnKeyReleased(unsigned char keyCode);
	virtual int Release();
    
    
	int			m_prevX;
	int			m_prevY;

	unsigned long			m_lastTime;
	unsigned long			m_currTime;

	//base utility
	int LoadProgramFromFile(char* vtxName, char* frgName);
	GLuint LoadShaderFromString(const char* pVtx,const char* pFrg,const char** const pszAttribs,const int i32NumAttribs);
//	GLuint LoadShaderFromBinFile(const char* pVtx,const char* pFrg,const char** const pszAttribs,const int i32NumAttribs);
	int LoadAlphaTextureFromBMP(const char* name, unsigned int* tid);
	int LoadAlphaTextureFromBMP(const char* name, unsigned int* tid, int& bmpWidth,int& bmpHeight);
	int LoadRGBTextureFromBMP(const char* name,unsigned int* tid);
	int LoadRGBATextureFromPNG(const char* name, unsigned int* tid, int& pngWidth, int& pngHeight);
	void HandleInput();
	void DrawAxisAlignedQuad(PVRTVec2 afLowerLeft, PVRTVec2 afUpperRight);
	int			m_screenWidth;
	int			m_screenHeight;
	void* 		pDisplayContext;
	void*       pScreenContext;
	unsigned int	m_typeId;

	bool bContinueDraw;
	bool IsContinue2Draw();
    void setContinueDraw(int continueDraw);
};

#endif //__GL_SHELL_H__
