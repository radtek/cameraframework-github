
#include "Pas/PDCMsgHandlerFord.h"
//#include "VPAServiceStubImpl.hpp"
//#include "PDCServiceProxy.h"
#include "Pas/PDCServiceFord.h"
#include "Pas/PDCFactory.h"
#include "Pas/PDCGraphicFord.h"
#include "CMessageQueue.h"
//concreate lib provide by graphic
#include "ADASManager/PAS/GraphicCore/GraphicVPAFord.h"
#include "Pas/FordPDCTest.h"

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {
namespace Pas {

PDCFactory* PDCFactory::m_pInstance=NULL;

PDCFactory* PDCFactory::getInstance()
{
   if(m_pInstance == NULL)
   {
	   m_pInstance = new PDCFactory();
   }
   return m_pInstance;
}

void PDCFactory::delInstance()
{
   if(m_pInstance != NULL)
   {
      delete m_pInstance;
      m_pInstance = NULL;
   }
}

PDCFactory::~PDCFactory()
{
	m_pInstance = NULL;
}
#define VPA_w	152*2
#define VPA_h	228*2
#define VPA_x	(800/2-VPA_w/2)
#define VPA_y	(480/2-VPA_h/2)

PDCFactory::PDCFactory()
{
	ALOGI("PDCFactory() !\n");
}

PDCServiceFord* PDCFactory::vSetup()
{
	ALOGI(" [%s, %d]\n", __FUNCTION__, __LINE__);
	CMessageQueue* pMsgQueue =NULL;
#ifndef PRESCORE_SUPPORT   //#define PRESCORE_SUPPORT 1
    pMsgQueue = new CMessageQueue("FordPDCQueue", 300, new PDCMsgHandlerFord());
#endif
    //create ford graphic proecess client
    GraphicVPAFord* pGraphicVPAFord = new GraphicVPAFord();   //therad
    if(pGraphicVPAFord->vInit(800,480))
    //if(pGraphicVPAFord->vInit(640,720))
	{
		ALOGI("PDCFactory() vInit VPA graphic failed!\n");
	}
	else
	{
        ALOGI("PDCFactory() vSetup call start begine!\n");
		pGraphicVPAFord->start();// start graphic thread!!
        ALOGI("PDCFactory() vSetup call start end!\n");
	}
	;//create surface todo -------init is not properly get!!!!
    //pGraphicVPAFord->bSetVPASize(VPA_w,VPA_h);//to be desided by camera team
	//pGraphicVPAFord->bSetVPALeftBottom(VPA_x,VPA_y);//deside by camera team
    //pGraphicVPAFord->bSetPDCSize(152,288);//to be desided by camera team
	//pGraphicVPAFord->bSetPDCLeftBottom(200,200);//deside by camera team
	//pGraphicVPAFord->bSetVDTState(0,0,20,40);


	 //create ford PDC app - graphic  client -- not use this wrapper now
	//PDCGraphicFord* pPDCGraphicFord = new PDCGraphicFord(pGraphicPDCFord);


	//create ford PDC app client -- lost first serveral msg
    ALOGI("PDCFactory() pMsgQueue = %p!\n", pMsgQueue);
	PDCServiceFord::getInstance()->vInitialize(pMsgQueue, pGraphicVPAFord);
	//setup msg handler

	//m_pVPAStubImpl=  new  VPAServiceStubImpl(m_pPDCServiceFord);
	//m_pPDCServiceProxy=  new  PDCServiceProxy(m_pPDCServiceFord);
	//run some test cases

	FordPDCTest* ptest = new FordPDCTest(PDCServiceFord::getInstance(),pGraphicVPAFord);
	//ptest->start();

	return PDCServiceFord::getInstance();
	//PDCServiceFord::getInstance()->join();
}

} // namespace Pas
} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman