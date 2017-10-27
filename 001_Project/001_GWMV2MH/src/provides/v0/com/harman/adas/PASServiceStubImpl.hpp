/**
 * generated by DCIF CodeGen Version: R2_v2.3.0
 * generated on: Thu Oct 12 15:16:25 CST 2017
 */

#ifndef V0_COM_HARMAN_ADAS_PASSERVICESTUBIMPL_HPP
#define V0_COM_HARMAN_ADAS_PASSERVICESTUBIMPL_HPP

#include <CommonAPI/CommonAPI.hpp>
#include "v0/com/harman/adas/PASServiceStubDefault.hpp"

namespace v0 {
namespace com {
namespace harman {
namespace adas {

class PASServiceStubImpl : public v0::com::harman::adas::PASServiceStubDefault
{

public:
	PASServiceStubImpl();
    virtual ~PASServiceStubImpl();

	virtual void SwitchPASView(const std::shared_ptr<CommonAPI::ClientId> _client, ::v0::com::harman::adas::PASBaseType::enPASViewStatus m_ePASViewStatus, SwitchPASViewReply_t);
};

} // namespace adas
} // namespace harman
} // namespace com
} // namespace v0

#endif //V0_COM_HARMAN_ADAS_PASSERVICESTUBIMPL_HPP
