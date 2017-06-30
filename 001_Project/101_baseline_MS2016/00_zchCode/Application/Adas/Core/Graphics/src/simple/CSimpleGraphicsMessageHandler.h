#ifndef _CSIMPLE_GRAPHICS_MESSAGEHANDLER_H
#define _CSIMPLE_GRAPHICS_MESSAGEHANDLER_H

#include "foundation.h"

class CSimpleGraphicsMessageHandler : public CMessageHandler
{
public:

protected:
	virtual void _handle(UInt32 uiType, UInt32 uiID, void* pData);

};


#endif
