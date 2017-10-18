
#ifndef __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_PDCFACTORY_H__
#define __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_PDCFACTORY_H__

//#include "VPAServiceStubImpl.hpp"
//#include "PDCServiceProxy.h"
#include "PDCServiceFord.h"
//using namespace v0::com::harman::ParkAssist;
//using namespace v1::com::harman::ParkAssist;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {
namespace Pas {

class PDCFactory {
public:
    static PDCFactory* getInstance();
    static void 				delInstance();
    PDCServiceFord* vSetup();
    virtual ~PDCFactory();
private:
    PDCFactory();
    static PDCFactory*  m_pInstance;
    //VPAServiceStubImpl* m_pVPAStubImpl;
    //PDCServiceProxy* m_pPDCServiceProxy;
};

} // namespace Pas
} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_PDCFACTORY_H__