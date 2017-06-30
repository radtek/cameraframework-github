#ifndef _C_ADAS_MANAGER_H_
#define _C_ADAS_MANAGER_H_


#include "foundation.h"
#include "IAdasCtrl.h"

#define SEND_BASEMESSAGE(uiType, uiID)	\
	CAdasManager::getInstance()->pushMessage(tagBaseMessage(uiType,uiID), sizeof(tagBaseMessage));

class CAdasManager : public IRunnable
{
public:
	static CAdasManager* 	getInstance();
	static void				deleteInstance();
	virtual ~CAdasManager();

	//Thread APIs
	void start(CMessageQueue* pMsgQueue, IAdasCtrl* pCtrl);
	void quit();
	void join();
	void run();

	void resume();

	// push message
	void pushMessage(const tagBaseMessage& rMsg, UInt32 uiLen);

protected:
	CAdasManager();

protected:	// data

private:	// data
	static CAdasManager*	s_pInstance;

   CMessageQueue*	m_pMsgQueue;	//Message Queue
   IAdasCtrl*		m_pCtrl;

   //Thread
   Thread  			m_hThread;

   CEvent			m_event;
   BOOLEAN		 	m_bQuit;
};


#endif /* _CADAS_MANAGER_H_ */

