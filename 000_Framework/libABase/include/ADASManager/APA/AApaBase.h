#ifndef  _APA_BASE_H_
#define  _APA_BASE_H_

#include "TraceMacros.h"
#include "TypeDefine.h"
#include "platformdef.h"
#include "CFunctor.h"
#include "ADASManager/ModuleBase.h"
#include "Observer.h"

using namespace Harman::Adas::AFramework::AFoundation;

namespace Harman 		{
namespace Adas 			{
namespace AFramework 	{
namespace ABase 		{
namespace ADASManager 	{

using namespace std;

class AApaBase : public ModuleBase, Observer
{
public:
	AApaBase();
	virtual ~AApaBase();

public:
	virtual a_status  initialize();
	virtual VOID       unInitialize(){};
	virtual VOID       beforeHandleMessageQueue(){};
	virtual VOID       afterHandleMessageQueue();
	virtual a_status  isModuleAvailabel();
	virtual VOID Update(Subject* subject, Int32 state);
	virtual VOID onHandle(UInt32 uiEventID, const string& pData);

private:
	// typedef CFunctorArg1<const string&> 	CFunctor;

protected:
	a_status registerFunc(UInt32 eventID, CFunctor* pFunctor);
	VOID  updateModuleState();

private:
	map<UInt32, CFunctor*> m_mMapApaFunc;
	BOOLEAN m_bApaAvailable;


};


}//ADASManager
}		//ABase
}	//AFramework
}		//Adas
}		//Harmane


#endif
