
#include <iostream>
#include <memory>
#include <unistd.h>

#include "CAdasManagerGWMv2.h"
#include "MessageForQueue.h"

using namespace std;
using namespace Harman::Adas::AProject::GWMV2MH;

int main(int argc, char **argv) {
    CAdasManagerGWMv2::getInstance()->start();
    CAdasManagerGWMv2::getInstance()->pushMessage(new MessageForQueue(0, 0, string("456")));
    CAdasManagerGWMv2::getInstance()->join();

    getchar();
    return 0;
}
