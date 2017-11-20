#include <config.h>
#include <platform.h>
#include "AEGL.h"

namespace Harman 			{
namespace Adas        		{
namespace AFramework  		{
namespace AGraphic    		{


CAdasEGL::CAdasEGL()
{
}

CAdasEGL::~CAdasEGL()
{
}

struct EGLInfo* CAdasEGL::EGLInitialize(VOID *display)
{
	struct EGLInfo *egl = NULL;
	EGLint rval = EGL_TRUE;
	static const struct 
	{
		char *extension, *entrypoint;
	}swap_damage_ext_to_entrypoint[] = {
		{
			.extension = "EGL_EXT_swap_buffers_with_damage",
			.entrypoint = "eglSwapBuffersWithDamageEXT",
		},
		{
			.extension = "EGL_KHR_swap_buffers_with_damage",
			.entrypoint = "eglSwapBuffersWithDamageKHR",
		},
	};
	
	static const EGLint context_attribs[] = {
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	const char *extensions;

	EGLint config_attribs[] = {
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_RED_SIZE, 1,
		EGL_GREEN_SIZE, 1,
		EGL_BLUE_SIZE, 1,
		EGL_ALPHA_SIZE, 1,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_NONE
	};

	EGLint config_attribsex[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_RED_SIZE,   8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE,  8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_STENCIL_SIZE, 8,
        EGL_SAMPLE_BUFFERS, 1,
        EGL_SAMPLES, 2,
        EGL_NONE };

	EGLint major, minor, n, count, i, size;
	EGLBoolean 	ret;
	EGLDisplay 	egl_disp;
	EGLContext 	egl_ctx;
	EGLConfig 	egl_conf;
	EGLConfig 	*configs;

	egl = new EGLInfo;
	if(NULL == egl)
	{
		return egl;
	}
	
	egl_disp = weston_platform_get_egl_display(EGL_PLATFORM_WAYLAND_KHR, (void *)display, NULL);
	//egl_disp = eglGetDisplay((EGLNativeDisplayType)display);
	if(EGL_NO_DISPLAY == egl_disp) 
	{
        perror("eglGetDisplay");
        //rval = EGL_FALSE;
        goto fail;
    }

	ret = eglInitialize(egl_disp, &major, &minor);
	if(EGL_TRUE != ret)
	{
    	perror("eglInitialize");
    	//rval = EGL_FALSE;
    	goto fail;
    }

	ret = eglBindAPI(EGL_OPENGL_ES_API);
	if(EGL_TRUE != ret)
	{
		perror("eglBindAPI");
		//rval = EGL_FALSE;
		goto fail;
	}

#if 0
	if(!eglGetConfigs(egl_disp, NULL, 0, &count) || count < 1)
	{
		perror("eglGetConfigs");
		//rval = EGL_FALSE;
		goto fail;
	}

	configs = (EGLConfig *)calloc(count, sizeof *configs);
	if(NULL == configs)
	{
		perror("calloc memory fail!");
		//rval = EGL_FALSE;
		goto fail;
	}

	ret = eglChooseConfig(egl_disp, config_attribs, configs, count, &n);
	if((EGL_TRUE != ret) && (n < 1))
	{
		perror("eglChooseConfig");
		//rval = EGL_FALSE;
		goto fail;
	}
	printf(" [%s, %d]  n = %d\n", __FUNCTION__, __LINE__, n);

	for (i = 0; i < n; i++) 
	{
		eglGetConfigAttrib(egl_disp, configs[i], EGL_BUFFER_SIZE, &size);
		printf(" [%s, %d]  size = %d\n", __FUNCTION__, __LINE__, size);
	}
	free(configs);
	if(NULL == egl_conf) 
	{
		fprintf(stderr, "did not find config with buffer size %d\n", size);
		//rval = EGL_FALSE;
		goto fail;
	}
#else
	ret = eglChooseConfig(egl_disp, config_attribsex, &egl_conf, 1, &n);
	if((EGL_TRUE != ret) && (n < 1))
	{
		perror("eglChooseConfig");
		//rval = EGL_FALSE;
		goto fail;
	}
#endif
	egl_ctx = eglCreateContext(egl_disp, egl_conf, EGL_NO_CONTEXT, context_attribs);
	if(EGL_NO_CONTEXT == egl_ctx) 
	{
        perror("eglCreateContext");
        //rval = EGL_FALSE;
        goto fail;
    }
	
//fail5:	eglMakeCurrent(egl_disp, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
//fail4:	eglDestroySurface(egl_disp, egl_surf);
//fail3:	eglDestroyContext(egl_disp, egl_ctx);
//fail2:	eglTerminate(egl_disp);
//fail1:	eglReleaseThread();

	egl->egl_disp = egl_disp;
	egl->egl_ctx  = egl_ctx;
	egl->egl_conf = egl_conf;
	//printf(" [%s, %d]  eglInfo = %p %p %p\n", __FUNCTION__, __LINE__, egl_disp, egl_conf, egl_ctx);
	
	//glClear(GL_COLOR_BUFFER_BIT);
	//eglMakeCurrent(egl_disp, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	//eglTerminate(egl_disp);
	return egl;

fail:  	
	delete egl;
    egl = NULL;
	return egl;
}

void CAdasEGL::EGLMakeCurrent(struct EGLInfo *egl)
{
	EGLBoolean 	ret;

	if(NULL == egl)
	{
		return ;
	}
	
    ret = eglMakeCurrent(egl->egl_disp, egl->egl_surf, egl->egl_surf, egl->egl_ctx);
    if(EGL_TRUE != ret) 
	{
        perror("eglMakeCurrent");
    }
}

void CAdasEGL::EGLSwapBuffers(struct EGLInfo *egl)
{
	EGLBoolean 	ret;

	if(NULL == egl)
	{
		return ;
	}
	
	printf(" [%s, %d]  %p, %p\n", __FUNCTION__, __LINE__, egl->egl_disp, egl->egl_surf);
	ret = eglSwapBuffers(egl->egl_disp, egl->egl_surf);
    if(EGL_TRUE != ret) 
	{
        perror("eglSwapBuffers");
    }
}


}
}
}
}

/* EOF */

