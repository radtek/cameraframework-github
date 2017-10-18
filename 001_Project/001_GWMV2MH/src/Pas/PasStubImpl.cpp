
#include "Pas/PasStubImpl.h"

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {
namespace Pas {

PasStubImpl::PasStubImpl(CameraHub* hub)
    : APasBase(hub)
{
}

PasStubImpl::~PasStubImpl()
{
}

a_status PasStubImpl::initialize()
{
    ALOGD("initialize\n");
    //registerFunc((UInt32)eCameraActivate_ON, makeFunctor(this, &PasStubImpl::showCamera));
    return a_status(0);
}

VOID PasStubImpl::afterHandleMessageQueue()
{
}

VOID PasStubImpl::showCamera(const string& pData)
{
    ALOGD("showCamera [%s]\n", pData.c_str());
    // m_pRearCamera->OpenCamera();
    // m_pRearCamera->StartCapture();
}

} // namespace Pas
} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman