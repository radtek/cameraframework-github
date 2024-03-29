/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by Voice CodeGen Version: R1_v1.3.0
* generated on: Tue Mar 07 13:22:52 CST 2017
*/

#ifndef V0_ORG_HARMAN_FORD_AUDIO_TYPES_DBUS_DEPLOYMENT_HPP_
#define V0_ORG_HARMAN_FORD_AUDIO_TYPES_DBUS_DEPLOYMENT_HPP_

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif
#include <CommonAPI/DBus/DBusDeployment.hpp>
#undef COMMONAPI_INTERNAL_COMPILATION

namespace v0 {
namespace org {
namespace harman {
namespace ford {
namespace audio_types_ {

// typecollection-specific deployment types
typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> IPC_Infotainment_structDeployment_t;

typedef CommonAPI::EmptyDeployment IPC_New_Attn_Event_enumDeployment_t;

typedef CommonAPI::EmptyDeployment IPC_Attn_Info_Audio_enumDeployment_t;

typedef CommonAPI::EmptyDeployment BeltminderAudioMute_enumDeployment_t;

typedef CommonAPI::EmptyDeployment IPC_MyKeyVolLimit_St_enumDeployment_t;

typedef CommonAPI::EmptyDeployment Chime_Source_enumDeployment_t;

typedef CommonAPI::EmptyDeployment Power_Up_Chime_Modules_enumDeployment_t;


// typecollection-specific deployments

} // namespace audio_types_
} // namespace ford
} // namespace harman
} // namespace org
} // namespace v0

#endif // V0_ORG_HARMAN_FORD_AUDIO_TYPES_DBUS_DEPLOYMENT_HPP_
