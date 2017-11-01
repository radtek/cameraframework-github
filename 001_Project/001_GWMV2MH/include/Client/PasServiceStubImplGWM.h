
#ifndef __HARMAN_ADAS_APROJECT_GWMV2MH_CLIENT_PASSERVICESTUBIMPLGWM_H__
#define __HARMAN_ADAS_APROJECT_GWMV2MH_CLIENT_PASSERVICESTUBIMPLGWM_H__

#include "v0/com/harman/adas/PASServiceStubImpl.hpp"
#include "TraceMacros.h"

using v0::com::harman::adas::PASServiceStubImpl;

using namespace std;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {

class PasServiceStubImplGWM : public PASServiceStubImpl
{
public:
    static PasServiceStubImplGWM* getInstance();
    virtual ~PasServiceStubImplGWM();

    // virtual void SwitchPASView(const std::shared_ptr<CommonAPI::ClientId> _client,
    //         ::v0::com::harman::adas::PASBaseType::enPASViewStatus m_ePASViewStatus,
    //         SwitchPASViewReply_t) override;

private:
    PasServiceStubImplGWM();

private:
    static PasServiceStubImplGWM* m_pInstance;
};

} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_APROJECT_GWMV2MH_CLIENT_PASSERVICESTUBIMPLGWM_H__