
#ifndef __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_PDCSERVICEFORD_H__
#define __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_PDCSERVICEFORD_H__

#include "ADASManager/PAS/ParkAssist_PDCService.h"
#include "CMessageHandler.h"
#include "PDCGraphicFord.h"
#include "ADASManager/PAS/GraphicCore/GraphicVPAFord.h"
#include "PDCSensor.h"
//#include "PDCServiceStubImpl.hpp"
#include <string>

using namespace std;

using Harman::Adas::AFramework::AFoundation::CMessageSubHandler;
using Harman::Adas::AFramework::ABase::ADASManager::GraphicVPAFord;
using Harman::Adas::AFramework::ABase::ADASManager::CPDCService;

#define PRESCORE_SUPPORT 1

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {
namespace Pas {

class PDCSensorHub;
//todo: set pdc only works on PDCServiceStubImpl?
//class PDCServiceFord : public CPDCService,public CMessageSubHandler, PDCServiceStubImpl{
class PDCServiceFord : public CPDCService, public CMessageSubHandler{
public:
	#define MAX_PDC_MSG_LEN 2
    virtual ~PDCServiceFord();
	enum eFordPDCState  {
		eSTOP,
		eMISSING,
		eFAULT,
		eRUN,
		ePAUSE,
		eEXIT
	};

	enum eFordPDCMsgType  {
		eSENSORTXT,
		eSENSORDISTANCE,
		eGUIDELINECMD,
		eGUIDELINERADISTATE,
		eFORDPDCMSGTYPENUM
	};

//same order as usr.cfg
	enum ePDCSensorMsg  {
		ePDCMSG,

		eFRONTLEFTCNTR,
		eFRONTRIGHTCNTR,
		eFRONTLEFTCRNR,
		eFRONTRIGHTCRNR,

		eSIDELEFT1,
		eSIDERIGHT1,
		eSIDELEFT2,
		eSIDERIGHT2,

		eSIDELEFT3,
		eSIDERIGHT3,
		eSIDELEFT4,
		eSIDERIGHT4,

		eREARLEFTCRNR,
		eREARRIGHTCRNR,
		eREARLEFTCNTR,
		eREARRIGHTCNTR,

		eGUIDELINESTATE,
		eGUIDELINERADILEFT,
		eGUIDELINERADIRIGHT,
		eGUIDELINEDRVDRI,

		ePDCSIGNUM,
	};

//to support guild line request
	enum eFordGuideLineMsg  {
		eGUIDELINETXT_OFF,
		eGUIDELINETXT_ON,

		eGUIDELINESIGNUM,
	};

//to support guild line positive - nagative
	enum eFordGuideLineDriState	{
		eDIRNOTKNOW = 0,
		eNOMOTION = 1,
		eFPOSITIVE = 2,
		eBPOSITIVE = 3,
		eFNEGATIVE = 4,
		eBNEGATIVE = 5,
		eNOTUSED1 = 6,
		eNOTUSED2 = 7,

		eFORDGUIDELINEDRISTATENUM,
	};

	static PDCServiceFord* getInstance();
	static void delInstance();
	virtual BOOLEAN initialize(string sServiceName) override;
	void vInitialize(CMessageQueue* pMsgQueue, GraphicVPAFord* pGraphicVPAFord);//remove ford graphic client in app
	void vUpdateSize(void* pData);
	void vUpdatePosition(void* pData);
	void vUpdateDistance(void* pData);
    void vSetDayMode();
    void vSetNightMode();
	void beforeHandleMsgQueue();
	void afterHandleMsgQueue();
	void pushPDCMsg(const eFordPDCMsgType eMsgType,const int iMsgId, int* data);

	void onABMPDCMsg(const char*);
	void onSensorPosition(const char*);

    bool bSetVPALeftBottom(int x, int y){m_pVPAGraphicFord->bSetVPALeftBottom(x,y);return false;};
    bool bSetVPASize(int w, int h){m_pVPAGraphicFord->bSetVPASize(w,h);return false;};
    bool bGetPDCState();
    void SetPDCViewState(bool bPDCViewState);
    void SetPDCBackgroundState(bool bPDCBackgroundState) {m_pVPAGraphicFord->vSetPDCBackgroundState(bPDCBackgroundState);};
	void vResetPDCGraphicState();
	void onGuideLineCmd(const char* data);
	void onGuideLineRadius(const char* data);

	virtual VOID dispatchEvent(UInt32 uiEventID, const string& pData) override;
private:
	PDCServiceFord();
	GraphicVPAFord* m_pVPAGraphicFord;
	static PDCServiceFord* m_pInstance;
	bool m_bPDCServiceCfg;
	bool m_PDC_Cfg ;
	bool m_bLastPDCDisp ;
	eFordPDCState m_PDC_Stat;
	//buffer for msg que
	int m_PDCSensorMsg[ePDCSIGNUM][MAX_PDC_MSG_LEN];
	void vSyncLayers();
	PDCSensorHub* m_PDCSensorHub;
	unsigned char m_cVDTLuanchControl;
};

} // namespace Pas
} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_PDCSERVICEFORD_H__