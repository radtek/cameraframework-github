#ifndef _CMSG_RUNNABLE_QNX_H_
#define _CMSG_RUNNABLE_QNX_H_

#include "foundation.h"

class CMsgQueueRunnable : public CRunnable
{
public:
	CMsgQueueRunnable(const string& strName,CEvent::CALLBACK func = NULL);
	virtual ~CMsgQueueRunnable();
	//Thread APIs
	virtual void start(void* pMsgQueue);

	// push message
	void 	pushMessage(const tagBaseMessage& rMsg, UInt32 uiLen);

protected:
	virtual void update();
	virtual void beforeHandleMessageQueue();
	virtual void afterHandleMessageQueue();

protected:	// data
	BOOLEAN	m_bInitialized;

private:	// data
   CMessageQueue*	m_pMsgQueue;	//Message Queue
};


#endif /* _CADAS_MANAGER_H_ */

