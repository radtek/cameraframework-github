#ifndef _CMESSAGE_H
#define _CMESSAGE_H

#include "common.h"


struct tagBaseMessage
{
	tagBaseMessage(UInt32 uiType, UInt32 uiID)
	: _uiType(uiType)
	, _uiID(uiID)
	{
		;
	}

	tagBaseMessage()
	: _uiType(0)
	, _uiID(0)
	{
		;
	}

	UInt32 _uiType;
	UInt32 _uiID;
};

#endif
