#include <iostream>
#include <memory>
#include <unistd.h>
#include "CAdasManagerGWMv2.h"
#include "MessageForQueue.h"

/*
#include "RVCGWMv2.h"
#include "SVCGWMv2.h"
#include "CamHubGWMv2.h"
#include "AVCGWMv2.h"
*/
using namespace std;
using namespace Harman::Adas::AProject::GWMV2MH;

int main()
{
    CAdasManagerGWMv2::getInstance()->start();
    CAdasManagerGWMv2::getInstance()->pushMessage(new MessageForQueue(0,0, string("456")));
    CAdasManagerGWMv2::getInstance()->join();
   	
   // getchar();

    return 0;
}

