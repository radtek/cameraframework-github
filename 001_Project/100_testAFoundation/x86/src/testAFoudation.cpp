// testAFoundation.cpp : Defines the entry point for the console application.
//

#include "..\testAFoudation_vs2013\stdafx.h"
#include "windows.h"
#pragma comment(lib, "libAFoundation.lib")
#include "..\..\..\..\000_Framework\libAFoundation\include\CRunableBase.h"

class CTest : public CRunableBase
{
public:
	CTest();
	~CTest(){;};
	void update();
};
CTest::CTest()
:CRunableBase("CTest",false)
{
;
}

void CTest::update()
{
	Sleep(3000);
	printf("thread test AFoundation is runing...\n");

}

int _tmain(int argc, _TCHAR* argv[])
{
	CTest* ptest = new CTest();
	ptest->start();
	ptest->join();
	return 0;
}

