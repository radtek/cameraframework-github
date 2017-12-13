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

	if(EGL_NO_DISPLAY == egl_disp)
	{
#ifdef graphic_DEBUG
        ALOGE("eglGetDisplay");
#endif
        goto fail;
    }

	ret = eglInitialize(egl_disp, &major, &minor);
	if(EGL_TRUE != ret)
	{
#ifdef graphic_DEBUG
    	ALOGE("eglInitialize");
#endif
    	goto fail;
    }

	ret = eglBindAPI(EGL_OPENGL_ES_API);
	if(EGL_TRUE != ret)
	{
#ifdef graphic_DEBUG
		ALOGE("eglBindAPI");
#endif
		goto fail;
	}

	ret = eglChooseConfig(egl_disp, config_attribsex, &egl_conf, 1, &n);
	if((EGL_TRUE != ret) && (n < 1))
	{
#ifdef graphic_DEBUG
		ALOGE("eglChooseConfig");
#endif
		goto fail;
	}

	egl_ctx = eglCreateContext(egl_disp, egl_conf, EGL_NO_CONTEXT, context_attribs);

	if(EGL_NO_CONTEXT == egl_ctx)
	{
#ifdef graphic_DEBUG
        ALOGE("eglCreateContext");
#endif
        goto fail;
    }

	egl->egl_disp = egl_disp;
	egl->egl_ctx  = egl_ctx;
	egl->egl_conf = egl_conf;

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
#ifdef graphic_DEBUG
        ALOGE("eglMakeCurrent");
#endif
    }
}

void CAdasEGL::EGLSwapBuffers(struct EGLInfo *egl)
{
	EGLBoolean 	ret;

	if(NULL == egl)
	{
		return ;
	}

	ret = eglSwapBuffers(egl->egl_disp, egl->egl_surf);
    if(EGL_TRUE != ret)
	{
#ifdef graphic_DEBUG
        ALOGE("eglSwapBuffers");
#endif
    }
}


}
}
}
}


