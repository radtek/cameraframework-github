#include "CEGL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TRC_SCOPE_DEF(CEGL, CEGL, Initialize);
TRC_SCOPE_DEF(CEGL, CEGL, unInitialize);
TRC_SCOPE_DEF(CEGL, CEGL, update);
TRC_SCOPE_DEF(CEGL, CEGL, ChooseConfig);

CEGL* CEGL::s_pInstance = NULL;

CEGL* CEGL::getInstance()
{
	if(s_pInstance == NULL)
	{
		s_pInstance = new CEGL();
	}
	return s_pInstance;
}

void CEGL::deleteInstance()
{
	if(s_pInstance)
	{
		delete s_pInstance;
		s_pInstance = NULL;
	}
}

CEGL::CEGL()
{
	m_Context.display = NULL;
	m_Context.eglConfig = NULL;
	m_Context.eglContext = NULL;
	m_Context.eglSurface = NULL;
	m_Window = NULL;
	m_bInitialized = false;

	//set config default value;
	m_ConfigAttr.level = EGL_DONT_CARE;
	m_ConfigAttr.surface_type = EGL_WINDOW_BIT;
	m_ConfigAttr.renderable_type = EGL_OPENGL_ES2_BIT;
	m_ConfigAttr.red_size = 8;
	m_ConfigAttr.green_size = 8;
	m_ConfigAttr.blue_size = 8;
	m_ConfigAttr.alpha_size = 8;
	m_ConfigAttr.sample_buffers = EGL_DONT_CARE;//1;
	m_ConfigAttr.samples = EGL_DONT_CARE;//4;
	m_ConfigAttr.config_id = EGL_DONT_CARE;
}

CEGL::~CEGL()
{
	;
}


bool CEGL::initialize(EGLNativeWindowType window)
{
	TRC_SCOPE(CEGL, CEGL, Initialize);
	if(window == NULL)
	{
		printf("Input window for EGL init false!!!\n");
		DBG_ERROR(("Input window for EGL init false!!!\n"));
		return false;
	}

	EGLint egl_interval = 1;
	EGLint eglError;

	EGLint surfAttribList[] = {
			EGL_RENDER_BUFFER, EGL_BACK_BUFFER,
			EGL_NONE
	};

	EGLint ctxAttribList[] = {
			EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE,
	};

	if(m_bInitialized)
		return true;

	m_Window = window;


	m_Context.display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if( EGL_NO_DISPLAY == m_Context.display)
	{
		printf("eglCreateContext failed!\n");
//		DBG_ERROR(("eglCreateContext"));
		goto fail1;
	}

	if(!eglInitialize(m_Context.display, NULL, NULL))
	{
		eglError = eglGetError();
		printf("eglInitialize:%d\n",eglError);
//		DBG_ERROR(("eglInitialize:%d\n",eglError));
		goto fail2;
	}

	m_Context.eglConfig = chooseConfig();
	if(m_Context.eglConfig == 0)
	{
		printf("m_Context.eglConfig == 0!\n");
		goto fail2;
	}

	//create render surface

	m_Context.eglSurface = eglCreateWindowSurface(m_Context.display, m_Context.eglConfig, m_Window,surfAttribList);
	if( EGL_NO_SURFACE == m_Context.eglSurface)
	{
		printf("eglCreateWindowSurface failed!\n");
		switch(eglGetError())
		{
		case EGL_BAD_MATCH:
			DBG_ERROR(("eglCreateWindowSurface:EGL_BAD_MATCH!\n"));
			break;
		case EGL_BAD_CONFIG:
			DBG_ERROR(("eglCreateWindowSurface:EGL_BAD_CONFIG!\n"));
			break;
		case EGL_BAD_NATIVE_WINDOW:
			DBG_ERROR(("eglCreateWindowSurface:EGL_BAD_NATIVE_WINDOW!\n"));
			break;
		case EGL_BAD_ALLOC:
			DBG_ERROR(("eglCreateWindowSurface:EGL_BAD_ALLOC!\n"));
			break;
		}
		goto fail2;
	}

	//create egl rendering context
	m_Context.eglContext = eglCreateContext(m_Context.display, m_Context.eglConfig, EGL_NO_CONTEXT, ctxAttribList);
	if( EGL_NO_CONTEXT == m_Context.eglContext)
	{
		printf("eglCreateContext failed!\n");
		if(EGL_BAD_CONFIG == eglGetError())
		{
			DBG_ERROR(("eglCreateContext:EGL_BAD_CONFIG!\n"));
			goto fail3;
		}
	}

	//make an eglContext current
	if(!eglMakeCurrent(m_Context.display, m_Context.eglSurface, m_Context.eglSurface, m_Context.eglContext))
	{
		printf("eglMakeCurrent failed!\n");
	//	DBG_ERROR(("eglMakeCurrent!\n"));
		goto fail4;
	}

	if (eglSwapInterval(m_Context.display, egl_interval) != EGL_TRUE)
	{
		eglError = eglGetError();
		printf("eglSwapInterval error: err = %d\n",eglError);
		DBG_ERROR(("eglSwapInterval error: err = %d\n",eglError));
		goto fail5;
	}

	m_bInitialized = true;
//	printf("m_bInitialized = true!\n");
	return true;

fail5:
	if( EGL_TRUE != eglMakeCurrent(m_Context.display,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT))
	{
		DBG_ERROR(("eglMakeCurrent!\n"));
	}
fail4:
	if(EGL_TRUE == eglDestroyContext(m_Context.display,m_Context.eglContext))
	{
		m_Context.eglContext = NULL;
	}
	else
	{
		if(EGL_BAD_CONTEXT == eglGetError())
			DBG_ERROR(("eglDestroyContext: EGL_BAD_CONTEXT!\n")); // m_Context.eglContext is not a valid rendering context
		else
			DBG_ERROR(("eglDestroyContext\n"));
	}

fail3:
	if( EGL_TRUE == eglDestroySurface(m_Context.display,m_Context.eglSurface))
	{
		m_Context.eglSurface = NULL;
	}
	else
	{
		if(EGL_BAD_SURFACE == eglGetError())
			DBG_ERROR(("eglDestroySurface:EGL_BAD_SURFACE!\n"));
		else
			DBG_ERROR(("eglDestroySurface!\n"));
	}

fail2:
	//release resources associated with use of EGL and OpenGLES on a display
	if(EGL_TRUE == eglTerminate(m_Context.display))
	{
		m_Context.display = NULL;
	}
	else
	{
		if(EGL_BAD_DISPLAY == eglGetError())
			DBG_ERROR(("eglTerminate:EGL_BAD_DISPLAY!\n"));
		else
			DBG_ERROR(("eglTerminate!\n"));
	}

fail1:
	if(EGL_TRUE != eglReleaseThread())
	{
		DBG_ERROR(("eglReleaseThread!\n"));
	}
	return false;
}

bool CEGL::unInitialize()
{
	TRC_SCOPE(CEGL, CEGL, unInitialize);

	if(!m_bInitialized)
		return true;

	if( EGL_TRUE != eglMakeCurrent(m_Context.display,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT))
	{
		DBG_ERROR(("eglMakeCurrent!\n"));
	}

	if(EGL_TRUE == eglDestroyContext(m_Context.display,m_Context.eglContext))
	{
		m_Context.eglContext = NULL;
	}
	else
	{
		if(EGL_BAD_CONTEXT == eglGetError())
			DBG_ERROR(("eglDestroyContext: EGL_BAD_CONTEXT!\n")); // m_Context.eglContext is not a valid rendering context
		else
			DBG_ERROR(("eglDestroyContext\n"));
	}

	if( EGL_TRUE == eglDestroySurface(m_Context.display,m_Context.eglSurface))
	{
		m_Context.eglSurface = NULL;
	}
	else
	{
		if(EGL_BAD_SURFACE == eglGetError())
			DBG_ERROR(("eglDestroySurface:EGL_BAD_SURFACE!\n"));
		else
			DBG_ERROR(("eglDestroySurface!\n"));
	}

	//release resources associated with use of EGL and OpenGLES on a display
	if(EGL_TRUE == eglTerminate(m_Context.display))
	{
		m_Context.display = NULL;
	}
	else
	{
		if(EGL_BAD_DISPLAY == eglGetError())
			DBG_ERROR(("eglTerminate:EGL_BAD_DISPLAY!\n"));
		else
			DBG_ERROR(("eglTerminate!\n"));
	}

	if(EGL_TRUE != eglReleaseThread())
	{
		DBG_ERROR(("eglReleaseThread!\n"));
	}
	m_Window = NULL;
	m_bInitialized = false;
	return true;
}

bool CEGL::update()
{
	if(EGL_TRUE !=eglSwapBuffers(m_Context.display, m_Context.eglSurface))
	{
        TRC_SCOPE(CEGL, CEGL, update);
		DBG_ERROR(("eglSwapBuffers:%d!\n", eglGetError()));
		return false;
	}
	return true;
}

EGLConfig CEGL::chooseConfig()
{
	TRC_SCOPE(CEGL, CEGL, ChooseConfig);

	EGLConfig egl_conf = (EGLConfig)0;
	EGLint err;

	EGLint iNumConfigs = 0;
	if (eglGetConfigs(m_Context.display, NULL, 0, &iNumConfigs) != EGL_TRUE || iNumConfigs == 0)
	{
		err = eglGetError();
		printf("eglGetConfigs error: err = %d, iNumConfigs=%d\n",err,iNumConfigs);
		DBG_ERROR(("eglGetConfigs error: err = %d, iNumConfigs=%d\n",err,iNumConfigs));
		return egl_conf;
	}

	EGLConfig *egl_configs = new EGLConfig [iNumConfigs];
	if (egl_configs == NULL)
	{
		printf("egl_configs == NULL!\n");
		DBG_ERROR(("egl_configs malloc resources failed!\n"));
		return egl_conf;
	}

	if (eglGetConfigs(m_Context.display, egl_configs, iNumConfigs, &iNumConfigs) != EGL_TRUE)
	{
		err = eglGetError();
		printf("eglGetConfigs error: err = %d\n",err);
		DBG_ERROR(("eglGetConfigs error: err = %d\n",err));
		delete [] egl_configs;
		return egl_conf;
	}

	/*
	Now we just have to go through the list of configs and find one that
	has all the attributes we are looking for. Some attributes like the
	surface type or the renderable type are masks. All the others are just
	integers that we need to match unless we don't care about the value.
	*/
	EGLint iVal;

	for (EGLint i = 0; i < iNumConfigs; i++)
	{
		if (m_ConfigAttr.config_id != EGL_DONT_CARE)
		{
			eglGetConfigAttrib(m_Context.display, egl_configs[i], EGL_CONFIG_ID, &iVal);
			if (iVal == m_ConfigAttr.config_id)
			{
				egl_conf = egl_configs[i];
				break;
			}
			else
			{
				continue;
			}
		}

		eglGetConfigAttrib(m_Context.display, egl_configs[i], EGL_SURFACE_TYPE, &iVal);
		if (!(iVal & m_ConfigAttr.surface_type))
		{
//			printf("[%d],ival=%d != m_ConfigAttr.surface_type\n",i,iVal);
			continue;
		}

		eglGetConfigAttrib(m_Context.display, egl_configs[i], EGL_RENDERABLE_TYPE, &iVal);
		if (!(iVal & m_ConfigAttr.renderable_type))
		{
//			printf("[%d],ival=%d != m_ConfigAttr.renderable_type\n",i,iVal);
			continue;
		}

		eglGetConfigAttrib(m_Context.display, egl_configs[i], EGL_DEPTH_SIZE, &iVal);
		if (iVal == 0)
		{
//			printf("[%d],EGL_DEPTH_SIZE=0\n",i);
			continue;
		}

		if (m_ConfigAttr.level != EGL_DONT_CARE)
		{
			eglGetConfigAttrib(m_Context.display, egl_configs[i], EGL_LEVEL, &iVal);
			if (iVal != m_ConfigAttr.level)
			{
//				printf("[%d],ival=%d != m_ConfigAttr.level\n",i,iVal);
				continue;
			}
		}

		if (m_ConfigAttr.red_size != EGL_DONT_CARE)
		{
			eglGetConfigAttrib(m_Context.display, egl_configs[i], EGL_RED_SIZE, &iVal);
			if (iVal != m_ConfigAttr.red_size)
			{
//				printf("[%d],ival=%d != m_ConfigAttr.red\n",i,iVal);
				continue;
			}
		}

		if (m_ConfigAttr.green_size != EGL_DONT_CARE)
		{
			eglGetConfigAttrib(m_Context.display, egl_configs[i], EGL_GREEN_SIZE, &iVal);
			if (iVal != m_ConfigAttr.green_size)
			{
//				printf("[%d],ival=%d != m_ConfigAttr.green\n",i,iVal);
				continue;
			}
		}

		if (m_ConfigAttr.blue_size != EGL_DONT_CARE)
		{
			eglGetConfigAttrib(m_Context.display, egl_configs[i], EGL_BLUE_SIZE, &iVal);
			if (iVal != m_ConfigAttr.blue_size)
			{
//				printf("[%d],ival=%d != m_ConfigAttr.blue\n",i,iVal);
				continue;
			}
		}

		if (m_ConfigAttr.alpha_size != EGL_DONT_CARE)
		{
			eglGetConfigAttrib(m_Context.display, egl_configs[i], EGL_ALPHA_SIZE, &iVal);
			if (iVal != m_ConfigAttr.alpha_size)
			{
//				printf("[%d],ival=%d != m_ConfigAttr.alpha\n",i,iVal);
				continue;
			}
		}

		if (m_ConfigAttr.sample_buffers != EGL_DONT_CARE)
		{
			eglGetConfigAttrib(m_Context.display, egl_configs[i], EGL_SAMPLE_BUFFERS, &iVal);
			if (iVal != m_ConfigAttr.sample_buffers)
			{
//				printf("[%d],ival=%d != m_ConfigAttr.sample_buffers\n",i,iVal);
				continue;
			}
		}

		if (m_ConfigAttr.samples != EGL_DONT_CARE)
		{
			eglGetConfigAttrib(m_Context.display, egl_configs[i], EGL_SAMPLES, &iVal);
			if (iVal != m_ConfigAttr.samples)
			{
//				printf("[%d],ival=%d != m_ConfigAttr.samples\n",i,iVal);
				continue;
			}
		}

		egl_conf = egl_configs[i];
		//printf("egl_conf id = %d\n",i);
		break;
	}

//	egl_conf = egl_configs[24];
	delete [] egl_configs;

	if (egl_conf != (EGLConfig)0)
	{
		if (m_ConfigAttr.level == EGL_DONT_CARE)
		{
			eglGetConfigAttrib(m_Context.display, egl_conf, EGL_LEVEL, &iVal);
			m_ConfigAttr.level = iVal;
		}
	}

	return egl_conf;
}

void CEGL::setConfigAttrib(eEglConfAttribute attrib, EGLint value)
{
	if(m_bInitialized)
		return;
	switch(attrib)
	{
	case eLevel:
		m_ConfigAttr.level = value;
		break;
	case eSurfaceType:
		m_ConfigAttr.surface_type = value;
		break;
	case eRenderableType:
		m_ConfigAttr.renderable_type = value;
		break;
	case eRedSize:
		m_ConfigAttr.red_size = value;
		break;
	case eGreenSize:
		m_ConfigAttr.green_size = value;
		break;
	case eBlueSize:
		m_ConfigAttr.blue_size = value;
		break;
	case eAlpahSize:
		m_ConfigAttr.alpha_size = value;
		break;
	case eSampleBuffers:
		m_ConfigAttr.sample_buffers = value;
		break;
	case eSamples:
		m_ConfigAttr.samples = value;
		break;
	case eConfigID:
		m_ConfigAttr.config_id = value;
		break;
	default:
		break;
	}
}
