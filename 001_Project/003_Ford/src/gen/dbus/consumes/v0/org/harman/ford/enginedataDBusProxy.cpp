/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by Voice CodeGen Version: R1_v1.3.0
* generated on: Tue Mar 07 13:22:52 CST 2017
*/
#include <v0/org/harman/ford/enginedataDBusProxy.hpp>

namespace v0 {
namespace org {
namespace harman {
namespace ford {

std::shared_ptr<CommonAPI::DBus::DBusProxy> createenginedataDBusProxy(
	const CommonAPI::DBus::DBusAddress &_address,
	const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection) {
	return std::make_shared<enginedataDBusProxy>(_address, _connection);
}

INITIALIZER(registerenginedataDBusProxy) {
     CommonAPI::DBus::Factory::get()->registerProxyCreateMethod(
		enginedata::getInterface(),
		&createenginedataDBusProxy);
}

enginedataDBusProxy::enginedataDBusProxy(
	const CommonAPI::DBus::DBusAddress &_address,
	const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection)
	:	CommonAPI::DBus::DBusProxy(_address, _connection)
,		engMnfld_P_Actl_(*this, "onEngMnfld_P_ActlAttributeChanged", "q", "getEngMnfld_P_ActlAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		engOil_P_Actl_(*this, "onEngOil_P_ActlAttributeChanged", "q", "getEngOil_P_ActlAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		prkBrkStatus_(*this, "onPrkBrkStatusAttributeChanged", "(iy)", "getPrkBrkStatusAttribute", static_cast<::v0::org::harman::ford::enginedata_types_::PrkBrkStatus_structDeployment_t*>(nullptr)),
		absActv_B_Actl_enum_(*this, "onAbsActv_B_Actl_enumAttributeChanged", "i", "getAbsActv_B_Actl_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		factoryReset_St_enum_(*this, "onFactoryReset_St_enumAttributeChanged", "i", "getFactoryReset_St_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		drStatTgate_B_Actl_enum_(*this, "onDrStatTgate_B_Actl_enumAttributeChanged", "i", "getDrStatTgate_B_Actl_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		ignition_Status_enum_(*this, "onIgnition_Status_enumAttributeChanged", "i", "getIgnition_Status_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		ignKeyType_D_Actl_enum_(*this, "onIgnKeyType_D_Actl_enumAttributeChanged", "i", "getIgnKeyType_D_Actl_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		drStatRl_B_Actl_enum_(*this, "onDrStatRl_B_Actl_enumAttributeChanged", "i", "getDrStatRl_B_Actl_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		drStatRr_B_Actl_enum_(*this, "onDrStatRr_B_Actl_enumAttributeChanged", "i", "getDrStatRr_B_Actl_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		lifeCycMde_D_Actl_enum_(*this, "onLifeCycMde_D_Actl_enumAttributeChanged", "i", "getLifeCycMde_D_Actl_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		prkBrkActv_B_Actl_(*this, "onPrkBrkActv_B_ActlAttributeChanged", "(iy)", "getPrkBrkActv_B_ActlAttribute", static_cast<::v0::org::harman::ford::enginedata_types_::PrkBrkActv_B_Actl_structDeployment_t*>(nullptr)),
		delay_Accy_enum_(*this, "onDelay_Accy_enumAttributeChanged", "i", "getDelay_Accy_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		drStatDrv_B_Actl_enum_(*this, "onDrStatDrv_B_Actl_enumAttributeChanged", "i", "getDrStatDrv_B_Actl_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		pwPckTq_D_Stat_enum_(*this, "onPwPckTq_D_Stat_enumAttributeChanged", "i", "getPwPckTq_D_Stat_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		eng_D_Stat_enum_(*this, "onEng_D_Stat_enumAttributeChanged", "i", "getEng_D_Stat_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		trnAinTq_D_Qf_enum_(*this, "onTrnAinTq_D_Qf_enumAttributeChanged", "i", "getTrnAinTq_D_Qf_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		trnAout_W_ActlUnfilt_enum_(*this, "onTrnAout_W_ActlUnfilt_enumAttributeChanged", "i", "getTrnAout_W_ActlUnfilt_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		apedPosPcActl_D_Qf_enum_(*this, "onApedPosPcActl_D_Qf_enumAttributeChanged", "i", "getApedPosPcActl_D_Qf_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		engClnt_Te_Actl_(*this, "onEngClnt_Te_ActlAttributeChanged", "y", "getEngClnt_Te_ActlAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		engOil_Te_Actl_(*this, "onEngOil_Te_ActlAttributeChanged", "y", "getEngOil_Te_ActlAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		engAout_Tq_Actl_(*this, "onEngAout_Tq_ActlAttributeChanged", "q", "getEngAout_Tq_ActlAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		engAoutTqActl_D_Qf_enum_(*this, "onEngAoutTqActl_D_Qf_enumAttributeChanged", "i", "getEngAoutTqActl_D_Qf_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		odoCount_(*this, "onOdoCountAttributeChanged", "y", "getOdoCountAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		vehicleGGCCData_(*this, "onVehicleGGCCDataAttributeChanged", "t", "getVehicleGGCCDataAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		disp_VehUntTripCoUsrSel_enum_(*this, "onDisp_VehUntTripCoUsrSel_enumAttributeChanged", "setDisp_VehUntTripCoUsrSel_enumAttribute", "i", "getDisp_VehUntTripCoUsrSel_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		disp_VehUnitTempUsrSel_enum_(*this, "onDisp_VehUnitTempUsrSel_enumAttributeChanged", "setDisp_VehUnitTempUsrSel_enumAttribute", "i", "getDisp_VehUnitTempUsrSel_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		trnIpcDsplyGear_D_Actl_enum_(*this, "onTrnIpcDsplyGear_D_Actl_enumAttributeChanged", "i", "getTrnIpcDsplyGear_D_Actl_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		mc_VehUnitTempUsrSel_St_enum_(*this, "onMc_VehUnitTempUsrSel_St_enumAttributeChanged", "i", "getMc_VehUnitTempUsrSel_St_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		mc_VehUntTrpCoUsrSel_St_enum_(*this, "onMc_VehUntTrpCoUsrSel_St_enumAttributeChanged", "i", "getMc_VehUntTrpCoUsrSel_St_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		tire_Pressure_Data_DRW_HS3_(*this, "onTire_Pressure_Data_DRW_HS3AttributeChanged", "(ii)", "getTire_Pressure_Data_DRW_HS3Attribute", static_cast<::v0::org::harman::ford::enginedata_types_::Tire_Pressure_Data_DRW_HS3_structDeployment_t*>(nullptr)),
		tire_Pressure_Status_(*this, "onTire_Pressure_StatusAttributeChanged", "(iiiiiiiiyy)", "getTire_Pressure_StatusAttribute", static_cast<::v0::org::harman::ford::enginedata_types_::Tire_Pressure_Status_structDeployment_t*>(nullptr)),
		tire_Pressure_Data_HS3_(*this, "onTire_Pressure_Data_HS3AttributeChanged", "(iiii)", "getTire_Pressure_Data_HS3Attribute", static_cast<::v0::org::harman::ford::enginedata_types_::Tire_Pressure_Data_HS3_structDeployment_t*>(nullptr)),
		body_Info_sig_5_(*this, "onBody_Info_sig_5AttributeChanged", "(yi)", "getBody_Info_sig_5Attribute", static_cast<::v0::org::harman::ford::enginedata_types_::Body_Info_sig_5_structDeployment_t*>(nullptr)),
		brakeSnData_2_sig_0_(*this, "onBrakeSnData_2_sig_0AttributeChanged", "(ii)", "getBrakeSnData_2_sig_0Attribute", static_cast<::v0::org::harman::ford::enginedata_types_::BrakeSnData_2_sig_0_structDeployment_t*>(nullptr)),
		engineData_12_HS3_sig_2_(*this, "onEngineData_12_HS3_sig_2AttributeChanged", "(ii)", "getEngineData_12_HS3_sig_2Attribute", static_cast<::v0::org::harman::ford::enginedata_types_::EngineData_12_HS3_sig_2_structDeployment_t*>(nullptr)),
		gWM_Send_Signals_sig_0_(*this, "onGWM_Send_Signals_sig_0AttributeChanged", "(ii)", "getGWM_Send_Signals_sig_0Attribute", static_cast<::v0::org::harman::ford::enginedata_types_::GWM_Send_Signals_sig_0_structDeployment_t*>(nullptr)),
		trailerBrakeData_sig_0_(*this, "onTrailerBrakeData_sig_0AttributeChanged", "(ii)", "getTrailerBrakeData_sig_0Attribute", static_cast<::v0::org::harman::ford::enginedata_types_::TrailerBrakeData_sig_0_structDeployment_t*>(nullptr)),
		trailerBrakeData_sig_1_(*this, "onTrailerBrakeData_sig_1AttributeChanged", "(ii)", "getTrailerBrakeData_sig_1Attribute", static_cast<::v0::org::harman::ford::enginedata_types_::TrailerBrakeData_sig_1_structDeployment_t*>(nullptr))
{
}

      enginedataDBusProxy::EngMnfld_P_ActlAttribute& enginedataDBusProxy::getEngMnfld_P_ActlAttribute() {
          return engMnfld_P_Actl_;
      }
      enginedataDBusProxy::EngOil_P_ActlAttribute& enginedataDBusProxy::getEngOil_P_ActlAttribute() {
          return engOil_P_Actl_;
      }
      enginedataDBusProxy::PrkBrkStatusAttribute& enginedataDBusProxy::getPrkBrkStatusAttribute() {
          return prkBrkStatus_;
      }
      enginedataDBusProxy::AbsActv_B_Actl_enumAttribute& enginedataDBusProxy::getAbsActv_B_Actl_enumAttribute() {
          return absActv_B_Actl_enum_;
      }
      enginedataDBusProxy::FactoryReset_St_enumAttribute& enginedataDBusProxy::getFactoryReset_St_enumAttribute() {
          return factoryReset_St_enum_;
      }
      enginedataDBusProxy::DrStatTgate_B_Actl_enumAttribute& enginedataDBusProxy::getDrStatTgate_B_Actl_enumAttribute() {
          return drStatTgate_B_Actl_enum_;
      }
      enginedataDBusProxy::Ignition_Status_enumAttribute& enginedataDBusProxy::getIgnition_Status_enumAttribute() {
          return ignition_Status_enum_;
      }
      enginedataDBusProxy::IgnKeyType_D_Actl_enumAttribute& enginedataDBusProxy::getIgnKeyType_D_Actl_enumAttribute() {
          return ignKeyType_D_Actl_enum_;
      }
      enginedataDBusProxy::DrStatRl_B_Actl_enumAttribute& enginedataDBusProxy::getDrStatRl_B_Actl_enumAttribute() {
          return drStatRl_B_Actl_enum_;
      }
      enginedataDBusProxy::DrStatRr_B_Actl_enumAttribute& enginedataDBusProxy::getDrStatRr_B_Actl_enumAttribute() {
          return drStatRr_B_Actl_enum_;
      }
      enginedataDBusProxy::LifeCycMde_D_Actl_enumAttribute& enginedataDBusProxy::getLifeCycMde_D_Actl_enumAttribute() {
          return lifeCycMde_D_Actl_enum_;
      }
      enginedataDBusProxy::PrkBrkActv_B_ActlAttribute& enginedataDBusProxy::getPrkBrkActv_B_ActlAttribute() {
          return prkBrkActv_B_Actl_;
      }
      enginedataDBusProxy::Delay_Accy_enumAttribute& enginedataDBusProxy::getDelay_Accy_enumAttribute() {
          return delay_Accy_enum_;
      }
      enginedataDBusProxy::DrStatDrv_B_Actl_enumAttribute& enginedataDBusProxy::getDrStatDrv_B_Actl_enumAttribute() {
          return drStatDrv_B_Actl_enum_;
      }
      enginedataDBusProxy::PwPckTq_D_Stat_enumAttribute& enginedataDBusProxy::getPwPckTq_D_Stat_enumAttribute() {
          return pwPckTq_D_Stat_enum_;
      }
      enginedataDBusProxy::Eng_D_Stat_enumAttribute& enginedataDBusProxy::getEng_D_Stat_enumAttribute() {
          return eng_D_Stat_enum_;
      }
      enginedataDBusProxy::TrnAinTq_D_Qf_enumAttribute& enginedataDBusProxy::getTrnAinTq_D_Qf_enumAttribute() {
          return trnAinTq_D_Qf_enum_;
      }
      enginedataDBusProxy::TrnAout_W_ActlUnfilt_enumAttribute& enginedataDBusProxy::getTrnAout_W_ActlUnfilt_enumAttribute() {
          return trnAout_W_ActlUnfilt_enum_;
      }
      enginedataDBusProxy::ApedPosPcActl_D_Qf_enumAttribute& enginedataDBusProxy::getApedPosPcActl_D_Qf_enumAttribute() {
          return apedPosPcActl_D_Qf_enum_;
      }
      enginedataDBusProxy::EngClnt_Te_ActlAttribute& enginedataDBusProxy::getEngClnt_Te_ActlAttribute() {
          return engClnt_Te_Actl_;
      }
      enginedataDBusProxy::EngOil_Te_ActlAttribute& enginedataDBusProxy::getEngOil_Te_ActlAttribute() {
          return engOil_Te_Actl_;
      }
      enginedataDBusProxy::EngAout_Tq_ActlAttribute& enginedataDBusProxy::getEngAout_Tq_ActlAttribute() {
          return engAout_Tq_Actl_;
      }
      enginedataDBusProxy::EngAoutTqActl_D_Qf_enumAttribute& enginedataDBusProxy::getEngAoutTqActl_D_Qf_enumAttribute() {
          return engAoutTqActl_D_Qf_enum_;
      }
      enginedataDBusProxy::OdoCountAttribute& enginedataDBusProxy::getOdoCountAttribute() {
          return odoCount_;
      }
      enginedataDBusProxy::VehicleGGCCDataAttribute& enginedataDBusProxy::getVehicleGGCCDataAttribute() {
          return vehicleGGCCData_;
      }
      enginedataDBusProxy::Disp_VehUntTripCoUsrSel_enumAttribute& enginedataDBusProxy::getDisp_VehUntTripCoUsrSel_enumAttribute() {
          return disp_VehUntTripCoUsrSel_enum_;
      }
      enginedataDBusProxy::Disp_VehUnitTempUsrSel_enumAttribute& enginedataDBusProxy::getDisp_VehUnitTempUsrSel_enumAttribute() {
          return disp_VehUnitTempUsrSel_enum_;
      }
      enginedataDBusProxy::TrnIpcDsplyGear_D_Actl_enumAttribute& enginedataDBusProxy::getTrnIpcDsplyGear_D_Actl_enumAttribute() {
          return trnIpcDsplyGear_D_Actl_enum_;
      }
      enginedataDBusProxy::Mc_VehUnitTempUsrSel_St_enumAttribute& enginedataDBusProxy::getMc_VehUnitTempUsrSel_St_enumAttribute() {
          return mc_VehUnitTempUsrSel_St_enum_;
      }
      enginedataDBusProxy::Mc_VehUntTrpCoUsrSel_St_enumAttribute& enginedataDBusProxy::getMc_VehUntTrpCoUsrSel_St_enumAttribute() {
          return mc_VehUntTrpCoUsrSel_St_enum_;
      }
      enginedataDBusProxy::Tire_Pressure_Data_DRW_HS3Attribute& enginedataDBusProxy::getTire_Pressure_Data_DRW_HS3Attribute() {
          return tire_Pressure_Data_DRW_HS3_;
      }
      enginedataDBusProxy::Tire_Pressure_StatusAttribute& enginedataDBusProxy::getTire_Pressure_StatusAttribute() {
          return tire_Pressure_Status_;
      }
      enginedataDBusProxy::Tire_Pressure_Data_HS3Attribute& enginedataDBusProxy::getTire_Pressure_Data_HS3Attribute() {
          return tire_Pressure_Data_HS3_;
      }
      enginedataDBusProxy::Body_Info_sig_5Attribute& enginedataDBusProxy::getBody_Info_sig_5Attribute() {
          return body_Info_sig_5_;
      }
      enginedataDBusProxy::BrakeSnData_2_sig_0Attribute& enginedataDBusProxy::getBrakeSnData_2_sig_0Attribute() {
          return brakeSnData_2_sig_0_;
      }
      enginedataDBusProxy::EngineData_12_HS3_sig_2Attribute& enginedataDBusProxy::getEngineData_12_HS3_sig_2Attribute() {
          return engineData_12_HS3_sig_2_;
      }
      enginedataDBusProxy::GWM_Send_Signals_sig_0Attribute& enginedataDBusProxy::getGWM_Send_Signals_sig_0Attribute() {
          return gWM_Send_Signals_sig_0_;
      }
      enginedataDBusProxy::TrailerBrakeData_sig_0Attribute& enginedataDBusProxy::getTrailerBrakeData_sig_0Attribute() {
          return trailerBrakeData_sig_0_;
      }
      enginedataDBusProxy::TrailerBrakeData_sig_1Attribute& enginedataDBusProxy::getTrailerBrakeData_sig_1Attribute() {
          return trailerBrakeData_sig_1_;
      }

    


void enginedataDBusProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
          ownVersionMajor = 0;
          ownVersionMinor = 1;
      }

      } // namespace ford
      } // namespace harman
      } // namespace org
      } // namespace v0
