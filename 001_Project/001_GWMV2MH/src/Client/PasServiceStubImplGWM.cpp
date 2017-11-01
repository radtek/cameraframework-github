
#include "PasServiceStubImplGWM.h"
#include "Pas/PDCFactory.h"
#include "Pas/PDCServiceFord.h"

using Harman::Adas::AProject::GWMV2MH::Pas::PDCFactory;
using Harman::Adas::AProject::GWMV2MH::Pas::PDCServiceFord;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {

PasServiceStubImplGWM* PasServiceStubImplGWM::m_pInstance = NULL;

PasServiceStubImplGWM* PasServiceStubImplGWM::getInstance()
{
    if(NULL == m_pInstance)
    {
        m_pInstance = new PasServiceStubImplGWM();
    }

    return m_pInstance;
}

PasServiceStubImplGWM::PasServiceStubImplGWM()
{
    // PDCFactory *pTest = PDCFactory::getInstance();
    // PDCServiceFord *m_PDCServiceFord = pTest->vSetup();

    //---------------------------------------
    //m_PDCServiceFord->pushPDCMsg();
}

PasServiceStubImplGWM::~PasServiceStubImplGWM()
{

}

// void PasServiceStubImplGWM::SwitchPASView(const std::shared_ptr<CommonAPI::ClientId> _client,
//     ::v0::com::harman::adas::PASBaseType::enPASViewStatus m_ePASViewStatus,
//     SwitchPASViewReply_t)
// {

// }

} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman