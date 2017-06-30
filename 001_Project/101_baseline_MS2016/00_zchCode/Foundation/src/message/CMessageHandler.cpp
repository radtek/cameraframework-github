#include "CMessageHandler.h"


void CMessageHandler::handle(UInt32* pMsg)
{
	UInt32 uiType = pMsg[0];
	UInt32 uiID = pMsg[1];

	_handle(uiType, uiID, (void*)pMsg);
}
