#ifndef  A_AVM_BASE_H_
#define A_AVM_BASE_H_

#include "TraceMacros.h"
#include "TypeDefine.h"
#include "platformdef.h"
#include "CFunctor.h"
#include "ADASManager/ModuleBase.h"
#include "Observer.h"
#include "ADASManager/Camera/FrontCamera.h"
#include "ADASManager/Camera/ReserveCamera.h"
#include "ADASManager/Camera/LeftCamera.h"
#include "ADASManager/Camera/RightCamera.h"
#include "ADASManager/Camera/CameraHub.h"
using namespace std;
using namespace Harman::Adas::AFramework::AFoundation;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {


enum eMessageType
{
	eMessageType_SwitchAVM,
	eMessageType_SwitchAVMView,
	eMessageType_SwitchGuideLine,
	eMessageType_SwitchCTA,
	eMessageType_UNKNOWN = 0x70000000
};


class CAvmBase : public ModuleBase
                            , Observer
{
public:
	CAvmBase();
	virtual ~CAvmBase();

public:
	virtual a_status	initialize();
	virtual VOID		unInitialize(){};
	virtual VOID		beforeHandleMessageQueue(){};
	virtual VOID		afterHandleMessageQueue();
	virtual a_status	isModuleAvailabel();
	virtual VOID		Update(Subject* subject, Int32 state);
	virtual VOID		onHandle(UInt32 uiEventID, const string& pData);

	//typedef CFunctorArg1<const string&>	CFunctor;
	
private:
	 

protected:
	a_status registerFunc(UInt32 eventID, CFunctor* pFunctor);
	VOID  SwitchAVM(const string& AVMMode);
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