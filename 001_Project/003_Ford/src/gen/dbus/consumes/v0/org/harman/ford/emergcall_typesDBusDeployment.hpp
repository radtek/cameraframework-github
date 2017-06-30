/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by Voice CodeGen Version: R1_v1.3.0
* generated on: Tue Mar 07 13:22:52 CST 2017
*/

#ifndef V0_ORG_HARMAN_FORD_EMERGCALL_TYPES_DBUS_DEPLOYMENT_HPP_
#define V0_ORG_HARMAN_FORD_EMERGCALL_TYPES_DBUS_DEPLOYMENT_HPP_

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif
#include <CommonAPI/DBus/DBusDeployment.hpp>
#undef COMMONAPI_INTERNAL_COMPILATION

namespace v0 {
namespace org {
namespace harman {
namespace ford {
namespace emergcall_types_ {

// typecollection-specific deployment types
typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> EmgcyCallMute_D_Stat_structDeployment_t;

typedef CommonAPI::EmptyDeployment EmgcyCallMute_D_Stat_enumDeployment_t;

typedef CommonAPI::EmptyDeployment SpkrStdCntr_D_Stat_enumDeployment_t;

typedef CommonAPI::EmptyDeployment SpkrStdLeft_D_Stat_enumDeployment_t;

typedef CommonAPI::EmptyDeployment SpkrStdRight_D_Stat_enumDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> EmgcyCall_D_Stat_structDeployment_t;

typedef CommonAPI::EmptyDeployment EmgcyCall_D_Stat_enumDeployment_t;

typedef CommonAPI::EmptyDeployment EmgcyCallHmi_D_Stat_enumDeployment_t;


// typecollection-specific deployments

} // namespace emergcall_types_
} // namespace ford
} // namespace harman
} // namespace org
} // namespace v0

#endif // V0_ORG_HARMAN_FORD_EMERGCALL_TYPES_DBUS_DEPLOYMENT_HPP_
