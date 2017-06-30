/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by Voice CodeGen Version: R1_v1.3.0
* generated on: Tue Mar 07 13:22:52 CST 2017
*/
#ifndef V0_ORG_HARMAN_FORD_visualparkassist_PROXY_BASE_HPP_
#define V0_ORG_HARMAN_FORD_visualparkassist_PROXY_BASE_HPP_

#include <v0/org/harman/ford/visualparkassist.hpp>


#include <v0/org/harman/ford/visualparkassist_types.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Deployment.hpp>
#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Struct.hpp>
#include <cstdint>

#include <CommonAPI/Attribute.hpp>
#include <CommonAPI/Proxy.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v0 {
namespace org {
namespace harman {
namespace ford {

class visualparkassistProxyBase
    : virtual public CommonAPI::Proxy {
public:
    typedef CommonAPI::ObservableReadonlyAttribute<::v0::org::harman::ford::visualparkassist_types::PrkAidSnsRlCrnr_D_Stat_enum> PrkAidSnsRlCrnr_D_Stat_enumAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v0::org::harman::ford::visualparkassist_types::PrkAidSnsRlCntr_D_Stat_enum> PrkAidSnsRlCntr_D_Stat_enumAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v0::org::harman::ford::visualparkassist_types::PrkAidSnsRrCntr_D_Stat_enum> PrkAidSnsRrCntr_D_Stat_enumAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v0::org::harman::ford::visualparkassist_types::PrkAidSnsRrCrnr_D_Stat_enum> PrkAidSnsRrCrnr_D_Stat_enumAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v0::org::harman::ford::visualparkassist_types::SidePrkSnsL3_D_Stat_enum> SidePrkSnsL3_D_Stat_enumAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v0::org::harman::ford::visualparkassist_types::SidePrkSnsL4_D_Stat_enum> SidePrkSnsL4_D_Stat_enumAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v0::org::harman::ford::visualparkassist_types::SidePrkSnsR3_D_Stat_enum> SidePrkSnsR3_D_Stat_enumAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v0::org::harman::ford::visualparkassist_types::SidePrkSnsR4_D_Stat_enum> SidePrkSnsR4_D_Stat_enumAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<uint8_t> ApaBrk_A_RqAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v0::org::harman::ford::visualparkassist_types::PrkAidMsgTxt_D_Rq_struct> PrkAidMsgTxt_D_RqAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v0::org::harman::ford::visualparkassist_types::PrkAidSnsFlCrnr_D_Stat_enum> PrkAidSnsFlCrnr_D_Stat_enumAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v0::org::harman::ford::visualparkassist_types::PrkAidSnsFlCntr_D_Stat_enum> PrkAidSnsFlCntr_D_Stat_enumAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v0::org::harman::ford::visualparkassist_types::PrkAidSnsFrCntr_D_Stat_enum> PrkAidSnsFrCntr_D_Stat_enumAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v0::org::harman::ford::visualparkassist_types::PrkAidSnsFrCrnr_D_Stat_enum> PrkAidSnsFrCrnr_D_Stat_enumAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v0::org::harman::ford::visualparkassist_types::SidePrkSnsL2_D_Stat_enum> SidePrkSnsL2_D_Stat_enumAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v0::org::harman::ford::visualparkassist_types::SidePrkSnsL1_D_Stat_enum> SidePrkSnsL1_D_Stat_enumAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v0::org::harman::ford::visualparkassist_types::SidePrkSnsR2_D_Stat_enum> SidePrkSnsR2_D_Stat_enumAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v0::org::harman::ford::visualparkassist_types::SidePrkSnsR1_D_Stat_enum> SidePrkSnsR1_D_Stat_enumAttribute;


    /**
     * description: No Information Available
     */
    virtual PrkAidSnsRlCrnr_D_Stat_enumAttribute& getPrkAidSnsRlCrnr_D_Stat_enumAttribute() = 0;
    /**
     * description: No Information Available
     */
    virtual PrkAidSnsRlCntr_D_Stat_enumAttribute& getPrkAidSnsRlCntr_D_Stat_enumAttribute() = 0;
    /**
     * description: No Information Available
     */
    virtual PrkAidSnsRrCntr_D_Stat_enumAttribute& getPrkAidSnsRrCntr_D_Stat_enumAttribute() = 0;
    /**
     * description: No Information Available
     */
    virtual PrkAidSnsRrCrnr_D_Stat_enumAttribute& getPrkAidSnsRrCrnr_D_Stat_enumAttribute() = 0;
    /**
     * description: No Information Available
     */
    virtual SidePrkSnsL3_D_Stat_enumAttribute& getSidePrkSnsL3_D_Stat_enumAttribute() = 0;
    /**
     * description: No Information Available
     */
    virtual SidePrkSnsL4_D_Stat_enumAttribute& getSidePrkSnsL4_D_Stat_enumAttribute() = 0;
    /**
     * description: No Information Available
     */
    virtual SidePrkSnsR3_D_Stat_enumAttribute& getSidePrkSnsR3_D_Stat_enumAttribute() = 0;
    /**
     * description: No Information Available
     */
    virtual SidePrkSnsR4_D_Stat_enumAttribute& getSidePrkSnsR4_D_Stat_enumAttribute() = 0;
    /**
     * description: No Information Available
     */
    virtual ApaBrk_A_RqAttribute& getApaBrk_A_RqAttribute() = 0;
    /**
     * description: No Information Available
     */
    virtual PrkAidMsgTxt_D_RqAttribute& getPrkAidMsgTxt_D_RqAttribute() = 0;
    /**
     * description: No Information Available
     */
    virtual PrkAidSnsFlCrnr_D_Stat_enumAttribute& getPrkAidSnsFlCrnr_D_Stat_enumAttribute() = 0;
    /**
     * description: No Information Available
     */
    virtual PrkAidSnsFlCntr_D_Stat_enumAttribute& getPrkAidSnsFlCntr_D_Stat_enumAttribute() = 0;
    /**
     * description: No Information Available
     */
    virtual PrkAidSnsFrCntr_D_Stat_enumAttribute& getPrkAidSnsFrCntr_D_Stat_enumAttribute() = 0;
    /**
     * description: No Information Available
     */
    virtual PrkAidSnsFrCrnr_D_Stat_enumAttribute& getPrkAidSnsFrCrnr_D_Stat_enumAttribute() = 0;
    /**
     * description: No Information Available
     */
    virtual SidePrkSnsL2_D_Stat_enumAttribute& getSidePrkSnsL2_D_Stat_enumAttribute() = 0;
    /**
     * description: No Information Available
     */
    virtual SidePrkSnsL1_D_Stat_enumAttribute& getSidePrkSnsL1_D_Stat_enumAttribute() = 0;
    /**
     * description: No Information Available
     */
    virtual SidePrkSnsR2_D_Stat_enumAttribute& getSidePrkSnsR2_D_Stat_enumAttribute() = 0;
    /**
     * description: No Information Available
     */
    virtual SidePrkSnsR1_D_Stat_enumAttribute& getSidePrkSnsR1_D_Stat_enumAttribute() = 0;


};

} // namespace ford
} // namespace harman
} // namespace org
} // namespace v0


// Compatibility
namespace v0_1 = v0;

#endif // V0_ORG_HARMAN_FORD_visualparkassist_PROXY_BASE_HPP_
