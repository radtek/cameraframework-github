

#include "AGraphic.h"

//using Harman::Adas::AFramework::AGraphic::AEGLManager;
//using Harman::Adas::AFramework::AGraphic::AOpenGLESManager;
//using namespace Harman::Adas::AFramework::AGraphic::CAdasDisplay;


namespace Harman 			{
namespace Adas        		{
namespace AFramework  		{
namespace AGraphic    		{

CAdasGraphic::CAdasGraphic()
//: buseEGL(bActiveEGL)
{
	Int32 ret = -1;	
	mDisplay = new CAdasDisplay();
	if(NULL == mDisplay)
	{
		cout<<"Error: malloc CAdasDisplay class space failed.\n";
		return ;
	}

	ret = mDisplay->createDisplay();
	if(-1 == ret)
	{
		cout<<"Error: createDisplay failed.\n";
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
    	cout << "name: 	" << surfaceInfo.surfaceName << std::endl;
    	cout << "ID  : 	" << surfaceInfo.surfaceId << std::endl;
    	cout << "Type: 	" << surfaceInfo.moduleType << std::endl;
    	cout << "EGL : 	" << surfaceInfo.bActiveEGL << std::endl;
    	cout << "Pos : 	" << surfaceInfo.viewPos.viewPos.x << ", " << surfaceInfo.viewPos.viewPos.y << std::endl;
    	cout << "Size: 	" << surfaceInfo.viewPos.width << ", " << surfaceInfo.viewPos.height << std::endl;
    	ret = mDisplay->createSurface(surfaceInfo);
		if(-1 == ret)
		{
			cout<<"Error: createSurface failed.\n";
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

/* EOF */

