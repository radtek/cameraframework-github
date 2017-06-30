#ifndef _ISVCIPC_HOOKER_H
#define _ISVCIPC_HOOKER_H
	
#include "foundation.h"

class ISvcIpcHooker
{
public:// method
	virtual void onServiceStatus (BOOLEAN bAvailable) = 0;
	virtual void onResponse	(const string &strMethodName, const string &strData) = 0;
	virtual void onAResponse	(const string &strMethodName, const string &strData) = 0;
	virtual void onSignal	(const string &strSignalName, const string &strData) = 0;
	virtual void onRequest(SVCIPC_tReqContext context, const string &strRequestName, const string &strData) = 0;
};

#endif
