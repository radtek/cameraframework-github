/**
 * generated by Voice CodeGen Version: R1_v1.3.0
 * generated on: Thu Nov 24 16:30:49 IST 2016
 */

#ifndef V0_COM_HARMAN_PARKASSIST_APASERVICESTUBIMPL_HPP
#define V0_COM_HARMAN_PARKASSIST_APASERVICESTUBIMPL_HPP

#include <CommonAPI/CommonAPI.hpp>
#include "v0/com/harman/ParkAssist/APAServiceStubDefault.hpp"
#include "ParkAssistSrv_Common/CommonCore.hpp"
#include "ParkAssistSrv_Common/CPAMContext.hpp"

namespace v0 {
namespace com {
namespace harman {
namespace ParkAssist {

class APAServiceStubImpl : public v0::com::harman::ParkAssist::APAServiceStubDefault
{

    public:
    
        APAServiceStubImpl(CContext *p_pobjContext);
        virtual ~APAServiceStubImpl();

        virtual void SelectApaMode(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::harman::ParkAssist::APABaseType::enAPAMode m_eModeReq, SelectApaModeReply_t);
        void ApaMde_D_StatToTableMapping();
        void ApaGearShif_D_RqDrvToTableMapping();
        void UpdateAPAFeatureAvailabilityToHMI();
        void ParseAllTables();
		void ParsePrkAidMsgTxtTables();
    private:
        
        CContext *m_pobjContext;
        void CreateReferenceTable();
};

} // namespace ParkAssist
} // namespace harman
} // namespace com
} // namespace v0

#endif //V0_COM_HARMAN_PARKASSIST_APASERVICESTUBIMPL_HPP
