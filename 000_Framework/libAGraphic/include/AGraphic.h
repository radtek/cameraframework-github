#ifndef  AGRAPHIC_H
#define  AGRAPHIC_H
#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

#include "TypeDefine.h"
//#include "wayland-client.h"
//#include "wayland-egl.h"
//#include "wayland-cursor.h"
//#include <xdg-shell-unstable-v6-client-protocol.h>
//#include <ivi-application-client-protocol.h>
#include "ADisplay.h"

using namespace std;

using namespace Harman::Adas::AFramework::AGraphic;
//using Harman::Adas::AFramework::AGraphic::CAdasOpenGLES;
//using namespace Harman::Adas::AFramework::AGraphic::CAdasDisplay;

namespace Harman 			{
namespace Adas 				{
namespace AFramework 		{
namespace AGraphic 			{

/*typedef struct
{
	string					surfaceName;
	UInt32					surfaceId;
	bool					bActiveEGL;
	//EGLSurface			  egl_surf;
	viewInfo				viewPos;
}tsurfaceInfo;*/
typedef vector<tsurfaceInfo> tsurfaceList;

class CAdasGraphic
{		
public:
	CAdasGraphic();
	virtual ~CAdasGraphic();
	
    Int32 createSurface(tsurfaceList surfaceInfoList);
	Int32 destroySurface(UInt32 surfaceID);
	Int32 Render(trenderData renderData);
	//VOID update(const CHAR *buf);

private:

private:
	CAdasDisplay *mDisplay;
	
private:
	//map<UInt32, ModuleBase*> m_mModuleMap;
	//map<string, struct wl_surface *>  mSurfaceMap;
	//map<UInt32, string>  mSurfaceMap;

};

}
}
}
}

#endif  //  AGRAPHIC_H
/* EOF */


