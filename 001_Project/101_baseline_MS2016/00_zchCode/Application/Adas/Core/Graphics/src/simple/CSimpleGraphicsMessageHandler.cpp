#include "CSimpleGraphicsMessageHandler.h"
#include "CSimpleGraphicsThread.h"

void CSimpleGraphicsMessageHandler::_handle(UInt32 uiType, UInt32 uiID, void* pData)
{
	if( CSimpleGraphicsThread::getInstance() )
	{
		CBaseGraphicsImpl* pGraphicsImpl = CSimpleGraphicsThread::getInstance()->getGraphicsImpl();
		if( pGraphicsImpl )
		{
			pGraphicsImpl->dispatchEvent(uiID, pData);
		}
	}
}
