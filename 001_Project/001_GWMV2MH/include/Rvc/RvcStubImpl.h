
#ifndef __HARMAN_ADAS_APROJECT_GWMV2MH_RVCSTUBIMPL_H__
#define __HARMAN_ADAS_APROJECT_GWMV2MH_RVCSTUBIMPL_H__

#include "ADASManager/RVC/ARvcBase.h"

using namespace std;
using namespace Harman::Adas::AFramework::ABase::ADASManager;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {

class RvcStubImpl : public ARvcBase
{
public:
    RvcStubImpl(CameraHub* hub);
    virtual ~RvcStubImpl();

public:
    a_status initialize();
    VOID afterHandleMessageQueue();

    VOID showCamera(const string& pData);

private:

};

} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_APROJECT_GWMV2MH_RVCSTUBIMPL_H__