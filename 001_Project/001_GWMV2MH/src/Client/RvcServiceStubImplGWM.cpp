#include "RvcServiceStubImplGWM.h"

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {


RvcServiceStubImplGWM* RvcServiceStubImplGWM::m_pInstance = NULL;

RvcServiceStubImplGWM::RvcServiceStubImplGWM()
{

}

RvcServiceStubImplGWM::~RvcServiceStubImplGWM()
{

}


RvcServiceStubImplGWM* RvcServiceStubImplGWM::getInstance()
{
	if(NULL == m_pInstance)
	{
		m_pInstance = new RvcServiceStubImplGWM();
	}

	return m_pInstance;
}









}
}
}
}