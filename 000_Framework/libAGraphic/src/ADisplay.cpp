
#include <iostream>
#include <iterator>
#include <ilm/ilm_control.h>
#include <platform.h>
#include "ADisplay.h"

using namespace std;

namespace Harman 			{
namespace Adas        		{
namespace AFramework  		{
namespace AGraphic    		{

struct wl_shell_surface_listener CAdasDisplay::shellSurfaceListener = {
	handlePing,
	handleConfigure,
	handlePopupDone,
};

struct wl_registry_listener CAdasDisplay::registry_listener = {
	registry_handle_global,
	registry_handle_global_remove
};

void CAdasDisplay::handlePing(void *data, struct wl_shell_surface *shellSurface, uint32_t serial)
{
	(void)data;
	wl_shell_surface_pong(shellSurface, serial);
}

void CAdasDisplay::handleConfigure(void *data, struct wl_shell_surface *shellSurface,
				uint32_t edges, int32_t width, int32_t height)
{
	(void)data;
	(void)shellSurface;
	(void)edges;
	(void)width;
	(void)height;
}

void CAdasDisplay::handlePopupDone(void *data, struct wl_shell_surface *shellSurface)
{
	(void)data;
	(void)shellSurface;
}

void CAdasDisplay::registry_handle_global(void *data, struct wl_registry *registry,
               								   uint32_t name, const char *interface, uint32_t version)
{
    dispalyInfo *d = (dispalyInfo *)data;

    if(strcmp(interface, "wl_compositor") == 0)
	{
        d->wlCompositor = (wl_compositor*)wl_registry_bind(registry, name, &wl_compositor_interface, 1);
    }
	else if(strcmp(interface, "wl_shell") == 0)
	{
        d->wlShell = (struct wl_shell*)wl_registry_bind(registry, name, &wl_shell_interface, 1);
    }
	else if(strcmp(interface, "wl_seat") == 0)
	{
        d->wlSeat = (wl_seat*)wl_registry_bind(registry, name, &wl_seat_interface, 1);
    }
	else if(strcmp(interface, "ivi_application") == 0)
	{
        d->iviApp = (struct ivi_application*)wl_registry_bind(registry, name, &ivi_application_interface, 1);
    }
}

void CAdasDisplay::registry_handle_global_remove(void *data, struct wl_registry *registry, uint32_t name)
{
}

CAdasDisplay::CAdasDisplay()
{
	mdispalyInfo = new dispalyInfo;
	if(NULL == mdispalyInfo)
	{
#ifdef graphic_DEBUG
		ALOGE("Error: malloc display info failed\n");
#endif
		return ;
	}
	memset(mdispalyInfo, 0, sizeof(dispalyInfo));

	mGuideLine = new GuideLine();
	if(NULL == mGuideLine)
	{
#ifdef graphic_DEBUG
		ALOGE("Error: malloc GuideLine failed\n");
#endif
		return ;
	}
}

CAdasDisplay::~CAdasDisplay()
{
	if(NULL != mOpenGL)
	{
		delete mOpenGL;
		mOpenGL = NULL;
	}

	if(NULL != mEGL)
	{
		delete mEGL;
		mEGL = NULL;
	}

	if(NULL != mdispalyInfo)
	{
		delete mdispalyInfo;
		mdispalyInfo = NULL;
	}

	if(NULL != mGuideLine)
	{
		delete mGuideLine;
		mGuideLine = NULL;
	}
}

Int32 CAdasDisplay::createDisplay()
{
    mdispalyInfo->wlDisplay = wl_display_connect(NULL);

    if(NULL == mdispalyInfo->wlDisplay)
    {
#ifdef graphic_DEBUG
        ALOGE("Error: wl_display_connect failed\n");
#endif
		return -1;
    }

    mdispalyInfo->wlRegistry = wl_display_get_registry(mdispalyInfo->wlDisplay);
	if(NULL == mdispalyInfo->wlRegistry)
    {
#ifdef graphic_DEBUG
        ALOGE("Error: wl_display_get_registry failed\n");
#endif
		return -1;
    }

    wl_registry_add_listener(mdispalyInfo->wlRegistry, &registry_listener, mdispalyInfo);

	wl_display_dispatch(mdispalyInfo->wlDisplay);

    wl_display_roundtrip(mdispalyInfo->wlDisplay);

	return 0;
}

Int32 CAdasDisplay::createSurface(tsurfaceInfo surfaceInfo)
{
	UInt32 	surfaceID = surfaceInfo.surfaceId;
	emoduleType moduleType = surfaceInfo.moduleType;
	bool 	buseEGL = surfaceInfo.bActiveEGL;

	Int32 	PosX 	= surfaceInfo.viewPos.viewPos.x;
	Int32 	PosY 	= surfaceInfo.viewPos.viewPos.y;
	Int32 	Width 	= surfaceInfo.viewPos.width;
	Int32 	Height 	= surfaceInfo.viewPos.height;
	surface surfaceData;

	for(vector<surface>::iterator iter=mdispalyInfo->surfaceList.begin(); iter!=mdispalyInfo->surfaceList.end(); iter++)
	{
		if(surfaceID == iter->surfaceID)
		{
#ifdef graphic_DEBUG
			ALOGE("Error: This surface has already exist\n");
#endif
			return -1;
		}
	}

	memset(&surfaceData, 0, sizeof(surface));

	surfaceData.wlSurface = wl_compositor_create_surface(mdispalyInfo->wlCompositor);
	if(NULL == surfaceData.wlSurface)
    {
#ifdef graphic_DEBUG
        ALOGE("Error: wl_compositor_create_surface failed\n");
#endif
        destroySurface(surfaceID);
		return -1;
    }

	if(mdispalyInfo->iviApp)
	{
		surfaceData.iviSurface = ivi_application_surface_create(mdispalyInfo->iviApp, surfaceID, surfaceData.wlSurface);
	}
	else if(mdispalyInfo->wlShell)
	{
		surfaceData.wlShellSurface = wl_shell_get_shell_surface(mdispalyInfo->wlShell, surfaceData.wlSurface);
	}

	if(surfaceData.wlShellSurface)
	{
		wl_shell_surface_add_listener(
							reinterpret_cast<struct wl_shell_surface*>(surfaceData.wlShellSurface),
							&shellSurfaceListener, mdispalyInfo);
	}
	surfaceData.surfaceName = surfaceInfo.surfaceName;
	surfaceData.surfaceID = surfaceID;
	surfaceData.moduleType = moduleType;
	surfaceData.viewPos.viewPos.x = PosX;
	surfaceData.viewPos.viewPos.y = PosY;
	surfaceData.viewPos.width = Width;
	surfaceData.viewPos.height = Height;

	if(buseEGL)
	{
		CAdasEGL *pEGL = new CAdasEGL();
		if(NULL == pEGL)
		{
#ifdef graphic_DEBUG
			ALOGE("Error: malloc OpenGLES failed\n");
#endif
			delete mdispalyInfo;
			mdispalyInfo = NULL;
			return -1;
		}

		surfaceData.eglInfo = pEGL->EGLInitialize(mdispalyInfo->wlDisplay);
		if(NULL == surfaceData.eglInfo)
		{
#ifdef graphic_DEBUG
			ALOGE("Error: Initialize EGL failed\n");
#endif
			return -1;
		}


		surfaceData.wlNativeWindow = wl_egl_window_create(surfaceData.wlSurface, Width, Height);

		struct EGLInfo	*eglInfo = surfaceData.eglInfo;
#ifdef graphic_DEBUG
		ALOGI(" [%s, %d]  eglInfo = %p %p %p\n", __FUNCTION__, __LINE__, eglInfo->egl_disp, eglInfo->egl_conf, eglInfo->egl_ctx);
#endif
		surfaceData.eglInfo->egl_surf = eglCreateWindowSurface(eglInfo->egl_disp, eglInfo->egl_conf, surfaceData.wlNativeWindow, NULL);

		pEGL->EGLMakeCurrent(eglInfo);

		if(MODULE_GUIDELINE == moduleType)
		{
			if(NULL != mGuideLine)
			{
				int ret=mGuideLine->GuideLineInit();
				if (ret!=0)
				{
#ifdef graphic_DEBUG
					ALOGE("Error: GuideLineInit failed\n");
#endif
					return ret;
				}
			}
		}
		else
		{
			CAdasOpenGLES *pOpenGL = new CAdasOpenGLES(moduleType);

			if(NULL == pOpenGL)
			{
#ifdef graphic_DEBUG
				ALOGE("Error: malloc OpenGLES failed\n");
#endif
				delete pEGL;
				pEGL = NULL;

				delete mdispalyInfo;
				mdispalyInfo = NULL;

				return -1;
			}
			mOpenGLMap.insert(make_pair(surfaceID, pOpenGL));
			pOpenGL->OpenGLESInitialize(moduleType);
		}

		mEGLMap.insert(make_pair(surfaceID, pEGL));

	}

	mdispalyInfo->surfaceList.push_back(surfaceData);

	return 0;
}

Int32 CAdasDisplay::destroySurface(UInt32 surfaceID)
{
	/*if (mdispalyInfo->wlNativeWindow)
    {
        wl_egl_window_destroy(mdispalyInfo->wlNativeWindow);
    }
    if (mdispalyInfo->iviSurface)
    {
        ivi_surface_destroy(mdispalyInfo->iviSurface);
    }
    if (mdispalyInfo->wlShellSurface)
    {
        wl_shell_surface_destroy(reinterpret_cast<struct wl_shell_surface*>(mdispalyInfo->wlShellSurface));
    }
    if (mdispalyInfo->wlSurface)
    {
        wl_surface_destroy(mdispalyInfo->wlSurface);
    }
    if (mdispalyInfo->wlShell)
    {
        wl_shell_destroy(mdispalyInfo->wlShell);
    }
    if (mdispalyInfo.iviApp)
    {
        ivi_application_destroy(mdispalyInfo->iviApp);
    }
    if (mdispalyInfo->wlCompositor)
    {
        wl_compositor_destroy(mdispalyInfo->wlCompositor);
    }*/

}

Int32 CAdasDisplay::Render(trenderData renderData)
{
	UInt32 surfaceID = renderData.surfaceID;
#ifdef graphic_DEBUG
	ALOGI(" [%s, %d]  surfaceID = %d\n", __FUNCTION__, __LINE__, surfaceID);
#endif
	for(vector<surface>::iterator iter=mdispalyInfo->surfaceList.begin(); iter!=mdispalyInfo->surfaceList.end(); iter++)
	{
		if(surfaceID == iter->surfaceID)
		{
			auto itEGL = mEGLMap.find(surfaceID);
			if(itEGL != mEGLMap.end())
			{
#ifdef graphic_DEBUG
       			ALOGI("EGLMap Find, the surface ID is :%d", itEGL->first);
#endif
			}
    		else
			{
#ifdef graphic_DEBUG
       			ALOGI("EGLMap Do not Find surface ID :%d",itEGL->first);
#endif
				return -1;
			}

			itEGL->second->EGLMakeCurrent(iter->eglInfo);

			auto itOpenGL = mOpenGLMap.find(surfaceID);
			if(itOpenGL != mOpenGLMap.end())
			{
#ifdef graphic_DEBUG
       			ALOGI("GLMap Find, the surface ID is :%d" , itOpenGL->first);
#endif
			}
    		else
			{
#ifdef graphic_DEBUG
       			ALOGI("GLMap Do not Find, the surface ID is :%d" , itOpenGL->first);
#endif
				return -1;
			}

			itOpenGL->second->OpenGLESRender(renderData.bufferMap);

			mEGL->EGLSwapBuffers(iter->eglInfo);

			return 0;
		}
	}
}

Int32 CAdasDisplay::showGuideLine(UInt32 surfaceID, Float32 Angle)
{
	guidelineinfo infos;
	infos.GUIDELINE_PARA.angle = Angle;
	infos.GUIDELINE_PARA.dynamic = 1;
	infos.GUIDELINE_PARA.rearspace = 0;
	infos.GUIDELINE_PARA.wheelbase = 1.4;
	infos.GUIDELINE_PARA.vichelSpeed = 0;
	infos.GUIDELINE_PARA.forcastTime = 10;

	for(vector<surface>::iterator iter=mdispalyInfo->surfaceList.begin(); iter!=mdispalyInfo->surfaceList.end(); iter++)
	{
		if(surfaceID == iter->surfaceID)
		{
			auto itEGL = mEGLMap.find(surfaceID);
			if(itEGL != mEGLMap.end())
			{
#ifdef graphic_DEBUG
				ALOGI("Guideline surface Find, the ID is :%d\n", itEGL->first);
#endif
			}
    		else
			{
#ifdef graphic_DEBUG
       			ALOGI("Guideline surface Do not Find\n");
#endif
				return -1;
			}

			itEGL->second->EGLMakeCurrent(iter->eglInfo);

			int ret=mGuideLine->GuideLineRender(infos);
			if (ret!=0)
			{
#ifdef graphic_DEBUG
				ALOGE("GuideLineRender Failed\n");
#endif
				return ret;
			}

			mEGL->EGLSwapBuffers(iter->eglInfo);

			return 0;
		}
	}
	return 0;
}

Int32 CAdasDisplay::hideGuideLine(UInt32 surfaceID)
{
	for(vector<surface>::iterator iter=mdispalyInfo->surfaceList.begin(); iter!=mdispalyInfo->surfaceList.end(); iter++)
	{
		if(surfaceID == iter->surfaceID)
		{
			auto itEGL = mEGLMap.find(surfaceID);
			if(itEGL != mEGLMap.end())
			{
#ifdef graphic_DEBUG
				ALOGI("Guideline surface Find, the ID is :%d\n", itEGL->first);
#endif
			}
    		else
			{
#ifdef graphic_DEBUG
       			ALOGI("Guideline surface Do not Find\n");
#endif
				return -1;
			}

			itEGL->second->EGLMakeCurrent(iter->eglInfo);

			mGuideLine->GuideLineHide();

			mEGL->EGLSwapBuffers(iter->eglInfo);

			return 0;
		}
	}
	return 0;
}


}
}
}
}


