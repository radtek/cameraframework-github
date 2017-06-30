#ifndef _CBASE_DBUSPARSER_H
#define _CBASE_DBUSPARSER_H

#include "foundation.h"
#include "ISvcIpc.h"
#include "ISvcIpcHooker.h"




class CBaseDBUSParser : public ISvcIpcHooker
{
public:	// class enum struct

private: // class enum struct, typedef
	typedef CFunctorArg1<const string&> 					CFunctor;
	typedef CFunctorArg2<SVCIPC_tReqContext, const string&>	CFunctor2;

public: // method
	//CBaseDBUSParser();
	virtual ~CBaseDBUSParser();
	
	// TODO: implement IBaseService here
	virtual	void	connect(ISvcIpc* psvcipc);
	virtual	void	disconnect();
	virtual BOOLEAN	isAvailable()	{ return m_bAvailable; }

	void			asynSendMessage(const tagBaseMessage& rMsg, UInt32 uiLen);
			
protected:// method
	CBaseDBUSParser(BOOLEAN bClient=TRUE);		
	
	// beidong
	void 	onServiceStatus (BOOLEAN bAvailable);
	void 	onAResponse	(const string &strMethodName, const string &strData);
	void 	onResponse	(const string &strMethodName, const string &strData);
	void 	onSignal	(const string &strSignalName, const string &strData);
	void	onRequest(SVCIPC_tReqContext context, const string &strMethodName, const string &strData);
	// zhudong
	void	invoke(const string &strMethodName, const string &strParams);
    void	ainvoke(const string &strMethodName, const string &strParams);
	void	emit(const string &strMethodName, const string &strParams);
	void	returnResult(SVCIPC_tReqContext context, const string &strReply, const string& strToken);
	// register 
	void	registerTarget	(const string &strBusName, const string &strObjPath);
	void	registerResponseCallback(const string &strResponseName, CFunctor* pFunctor);
    void	registerAResponseCallback(const string &strAResponseName, CFunctor* pFunctor);
	void	registerSignalCallback(const string &strSignalName, CFunctor* pFunctor);
	void	registerRequestCallback(const string &strRequestName, CFunctor2* pFunctor);
	
private:// method

protected:// property
	ISvcIpc*			m_svcipc;

private:// property
	BOOLEAN				m_bClient;
	BOOLEAN				m_bAvailable;

	string				m_strBusName;
	string				m_strObjPath;
	
	HashMap<string, CFunctor*>	m_hmapSignalFunctor;
	HashMap<string, CFunctor*>	m_hmapAResponseFunctor;
    HashMap<string, CFunctor*>	m_hmapResponseFunctor;
	HashMap<string, CFunctor2*>	m_hmapRequestFunctor;
};

#endif
