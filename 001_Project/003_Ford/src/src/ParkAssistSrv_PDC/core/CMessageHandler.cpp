#include "CMessageHandler.h"


void CMessageHandler::handle(tagBaseMessage* pMsg)
{
	unsigned int ucType = pMsg->_uiType;
	unsigned int uiID =  pMsg->_uiID;

	_handle(ucType, uiID, (void*)pMsg->_pData);
}
