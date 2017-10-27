#include "ReverseSignalReceive.h"
#include "CAdasManagerGWMv2.h"
#include "AdasModuleCtrlImpl.h"
#include "RvcMsgQDefine.h"
#include "RvcServiceStubImplGWM.h"
#include "v0/com/harman/adas/RVCBaseType.hpp"
#include "TraceMacros.h"

using namespace Harman::Adas::AFramework::AFoundation;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {


//ReverseSignalReceive* ReverseSignalReceive::m_pInstance = NULL;

ReverseSignalReceive::ReverseSignalReceive()
{
	m_pEGPIO = new EpollGPIO(string("epoll gpio"), REVERSE_GEAR_GPIO_NUM, 
			makeFunctor(this, &ReverseSignalReceive::GPIOCALLBACK));

	m_pEGPIO->start();
}

ReverseSignalReceive::~ReverseSignalReceive()
{

}


VOID ReverseSignalReceive::GPIOCALLBACK(unsigned int value)
{
	if(REVERSE_GEAR_COME_ON == value)
	{
		ALOGI("ReverseSignalReceive : GPIO = %u, ON\n", value);
		CAdasManagerGWMv2::getInstance()->pushMessage(new MessageForQueue(
			AdasModuleCtrlImpl::eModuleType_RVC,
			eCameraActivate_ON,
			"456"));

		RvcServiceStubImplGWM::getInstance()->setRvcStateAttribute(
			::v0::com::harman::adas::RVCBaseType::enRvcState::e_RVC_ON
			);
	}
	else if(REVERSE_GEAR_HAS_GONE == value)
	{
		ALOGI("ReverseSignalReceive : GPIO = %u, OFF\n", value);
		CAdasManagerGWMv2::getInstance()->pushMessage(new MessageForQueue(
			AdasModuleCtrlImpl::eModuleType_RVC,
			eCameraActivate_OFF,
			"789"));

		RvcServiceStubImplGWM::getInstance()->setRvcStateAttribute(
			::v0::com::harman::adas::RVCBaseType::enRvcState::e_RVC_OFF
			);
	}
}






}
}
}
}