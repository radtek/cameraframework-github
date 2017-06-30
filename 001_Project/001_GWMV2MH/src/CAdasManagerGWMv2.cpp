#include "CAdasManagerGWMv2.h"
#include "AdasModuleCtrlImpl.h"
#include "CMessageQueue.h"
#include "CMessageHandler.h"
#include "Rvc/RvcMsgQDefine.h"
#include "ADASManager/Camera/CameraEventDefine.h"

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {

string moduleTab[] = {
    string("RVC"),
    STRING_NULL
};

CAdasManagerGWMv2* CAdasManagerGWMv2::s_pInstance = NULL;

CAdasManagerGWMv2* CAdasManagerGWMv2::getInstance()
{
    if( s_pInstance == NULL)
    {
        s_pInstance = new CAdasManagerGWMv2();
    }

    return s_pInstance;
}

VOID CAdasManagerGWMv2::deleteInstance()
{
    if( s_pInstance != NULL )
    {
        delete s_pInstance;
        s_pInstance = NULL;
    }
}

CAdasManagerGWMv2::CAdasManagerGWMv2()
    :CAdasManager(string("adas"), new CMessageQueue(string("adas"), 300, (CMessageHandler*)(AdasModuleCtrlImpl::getInstance())))
{
    ALOGD("CAdasManagerGWMv2\n");
     REGCB_CCR(makeFunctor(this, &CAdasManagerGWMv2::vCaseCallback));
}

CAdasManagerGWMv2::~CAdasManagerGWMv2()
{
    ;
}

VOID CAdasManagerGWMv2::init()
{
    ALOGD("init\n");

    BYTE cameraFlag = 0;
    for(auto mode : moduleTab)
    {
        if(mode == ADAS_MODULE_RVC)
        {
            cameraFlag |= s_RVC_Map_Cameras;
        }
        #if 0
        else if(mode == ADAS_MODULE_SVC)
        {
            cameraFlag |= s_SVC_Map_Cameras;
        }
        else if(mode == ADAS_MODULE_AVM)
        {
            cameraFlag |= s_AVM_Map_Cameras;
        }
        else if(mode == ADAS_MODULE_PAS)
        {
            cameraFlag |= s_PAS_Map_Cameras;
        }
        else if(mode == ADAS_MODULE_APA)
        {
            cameraFlag |= s_APA_Map_Cameras;
        }
        else if(moduleTab[index]  == ADAS_MODULE_COMMON)
        {

        }
        #endif
    }
    AdasModuleCtrlImpl::getInstance()->CreateModules(moduleTab, cameraFlag);
    AdasModuleCtrlImpl::getInstance()->ModuleInit();
}

VOID CAdasManagerGWMv2::vCaseCallback(const string& strMockIPC)
{
	//string strMockIPC;
	//if(NULL  ==strMockIPC) return;
	ALOGD("CAdasManagerGWMv2 received Mock IPC :%s  \n", strMockIPC.c_str());
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
		ALOGD("CAdasManagerGWMv2 loop back msg :%s  \n", ((sNewMsg.substr(5,sNewMsg.size())).c_str()));
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
		ALOGE("wrong1 GWMv2 Mock message :%s  \n", strMockIPC.c_str());
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
		ALOGE("wrong2 GWMv2 Mock message :%s  \n", strMockIPC.c_str());
		return;
	}
	//get messageArgs	
	strArgs=sNewMsg;
	SENDTO_CCR("GWMv2 case client adapter  received one msg");     
	//ALOGD("adptor GWMv2 message :uiModuleTyp[%d] uiMeaasgeID[%d]  strArgs[%s]  \n", uiModuleTyp,uiMeaasgeID,strArgs.c_str());
	pushMessage(new MessageForQueue(uiModuleTyp,uiMeaasgeID,strArgs));
	//pushMessage(new MessageForQueue(0,0, string("456")));
}

}
}
}
}
