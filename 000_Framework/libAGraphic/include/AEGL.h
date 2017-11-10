#ifndef  AEGL_H
#define  AEGL_H
#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include "graphicType.h"

using namespace std;

//using Harman::Adas::AFramework::AGraphic::AEGLManager::CAdasEGL;

namespace Harman 		{
namespace Adas 			{
namespace AFramework 	{
namespace AGraphic 		{

struct EGLInfo
{
	EGLDisplay egl_disp;
	EGLContext egl_ctx;
	EGLConfig  egl_conf;
	EGLSurface egl_surf;
};

class CAdasEGL
{
public:

public:
    CAdasEGL();	
	virtual ~CAdasEGL();
    struct EGLInfo* EGLInitialize(VOID *display);
	VOID EGLMakeCurrent(struct EGLInfo *egl);
	void EGLSwapBuffers(struct EGLInfo *egl);

private:
	EGLDisplay egl_disp;
	EGLContext egl_ctx;
	EGLConfig  egl_conf;
private:
};

}
}
}
}

#endif  //  AEGL_H
/* EOF */


