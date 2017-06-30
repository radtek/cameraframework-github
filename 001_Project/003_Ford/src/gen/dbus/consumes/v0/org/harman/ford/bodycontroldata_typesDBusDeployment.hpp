/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by Voice CodeGen Version: R1_v1.3.0
* generated on: Tue Mar 07 13:22:52 CST 2017
*/

#ifndef V0_ORG_HARMAN_FORD_BODYCONTROLDATA_TYPES_DBUS_DEPLOYMENT_HPP_
#define V0_ORG_HARMAN_FORD_BODYCONTROLDATA_TYPES_DBUS_DEPLOYMENT_HPP_

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif
#include <CommonAPI/DBus/DBusDeployment.hpp>
#undef COMMONAPI_INTERNAL_COMPILATION

namespace v0 {
namespace org {
namespace harman {
namespace ford {
namespace bodycontroldata_types_ {

// typecollection-specific deployment types
typedef CommonAPI::EmptyDeployment VehYaw_W_Actl_UB_enumDeployment_t;

typedef CommonAPI::EmptyDeployment VehYaw_W_Actl_enumDeployment_t;

typedef CommonAPI::EmptyDeployment StabCtlBrkActv_B_Actl_enumDeployment_t;

typedef CommonAPI::EmptyDeployment GearLvrPos_D_Actl_enumDeployment_t;

typedef CommonAPI::EmptyDeployment GearLvrPos_D_Actl_UB_enumDeployment_t;

typedef CommonAPI::EmptyDeployment FactoryReset_Rq_enumDeployment_t;

typedef CommonAPI::EmptyDeployment TCU_ESN_D_Rq_enumDeployment_t;

typedef CommonAPI::EmptyDeployment TCU_Sftwr_Update_D_St_enumDeployment_t;

typedef CommonAPI::EmptyDeployment Parklamp_Status_enumDeployment_t;

typedef CommonAPI::EmptyDeployment Day_Night_Status_enumDeployment_t;

typedef CommonAPI::EmptyDeployment Backlit_LED_Status_enumDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> Dimming_Lvl_structDeployment_t;

typedef CommonAPI::EmptyDeployment Dimming_Lvl_enumDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> Litval_structDeployment_t;

typedef CommonAPI::EmptyDeployment Litval_enumDeployment_t;

typedef CommonAPI::EmptyDeployment TCMode_enumDeployment_t;

typedef CommonAPI::EmptyDeployment DistanceBarSetting_enumDeployment_t;

typedef CommonAPI::EmptyDeployment PwPck_D_Stat_UB_enumDeployment_t;

typedef CommonAPI::EmptyDeployment Outside_Air_Temp_Stat_UB_enumDeployment_t;

typedef CommonAPI::EmptyDeployment RstrnImpactEvntStatus_enumDeployment_t;

typedef CommonAPI::EmptyDeployment VehVActlEng_D_Qf_enumDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> Veh_V_ActlEng_structDeployment_t;

typedef CommonAPI::EmptyDeployment HMI_HMIMode_St_enumDeployment_t;

typedef CommonAPI::EmptyDeployment TCU_Init_Actvtn_St_enumDeployment_t;

typedef CommonAPI::EmptyDeployment TCU_Final_Actvtn_St_enumDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> GWM_Send_Signals_7_HS3_sig_5_structDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> Body_Info_1_HS3_sig_0_structDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> Vehicle_Status_Msg_sig_0_structDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> BodyInformation_3_sig_1_structDeployment_t;


// typecollection-specific deployments

} // namespace bodycontroldata_types_
} // namespace ford
} // namespace harman
} // namespace org
} // namespace v0

#endif // V0_ORG_HARMAN_FORD_BODYCONTROLDATA_TYPES_DBUS_DEPLOYMENT_HPP_
