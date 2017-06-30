#ifndef _C_EOL_HPP_
#define _C_EOL_HPP_

#include "CPPSService.hpp"
#include "svs.h"
#include "CCamera.hpp"
#include "Env.hpp"

#define BITMASK_CONTROL_REARGEAR 0x1
#define BITMASK_CONTROL_HARDPIN 0x2
class EOL
{
public: // enum struct typedef

    enum { eEOLReservedItemNum = 4 };
	enum ERVCEOL
	{
	   //SCAINA ONLY
	   eFrontCameraUpperSpeedLimit,//byte
	   eFrontCameraUpperSpeedHysteresis,//byte
	   eCamera1ReverseGeneralForwardDeactivationSpeed,//byte
	   eCamera2ReverseGeneralForwardDeactivationSpeed,//byte
	   eCamera1ReverseGeneralForwardHysteresis,//byte
	   eCamera2ReverseGeneralForwardHysteresis,//byte
	   eFunction_ReverseCameraActiveTimer,
	   eFunction_Camera1StartupTime,//byte 0~255
	   eFunction_Camera2StartupTime,//byte 0~255
	   eFunction_Camera1,//
	   eFunction_Camera2,//
	   eReverseGuidelinesCamera1,//
	   eReverseGuidelinesCamera2,//
	   eGeneralCameraActivationWorklightCamera1,//0vs1~0xff
	   eGeneralCameraActivationWorklightCamera2,//0vs1~0xff
	   eGeneralCameraActivationDirectionIndicatorsCamera1,//0vs1~0xff
	   eGeneralCameraActivationDirectionIndicatorsCamera2,//0vs1~0xff
	   eSteeringWheelPosition,//
	   eRVCEOLNum,
	};
enum ERVCEOLMAN
	{
      eSystem_Camera1,
      eSystem_Camera2,
      eCamera_Control,
      eCamera2_control_on_CAN,
      eDeactivation_Speed,
      eStartup_screen,
      eSystem_RestrictionsWhileDriving_Camera,
	  eRVCEOLNumMAN,
	};
/*	enum eFunctionCamera
	{
	   eOffFunctionCamera,
	   eGeneralCam,
	   eReverse,
	   eFront,
	};*/

	enum EReverseGuidelines
	{
	   eImage1,
	   eImage2,
	   eImage3,
	   eImage4,
	   eImage5,
	   eImage6,
	   eImage7,
	   eImage8,
	   eImage9,
	   eImage10,
	   eOffReverseGuideline,
	};

	enum EOnOff
	{
	   eOff,
	   eOn,
	};

	enum ESteeringWheelPosition
	{
	   eRHD,
	   eLHD,
	   eCenter,
	   eNone,
	};
//add for MAN

	enum EMANCarType
	{
	   eMANCarDefault,
	   eMANTruck,
	   eMANCoach,
	   eMANCoach2,
	};

	struct tagRVCEOLItem
	{
	   const char* 	pzName;
	   void*     	pItemBuf;
	   UInt32		min;
	   BOOLEAN		bInt;
	};

public: //method
	static 	BOOLEAN initialize();
	static  void	unInitialize();



	static UInt32					getFrontUpperSpeedLimit( )						{ return s_uiFrontUpperSpeedLimit;			}
	static UInt32					getFrontUpperSpeedHysteresis()					{ return s_uiFrontUpperSpeedHysteresis;		}
   //shared MAN SCANIA 
   static UInt32					getRevGelDeactSpeed(CCamera::EPos ePos)			{ return s_uiRevGelDeactSpeed[ePos];		}
	static UInt32					getRevGelSpeedHysteresis(CCamera::EPos ePos)	{ return s_uiRevGelSpeedHysteresis[ePos];	}
   //shared MAN SCANIA
	static CCamera::EType			getCameraType(CCamera::EPos ePos)				{ return s_eCameraType[ePos];			}

	static UInt32					getCameraStartupTime(CCamera::EPos ePos)		
    { 
        UInt32 ret =0; 
        if(0==s_uiCameraStartupTime[ePos]) return ret; 
        return ret = ((255>=s_uiCameraStartupTime[ePos])&&(5<=s_uiCameraStartupTime[ePos]))?s_uiCameraStartupTime[ePos]*20:100;  
    }

	static UInt32					getReverseActiveTime()							{ return s_uiReverseActiveTime;			}

	static UInt32					getReverseGuideLineIndex(CCamera::EPos ePos)	{ UInt32 ret; return ret = ((1<=s_eReverseGuidelines[ePos])&&(10>=s_eReverseGuidelines[ePos]))?(s_eReverseGuidelines[ePos]-1):eOffReverseGuideline;	}
	static UInt32					getOff_GuideLineNum()							{ return eOffReverseGuideline;			}

	static BOOLEAN					isGelActivateWorkLightOn(CCamera::EPos ePos)	{ return (s_eGelActivateWorkLight[ePos] != eOff);}
	static BOOLEAN					isGelActivateDirIndicatorOn(CCamera::EPos ePos)	{ return (s_eGelActivateDirIndicator[ePos] != eOff);}

	static ESteeringWheelPosition	getWheelPos()									{ return s_eSteerWheelPos;	}

	static BOOLEAN					getInitCapture() 								{ return s_bInitCapture;	}
	static void						setInitCapture(BOOLEAN b)						{ s_bInitCapture = b;	}

	static Int32 getCameraSourceIdx() { return s_iCamSouceIndex;	}
	static void	 setCameraSourceIndex(Int32 i) { s_iCamSouceIndex = i; 	}
	//static stQNXCapConfig_t& getQNXCaptureConfig() { return s_qnxCapConfig;	}

   //MAN ONLY
	static BOOLEAN IfNeedCheckReverseGear(CCamera::EPos ePos) { return (BITMASK_CONTROL_REARGEAR==(s_eCamera_Control[ePos]&BITMASK_CONTROL_REARGEAR));	}
    static BOOLEAN IfNeedCheckHardPin(CCamera::EPos ePos)     { return (BITMASK_CONTROL_HARDPIN ==(s_eCamera_Control[ePos]&BITMASK_CONTROL_HARDPIN));	}
	static BOOLEAN IfNeedCheckSpeedRestriction() { return (eOff!=s_eMANRestrictionsWhileDriving);	}

    //but system will make sure different input to coash and trunk- adas service keep same apis?
    static BOOLEAN IsMANTruckTarget()	{ return (!IsMANCoachTarget());}
    static BOOLEAN IsMANCoachTarget()	{ return (eMANCoach== s_eMANCarType)||(eMANCoach2== s_eMANCarType);}

//private:
	//static void 					readManDefaultEOL();

private: // data
   static UInt32					s_uiFrontUpperSpeedLimit;							//0-250km/h
   static UInt32					s_uiFrontUpperSpeedHysteresis;

   static UInt32					s_uiRevGelDeactSpeed[EOL::eEOLReservedItemNum];		//0-250km/h
   static UInt32					s_uiRevGelSpeedHysteresis[EOL::eEOLReservedItemNum];

   static UInt32 					s_uiCameraStartupTime[EOL::eEOLReservedItemNum];
   static UInt32 					s_uiReverseActiveTime;

   static CCamera::EType			s_eCameraType[EOL::eEOLReservedItemNum];

   static EReverseGuidelines 		s_eReverseGuidelines[EOL::eEOLReservedItemNum];		//off-image1~image10
   static EOnOff 					s_eGelActivateWorkLight[EOL::eEOLReservedItemNum];
   static EOnOff 					s_eGelActivateDirIndicator[EOL::eEOLReservedItemNum];
   static ESteeringWheelPosition 	s_eSteerWheelPos;

   static BOOLEAN					s_bInitCapture;
   static Int32						s_iCamSouceIndex;
   //static stQNXCapConfig_t			s_qnxCapConfig;

   static tagRVCEOLItem					s_RVCEOLItemTable[eRVCEOLNum];
   static tagRVCEOLItem					s_RVCEOLItemTableMAN[eRVCEOLNumMAN];
    
   //add for MAN
   static UInt32 	s_eCamera_Control[EOL::eEOLReservedItemNum];
   static EMANCarType s_eMANCarType;
   static EOnOff s_eMANRestrictionsWhileDriving;
};

#endif  

