#ifndef _CADASMESSAGE_QUEUE_H
#define _CADASMESSAGE_QUEUE_H

#include "common.h"
#include "mqueue.h"
#include "thread/CEvent.h"
#include "thread/Mutex.h"
#include "CMessageHandler.h"
#include "CMessage.h"

class CMessageQueue : public Ref
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
	
	void 			pushMessage(const tagBaseMessage& rMsg, UInt32 uiMsgLen);
	virtual void	handleMessageQueue();

	BOOLEAN			isEmpty();
	//virtual void  	blockHandleMessageQueue();

protected:	// method
	void	_handleMessageQueue();
	
private:	// method

protected:	// data
	//bool	 m_bQuit;

private:	// data
	string					m_strMsgQueueName;
	mqd_t  	m_iMsgQueue;

	CMessageHandler* m_pHandler;
};

#endif
