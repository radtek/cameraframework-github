#ifndef _CSIMPLE_CAPTURE_MESSAGEHANDLER_H
#define _CSIMPLE_CAPTURE_MESSAGEHANDLER_H

#include "foundation.h"

class CSimpleCaptureMessageHandler : public CMessageHandler
{
public:

protected:
	virtual void _handle(UInt32 uiType, UInt32 uiID, void* pData);

};


#endif
