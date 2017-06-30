#ifndef _CCANPROCESSOR_HPP_
#define _CCANPROCESSOR_HPP_

#include "MessageDefineSCANIA.hpp"
#include "svs.h"
#include "CCanClient.hpp"
#include "MessageDefine.hpp"
//todo: MAN and SCAINA use same can process now....
class CCanProcessor : public CMessageSubHandler
{
public:
   static CCanProcessor* 	getInstance();
   static void 				delInstance();
   virtual ~CCanProcessor();

   DECLARE_DISPATCH

   // CCanClient
   void 	onCruiseControlVehSpeed(void* pData);
   void		onSwitchParams(void* pData);
   void     onCANOnOffParams(void* pData);

   const tagCruiseControlVehSpeed& 	getCruiseControlVehSpeed() const	{ return m_tagCruCtrlVehSpeed;	}
   const tagSwitchParams&			getSwitchParams() const				{ return m_tagSwitchParams;		}

   Float32 	getSpeed() const					{ return ((Float32)m_tagCruCtrlVehSpeed.uiWheelBasedVehSpeed/256);							}
   BOOLEAN 	isParkBrakeSwitchNotSet() const		{ return (m_LogicPBSwich == ePBS_NotSet);	}
   BOOLEAN  isIndicatorRightIntendedOn() const	{ return (m_LogicRightIndicatorIntender == eSV_On);	}
   BOOLEAN  isIndicatorLeftIntendedOn() const  	{ return (m_LogicLeftIndicatorIntender == eSV_On);	}
   //use case indicator intended should be considered both 
   BOOLEAN  isIndicatorRightIntendedOff() const	{ return (m_LogicRightIndicatorIntender == eSV_Off);	}
   BOOLEAN  isIndicatorLeftIntendedOff() const  	{ return (m_LogicLeftIndicatorIntender == eSV_Off);	}
   //this struct may cancelled by hk, it is logic state 
   BOOLEAN	isInReverse() const					{ return (m_LogicReverseGearState == eSV_On);			}
   BOOLEAN	isNotInReverse() const					{ return (m_LogicReverseGearState== eSV_Off);			}

   BOOLEAN IsWorkLightToggleOn() const	{ return (m_LogicWorkLigthToggleSwitch== eSV_On);	}
   BOOLEAN  IsOutOfStandbyWorkLight() const { return (m_tagSwitchParams.eWorkLigthToggleSwitch== eSV_On);   }
   BOOLEAN  isOutOfStandbyTurnRight() const	{ return ((m_tagSwitchParams.eRightIndicatorIntended== eSV_On)&&(m_tagSwitchParams.eLeftIndicatorIntended != eSV_Off));	}
   BOOLEAN  isOutOfStandbyTurnLeft() const  { return ((m_tagSwitchParams.eRightIndicatorIntended!= eSV_Off)&&(m_tagSwitchParams.eLeftIndicatorIntended == eSV_On));	}
   
   void vDisableWorkLightSwitch() { m_LogicWorkLigthToggleSwitch = eSV_Off; };
   void vDisableIndicatorLeft()   { m_LogicLeftIndicatorIntender = eSV_Off; };
   void vDisableIndicatorRight()  { m_LogicRightIndicatorIntender = eSV_Off; };
   void vDisableLogicState();
   void vDisableRearGearLogicState();
   void vSetRearGearLogicState();
   void vSetRearOnoffLogicState();
   void vSetFrontOnoffLogicState();
   void vSetGen1OnoffLogicState();
   void vSetGen2OnoffLogicState();
   //manually cancel rear gear state by HK
   void cancelRearGearState(BOOLEAN isautorequest);
   BOOLEAN	isDrivingForward() const					{ return (m_tagSwitchParams.eReverseSwitch == eSV_Off);}
   BOOLEAN	isReverseEngaged() const					{ return (m_tagSwitchParams.eReverseSwitch == eSV_On);}
   BOOLEAN	isCANOnOffShowRearCam() const					{ return (m_LogicRearVwCam== eCANOnOff_On);			}
   BOOLEAN	isCANOnOffShowFrntCam() const					{ return (m_LogicFrntVwCam== eCANOnOff_On);			}
   BOOLEAN	isCANOnOffShowGenCam1() const					{ return (m_LogicGenCam1== eCANOnOff_On);			}
   BOOLEAN	isCANOnOffShowGenCam2() const					{ return (m_LogicGenCam2== eCANOnOff_On);			}
   BOOLEAN	isCANOnOffShowGenCam3() const					{ return (m_LogicGenCam3== eCANOnOff_On);			}
   BOOLEAN	isCANOnOffShowGenCam4() const					{ return (m_LogicGenCam4== eCANOnOff_On);			}

   BOOLEAN	isCANOnOffRearCam() const					{ return (m_CANRequestOnOffCamera.eRearVwCam== eCANOnOff_On);			}
   BOOLEAN	isCANOnOffFrntCam() const					{ return (m_CANRequestOnOffCamera.eFrntVwCam== eCANOnOff_On);			}
   BOOLEAN	isCANOnOffGenCam1() const					{ return (m_CANRequestOnOffCamera.eGenCam1== eCANOnOff_On);			}
   BOOLEAN	isCANOnOffGenCam2() const					{ return (m_CANRequestOnOffCamera.eGenCam2== eCANOnOff_On);			}
   BOOLEAN	isCANOnOffGenCam3() const					{ return (m_CANRequestOnOffCamera.eGenCam3== eCANOnOff_On);			}
   BOOLEAN	isCANOnOffGenCam4() const					{ return (m_CANRequestOnOffCamera.eGenCam4== eCANOnOff_On);			}

private:
   CCanProcessor();

private: // data
   static CCanProcessor* s_pInstance;

   tagCruiseControlVehSpeed 	m_tagCruCtrlVehSpeed;
   tagSwitchParams				m_tagSwitchParams;//MAN share this msg now
   tagCANRequestOnOffCamera     m_CANRequestOnOffCamera;
   //a rear gear logic state for reverse camera
   ESwitchValue                 m_LogicReverseGearState;
   //logic state for all event to support standby event cancel camera active state
   EParkBrakeSwitch             m_LogicPBSwich;
   ESwitchValue                 m_LogicRightIndicatorIntender;
   ESwitchValue                 m_LogicLeftIndicatorIntender;
   ESwitchValue                 m_LogicWorkLigthToggleSwitch;
   #if 1
   //logic state for direcly request, not provide in pps interface so comment first
   ECANOnOffValue               m_LogicRearVwCam;
   ECANOnOffValue               m_LogicFrntVwCam;
   ECANOnOffValue               m_LogicGenCam1;
   ECANOnOffValue               m_LogicGenCam2;
   ECANOnOffValue               m_LogicGenCam3;
   ECANOnOffValue               m_LogicGenCam4;
   #endif
};

#endif  

