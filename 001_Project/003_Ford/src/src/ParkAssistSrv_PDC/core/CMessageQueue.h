#ifndef _CMESSAGE_QUEUE_H
#define _CMESSAGE_QUEUE_H
#include "TraceMacros.h"
#include "CMessageHandler.h"
#include "CMessage.h"
#include <condition_variable>
#include <queue>
#include <string>
using namespace std;

class CMessageQueue
{
public:	// class enum struct
	enum EType
	{
		ET_BLOCK		= 0X00000001,
		ET_NONBLOCK		= 0X00000002,
	};

private: // class enum struct

public: // method
	CMessageQueue(const string& strMsgQueueName, unsigned int uiQueueMaxSize, CMessageHandler* pHandler);
	virtual ~CMessageQueue();
	
	void 			pushMessage(const tagBaseMessage& rMsg, int uiMsgLen=0);
	virtual void	handleMessageQueue();

	bool			isEmpty();
	//virtual void  	blockHandleMessageQueue();

protected:	// method
	void	_handleMessageQueue();
	
private:	// method

protected:	// data
	//bool	 m_bQuit;

private:	// data
	string					m_strMsgQueueName;
    queue<tagBaseMessage>  	m_iMsgQueue;
	condition_variable mWaitEventCondVar;
	mutex mEventlockMutex;
	tagBaseMessage mEventData;

	CMessageHandler* m_pHandler;
};

#endif
