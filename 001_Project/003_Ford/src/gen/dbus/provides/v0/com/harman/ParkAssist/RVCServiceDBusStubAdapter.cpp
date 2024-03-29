/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by Voice CodeGen Version: R1_v1.3.0
* generated on: Tue Mar 07 13:22:52 CST 2017
*/
#include <v0/com/harman/ParkAssist/RVCService.hpp>
#include <v0/com/harman/ParkAssist/RVCServiceDBusStubAdapter.hpp>

namespace v0 {
namespace com {
namespace harman {
namespace ParkAssist {

std::shared_ptr<CommonAPI::DBus::DBusStubAdapter> createRVCServiceDBusStubAdapter(
                   const CommonAPI::DBus::DBusAddress &_address,
                   const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection,
                   const std::shared_ptr<CommonAPI::StubBase> &_stub) {
    return std::make_shared<RVCServiceDBusStubAdapter>(_address, _connection, _stub);
}

INITIALIZER(registerRVCServiceDBusStubAdapter) {
    CommonAPI::DBus::Factory::get()->registerStubAdapterCreateMethod(
    	RVCService::getInterface(), &createRVCServiceDBusStubAdapter);
}

RVCServiceDBusStubAdapterInternal::~RVCServiceDBusStubAdapterInternal() {
    deactivateManagedInstances();
    RVCServiceDBusStubAdapterHelper::deinit();
}

void RVCServiceDBusStubAdapterInternal::deactivateManagedInstances() {

}

const char* RVCServiceDBusStubAdapterInternal::getMethodsDBusIntrospectionXmlData() const {
    static const std::string introspectionData =
        "<method name=\"getInterfaceVersion\">\n"
            "<arg name=\"value\" type=\"uu\" direction=\"out\" />"
        "</method>\n"
        "<method name=\"getRVCZoomOnOffAttribute\">\n"
            "<arg name=\"value\" type=\"i\" direction=\"out\" />"
        "</method>\n"
        "<method name=\"setRVCZoomOnOffAttribute\">\n"
            "<arg name=\"requestedValue\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"setValue\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<signal name=\"onRVCZoomOnOffAttributeChanged\">\n"
            "<arg name=\"changedValue\" type=\"i\" />\n"
        "</signal>\n"
        "<method name=\"getRVCSpiltViewOnOffAttribute\">\n"
            "<arg name=\"value\" type=\"i\" direction=\"out\" />"
        "</method>\n"
        "<method name=\"setRVCSpiltViewOnOffAttribute\">\n"
            "<arg name=\"requestedValue\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"setValue\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<signal name=\"onRVCSpiltViewOnOffAttributeChanged\">\n"
            "<arg name=\"changedValue\" type=\"i\" />\n"
        "</signal>\n"
        "<method name=\"getRVCDisPlayStatusAttribute\">\n"
            "<arg name=\"value\" type=\"i\" direction=\"out\" />"
        "</method>\n"
        "<signal name=\"onRVCDisPlayStatusAttributeChanged\">\n"
            "<arg name=\"changedValue\" type=\"i\" />\n"
        "</signal>\n"
        "<method name=\"getRVCErrorAttribute\">\n"
            "<arg name=\"value\" type=\"i\" direction=\"out\" />"
        "</method>\n"
        "<signal name=\"onRVCErrorAttributeChanged\">\n"
            "<arg name=\"changedValue\" type=\"i\" />\n"
        "</signal>\n"
        "<method name=\"getCameraDelayOnOffAttribute\">\n"
            "<arg name=\"value\" type=\"b\" direction=\"out\" />"
        "</method>\n"
        "<method name=\"setCameraDelayOnOffAttribute\">\n"
            "<arg name=\"requestedValue\" type=\"b\" direction=\"in\" />\n"
            "<arg name=\"setValue\" type=\"b\" direction=\"out\" />\n"
        "</method>\n"
        "<signal name=\"onCameraDelayOnOffAttributeChanged\">\n"
            "<arg name=\"changedValue\" type=\"b\" />\n"
        "</signal>\n"
        "<method name=\"getRVCEnhancedPrkAidAttribute\">\n"
            "<arg name=\"value\" type=\"b\" direction=\"out\" />"
        "</method>\n"
        "<method name=\"setRVCEnhancedPrkAidAttribute\">\n"
            "<arg name=\"requestedValue\" type=\"b\" direction=\"in\" />\n"
            "<arg name=\"setValue\" type=\"b\" direction=\"out\" />\n"
        "</method>\n"
        "<signal name=\"onRVCEnhancedPrkAidAttributeChanged\">\n"
            "<arg name=\"changedValue\" type=\"b\" />\n"
        "</signal>\n"
        "<method name=\"getRVCTrunkStatusAttribute\">\n"
            "<arg name=\"value\" type=\"b\" direction=\"out\" />"
        "</method>\n"
        "<method name=\"setRVCTrunkStatusAttribute\">\n"
            "<arg name=\"requestedValue\" type=\"b\" direction=\"in\" />\n"
            "<arg name=\"setValue\" type=\"b\" direction=\"out\" />\n"
        "</method>\n"
        "<signal name=\"onRVCTrunkStatusAttributeChanged\">\n"
            "<arg name=\"changedValue\" type=\"b\" />\n"
        "</signal>\n"
        "<method name=\"getDisplayIconTypeAttribute\">\n"
            "<arg name=\"value\" type=\"i\" direction=\"out\" />"
        "</method>\n"
        "<signal name=\"onDisplayIconTypeAttributeChanged\">\n"
            "<arg name=\"changedValue\" type=\"i\" />\n"
        "</signal>\n"
        "<method name=\"CancelRVCReq\">\n"
            "<arg name=\"_m_eCancelRVC\" type=\"i\" direction=\"in\" />\n"
        "</method>\n"

    ;
    return introspectionData.c_str();
}

CommonAPI::DBus::DBusGetAttributeStubDispatcher<
        ::v0::com::harman::ParkAssist::RVCServiceStub,
        CommonAPI::Version
        > RVCServiceDBusStubAdapterInternal::getRVCServiceInterfaceVersionStubDispatcher(&RVCServiceStub::getInterfaceVersion, "uu");

CommonAPI::DBus::DBusGetAttributeStubDispatcher<
        ::v0::com::harman::ParkAssist::RVCServiceStub,
        ::v1::com::harman::ParkAssist::ParkAssistBaseType::enRVCZoom
        > RVCServiceDBusStubAdapterInternal::getRVCZoomOnOffAttributeStubDispatcher(
            &::v0::com::harman::ParkAssist::RVCServiceStub::getRVCZoomOnOffAttribute
            , "i"
            );
CommonAPI::DBus::DBusSetObservableAttributeStubDispatcher<
        ::v0::com::harman::ParkAssist::RVCServiceStub,
        ::v1::com::harman::ParkAssist::ParkAssistBaseType::enRVCZoom
        > RVCServiceDBusStubAdapterInternal::setRVCZoomOnOffAttributeStubDispatcher(
                &::v0::com::harman::ParkAssist::RVCServiceStub::getRVCZoomOnOffAttribute,
                &RVCServiceStubRemoteEvent::onRemoteSetRVCZoomOnOffAttribute,
                &RVCServiceStubRemoteEvent::onRemoteRVCZoomOnOffAttributeChanged
                ,&RVCServiceStubAdapter::fireRVCZoomOnOffAttributeChanged
                ,"i"
                );
CommonAPI::DBus::DBusGetAttributeStubDispatcher<
        ::v0::com::harman::ParkAssist::RVCServiceStub,
        ::v1::com::harman::ParkAssist::ParkAssistBaseType::enRVCSplitView
        > RVCServiceDBusStubAdapterInternal::getRVCSpiltViewOnOffAttributeStubDispatcher(
            &::v0::com::harman::ParkAssist::RVCServiceStub::getRVCSpiltViewOnOffAttribute
            , "i"
            );
CommonAPI::DBus::DBusSetObservableAttributeStubDispatcher<
        ::v0::com::harman::ParkAssist::RVCServiceStub,
        ::v1::com::harman::ParkAssist::ParkAssistBaseType::enRVCSplitView
        > RVCServiceDBusStubAdapterInternal::setRVCSpiltViewOnOffAttributeStubDispatcher(
                &::v0::com::harman::ParkAssist::RVCServiceStub::getRVCSpiltViewOnOffAttribute,
                &RVCServiceStubRemoteEvent::onRemoteSetRVCSpiltViewOnOffAttribute,
                &RVCServiceStubRemoteEvent::onRemoteRVCSpiltViewOnOffAttributeChanged
                ,&RVCServiceStubAdapter::fireRVCSpiltViewOnOffAttributeChanged
                ,"i"
                );
CommonAPI::DBus::DBusGetAttributeStubDispatcher<
        ::v0::com::harman::ParkAssist::RVCServiceStub,
        ::v1::com::harman::ParkAssist::ParkAssistBaseType::enRVCStatus
        > RVCServiceDBusStubAdapterInternal::getRVCDisPlayStatusAttributeStubDispatcher(
            &::v0::com::harman::ParkAssist::RVCServiceStub::getRVCDisPlayStatusAttribute
            , "i"
            );
CommonAPI::DBus::DBusGetAttributeStubDispatcher<
        ::v0::com::harman::ParkAssist::RVCServiceStub,
        ::v1::com::harman::ParkAssist::ParkAssistBaseType::enRVCError
        > RVCServiceDBusStubAdapterInternal::getRVCErrorAttributeStubDispatcher(
            &::v0::com::harman::ParkAssist::RVCServiceStub::getRVCErrorAttribute
            , "i"
            );
CommonAPI::DBus::DBusGetAttributeStubDispatcher<
        ::v0::com::harman::ParkAssist::RVCServiceStub,
        bool
        > RVCServiceDBusStubAdapterInternal::getCameraDelayOnOffAttributeStubDispatcher(
            &::v0::com::harman::ParkAssist::RVCServiceStub::getCameraDelayOnOffAttribute
            , "b"
            );
CommonAPI::DBus::DBusSetObservableAttributeStubDispatcher<
        ::v0::com::harman::ParkAssist::RVCServiceStub,
        bool
        > RVCServiceDBusStubAdapterInternal::setCameraDelayOnOffAttributeStubDispatcher(
                &::v0::com::harman::ParkAssist::RVCServiceStub::getCameraDelayOnOffAttribute,
                &RVCServiceStubRemoteEvent::onRemoteSetCameraDelayOnOffAttribute,
                &RVCServiceStubRemoteEvent::onRemoteCameraDelayOnOffAttributeChanged
                ,&RVCServiceStubAdapter::fireCameraDelayOnOffAttributeChanged
                ,"b"
                );
CommonAPI::DBus::DBusGetAttributeStubDispatcher<
        ::v0::com::harman::ParkAssist::RVCServiceStub,
        bool
        > RVCServiceDBusStubAdapterInternal::getRVCEnhancedPrkAidAttributeStubDispatcher(
            &::v0::com::harman::ParkAssist::RVCServiceStub::getRVCEnhancedPrkAidAttribute
            , "b"
            );
CommonAPI::DBus::DBusSetObservableAttributeStubDispatcher<
        ::v0::com::harman::ParkAssist::RVCServiceStub,
        bool
        > RVCServiceDBusStubAdapterInternal::setRVCEnhancedPrkAidAttributeStubDispatcher(
                &::v0::com::harman::ParkAssist::RVCServiceStub::getRVCEnhancedPrkAidAttribute,
                &RVCServiceStubRemoteEvent::onRemoteSetRVCEnhancedPrkAidAttribute,
                &RVCServiceStubRemoteEvent::onRemoteRVCEnhancedPrkAidAttributeChanged
                ,&RVCServiceStubAdapter::fireRVCEnhancedPrkAidAttributeChanged
                ,"b"
                );
CommonAPI::DBus::DBusGetAttributeStubDispatcher<
        ::v0::com::harman::ParkAssist::RVCServiceStub,
        bool
        > RVCServiceDBusStubAdapterInternal::getRVCTrunkStatusAttributeStubDispatcher(
            &::v0::com::harman::ParkAssist::RVCServiceStub::getRVCTrunkStatusAttribute
            , "b"
            );
CommonAPI::DBus::DBusSetObservableAttributeStubDispatcher<
        ::v0::com::harman::ParkAssist::RVCServiceStub,
        bool
        > RVCServiceDBusStubAdapterInternal::setRVCTrunkStatusAttributeStubDispatcher(
                &::v0::com::harman::ParkAssist::RVCServiceStub::getRVCTrunkStatusAttribute,
                &RVCServiceStubRemoteEvent::onRemoteSetRVCTrunkStatusAttribute,
                &RVCServiceStubRemoteEvent::onRemoteRVCTrunkStatusAttributeChanged
                ,&RVCServiceStubAdapter::fireRVCTrunkStatusAttributeChanged
                ,"b"
                );
CommonAPI::DBus::DBusGetAttributeStubDispatcher<
        ::v0::com::harman::ParkAssist::RVCServiceStub,
        ::v1::com::harman::ParkAssist::ParkAssistBaseType::enDisplayIconType
        > RVCServiceDBusStubAdapterInternal::getDisplayIconTypeAttributeStubDispatcher(
            &::v0::com::harman::ParkAssist::RVCServiceStub::getDisplayIconTypeAttribute
            , "i"
            );



CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    ::v0::com::harman::ParkAssist::RVCServiceStub,
    std::tuple<::v1::com::harman::ParkAssist::ParkAssistBaseType::enCancelRVC>,
    std::tuple<>,
    std::tuple<CommonAPI::EmptyDeployment>,
    std::tuple<>
    
    > RVCServiceDBusStubAdapterInternal::cancelRVCReqStubDispatcher(
    &RVCServiceStub::CancelRVCReq, "",
					std::make_tuple(static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
                	std::make_tuple());


void RVCServiceDBusStubAdapterInternal::fireRVCZoomOnOffAttributeChanged(const ::v1::com::harman::ParkAssist::ParkAssistBaseType::enRVCZoom& value) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<
    ::v1::com::harman::ParkAssist::ParkAssistBaseType::enRVCZoom
    >>
        ::sendSignal(
            *this,
            "onRVCZoomOnOffAttributeChanged",
            "i",
            value
    
    );
}
void RVCServiceDBusStubAdapterInternal::fireRVCSpiltViewOnOffAttributeChanged(const ::v1::com::harman::ParkAssist::ParkAssistBaseType::enRVCSplitView& value) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<
    ::v1::com::harman::ParkAssist::ParkAssistBaseType::enRVCSplitView
    >>
        ::sendSignal(
            *this,
            "onRVCSpiltViewOnOffAttributeChanged",
            "i",
            value
    
    );
}
void RVCServiceDBusStubAdapterInternal::fireRVCDisPlayStatusAttributeChanged(const ::v1::com::harman::ParkAssist::ParkAssistBaseType::enRVCStatus& value) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<
    ::v1::com::harman::ParkAssist::ParkAssistBaseType::enRVCStatus
    >>
        ::sendSignal(
            *this,
            "onRVCDisPlayStatusAttributeChanged",
            "i",
            value
    
    );
}
void RVCServiceDBusStubAdapterInternal::fireRVCErrorAttributeChanged(const ::v1::com::harman::ParkAssist::ParkAssistBaseType::enRVCError& value) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<
    ::v1::com::harman::ParkAssist::ParkAssistBaseType::enRVCError
    >>
        ::sendSignal(
            *this,
            "onRVCErrorAttributeChanged",
            "i",
            value
    
    );
}
void RVCServiceDBusStubAdapterInternal::fireCameraDelayOnOffAttributeChanged(const bool& value) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<
    bool
    >>
        ::sendSignal(
            *this,
            "onCameraDelayOnOffAttributeChanged",
            "b",
            value
    
    );
}
void RVCServiceDBusStubAdapterInternal::fireRVCEnhancedPrkAidAttributeChanged(const bool& value) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<
    bool
    >>
        ::sendSignal(
            *this,
            "onRVCEnhancedPrkAidAttributeChanged",
            "b",
            value
    
    );
}
void RVCServiceDBusStubAdapterInternal::fireRVCTrunkStatusAttributeChanged(const bool& value) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<
    bool
    >>
        ::sendSignal(
            *this,
            "onRVCTrunkStatusAttributeChanged",
            "b",
            value
    
    );
}
void RVCServiceDBusStubAdapterInternal::fireDisplayIconTypeAttributeChanged(const ::v1::com::harman::ParkAssist::ParkAssistBaseType::enDisplayIconType& value) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<
    ::v1::com::harman::ParkAssist::ParkAssistBaseType::enDisplayIconType
    >>
        ::sendSignal(
            *this,
            "onDisplayIconTypeAttributeChanged",
            "i",
            value
    
    );
}



const RVCServiceDBusStubAdapterHelper::StubDispatcherTable& RVCServiceDBusStubAdapterInternal::getStubDispatcherTable() {
    return stubDispatcherTable_;
}

const CommonAPI::DBus::StubAttributeTable& RVCServiceDBusStubAdapterInternal::getStubAttributeTable() {
    return stubAttributeTable_;
}

RVCServiceDBusStubAdapterInternal::RVCServiceDBusStubAdapterInternal(
        const CommonAPI::DBus::DBusAddress &_address,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection,
        const std::shared_ptr<CommonAPI::StubBase> &_stub)
	: CommonAPI::DBus::DBusStubAdapter(_address, _connection,false),
      RVCServiceDBusStubAdapterHelper(_address, _connection, std::dynamic_pointer_cast<RVCServiceStub>(_stub), false),
      stubDispatcherTable_({
            { { "getRVCZoomOnOffAttribute", "" }, &com::harman::ParkAssist::RVCServiceDBusStubAdapterInternal::getRVCZoomOnOffAttributeStubDispatcher }
            , { { "setRVCZoomOnOffAttribute", "i" }, &com::harman::ParkAssist::RVCServiceDBusStubAdapterInternal::setRVCZoomOnOffAttributeStubDispatcher },
            { { "getRVCSpiltViewOnOffAttribute", "" }, &com::harman::ParkAssist::RVCServiceDBusStubAdapterInternal::getRVCSpiltViewOnOffAttributeStubDispatcher }
            , { { "setRVCSpiltViewOnOffAttribute", "i" }, &com::harman::ParkAssist::RVCServiceDBusStubAdapterInternal::setRVCSpiltViewOnOffAttributeStubDispatcher },
            { { "getRVCDisPlayStatusAttribute", "" }, &com::harman::ParkAssist::RVCServiceDBusStubAdapterInternal::getRVCDisPlayStatusAttributeStubDispatcher },
            { { "getRVCErrorAttribute", "" }, &com::harman::ParkAssist::RVCServiceDBusStubAdapterInternal::getRVCErrorAttributeStubDispatcher },
            { { "getCameraDelayOnOffAttribute", "" }, &com::harman::ParkAssist::RVCServiceDBusStubAdapterInternal::getCameraDelayOnOffAttributeStubDispatcher }
            , { { "setCameraDelayOnOffAttribute", "b" }, &com::harman::ParkAssist::RVCServiceDBusStubAdapterInternal::setCameraDelayOnOffAttributeStubDispatcher },
            { { "getRVCEnhancedPrkAidAttribute", "" }, &com::harman::ParkAssist::RVCServiceDBusStubAdapterInternal::getRVCEnhancedPrkAidAttributeStubDispatcher }
            , { { "setRVCEnhancedPrkAidAttribute", "b" }, &com::harman::ParkAssist::RVCServiceDBusStubAdapterInternal::setRVCEnhancedPrkAidAttributeStubDispatcher },
            { { "getRVCTrunkStatusAttribute", "" }, &com::harman::ParkAssist::RVCServiceDBusStubAdapterInternal::getRVCTrunkStatusAttributeStubDispatcher }
            , { { "setRVCTrunkStatusAttribute", "b" }, &com::harman::ParkAssist::RVCServiceDBusStubAdapterInternal::setRVCTrunkStatusAttributeStubDispatcher },
            { { "getDisplayIconTypeAttribute", "" }, &com::harman::ParkAssist::RVCServiceDBusStubAdapterInternal::getDisplayIconTypeAttributeStubDispatcher }
            ,
            { { "CancelRVCReq", "i" }, &com::harman::ParkAssist::RVCServiceDBusStubAdapterInternal::cancelRVCReqStubDispatcher }
            }),
        stubAttributeTable_() {

    stubDispatcherTable_.insert({ { "getInterfaceVersion", "" }, &com::harman::ParkAssist::RVCServiceDBusStubAdapterInternal::getRVCServiceInterfaceVersionStubDispatcher });
}

bool RVCServiceDBusStubAdapterInternal::hasFreedesktopProperties() {
    return false;
}

} // namespace ParkAssist
} // namespace harman
} // namespace com
} // namespace v0
