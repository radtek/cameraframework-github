/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by Voice CodeGen Version: R1_v1.3.0
* generated on: Tue Mar 07 13:22:52 CST 2017
*/

#ifndef V0_ORG_HARMAN_FORD_NAVI_TYPES_DBUS_DEPLOYMENT_HPP_
#define V0_ORG_HARMAN_FORD_NAVI_TYPES_DBUS_DEPLOYMENT_HPP_

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif
#include <CommonAPI/DBus/DBusDeployment.hpp>
#undef COMMONAPI_INTERNAL_COMPILATION

namespace v0 {
namespace org {
namespace harman {
namespace ford {
namespace navi_types_ {

// typecollection-specific deployment types
typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> TCU_Request_Signals_2_structDeployment_t;

typedef CommonAPI::EmptyDeployment GPS_Track_D_Rq_enumDeployment_t;

typedef CommonAPI::EmptyDeployment APIM_SwPartNo_D_Rq_enumDeployment_t;

typedef CommonAPI::EmptyDeployment TCU_Init_Actvtn_Rq_enumDeployment_t;

typedef CommonAPI::EmptyDeployment TCU_Final_Actvtn_Rq_enumDeployment_t;


// typecollection-specific deployments

} // namespace navi_types_
} // namespace ford
} // namespace harman
} // namespace org
} // namespace v0

#endif // V0_ORG_HARMAN_FORD_NAVI_TYPES_DBUS_DEPLOYMENT_HPP_
