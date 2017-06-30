/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by Voice CodeGen Version: R1_v1.3.0
* generated on: Tue Mar 07 13:22:52 CST 2017
*/
#ifndef V0_ORG_HARMAN_FORD_bodycontroldata_DBUS_PROXY_HPP_
#define V0_ORG_HARMAN_FORD_bodycontroldata_DBUS_PROXY_HPP_

#include <v0/org/harman/ford/bodycontroldataProxyBase.hpp>
#include "v0/org/harman/ford/bodycontroldataDBusDeployment.hpp"

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/DBus/DBusAddress.hpp>
#include <CommonAPI/DBus/DBusFactory.hpp>
#include <CommonAPI/DBus/DBusProxy.hpp>
#include <CommonAPI/DBus/DBusAddressTranslator.hpp>
#include <CommonAPI/DBus/DBusAttribute.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

#include <string>

namespace v0 {
namespace org {
namespace harman {
namespace ford {

class bodycontroldataDBusProxy
    : virtual public bodycontroldataProxyBase, 
      virtual public CommonAPI::DBus::DBusProxy {
public:
    bodycontroldataDBusProxy(
        const CommonAPI::DBus::DBusAddress &_address,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection);

    virtual ~bodycontroldataDBusProxy() { }

    virtual RearDiffOil_Te_ActlAttribute& getRearDiffOil_Te_ActlAttribute();
    virtual FuelLvlWarn_D_ActlEngAttribute& getFuelLvlWarn_D_ActlEngAttribute();
    virtual FuelLvl_Pc_DsplyEngAttribute& getFuelLvl_Pc_DsplyEngAttribute();
    virtual StabCtlBrkActv_B_Actl_enumAttribute& getStabCtlBrkActv_B_Actl_enumAttribute();
    virtual FuelRange_L_DsplyAttribute& getFuelRange_L_DsplyAttribute();
    virtual LightAmbColor_No_ActlAttribute& getLightAmbColor_No_ActlAttribute();
    virtual LightAmbIntsty_No_ActlAttribute& getLightAmbIntsty_No_ActlAttribute();
    virtual FactoryReset_Rq_enumAttribute& getFactoryReset_Rq_enumAttribute();
    virtual TCU_ESN_D_Rq_enumAttribute& getTCU_ESN_D_Rq_enumAttribute();
    virtual TCU_Sftwr_Update_D_St_enumAttribute& getTCU_Sftwr_Update_D_St_enumAttribute();
    virtual Parklamp_Status_enumAttribute& getParklamp_Status_enumAttribute();
    virtual Day_Night_Status_enumAttribute& getDay_Night_Status_enumAttribute();
    virtual Backlit_LED_Status_enumAttribute& getBacklit_LED_Status_enumAttribute();
    virtual Dimming_LvlAttribute& getDimming_LvlAttribute();
    virtual LitvalAttribute& getLitvalAttribute();
    virtual ApedPos_Pc_ActlArbAttribute& getApedPos_Pc_ActlArbAttribute();
    virtual EngAout_N_ActlAttribute& getEngAout_N_ActlAttribute();
    virtual TCMode_enumAttribute& getTCMode_enumAttribute();
    virtual FuelFlw_Vl_DsplyAttribute& getFuelFlw_Vl_DsplyAttribute();
    virtual WhlRotatFr_No_CntAttribute& getWhlRotatFr_No_CntAttribute();
    virtual WhlRotatFl_No_CntAttribute& getWhlRotatFl_No_CntAttribute();
    virtual WhlRotatRr_No_CntAttribute& getWhlRotatRr_No_CntAttribute();
    virtual WhlRotatRl_No_CntAttribute& getWhlRotatRl_No_CntAttribute();
    virtual WhlDirRr_D_ActlAttribute& getWhlDirRr_D_ActlAttribute();
    virtual WhlDirFl_D_ActlAttribute& getWhlDirFl_D_ActlAttribute();
    virtual WhlDirFr_D_ActlAttribute& getWhlDirFr_D_ActlAttribute();
    virtual WhlDirRl_D_ActlAttribute& getWhlDirRl_D_ActlAttribute();
    virtual DistanceBarSetting_enumAttribute& getDistanceBarSetting_enumAttribute();
    virtual RstrnImpactEvntStatus_enumAttribute& getRstrnImpactEvntStatus_enumAttribute();
    virtual VehVActlEng_D_Qf_enumAttribute& getVehVActlEng_D_Qf_enumAttribute();
    virtual Veh_V_ActlEngAttribute& getVeh_V_ActlEngAttribute();
    virtual HMI_HMIMode_St_enumAttribute& getHMI_HMIMode_St_enumAttribute();
    virtual LightAmbColor_No_RqAttribute& getLightAmbColor_No_RqAttribute();
    virtual LightAmbIntsty_No_RqAttribute& getLightAmbIntsty_No_RqAttribute();
    virtual TCU_Init_Actvtn_St_enumAttribute& getTCU_Init_Actvtn_St_enumAttribute();
    virtual TCU_Final_Actvtn_St_enumAttribute& getTCU_Final_Actvtn_St_enumAttribute();
    virtual GWM_Send_Signals_7_HS3_sig_5Attribute& getGWM_Send_Signals_7_HS3_sig_5Attribute();
    virtual Body_Info_1_HS3_sig_0Attribute& getBody_Info_1_HS3_sig_0Attribute();
    virtual Vehicle_Status_Msg_sig_0Attribute& getVehicle_Status_Msg_sig_0Attribute();
    virtual BodyInformation_3_sig_1Attribute& getBodyInformation_3_sig_1Attribute();




    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

private:
   
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<RearDiffOil_Te_ActlAttribute>> rearDiffOil_Te_Actl_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<FuelLvlWarn_D_ActlEngAttribute>> fuelLvlWarn_D_ActlEng_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<FuelLvl_Pc_DsplyEngAttribute>> fuelLvl_Pc_DsplyEng_;
    class DBusstabCtlBrkActv_B_Actl_enum_Attribute : public CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<StabCtlBrkActv_B_Actl_enumAttribute>> {
    public:
    template <typename... _A>
    	DBusstabCtlBrkActv_B_Actl_enum_Attribute(DBusProxy &_proxy,
    		_A ... arguments)
    		: CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<StabCtlBrkActv_B_Actl_enumAttribute>>(
    			_proxy, arguments...) {}
    };
    DBusstabCtlBrkActv_B_Actl_enum_Attribute stabCtlBrkActv_B_Actl_enum_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<FuelRange_L_DsplyAttribute>> fuelRange_L_Dsply_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<LightAmbColor_No_ActlAttribute>> lightAmbColor_No_Actl_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<LightAmbIntsty_No_ActlAttribute>> lightAmbIntsty_No_Actl_;
    class DBusfactoryReset_Rq_enum_Attribute : public CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<FactoryReset_Rq_enumAttribute>> {
    public:
    template <typename... _A>
    	DBusfactoryReset_Rq_enum_Attribute(DBusProxy &_proxy,
    		_A ... arguments)
    		: CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<FactoryReset_Rq_enumAttribute>>(
    			_proxy, arguments...) {}
    void setValue(const ::v0::org::harman::ford::bodycontroldata_types::FactoryReset_Rq_enum& requestValue,
    	CommonAPI::CallStatus& callStatus,
    	::v0::org::harman::ford::bodycontroldata_types::FactoryReset_Rq_enum& responseValue,
    	const CommonAPI::CallInfo *_info = nullptr) {
    		// validate input parameters
    		if (!requestValue.validate()) {
    			callStatus = CommonAPI::CallStatus::INVALID_VALUE;
    			return;
    		}
    		// call parent function if ok
    		CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<FactoryReset_Rq_enumAttribute>>::setValue(requestValue, callStatus, responseValue, _info);
    	}
    std::future<CommonAPI::CallStatus> setValueAsync(const ::v0::org::harman::ford::bodycontroldata_types::FactoryReset_Rq_enum& requestValue,
    	std::function<void(const CommonAPI::CallStatus &, ::v0::org::harman::ford::bodycontroldata_types::FactoryReset_Rq_enum)> _callback,
    	const CommonAPI::CallInfo *_info) {
    		// validate input parameters
    		if (!requestValue.validate()) {
    			::v0::org::harman::ford::bodycontroldata_types::FactoryReset_Rq_enum _returnvalue;
    			_callback(CommonAPI::CallStatus::INVALID_VALUE, _returnvalue);
    			std::promise<CommonAPI::CallStatus> promise;
    			promise.set_value(CommonAPI::CallStatus::INVALID_VALUE);
    			return promise.get_future();            				
    		}
    		// call parent function if ok
    		return CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<FactoryReset_Rq_enumAttribute>>::setValueAsync(requestValue, _callback, _info);
    	}
    };
    DBusfactoryReset_Rq_enum_Attribute factoryReset_Rq_enum_;
    class DBustCU_ESN_D_Rq_enum_Attribute : public CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<TCU_ESN_D_Rq_enumAttribute>> {
    public:
    template <typename... _A>
    	DBustCU_ESN_D_Rq_enum_Attribute(DBusProxy &_proxy,
    		_A ... arguments)
    		: CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<TCU_ESN_D_Rq_enumAttribute>>(
    			_proxy, arguments...) {}
    void setValue(const ::v0::org::harman::ford::bodycontroldata_types::TCU_ESN_D_Rq_enum& requestValue,
    	CommonAPI::CallStatus& callStatus,
    	::v0::org::harman::ford::bodycontroldata_types::TCU_ESN_D_Rq_enum& responseValue,
    	const CommonAPI::CallInfo *_info = nullptr) {
    		// validate input parameters
    		if (!requestValue.validate()) {
    			callStatus = CommonAPI::CallStatus::INVALID_VALUE;
    			return;
    		}
    		// call parent function if ok
    		CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<TCU_ESN_D_Rq_enumAttribute>>::setValue(requestValue, callStatus, responseValue, _info);
    	}
    std::future<CommonAPI::CallStatus> setValueAsync(const ::v0::org::harman::ford::bodycontroldata_types::TCU_ESN_D_Rq_enum& requestValue,
    	std::function<void(const CommonAPI::CallStatus &, ::v0::org::harman::ford::bodycontroldata_types::TCU_ESN_D_Rq_enum)> _callback,
    	const CommonAPI::CallInfo *_info) {
    		// validate input parameters
    		if (!requestValue.validate()) {
    			::v0::org::harman::ford::bodycontroldata_types::TCU_ESN_D_Rq_enum _returnvalue;
    			_callback(CommonAPI::CallStatus::INVALID_VALUE, _returnvalue);
    			std::promise<CommonAPI::CallStatus> promise;
    			promise.set_value(CommonAPI::CallStatus::INVALID_VALUE);
    			return promise.get_future();            				
    		}
    		// call parent function if ok
    		return CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<TCU_ESN_D_Rq_enumAttribute>>::setValueAsync(requestValue, _callback, _info);
    	}
    };
    DBustCU_ESN_D_Rq_enum_Attribute tCU_ESN_D_Rq_enum_;
    class DBustCU_Sftwr_Update_D_St_enum_Attribute : public CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<TCU_Sftwr_Update_D_St_enumAttribute>> {
    public:
    template <typename... _A>
    	DBustCU_Sftwr_Update_D_St_enum_Attribute(DBusProxy &_proxy,
    		_A ... arguments)
    		: CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<TCU_Sftwr_Update_D_St_enumAttribute>>(
    			_proxy, arguments...) {}
    };
    DBustCU_Sftwr_Update_D_St_enum_Attribute tCU_Sftwr_Update_D_St_enum_;
    class DBusparklamp_Status_enum_Attribute : public CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<Parklamp_Status_enumAttribute>> {
    public:
    template <typename... _A>
    	DBusparklamp_Status_enum_Attribute(DBusProxy &_proxy,
    		_A ... arguments)
    		: CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<Parklamp_Status_enumAttribute>>(
    			_proxy, arguments...) {}
    };
    DBusparklamp_Status_enum_Attribute parklamp_Status_enum_;
    class DBusday_Night_Status_enum_Attribute : public CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<Day_Night_Status_enumAttribute>> {
    public:
    template <typename... _A>
    	DBusday_Night_Status_enum_Attribute(DBusProxy &_proxy,
    		_A ... arguments)
    		: CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<Day_Night_Status_enumAttribute>>(
    			_proxy, arguments...) {}
    };
    DBusday_Night_Status_enum_Attribute day_Night_Status_enum_;
    class DBusbacklit_LED_Status_enum_Attribute : public CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<Backlit_LED_Status_enumAttribute>> {
    public:
    template <typename... _A>
    	DBusbacklit_LED_Status_enum_Attribute(DBusProxy &_proxy,
    		_A ... arguments)
    		: CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<Backlit_LED_Status_enumAttribute>>(
    			_proxy, arguments...) {}
    };
    DBusbacklit_LED_Status_enum_Attribute backlit_LED_Status_enum_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<Dimming_LvlAttribute, ::v0::org::harman::ford::bodycontroldata_types_::Dimming_Lvl_structDeployment_t>> dimming_Lvl_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<LitvalAttribute, ::v0::org::harman::ford::bodycontroldata_types_::Litval_structDeployment_t>> litval_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<ApedPos_Pc_ActlArbAttribute>> apedPos_Pc_ActlArb_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<EngAout_N_ActlAttribute>> engAout_N_Actl_;
    class DBustCMode_enum_Attribute : public CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<TCMode_enumAttribute>> {
    public:
    template <typename... _A>
    	DBustCMode_enum_Attribute(DBusProxy &_proxy,
    		_A ... arguments)
    		: CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<TCMode_enumAttribute>>(
    			_proxy, arguments...) {}
    };
    DBustCMode_enum_Attribute tCMode_enum_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<FuelFlw_Vl_DsplyAttribute>> fuelFlw_Vl_Dsply_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<WhlRotatFr_No_CntAttribute>> whlRotatFr_No_Cnt_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<WhlRotatFl_No_CntAttribute>> whlRotatFl_No_Cnt_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<WhlRotatRr_No_CntAttribute>> whlRotatRr_No_Cnt_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<WhlRotatRl_No_CntAttribute>> whlRotatRl_No_Cnt_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<WhlDirRr_D_ActlAttribute>> whlDirRr_D_Actl_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<WhlDirFl_D_ActlAttribute>> whlDirFl_D_Actl_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<WhlDirFr_D_ActlAttribute>> whlDirFr_D_Actl_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<WhlDirRl_D_ActlAttribute>> whlDirRl_D_Actl_;
    class DBusdistanceBarSetting_enum_Attribute : public CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<DistanceBarSetting_enumAttribute>> {
    public:
    template <typename... _A>
    	DBusdistanceBarSetting_enum_Attribute(DBusProxy &_proxy,
    		_A ... arguments)
    		: CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<DistanceBarSetting_enumAttribute>>(
    			_proxy, arguments...) {}
    void setValue(const ::v0::org::harman::ford::bodycontroldata_types::DistanceBarSetting_enum& requestValue,
    	CommonAPI::CallStatus& callStatus,
    	::v0::org::harman::ford::bodycontroldata_types::DistanceBarSetting_enum& responseValue,
    	const CommonAPI::CallInfo *_info = nullptr) {
    		// validate input parameters
    		if (!requestValue.validate()) {
    			callStatus = CommonAPI::CallStatus::INVALID_VALUE;
    			return;
    		}
    		// call parent function if ok
    		CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<DistanceBarSetting_enumAttribute>>::setValue(requestValue, callStatus, responseValue, _info);
    	}
    std::future<CommonAPI::CallStatus> setValueAsync(const ::v0::org::harman::ford::bodycontroldata_types::DistanceBarSetting_enum& requestValue,
    	std::function<void(const CommonAPI::CallStatus &, ::v0::org::harman::ford::bodycontroldata_types::DistanceBarSetting_enum)> _callback,
    	const CommonAPI::CallInfo *_info) {
    		// validate input parameters
    		if (!requestValue.validate()) {
    			::v0::org::harman::ford::bodycontroldata_types::DistanceBarSetting_enum _returnvalue;
    			_callback(CommonAPI::CallStatus::INVALID_VALUE, _returnvalue);
    			std::promise<CommonAPI::CallStatus> promise;
    			promise.set_value(CommonAPI::CallStatus::INVALID_VALUE);
    			return promise.get_future();            				
    		}
    		// call parent function if ok
    		return CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<DistanceBarSetting_enumAttribute>>::setValueAsync(requestValue, _callback, _info);
    	}
    };
    DBusdistanceBarSetting_enum_Attribute distanceBarSetting_enum_;
    class DBusrstrnImpactEvntStatus_enum_Attribute : public CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<RstrnImpactEvntStatus_enumAttribute>> {
    public:
    template <typename... _A>
    	DBusrstrnImpactEvntStatus_enum_Attribute(DBusProxy &_proxy,
    		_A ... arguments)
    		: CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<RstrnImpactEvntStatus_enumAttribute>>(
    			_proxy, arguments...) {}
    };
    DBusrstrnImpactEvntStatus_enum_Attribute rstrnImpactEvntStatus_enum_;
    class DBusvehVActlEng_D_Qf_enum_Attribute : public CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<VehVActlEng_D_Qf_enumAttribute>> {
    public:
    template <typename... _A>
    	DBusvehVActlEng_D_Qf_enum_Attribute(DBusProxy &_proxy,
    		_A ... arguments)
    		: CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<VehVActlEng_D_Qf_enumAttribute>>(
    			_proxy, arguments...) {}
    };
    DBusvehVActlEng_D_Qf_enum_Attribute vehVActlEng_D_Qf_enum_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<Veh_V_ActlEngAttribute, ::v0::org::harman::ford::bodycontroldata_types_::Veh_V_ActlEng_structDeployment_t>> veh_V_ActlEng_;
    class DBushMI_HMIMode_St_enum_Attribute : public CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<HMI_HMIMode_St_enumAttribute>> {
    public:
    template <typename... _A>
    	DBushMI_HMIMode_St_enum_Attribute(DBusProxy &_proxy,
    		_A ... arguments)
    		: CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<HMI_HMIMode_St_enumAttribute>>(
    			_proxy, arguments...) {}
    void setValue(const ::v0::org::harman::ford::bodycontroldata_types::HMI_HMIMode_St_enum& requestValue,
    	CommonAPI::CallStatus& callStatus,
    	::v0::org::harman::ford::bodycontroldata_types::HMI_HMIMode_St_enum& responseValue,
    	const CommonAPI::CallInfo *_info = nullptr) {
    		// validate input parameters
    		if (!requestValue.validate()) {
    			callStatus = CommonAPI::CallStatus::INVALID_VALUE;
    			return;
    		}
    		// call parent function if ok
    		CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<HMI_HMIMode_St_enumAttribute>>::setValue(requestValue, callStatus, responseValue, _info);
    	}
    std::future<CommonAPI::CallStatus> setValueAsync(const ::v0::org::harman::ford::bodycontroldata_types::HMI_HMIMode_St_enum& requestValue,
    	std::function<void(const CommonAPI::CallStatus &, ::v0::org::harman::ford::bodycontroldata_types::HMI_HMIMode_St_enum)> _callback,
    	const CommonAPI::CallInfo *_info) {
    		// validate input parameters
    		if (!requestValue.validate()) {
    			::v0::org::harman::ford::bodycontroldata_types::HMI_HMIMode_St_enum _returnvalue;
    			_callback(CommonAPI::CallStatus::INVALID_VALUE, _returnvalue);
    			std::promise<CommonAPI::CallStatus> promise;
    			promise.set_value(CommonAPI::CallStatus::INVALID_VALUE);
    			return promise.get_future();            				
    		}
    		// call parent function if ok
    		return CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<HMI_HMIMode_St_enumAttribute>>::setValueAsync(requestValue, _callback, _info);
    	}
    };
    DBushMI_HMIMode_St_enum_Attribute hMI_HMIMode_St_enum_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<LightAmbColor_No_RqAttribute>> lightAmbColor_No_Rq_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<LightAmbIntsty_No_RqAttribute>> lightAmbIntsty_No_Rq_;
    class DBustCU_Init_Actvtn_St_enum_Attribute : public CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<TCU_Init_Actvtn_St_enumAttribute>> {
    public:
    template <typename... _A>
    	DBustCU_Init_Actvtn_St_enum_Attribute(DBusProxy &_proxy,
    		_A ... arguments)
    		: CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<TCU_Init_Actvtn_St_enumAttribute>>(
    			_proxy, arguments...) {}
    void setValue(const ::v0::org::harman::ford::bodycontroldata_types::TCU_Init_Actvtn_St_enum& requestValue,
    	CommonAPI::CallStatus& callStatus,
    	::v0::org::harman::ford::bodycontroldata_types::TCU_Init_Actvtn_St_enum& responseValue,
    	const CommonAPI::CallInfo *_info = nullptr) {
    		// validate input parameters
    		if (!requestValue.validate()) {
    			callStatus = CommonAPI::CallStatus::INVALID_VALUE;
    			return;
    		}
    		// call parent function if ok
    		CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<TCU_Init_Actvtn_St_enumAttribute>>::setValue(requestValue, callStatus, responseValue, _info);
    	}
    std::future<CommonAPI::CallStatus> setValueAsync(const ::v0::org::harman::ford::bodycontroldata_types::TCU_Init_Actvtn_St_enum& requestValue,
    	std::function<void(const CommonAPI::CallStatus &, ::v0::org::harman::ford::bodycontroldata_types::TCU_Init_Actvtn_St_enum)> _callback,
    	const CommonAPI::CallInfo *_info) {
    		// validate input parameters
    		if (!requestValue.validate()) {
    			::v0::org::harman::ford::bodycontroldata_types::TCU_Init_Actvtn_St_enum _returnvalue;
    			_callback(CommonAPI::CallStatus::INVALID_VALUE, _returnvalue);
    			std::promise<CommonAPI::CallStatus> promise;
    			promise.set_value(CommonAPI::CallStatus::INVALID_VALUE);
    			return promise.get_future();            				
    		}
    		// call parent function if ok
    		return CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<TCU_Init_Actvtn_St_enumAttribute>>::setValueAsync(requestValue, _callback, _info);
    	}
    };
    DBustCU_Init_Actvtn_St_enum_Attribute tCU_Init_Actvtn_St_enum_;
    class DBustCU_Final_Actvtn_St_enum_Attribute : public CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<TCU_Final_Actvtn_St_enumAttribute>> {
    public:
    template <typename... _A>
    	DBustCU_Final_Actvtn_St_enum_Attribute(DBusProxy &_proxy,
    		_A ... arguments)
    		: CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<TCU_Final_Actvtn_St_enumAttribute>>(
    			_proxy, arguments...) {}
    void setValue(const ::v0::org::harman::ford::bodycontroldata_types::TCU_Final_Actvtn_St_enum& requestValue,
    	CommonAPI::CallStatus& callStatus,
    	::v0::org::harman::ford::bodycontroldata_types::TCU_Final_Actvtn_St_enum& responseValue,
    	const CommonAPI::CallInfo *_info = nullptr) {
    		// validate input parameters
    		if (!requestValue.validate()) {
    			callStatus = CommonAPI::CallStatus::INVALID_VALUE;
    			return;
    		}
    		// call parent function if ok
    		CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<TCU_Final_Actvtn_St_enumAttribute>>::setValue(requestValue, callStatus, responseValue, _info);
    	}
    std::future<CommonAPI::CallStatus> setValueAsync(const ::v0::org::harman::ford::bodycontroldata_types::TCU_Final_Actvtn_St_enum& requestValue,
    	std::function<void(const CommonAPI::CallStatus &, ::v0::org::harman::ford::bodycontroldata_types::TCU_Final_Actvtn_St_enum)> _callback,
    	const CommonAPI::CallInfo *_info) {
    		// validate input parameters
    		if (!requestValue.validate()) {
    			::v0::org::harman::ford::bodycontroldata_types::TCU_Final_Actvtn_St_enum _returnvalue;
    			_callback(CommonAPI::CallStatus::INVALID_VALUE, _returnvalue);
    			std::promise<CommonAPI::CallStatus> promise;
    			promise.set_value(CommonAPI::CallStatus::INVALID_VALUE);
    			return promise.get_future();            				
    		}
    		// call parent function if ok
    		return CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<TCU_Final_Actvtn_St_enumAttribute>>::setValueAsync(requestValue, _callback, _info);
    	}
    };
    DBustCU_Final_Actvtn_St_enum_Attribute tCU_Final_Actvtn_St_enum_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<GWM_Send_Signals_7_HS3_sig_5Attribute, ::v0::org::harman::ford::bodycontroldata_types_::GWM_Send_Signals_7_HS3_sig_5_structDeployment_t>> gWM_Send_Signals_7_HS3_sig_5_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<Body_Info_1_HS3_sig_0Attribute, ::v0::org::harman::ford::bodycontroldata_types_::Body_Info_1_HS3_sig_0_structDeployment_t>> body_Info_1_HS3_sig_0_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<Vehicle_Status_Msg_sig_0Attribute, ::v0::org::harman::ford::bodycontroldata_types_::Vehicle_Status_Msg_sig_0_structDeployment_t>> vehicle_Status_Msg_sig_0_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<BodyInformation_3_sig_1Attribute, ::v0::org::harman::ford::bodycontroldata_types_::BodyInformation_3_sig_1_structDeployment_t>> bodyInformation_3_sig_1_;


};

} // namespace ford
} // namespace harman
} // namespace org
} // namespace v0

#endif // V0_ORG_HARMAN_FORD_bodycontroldata_DBUS_PROXY_HPP_

