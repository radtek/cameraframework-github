#ifndef CGRAPHICOVERLAYTHREAD_HPP_
#define CGRAPHICOVERLAYTHREAD_HPP_

#include "CScreenWindow.h"
#include "CGraphicsThread.h"

class CBaseGraphicsImpl;

class CSimpleGraphicsThread : public CGraphicsThread
{
public:
	static CSimpleGraphicsThread* getInstance(CBaseGraphicsImpl* pGraphicsImpl=NULL);
	//static void deleteInstance();


	CSimpleGraphicsThread(const string& strName, CBaseGraphicsImpl* pGraphicsImpl);
	virtual ~CSimpleGraphicsThread();

protected:

	virtual bool initialize() ;
	virtual void unInitialize() ;
	virtual void beforeHandleMessageQueue();
	virtual void afterHandleMessageQueue();

	bool initGraphicRes();
	bool updateGraphic();
   bool PostDummyWin();
private:
   CScreenWindow* 			m_pWin;

   static CSimpleGraphicsThread*	s_pInstance;

};

#endif /* CGRAPHICOVERLAYTHREAD_HPP_ */
