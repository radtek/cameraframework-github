#ifndef REVERSE_SIGNAL_RECEIVE_H_
#define REVERSE_SIGNAL_RECEIVE_H_

#include "AFoundation.h"

using namespace std;
using namespace Harman::Adas::AFramework::AFoundation;


namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {


class ReverseSignalReceive
{
public:
	ReverseSignalReceive();
	// static ReverseSignalReceive* getInstance();
	~ReverseSignalReceive();


	VOID start();

	VOID GPIOCALLBACK(unsigned int value);

private:
	// static ReverseSignalReceive* m_pInstance;
	EpollGPIO* m_pEGPIO;
};



}
}
}
}


#endif