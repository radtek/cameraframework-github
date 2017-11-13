#ifndef  ADISPLAY_H
#define  ADISPLAY_H
#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

#include <map>
#include "graphicType.h"
#include "wayland-client.h"
#include "wayland-egl.h"
#include "wayland-cursor.h"
#include <ivi-application-client-protocol.h>
#include "ADisplay.h"
#include "AEGL.h"
#include "AOpenGLES.h"
#include "GuideLine.h"

using namespace std;

using namespace Harman::Adas::AFramework::AGraphic;


namespace Harman 			{
namespace Adas 				{
namespace AFramework 		{
namespace AGraphic 			{
	
//#ifdef LINUX_OS
typedef struct
{
	string					surfaceName;
	UInt32					surfaceID;
	emoduleType 			moduleType;
	struct wl_surface		*wlSurface;
	struct wl_egl_window	*wlNativeWindow;
	struct ivi_surface		*iviSurface;
	struct wl_shell_surface *wlShellSurface;
	struct EGLInfo			*eglInfo;
	//EGLSurface				eglSurface;
	viewInfo				viewPos;
}surface;

typedef struct
{
	struct wl_display		*wlDisplay;
	struct wl_registry		*wlRegistry;
	struct wl_compositor	*wlCompositor;
	//struct wl_surface 		*wlSurface;
	//struct wl_egl_window	*wlNativeWindow;
	struct wl_seat			*wlSeat;
	struct wl_pointer		*wlPointer;
	struct wl_shm			*wlShm;
	//struct wl_cursor_theme	*cursor_theme;
	//struct wl_cursor		*default_cursor;
	//struct wl_surface 		*cursor_surface;
	struct ivi_application	*iviApp;
	struct wl_shell 		*wlShell;
	//struct wl_shell_surface *wlShellSurface;
	//struct ivi_surface		*iviSurface;
	//struct EGLInfo			*eglInfo;
	vector<surface> 	surfaceList;
}dispalyInfo;

class CAdasDisplay
{
public:		

public:
	static void handlePing(void *data, struct wl_shell_surface *shellSurface, uint32_t serial);
	static void handleConfigure(void *data, struct wl_shell_surface *shellSurface, uint32_t edges, int32_t width, int32_t height);
	static void handlePopupDone(void *data, struct wl_shell_surface *shellSurface);
	static void registry_handle_global(void *data, struct wl_registry *registry, uint32_t name, const char *interface, uint32_t version);
	static void registry_handle_global_remove(void *data, struct wl_registry *registry, uint32_t name);
	//static void handle_surface_configure(void *data, struct zxdg_surface_v6 *surface, uint32_t serial);
	//static void usage(int error_code);
	
public:
	CAdasDisplay();
	virtual ~CAdasDisplay();
	
	Int32 createDisplay();
	Int32 createSurface(tsurfaceInfo surfaceInfo);
	Int32 destroySurface(UInt32 surfaceID);
	Int32 Render(trenderData renderData);
	Int32 showGuideLine(UInt32 surfaceID, Float32 Angle);
	Int32 hideGuideLine();

private:

private:
	CAdasEGL    	*mEGL;
	CAdasOpenGLES	*mOpenGL;
	dispalyInfo 	*mdispalyInfo;
	
private:
	//static int running;
	static struct wl_shell_surface_listener shellSurfaceListener;
	static struct wl_registry_listener registry_listener;
	//map<UInt32, ModuleBase*> m_mModuleMap;
	//map<string, struct wl_surface *>  mSurfaceMap;
	//map<UInt32, string>  mSurfaceMap;
	GuideLine *mGuideLine;
	map<UInt32, CAdasOpenGLES*>  mOpenGLMap;
	map<UInt32, CAdasEGL*>  	 mEGLMap;

};

}
}
}
}

#endif  //  ADISPLAY_H
/* EOF */


