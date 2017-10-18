

#include "Pas/FordPDCTest.h"

//#define DELAYPDC (100000)
#define DELAYPDC (4000)

#define VPA_w	152*2
#define VPA_h	228*2
#define VPA_x	(800/2-VPA_w/2)
#define VPA_y	(480/2-VPA_h/2)

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {
namespace Pas {

int familyNum[] = {0,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,2,2,2,2,2};

int i =0;

int short_radius=0,long_radius=0;

void FordPDCTest::vUsecase_blockstate()
{
	// testvalue = 0x5;//all sensor on
	//m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORTXT,PDCServiceFord::ePDCMSG,(int*)&testvalue);
	usleep(DELAYPDC*3);

	int testvalue = 0xd;
	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORTXT,PDCServiceFord::ePDCMSG,(int*)&testvalue);
	usleep(DELAYPDC*3);

	testvalue = 0x1;//all sensor on
	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eREARRIGHTCNTR,(int*)&testvalue);
	usleep(DELAYPDC*30);

	int value = 0;
	for(value=0;value<familyNum[PDCServiceFord::eREARLEFTCRNR];value++)
	{
		usleep(DELAYPDC*3);
		PDCA_LOG_INFO("eREAR LEFT CRNR =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eREARLEFTCRNR,(int*)&value);
	}

	for(value=0;value<familyNum[PDCServiceFord::eREARLEFTCNTR];value++)
	{
		usleep(DELAYPDC*3);
		PDCA_LOG_INFO("eREAR LEFT CNTR =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eREARLEFTCNTR,(int*)&value);
		usleep(DELAYPDC);
	}



	vUsecase_FrontWalkThrough();
	//vUsecase_RearWalkThrough();
	vUsecase_LeftWalkThrough();
	vUsecase_RightWalkThrough();
}

void FordPDCTest::vUsecase_Ticket2205704()
{
	int value = 0x0A;
	//for(value=0;value<familyNum[PDCServiceFord::eSIDELEFT1];value++)
	{
		/*usleep(DELAYPDC*10*10);
		printf("	 [%s, %d] eSIDELEFT1 is ===%d(0x%2.2x)===\n", __FUNCTION__, __LINE__, value, value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORTXT,PDCServiceFord::ePDCMSG,(int*)&value);
		usleep(DELAYPDC);
		value = 0x09;
		usleep(DELAYPDC*10*10);
		printf("	 [%s, %d] eSIDELEFT1 is ===%d(0x%2.2x)===\n", __FUNCTION__, __LINE__, value, value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDELEFT1,(int*)&value);
		usleep(DELAYPDC);*/
		value = 0x02;
		usleep(DELAYPDC*10*10);
		printf("	 [%s, %d] eFRONTLEFTCNTR is ===%d(0x%2.2x)===\n", __FUNCTION__, __LINE__, value, value);
		//m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eFRONTLEFTCNTR,(int*)&value);
		usleep(DELAYPDC);
		printf("	 [%s, %d] eFRONTLEFTCRNR is ===%d(0x%2.2x)===\n", __FUNCTION__, __LINE__, value, value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eFRONTLEFTCRNR,(int*)&value);
	}
}


void FordPDCTest::vUsecase_LeftWalkThroughJC()
{
	/*int value = 5;
	for(value=0;value<familyNum[PDCServiceFord::eSIDELEFT1];value++)
	{
		usleep(DELAYPDC*3*10);
		PDCA_LOG_INFO("eSIDELEFT1 =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDELEFT1,(int*)&value);
		usleep(DELAYPDC);
	}*/

	int value = 5;
	//for(value=0;value<familyNum[PDCServiceFord::eSIDELEFT1];value++)
	{
		usleep(DELAYPDC*10*10);
		printf("	 [%s, %d] eSIDELEFT1 is ===%d===\n", __FUNCTION__, __LINE__, value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDELEFT1,(int*)&value);
		usleep(DELAYPDC);
		value = 0;
		usleep(DELAYPDC*10*10);
		printf("	 [%s, %d] eSIDELEFT1 is ===%d===\n", __FUNCTION__, __LINE__, value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDELEFT1,(int*)&value);
		usleep(DELAYPDC);
	}
}


void FordPDCTest::vUsecase_FrontWalkThroughJC()
{
	int value = 0;

	for(value=0;value<familyNum[PDCServiceFord::eFRONTLEFTCNTR];value++)
	{
		usleep(DELAYPDC*3*10);
		PDCA_LOG_INFO("FRONT LEFT CNTR  =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eFRONTLEFTCNTR,(int*)&value);
		usleep(DELAYPDC*10);
	}
}

void FordPDCTest::vUsecase_FrontWalkThrough()
{
	int value = 0;
	for(value=0;value<familyNum[PDCServiceFord::eFRONTLEFTCRNR];value++)
	{
		usleep(DELAYPDC*3);
		PDCA_LOG_INFO("FRONT LEFT CRNR  =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eFRONTLEFTCRNR,(int*)&value);
		usleep(DELAYPDC);
	}

	for(value=0;value<familyNum[PDCServiceFord::eFRONTLEFTCNTR];value++)
	{
		usleep(DELAYPDC*3);
		PDCA_LOG_INFO("FRONT LEFT CNTR  =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eFRONTLEFTCNTR,(int*)&value);
		usleep(DELAYPDC);
	}

	for(value=0;value<familyNum[PDCServiceFord::eFRONTRIGHTCNTR];value++)
	{
		PDCA_LOG_INFO("FRONT RIGHT CNTR  =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eFRONTRIGHTCNTR,(int*)&value);
		usleep(DELAYPDC);
	}

	for(value=0;value<familyNum[PDCServiceFord::eFRONTRIGHTCRNR];value++)
	{
		usleep(DELAYPDC*3);
		PDCA_LOG_INFO("FRONT RIGHT CRNR  =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eFRONTRIGHTCRNR,(int*)&value);
		usleep(DELAYPDC);
	}
}
void FordPDCTest::vUsecase_RearWalkThrough()
{
	int value = 0;
	for(value=0;value<familyNum[PDCServiceFord::eREARLEFTCRNR];value++)
	{
		usleep(DELAYPDC*3);
		PDCA_LOG_INFO("eREAR LEFT CRNR =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eREARLEFTCRNR,(int*)&value);
	}

	for(value=0;value<familyNum[PDCServiceFord::eREARLEFTCNTR];value++)
	{
		usleep(DELAYPDC*3);
		PDCA_LOG_INFO("eREAR LEFT CNTR =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eREARLEFTCNTR,(int*)&value);
		usleep(DELAYPDC);
	}
	for(value=0;value<familyNum[PDCServiceFord::eREARRIGHTCNTR];value++)
	{
		usleep(DELAYPDC*3);
		PDCA_LOG_INFO("eREAR RIGHT CNTR  =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eREARRIGHTCNTR,(int*)&value);
		usleep(DELAYPDC);
	}
	for(value=0;value<familyNum[PDCServiceFord::eREARRIGHTCRNR];value++)
	{
		usleep(DELAYPDC*3);
		PDCA_LOG_INFO("eREAR RIGHT CRNR  =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eREARRIGHTCRNR,(int*)&value);
		usleep(DELAYPDC);
	}
}
void FordPDCTest::vUsecase_LeftWalkThrough()
{
	int value = 0;
	for(value=0;value<familyNum[PDCServiceFord::eSIDELEFT1];value++)
	{
		usleep(DELAYPDC*3);
		PDCA_LOG_INFO("eSIDELEFT1 =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDELEFT1,(int*)&value);
		usleep(DELAYPDC);
	}
	for(value=0;value<familyNum[PDCServiceFord::eSIDELEFT2];value++)
	{
		usleep(DELAYPDC*3);
		PDCA_LOG_INFO("eSIDELEFT2 =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDELEFT2,(int*)&value);
		usleep(DELAYPDC);
	}
	for(value=0;value<familyNum[PDCServiceFord::eSIDELEFT3];value++)
	{
		PDCA_LOG_INFO("eSIDELEFT3 =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDELEFT3,(int*)&value);
		usleep(DELAYPDC);
	}

	for(value=0;value<familyNum[PDCServiceFord::eSIDELEFT4];value++)
	{
		usleep(DELAYPDC*3);
		PDCA_LOG_INFO("eSIDELEFT4 =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDELEFT4,(int*)&value);
		usleep(DELAYPDC);
	}
}
void FordPDCTest::vUsecase_RightWalkThrough()
{
	int value = 0;
	for(value=0;value<familyNum[PDCServiceFord::eSIDERIGHT1];value++)
	{
		PDCA_LOG_INFO("eSIDE RIGHT1 =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDERIGHT1,(int*)&value);
		usleep(DELAYPDC);
	}
	for(value=0;value<familyNum[PDCServiceFord::eSIDERIGHT2];value++)
	{
		PDCA_LOG_INFO("eSIDE RIGHT2 =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDERIGHT2,(int*)&value);
		usleep(DELAYPDC);
	}
	for(value=0;value<familyNum[PDCServiceFord::eSIDERIGHT3];value++)
	{
		PDCA_LOG_INFO("eSIDE RIGHT3 =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDERIGHT3,(int*)&value);
		usleep(DELAYPDC);
	}
	for(value=0;value<familyNum[PDCServiceFord::eSIDERIGHT4];value++)
	{
		PDCA_LOG_INFO("eSIDE RIGHT4 =%d\n",value);
		m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDERIGHT4,(int*)&value);
		usleep(DELAYPDC);
	}
}
void FordPDCTest::vUsecase_NormalWalkThrough()
{
	int value = 0x5;//all sensor on
	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORTXT,PDCServiceFord::ePDCMSG,(int*)&value);
	usleep(DELAYPDC*3);
	vUsecase_Ticket2205704();
	//vUsecase_FrontWalkThroughJC();
	//vUsecase_LeftWalkThroughJC();
	//vUsecase_FrontWalkThrough();
	//vUsecase_RearWalkThrough();
	//vUsecase_LeftWalkThrough();
	//vUsecase_RightWalkThrough();

}

void FordPDCTest::vUsecase_VDT_Forward_straight()
{
	int value = (int)PDCServiceFord::eGUIDELINETXT_ON;
 	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINECMD,PDCServiceFord::eGUIDELINESTATE,(int*)&value);

	value = 0;
	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINEDRVDRI,(int*)&value);
    //change vdt
    int val = 1000;
    m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINERADILEFT,(int*)&val);
    m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINERADIRIGHT,(int*)&val);

    usleep(DELAYPDC*10);

}

void FordPDCTest::vUsecase_VDT_Rearward_straight()
{
	int value = (int)PDCServiceFord::eGUIDELINETXT_ON;
 	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINECMD,PDCServiceFord::eGUIDELINESTATE,(int*)&value);

    value = 0;
	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINEDRVDRI,(int*)&value);
    //change vdt
    int val = 1000;
    m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINERADILEFT,(int*)&val);
    m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINERADIRIGHT,(int*)&val);
    usleep(DELAYPDC*10);

}
//negative turn = circles center is left side, so left radus should smaller
void  FordPDCTest::vUsecase_VDT_Rearward_LtNegative()
{
	int value = (int)PDCServiceFord::eGUIDELINETXT_ON;
 	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINECMD,PDCServiceFord::eGUIDELINESTATE,(int*)&value);

    value = 5;
	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINEDRVDRI,(int*)&value);
    //change vdt
    int val = -300;
    m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINERADILEFT,(int*)&val);
    val = -400;
    m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINERADIRIGHT,(int*)&val);
    usleep(DELAYPDC*10);
}
void  FordPDCTest::vUsecase_VDT_Rearward_RtPositive()
{
	int value = (int)PDCServiceFord::eGUIDELINETXT_ON;
 	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINECMD,PDCServiceFord::eGUIDELINESTATE,(int*)&value);

    value = 3;
	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINEDRVDRI,(int*)&value);
    //change vdt
    int val = 300;
    m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINERADILEFT,(int*)&val);
    val = 200;
    m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINERADIRIGHT,(int*)&val);
    usleep(DELAYPDC*10);
}
void  FordPDCTest::vUsecase_VDT_Forward_RtPositive()
{
	int value = (int)PDCServiceFord::eGUIDELINETXT_ON;
 	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINECMD,PDCServiceFord::eGUIDELINESTATE,(int*)&value);

	value = 2;
	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINEDRVDRI,(int*)&value);
    //change vdt
    int val = 400;
    m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINERADILEFT,(int*)&val);
    val = 300;
    m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINERADIRIGHT,(int*)&val);

    usleep(DELAYPDC*10);
}
///left negative - right val > left val
void  FordPDCTest::vUsecase_VDT_Forward_LtNegative()
{
	int value = (int)PDCServiceFord::eGUIDELINETXT_ON;
 	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINECMD,PDCServiceFord::eGUIDELINESTATE,(int*)&value);

	value = 4;
	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINEDRVDRI,(int*)&value);
    //change vdt
    int val = -400;
    m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINERADILEFT,(int*)&val);
    val = -500;
    m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINERADIRIGHT,(int*)&val);

    usleep(DELAYPDC*10);
}

void  FordPDCTest::vUsecase_VDT_OFF()
{
	int value = (int)PDCServiceFord::eGUIDELINETXT_OFF;
 	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINECMD,PDCServiceFord::eGUIDELINESTATE,(int*)&value);
    m_PDCServiceFord->bSetVPASize(152,228);
    //m_PDCServiceFord->bSetVPALeftBottom(400,240);
    m_PDCServiceFord->bSetVPALeftBottom((800/2) - (152/2),(480/2) - (228/2));
    usleep(DELAYPDC*10);
}

void  FordPDCTest::vUsecase_VDT_LaunchControl()
{
	int value = (int)PDCServiceFord::eGUIDELINETXT_ON;
 	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINECMD,PDCServiceFord::eGUIDELINESTATE,(int*)&value);
	value = 1;
	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINEDRVDRI,(int*)&value);
	value = (int)PDCServiceFord::eGUIDELINETXT_ON;
 	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINECMD,PDCServiceFord::eGUIDELINESTATE,(int*)&value);
 	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINEDRVDRI,(int*)&value);
	value = (int)PDCServiceFord::eGUIDELINETXT_ON;
    int val = -400;
    m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINERADILEFT,(int*)&val);
    val = -500;
    m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINERADIRIGHT,(int*)&val);
  	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADISTATE,PDCServiceFord::eGUIDELINEDRVDRI,(int*)&value);
	value = (int)PDCServiceFord::eGUIDELINETXT_OFF;
    usleep(DELAYPDC*10);
}

void  FordPDCTest::vUsecase_VDT_Normal()
{
#if 1
	usleep(DELAYPDC*10);
	int value = 0x5;//all sensor on
	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORTXT,PDCServiceFord::ePDCMSG,(int*)&value);
	vUsecase_VDT_LaunchControl();
	/*vUsecase_VDT_Forward_straight();
	vUsecase_VDT_OFF();
	usleep(DELAYPDC*3);
	vUsecase_VDT_Rearward_straight();
	vUsecase_VDT_OFF();
	usleep(DELAYPDC*3);
	vUsecase_VDT_Rearward_LtNegative();
	vUsecase_VDT_OFF();
	usleep(DELAYPDC*3);*/
	vUsecase_VDT_Rearward_RtPositive();
	vUsecase_VDT_OFF();
	usleep(DELAYPDC*3);
	/*vUsecase_VDT_Forward_RtPositive();
	vUsecase_VDT_Forward_LtNegative();

	vUsecase_VDT_Forward_straight();
	vUsecase_VDT_Rearward_straight();

	vUsecase_VDT_OFF();*/
	usleep(DELAYPDC*3);
#endif

}


void FordPDCTest::update()
{
#if 0
	usleep(DELAYPDC*10);
	int value = 0x5;//all sensor on
	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORTXT,PDCServiceFord::ePDCMSG,(int*)&value);
	vUsecase_VDT_LaunchControl();
	vUsecase_VDT_Forward_straight();
	vUsecase_VDT_OFF();
	usleep(DELAYPDC*3);
	vUsecase_VDT_Rearward_straight();
	vUsecase_VDT_OFF();
	usleep(DELAYPDC*3);
	vUsecase_VDT_Rearward_LtNegative();
	vUsecase_VDT_OFF();
	usleep(DELAYPDC*3);
	vUsecase_VDT_Rearward_RtPositive();
	vUsecase_VDT_OFF();
	usleep(DELAYPDC*3);
	vUsecase_VDT_Forward_RtPositive();
	vUsecase_VDT_Forward_LtNegative();

	vUsecase_VDT_Forward_straight();
	//vUsecase_FrontWalkThrough();
	vUsecase_VDT_Rearward_straight();
	//vUsecase_RearWalkThrough();

	vUsecase_VDT_OFF();
	usleep(DELAYPDC*3);
#endif
	vUsecase_VDT_Normal();
	/*usleep(DELAYPDC*10);
	static int value = 0;
	value = 5;//all sensor on
	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORTXT,PDCServiceFord::ePDCMSG,(int*)&value);
	usleep(DELAYPDC*3);*/
	//vUsecase_NormalWalkThrough();
	//vUsecase_blockstate();
	//vUsecase_VDT_Forward_straight();
	//vUsecase_VDT_Rearward_straight();

#if 0
	static int value = 0;
	eDRVState dvtstate = eForward;
	eSymbolState symbolState = eNegative;
	int short_radius=90,long_radius=0;
	int guilieData[]={GraphicVDT::eForward,GraphicVDT::eForwardPositive,300,350} ;
	value = 5;//all sensor on
	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORTXT,PDCServiceFord::ePDCMSG,(int*)&value);
	usleep(DELAYPDC*3);


	//m_PDCServiceFord->SetPDCViewState(false);
	//m_PDCServiceFord->vResetPDCGraphicState();


    m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINECMD,PDCServiceFord::eGUIDELINETXT_ON,(int*)&value);
    //change vdt
    m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINERADIUS,0,(int*)guilieData);
    usleep(DELAYPDC*10);
    m_PDCServiceFord->bSetVDTDisable();

	{usleep(DELAYPDC*5);};

	value = 5;//all sensor on
	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORTXT,PDCServiceFord::ePDCMSG,(int*)&value);
	usleep(DELAYPDC*3);
	for(value=0;value<16;value++)
	{
	//	usleep(DELAYPDC*3);
	//	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORTXT,PDCServiceFord::ePDCMSG,(int*)&value);
	}

    {
    	usleep(DELAYPDC*5);
    }
	// value = 1;
 // 	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eREARLEFTCRNR,(int*)&value);
	// m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eREARRIGHTCNTR,(int*)&value);
	// usleep(DELAYPDC*13);
	// m_PDCServiceFord->vResetPDCGraphicState();
	// usleep(DELAYPDC*13);
	// value = 2;
 // 	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eREARLEFTCRNR,(int*)&value);
	// m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eREARRIGHTCNTR,(int*)&value);
	// usleep(DELAYPDC*13);
	// value = 3;
 // 	m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eREARLEFTCRNR,(int*)&value);
	// m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eREARRIGHTCNTR,(int*)&value);
	// usleep(DELAYPDC*13);

		eDRVState dvtstate;
		eSymbolState symbolState;
        if (i<16)
        {

            if(i%6==0)
            {
                dvtstate = eForward;
                short_radius=1000;
                long_radius=1000;
                symbolState = ePositive;

            }
            if(i%6==1)
            {
                dvtstate = eForward;
                short_radius =200;
                long_radius=263;
                symbolState = ePositive;

            }
            if(i%6==2)
            {
                dvtstate = eForward;
                short_radius =200;
                long_radius=263;
                symbolState = eNegative;

            }
            if(i%6==3)
            {
                dvtstate = eRearward;
                short_radius=1000;
                long_radius=1000;
                symbolState = ePositive;

            }
            if(i%6==4)
            {
                dvtstate = eRearward;
                short_radius =200;
                long_radius=263;
                symbolState = eNegative;

            }
            if(i%6==5)
            {
                dvtstate = eRearward;
                short_radius =200;
                long_radius=263;
                symbolState = ePositive;

            }

            if(i==5)
            {
                m_GraphicVPAFord->bSetVDTEnable();
            }
            if(i==10)
            {
                m_GraphicVPAFord->bSetVDTDisable();

            }


            if (i<15 && i>=10)
            {
                PDCL_LOG_INFO("bSetGraphicPDCState run !!\n");
                //m_GraphicVPAFord->bSetGraphicPDCState(pdcStatus);
            }

            if(i==15)
            {
               m_GraphicVPAFord->bSetVDTEnable();
               m_GraphicVPAFord->bSetPDCDisable();
            }

            //change vdt
            m_GraphicVPAFord->bSetVDTState(dvtstate,symbolState,short_radius,long_radius);
            // change status
        }
        else if(i<32)
        {

            dvtstate = eForward;
            symbolState = ePositive;
            short_radius =200+50*(i-15);
            long_radius=263;
            PDCL_LOG_INFO("short_radius is -------%d\n",short_radius);
            PDCL_LOG_INFO("Radius add is -------%d\n",(i-15));
            m_GraphicVPAFord->bSetVDTState(dvtstate,symbolState,short_radius,long_radius);

        }else if(i<37)
        {
            dvtstate = eForward;
            short_radius=1000;
            long_radius=1000;
            symbolState = ePositive;
            PDCL_LOG_INFO("short_radius is -------%d\n",short_radius);
            PDCL_LOG_INFO("Radius add is -------%d\n",(i-15));
            m_GraphicVPAFord->bSetVDTState(dvtstate,symbolState,short_radius,long_radius);

        }
        else
        {

            dvtstate = eForward;
            symbolState = eNegative;
            short_radius =1000-(i-37)*50;
            long_radius=263;
            PDCL_LOG_INFO("short_radius is -------%d\n",short_radius);
            PDCL_LOG_INFO("Radius add is -------%d\n",(i-15));
            m_GraphicVPAFord->bSetVDTState(dvtstate,symbolState,short_radius,long_radius);

            if (short_radius==200)
            {
               i = 1;
            }

        }
        i++;//move 4 pixels
        usleep(1000000);



	m_PDCServiceFord->SetPDCViewState(false);
	//usleep(DELAYPDC*13);
	//value = 3;
 	//m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eREARLEFTCRNR,(int*)&value);
	//usleep(DELAYPDC*3);

	//value = 5;//all sensor on
	//m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORTXT,PDCServiceFord::ePDCMSG,(int*)&value);
	//usleep(DELAYPDC*3);
#if 0

	m_PDCServiceFord->vResetPDCGraphicState();
#endif
	//value =1;
	//m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORTXT,PDCServiceFord::ePDCMSG,(int*)&value);
#endif
}

void FordPDCTest::setup()
{
	//m_testAMBPDC.Initialize(m_PDCServiceFord);
	start();
}

FordPDCTest::FordPDCTest(PDCServiceFord* pPDCServiceFord,GraphicVPAFord* pGraphicVPAFord)
	: CRunableBase("FordPDCTest",false)
{
	PDCA_LOG_INFO("FordPDCTest created!");
	m_PDCServiceFord = pPDCServiceFord;
	m_GraphicVPAFord = pGraphicVPAFord;
};

} // namespace Pas
} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman