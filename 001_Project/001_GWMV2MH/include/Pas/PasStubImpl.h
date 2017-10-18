
#ifndef __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_PASSTUBIMPL_H_
#define __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_PASSTUBIMPL_H_

#include "ADASManager/PAS/APasBase.h"

using namespace std;
using namespace Harman::Adas::AFramework::ABase::ADASManager;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {
namespace Pas {

class PasStubImpl : public APasBase
{
public:
    PasStubImpl(CameraHub* hub);
    virtual ~PasStubImpl();

public:
    a_status initialize();
    VOID afterHandleMessageQueue();

    VOID showCamera(const string& pData);

private:

};

} // namespace Pas
} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_PASSTUBIMPL_H_