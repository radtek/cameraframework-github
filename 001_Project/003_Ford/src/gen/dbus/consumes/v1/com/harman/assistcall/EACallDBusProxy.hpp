/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by Voice CodeGen Version: R1_v1.3.0
* generated on: Tue Mar 07 13:22:52 CST 2017
*/
/**
 * description: This is a Emergency Assitance Module  interface that is used by HMI and other
 *   module to 	   to get the EA supported features.
 * author: KHegde
 */
#ifndef V1_COM_HARMAN_ASSISTCALL_EA_Call_DBUS_PROXY_HPP_
#define V1_COM_HARMAN_ASSISTCALL_EA_Call_DBUS_PROXY_HPP_

#include <v1/com/harman/assistcall/EACallProxyBase.hpp>
#include "v1/com/harman/assistcall/EACallDBusDeployment.hpp"

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/DBus/DBusAddress.hpp>
#include <CommonAPI/DBus/DBusFactory.hpp>
#include <CommonAPI/DBus/DBusProxy.hpp>
#include <CommonAPI/DBus/DBusAddressTranslator.hpp>
#include <CommonAPI/DBus/DBusAttribute.hpp>
#include <CommonAPI/DBus/DBusEvent.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

#include <string>

namespace v1 {
namespace com {
namespace harman {
namespace assistcall {

class EACallDBusProxy
    : virtual public EACallProxyBase, 
      virtual public CommonAPI::DBus::DBusProxy {
public:
    EACallDBusProxy(
        const CommonAPI::DBus::DBusAddress &_address,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection);

    virtual ~EACallDBusProxy() { }

    virtual EAFeatureNameAttribute& getEAFeatureNameAttribute();
    virtual EAUserSettingStateAttribute& getEAUserSettingStateAttribute();
    virtual EAEventFlagAttribute& getEAEventFlagAttribute();
    virtual EAOperationalStateAttribute& getEAOperationalStateAttribute();
    virtual EAFeatureAvailabilityAttribute& getEAFeatureAvailabilityAttribute();
    virtual EAEventStatusAttribute& getEAEventStatusAttribute();
    virtual GpsDataAttribute& getGpsDataAttribute();
    virtual EaKeyTypeAttribute& getEaKeyTypeAttribute();
    virtual EAOperationalStatusAttribute& getEAOperationalStatusAttribute();
    virtual GpsLatLonDataAttribute& getGpsLatLonDataAttribute();

    virtual NotifyTMessageIDEvent& getNotifyTMessageIDEvent();
    virtual NotifyPMessageIDEvent& getNotifyPMessageIDEvent();
    virtual NotifyToTerminateTMEvent& getNotifyToTerminateTMEvent();
    virtual NotifyEACallCancelTimerEvent& getNotifyEACallCancelTimerEvent();
    virtual NotifyCancelTTSPlayEvent& getNotifyCancelTTSPlayEvent();

    /**
     * description: cancelRequestConfirm:          errorCode: Type='eErrorCode' Description='This
     *   is the                          return value of the method call '             
     *                This method can be used by HMI client to cancel           EA
     *   event behaviour
     * author: KHegde
     */
    virtual void cancelRequest(CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::assistcall::EACallTypedefs::eErrorCode &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> cancelRequestAsync(CancelRequestAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: cancelRequestConfirm:          errorCode: Type='eErrorCode' Description='This
     *   is the                          return value of the method call '             
     *                This method can be used by HMI client to confirm the user        
     *      request for the cancel EA event behaviour
     * author: KHegde
     */
    virtual void cancelRequestConfirm(CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::assistcall::EACallTypedefs::eErrorCode &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> cancelRequestConfirmAsync(CancelRequestConfirmAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: hmiRequestStartEACall:          errorCode: Type='eErrorCode' Description='This
     *   is the                          return value of the method call '             
     *                This method can be used by HMI to start the EA call when user
     *   selects "NO" in             cancel confirmation pop up.
     * author: KHegde
     */
    virtual void hmiRequestStartEACall(CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::assistcall::EACallTypedefs::eErrorCode &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> hmiRequestStartEACallAsync(HmiRequestStartEACallAsyncCallback _callback, const CommonAPI::CallInfo *_info);


    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

private:
   
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<EAFeatureNameAttribute, CommonAPI::DBus::StringDeployment>> eAFeatureName_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<EAUserSettingStateAttribute>> eAUserSettingState_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<EAEventFlagAttribute>> eAEventFlag_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<EAOperationalStateAttribute>> eAOperationalState_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<EAFeatureAvailabilityAttribute>> eAFeatureAvailability_;
    class DBuseAEventStatus_Attribute : public CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<EAEventStatusAttribute>> {
    public:
    template <typename... _A>
    	DBuseAEventStatus_Attribute(DBusProxy &_proxy,
    		_A ... arguments)
    		: CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<EAEventStatusAttribute>>(
    			_proxy, arguments...) {}
    };
    DBuseAEventStatus_Attribute eAEventStatus_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<GpsDataAttribute, ::v1::com::harman::assistcall::EACallTypedefs_::GPSDataDeployment_t>> gpsData_;
    class DBuseaKeyType_Attribute : public CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<EaKeyTypeAttribute>> {
    public:
    template <typename... _A>
    	DBuseaKeyType_Attribute(DBusProxy &_proxy,
    		_A ... arguments)
    		: CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<EaKeyTypeAttribute>>(
    			_proxy, arguments...) {}
    };
    DBuseaKeyType_Attribute eaKeyType_;
    class DBuseAOperationalStatus_Attribute : public CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<EAOperationalStatusAttribute>> {
    public:
    template <typename... _A>
    	DBuseAOperationalStatus_Attribute(DBusProxy &_proxy,
    		_A ... arguments)
    		: CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<EAOperationalStatusAttribute>>(
    			_proxy, arguments...) {}
    };
    DBuseAOperationalStatus_Attribute eAOperationalStatus_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<GpsLatLonDataAttribute, ::v1::com::harman::assistcall::EACallTypedefs_::GPSLatLonDataDeployment_t>> gpsLatLonData_;

    CommonAPI::DBus::DBusEvent<NotifyTMessageIDEvent, CommonAPI::Deployable<::v1::com::harman::assistcall::EACallTypedefs::eTMessageType, CommonAPI::EmptyDeployment>> notifyTMessageID_;
    CommonAPI::DBus::DBusEvent<NotifyPMessageIDEvent, CommonAPI::Deployable<::v1::com::harman::assistcall::EACallTypedefs::ePMessageType, CommonAPI::EmptyDeployment>> notifyPMessageID_;
    CommonAPI::DBus::DBusEvent<NotifyToTerminateTMEvent, CommonAPI::Deployable<::v1::com::harman::assistcall::EACallTypedefs::eTMessageType, CommonAPI::EmptyDeployment>> notifyToTerminateTM_;
    CommonAPI::DBus::DBusEvent<NotifyEACallCancelTimerEvent, CommonAPI::Deployable<uint8_t, CommonAPI::EmptyDeployment>, CommonAPI::Deployable<uint8_t, CommonAPI::EmptyDeployment>> notifyEACallCancelTimer_;
    CommonAPI::DBus::DBusEvent<NotifyCancelTTSPlayEvent, CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment>> notifyCancelTTSPlay_;

};

} // namespace assistcall
} // namespace harman
} // namespace com
} // namespace v1

#endif // V1_COM_HARMAN_ASSISTCALL_EA_Call_DBUS_PROXY_HPP_

