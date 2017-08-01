/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.201702211714.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.3.0
* generated on: Tue Aug 01 13:37:50 CST 2017
*/
#ifndef V1_COM_HARMAN_ADAS_AVM_Base_Type_HPP_
#define V1_COM_HARMAN_ADAS_AVM_Base_Type_HPP_



#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Deployment.hpp>
#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Struct.hpp>
#include <CommonAPI/Types.hpp>
#include <cstdint>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace com {
namespace harman {
namespace adas {

struct AVMBaseType {
    
    struct enAVMStatus : CommonAPI::Enumeration<int32_t> {
        enum Literal : int32_t {
            e_AVM_NOT_CONFIGURED = 0,
            e_AVM_TOP_VIEW = 1,
            e_AVM_FRONT_VIEW = 2,
            e_AVM_REAR_VIEW = 3,
            e_AVM_RIGHT_VIEW = 4,
            e_AVM_LEFT_VIEW = 5,
            e_AVM_FRONT_RIGHT_VIEW = 6,
            e_AVM_FRONT_LEFT_VIEW = 7,
            e_AVM_REAR_RIGHT_VIEW = 8,
            e_AVM_REAR_LEFT_VIEW = 9,
            e_AVM_TOP_FRONT_VIEW = 10,
            e_AVM_TOP_REAR_VIEW = 11,
            e_AVM_TOP_RIGHT_VIEW = 12,
            e_AVM_TOP_LEFT_VIEW = 13,
            e_AVM_TOP_FRONT_RIGHT_VIEW = 14,
            e_AVM_TOP_FRONT_LEFT_VIEW = 15,
            e_AVM_TOP_REAR_RIGHT_VIEW = 16,
            e_AVM_TOP_REAR_LEFT_VIEW = 17,
            e_AVM_OFF_OVERSPEED = 18,
            e_AVM_OFF = 19,
            e_AVM_ERR = 20
        };
        
        enAVMStatus() 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(Literal::e_AVM_NOT_CONFIGURED)) {}
        enAVMStatus(Literal _literal) 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast<int32_t>(Literal::e_AVM_NOT_CONFIGURED):
                case static_cast<int32_t>(Literal::e_AVM_TOP_VIEW):
                case static_cast<int32_t>(Literal::e_AVM_FRONT_VIEW):
                case static_cast<int32_t>(Literal::e_AVM_REAR_VIEW):
                case static_cast<int32_t>(Literal::e_AVM_RIGHT_VIEW):
                case static_cast<int32_t>(Literal::e_AVM_LEFT_VIEW):
                case static_cast<int32_t>(Literal::e_AVM_FRONT_RIGHT_VIEW):
                case static_cast<int32_t>(Literal::e_AVM_FRONT_LEFT_VIEW):
                case static_cast<int32_t>(Literal::e_AVM_REAR_RIGHT_VIEW):
                case static_cast<int32_t>(Literal::e_AVM_REAR_LEFT_VIEW):
                case static_cast<int32_t>(Literal::e_AVM_TOP_FRONT_VIEW):
                case static_cast<int32_t>(Literal::e_AVM_TOP_REAR_VIEW):
                case static_cast<int32_t>(Literal::e_AVM_TOP_RIGHT_VIEW):
                case static_cast<int32_t>(Literal::e_AVM_TOP_LEFT_VIEW):
                case static_cast<int32_t>(Literal::e_AVM_TOP_FRONT_RIGHT_VIEW):
                case static_cast<int32_t>(Literal::e_AVM_TOP_FRONT_LEFT_VIEW):
                case static_cast<int32_t>(Literal::e_AVM_TOP_REAR_RIGHT_VIEW):
                case static_cast<int32_t>(Literal::e_AVM_TOP_REAR_LEFT_VIEW):
                case static_cast<int32_t>(Literal::e_AVM_OFF_OVERSPEED):
                case static_cast<int32_t>(Literal::e_AVM_OFF):
                case static_cast<int32_t>(Literal::e_AVM_ERR):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const enAVMStatus &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const enAVMStatus &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const enAVMStatus &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const enAVMStatus &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const enAVMStatus &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const enAVMStatus &_other) const { return (value_ > _other.value_); }
        
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast<int32_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast<int32_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast<int32_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast<int32_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast<int32_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast<int32_t>(_value)); }
    };
    
    struct enAVMViewMode : CommonAPI::Enumeration<int32_t> {
        enum Literal : int32_t {
            e_SET_OFF = 0,
            e_SET_TOP_VIEW = 1,
            e_SET_FRONT_VIEW = 2,
            e_SET_REAR_VIEW = 3,
            e_SET_RIGHT_VIEW = 4,
            e_SET_LEFT_VIEW = 5,
            e_SET_FRONT_RIGHT_VIEW = 6,
            e_SET_FRONT_LEFT_VIEW = 7,
            e_SET_REAR_RIGHT_VIEW = 8,
            e_SET_REAR_LEFT_VIEW = 9,
            e_SET_TOP_REAR_VIEW = 10,
            e_SET_TOP_FRONT_VIEW = 11,
            e_SET_TOP_RIGHT_VIEW = 12,
            e_SET_TOP_LEFT_VIEW = 13,
            e_SET_TOP_FRONT_RIGHT_VIEW = 14,
            e_SET_TOP_FRONT_LEFT_VIEW = 15,
            e_SET_TOP_REAR_RIGHT_VIEW = 16,
            e_SET_TOP_REAR_LEFT_VIEW = 17
        };
        
        enAVMViewMode() 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(Literal::e_SET_OFF)) {}
        enAVMViewMode(Literal _literal) 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast<int32_t>(Literal::e_SET_OFF):
                case static_cast<int32_t>(Literal::e_SET_TOP_VIEW):
                case static_cast<int32_t>(Literal::e_SET_FRONT_VIEW):
                case static_cast<int32_t>(Literal::e_SET_REAR_VIEW):
                case static_cast<int32_t>(Literal::e_SET_RIGHT_VIEW):
                case static_cast<int32_t>(Literal::e_SET_LEFT_VIEW):
                case static_cast<int32_t>(Literal::e_SET_FRONT_RIGHT_VIEW):
                case static_cast<int32_t>(Literal::e_SET_FRONT_LEFT_VIEW):
                case static_cast<int32_t>(Literal::e_SET_REAR_RIGHT_VIEW):
                case static_cast<int32_t>(Literal::e_SET_REAR_LEFT_VIEW):
                case static_cast<int32_t>(Literal::e_SET_TOP_REAR_VIEW):
                case static_cast<int32_t>(Literal::e_SET_TOP_FRONT_VIEW):
                case static_cast<int32_t>(Literal::e_SET_TOP_RIGHT_VIEW):
                case static_cast<int32_t>(Literal::e_SET_TOP_LEFT_VIEW):
                case static_cast<int32_t>(Literal::e_SET_TOP_FRONT_RIGHT_VIEW):
                case static_cast<int32_t>(Literal::e_SET_TOP_FRONT_LEFT_VIEW):
                case static_cast<int32_t>(Literal::e_SET_TOP_REAR_RIGHT_VIEW):
                case static_cast<int32_t>(Literal::e_SET_TOP_REAR_LEFT_VIEW):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const enAVMViewMode &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const enAVMViewMode &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const enAVMViewMode &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const enAVMViewMode &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const enAVMViewMode &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const enAVMViewMode &_other) const { return (value_ > _other.value_); }
        
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast<int32_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast<int32_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast<int32_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast<int32_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast<int32_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast<int32_t>(_value)); }
    };
    
    struct enAVMGuideLineMode : CommonAPI::Enumeration<int32_t> {
        enum Literal : int32_t {
            e_AVM_STATIC_GUIDELINE_OFF = 0,
            e_AVM_STATIC_GUIDELINE_REAR = 1,
            e_AVM_STATIC_GUIDELINE_FRONT = 2,
            e_AVM_STATIC_GUIDELINE_FRONT_REAR = 3,
            e_AVM_DYNAMIC_GUIDELINE_OFF = 4,
            e_AVM_DYNAMIC_GUIDELLINE_REAR = 5,
            e_AVM_DYNAMIC_GUIDELLINE_FRONT = 6,
            e_AVM_DYNAMIC_GUIDELINE_FRONT_REAR = 7
        };
        
        enAVMGuideLineMode() 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(Literal::e_AVM_STATIC_GUIDELINE_OFF)) {}
        enAVMGuideLineMode(Literal _literal) 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast<int32_t>(Literal::e_AVM_STATIC_GUIDELINE_OFF):
                case static_cast<int32_t>(Literal::e_AVM_STATIC_GUIDELINE_REAR):
                case static_cast<int32_t>(Literal::e_AVM_STATIC_GUIDELINE_FRONT):
                case static_cast<int32_t>(Literal::e_AVM_STATIC_GUIDELINE_FRONT_REAR):
                case static_cast<int32_t>(Literal::e_AVM_DYNAMIC_GUIDELINE_OFF):
                case static_cast<int32_t>(Literal::e_AVM_DYNAMIC_GUIDELLINE_REAR):
                case static_cast<int32_t>(Literal::e_AVM_DYNAMIC_GUIDELLINE_FRONT):
                case static_cast<int32_t>(Literal::e_AVM_DYNAMIC_GUIDELINE_FRONT_REAR):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const enAVMGuideLineMode &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const enAVMGuideLineMode &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const enAVMGuideLineMode &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const enAVMGuideLineMode &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const enAVMGuideLineMode &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const enAVMGuideLineMode &_other) const { return (value_ > _other.value_); }
        
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast<int32_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast<int32_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast<int32_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast<int32_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast<int32_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast<int32_t>(_value)); }
    };
    
    struct enAVMCamState : CommonAPI::Enumeration<int32_t> {
        enum Literal : int32_t {
            e_AVM_CAMERA_NOT_AVAILABLE = 0,
            e_AVM_CAMERA_SIGNAL_GOOD = 1,
            e_AVM_CAMERA_SIGNAL_LOST = 2
        };
        
        enAVMCamState() 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(Literal::e_AVM_CAMERA_NOT_AVAILABLE)) {}
        enAVMCamState(Literal _literal) 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast<int32_t>(Literal::e_AVM_CAMERA_NOT_AVAILABLE):
                case static_cast<int32_t>(Literal::e_AVM_CAMERA_SIGNAL_GOOD):
                case static_cast<int32_t>(Literal::e_AVM_CAMERA_SIGNAL_LOST):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const enAVMCamState &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const enAVMCamState &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const enAVMCamState &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const enAVMCamState &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const enAVMCamState &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const enAVMCamState &_other) const { return (value_ > _other.value_); }
        
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast<int32_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast<int32_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast<int32_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast<int32_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast<int32_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast<int32_t>(_value)); }
    };
    
    struct enAutoCaliState : CommonAPI::Enumeration<int32_t> {
        enum Literal : int32_t {
            e_AVM_AUTO_CALI_OFF = 0,
            e_AVM_AUTO_CALI_NOTAVALIABLE = 1,
            e_AVM_AUTO_CALI_RUNNING = 2,
            e_AVM_AUTO_CALI_SUCCESS = 3,
            e_AVM_AUTO_CALI_FAILED = 4,
            e_AVM_AUTO_CALI_IDLE = 5
        };
        
        enAutoCaliState() 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(Literal::e_AVM_AUTO_CALI_OFF)) {}
        enAutoCaliState(Literal _literal) 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast<int32_t>(Literal::e_AVM_AUTO_CALI_OFF):
                case static_cast<int32_t>(Literal::e_AVM_AUTO_CALI_NOTAVALIABLE):
                case static_cast<int32_t>(Literal::e_AVM_AUTO_CALI_RUNNING):
                case static_cast<int32_t>(Literal::e_AVM_AUTO_CALI_SUCCESS):
                case static_cast<int32_t>(Literal::e_AVM_AUTO_CALI_FAILED):
                case static_cast<int32_t>(Literal::e_AVM_AUTO_CALI_IDLE):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const enAutoCaliState &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const enAutoCaliState &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const enAutoCaliState &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const enAutoCaliState &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const enAutoCaliState &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const enAutoCaliState &_other) const { return (value_ > _other.value_); }
        
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast<int32_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast<int32_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast<int32_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast<int32_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast<int32_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast<int32_t>(_value)); }
    };
    
    struct enAutoCaliWorkModeAuto : CommonAPI::Enumeration<int32_t> {
        enum Literal : int32_t {
            e_AUTO_CALI_ON_AUTO = 0,
            e_AUTO_CALI_OFF_AUTO = 1
        };
        
        enAutoCaliWorkModeAuto() 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(Literal::e_AUTO_CALI_ON_AUTO)) {}
        enAutoCaliWorkModeAuto(Literal _literal) 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast<int32_t>(Literal::e_AUTO_CALI_ON_AUTO):
                case static_cast<int32_t>(Literal::e_AUTO_CALI_OFF_AUTO):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const enAutoCaliWorkModeAuto &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const enAutoCaliWorkModeAuto &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const enAutoCaliWorkModeAuto &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const enAutoCaliWorkModeAuto &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const enAutoCaliWorkModeAuto &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const enAutoCaliWorkModeAuto &_other) const { return (value_ > _other.value_); }
        
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast<int32_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast<int32_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast<int32_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast<int32_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast<int32_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast<int32_t>(_value)); }
    };
    
    struct enAutoCaliWorkModeManu : CommonAPI::Enumeration<int32_t> {
        enum Literal : int32_t {
            e_AUTO_CALI_ON_MANU = 0,
            e_AUTO_CALI_OFF_MANU = 1
        };
        
        enAutoCaliWorkModeManu() 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(Literal::e_AUTO_CALI_ON_MANU)) {}
        enAutoCaliWorkModeManu(Literal _literal) 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast<int32_t>(Literal::e_AUTO_CALI_ON_MANU):
                case static_cast<int32_t>(Literal::e_AUTO_CALI_OFF_MANU):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const enAutoCaliWorkModeManu &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const enAutoCaliWorkModeManu &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const enAutoCaliWorkModeManu &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const enAutoCaliWorkModeManu &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const enAutoCaliWorkModeManu &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const enAutoCaliWorkModeManu &_other) const { return (value_ > _other.value_); }
        
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast<int32_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast<int32_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast<int32_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast<int32_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast<int32_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast<int32_t>(_value)); }
    };
    struct stAVMCamState : CommonAPI::Struct<enAVMCamState, enAVMCamState, enAVMCamState, enAVMCamState> {
    	
    	stAVMCamState() {
    	}
    	stAVMCamState(const enAVMCamState &_Right_Cam, const enAVMCamState &_Left_Cam, const enAVMCamState &_Front_Cam, const enAVMCamState &_Rear_Cam)
    	{
    		std::get<0>(values_) = _Right_Cam;
    		std::get<1>(values_) = _Left_Cam;
    		std::get<2>(values_) = _Front_Cam;
    		std::get<3>(values_) = _Rear_Cam;
    	}
    	inline const enAVMCamState &getRight_Cam() const { return std::get<0>(values_); }
    	inline void setRight_Cam(const enAVMCamState &_value) { std::get<0>(values_) = _value; }
    	inline const enAVMCamState &getLeft_Cam() const { return std::get<1>(values_); }
    	inline void setLeft_Cam(const enAVMCamState &_value) { std::get<1>(values_) = _value; }
    	inline const enAVMCamState &getFront_Cam() const { return std::get<2>(values_); }
    	inline void setFront_Cam(const enAVMCamState &_value) { std::get<2>(values_) = _value; }
    	inline const enAVMCamState &getRear_Cam() const { return std::get<3>(values_); }
    	inline void setRear_Cam(const enAVMCamState &_value) { std::get<3>(values_) = _value; }
    	inline bool operator==(const stAVMCamState& _other) const {
                return (getRight_Cam() == _other.getRight_Cam() && getLeft_Cam() == _other.getLeft_Cam() && getFront_Cam() == _other.getFront_Cam() && getRear_Cam() == _other.getRear_Cam());
        }
    	inline bool operator!=(const stAVMCamState &_other) const {
    		return !((*this) == _other);
    	}
    
    };



static inline const char* getTypeCollectionName() {
    static const char* typeCollectionName = "com.harman.adas.AVMBaseType";
    return typeCollectionName;
}

inline CommonAPI::Version getTypeCollectionVersion() {
    return CommonAPI::Version(1, 0);
}

}; // struct AVMBaseType

} // namespace adas
} // namespace harman
} // namespace com
} // namespace v1

namespace CommonAPI {
}


namespace std {
    //Hash for enAVMStatus
    template<>
    struct hash<::v1::com::harman::adas::AVMBaseType::enAVMStatus> {
        inline size_t operator()(const ::v1::com::harman::adas::AVMBaseType::enAVMStatus& enAVMStatus) const {
            return static_cast<int32_t>(enAVMStatus);
        }
    };
    //Hash for enAVMViewMode
    template<>
    struct hash<::v1::com::harman::adas::AVMBaseType::enAVMViewMode> {
        inline size_t operator()(const ::v1::com::harman::adas::AVMBaseType::enAVMViewMode& enAVMViewMode) const {
            return static_cast<int32_t>(enAVMViewMode);
        }
    };
    //Hash for enAVMGuideLineMode
    template<>
    struct hash<::v1::com::harman::adas::AVMBaseType::enAVMGuideLineMode> {
        inline size_t operator()(const ::v1::com::harman::adas::AVMBaseType::enAVMGuideLineMode& enAVMGuideLineMode) const {
            return static_cast<int32_t>(enAVMGuideLineMode);
        }
    };
    //Hash for enAVMCamState
    template<>
    struct hash<::v1::com::harman::adas::AVMBaseType::enAVMCamState> {
        inline size_t operator()(const ::v1::com::harman::adas::AVMBaseType::enAVMCamState& enAVMCamState) const {
            return static_cast<int32_t>(enAVMCamState);
        }
    };
    //Hash for enAutoCaliState
    template<>
    struct hash<::v1::com::harman::adas::AVMBaseType::enAutoCaliState> {
        inline size_t operator()(const ::v1::com::harman::adas::AVMBaseType::enAutoCaliState& enAutoCaliState) const {
            return static_cast<int32_t>(enAutoCaliState);
        }
    };
    //Hash for enAutoCaliWorkModeAuto
    template<>
    struct hash<::v1::com::harman::adas::AVMBaseType::enAutoCaliWorkModeAuto> {
        inline size_t operator()(const ::v1::com::harman::adas::AVMBaseType::enAutoCaliWorkModeAuto& enAutoCaliWorkModeAuto) const {
            return static_cast<int32_t>(enAutoCaliWorkModeAuto);
        }
    };
    //Hash for enAutoCaliWorkModeManu
    template<>
    struct hash<::v1::com::harman::adas::AVMBaseType::enAutoCaliWorkModeManu> {
        inline size_t operator()(const ::v1::com::harman::adas::AVMBaseType::enAutoCaliWorkModeManu& enAutoCaliWorkModeManu) const {
            return static_cast<int32_t>(enAutoCaliWorkModeManu);
        }
    };
}


// Compatibility
namespace v1_0 = v1;

#endif // V1_COM_HARMAN_ADAS_AVM_Base_Type_HPP_
