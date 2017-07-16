#include <iostream>
#include <memory>
#include <unistd.h>
#include "FWTester.h"

using namespace std;
using namespace Harman::Adas::AFramework::FWTester;

int main()
{
    FWTester::getInstance()->start();
    //FWTester::getInstance()->pushMessage(new MessageForQueue(0,0, string("456")));
    FWTester::getInstance()->join();
   	
   // getchar();

    return 0;
}

