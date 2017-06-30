/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by Voice CodeGen Version: R1_v1.3.0
* generated on: Tue Mar 07 13:22:52 CST 2017
*/
#ifndef V0_COM_HARMAN_PARKASSIST_PDC_Service_STUB_HPP_
#define V0_COM_HARMAN_PARKASSIST_PDC_Service_STUB_HPP_

#include <functional>



#include <v1/com/harman/ParkAssist/PDCBaseType.hpp>

#include <v0/com/harman/ParkAssist/PDCService.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <cstdint>
#include <vector>

#include <CommonAPI/Stub.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v0 {
namespace com {
namespace harman {
namespace ParkAssist {

/**
 * Receives messages from remote and handles all dispatching of deserialized calls
 * to a stub for the service PDCService. Also provides means to send broadcasts
 * and attribute-changed-notifications of observable attributes as defined by this service.
 * An application developer should not need to bother with this class.
 */
class PDCServiceStubAdapter
    : public virtual CommonAPI::StubAdapter, 
      public virtual PDCService {
 public:
    ///Notifies all remote listeners about a change of value of the attribute PDCStatus.
    virtual void firePDCStatusAttributeChanged(const ::v1::com::harman::ParkAssist::PDCBaseType::enPDCStatus& PDCStatus) = 0;
    ///Notifies all remote listeners about a change of value of the attribute PDCErrorStatus.
    virtual void firePDCErrorStatusAttributeChanged(const bool& PDCErrorStatus) = 0;



    virtual void deactivateManagedInstances() = 0;
protected:
    /**
     * Defines properties for storing the ClientIds of clients / proxies that have
     * subscribed to the selective broadcasts
     */
};

/**
 * Defines the necessary callbacks to handle remote set events related to the attributes
 * defined in the IDL description for PDCService.
 * For each attribute two callbacks are defined:
 * - a verification callback that allows to verify the requested value and to prevent setting
 *   e.g. an invalid value ("onRemoteSet<AttributeName>").
 * - an action callback to do local work after the attribute value has been changed
 *   ("onRemote<AttributeName>Changed").
 *
 * This class and the one below are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class PDCServiceStubRemoteEvent
{
public:
    virtual ~PDCServiceStubRemoteEvent() { }

};

/**
 * Defines the interface that must be implemented by any class that should provide
 * the service PDCService to remote clients.
 * This class and the one above are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class PDCServiceStub
    : public virtual CommonAPI::Stub<PDCServiceStubAdapter, PDCServiceStubRemoteEvent>
{
public:
    typedef std::function<void ()>CancelPDCReqReply_t;

    virtual ~PDCServiceStub() {}
    virtual const CommonAPI::Version& getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> clientId) = 0;

    /// Provides getter access to the attribute PDCStatus
    virtual const ::v1::com::harman::ParkAssist::PDCBaseType::enPDCStatus &getPDCStatusAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) = 0;
    /// Provides getter access to the attribute PDCErrorStatus
    virtual const bool &getPDCErrorStatusAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) = 0;

    /// This is the method that will be called on remote calls on the method CancelPDCReq.
    virtual void CancelPDCReq(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::harman::ParkAssist::PDCBaseType::enCancelPDCIcon _m_eCancelPDC, CancelPDCReqReply_t _reply) = 0;

    using CommonAPI::Stub<PDCServiceStubAdapter, PDCServiceStubRemoteEvent>::initStubAdapter;
    typedef CommonAPI::Stub<PDCServiceStubAdapter, PDCServiceStubRemoteEvent>::StubAdapterType StubAdapterType;
    typedef CommonAPI::Stub<PDCServiceStubAdapter, PDCServiceStubRemoteEvent>::RemoteEventHandlerType RemoteEventHandlerType;
    typedef PDCServiceStubRemoteEvent RemoteEventType;
    typedef PDCService StubInterface;
};

} // namespace ParkAssist
} // namespace harman
} // namespace com
} // namespace v0


// Compatibility
namespace v0_1 = v0;

#endif // V0_COM_HARMAN_PARKASSIST_PDC_Service_STUB_HPP_
