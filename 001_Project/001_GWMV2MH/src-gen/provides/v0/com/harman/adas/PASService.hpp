/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.201702211714.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.3.0
* generated on: Tue Aug 01 13:37:50 CST 2017
*/
#ifndef V0_COM_HARMAN_ADAS_PAS_SERVICE_HPP_
#define V0_COM_HARMAN_ADAS_PAS_SERVICE_HPP_




#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Types.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v0 {
namespace com {
namespace harman {
namespace adas {

class PASService {
public:
    virtual ~PASService() { }

    static inline const char* getInterface();
    static inline CommonAPI::Version getInterfaceVersion();
};

const char* PASService::getInterface() {
    return ("com.harman.adas.PASService");
}

CommonAPI::Version PASService::getInterfaceVersion() {
    return CommonAPI::Version(0, 1);
}


} // namespace adas
} // namespace harman
} // namespace com
} // namespace v0

namespace CommonAPI {
}


// Compatibility
namespace v0_1 = v0;

#endif // V0_COM_HARMAN_ADAS_PAS_SERVICE_HPP_