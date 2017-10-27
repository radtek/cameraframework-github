#ifndef RVC_SERVICE_STUB_IMPL_GWM_H_
#define RVC_SERVICE_STUB_IMPL_GWM_H_

#include "v0/com/harman/adas/RvcServiceStubImpl.hpp"
#include "TraceMacros.h"

using namespace std;
using namespace v0::com::harman::adas;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {

class RvcServiceStubImplGWM : public RvcServiceStubImpl
{
public:
	static RvcServiceStubImplGWM* getInstance();
	virtual ~RvcServiceStubImplGWM();

private:
	RvcServiceStubImplGWM();

private:
	static RvcServiceStubImplGWM* m_pInstance;
		
};

}
}
}
}

#endif