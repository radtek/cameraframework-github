#ifndef _CMESSAGE_HANDLER_H
#define _CMESSAGE_HANDLER_H

#include "common.h"

#define BEGIN_DISPATCH(CLASSNAME)	\
void CLASSNAME::dispatchEvent(UInt32 uiEventID, void* pData)	\
{\
	switch(uiEventID)	\
	{

#define DISPATCH_EVENT(uiEventID, Function)	\
		case uiEventID:	\
		{	\
			Function(pData);\
		}	\
		break;

#define DISPATCH_EVENT_NOPARAM(uiEventID, Function)	\
		case uiEventID:	\
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
	virtual void dispatchEvent(UInt32 uiEventID, void* pData);





class CMessageHandler
{
public:
	//CMessageHandler();
	//virtual ~CMessageHandler();

	void handle(UInt32* pMsg);

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
	virtual void _handle(UInt32 uiType, UInt32 uiEventID, void* pData) = 0;

};


class CMessageSubHandler
{
public:
	virtual void dispatchEvent(UInt32 uiEventID, void* pData) = 0;
};


#endif
