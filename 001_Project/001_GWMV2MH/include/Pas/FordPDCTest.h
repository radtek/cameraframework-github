
#ifndef __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_FORDPDCTEST_H__
#define __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_FORDPDCTEST_H__

//#include "../../../src-gen/consumes/v0/org/harman/ford/visualparkassist_types.hpp"
//#include "../CAMB_PDCConsumerHandler.hpp"
#include "PAS/GraphicCore/GraphicVPAFord.h"
#include "Pas/PDCServiceFord.h"
#include "CRunableBase.h"

//using namespace v0::org::harman::ford;

using Harman::Adas::AFramework::AFoundation::CRunableBase;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {
namespace Pas {

class FordPDCTest : public CRunableBase {
public:
	FordPDCTest(PDCServiceFord* pPDCServiceFord,GraphicVPAFord* pGraphicVPAFord);
    void update();
	void setup();
    virtual VOID init() override;
private:
	void vSendPDCState();
	//AMB_PDCConsumerHandler m_testAMBPDC;
	void vUsecase_blockstate();
	void vUsecase_Ticket2205704();
	void vUsecase_LeftWalkThroughJC();
	void vUsecase_FrontWalkThroughJC();
	void vUsecase_NormalWalkThrough();
	void vUsecase_FrontWalkThrough();
	void vUsecase_RearWalkThrough();
	void vUsecase_LeftWalkThrough();
	void vUsecase_RightWalkThrough();
	void vUsecase_VDT_Forward_straight();
	void vUsecase_VDT_Rearward_straight();
	void vUsecase_VDT_Rearward_LtNegative();
	void vUsecase_VDT_Rearward_RtPositive();
	void vUsecase_VDT_Forward_RtPositive();
	void vUsecase_VDT_Forward_LtNegative();
	void vUsecase_VDT_OFF();
	void vUsecase_VDT_LaunchControl();
	void vUsecase_VDT_Normal();
	PDCServiceFord* m_PDCServiceFord;
	GraphicVPAFord* m_GraphicVPAFord;
};

} // namespace Pas
} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_FORDPDCTEST_H__