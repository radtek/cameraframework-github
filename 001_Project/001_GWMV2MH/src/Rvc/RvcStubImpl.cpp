#include "Rvc/RvcStubImpl.h"
#include "Rvc/RvcMsgQDefine.h"

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
    ALOGD("initialize\n");
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
}

}
}
}
}