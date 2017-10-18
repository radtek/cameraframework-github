
#include "Pas/PDCSensor.h"

#include <string.h>

//-2 --- graphic lib will use last state / startup state

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {
namespace Pas {

static int s_iPDCState[24]={
   -2,-2,-2,-2,
   -2,-2,-2,-2,
   -2,-2,-2,-2,
   -2,-2,-2,-2,
   -2,-2,-2,-2,
   -2,-2,-2,-2,
};
static int s_iPDCStateLast[24]={
   -2,-2,-2,-2,
   -2,-2,-2,-2,
   -2,-2,-2,-2,
   -2,-2,-2,-2,
   -2,-2,-2,-2,
   -2,-2,-2,-2,
};
enum eSns_RearLogicSector{
	e_Rear_OL ,
	e_Rear_OR ,
	e_Rear_IL ,
	e_Rear_IR ,
	e_Rear_SnsNum ,
};
enum eSns_FrontLogicSector{
	e_Front_OL ,
	e_Front_OR ,
	e_Front_IL,
	e_Front_IR ,
	e_Front_SnsNum ,
};
enum eSns_LeftLogicSector{
	e_Left_1 ,
	e_Left_2 ,
	e_Left_3 ,
	e_Left_4 ,
	e_Left_SnsNum ,
};
enum eSns_RightLogicSector{
	e_Right_1,
	e_Right_2,
	e_Right_3,
	e_Right_4,
	e_Right_SnsNum ,
};

//PDC position table based on sns state for [e_Sns_On]
//use only one png file to cover this positon and the state of all the zone
PDCSensorHub::eSns_DispState eSnsReI_DispStateLUT[]=
{
	//0~3
	PDCSensorHub::e_Inactive,PDCSensorHub::e_Warn_1,PDCSensorHub::e_Warn_2,PDCSensorHub::e_Warn_2,
	PDCSensorHub::e_Warn_3,PDCSensorHub::e_Warn_3,PDCSensorHub::e_Warn_4,PDCSensorHub::e_Warn_4,
	//8 9 A B
	PDCSensorHub::e_Warn_5,PDCSensorHub::e_Warn_5,PDCSensorHub::e_Warn_6,PDCSensorHub::e_Warn_6,
	//C D E F
	PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,

	PDCSensorHub::e_LastState
};
PDCSensorHub::eSns_DispState eSnsReO_DispStateLUT[]=
{
	//0~3
	PDCSensorHub::e_Inactive,PDCSensorHub::e_Warn_1,PDCSensorHub::e_Warn_2,PDCSensorHub::e_Warn_2,
	PDCSensorHub::e_Warn_3,PDCSensorHub::e_Warn_3,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,
	//8 9 A B
	PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,
	//C D E F
	PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,

	PDCSensorHub::e_LastState
};
PDCSensorHub::eSns_DispState eSnsFrI_DispStateLUT[ ]=
{
	//0~3
	PDCSensorHub::e_Inactive,PDCSensorHub::e_Warn_1,PDCSensorHub::e_Warn_2,PDCSensorHub::e_Warn_2,
	PDCSensorHub::e_Warn_3,PDCSensorHub::e_Warn_3,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,
	//8 9 A B
	PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,
	//C D E F
	PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,

	PDCSensorHub::e_LastState
};
PDCSensorHub::eSns_DispState eSnsFrO_DispStateLUT[ ]=
{
	//0~3
	PDCSensorHub::e_Inactive,PDCSensorHub::e_Warn_1,PDCSensorHub::e_Warn_2,PDCSensorHub::e_Warn_2,
	PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,
	//8 9 A B
	PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,
	//C D E F
	PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,

	PDCSensorHub::e_LastState
} ;

PDCSensorHub::eSns_DispState eSnsSide_DispStateLUT[ ]=
{
	//0~3
	PDCSensorHub::e_Inactive,PDCSensorHub::e_Warn_1,PDCSensorHub::e_Warn_1,PDCSensorHub::e_Warn_1,
	PDCSensorHub::e_Warn_1,PDCSensorHub::e_Warn_2,PDCSensorHub::e_Warn_2,PDCSensorHub::e_Warn_2,
	//8 9 A B
	PDCSensorHub::e_Warn_2,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,
	//C D E F
	PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,PDCSensorHub::e_Idle,

	PDCSensorHub::e_LastState
};

// - these txt values makes disp off - so sensor state should be off - inactive
	/*	case e_All_Park_Sensors_Off: 0
		case e_Park_Sys_Alternate_Mode: 6
		case e_NotUsed3: 3
		case e_NotUsed4: 4
		case e_NotUsed7: 7
		case e_Not_Avail_Trlr_attchd: B */


//PDC msg txt table  --ePDCMsgTxt explains
PDCSensorBase::eSns_State tSnsRe_StateLUT[ ]=
{
	//0~3
	PDCSensorBase::e_Sns_Off,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_Off,
	PDCSensorBase::e_Sns_Off,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_Off,PDCSensorBase::e_Sns_Off,
	//8 9 A B
	PDCSensorBase::e_Trailer,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_Off,
	//C D E F
	PDCSensorBase::e_Trailer,PDCSensorBase::e_SnsBlocked,PDCSensorBase::e_Sns_On,PDCSensorBase::e_SnsBlocked,
} ;
//PDC msg txt table  --ePDCMsgTxt explains
PDCSensorBase::eSns_State tSnsFr_StateLUT[ ]=
{
	//0~3
	PDCSensorBase::e_Sns_Off,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_Off,
	PDCSensorBase::e_Sns_Off,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_Off,PDCSensorBase::e_Sns_Off,
	//8 9 A B
	PDCSensorBase::e_SnsBlocked,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_Off,
	//C D E F
	PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_On,PDCSensorBase::e_SnsBlocked,PDCSensorBase::e_SnsBlocked,
} ;
//PDC msg txt table  --ePDCMsgTxt and specific sensor state explains
PDCSensorBase::eSns_State tSnsSide1_StateLUT[ ]=
{
	//0~3
	PDCSensorBase::e_Sns_Off,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_Off,
	PDCSensorBase::e_Sns_Off,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_Off,PDCSensorBase::e_Sns_Off,
	//8 9 A B
	PDCSensorBase::e_SnsBlocked,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_Off,
	//C D E F
	PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_On,PDCSensorBase::e_SnsBlocked,PDCSensorBase::e_SnsBlocked,
} ;

PDCSensorBase::eSns_State tSnsSide23_StateLUT[]=
{
	//0~3
	PDCSensorBase::e_Sns_Off,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_Off,
	PDCSensorBase::e_Sns_Off,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_Off,PDCSensorBase::e_Sns_Off,
	//8 9 A B
	PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_Off,
	//C D E F
	PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_On,
} ;

PDCSensorBase::eSns_State tSnsSide4_StateLUT[]=
{
	//0~3
	PDCSensorBase::e_Sns_Off,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_Off,
	PDCSensorBase::e_Sns_Off,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_Off,PDCSensorBase::e_Sns_Off,
	//8 9 A B
	PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_On,PDCSensorBase::e_Sns_Off,
	//C D E F
	PDCSensorBase::e_Sns_On,PDCSensorBase::e_SnsBlocked,PDCSensorBase::e_Sns_On,PDCSensorBase::e_SnsBlocked,
} ;

int PDCSensorHub::m_spCarOutlineState = 0;
PDCSensorHub::PDCSensorHub()
{
	PDCA_LOG_INFO("PDCSensorHub() !\n");
	m_PDCMsgTxt = 0; //normal state
	m_PDC_Stat = e_INACTIVE;
	m_PDCDisp = false;
	m_pAreaExtState[e_Front_Area]= &s_iPDCState[e_EXTSTATEFRONT];
	m_pAreaExtState[e_Rear_Area]= &s_iPDCState[e_EXTSTATEREAR];
	m_pAreaExtState[e_Left_Area]= &s_iPDCState[e_EXTSTATELEFT];
	m_pAreaExtState[e_Right_Area]= &s_iPDCState[e_EXTSTATERIGHT];
	m_spCarOutlineState = 0; //clr bit mask for all the sns
	m_pRearSns[e_Rear_OL] =(IPDCSensorIntfFord*) new  PDCRearSensor((int*)tSnsRe_StateLUT,(int*)eSnsReO_DispStateLUT,(int*)&s_iPDCState[e_REARLEFTCRNR],e_REARLEFTCRNR);
	m_pRearSns[e_Rear_OR] =(IPDCSensorIntfFord*) new  PDCRearSensor((int*)tSnsRe_StateLUT,(int*)eSnsReO_DispStateLUT,(int*)&s_iPDCState[e_REARRIGHTCRNR],e_REARRIGHTCRNR);
	m_pRearSns[e_Rear_IL] =(IPDCSensorIntfFord*) new  PDCRearSensor((int*)tSnsRe_StateLUT,(int*)eSnsReI_DispStateLUT,(int*)&s_iPDCState[e_REARLEFTCNTR],e_REARLEFTCNTR);
	m_pRearSns[e_Rear_IR] =(IPDCSensorIntfFord*) new  PDCRearSensor((int*)tSnsRe_StateLUT,(int*)eSnsReI_DispStateLUT,(int*)&s_iPDCState[e_REARRIGHTCNTR],e_REARRIGHTCNTR);

	m_pFrontSns[e_Front_OL] =(IPDCSensorIntfFord*) new PDCFrontSensor((int*)tSnsFr_StateLUT,(int*)eSnsFrO_DispStateLUT,(int*)&s_iPDCState[e_FRONTLEFTCRNR],e_FRONTLEFTCRNR);
	m_pFrontSns[e_Front_OR] =(IPDCSensorIntfFord*) new PDCFrontSensor((int*)tSnsFr_StateLUT,(int*)eSnsFrO_DispStateLUT,(int*)&s_iPDCState[e_FRONTRIGHTCRNR],e_FRONTRIGHTCRNR);
	m_pFrontSns[e_Front_IL] =(IPDCSensorIntfFord*) new PDCFrontSensor((int*)tSnsFr_StateLUT,(int*)eSnsFrI_DispStateLUT,(int*)&s_iPDCState[e_FRONTLEFTCNTR],e_FRONTLEFTCNTR);
	m_pFrontSns[e_Front_IR] =(IPDCSensorIntfFord*) new PDCFrontSensor((int*)tSnsFr_StateLUT,(int*)eSnsFrI_DispStateLUT,(int*)&s_iPDCState[e_FRONTRIGHTCNTR],e_FRONTRIGHTCNTR);

	m_pRightSns[e_Right_1] =(IPDCSensorIntfFord*) new PDCSideSensor((int*)tSnsSide1_StateLUT,(int*)eSnsSide_DispStateLUT,(int*)&s_iPDCState[e_SIDERIGHT1],e_SIDERIGHT1);
	m_pRightSns[e_Right_2] =(IPDCSensorIntfFord*) new PDCSideSensor((int*)tSnsSide23_StateLUT,(int*)eSnsSide_DispStateLUT,(int*)&s_iPDCState[e_SIDERIGHT2],e_SIDERIGHT2);
	m_pRightSns[e_Right_3] =(IPDCSensorIntfFord*) new PDCSideSensor((int*)tSnsSide23_StateLUT,(int*)eSnsSide_DispStateLUT,(int*)&s_iPDCState[e_SIDERIGHT3],e_SIDERIGHT3);
	m_pRightSns[e_Right_4] =(IPDCSensorIntfFord*) new PDCSideSensor((int*)tSnsSide4_StateLUT,(int*)eSnsSide_DispStateLUT,(int*)&s_iPDCState[e_SIDERIGHT4],e_SIDERIGHT4);

	m_pLeftSns[e_Left_1] =(IPDCSensorIntfFord*) new  PDCSideSensor((int*)tSnsSide1_StateLUT,(int*)eSnsSide_DispStateLUT,(int*)&s_iPDCState[e_SIDELEFT1],e_SIDELEFT1);
	m_pLeftSns[e_Left_2] =(IPDCSensorIntfFord*) new  PDCSideSensor((int*)tSnsSide23_StateLUT,(int*)eSnsSide_DispStateLUT,(int*)&s_iPDCState[e_SIDELEFT2],e_SIDELEFT2);
	m_pLeftSns[e_Left_3] =(IPDCSensorIntfFord*) new  PDCSideSensor((int*)tSnsSide23_StateLUT,(int*)eSnsSide_DispStateLUT,(int*)&s_iPDCState[e_SIDELEFT3],e_SIDELEFT3);
	m_pLeftSns[e_Left_4] =(IPDCSensorIntfFord*) new  PDCSideSensor((int*)tSnsSide4_StateLUT,(int*)eSnsSide_DispStateLUT,(int*)&s_iPDCState[e_SIDELEFT4],e_SIDELEFT4);
};


PDCSensorHub::~PDCSensorHub()
{
	m_PDCMsgTxt = 0;

	for(int i=0; i<e_Rear_SnsNum; i++)
	{
		delete (PDCRearSensor*)m_pRearSns[i];
	}
	for(int i=0; i<e_Front_SnsNum; i++)
	{
		delete (PDCFrontSensor*)m_pFrontSns[i];
	}
	for(int i=0; i<e_Right_SnsNum; i++)
	{
		delete (PDCSideSensor*)m_pRightSns[i];
	}
	for(int i=0; i<e_Left_SnsNum; i++)
	{
		delete (PDCSideSensor*)m_pLeftSns[i];
	}
}
//udpated specific sensor state to state buffer
			//e_Trailer = 1,
			//e_SnsBlocked = 2,
void PDCSensorHub::vSetAreaSnsState(IPDCSensorIntfFord** pSnsInf, int iArea, int iAreaSnsNum,int val)
{
	for(int i=0;i<iAreaSnsNum;i++)
	{
		pSnsInf[i]->vSetSenorVal(val);
	}
}
//only check ext state after all sns finish updated
void PDCSensorHub::vUpdateAreaSnsExtState(IPDCSensorIntfFord** pSnsInf, int iArea, int iAreaSnsNum)
{

	for(int i=0;i<iAreaSnsNum;i++)
	{
		PDCA_LOG_INFO("PDCSensorHub::vUpdateAreaSnsExtState- blk @ area sns id[%d] - area id[%d]- ext id[%d]\n",i,iArea,pSnsInf[i]->iGetSnsExtState());
		if(e_BLKSTATE == pSnsInf[i]->iGetSnsExtState())
		{
			*m_pAreaExtState[iArea] = e_BLKSTATE;
			vSetAreaSnsState(pSnsInf,iArea,iAreaSnsNum,PDCSensorHub::eSns_DispState(15));
			PDCA_LOG_INFO("PDCSensorHub::vUpdateAreaSnsExtState- blk @ area sns id[%d] - area id[%d]\n",i,iArea);
			return;
		}
	}

	for(int i=0;i<iAreaSnsNum;i++)
	{
		if(e_TARILERSTATE == pSnsInf[i]->iGetSnsExtState())
		{
			*m_pAreaExtState[iArea] = e_TARILERSTATE;
			vSetAreaSnsState(pSnsInf,iArea,iAreaSnsNum,PDCSensorHub::e_Inactive);
			PDCA_LOG_INFO("PDCSensorHub::vUpdateAreaSnsExtState- trail @ area sns id[%d] - area id[%d]\n",i,iArea);
			return;
		}
	}
	*m_pAreaExtState[iArea] = PDCSensorHub::e_Inactive;
}

void PDCSensorHub::vSetPDCMsg(int sensor , int val)
{
	//todo - single blk or trail will update whole area
	//take blk state as higher priority to show
	PDCA_LOG_INFO("PDCSensorHub::vSetPDCMsg  %d - %d\n",sensor,val);
	switch (sensor)
	{
		case PDCServiceFord::eFRONTLEFTCNTR:
			m_pFrontSns[e_Front_IL]->vSnsMsgState(val);
			vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pFrontSns,(int)e_Front_Area,(int)e_Front_SnsNum);
			break;
		case PDCServiceFord::eFRONTRIGHTCNTR:
			m_pFrontSns[e_Front_IR]->vSnsMsgState(val);
			vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pFrontSns,(int)e_Front_Area,(int)e_Front_SnsNum);
			break;
		case PDCServiceFord::eFRONTLEFTCRNR:
			m_pFrontSns[e_Front_OL]->vSnsMsgState(val);
			vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pFrontSns,(int)e_Front_Area,(int)e_Front_SnsNum);
			break;
		case PDCServiceFord::eFRONTRIGHTCRNR:
			m_pFrontSns[e_Front_OR]->vSnsMsgState(val);
			vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pFrontSns,(int)e_Front_Area,(int)e_Front_SnsNum);
			break;

		case PDCServiceFord::eREARLEFTCNTR:
			m_pRearSns[e_Rear_IL]->vSnsMsgState(val);
			vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pRearSns,(int)e_Rear_Area,(int)e_Rear_SnsNum);
			break;
		case PDCServiceFord::eREARRIGHTCNTR:
			m_pRearSns[e_Rear_IR]->vSnsMsgState(val);
			vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pRearSns,(int)e_Rear_Area,(int)e_Rear_SnsNum);
			break;
		case PDCServiceFord::eREARLEFTCRNR:
			m_pRearSns[e_Rear_OL]->vSnsMsgState(val);
			vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pRearSns,(int)e_Rear_Area,(int)e_Rear_SnsNum);
			break;
		case PDCServiceFord::eREARRIGHTCRNR:
			m_pRearSns[e_Rear_OR]->vSnsMsgState(val);
			vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pRearSns,(int)e_Rear_Area,(int)e_Rear_SnsNum);
			break;

		case PDCServiceFord::eSIDELEFT1:
			m_pLeftSns[e_Left_1]->vSnsMsgState(val);
			vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pLeftSns,(int)e_Left_Area,(int)e_Left_SnsNum);
			break;
		case PDCServiceFord::eSIDELEFT2:
			m_pLeftSns[e_Left_2]->vSnsMsgState(val);
			vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pLeftSns,(int)e_Left_Area,(int)e_Left_SnsNum);
			break;
		case PDCServiceFord::eSIDELEFT3:
			m_pLeftSns[e_Left_3]->vSnsMsgState(val);
			vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pLeftSns,(int)e_Left_Area,(int)e_Left_SnsNum);
			break;
		case PDCServiceFord::eSIDELEFT4:
			m_pLeftSns[e_Left_4]->vSnsMsgState(val);
			vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pLeftSns,(int)e_Left_Area,(int)e_Left_SnsNum);
			break;

		case PDCServiceFord::eSIDERIGHT1:
			m_pRightSns[e_Right_1]->vSnsMsgState(val);
			vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pRightSns,(int)e_Right_Area,(int)e_Right_SnsNum);
			break;
		case PDCServiceFord::eSIDERIGHT2:
			m_pRightSns[e_Right_2]->vSnsMsgState(val);
			vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pRightSns,(int)e_Right_Area,(int)e_Right_SnsNum);
			break;
		case PDCServiceFord::eSIDERIGHT3:
			m_pRightSns[e_Right_3]->vSnsMsgState(val);
			vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pRightSns,(int)e_Right_Area,(int)e_Right_SnsNum);
			break;
		case PDCServiceFord::eSIDERIGHT4:
			m_pRightSns[e_Right_4]->vSnsMsgState(val);
			vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pRightSns,(int)e_Right_Area,(int)e_Right_SnsNum);
			break;
		default:
			PDCA_LOG_INFO("err: PDCSensorHub::vSetPDCMsg  %d - %d\n",sensor,val);
			break;
	}
	//printf(" [%s, %d] m_PDCDisp = %d\n", __FUNCTION__, __LINE__, m_PDCDisp);
	//printf(" [%s, %d] m_spCarOutlineState = %d\n", __FUNCTION__, __LINE__, m_spCarOutlineState);
	if(m_PDCDisp)
	{
		s_iPDCState[e_CARSTATE] = (m_spCarOutlineState ==0)?1:0;//resouce index 0 is warning outline, index 1 is normal car img
	}
}

static bool bViewStateCleared = false;
//ovPDCServiceFord::erall sensor state update
void PDCSensorHub::vSetPDCTxt(int val)
{
	/* AVTIVE PDC_SATE
	R_SNSRS_ON_F_SNSRS_OFF |
	R_SNSRS_OFF_F_SNSRS_ON |
	R_SNSRS_ON_F_SNSRS_ON |
	FAIL_MODE_NO_CHIME |
	FAIL_MODE_WITH_CHIME |R_SNS_INACTIVE_TRLR_ATCH |
	R_Sns_Trlr_F_Sns_Blk |
	R_Sns_Blk_F_Sns_On |
	R_Sns_On_F_Sns_Blk |
	All_Sns_Blk
	After consecutive samples for (T>=PDC_Stat_Timr_Cfg)

	*/
	/*
	ALL_PARK_SENSORS_OFF |
	PARK_SYS_ALTERNATE_MODE |
	NOT_USED |
	NOT_AVAIL_TRLR_ATTCHD
	After consecutive samples for (T>=PDC_Stat_Timr_Cfg)

	*/
	//work around for CAN issue
	//if(val==(int)e_All_Sns_Blk) val=e_All_Park_Sensors_Off;

	switch(val)
	{
		case e_R_Snsrs_On_F_Snsrs_Off:
		case e_R_Snsrs_Off_F_Snsrs_On:
		case e_R_Snsrs_On_F_Snsrs_On:
		case e_Fail_Mode_with_Chime:
		case e_Fail_Mode_no_Chime:
		case e_R_Sns_Inactive_Trlr_atch:
		case e_R_Sns_Trlr_F_Sns_Blk:
		case e_R_Sns_Blk_F_Sns_ON:
		case e_R_Sns_ON_F_Sns_Blk:
		case e_All_Sns_Blk:
			m_PDC_Stat = e_ACTIVE;
			m_PDCDisp = true;
			PDCA_LOG_INFO("PDCSensorHub vSnsMsgTxt: PDCDSIP true\n") ;
			break;
		case e_All_Park_Sensors_Off:
		case e_Park_Sys_Alternate_Mode:
		case e_NotUsed3:
		case e_NotUsed4:
		case e_NotUsed7:
		case e_Not_Avail_Trlr_attchd:
			m_PDC_Stat = e_INACTIVE;
			m_PDCDisp = false;
			PDCA_LOG_INFO("PDCSensorHub vSnsMsgTxt: PDCDSIP false\n") ;
			break;
		default:
			PDCA_LOG_INFO("PDCSensorHub vSnsMsgTxt unknown: %d \n",val) ;
			break;
	}
	if(m_PDCDisp)
	{
		memcpy(s_iPDCState,s_iPDCStateLast,sizeof(s_iPDCStateLast));
		//s_iPDCState[e_CARSTATE] = 0;
		bViewStateCleared =false;
		vUpdateTxtToAllSensor(val);
		s_iPDCState[e_CARSTATE] = (m_spCarOutlineState ==0)?1:0;//resouce index 0 is warning outline, index 1 is normal car img
	}
	else
	{
		//todo: on closed state, PDC updated state
		vUpdateTxtToAllSensor(val);
		//set all the state to inactive  -- on ford pdc service also paused graphic layer
		//keep last car image,
		if(!bViewStateCleared)
		{
			memcpy(s_iPDCStateLast,s_iPDCState,sizeof(s_iPDCStateLast));
			for(unsigned int i = 0;i<int(e_PDCPNGNUM);i++)
			{
				s_iPDCState[i]= e_Inactive;
			}
			bViewStateCleared = true;
		}
	}
}

void PDCSensorHub::vUpdateTxtToAllSensor(int val)
{
		for(int i=0; i<e_Rear_SnsNum ; i++)
		{
			m_pRearSns[i]->vSnsMsgTxt(val);
		}
		vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pRearSns,(int)e_Rear_Area,(int)e_Rear_SnsNum);

		for(int i=0; i<e_Front_SnsNum ; i++)
		{
			m_pFrontSns[i]->vSnsMsgTxt(val);
		}
		vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pFrontSns,(int)e_Front_Area,(int)e_Front_SnsNum);

		for(int i=0; i<e_Right_SnsNum ; i++)
		{
			m_pRightSns[i]->vSnsMsgTxt(val);
		}
		vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pRightSns,(int)e_Right_Area,(int)e_Right_SnsNum);

		for(int i=0; i<e_Left_SnsNum ; i++)
		{
			m_pLeftSns[i]->vSnsMsgTxt(val);
		}
		vUpdateAreaSnsExtState((IPDCSensorIntfFord**)m_pLeftSns,(int)e_Left_Area,(int)e_Left_SnsNum);

}

//todo - png file of the pdc state to match all the sensor cases
//SKIP FIRST SLOT AS GRPAHIC BUFF START PROCESS ON FIRST SLOT
int* PDCSensorHub::pGetPDCState()
{
	PDCL_LOG_INFO("pGetPDCState run !! %d-%d-%d-%d=%d-%d-%d-%d=%d-%d-%d-%d=%d-%d-%d-%d=[%d]=-%d-%d-%d-%d", \
    s_iPDCState[0],s_iPDCState[1],s_iPDCState[2],s_iPDCState[3], \
    s_iPDCState[4],s_iPDCState[5],s_iPDCState[6],s_iPDCState[7], \
    s_iPDCState[8],s_iPDCState[9],s_iPDCState[10],s_iPDCState[11], \
    s_iPDCState[12],s_iPDCState[13],s_iPDCState[14],s_iPDCState[15], \
    s_iPDCState[16],s_iPDCState[17],s_iPDCState[18],s_iPDCState[19],
    s_iPDCState[20]);
   return &s_iPDCState[0];
}


void PDCSensorHub::SetPDCViewState(bool bPDCViewState)
{
	if(bPDCViewState)
	{
		memcpy(s_iPDCState,s_iPDCStateLast,sizeof(s_iPDCStateLast));
		bViewStateCleared = false;
		m_PDCDisp = true;//todo  -- HMI request to show actully is not support?
	}
	else
	{
		//set all the state to inactive  -- on ford pdc service also paused graphic layer
		m_PDCDisp= false;
		if(!bViewStateCleared)
		{
			memcpy(s_iPDCStateLast,s_iPDCState,sizeof(s_iPDCStateLast));
			for(unsigned int i = 0;i<int(e_PDCPNGNUM);i++)
			{
				s_iPDCState[i]= e_Inactive;
			}
			bViewStateCleared = true;
		}
	}

}

void PDCSensorHub::ResetPDCGraphicState()
{

	//for first 16 buffer is distance resouce
	for(unsigned int i = 0;i<16;i++)
	{
		s_iPDCState[i]= 0;//0 will show the gray color view as idle state
	}
	for(unsigned int i = 16;i<e_PDCPNGNUM;i++)
	{
		s_iPDCState[i]= e_Inactive;
	}
	m_spCarOutlineState = 0;// clr the outline state
	s_iPDCState[e_CARSTATE] = 1; //index of car resource is normal state

	//jsut reset PDC state
	memcpy(s_iPDCStateLast,s_iPDCState,sizeof(s_iPDCStateLast));
}

//----------------------------------------------
PDCSensorBase::PDCSensorBase(int* pStateLUT,int* pDispStateLUT,int* piWarnState, unsigned int uiSnsId)
:m_pStateLUT(pStateLUT)
,m_pDispStateLUT(pDispStateLUT)
,m_pWarnState (piWarnState)
,m_ExtState (PDCSensorHub::e_Inactive)
,m_MsgVal(16)//16 is showlast state in LUT ,in order to show default view purpose
,m_eSnsState(e_Sns_On)
,m_SnsId(uiSnsId)

{

}

PDCSensorBase::~PDCSensorBase()
{
	m_pStateLUT = NULL;
	m_pDispStateLUT = NULL;
	m_pWarnState = NULL;
}
void PDCSensorBase::vSetSnsStateVal(int val)
{
	*m_pWarnState = PDCSensorHub::eSns_DispState(val);
}
void PDCSensorBase::vSetSnsState(int val)
{
	//LUT only have 16  slots to check
	if((val < 0)||(val >16))
	{
		PDCA_LOG_INFO("error - excced limit: PDCSensorBase vSetSnsState: val[%d]\n",val) ;
		return;
	}
	int SensorState = m_pDispStateLUT[val];
	//translate  eSns_DispState to grphic index of resource
	#if 0
	if((SensorState == PDCSensorHub::e_Warn_1)
	||(SensorState == PDCSensorHub::e_Warn_2)
	||(SensorState == PDCSensorHub::e_Warn_3)
	||(SensorState == PDCSensorHub::e_Warn_4)
	||(SensorState == PDCSensorHub::e_Warn_5)
	||(SensorState == PDCSensorHub::e_Warn_6))
	||(SensorState == PDCSensorHub::e_Inactive))
	#endif
	// change distance val to the offset  in the png files config in the cfg files
	//int iPDCResOffset = (int)PDCSensorHub::e_Idle;//first is idle, res before ilde is not cfg yet...
	if((SensorState >=(int)PDC_DISTANCE_RES_OFFSET)&&(SensorState<(int)PDCSensorHub::e_Sns_DispState_num))
	{
		SensorState -=(int)PDC_DISTANCE_RES_OFFSET;
	}
	*m_pWarnState = PDCSensorHub::eSns_DispState( SensorState);
	m_ExtState=PDCSensorHub::e_Inactive;
	m_MsgVal = val;
	PDCA_LOG_INFO("set PDCSensorBase vSetSnsState: val[%d][%d]\n",val,*m_pWarnState) ;
}


//----------------------------------------------
PDCRearSensor::PDCRearSensor(int* pStateLUT,int* pDispStateLUT,int* pWarnState, unsigned int uiSnsId)
:PDCSensorBase(pStateLUT,pDispStateLUT,pWarnState,uiSnsId)
{


}
//msg txt index pre process table
void PDCRearSensor::vSnsMsgTxt(int val)
{
	if((0<=val)&&(val<16))
	{
		m_eSnsState =(eSns_State) m_pStateLUT[val];
	}
	else if(-1==val)
	{
		PDCA_LOG_INFO("RearSensor vSnsMsgTxt: PDCDSIP false\n") ;
	}
	else
	{
		PDCA_LOG_INFO("RearSensor vSnsMsgTxt: val[%d]\n",val) ;
	}

	vSnsMsgState(m_MsgVal);//update last val based on new sensor outside state
}
void PDCRearSensor::vSnsMsgState(int val)
{
	PDCA_LOG_INFO("RearSensor svSnsMsgState [%d][%d]\n",(int)m_eSnsState,val) ;

	switch (m_eSnsState)
	{
		case PDCSensorBase::e_Sns_Off :
			*m_pWarnState=-1;
			m_ExtState=-1;
			break;
		case PDCSensorBase::e_Sns_On :
			vSetSnsState(val);
			break;
		case PDCSensorBase::e_Trailer :
			//*m_pWarnState=PDCSensorHub::e_Inactive;
			m_ExtState=PDCSensorHub::e_TARILERSTATE;
			*m_pWarnState=-1;
			//m_ExtState=0;
			PDCA_LOG_INFO("RearSensor sensor state e_Trailer\n") ;
			break;
		case PDCSensorBase::e_SnsBlocked :
			m_MsgVal=val;
			if(1==m_MsgVal)
			{
				m_ExtState=PDCSensorHub::e_BLKSTATE;
			}
			else if(0==m_MsgVal)
			{
				//todo: what is no state
				//m_ExtState=PDCSensorHub::e_NoState;
				m_ExtState=PDCSensorHub::e_Inactive;
			}
			else
			{
				m_ExtState=PDCSensorHub::e_Inactive;
			}
			*m_pWarnState=PDCSensorHub::eSns_DispState(0);// make it as idle state

			PDCA_LOG_INFO("RearSensor sensor state e_Sns_blk[%d]\n",m_ExtState) ;
			break;
		default:
			PDCA_LOG_INFO("RearSensor sensor state not defined [%d]\n",(int)m_eSnsState) ;
			break;
	}
	if(val == 1)
	{
		vSetCarOutLineState();
	}
	else
	{
		vClrCarOutLineState();
	}
}

//----------------------------------------------

PDCFrontSensor::PDCFrontSensor(int* pStateLUT,int* pDispStateLUT,int* pWarnState, unsigned int uiSnsId)
:PDCSensorBase(pStateLUT,pDispStateLUT,pWarnState, uiSnsId)
{


}
//msg txt index pre process table
void PDCFrontSensor::vSnsMsgTxt(int val)
{
	if((0<=val)&&(val<16))
	{
		m_eSnsState = (eSns_State)m_pStateLUT[val];
	}
	else if(-1==val)
	{
		PDCA_LOG_INFO("FrontSensor vSnsMsgTxt: PDCDSIP false\n") ;
	}
	else
	{
		PDCA_LOG_INFO("FrontSensor vSnsMsgTxt: val[%d]\n",val) ;
	}

	vSnsMsgState(m_MsgVal);//update last val based on new sensor outside state
}
void PDCFrontSensor::vSnsMsgState(int val)
{
	PDCA_LOG_INFO("PDCFrontSensor svSnsMsgState [%d][%d]\n",(int)m_eSnsState,val) ;
	switch (m_eSnsState)
	{
		case PDCSensorBase::e_Sns_Off :
			*m_pWarnState=-1;
			m_ExtState=-1;
			break;
		case PDCSensorBase::e_Sns_On :
			vSetSnsState(val);
			break;
		case PDCSensorBase::e_SnsBlocked :
			m_MsgVal=val;
			if(1==m_MsgVal)
			{
				m_ExtState=PDCSensorHub::e_BLKSTATE;
			}
			else if(0==m_MsgVal)
			{
				m_ExtState=PDCSensorHub::e_Inactive;
				//*m_pWarnState=PDCSensorHub::e_NoState;
			}
			else
			{
				m_ExtState=PDCSensorHub::e_Inactive;
			}
			*m_pWarnState=PDCSensorHub::eSns_DispState(0);// make it as idle state

			PDCA_LOG_INFO("FrontSensor sensor state e_Blocked\n") ;
			break;
		default:
			PDCA_LOG_INFO("FrontSensor sensor state not defined [%d]\n",m_eSnsState) ;
			break;
	}
	if(val == 1)
	{
		vSetCarOutLineState();
	}
	else
	{
		vClrCarOutLineState();
	}
}

//----------------------------------------------

PDCSideSensor::PDCSideSensor(int* pStateLUT,int* pDispStateLUT,int* pWarnState, unsigned int uiSnsId)
:PDCSensorBase(pStateLUT,pDispStateLUT,pWarnState, uiSnsId)
{


}
//msg txt index pre process table
void PDCSideSensor::vSnsMsgTxt(int val)
{
	if((0<=val)&&(val<16))
	{
		m_eSnsState =(eSns_State) m_pStateLUT[val];
	}
	else if(-1==val)
	{
		PDCA_LOG_INFO("PDCSideSensor vSnsMsgTxt: PDCDSIP false\n") ;
	}
	else
	{
		PDCA_LOG_INFO("PDCSideSensor vSnsMsgTxt: val[%d]\n",val) ;
	}

	vSnsMsgState(m_MsgVal);//update last val based on new sensor outside state
}
void PDCSideSensor::vSnsMsgState(int val)
{
	PDCA_LOG_INFO("PDCSideSensor svSnsMsgState [%d][%d]\n",(int)m_eSnsState,val) ;
	switch (m_eSnsState)
	{
		case PDCSensorBase::e_Sns_Off :
			*m_pWarnState=-1;
			m_ExtState=-1;
			break;
		case PDCSensorBase::e_Sns_On :
			vSetSnsState(val);
			break;
		case PDCSensorBase::e_SnsBlocked :
			m_MsgVal=val;
			if(1==m_MsgVal)
			{
				m_ExtState=PDCSensorHub::e_BLKSTATE;
			}
			else if(0==m_MsgVal)
			{
				//m_ExtState=PDCSensorHub::e_NoState;
				m_ExtState=PDCSensorHub::e_Inactive;
			}
			else
			{
				m_ExtState=PDCSensorHub::e_Inactive;
			}
			*m_pWarnState=PDCSensorHub::eSns_DispState(0);// make it as idle state

			PDCA_LOG_INFO("PDCSideSensor sensor state e_Blocked\n") ;
			break;
		default:
			PDCA_LOG_INFO("PDCSideSensor sensor state not defined [%d]\n",m_eSnsState) ;
			break;
	}
	if((val >= 1)&&(val <= 4))
	{
		vSetCarOutLineState();
	}
	else
	{
		vClrCarOutLineState();
	}
}

} // namespace Pas
} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman