#ifndef _ISVC_IPC_H
#define _ISVC_IPC_H


#include "jsoncpp/json.h"
#include "svcipc/svcipc.h"
#include "foundation.h"

class ISvcIpcHooker;
class ISvcIpc
{
public:// method	
	virtual void hook(const string &strBusName, ISvcIpcHooker* pHooker) = 0;
	virtual void unhook(const string &strBusName, ISvcIpcHooker* pHooker) = 0;

	virtual void registerDBusService(const string& strBusName, const string& strObjPath, ISvcIpcHooker* pService) = 0;
	virtual void unRegisterDBusService(const string& strBusName, const string& strObjPath) = 0;
	
	virtual void invoke(const string &strBusName, const string &strObjPath, const string &strMethodName, const string &objParams) = 0;
	virtual void ainvoke(const string &strBusName, const string &strObjPath, const string &strMethodName, const string &objParams) = 0;
	virtual void subscribeSignal(const string &strBusName, const string &strObjPath, const string &strSignalName) = 0;
	virtual void unsubscribeSignal(const string &strBusName, const string &strObjPath, const string &strSignalName) = 0;
	virtual void subscribeServiceAvailable(const string &strBusName, const string &strObjPath) = 0;
	virtual void unsubscribeServiceAvailable(const string &strBusName, const string &strObjPath) = 0;

	virtual void emit(const string& strMethod, const string& strParams) = 0;
	virtual void returnResult(SVCIPC_tReqContext context, const string& strRet) = 0;
};

#endif

