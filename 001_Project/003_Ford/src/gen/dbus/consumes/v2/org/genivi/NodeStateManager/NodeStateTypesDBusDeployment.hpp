/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by Voice CodeGen Version: R1_v1.3.0
* generated on: Tue Mar 07 13:22:52 CST 2017
*/

#ifndef V2_ORG_GENIVI_NODESTATEMANAGER_NODE_STATE_TYPES_DBUS_DEPLOYMENT_HPP_
#define V2_ORG_GENIVI_NODESTATEMANAGER_NODE_STATE_TYPES_DBUS_DEPLOYMENT_HPP_

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif
#include <CommonAPI/DBus/DBusDeployment.hpp>
#undef COMMONAPI_INTERNAL_COMPILATION

namespace v2 {
namespace org {
namespace genivi {
namespace NodeStateManager {
namespace NodeStateTypes_ {

// typecollection-specific deployment types
typedef CommonAPI::EmptyDeployment NsmErrorStatusDeployment_t;

typedef CommonAPI::EmptyDeployment NsmApplicationModeDeployment_t;

typedef CommonAPI::EmptyDeployment NsmRestartReasonDeployment_t;

typedef CommonAPI::EmptyDeployment NsmSeatDeployment_t;

typedef CommonAPI::EmptyDeployment NsmSessionStateDeployment_t;

typedef CommonAPI::EmptyDeployment NsmShutdownReasonDeployment_t;

typedef CommonAPI::EmptyDeployment NsmRunningReasonDeployment_t;

typedef CommonAPI::EmptyDeployment NsmNodeStateDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> NsmSessionDeployment_t;

typedef CommonAPI::EmptyDeployment NsmShutdownTypeDeployment_t;


// typecollection-specific deployments

} // namespace NodeStateTypes_
} // namespace NodeStateManager
} // namespace genivi
} // namespace org
} // namespace v2

#endif // V2_ORG_GENIVI_NODESTATEMANAGER_NODE_STATE_TYPES_DBUS_DEPLOYMENT_HPP_
