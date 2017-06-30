
#include "CEOL.hpp"
#include "CCamera.hpp"
#include "Env.hpp"

#define MANSCAIA_PPS_FILEBASE "/pps/Diag/EOL"

UInt32	EOL::s_uiFrontUpperSpeedLimit = 0;							//0-250km/h
UInt32 EOL::s_uiFrontUpperSpeedHysteresis = 0;

UInt32 EOL::s_uiRevGelDeactSpeed[EOL::eEOLReservedItemNum]={0,0,0,0};		//0-250km/h
UInt32 EOL::s_uiRevGelSpeedHysteresis[EOL::eEOLReservedItemNum]={0,0,0,0};

UInt32 EOL::s_uiCameraStartupTime[EOL::eEOLReservedItemNum]={0,0,0,0};
UInt32 EOL::s_uiReverseActiveTime = 0;

CCamera::EType EOL::s_eCameraType[EOL::eEOLReservedItemNum]={CCamera::eType_Off,CCamera::eType_Off,CCamera::eType_Off,CCamera::eType_Off};

EOL::EReverseGuidelines EOL::s_eReverseGuidelines[EOL::eEOLReservedItemNum]={EOL::eOffReverseGuideline,EOL::eOffReverseGuideline,EOL::eOffReverseGuideline,EOL::eOffReverseGuideline};		//off-image1~image10
EOL::EOnOff EOL::s_eGelActivateWorkLight[EOL::eEOLReservedItemNum]={EOL::eOff,EOL::eOff,EOL::eOff,EOL::eOff};
EOL::EOnOff EOL::s_eGelActivateDirIndicator[EOL::eEOLReservedItemNum]={EOL::eOff,EOL::eOff,EOL::eOff,EOL::eOff};
EOL::ESteeringWheelPosition EOL::s_eSteerWheelPos = EOL::eLHD;

BOOLEAN EOL::s_bInitCapture = FALSE;
Int32 EOL::s_iCamSouceIndex = 0;
UInt32 EOL::s_eCamera_Control[EOL::eEOLReservedItemNum] ={0,0,0,0};
EOL::EMANCarType  EOL::s_eMANCarType = EOL::eMANTruck;
EOL::EOnOff EOL::s_eMANRestrictionsWhileDriving = EOL::eOff;


//TBD 
#if 0
Byte
Bit
Name
Conversion
0
 	
Camera2_control_on_CAN
HexDump (1Byte)
 	
0
Rear Gear CAN
On/Off (1Bit)
1
DashBoard Switch
On/Off (1Bit)
2 - 7
Reserved
Unsigned (6Bit)

for camera1 name is:
Camera_Control
#endif

EOL::tagRVCEOLItem EOL::s_RVCEOLItemTable[EOL::eRVCEOLNum]=
   {
      //SCAINA
      {        	"Function_FrontCameraUpperSpeedLimit",                      (void*)&EOL::s_uiFrontUpperSpeedLimit	,0, FALSE},
      {        	"Function_FrontCameraUpperSpeedHysteresis",                 (void*)&EOL::s_uiFrontUpperSpeedHysteresis	,0,FALSE},
      {        	"Function_Camera1ReverseGeneralForwardDeactivationSpeed",   (void*)(EOL::s_uiRevGelDeactSpeed	),0,	FALSE},
      {        	"Function_Camera2ReverseGeneralForwardDeactivationSpeed",   (void*)(EOL::s_uiRevGelDeactSpeed+1),0,	FALSE},
      {        	"Function_Camera1ReverseGeneralForwardHysteresis",          (void*)(EOL::s_uiRevGelSpeedHysteresis),0,	FALSE},
      {        	"Function_Camera2ReverseGeneralForwardHysteresis",          (void*)(EOL::s_uiRevGelSpeedHysteresis+1),0,	FALSE},
      {        	"Function_Camera1StartupTime",                              (void*)(EOL::s_uiCameraStartupTime),0,		FALSE},
      {        	"Function_Camera2StartupTime",                              (void*)(EOL::s_uiCameraStartupTime+1),0,		FALSE},
      {			"Function_ReverseCameraActiveTimer",						(void*)(&EOL::s_uiReverseActiveTime),0,			FALSE},
      {        	"Function_Camera1",                                         (void*)(EOL::s_eCameraType),0,				TRUE},
      {        	"Function_Camera2",                                         (void*)(EOL::s_eCameraType+1),0,				TRUE},
      {        	"Function_ReverseGuidelinesCamera1",                        (void*)(EOL::s_eReverseGuidelines),0,			TRUE},
      {        	"Function_ReverseGuidelinesCamera2",                        (void*)(EOL::s_eReverseGuidelines+1),0,		TRUE},
      {        	"Function_GeneralCameraActivationWorklightCamera1",         (void*)(EOL::s_eGelActivateWorkLight),0,		TRUE},
      {        	"Function_GeneralCameraActivationWorklightCamera2",         (void*)(EOL::s_eGelActivateWorkLight+1),0,		TRUE},
      {      	"Function_GeneralCameraActivationDirectionIndicatorsCamera1",  	(void*)(EOL::s_eGelActivateDirIndicator),0,	TRUE},
      {     	"Function_GeneralCameraActivationDirectionIndicatorsCamera2",  	(void*)(EOL::s_eGelActivateDirIndicator+1),0,	TRUE},
      {        	"System_SteeringWheelPosition",                                	(void*)(&EOL::s_eSteerWheelPos),0				,TRUE},
};
EOL::tagRVCEOLItem EOL::s_RVCEOLItemTableMAN[EOL::eRVCEOLNumMAN]=
   {
      {      	"System_Camera1",  	(void*)(EOL::s_eCameraType),           0,				    TRUE},
      {     	"System_Camera2",  	(void*)(EOL::s_eCameraType+1),         0,	                TRUE},
      {         "Camera_Control",    (void*)(EOL::s_eCamera_Control),      0,                  FALSE},
      {         "Camera2_control_on_CAN",    (void*)(EOL::s_eCamera_Control+1),      0,                  FALSE},
      {         "Deactivation_Speed",    (void*)(EOL::s_uiRevGelDeactSpeed),      0,          FALSE},
      {         "Startup_screen",    (void*)(&EOL::s_eMANCarType),      0,          TRUE},
      {         "System_RestrictionsWhileDriving_Camera",    (void*)(&EOL::s_eMANRestrictionsWhileDriving),      0,          TRUE},
      
};

TRC_SCOPE_DEF(ADAS, EOL, initialize);
BOOLEAN EOL::initialize()
{
	TRC_SCOPE(ADAS, EOL, initialize);
#if 0
	if( Env::isMANTarget() || Env::isUseCmdLine() )
	{
		readManDefaultEOL();
		return TRUE;
	}
#endif
   UInt32 uiItemNum = 0;
   tagRVCEOLItem *ptagEOLTable =NULL;
   CPPSService* pPPS = CPPSService::getInstance();
   if( !pPPS->initialize(MANSCAIA_PPS_FILEBASE) )
   {
	   DBG_ERROR(("pps initialize failed\n"));
	   return FALSE;
   }
   else
   {
       if(Env::isMANTarget())
       {
         ptagEOLTable = s_RVCEOLItemTableMAN;
         uiItemNum = eRVCEOLNumMAN;
       }
       else if(Env::isScaniaTarget())
       {
         ptagEOLTable = s_RVCEOLItemTable;
         uiItemNum = eRVCEOLNum;
       }
       else
       {
            DBG_ERROR(("read target value failed, read SCAINA as default\n"));
            ptagEOLTable = s_RVCEOLItemTable;
            uiItemNum = eRVCEOLNum;
       }
       
       
       
	   for(UInt32 i = 0 ; i < uiItemNum; ++i)
	   {
		   if( ptagEOLTable[i].bInt )
		   {
			   if( !pPPS->getIntValue(string(ptagEOLTable[i].pzName),(Int32*)ptagEOLTable[i].pItemBuf) )
			   		DBG_ERROR(("bGetEOLValue fail %s\n",ptagEOLTable[i].pzName));
			   //Int32 iValue = (Int32)(*(Int32*)s_RVCEOLItemTable[i].pItemBuf);
			   //if( uiValue < s_RVCEOLItemTable[i].min )
			   //		(*s_RVCEOLItemTable[i].pItemBuf) = s_RVCEOLItemTable[i].min;
		   }
		   else
		   {
			   if( !pPPS->getUIntValue(string(ptagEOLTable[i].pzName),(UInt32*)ptagEOLTable[i].pItemBuf) )
				   DBG_ERROR(("bGetEOLValue fail %s\n",ptagEOLTable[i].pzName));

			  // UInt32 uiValue = (UInt32)(*s_RVCEOLItemTable[i].pItemBuf);
			 // if( uiValue < s_RVCEOLItemTable[i].min )
				//  (*s_RVCEOLItemTable[i].pItemBuf) = s_RVCEOLItemTable[i].min;
		   }
	   }
   }

   //adapt man camera type with scaina camera to reuse priority prcocess 
   //but now MAN has no dependency on this variant
   if(Env::isMANTarget())
   {
      for(int CamIndex=0; CamIndex < CCamera::eCameraNum; CamIndex++)
      {
          if(1==s_eCameraType[CamIndex])
          {
              s_eCameraType[CamIndex]= IfNeedCheckReverseGear((CCamera::EPos)CamIndex) ? CCamera::eType_Reverse : CCamera::eType_General;
          }
      }
   }
   else
   {
      DBG_ERROR(("read MAN target type failed, set truck as default\n"));
   }

   CPPSService::delInstance();

   return TRUE;
}

void EOL::unInitialize()
{
	CPPSService::delInstance();
}
#if 0
void EOL::readManDefaultEOL()
{
	s_uiFrontUpperSpeedLimit = 100;
	s_uiFrontUpperSpeedHysteresis = 15;
	s_uiRevGelDeactSpeed[0] = 10;
	s_uiRevGelDeactSpeed[1] = 10;
	s_uiRevGelSpeedHysteresis[0] = 10;
	s_uiRevGelSpeedHysteresis[1] = 10;
	s_uiReverseActiveTime = 0;

	s_uiCameraStartupTime[0] = 500;
	s_uiCameraStartupTime[1] = 500;
	s_eCameraType[CCamera::eCamera1] = CCamera::eType_Reverse;
	s_eCameraType[CCamera::eCamera2] = CCamera::eType_General;
	s_eReverseGuidelines[0] = eImage1;
	s_eReverseGuidelines[1] = eImage2;
	s_eGelActivateWorkLight[0] = eOn;
	s_eGelActivateWorkLight[1] = eOn;
	s_eGelActivateDirIndicator[0] = eOff;
	s_eGelActivateDirIndicator[1] = eOff;
	s_eSteerWheelPos = eLHD;

	 if( CCommandLineParser::getInstance()->getItemBool("useCmdEOL") )
	 {
		 UInt32 uiItemNum = eRVCEOLNum;


		 DBG_MSG(("get value from command line\n"));
		for(UInt32 i = 0 ; i < uiItemNum; ++i)
		{
			//(*s_RVCEOLItemTable[i].pItemBuf) = CCommandLineParser::getInstance()->getItemUInt(string(s_RVCEOLItemTable[i].pzName));
			//DBG_MSG(("%s = %u\n",s_RVCEOLItemTable[i].pzName,*(s_RVCEOLItemTable[i].pItemBuf) ));
		}
		 DBG_MSG(("get value from command line end\n"));

	 }

}
#endif





