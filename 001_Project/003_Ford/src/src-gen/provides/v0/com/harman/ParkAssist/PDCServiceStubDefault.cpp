/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by Voice CodeGen Version: R1_v1.3.0
* generated on: Tue Mar 07 13:22:52 CST 2017
*/
#include <v0/com/harman/ParkAssist/PDCServiceStubDefault.hpp>
#include <assert.h>

namespace v0 {
namespace com {
namespace harman {
namespace ParkAssist {

PDCServiceStubDefault::PDCServiceStubDefault():
        remoteEventHandler_(this),
        interfaceVersion_(PDCService::getInterfaceVersion()) {
}

const CommonAPI::Version& PDCServiceStubDefault::getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return interfaceVersion_;
}

PDCServiceStubRemoteEvent* PDCServiceStubDefault::initStubAdapter(const std::shared_ptr<PDCServiceStubAdapter> &_adapter) {
    CommonAPI::Stub<PDCServiceStubAdapter, PDCServiceStubRemoteEvent>::stubAdapter_ = _adapter;
    return &remoteEventHandler_;
}

const ::v1::com::harman::ParkAssist::PDCBaseType::enPDCStatus& PDCServiceStubDefault::getPDCStatusAttribute() {
    return pDCStatusAttributeValue_;
}

const ::v1::com::harman::ParkAssist::PDCBaseType::enPDCStatus& PDCServiceStubDefault::getPDCStatusAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return getPDCStatusAttribute();
}

void PDCServiceStubDefault::setPDCStatusAttribute(::v1::com::harman::ParkAssist::PDCBaseType::enPDCStatus _value) {
    const bool valueChanged = trySetPDCStatusAttribute(std::move(_value));
    if (valueChanged) {
        auto stubAdapter = CommonAPI::Stub<PDCServiceStubAdapter, PDCServiceStubRemoteEvent>::stubAdapter_.lock();
        if (stubAdapter)
            stubAdapter->firePDCStatusAttributeChanged(pDCStatusAttributeValue_);
    }
}

bool PDCServiceStubDefault::trySetPDCStatusAttribute(::v1::com::harman::ParkAssist::PDCBaseType::enPDCStatus _value) {
    if (!validatePDCStatusAttributeRequestedValue(_value))
        return false;

    const bool valueChanged = (pDCStatusAttributeValue_ != _value);
    pDCStatusAttributeValue_ = std::move(_value);
    return valueChanged;
}

bool PDCServiceStubDefault::validatePDCStatusAttributeRequestedValue(const ::v1::com::harman::ParkAssist::PDCBaseType::enPDCStatus &_value) {
    (void)_value;
	return _value.validate();
}


const bool& PDCServiceStubDefault::getPDCErrorStatusAttribute() {
    return pDCErrorStatusAttributeValue_;
}

const bool& PDCServiceStubDefault::getPDCErrorStatusAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return getPDCErrorStatusAttribute();
}

void PDCServiceStubDefault::setPDCErrorStatusAttribute(bool _value) {
    const bool valueChanged = trySetPDCErrorStatusAttribute(std::move(_value));
    if (valueChanged) {
        auto stubAdapter = CommonAPI::Stub<PDCServiceStubAdapter, PDCServiceStubRemoteEvent>::stubAdapter_.lock();
        if (stubAdapter)
            stubAdapter->firePDCErrorStatusAttributeChanged(pDCErrorStatusAttributeValue_);
    }
}

bool PDCServiceStubDefault::trySetPDCErrorStatusAttribute(bool _value) {
    if (!validatePDCErrorStatusAttributeRequestedValue(_value))
        return false;

    const bool valueChanged = (pDCErrorStatusAttributeValue_ != _value);
    pDCErrorStatusAttributeValue_ = std::move(_value);
    return valueChanged;
}

bool PDCServiceStubDefault::validatePDCErrorStatusAttributeRequestedValue(const bool &_value) {
    (void)_value;
	return true;
}



void PDCServiceStubDefault::CancelPDCReq(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::harman::ParkAssist::PDCBaseType::enCancelPDCIcon _m_eCancelPDC, CancelPDCReqReply_t _reply) {
    (void)_client;
    (void) _m_eCancelPDC;
    _reply();
}




PDCServiceStubDefault::RemoteEventHandler::RemoteEventHandler(PDCServiceStubDefault *_defaultStub)
    : 
      defaultStub_(_defaultStub) {
}

} // namespace ParkAssist
} // namespace harman
} // namespace com
} // namespace v0
