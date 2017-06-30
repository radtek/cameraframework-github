#ifndef _CSCANIA_MESSAGEHANDLER_H
#define _CSCANIA_MESSAGEHANDLER_H

#include "svs.h"

class CSCANIAMessageHandler : public CMessageHandler
{
public:

protected:
	virtual void _handle(UInt32 uiType, UInt32 uiID, void* pData);

};


#endif
