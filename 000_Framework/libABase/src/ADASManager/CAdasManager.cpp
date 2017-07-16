
#include "AFoundation.h"
#include "ADASManager/CAdasManager.h"
#include "ADASManager/AdasModuleCtrl.h"
#include "CMessageHandler.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

CAdasManager::CAdasManager(const string& strName, CMessageQueue* pMsgQueue)
: CMQRunnableService(strName, pMsgQueue)
{
    ALOGD("CAdasManager\n");
    PRINT_APP_OS_TYPE;
    LAUNCH_CCR ;
   // REGCB_CCR(makeFunctor(this, &CAdasManager::vCaseCallback));
}

CAdasManager::~CAdasManager()
{
    ;
}

void CAdasManager::vAddModule()
{
   
    SENDTO_CCR("CAdasManager:vAddModule success! \n")  ;
}

void CAdasManager::afterHandleMessageQueue()
{

}

void CAdasManager::beforeHandleMessageQueue()
{

}

void CAdasManager::init()
{

}

VOID CAdasManager::vCaseCallback(const string& strMockIPC)
{
	//string strMockIPC;
	//if(NULL  ==strMockIPC) return;
	//ALOGD("CAdasManager received Mock IPC :%s  \n", strMockIPC.c_str());
         //raw data from socket
	string sNewMsg = strMockIPC;
	string sTmpData ="default";
	int DataPos = sNewMsg.find(',');
	string::size_type pos=0;
	//GWMv2 msg data to get from raw data 
	UInt32 uiModuleTyp=0;   // moduleID
	UInt32 uiMeaasgeID=0;    // messageID
	string strArgs="dummy IPC msg";  // messageArgs	

	//loop back mode : to sync cases
	if(("[Str]"==sNewMsg.substr(0,5)))
	{
		//test target side to directly loop back to case client side
		SENDTO_CCR((sNewMsg.substr(5,sNewMsg.size())).c_str());
		ALOGD("CAdasManager loop back msg :%s  \n", ((sNewMsg.substr(5,sNewMsg.size())).c_str()));
		ACKTO_CCR;
		return;
	}
	ACKTO_CCR; // send out sync for a normal string 
	//get moduleID
	if ((pos=sNewMsg.find(',',pos))!=string::npos)  
	{
		sTmpData=sNewMsg.substr(0,pos); 
		sNewMsg = sNewMsg.substr(pos+1);
		uiModuleTyp = atoi(sTmpData.c_str());
	}
	else
	{
		ALOGE("wrong1 CAdasManager Mock message :%s  \n", strMockIPC.c_str());
		return;
	}	
	//get messageID	
	if ((pos=sNewMsg.find(',',pos))!=string::npos)  
	{
		sTmpData=sNewMsg.substr(0,pos); 
		sNewMsg = sNewMsg.substr(pos+1);
		uiMeaasgeID = atoi(sTmpData.c_str());
	}
	else
	{
		ALOGE("wrong2 CAdasManager Mock message :%s  \n", strMockIPC.c_str());
		return;
	}
	//get messageArgs	
	strArgs=sNewMsg;
	SENDTO_CCR("CAdasManager case client adapter  received one msg");     
	//ALOGD("adptor GWMv2 message :uiModuleTyp[%d] uiMeaasgeID[%d]  strArgs[%s]  \n", uiModuleTyp,uiMeaasgeID,strArgs.c_str());
	pushMessage(new MessageForQueue(uiModuleTyp,uiMeaasgeID,strArgs));
	//pushMessage(new MessageForQueue(0,0, string("456")));
}


}
}
}
}
}
