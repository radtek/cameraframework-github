#ifndef _CSVCIPC_H
#define _CSVCIPC_H

#include "foundation.h"
#include "ISvcIpc.h"
#include "ISvcIpcHooker.h"



class CBaseDBUSParser;
class CSvcIpc	: public ISvcIpc
{
public:// TODO: define const here

private:// TODO: define const here
		static const string METHOD_LABEL;
		static const string SIGAL_LABEL;
		static const string OWNER_LABEL;

public:// TODO: define embed class or struct or enum here
	

private:// TODO: define embed class or struct or enum here
	enum EEventCategory
	{
		EC_Status = 0,
		EC_Response,
		EC_Signal
	};
	
	struct tagIpcHooker
	{
		ISvcIpcHooker* hooker;

		tagIpcHooker()
		{
			hooker = NULL;
		}

		tagIpcHooker(ISvcIpcHooker* pHooker)
		{
			hooker = pHooker;
		}
	};

	struct tagSigInfo
	{
		SVCIPC_tSigSubHnd SigHnd;
		string            strToken;
	};
public:// method
	static CSvcIpc*	getInstance();
	static void deleteInstance();
	friend void onAsyncResult(const SVCIPC_tCallbackStatus* status, SVCIPC_tConstStr result, SVCIPC_tUserToken token);
	friend void onSignal(SVCIPC_tConstStr sigName, SVCIPC_tConstStr data, SVCIPC_tUserToken token);
	friend void onNotifyServiceOwnerChange(SVCIPC_tConstStr newName, SVCIPC_tConstStr oldOwner, SVCIPC_tConstStr newOwner, SVCIPC_tUserToken token);
	friend void onAsyncSubscribe(const SVCIPC_tCallbackStatus* status, SVCIPC_tSigSubHnd subHnd, SVCIPC_tUserToken token);
	friend void onRequest(SVCIPC_tReqContext context, SVCIPC_tConstStr method,
       						SVCIPC_tConstStr parms, SVCIPC_tBool noReplyExpected,
       						SVCIPC_tUserToken token);
	
	// TODO: define your public method here
	void	hook(const string &strBusName, ISvcIpcHooker* pHooker);
	void	unhook(const string &strBusName, ISvcIpcHooker* pHooker);

	void	subscribeSignal(const string &strBusName, const string &strObjPath, const string &strSignalName);
	void	unsubscribeSignal(const string &strBusName, const string &strObjPath, const string &strSignalName);
	void	subscribeServiceAvailable(const string &strBusName, const string &strObjPath);
	void	unsubscribeServiceAvailable(const string &strBusName, const string &strObjPath);

	void	registerDBusService(const string& strBusName, const string& strObjPath, ISvcIpcHooker* pService);
	void 	unRegisterDBusService(const string& strBusName, const string& strObjPath);

	void	invoke(const string &strBusName, const string &strObjPath, const string &strMethodName, const string &strJsonParams);
    void	ainvoke(const string &strBusName, const string &strObjPath, const string &strMethodName, const string &strJsonParams);
	void	emit(const string& strMethodName, const string& strParams);
	void	returnResult(SVCIPC_tReqContext context, const string& strRet);
	
	BOOLEAN start();
	void	stop();

protected:// method

private:// method
	CSvcIpc();
	virtual  ~CSvcIpc();
	// TODO: define your private method here
	void dispatchEvent(const string& strBusName, EEventCategory eCategory, const string &strName, const string &strData);
	
	void onInvokeCallback(SVCIPC_tConstStr result, SVCIPC_tUserToken token);
	void onSignal(SVCIPC_tConstStr sigName, SVCIPC_tConstStr data, SVCIPC_tUserToken token);
	void onNotifyServiceOwnerChange(SVCIPC_tConstStr newName, SVCIPC_tConstStr oldOwner, SVCIPC_tConstStr newOwner, SVCIPC_tUserToken token);
	void onSubscribeCallback(SVCIPC_tSigSubHnd subHnd, SVCIPC_tUserToken token);
	void onRequest(SVCIPC_tReqContext context, SVCIPC_tConstStr method,
       						SVCIPC_tConstStr parms, SVCIPC_tBool noReplyExpected,
       						SVCIPC_tUserToken token);
	
protected:// property

private:// property
	// TODO: define your private property here
	static CSvcIpc	*s_pInstance;
	map<string, tagIpcHooker*> m_mapSvcIpcHooker;
	map<string, tagSigInfo*>   m_mapSignal;

	ISvcIpcHooker* 		m_pService;
	SVCIPC_tConnection 	mConnnect;
	SVCIPC_tSvcRegHnd 	mRegHnd;
	BOOLEAN				m_bConnected;
};

#endif
