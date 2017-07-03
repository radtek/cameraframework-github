
#ifndef _CASECLIENTDEAMON_H_
#define _CASECLIENTDEAMON_H_
#include "../../../../libAFoundation/include/AFoundation.h"
#include "ADASCaseManager.h"
#include "CaseLogCollector.h"
using namespace Harman::Adas::AFramework::AFoundation;
using Harman::Adas::AFramework::AFoundation::CRunableBase;

class CCaseClientDeamon : public CRunableBase
{
public:
	static CCaseClientDeamon* 	getInstance();
    static void 			delInstance();
    virtual ~CCaseClientDeamon();
	void vSetupCaseClientDeamon(string sIP, int iPort);
	void init();
	void update();
private:
    CCaseClientDeamon();
	static CCaseClientDeamon*  s_pInstance;
	CAdasCaseManager* m_pAdasSocketManager;
	string m_sIP;
	int m_iPort;
};

class CExcuteCommand : public CRunableBase
{
public:
	CExcuteCommand();
    virtual ~CExcuteCommand();
	void init();
	void update();
private:
	int m_iCommandState;
};

#endif
