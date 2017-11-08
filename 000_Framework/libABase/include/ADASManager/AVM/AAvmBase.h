#ifndef  A_AVM_BASE_H_
#define A_AVM_BASE_H_

#include "TraceMacros.h"
#include "TypeDefine.h"
#include "platformdef.h"
#include "CFunctor.h"
#include "ADASManager/ModuleBase.h"
#include "Observer.h"

using namespace std;
using namespace Harman::Adas::AFramework::AFoundation;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {


class CAvmBase : public ModuleBase
                            , Observer
{

public:
	
	CAvmBase();
	virtual ~CAvmBase();

	virtual a_status	initialize();
	virtual VOID		unInitialize(){};
	virtual VOID		beforeHandleMessageQueue(){};
	virtual VOID		afterHandleMessageQueue();
	virtual a_status	isModuleAvailabel();
	virtual VOID		Update(Subject* subject, Int32 state);
	virtual VOID		onHandle(UInt32 uiEventID, const string& pData);	 

protected:
	a_status registerFunc(UInt32 eventID, CFunctor* pFunctor);
	VOID  updateModuleState();
	
private:
	map<UInt32, CFunctor*> m_mMapAvmFunc;

};


}//ADASManager
}//ABase
}//AFramework
}//Adas
}//Harmane


#endif/*define A_AVM_BASE_H_*/