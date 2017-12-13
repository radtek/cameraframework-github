#include "AGraphic.h"


namespace Harman 			{
namespace Adas        		{
namespace AFramework  		{
namespace AGraphic    		{

CAdasGraphic::CAdasGraphic()
{
	Int32 ret = -1;
	mDisplay = new CAdasDisplay();
	if(NULL == mDisplay)
	{
#ifdef graphic_DEBUG
		ALOGE("Error: malloc CAdasDisplay class space failed\n");
#endif
		return ;
	}

	ret = mDisplay->createDisplay();
	if(-1 == ret)
	{
#ifdef graphic_DEBUG
		ALOGE("Error: createDisplay failed\n");
#endif
		return ;
	}
}

CAdasGraphic::~CAdasGraphic()
{
	if(NULL != mDisplay)
	{
		delete mDisplay;
		mDisplay = NULL;
	}
}

Int32 CAdasGraphic::createSurface(tsurfaceList surfaceInfoList)
{
	Int32 ret = -1;
	for(auto surfaceInfo : surfaceInfoList)
    {
#ifdef graphic_DEBUG
    	ALOGI("name: %s\n",surfaceInfo.surfaceName.c_str());
    	ALOGI("ID: %d\n",surfaceInfo.surfaceId);
    	ALOGI("Type:%d\n",surfaceInfo.moduleType);
    	ALOGI("EGL :%d\n" , surfaceInfo.bActiveEGL);
    	ALOGI("Pos :%d,%d\n",surfaceInfo.viewPos.viewPos.x,surfaceInfo.viewPos.viewPos.y);
    	ALOGI("Size: %d,%d\n",surfaceInfo.viewPos.width, surfaceInfo.viewPos.height);
#endif
    	ret = mDisplay->createSurface(surfaceInfo);
		if(-1 == ret)
		{
#ifdef graphic_DEBUG
			ALOGE("Error: createSurface failed\n");
#endif
			return -1;
		}
	}

	return 0;
}

Int32 CAdasGraphic::destroySurface(UInt32 surfaceID)
{
	return 0;
}

Int32 CAdasGraphic::Render(trenderData renderData)
{
	mDisplay->Render(renderData);

	return 0;
}

Int32 CAdasGraphic::showGuideLine(UInt32 surfaceID, Float32 Angle)
{
	mDisplay->showGuideLine(surfaceID, Angle);

	return 0;
}

Int32 CAdasGraphic::hideGuideLine(UInt32 surfaceID)
{
	mDisplay->hideGuideLine(surfaceID);

	return 0;
}



}
}
}
}



