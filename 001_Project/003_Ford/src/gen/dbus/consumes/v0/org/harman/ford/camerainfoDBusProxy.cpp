/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by Voice CodeGen Version: R1_v1.3.0
* generated on: Tue Mar 07 13:22:52 CST 2017
*/
#include <v0/org/harman/ford/camerainfoDBusProxy.hpp>

namespace v0 {
namespace org {
namespace harman {
namespace ford {

std::shared_ptr<CommonAPI::DBus::DBusProxy> createcamerainfoDBusProxy(
	const CommonAPI::DBus::DBusAddress &_address,
	const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection) {
	return std::make_shared<camerainfoDBusProxy>(_address, _connection);
}

INITIALIZER(registercamerainfoDBusProxy) {
     CommonAPI::DBus::Factory::get()->registerProxyCreateMethod(
		camerainfo::getInterface(),
		&createcamerainfoDBusProxy);
}

camerainfoDBusProxy::camerainfoDBusProxy(
	const CommonAPI::DBus::DBusAddress &_address,
	const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection)
	:	CommonAPI::DBus::DBusProxy(_address, _connection)
,		camraViewSplit_B_Rq_enum_(*this, "onCamraViewSplit_B_Rq_enumAttributeChanged", "setCamraViewSplit_B_Rq_enumAttribute", "i", "getCamraViewSplit_B_Rq_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		camraOvrlStat_D_Rq_enum_(*this, "onCamraOvrlStat_D_Rq_enumAttributeChanged", "setCamraOvrlStat_D_Rq_enumAttribute", "i", "getCamraOvrlStat_D_Rq_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		camraOvrlDyn_D_Rq_enum_(*this, "onCamraOvrlDyn_D_Rq_enumAttributeChanged", "setCamraOvrlDyn_D_Rq_enumAttribute", "i", "getCamraOvrlDyn_D_Rq_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		camraOvrlTow_D_Rq_enum_(*this, "onCamraOvrlTow_D_Rq_enumAttributeChanged", "setCamraOvrlTow_D_Rq_enumAttribute", "i", "getCamraOvrlTow_D_Rq_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		camraZoomMan_D_Rq_enum_(*this, "onCamraZoomMan_D_Rq_enumAttributeChanged", "setCamraZoomMan_D_Rq_enumAttribute", "i", "getCamraZoomMan_D_Rq_enumAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		vehCharacteristicSet2_HS3_(*this, "onVehCharacteristicSet2_HS3AttributeChanged", "(ii)", "getVehCharacteristicSet2_HS3Attribute", static_cast<::v0::org::harman::ford::camerainfo_types_::VehCharacteristicSet2_HS3_structDeployment_t*>(nullptr)),
		vehCharacteristicSet2_HS3_sig_0_(*this, "onVehCharacteristicSet2_HS3_sig_0AttributeChanged", "(ii)", "getVehCharacteristicSet2_HS3_sig_0Attribute", static_cast<::v0::org::harman::ford::camerainfo_types_::VehCharacteristicSet2_HS3_sig_0_structDeployment_t*>(nullptr)),
		vehCharacteristicSet2_HS3_sig_1_(*this, "onVehCharacteristicSet2_HS3_sig_1AttributeChanged", "(ii)", "getVehCharacteristicSet2_HS3_sig_1Attribute", static_cast<::v0::org::harman::ford::camerainfo_types_::VehCharacteristicSet2_HS3_sig_1_structDeployment_t*>(nullptr)),
		vehCharacteristicSet2_HS3_sig_2_(*this, "onVehCharacteristicSet2_HS3_sig_2AttributeChanged", "(ii)", "getVehCharacteristicSet2_HS3_sig_2Attribute", static_cast<::v0::org::harman::ford::camerainfo_types_::VehCharacteristicSet2_HS3_sig_2_structDeployment_t*>(nullptr)),
		vehCharacteristicSet2_HS3_sig_3_(*this, "onVehCharacteristicSet2_HS3_sig_3AttributeChanged", "(ii)", "getVehCharacteristicSet2_HS3_sig_3Attribute", static_cast<::v0::org::harman::ford::camerainfo_types_::VehCharacteristicSet2_HS3_sig_3_structDeployment_t*>(nullptr)),
		vehCharacteristicSet2_HS3_sig_4_(*this, "onVehCharacteristicSet2_HS3_sig_4AttributeChanged", "(ii)", "getVehCharacteristicSet2_HS3_sig_4Attribute", static_cast<::v0::org::harman::ford::camerainfo_types_::VehCharacteristicSet2_HS3_sig_4_structDeployment_t*>(nullptr)),
		pAC_Send_Signals_sig_0_(*this, "onPAC_Send_Signals_sig_0AttributeChanged", "(ii)", "getPAC_Send_Signals_sig_0Attribute", static_cast<::v0::org::harman::ford::camerainfo_types_::PAC_Send_Signals_sig_0_structDeployment_t*>(nullptr))
{
}

      camerainfoDBusProxy::CamraViewSplit_B_Rq_enumAttribute& camerainfoDBusProxy::getCamraViewSplit_B_Rq_enumAttribute() {
          return camraViewSplit_B_Rq_enum_;
      }
      camerainfoDBusProxy::CamraOvrlStat_D_Rq_enumAttribute& camerainfoDBusProxy::getCamraOvrlStat_D_Rq_enumAttribute() {
          return camraOvrlStat_D_Rq_enum_;
      }
      camerainfoDBusProxy::CamraOvrlDyn_D_Rq_enumAttribute& camerainfoDBusProxy::getCamraOvrlDyn_D_Rq_enumAttribute() {
          return camraOvrlDyn_D_Rq_enum_;
      }
      camerainfoDBusProxy::CamraOvrlTow_D_Rq_enumAttribute& camerainfoDBusProxy::getCamraOvrlTow_D_Rq_enumAttribute() {
          return camraOvrlTow_D_Rq_enum_;
      }
      camerainfoDBusProxy::CamraZoomMan_D_Rq_enumAttribute& camerainfoDBusProxy::getCamraZoomMan_D_Rq_enumAttribute() {
          return camraZoomMan_D_Rq_enum_;
      }
      camerainfoDBusProxy::VehCharacteristicSet2_HS3Attribute& camerainfoDBusProxy::getVehCharacteristicSet2_HS3Attribute() {
          return vehCharacteristicSet2_HS3_;
      }
      camerainfoDBusProxy::VehCharacteristicSet2_HS3_sig_0Attribute& camerainfoDBusProxy::getVehCharacteristicSet2_HS3_sig_0Attribute() {
          return vehCharacteristicSet2_HS3_sig_0_;
      }
      camerainfoDBusProxy::VehCharacteristicSet2_HS3_sig_1Attribute& camerainfoDBusProxy::getVehCharacteristicSet2_HS3_sig_1Attribute() {
          return vehCharacteristicSet2_HS3_sig_1_;
      }
      camerainfoDBusProxy::VehCharacteristicSet2_HS3_sig_2Attribute& camerainfoDBusProxy::getVehCharacteristicSet2_HS3_sig_2Attribute() {
          return vehCharacteristicSet2_HS3_sig_2_;
      }
      camerainfoDBusProxy::VehCharacteristicSet2_HS3_sig_3Attribute& camerainfoDBusProxy::getVehCharacteristicSet2_HS3_sig_3Attribute() {
          return vehCharacteristicSet2_HS3_sig_3_;
      }
      camerainfoDBusProxy::VehCharacteristicSet2_HS3_sig_4Attribute& camerainfoDBusProxy::getVehCharacteristicSet2_HS3_sig_4Attribute() {
          return vehCharacteristicSet2_HS3_sig_4_;
      }
      camerainfoDBusProxy::PAC_Send_Signals_sig_0Attribute& camerainfoDBusProxy::getPAC_Send_Signals_sig_0Attribute() {
          return pAC_Send_Signals_sig_0_;
      }

    


void camerainfoDBusProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
          ownVersionMajor = 0;
          ownVersionMinor = 1;
      }

      } // namespace ford
      } // namespace harman
      } // namespace org
      } // namespace v0
