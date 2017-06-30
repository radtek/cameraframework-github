#include "CSvcIpc.h"
#include "CBaseDBUSParser.h"
#include "foundation.h"


CSvcIpc	*CSvcIpc::s_pInstance	= NULL;
const string CSvcIpc::METHOD_LABEL = ". MethodName is ";
const string CSvcIpc::SIGAL_LABEL = ". SigalName is ";
const string CSvcIpc::OWNER_LABEL = " is owner change";

void printError(const SVCIPC_tCallbackStatus* status, SVCIPC_tUserToken token)
{
	;
}

//for friend function
TRC_SCOPE_DEF(ADAS, CSvcIpc, onAsyncResult);
void onAsyncResult(const SVCIPC_tCallbackStatus* status, SVCIPC_tConstStr result, SVCIPC_tUserToken token)
{
    TRC_SCOPE(ADAS, CSvcIpc, onAsyncResult);
	if (status != NULL && SVCIPC_IS_ERROR(status->errCode))
	{
		DBG_MSG(("AsyncResult failed errCode = %u\n",SVCIPC_ERR_GET_CODE(status->errCode)));
		//printError(status, token);
		return;
	}
	CSvcIpc::getInstance()->onInvokeCallback(result, token);
}

void onSignal(SVCIPC_tConstStr sigName, SVCIPC_tConstStr data, SVCIPC_tUserToken token)
{
	CSvcIpc::getInstance()->onSignal(sigName, data, token);
}

TRC_SCOPE_DEF(ADAS, CSvcIpc, onAsyncSubscribe);
void onAsyncSubscribe(const SVCIPC_tCallbackStatus* status, SVCIPC_tSigSubHnd subHnd, SVCIPC_tUserToken token)
{
    TRC_SCOPE(ADAS, CSvcIpc, onAsyncSubscribe);
	if (status != NULL && SVCIPC_IS_ERROR(status->errCode))
	{
		DBG_MSG(("AsyncSubscribe failed errCode = %u\n",SVCIPC_ERR_GET_CODE(status->errCode)));
		//printError(status, token);
		return;
	}

	DBG_MSG(("AsyncSubscribe success\n"));
	CSvcIpc::getInstance()->onSubscribeCallback(subHnd, token);
}

void onNotifyServiceOwnerChange(SVCIPC_tConstStr newName, SVCIPC_tConstStr oldOwner, SVCIPC_tConstStr newOwner, SVCIPC_tUserToken token)
{
	CSvcIpc::getInstance()->onNotifyServiceOwnerChange(newName, oldOwner, newOwner, token);
}

void onRequest(SVCIPC_tReqContext context, SVCIPC_tConstStr method,
   						SVCIPC_tConstStr parms, SVCIPC_tBool noReplyExpected,
   						SVCIPC_tUserToken token)
{
	CSvcIpc::getInstance()->onRequest(context,method,parms,noReplyExpected,token);

	SVCIPC_freeReqContext(context);
}

TRC_SCOPE_DEF(ADAS, CSvcIpc, onReturnResults);
void onReturnResults(const SVCIPC_tCallbackStatus* status, SVCIPC_tUserToken token)
{
    TRC_SCOPE(ADAS, CSvcIpc, onReturnResults);
	SVCIPC_tConstStr msg;
	if (token != 0)
	{
	   msg = static_cast< SVCIPC_tConstStr >(token);
	}
	else
	{
	   msg = "";
	}

	if (status)
	{
		if (SVCIPC_IS_ERROR(status->errCode))
		{
			DBG_ERROR(("%s: Error=> %d Name= %s Msg=> %s\n", msg,
					status->errCode,
					(status->errName ? status->errName : "unknown"),
					(status->errMsg ? status->errMsg : "unknown")));

		}
		else
		{
			DBG_MSG(("%s: sent successfully\n", msg));
		}
	}
	else
	{
		DBG_ERROR(("%s: status is NULL\n", msg));
	}
}

CSvcIpc* CSvcIpc::getInstance()
{
	if (s_pInstance == NULL)
	{
		s_pInstance = new CSvcIpc();
	}

	return s_pInstance;
}

void CSvcIpc::deleteInstance()
{
	if (s_pInstance != NULL)
	{
		delete s_pInstance;
		s_pInstance = NULL;
	}
}

CSvcIpc::CSvcIpc()
	: m_pService(NULL)
	, mConnnect(NULL)
	, mRegHnd(NULL)
	, m_bConnected(FALSE)
{
	;	
}

CSvcIpc::~CSvcIpc()
{
	m_mapSvcIpcHooker.clear();
	m_mapSignal.clear();
	stop();
}

// TODO: implement your public method here
void CSvcIpc::hook(const string &strBusName, ISvcIpcHooker *pHooker)
{
	if (m_bConnected)
	{
		tagIpcHooker *pData = new tagIpcHooker(pHooker);
		m_mapSvcIpcHooker.insert( makePair(strBusName, pData) );
	}
   //todo:add fail process
   else
      {

   }
}

void CSvcIpc::unhook(const string &strBusName, ISvcIpcHooker* pHooker)
{
	if (m_bConnected)
	{
		m_mapSvcIpcHooker.erase(strBusName);
	}
}
TRC_SCOPE_DEF(ADAS, CSvcIpc, subscribeSignal);
void CSvcIpc::subscribeSignal(const string &strBusName, const string &strObjPath, const string &strSignalName)
{
    TRC_SCOPE(ADAS, CSvcIpc, subscribeSignal);
	if (FALSE == m_bConnected)  return;

	SVCIPC_tError rc;
	string strToken = strBusName + SIGAL_LABEL + strSignalName;

	tagSigInfo* pData = new tagSigInfo;
	pData->strToken = strToken;

	//SVCIPC_tSigSubHnd hHnd;
	rc = SVCIPC_asyncSubscribe(mConnnect,
						strObjPath.c_str(),
						strSignalName.c_str(),
						::onSignal,
						::onAsyncSubscribe,
						(SVCIPC_tUserToken)pData->strToken.c_str());
	
	if (SVCIPC_IS_ERROR(rc))
	{
		DBG_MSG(("CSvcIpc Failed to subscribe signal on server.\n  busName: %s, Signal is %s\n",
				strBusName.c_str(),strSignalName.c_str()));

		delete pData;

	}
	else
	{
		DBG_MSG(("CSvcIpc subscribe signal on server.\n busName: %s, Signal is %s token is %s\n",
				strBusName.c_str(), strSignalName.c_str(), strToken.c_str() ));

		pData->SigHnd = NULL;
		m_mapSignal.insert(makePair(strToken, pData));
	}
}

TRC_SCOPE_DEF(ADAS, CSvcIpc, unsubscribeSignal);
void CSvcIpc::unsubscribeSignal(const string &strBusName, const string &strObjPath, const string &strSignalName)
{
    TRC_SCOPE(ADAS, CSvcIpc, unsubscribeSignal);
	if (FALSE == m_bConnected)  return;

	string strToken = strBusName + SIGAL_LABEL + strSignalName;

	map<string, tagSigInfo*>::iterator it = m_mapSignal.find(strToken);
	if ( it != m_mapSignal.end() )
	{
		const tagSigInfo* pData = (*it).second;
		if( pData == NULL)
			return;

		SVCIPC_tError rc = SVCIPC_asyncUnsubscribe(pData->SigHnd, NULL, 0);
		if (SVCIPC_IS_ERROR(rc))
		{
			//CLog::error2(TRC_NAME_W, (const CHAR*)string::format(L"CSvcIpcClient Failed to unsubscribe signal.\n BusName is %ls, ObjPath is %ls, Signal is %ls\n",
			//				(const CHAR*)strBusName, (const CHAR*)strObjPath, (const CHAR*)strSignalName));
			DBG_MSG(("CSvcIpc async unsubscribe on server\n"));
		}

		m_mapSignal.erase(it);
	}
}
TRC_SCOPE_DEF(ADAS, CSvcIpc, subscribeServiceAvailable);
void CSvcIpc::subscribeServiceAvailable(const string &strBusName, const string &strObjPath)
{
    TRC_SCOPE(ADAS, CSvcIpc, subscribeServiceAvailable);
	if (FALSE == m_bConnected)  return;
	
	SVCIPC_tBool bAvail = SVCIPC_FALSE;
	SVCIPC_tSigSubHnd ownerSub;

	SVCIPC_tError rc = SVCIPC_nameHasOwner(mConnnect, strBusName.c_str(), &bAvail);
	
	if (SVCIPC_IS_ERROR(rc))
	{
		DBG_MSG(( "CSvcIpcClient Failed to nameHasOwner service.\n Busnamei is %s, ObjPath, %s",
					strBusName.c_str(), strObjPath.c_str() ) );
		return;
	}
	
	if(bAvail)
	{
		DBG_MSG(( "Service Owner is available.\nBusName is %s.\n",
						strBusName.c_str() ) );
		dispatchEvent(strBusName, EC_Status, "available", STRING_NULL);
	}
	else
	{
		DBG_MSG(("Service Owner is unavailable.\nBusName is %s.\n",
						strBusName.c_str()));
	}

	rc = SVCIPC_subscribeOwnerChanged(mConnnect, strBusName.c_str(),
                             ::onNotifyServiceOwnerChange,
                             NULL,//(SVCIPC_tUserToken)pcBusName,
                             &ownerSub);
	
	if (SVCIPC_IS_ERROR(rc))
	{
		DBG_MSG(("CSvcIpc subscribe owner changed on server.\n"));
	}


	tagSigInfo* pData = new tagSigInfo;
	//pData->pcToken = NULL;
	pData->SigHnd = ownerSub;
	m_mapSignal.insert(makePair(strBusName + OWNER_LABEL, pData));
	
}
TRC_SCOPE_DEF(ADAS, CSvcIpc, unsubscribeServiceAvailable);
void CSvcIpc::unsubscribeServiceAvailable(const string &strBusName, const string &strObjPath)
{
	if (FALSE == m_bConnected)  return;

	string strToken = strBusName + OWNER_LABEL;

	map<string, tagSigInfo*>::iterator it = m_mapSignal.find(strToken);
	if(it != m_mapSignal.end() && (*it).second != NULL )
	{
		SVCIPC_tError rc = SVCIPC_unsubscribe((*it).second->SigHnd);
		if (SVCIPC_IS_ERROR(rc))
		{
			TRC_SCOPE(ADAS, CSvcIpc, unsubscribeServiceAvailable);
			//CLog::error2(TRC_NAME_W, (const CHAR*)string::format(L"CSvcIpcClient Failed to unsubscribe Service\n Busnamei is %ls, ObjPath, %ls",
			//				(const CHAR*)strBusName, (const CHAR*)strObjPath));
			DBG_ERROR(("FAILED to unsubscribe service %s\n",strBusName.c_str() ));
		}
		m_mapSignal.erase(it);

	}
}

TRC_SCOPE_DEF(ADAS, CSvcIpc, registerDBusService);
void CSvcIpc::registerDBusService(const string& strBusName, const string& strObjPath, ISvcIpcHooker* pService)
{
    TRC_SCOPE(ADAS, CSvcIpc, registerDBusService);
	if( pService )
	{
		m_pService = pService;
	}
	SVCIPC_tError rc = SVCIPC_registerService(mConnnect, strBusName.c_str(), strObjPath.c_str(),
									0, ::onRequest, NULL, &mRegHnd);

	if (SVCIPC_IS_ERROR(rc))
	{
		DBG_MSG(("CSvcIpc::registerDBusService failed dbusName=%s objName=%s\n", strBusName.c_str(), strObjPath.c_str()));
	}
	else
	{
		DBG_MSG(("CSvcIpc::registerDBusService succeed dbusName=%s objName=%s\n", strBusName.c_str(), strObjPath.c_str()));
		if( pService )
			pService->onServiceStatus(TRUE);
	}

}
TRC_SCOPE_DEF(ADAS, CSvcIpc, unRegisterDBusService);
void CSvcIpc::unRegisterDBusService(const string& strBusName, const string& strObjPath)
{
	m_pService = NULL;
	SVCIPC_tError rc = SVCIPC_unregisterService(&mRegHnd);
	mRegHnd = NULL;
	if (SVCIPC_IS_ERROR(rc))
	{
		TRC_SCOPE(ADAS, CSvcIpc, unRegisterDBusService);
		//CLog::error2(TRC_NAME_W, (const CHAR*)string::format(L"CSvcIpcClient Failed to registerDBusService.\n BusName is %ls, ObjPath is %ls",
		//				(const CHAR*)strBusName, (const CHAR*)strObjPath) );
		DBG_ERROR(("unRegisterDBusService failed\n"));
	}
	else
	{
		//CLog::debug2(TRC_NAME_W, (const CHAR*)string::format(L"CSvcIpcClient successfully registerDBusService.\n BusName is %ls, ObjPath is %ls",
		//				(const CHAR*)strBusName, (const CHAR*)strObjPath );
	}
}
TRC_SCOPE_DEF(ADAS, CSvcIpc, invoke);
void CSvcIpc::invoke(const string &strBusName, const string &strObjPath, const string &strMethodName, const string &strJsonParams)
{
    TRC_SCOPE(ADAS, CSvcIpc, invoke);
   if (FALSE == m_bConnected) return;

   SVCIPC_tError rc = SVCIPC_ERROR_NONE;
   SVCIPC_tResponse * pResponse;
   int msecTimeout = 300;
   
   SVCIPC_tString result;

   Json::Value mParms;
   Json::FastWriter fastWriter;
	std::string ret;
   Json::Reader reader;

   rc = SVCIPC_invoke(mConnnect,
                     strBusName.c_str(),
                     strObjPath.c_str(),
                     strMethodName.c_str(),
                     strJsonParams.c_str(),
                     msecTimeout,
                     &pResponse);
   
   if ( SVCIPC_IS_ERROR(rc) )
   {
      DBG_MSG(("Failed to invoke method on server: 0x%0X", rc));
   }
   else
   {
      DBG_MSG(("Invoke method on server is ok!\n"));
   } 
	map<string, tagIpcHooker*>::iterator it = m_mapSvcIpcHooker.find(strBusName);

	if( it == m_mapSvcIpcHooker.end() || (*it).second == NULL )
   {  
      DBG_MSG(("CSvcIpc::m_mapSvcIpcHooker missing!\n"));
		return;
   }
	//DBG_MSG(("CSvcIpc::dispatchEvent2\n"));
	ISvcIpcHooker* pHooker = (*it).second->hooker;
	if (pHooker == NULL)
		return;

   DBG_MSG(("strMethodName = %s\n",strMethodName.c_str()));
   
   result = pResponse->result;
   if(!reader.parse(result ? result : "{}", mParms, false))
   {
      DBG_MSG(("CSvcIpc::invoke result format failed = %s\n",strMethodName.c_str()));
      mParms.clear();
   }
   else
   {
      ret = fastWriter.write(mParms);
      pHooker->onResponse(strMethodName, ret);
   }
	
   SVCIPC_freeResponse(pResponse);
}

void CSvcIpc::ainvoke(const string &strBusName, const string &strObjPath, const string &strMethodName, const string &strJsonParams)
{
   if (FALSE == m_bConnected)	return;	

   SVCIPC_tError rc;
   SVCIPC_tHandle invokeHnd;
	string strToken = strBusName + METHOD_LABEL + strMethodName;
   //string strToken = "testToken";
   //DBG_MSG(("------------->CSvcIpc::ainvoke token = %s\n",strToken.c_str()));

   rc = SVCIPC_asyncInvoke(mConnnect,
                           strBusName.c_str(),
                           strObjPath.c_str(),
                           strMethodName.c_str(),
                           strJsonParams.c_str(),
                           false,
                           -1,
                           onAsyncResult,
                           &invokeHnd,
                           (SVCIPC_tUserToken)(strToken.c_str()));

   if (SVCIPC_IS_ERROR(rc))
   {
   //CLog::error2(TRC_NAME_W, (const CHAR*)string::format(L"CSvcIpcClient Failed to invoke method on server.\n BusName is %ls, ObjPath is %ls, method is %ls",
   //				(const CHAR*)strBusName, (const CHAR*)strObjPath, (const CHAR*)strJsonParams));
   }
   else
   {
   //CLog::debug2(TRC_NAME_W, (const CHAR*)string::format(L"CSvcIpcClient successfully invoke method on server.\n BusName is %ls, ObjPath is %ls, method is %ls",
   //				(const CHAR*)strBusName, (const CHAR*)strObjPath, (const CHAR*)strJsonParams));
   }

}

TRC_SCOPE_DEF(ADAS, CSvcIpc, emit);
void CSvcIpc::emit(const string& strMethodName, const string& strParams)
{
    TRC_SCOPE(ADAS, CSvcIpc, emit);
	SVCIPC_tError rc = SVCIPC_emit(mRegHnd, strMethodName.c_str(), strParams.c_str());

	if (SVCIPC_IS_ERROR(rc))
	{
	  DBG_MSG(("SVCIPC_emit() error "));
	  //eResult = 1;
	}
}

TRC_SCOPE_DEF(ADAS, CSvcIpc, returnResult);
void CSvcIpc::returnResult(SVCIPC_tReqContext context, const string& strRet)
{
    TRC_SCOPE(ADAS, CSvcIpc, returnResult);
	SVCIPC_tError rc = SVCIPC_asyncReturnResult(context, strRet.c_str(), onReturnResults, NULL);
	if ( SVCIPC_IS_ERROR(rc) )
	{
		DBG_MSG(("Failed to ReturnResult, \n"));
	}
}

TRC_SCOPE_DEF(ADAS, CSvcIpc, start);
BOOLEAN CSvcIpc::start()
{		
    TRC_SCOPE(ADAS, CSvcIpc, start);
	SVCIPC_tError rc = SVCIPC_initialize();
	if (SVCIPC_IS_ERROR(rc))
	{
		DBG_MSG(("CSvcIpc Failed to initialize SvcIpc!\n"));
		return FALSE;
	}
	rc = SVCIPC_getConnection(SVCIPC_CONNECTION_SESSION, 0, &mConnnect);
	if ( SVCIPC_IS_ERROR(rc) )
	{
		DBG_MSG(("CSvcIpc Failed to connect to SvcIpc!\n"));
		return FALSE;
	}
	m_bConnected = TRUE;
	DBG_MSG(("Connect to SvcIpc successfully!\n"));
	return TRUE;
}

TRC_SCOPE_DEF(ADAS, CSvcIpc, stop);
void CSvcIpc::stop()
{
    TRC_SCOPE(ADAS, CSvcIpc, stop);
	if (TRUE == m_bConnected)
	{
		m_bConnected = FALSE;
		SVCIPC_tError rc = SVCIPC_closeConnection(mConnnect);
		if (SVCIPC_IS_ERROR(rc))
		{
			DBG_MSG(("CSvcIpc Failed to SVCIPC_closeConnection!\n"));
			return;
		}

		SVCIPC_shutdown();
		DBG_MSG(("Disconnect to SvcIpc successfully!\n"));
	}
}

void CSvcIpc::dispatchEvent(const string& strBusName, EEventCategory eCategory, const string &strName, const string &strData)
{
	//DBG_MSG(("CSvcIpc::dispatchEvent1\n"));
	map<string, tagIpcHooker*>::iterator it = m_mapSvcIpcHooker.find(strBusName);

	if( it == m_mapSvcIpcHooker.end() || (*it).second == NULL )
		return;

	//DBG_MSG(("CSvcIpc::dispatchEvent2\n"));
	ISvcIpcHooker* pHooker = (*it).second->hooker;
	if (pHooker == NULL)
		return;

	switch (eCategory)
	{
	case EC_Status:
		//DBG_MSG(("CSvcIpc::dispatchEvent:onServiceStatus %s\n", strName.c_str()));
		pHooker->onServiceStatus(strName == "available");

		break;

	case EC_Response:
		pHooker->onAResponse(strName, strData);
		break;

	case EC_Signal:
		pHooker->onSignal(strName, strData);
		break;
	}
}

void CSvcIpc::onInvokeCallback(SVCIPC_tConstStr result, SVCIPC_tUserToken token)
{
	string strToken((char*)token);
	string strData;
	//string::convertFromMBCS((char *)token, strToken);
	string::size_type iPos = strToken.find(METHOD_LABEL,0);
	if (iPos == string::npos )  return;
	
	string strDbusName = strToken.substr(0, iPos);
	string strMethod = strToken.substr(iPos + METHOD_LABEL.length(), strToken.length() - METHOD_LABEL.length() - iPos);
	
   if(strDbusName.empty()) 
   {
      printf("The service does not support token with dbus name inside\n");
      return;
   }
      
	//CLog::debug2(TRC_NAME_W, (const CHAR*)string::format(L"Recieve a response.\n, DbusName is %ls, Method is %ls, Data is %ls",
	//				(const CHAR*)strDbusName, (const CHAR*)strMethod, (const CHAR*)strData));

	if ( strData.empty() )
	{
		//CLog::debug2(TRC_NAME_W, (const CHAR*)string::format(L"This reponse's data is empty!"));
		strData = "";
	}

	dispatchEvent(strDbusName, EC_Response, strMethod, strData);
	
}

TRC_SCOPE_DEF(ADAS, CSvcIpc, onSignal);
void CSvcIpc::onSignal(SVCIPC_tConstStr sigName, SVCIPC_tConstStr data, SVCIPC_tUserToken token)
{
    TRC_SCOPE(ADAS, CSvcIpc, onSignal);
	string strToken((char*)token);
	string strData((char*)data);

	DBG_MSG(("signal %s %s\n",(char*)data, strToken.c_str()));

	string::size_type iPos = strToken.find(SIGAL_LABEL,0);
	if (iPos == string::npos )  return;

	string strDbusName = strToken.substr(0, iPos);
	string strSignal = strToken.substr(iPos + SIGAL_LABEL.length(), strToken.length() - SIGAL_LABEL.length() - iPos);

	if ( strData.empty() )
	{
		//CLog::debug2(TRC_NAME_W, (const CHAR*)string::format(L"This signal's data is empty!"));
		strData = "";
	}

	dispatchEvent(strDbusName, EC_Signal, strSignal, strData);
}

void CSvcIpc::onNotifyServiceOwnerChange(SVCIPC_tConstStr newName, SVCIPC_tConstStr oldOwner, SVCIPC_tConstStr newOwner, SVCIPC_tUserToken token)
{	
	string strDbusName(newName);
    //input is string type, so make "" as NULL input 
	if (0 == strcmp(oldOwner, "") && 0 != strcmp(newOwner, ""))
	{
        fprintf(stderr,"ADAS newOwner = %s\n",newOwner);
		dispatchEvent(strDbusName, EC_Status, "available", "");
	}
	else if (0 == strcmp(newOwner, "") &&  0 != strcmp(oldOwner, ""))
	{
        fprintf(stderr,"ADAS oldOwner = %s\n",oldOwner);
		dispatchEvent(strDbusName, EC_Status, "unavailable", "");
	}
    else
    {
        fprintf(stderr,"ADAS onNotifyServiceOwnerChange happened with exception\n");
    }
}

void CSvcIpc::onSubscribeCallback(SVCIPC_tSigSubHnd subHnd, SVCIPC_tUserToken token)
{
	if( token )
	{
		string strToken((char*)token);
		map<string, tagSigInfo*>::iterator it = m_mapSignal.find(strToken);

		if ( it != m_mapSignal.end() )
		{
			tagSigInfo* pData = (*it).second;
			if( pData )
				pData->SigHnd = subHnd;
		}
		else
		{
	//		CLog::error2(TRC_NAME_W, (const CHAR*)string::format(L"Enter Subscribe Callback function, CSvcIpcClient Failed to find token\n Token is %ls",
	//						(const CHAR*)strToken));
		}
	}
}

TRC_SCOPE_DEF(ADAS, CSvcIpc, onRequest);
void CSvcIpc::onRequest(SVCIPC_tReqContext context, SVCIPC_tConstStr method,
   						SVCIPC_tConstStr parms, SVCIPC_tBool noReplyExpected,
   						SVCIPC_tUserToken token)
{   
    TRC_SCOPE(ADAS, CSvcIpc, onRequest);
	string strMethod(method);
	//translateToLocal(method,strMethod);
	string strParams(parms);
	//translateToLocal(parms, strParams);
	{
		DBG_MSG(("svcipc onRequest %s - %s\n", strMethod.c_str(), strParams.c_str()) );
		if( m_pService )
		{
			m_pService->onRequest(context, strMethod, strParams);
		}
	}
}

