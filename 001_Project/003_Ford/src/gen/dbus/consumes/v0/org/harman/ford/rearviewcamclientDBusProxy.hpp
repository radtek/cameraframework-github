/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by Voice CodeGen Version: R1_v1.3.0
* generated on: Tue Mar 07 13:22:52 CST 2017
*/
#ifndef V0_ORG_HARMAN_FORD_rearviewcamclient_DBUS_PROXY_HPP_
#define V0_ORG_HARMAN_FORD_rearviewcamclient_DBUS_PROXY_HPP_

#include <v0/org/harman/ford/rearviewcamclientProxyBase.hpp>
#include "v0/org/harman/ford/rearviewcamclientDBusDeployment.hpp"

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

class rearviewcamclientDBusProxy
    : virtual public rearviewcamclientProxyBase, 
      virtual public CommonAPI::DBus::DBusProxy {
public:
    rearviewcamclientDBusProxy(
        const CommonAPI::DBus::DBusAddress &_address,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection);

    virtual ~rearviewcamclientDBusProxy() { }

    virtual GearRvrse_D_ActlAttribute& getGearRvrse_D_ActlAttribute();




    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

private:
   
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<GearRvrse_D_ActlAttribute, ::v0::org::harman::ford::rearviewcamclient_types_::GearRvrse_D_Actl_structDeployment_t>> gearRvrse_D_Actl_;


};

} // namespace ford
} // namespace harman
} // namespace org
} // namespace v0

#endif // V0_ORG_HARMAN_FORD_rearviewcamclient_DBUS_PROXY_HPP_

