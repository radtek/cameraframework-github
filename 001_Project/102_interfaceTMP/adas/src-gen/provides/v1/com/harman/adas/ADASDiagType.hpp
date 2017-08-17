/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.201702211714.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.3.0
* generated on: Tue Aug 01 13:37:50 CST 2017
*/
#ifndef V1_COM_HARMAN_ADAS_ADAS_Diag_Type_HPP_
#define V1_COM_HARMAN_ADAS_ADAS_Diag_Type_HPP_



#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Types.hpp>
#include <cstdint>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace com {
namespace harman {
namespace adas {

struct ADASDiagType {
    
    struct enDiagTestState : CommonAPI::Enumeration<int32_t> {
        enum Literal : int32_t {
            e_TestStartSuccess = 0,
            e_TestStartError = 1
        };
        
        enDiagTestState() 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(Literal::e_TestStartSuccess)) {}
        enDiagTestState(Literal _literal) 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast<int32_t>(Literal::e_TestStartSuccess):
                case static_cast<int32_t>(Literal::e_TestStartError):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const enDiagTestState &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const enDiagTestState &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const enDiagTestState &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const enDiagTestState &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const enDiagTestState &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const enDiagTestState &_other) const { return (value_ > _other.value_); }
        
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast<int32_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast<int32_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast<int32_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast<int32_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast<int32_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast<int32_t>(_value)); }
    };



static inline const char* getTypeCollectionName() {
    static const char* typeCollectionName = "com.harman.adas.ADASDiagType";
    return typeCollectionName;
}

inline CommonAPI::Version getTypeCollectionVersion() {
    return CommonAPI::Version(1, 0);
}

}; // struct ADASDiagType

} // namespace adas
} // namespace harman
} // namespace com
} // namespace v1

namespace CommonAPI {
}


namespace std {
    //Hash for enDiagTestState
    template<>
    struct hash<::v1::com::harman::adas::ADASDiagType::enDiagTestState> {
        inline size_t operator()(const ::v1::com::harman::adas::ADASDiagType::enDiagTestState& enDiagTestState) const {
            return static_cast<int32_t>(enDiagTestState);
        }
    };
}


// Compatibility
namespace v1_0 = v1;

#endif // V1_COM_HARMAN_ADAS_ADAS_Diag_Type_HPP_