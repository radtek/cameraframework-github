#include "Rvc/RvcStubImpl.h"
#include "Rvc/RvcMsgQDefine.h"
#include "RvcServiceStubImplGWM.h"
#include "v0/com/harman/adas/RVCBaseType.hpp"
#include "AFoundation.h"

using namespace Harman::Adas::AFramework::AFoundation;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {

RvcStubImpl::RvcStubImpl(CameraHub* hub)
    :ARvcBase(hub)
{

}

RvcStubImpl::~RvcStubImpl()
{

}

a_status  RvcStubImpl::initialize()
{
    ALOGD("RvcStubImpl::initialize\n");
    registerFunc((UInt32)eCameraActivate_ON, makeFunctor(this, &RvcStubImpl::showCamera));
    return a_status(0); 
}

VOID  RvcStubImpl::afterHandleMessageQueue()
{

}

VOID  RvcStubImpl::showCamera(const string& pData)
{
    ALOGD("showCamera [%s]\n", pData.c_str());
    m_pRearCamera->OpenCamera();
    m_pRearCamera->StartCapture();

    RvcServiceStubImplGWM::getInstance()->setRvcStateAttribute(::v0::com::harman::adas::RVCBaseType::enRvcState::e_RVC_ON);
}


}
}
}
}