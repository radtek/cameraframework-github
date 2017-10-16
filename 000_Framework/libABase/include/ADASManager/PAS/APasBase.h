
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_APASBASE_H_
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_APASBASE_H_

#include "TraceMacros.h"
#include "TypeDefine.h"
#include "platformdef.h"
#include "CFunctor.h"
#include "Observer.h"
#include "ADASManager/ModuleBase.h"
#include "ADASManager/Camera/ReserveCamera.h"
#include "ADASManager/Camera/CameraHub.h"

using namespace std;
using namespace Harman::Adas::AFramework::AFoundation;

using Harman::Adas::AFramework::ABase::ADASManager::CameraHub;
using Harman::Adas::AFramework::ABase::ADASManager::ReserveCamera;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class APasBase
    : public ModuleBase
    , public Observer
{
public:
	APasBase(CameraHub* hub);
	virtual ~APasBase();

public:
	virtual a_status initialize();
	virtual VOID unInitialize(){};
	virtual VOID beforeHandleMessageQueue(){};
	virtual VOID afterHandleMessageQueue();
	virtual a_status  isModuleAvailabel();
    virtual VOID Update(Subject* subject, Int32 state);
    virtual VOID onHandle(UInt32 uiEventID, const string& pData);

protected:
	a_status registerFunc(UInt32 eventID, CFunctor* pFunctor);

protected:
    Camera* m_pRearCamera = nullptr;

private:
	map<UInt32, CFunctor*> m_mMapPasFunc;

	BOOLEAN m_bPasAvailable = FALSE;
    CameraHub* m_pModuleHub = nullptr;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_APASBASE_H_