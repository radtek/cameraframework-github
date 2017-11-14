#ifndef  AGRAPHIC_H
#define  AGRAPHIC_H
#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

#include "graphicType.h"

#include "ADisplay.h"

using namespace std;

using namespace Harman::Adas::AFramework::AGraphic;


namespace Harman 			{
namespace Adas 				{
namespace AFramework 		{
namespace AGraphic 			{


typedef vector<tsurfaceInfo> tsurfaceList;

class CAdasGraphic
{		
public:
	CAdasGraphic();
	virtual ~CAdasGraphic();
	
    Int32 createSurface(tsurfaceList surfaceInfoList);
	Int32 destroySurface(UInt32 surfaceID);
	Int32 Render(trenderData renderData);
	Int32 showGuideLine(UInt32 surfaceID, Float32 Angle);
	Int32 hideGuideLine();

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


