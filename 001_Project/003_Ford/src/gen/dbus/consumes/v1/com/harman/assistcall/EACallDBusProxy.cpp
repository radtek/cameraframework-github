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
#include <v1/com/harman/assistcall/EACallDBusProxy.hpp>

namespace v1 {
namespace com {
namespace harman {
namespace assistcall {

std::shared_ptr<CommonAPI::DBus::DBusProxy> createEACallDBusProxy(
	const CommonAPI::DBus::DBusAddress &_address,
	const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection) {
	return std::make_shared<EACallDBusProxy>(_address, _connection);
}

INITIALIZER(registerEACallDBusProxy) {
     CommonAPI::DBus::Factory::get()->registerProxyCreateMethod(
		EACall::getInterface(),
		&createEACallDBusProxy);
}

EACallDBusProxy::EACallDBusProxy(
	const CommonAPI::DBus::DBusAddress &_address,
	const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection)
	:	CommonAPI::DBus::DBusProxy(_address, _connection)
,		eAFeatureName_(*this, "onEAFeatureNameAttributeChanged", "s", "getEAFeatureNameAttribute", static_cast<CommonAPI::DBus::StringDeployment*>(nullptr)),
		eAUserSettingState_(*this, "onEAUserSettingStateAttributeChanged", "setEAUserSettingStateAttribute", "b", "getEAUserSettingStateAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		eAEventFlag_(*this, "onEAEventFlagAttributeChanged", "b", "getEAEventFlagAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		eAOperationalState_(*this, "onEAOperationalStateAttributeChanged", "b", "getEAOperationalStateAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		eAFeatureAvailability_(*this, "onEAFeatureAvailabilityAttributeChanged", "b", "getEAFeatureAvailabilityAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		eAEventStatus_(*this, "onEAEventStatusAttributeChanged", "i", "getEAEventStatusAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		gpsData_(*this, "onGpsDataAttributeChanged", "(dd)", "getGpsDataAttribute", static_cast<::v1::com::harman::assistcall::EACallTypedefs_::GPSDataDeployment_t*>(nullptr)),
		eaKeyType_(*this, "onEaKeyTypeAttributeChanged", "i", "getEaKeyTypeAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		eAOperationalStatus_(*this, "onEAOperationalStatusAttributeChanged", "i", "getEAOperationalStatusAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		gpsLatLonData_(*this, "onGpsLatLonDataAttributeChanged", "(ddb)", "getGpsLatLonDataAttribute", static_cast<::v1::com::harman::assistcall::EACallTypedefs_::GPSLatLonDataDeployment_t*>(nullptr))
,		notifyTMessageID_(*this, "notifyTMessageID", "i", std::make_tuple(static_cast<CommonAPI::EmptyDeployment*>(nullptr))),
		notifyPMessageID_(*this, "notifyPMessageID", "i", std::make_tuple(static_cast<CommonAPI::EmptyDeployment*>(nullptr))),
		notifyToTerminateTM_(*this, "notifyToTerminateTM", "i", std::make_tuple(static_cast<CommonAPI::EmptyDeployment*>(nullptr))),
		notifyEACallCancelTimer_(*this, "notifyEACallCancelTimer", "yy", std::make_tuple(static_cast<CommonAPI::EmptyDeployment*>(nullptr), static_cast<CommonAPI::EmptyDeployment*>(nullptr))),
		notifyCancelTTSPlay_(*this, "notifyCancelTTSPlay", "s", std::make_tuple(static_cast<CommonAPI::DBus::StringDeployment*>(nullptr)))
{
}

      EACallDBusProxy::EAFeatureNameAttribute& EACallDBusProxy::getEAFeatureNameAttribute() {
          return eAFeatureName_;
      }
      EACallDBusProxy::EAUserSettingStateAttribute& EACallDBusProxy::getEAUserSettingStateAttribute() {
          return eAUserSettingState_;
      }
      EACallDBusProxy::EAEventFlagAttribute& EACallDBusProxy::getEAEventFlagAttribute() {
          return eAEventFlag_;
      }
      EACallDBusProxy::EAOperationalStateAttribute& EACallDBusProxy::getEAOperationalStateAttribute() {
          return eAOperationalState_;
      }
      EACallDBusProxy::EAFeatureAvailabilityAttribute& EACallDBusProxy::getEAFeatureAvailabilityAttribute() {
          return eAFeatureAvailability_;
      }
      EACallDBusProxy::EAEventStatusAttribute& EACallDBusProxy::getEAEventStatusAttribute() {
          return eAEventStatus_;
      }
      EACallDBusProxy::GpsDataAttribute& EACallDBusProxy::getGpsDataAttribute() {
          return gpsData_;
      }
      EACallDBusProxy::EaKeyTypeAttribute& EACallDBusProxy::getEaKeyTypeAttribute() {
          return eaKeyType_;
      }
      EACallDBusProxy::EAOperationalStatusAttribute& EACallDBusProxy::getEAOperationalStatusAttribute() {
          return eAOperationalStatus_;
      }
      EACallDBusProxy::GpsLatLonDataAttribute& EACallDBusProxy::getGpsLatLonDataAttribute() {
          return gpsLatLonData_;
      }

EACallDBusProxy::NotifyTMessageIDEvent& EACallDBusProxy::getNotifyTMessageIDEvent() {
    return notifyTMessageID_;
}
EACallDBusProxy::NotifyPMessageIDEvent& EACallDBusProxy::getNotifyPMessageIDEvent() {
    return notifyPMessageID_;
}
EACallDBusProxy::NotifyToTerminateTMEvent& EACallDBusProxy::getNotifyToTerminateTMEvent() {
    return notifyToTerminateTM_;
}
EACallDBusProxy::NotifyEACallCancelTimerEvent& EACallDBusProxy::getNotifyEACallCancelTimerEvent() {
    return notifyEACallCancelTimer_;
}
EACallDBusProxy::NotifyCancelTTSPlayEvent& EACallDBusProxy::getNotifyCancelTTSPlayEvent() {
    return notifyCancelTTSPlay_;
}
    
    /**
     * description: cancelRequestConfirm:          errorCode: Type='eErrorCode' Description='This
     *   is the                          return value of the method call '             
     *                This method can be used by HMI client to cancel           EA
     *   event behaviour
     * author: KHegde
     */
    void EACallDBusProxy::cancelRequest(CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::assistcall::EACallTypedefs::eErrorCode &_errorCode, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<::v1::com::harman::assistcall::EACallTypedefs::eErrorCode, CommonAPI::EmptyDeployment> deploy_errorCode(static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v1::com::harman::assistcall::EACallTypedefs::eErrorCode,CommonAPI::EmptyDeployment>
            >
        	>::callMethodWithReply(
        *this,
        "cancelRequest",
        "",
(_info ? _info : &CommonAPI::DBus::defaultCallInfo),
_internalCallStatus,
deploy_errorCode);
_errorCode = deploy_errorCode.getValue();
}
    std::future<CommonAPI::CallStatus> EACallDBusProxy::cancelRequestAsync(CancelRequestAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<::v1::com::harman::assistcall::EACallTypedefs::eErrorCode, CommonAPI::EmptyDeployment> deploy_errorCode(static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        return CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v1::com::harman::assistcall::EACallTypedefs::eErrorCode,CommonAPI::EmptyDeployment>
            >
        	>::callMethodAsync(
        *this,
        "cancelRequest",
        "",
        (_info ? _info : &CommonAPI::DBus::defaultCallInfo),
        [_callback] (CommonAPI::CallStatus _internalCallStatus, CommonAPI::Deployable<::v1::com::harman::assistcall::EACallTypedefs::eErrorCode, CommonAPI::EmptyDeployment> _errorCode) {
        	if (_callback)
        		_callback(_internalCallStatus, _errorCode.getValue());
        },
        std::make_tuple(deploy_errorCode));
    }
    /**
     * description: cancelRequestConfirm:          errorCode: Type='eErrorCode' Description='This
     *   is the                          return value of the method call '             
     *                This method can be used by HMI client to confirm the user        
     *      request for the cancel EA event behaviour
     * author: KHegde
     */
    void EACallDBusProxy::cancelRequestConfirm(CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::assistcall::EACallTypedefs::eErrorCode &_errorCode, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<::v1::com::harman::assistcall::EACallTypedefs::eErrorCode, CommonAPI::EmptyDeployment> deploy_errorCode(static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v1::com::harman::assistcall::EACallTypedefs::eErrorCode,CommonAPI::EmptyDeployment>
            >
        	>::callMethodWithReply(
        *this,
        "cancelRequestConfirm",
        "",
(_info ? _info : &CommonAPI::DBus::defaultCallInfo),
_internalCallStatus,
deploy_errorCode);
_errorCode = deploy_errorCode.getValue();
}
    std::future<CommonAPI::CallStatus> EACallDBusProxy::cancelRequestConfirmAsync(CancelRequestConfirmAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<::v1::com::harman::assistcall::EACallTypedefs::eErrorCode, CommonAPI::EmptyDeployment> deploy_errorCode(static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        return CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v1::com::harman::assistcall::EACallTypedefs::eErrorCode,CommonAPI::EmptyDeployment>
            >
        	>::callMethodAsync(
        *this,
        "cancelRequestConfirm",
        "",
        (_info ? _info : &CommonAPI::DBus::defaultCallInfo),
        [_callback] (CommonAPI::CallStatus _internalCallStatus, CommonAPI::Deployable<::v1::com::harman::assistcall::EACallTypedefs::eErrorCode, CommonAPI::EmptyDeployment> _errorCode) {
        	if (_callback)
        		_callback(_internalCallStatus, _errorCode.getValue());
        },
        std::make_tuple(deploy_errorCode));
    }
    /**
     * description: hmiRequestStartEACall:          errorCode: Type='eErrorCode' Description='This
     *   is the                          return value of the method call '             
     *                This method can be used by HMI to start the EA call when user
     *   selects "NO" in             cancel confirmation pop up.
     * author: KHegde
     */
    void EACallDBusProxy::hmiRequestStartEACall(CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::assistcall::EACallTypedefs::eErrorCode &_errorCode, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<::v1::com::harman::assistcall::EACallTypedefs::eErrorCode, CommonAPI::EmptyDeployment> deploy_errorCode(static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v1::com::harman::assistcall::EACallTypedefs::eErrorCode,CommonAPI::EmptyDeployment>
            >
        	>::callMethodWithReply(
        *this,
        "hmiRequestStartEACall",
        "",
(_info ? _info : &CommonAPI::DBus::defaultCallInfo),
_internalCallStatus,
deploy_errorCode);
_errorCode = deploy_errorCode.getValue();
}
    std::future<CommonAPI::CallStatus> EACallDBusProxy::hmiRequestStartEACallAsync(HmiRequestStartEACallAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<::v1::com::harman::assistcall::EACallTypedefs::eErrorCode, CommonAPI::EmptyDeployment> deploy_errorCode(static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        return CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v1::com::harman::assistcall::EACallTypedefs::eErrorCode,CommonAPI::EmptyDeployment>
            >
        	>::callMethodAsync(
        *this,
        "hmiRequestStartEACall",
        "",
        (_info ? _info : &CommonAPI::DBus::defaultCallInfo),
        [_callback] (CommonAPI::CallStatus _internalCallStatus, CommonAPI::Deployable<::v1::com::harman::assistcall::EACallTypedefs::eErrorCode, CommonAPI::EmptyDeployment> _errorCode) {
        	if (_callback)
        		_callback(_internalCallStatus, _errorCode.getValue());
        },
        std::make_tuple(deploy_errorCode));
    }


void EACallDBusProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
          ownVersionMajor = 1;
          ownVersionMinor = 0;
      }

      } // namespace assistcall
      } // namespace harman
      } // namespace com
      } // namespace v1
