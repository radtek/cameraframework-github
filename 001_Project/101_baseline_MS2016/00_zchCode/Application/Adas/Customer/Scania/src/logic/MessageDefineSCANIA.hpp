#ifndef _MESSAGE_DEFINE_SCANIA_H
#define _MESSAGE_DEFINE_SCANIA_H

#include "svs.h"
//#include "CAdasMsgQueDefineSCAINA.hpp"
#include "MessageDefine.hpp"

//----------------------------------CAN--------------------------------------------


enum ECANOnOffValue
{
	eCANOnOff_Off 			   = 0,
	eCANOnOff_On				= 1,
	eCANOnOff_Error				= 2,
	eCANOnOff_NotAvailable		= 3,
};

struct tagCANRequestOnOffCamera : public tagBaseMessage
{
	tagCANRequestOnOffCamera()
	: tagBaseMessage(eMsgType_CAN, eCANRequestOnOffCamera)
	{

	}

   ECANOnOffValue	eGenCam1	;
   ECANOnOffValue	eGenCam2	;
   ECANOnOffValue	eGenCam3	;
   ECANOnOffValue	eGenCam4	;
   ECANOnOffValue	eRearVwCam	;
   ECANOnOffValue	eFrntVwCam	;
   
};

#endif
