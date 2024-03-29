/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.201702211714.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.3.0
* generated on: Tue Aug 01 13:37:50 CST 2017
*/
#include <v0/com/harman/adas/ADASDiagnosisStubDefault.hpp>
#include <assert.h>

namespace v0 {
namespace com {
namespace harman {
namespace adas {

ADASDiagnosisStubDefault::ADASDiagnosisStubDefault():
        remoteEventHandler_(this),
        interfaceVersion_(ADASDiagnosis::getInterfaceVersion()) {
}

const CommonAPI::Version& ADASDiagnosisStubDefault::getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return interfaceVersion_;
}

ADASDiagnosisStubRemoteEvent* ADASDiagnosisStubDefault::initStubAdapter(const std::shared_ptr<ADASDiagnosisStubAdapter> &_adapter) {
    CommonAPI::Stub<ADASDiagnosisStubAdapter, ADASDiagnosisStubRemoteEvent>::stubAdapter_ = _adapter;
    return &remoteEventHandler_;
}


void ADASDiagnosisStubDefault::triggerCameraTesting(const std::shared_ptr<CommonAPI::ClientId> _client, triggerCameraTestingReply_t _reply) {
    (void)_client;
    ::v1::com::harman::adas::ADASDiagType::enDiagTestState m_DiagTest = ::v1::com::harman::adas::ADASDiagType::enDiagTestState::e_TestStartSuccess;
    if (!m_DiagTest.validate()) {
        return;
    }
    _reply(m_DiagTest);
}

void ADASDiagnosisStubDefault::getNumOfCameras(const std::shared_ptr<CommonAPI::ClientId> _client, getNumOfCamerasReply_t _reply) {
    (void)_client;
    uint8_t m_eAVMGuideLinewMode = 0u;
    _reply(m_eAVMGuideLinewMode);
}




ADASDiagnosisStubDefault::RemoteEventHandler::RemoteEventHandler(ADASDiagnosisStubDefault *_defaultStub)
    : 
      defaultStub_(_defaultStub) {
}

} // namespace adas
} // namespace harman
} // namespace com
} // namespace v0
