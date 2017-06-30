#ifndef _CMESSAGE_HANDLER_H
#define _CMESSAGE_HANDLER_H
#pragma once
#include  "CMessage.h"
#define BEGIN_DISPATCH(CLASSNAME)	\
void CLASSNAME::dispatchEvent(unsigned int uiEventID, void* pData)	\
{\
	switch(uiEventID)	\
	{

#define DISPATCH_EVENT(uiEventID, Function)	\
		case (uiEventID):	\
		{	\
			Function(pData);\
		}	\
		break;

#define DISPATCH_EVENT_NOPARAM(uiEventID, Function)	\
		case (uiEventID):	\
		{	\
			Function();\
		}	\
		break;

#define END_DISPATCH	\
		default:	\
			break;	\
	}	\
	return;	\
}

#define DECLARE_DISPATCH	\
	virtual void dispatchEvent(unsigned int uiEventID, void* pData);





class CMessageHandler
{
public:
	//CMessageHandler();
	//virtual ~CMessageHandler();

	void handle(tagBaseMessage* pMsg);

protected:
	/*switch( uiType )
		{
		case eMsgType_CAN:
			xxSubHandler::getInstance()->dispatchEvent(uiID, pData);
			break;
		case eMsgType_HMI:
			xxSubHandler::getInstance()->dispatchEvent(uiID, pData);
			break;
		case eMsgType_ScaniaOnOff:
			xxSubHandler::getInstance()->dispatchEvent(uiID, pData);
			break;
		case eMsgType_Diagnostic:
			xxSubHandler::getInstance()->dispatchEvent(uiID, pData);
			break;
		}
	 */
	virtual void _handle(unsigned int uiType, unsigned int uiEventID, void* pData) = 0;

};


class CMessageSubHandler
{
public:
	virtual void dispatchEvent(unsigned int uiEventID, void* pData) = 0;
};


#endif
