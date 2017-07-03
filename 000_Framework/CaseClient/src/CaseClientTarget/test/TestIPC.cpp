#include "stdafx.h"
#include "TestIPC.h"


CTestIPC::CTestIPC()
{
	
}



CTestIPC::~CTestIPC()
{
}
#if 1
void CTestIPC::ICallBackStubFunc(const char* stubFuncName, char* argv)
{

	switch (*stubFuncName)
	{
	case 0:
		//need parser of para list
		int inum = argv[0];
		testFunc1(inum);
	}

}
#endif

void CTestIPC::testFunc1(int i)
{
	REGISTER_CASE_IF;
	printf("testFunc1 = %d", i);
}