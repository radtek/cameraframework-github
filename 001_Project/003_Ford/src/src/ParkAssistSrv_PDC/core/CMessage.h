#ifndef _CMESSAGE_H
#define _CMESSAGE_H
#pragma once
struct tagBaseMessage
{
	tagBaseMessage(unsigned int uiType,unsigned int uiID, char* pData)
	: _uiType(uiType)
	, _uiID(uiID)
	, _pData(pData)
	{
		;
	}

	tagBaseMessage()
	: _uiType(0)
	, _uiID(0)
	, _pData(0)
	{
		;
	}

	unsigned int _uiType;
	unsigned int _uiID;
	char* _pData;
};

#endif
