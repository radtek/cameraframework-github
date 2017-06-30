#include "CBaseDBUSParser.h"
#include "CAdasManager.h"

CBaseDBUSParser::CBaseDBUSParser(BOOLEAN bClient)
: m_svcipc(NULL)
, m_bClient(bClient)
, m_bAvailable(FALSE)
{
	;
}

CBaseDBUSParser::~CBaseDBUSParser()
{
	for(HashMap<string, CFunctor*>::Iterator iter = m_hmapSignalFunctor.begin();
			iter != m_hmapSignalFunctor.end(); ++iter)
	{
		(*iter).second->release();
	}

	for(HashMap<string, CFunctor*>::Iterator iter = m_hmapAResponseFunctor.begin();
				iter != m_hmapAResponseFunctor.end(); ++iter)
	{
		(*iter).second->release();
	}
   for(HashMap<string, CFunctor*>::Iterator iter = m_hmapResponseFunctor.begin();
            iter != m_hmapResponseFunctor.end(); ++iter)
   {
      (*iter).second->release();
   }

	for(HashMap<string, CFunctor2*>::Iterator iter = m_hmapRequestFunctor.begin();
				iter != m_hmapRequestFunctor.end(); ++iter)
	{
		(*iter).second->release();
	}
}

void CBaseDBUSParser::connect(ISvcIpc* psvcipc)
{
	m_svcipc = psvcipc;
	if (m_svcipc != NULL)
	{
		if( m_bClient )
		{
			m_svcipc->hook(m_strBusName, this);
			m_svcipc->subscribeServiceAvailable(m_strBusName, m_strObjPath);
		}
		else
		{
			m_svcipc->registerDBusService(m_strBusName,m_strObjPath,this);
		}
	}
}

void CBaseDBUSParser::disconnect()
{
	if (m_svcipc != NULL)
	{	
		if( m_bClient )
		{
			m_svcipc->unsubscribeServiceAvailable(m_strBusName, m_strObjPath);
			m_svcipc->unhook(m_strBusName, this);
		}
		else
		{
			m_svcipc->unRegisterDBusService(m_strBusName, m_strObjPath);
		}
		
		m_svcipc = NULL;
	}
}
TRC_SCOPE_DEF(ADAS, CBaseDBUSParser, asynSendMessage);
void CBaseDBUSParser::asynSendMessage(const tagBaseMessage& rMsg, UInt32 uiLen)
{
    TRC_SCOPE(ADAS, CBaseDBUSParser, asynSendMessage);
	DBG_MSG(("CBaseDBUSParser::asynSendMessage\n"));
	CAdasManager::getInstance()->pushMessage(rMsg, uiLen);
}
TRC_SCOPE_DEF(ADAS, CBaseDBUSParser, onServiceStatus);
void CBaseDBUSParser::onServiceStatus (BOOLEAN bAvailable)
{
    TRC_SCOPE(ADAS, CBaseDBUSParser, onServiceStatus);
	m_bAvailable = bAvailable;

	if (m_bAvailable)
	{
		DBG_MSG(("CBaseDBUSParser::onServiceStatus available!\n"));
		for(HashMap<string, CFunctor*>::Iterator iter = m_hmapSignalFunctor.begin(); iter != m_hmapSignalFunctor.end(); ++iter)
		{
			DBG_MSG(("CBaseDBUSParser::onServiceStatus subscribeSignal%s!\n", (*iter).first.c_str()));
			m_svcipc->subscribeSignal(m_strBusName, m_strObjPath, (*iter).first);
		}
	}
	else
	{
		for(HashMap<string, CFunctor*>::Iterator iter = m_hmapSignalFunctor.begin(); iter != m_hmapSignalFunctor.end(); ++iter)
		{
			m_svcipc->unsubscribeSignal(m_strBusName, m_strObjPath, (*iter).first);
		}
	}
	
	// Dispatch SIG_serviceAvailable.
	//CData_Sig_serviceAvailable *pData = new CData_Sig_serviceAvailable();
	//pData->bAvailable = bAvailable;
	//asynSendMessage(CEventCommon::SIG_serviceAvailable,pData);
}

void CBaseDBUSParser::onAResponse	(const string &strMethodName, const string &strData)
{
	HashMap<string, CFunctor*>::Iterator it= m_hmapAResponseFunctor.find(strMethodName);
	if( it!= m_hmapAResponseFunctor.end() )
	{
		CFunctor* pfunctor = (*it).second;

		(*pfunctor)(strData);
		return ;
	}
	return ;
}

void CBaseDBUSParser::onResponse	(const string &strMethodName, const string &strData)
{
	HashMap<string, CFunctor*>::Iterator it= m_hmapResponseFunctor.find(strMethodName);
	if( it!= m_hmapResponseFunctor.end() )
	{
		CFunctor* pfunctor = (*it).second;

		(*pfunctor)(strData);
		return ;
	}
	return ;
}

void CBaseDBUSParser::onSignal	(const string &strSignalName, const string &strData)
{
	HashMap<string, CFunctor*>::Iterator it= m_hmapSignalFunctor.find(strSignalName);
	if( it!= m_hmapSignalFunctor.end() )
	{
		CFunctor* pfunctor = (*it).second;
		(*pfunctor)(strData);
		return ;
	}
	return ;
}

void CBaseDBUSParser::onRequest	(SVCIPC_tReqContext context, const string &strMethodName, const string &strData)
{
	HashMap<string, CFunctor2*>::Iterator it= m_hmapRequestFunctor.find(strMethodName);
	if( it!= m_hmapRequestFunctor.end() )
	{
		CFunctor2* pfunctor = (*it).second;
		(*pfunctor)(context, strData);
		return ;
	}
	return ;
}

void CBaseDBUSParser::registerTarget(const string &strBusName, const string &strObjPath)
{
	m_strBusName = strBusName;
	m_strObjPath = strObjPath;
}

void CBaseDBUSParser::invoke(const string &strMethodName, const string &strParams)
{
   if (m_svcipc != NULL)
   {
      m_svcipc->invoke(m_strBusName, m_strObjPath, strMethodName, strParams);	
   }
}

void CBaseDBUSParser::ainvoke(const string &strMethodName, const string &strParams)
{
   if (m_svcipc != NULL)
   {
      m_svcipc->ainvoke(m_strBusName, m_strObjPath, strMethodName, strParams);	
   }
}

void CBaseDBUSParser::emit(const string &strMethodName, const string &strParams)
{
	if(m_svcipc != NULL )
	{
		m_svcipc->emit(strMethodName, strParams);
	}
}

void CBaseDBUSParser::returnResult(SVCIPC_tReqContext context, const string &strReply, const string& strToken)
{
	if(m_svcipc != NULL )
	{
		m_svcipc->returnResult(context, strReply);
	}
}

void CBaseDBUSParser::registerAResponseCallback(const string &strAResponseName, CFunctor* pFunctor)
{
	m_hmapAResponseFunctor.insert( makePair(strAResponseName, pFunctor) );
}

void CBaseDBUSParser::registerResponseCallback(const string &strResponseName, CFunctor* pFunctor)
{
	m_hmapResponseFunctor.insert( makePair(strResponseName, pFunctor) );
}

void CBaseDBUSParser::registerSignalCallback(const string &strSignalName, CFunctor* pFunctor)
{
	m_hmapSignalFunctor.insert( makePair(strSignalName, pFunctor) );
}

void CBaseDBUSParser::registerRequestCallback(const string &strRequestName, CFunctor2* pFunctor)
{
	m_hmapRequestFunctor.insert( makePair(strRequestName, pFunctor) );
}
