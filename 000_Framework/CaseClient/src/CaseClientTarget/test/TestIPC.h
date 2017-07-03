#pragma once
#include "CaseClientRegister.h"
class CTestIPC : public CaseClientRegister
{
public:
	CTestIPC();
	~CTestIPC();
	virtual void ICallBackStubFunc(const char* stubFuncName, char* argv);
	//test IPC calls
	void testFunc1(int a);

};

