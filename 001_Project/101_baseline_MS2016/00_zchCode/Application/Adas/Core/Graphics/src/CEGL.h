#ifndef CEGL_HPP_
#define CEGL_HPP_

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "foundation.h"

typedef enum{
		eLevel,
		eSurfaceType,
		eRenderableType,
		eRedSize,
		eGreenSize,
		eBlueSize,
		eAlpahSize,
		eSampleBuffers,
		eSamples,
		eConfigID,
		eConfigAttribNum,
	}eEglConfAttribute;

typedef struct _egl_conf_attr_t
	{
		EGLint level;
		EGLint surface_type;
		EGLint renderable_type;
		EGLint red_size;
		EGLint green_size;
		EGLint blue_size;
		EGLint alpha_size;
		EGLint sample_buffers;
		EGLint samples;
		EGLint config_id;
	}stEglConfAttr;

class CEGL{

public:
	struct stEglContext{
		EGLDisplay display;
		EGLConfig eglConfig;
		EGLSurface eglSurface;
		EGLContext eglContext;
	};
	static CEGL*	getInstance();
	static void		deleteInstance();

	//if use, need to be called before initialize, or using the default value;
	void setConfigAttrib(eEglConfAttribute attrib, EGLint value);


	bool initialize(EGLNativeWindowType window);
	bool unInitialize();
	bool update();

	PFNEGLCREATEIMAGEKHRPROC getFnEGLCreateImageKHRFun()
	{
		return (PFNEGLCREATEIMAGEKHRPROC)eglGetProcAddress("eglCreateImageKHR");
	}

	PFNGLEGLIMAGETARGETTEXTURE2DOESPROC getFnEGLImageTargetTexture2DOES()
	{
		return (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)eglGetProcAddress("glEGLImageTargetTexture2DOES");
	}

private:
	EGLConfig chooseConfig();

protected:
	CEGL();
	~CEGL();

private:
	static CEGL* s_pInstance;

	stEglContext m_Context;
	stEglConfAttr m_ConfigAttr;
	EGLNativeWindowType m_Window;
	bool m_bInitialized;
};


#endif /* CEGL_HPP_ */
