/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by Voice CodeGen Version: R1_v1.3.0
* generated on: Tue Mar 07 13:22:52 CST 2017
*/
#ifndef V0_ORG_HARMAN_FORD_rearviewcamclient_PROXY_HPP_
#define V0_ORG_HARMAN_FORD_rearviewcamclient_PROXY_HPP_

#include <v0/org/harman/ford/rearviewcamclientProxyBase.hpp>


#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/AttributeExtension.hpp>
#include <CommonAPI/Factory.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v0 {
namespace org {
namespace harman {
namespace ford {

template <typename ... _AttributeExtensions>
class rearviewcamclientProxy
    : virtual public rearviewcamclient, 
      virtual public rearviewcamclientProxyBase,
      virtual public _AttributeExtensions... {
public:
    rearviewcamclientProxy(std::shared_ptr<CommonAPI::Proxy> delegate);
    ~rearviewcamclientProxy();

    typedef rearviewcamclient InterfaceType;


    /**
     * description: No Information Available
     */
    /**
     * Returns the wrapper class that provides access to the attribute GearRvrse_D_Actl.
     */
    virtual GearRvrse_D_ActlAttribute& getGearRvrse_D_ActlAttribute() {
        return delegate_->getGearRvrse_D_ActlAttribute();
    }




    /**
     * Returns the CommonAPI address of the remote partner this proxy communicates with.
     */
    virtual const CommonAPI::Address &getAddress() const;

    /**
     * Returns true if the remote partner for this proxy is currently known to be available.
     */
    virtual bool isAvailable() const;

    /**
     * Returns true if the remote partner for this proxy is available.
     */
    virtual bool isAvailableBlocking() const;

    /**
     * Returns the wrapper class that is used to (de-)register for notifications about
     * the availability of the remote partner of this proxy.
     */
    virtual CommonAPI::ProxyStatusEvent& getProxyStatusEvent();

    /**
     * Returns the wrapper class that is used to access version information of the remote
     * partner of this proxy.
     */
    virtual CommonAPI::InterfaceVersionAttribute& getInterfaceVersionAttribute();

 private:
    std::shared_ptr<rearviewcamclientProxyBase> delegate_;
};

typedef rearviewcamclientProxy<> rearviewcamclientProxyDefault;

namespace rearviewcamclientExtensions {
    /**
     * description: No Information Available
     */
    template <template <typename > class _ExtensionType>
    class GearRvrse_D_ActlAttributeExtension {
     public:
        typedef _ExtensionType<rearviewcamclientProxyBase::GearRvrse_D_ActlAttribute> extension_type;
    
        static_assert(std::is_base_of<typename CommonAPI::AttributeExtension<rearviewcamclientProxyBase::GearRvrse_D_ActlAttribute>, extension_type>::value,
                      "Not CommonAPI Attribute Extension!");
    #ifdef WIN32
        GearRvrse_D_ActlAttributeExtension() {}
    #endif
    
        GearRvrse_D_ActlAttributeExtension(rearviewcamclientProxyBase& proxy): attributeExtension_(proxy.getGearRvrse_D_ActlAttribute()) {
        }
    
        inline extension_type& getGearRvrse_D_ActlAttributeExtension() {
            return attributeExtension_;
        }
    
     private:
        extension_type attributeExtension_;
    };

} // namespace rearviewcamclientExtensions

//
// rearviewcamclientProxy Implementation
//
template <typename ... _AttributeExtensions>
rearviewcamclientProxy<_AttributeExtensions...>::rearviewcamclientProxy(std::shared_ptr<CommonAPI::Proxy> delegate):
        _AttributeExtensions(*(std::dynamic_pointer_cast<rearviewcamclientProxyBase>(delegate)))...,
        delegate_(std::dynamic_pointer_cast<rearviewcamclientProxyBase>(delegate)) {
}

template <typename ... _AttributeExtensions>
rearviewcamclientProxy<_AttributeExtensions...>::~rearviewcamclientProxy() {
}


template <typename ... _AttributeExtensions>
const CommonAPI::Address &rearviewcamclientProxy<_AttributeExtensions...>::getAddress() const {
    return delegate_->getAddress();
}

template <typename ... _AttributeExtensions>
bool rearviewcamclientProxy<_AttributeExtensions...>::isAvailable() const {
    return delegate_->isAvailable();
}

template <typename ... _AttributeExtensions>
bool rearviewcamclientProxy<_AttributeExtensions...>::isAvailableBlocking() const {
    return delegate_->isAvailableBlocking();
}

template <typename ... _AttributeExtensions>
CommonAPI::ProxyStatusEvent& rearviewcamclientProxy<_AttributeExtensions...>::getProxyStatusEvent() {
    return delegate_->getProxyStatusEvent();
}

template <typename ... _AttributeExtensions>
CommonAPI::InterfaceVersionAttribute& rearviewcamclientProxy<_AttributeExtensions...>::getInterfaceVersionAttribute() {
    return delegate_->getInterfaceVersionAttribute();
}


} // namespace ford
} // namespace harman
} // namespace org
} // namespace v0

namespace CommonAPI {
template<template<typename > class _AttributeExtension>
struct DefaultAttributeProxyHelper<::v0::org::harman::ford::rearviewcamclientProxy,
    _AttributeExtension> {
    typedef typename ::v0::org::harman::ford::rearviewcamclientProxy<
            ::v0::org::harman::ford::rearviewcamclientExtensions::GearRvrse_D_ActlAttributeExtension<_AttributeExtension>
    > class_t;
};
}


// Compatibility
namespace v0_1 = v0;

#endif // V0_ORG_HARMAN_FORD_rearviewcamclient_PROXY_HPP_
