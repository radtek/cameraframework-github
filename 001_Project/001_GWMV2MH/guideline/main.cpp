#include <iostream>
#include <unistd.h> 
#include "AGraphic.h"

using namespace std;



int main()
{
    cout<<"GuideLine Test"<<endl;

    cout << endl;
    cout << endl;
    cout << endl;

    CAdasGraphic *graphicptr=new CAdasGraphic();
    tsurfaceInfo surfaceInfo;
     tsurfaceList surfaceArry;
    surfaceInfo.surfaceName = "GuideLine";
    surfaceInfo.surfaceId = 51;
    surfaceInfo.moduleType = MODULE_GUIDELINE;
    surfaceInfo.bActiveEGL = TRUE;
    surfaceInfo.viewPos.width = 1280;//width;
    surfaceInfo.viewPos.height = 720;//height;
    surfaceInfo.viewPos.viewPos.x = 0;
    surfaceInfo.viewPos.viewPos.y = 0;
    surfaceArry.push_back(surfaceInfo);
    
    graphicptr->createSurface(surfaceArry);

     while(1)
    {
        graphicptr->showGuideLine(51,10);
        sleep(1);
        graphicptr->hideGuideLine();
        sleep(1);
        graphicptr->showGuideLine(51,0);
        sleep(1);
        graphicptr->hideGuideLine();
        sleep(1);
        graphicptr->showGuideLine(51,-10);
        sleep(1);
        graphicptr->hideGuideLine();
        sleep(1);
    }

   

    //main thread wait here
    getchar();

    if(graphicptr != nullptr) {
        delete graphicptr;
        graphicptr = nullptr;
    }

    return 0;
}