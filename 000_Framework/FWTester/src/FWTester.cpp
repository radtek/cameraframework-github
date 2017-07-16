#include "FWTester.h"


using namespace Harman::Adas::AFramework::AFoundation;


namespace Harman {
namespace Adas {
namespace AFramework {
namespace FWTester {

FWTester* FWTester::s_pInstance = NULL;

FWTester* FWTester::getInstance()
{
    if( s_pInstance == NULL)
    {
        s_pInstance = new FWTester();
    }

    return s_pInstance;
}

VOID FWTester::deleteInstance()
{
    if( s_pInstance != NULL )
    {
        delete s_pInstance;
        s_pInstance = NULL;
    }
}

FWTester::FWTester()
    :CAdasManager(string("FWTester"), new CMessageQueue(string("FWTester"), 300, (CMessageHandler*)(m_pTestModuleCtrl = new FWTesterModuleCtrl())))
{
	m_pTestCameraHub = new CameraHub();
	//m_pTestARvcBase= new ARvcBase(m_pTestCameraHub);

	ALOGD("FWTester\n");
	REGCB_CCR(makeFunctor(this, &FWTester::vCaseCallbackFWTester));
}

FWTester::~FWTester()
{
	delete m_pTestModuleCtrl;
	m_pTestModuleCtrl = NULL;
}

VOID FWTester::init()
{
    //m_pTestModuleCtrl->CreateModules(AdasModuleCtrl::eModuleType_RVC, static_cast<ModuleBase*> (m_pTestARvcBase));
    //m_pTestModuleCtrl->initialize();
}

VOID FWTester::vCaseCallbackFWTester(const string& strMockIPC)
{
	ALOGD("FWTester received Mock IPC :%s  \n", strMockIPC.c_str());
	vCaseCallback(strMockIPC.c_str());
}

//==========================================================
//test module ctrl ARvcBase

a_status	 FWTesterModuleCtrl:: CreateModules(UInt32 uiModuleType, ModuleBase* pBaseModule)
{
	m_mModuleMap.insert(makePair(uiModuleType,pBaseModule));
}




}
}
}
}
