
#include "svs.h"
#include "logic/CAdasCtrl.hpp"
#include "logic/CSCANIAMessageHandler.h"

#include "CEOL.hpp"


void SigHandler( int sig )
{
   printf("---chb--- sig %d received ,will quit soon\n", sig);

   switch(sig)
   {
   case SIGTERM:
      CAdasManager::getInstance()->quit();
      // CAdasManager::getInstance()->resume();
      CAdasManager::getInstance()->join();
      // CAdasCtrl::getInstance()->bAdasDestroyGraphic();
      signal(SIGTERM,SIG_DFL);
      raise(SIGTERM);
      break;
   //case SIGINT:
   //case SIGTSTP:
	//   exit(0);
   default:
      break;   
   }
}

#define G_ADAS_MGR_MSG_QUEUE "myname"
typedef void (*debugFun)(tagQNXCaptureDriverConfig& qnxCapConfig);
typedef struct
{
	const char  *OptionName;
	int         *CfgObj;
	debugFun    deFun;
}t_DeOptionCfgItem;

void covertToArrayInt(const string& str, Array<Int32>& aryInt, char dec)
{
	if( str.empty() )
		return;

	UInt32 uiStartPos = 0;
	UInt32 uiStrLen = str.size() - 1;
	while(uiStartPos < uiStrLen )
	{
		string::size_type pos = str.find(dec, uiStartPos);
		if( pos != string::npos )
		{
			string tmp = str.substr(uiStartPos, pos-uiStartPos);
			aryInt.push_back( StringUtil::toInt( tmp.c_str() ) );
			uiStartPos = pos + 1;
		}
		else
		{
			string tmp = str.substr(uiStartPos, uiStrLen-uiStartPos+1);
			aryInt.push_back( StringUtil::toInt( tmp.c_str() ) );
			break;
		}
	}


}
TRC_SCOPE_DEF(ADAS, main, getSourceByCmdLine);
void getSourceByCmdLine(tagQNXCaptureDriverConfig& qnxCapConfig)
{
	TRC_SCOPE(ADAS, main, getSourceByCmdLine);
	Array<Int32> aryInt;
	string str = CCommandLineParser::getInstance()->getItemstring("-source");

	//DBG_MSG(("source=%s\n", str.c_str()));
	covertToArrayInt(str, aryInt, ',');

	for( UInt32 i = 0; i < aryInt.size(); ++i)
	{
		qnxCapConfig.source[i] = aryInt[i];
		DBG_MSG(("SOURCE[i] = %d\n", aryInt[i]));
	}
}

void initCaptureConfig()
{
	tagQNXCaptureDriverConfig& qnxCapConfig = CAdasCtrl::getInstance()->getCaptureConfig();

	static t_DeOptionCfgItem debugTable[]=
	//--------OptionName--------------------cfg Obj--------------------------------debug callback funtion--------
	{
		{"-sourceNum",                     (int*)&qnxCapConfig.uiSrcNum,                             NULL},
		{"-source",                     	(int*)&qnxCapConfig.source[0],                            getSourceByCmdLine},
		{"-pipeline",                   	(int*)&qnxCapConfig.pipeline,                             NULL},
		{"-device",                     	(int*)&qnxCapConfig.device,                               NULL},
		{"-source_type",                   (int*)&qnxCapConfig.source_type,                          NULL},
		{"-cposX",                       	(int*)&qnxCapConfig.cpos[0],                              NULL},
		{"-cposY",                       	(int*)&qnxCapConfig.cpos[1],                              NULL},
		{"-sfsizeW",                     	(int*)&qnxCapConfig.sfsize[0],                            NULL},
		{"-sfsizeH",                     	(int*)&qnxCapConfig.sfsize[1],                            NULL},
		{"-csizeW",                      	(int*)&qnxCapConfig.csize[0],                             NULL},
		{"-csizeH",                      	(int*)&qnxCapConfig.csize[1],                             NULL},
		{"-ssizeW",                      	(int*)&qnxCapConfig.dfsize[0],                            NULL},
		{"-ssizeH",                      	(int*)&qnxCapConfig.dfsize[1],                            NULL},
	};

	for( UInt32 i = 0; i < sizeof(debugTable)/sizeof(t_DeOptionCfgItem);++i )
	{
		if( debugTable[i].deFun == NULL )
		{
			(*debugTable[i].CfgObj) = CCommandLineParser::getInstance()->getItemInt(
					string(debugTable[i].OptionName) );

			//DBG_MSG(("capture config[%d] = %d\n", i,(*debugTable[i].CfgObj) ));
		}
		else
		{
			debugTable[i].deFun(qnxCapConfig);
		}
	}

}
struct timespec TimeStampStartUp; 
TRC_SCOPE_DEF(CAdasMgr, CAdasMgr, main);
int main(int argc, char *argv[])
{
	UInt32 uiTime = getTickCount();

#ifdef TRACE_CLIENT
   CTraceThread::CHBConfig cfg(argc, argv, argv[0]);
   CTraceThread traceThread(cfg);
   
   TRC_SCOPE(CAdasMgr, CAdasMgr, main);
   HBOSTypes::TID tid = CHBThreadCtrl::startThread(traceThread);
   DBG_MSG(("Initializing Adas App... \t Trace thread id=0x%x \n", tid));
   DBG_MSG(("adas ver 201509017 send cammera staete after layer is ready, send active type*****************enter time******************** %u\n", uiTime));
#endif
   //Setup Signal Handlers
   signal(SIGTERM,  SigHandler);
   //signal(SIGINT,   SigHandler);
   //signal(SIGTSTP,  SigHandler);
   
   clock_gettime(CLOCK_MONOTONIC, &TimeStampStartUp);
   fprintf(stderr,"\n##############ADAS start at ----> %ld MS###########\n", (TimeStampStartUp.tv_sec)*1000 + ((TimeStampStartUp.tv_nsec)/(1000000L)));

   pthread_setname_np(pthread_self(), "main");

   CCommandLineParser::getInstance()->parse(argc, argv);
   EOL::setInitCapture( CCommandLineParser::getInstance()->getItemBool("-bInitCapture") );
   initCaptureConfig();


   //EOL::setCameraSourceIndex(CCommandLineParser::getInstance()->getItemBool("-source"));
   DBG_MSG(("source = %d\n", EOL::getCameraSourceIdx()));

   //if( !CAdasCtrl::getInstance()->bAdasInitGraphic() )
   //	{
	//   DBG_ERROR(("AdasInitGraphic failed\n"));
   //		return FALSE;
   //	}

   CAdasManager::getInstance()->start(new CMessageQueue(G_ADAS_MGR_MSG_QUEUE, 300, new CSCANIAMessageHandler()),
		   CAdasCtrl::getInstance());
   CAdasManager::getInstance()->join();

   //CAdasCtrl::getInstance()->bAdasDestroyGraphic();

   DBG_MSG(("Adas App exit\n"));

#ifdef TRACE_CLIENT
   traceThread.stop();
   CHBThreadCtrl::terminate( tid );
   CHBThreadCtrl::join( tid );//CHBThreadCtrl::join(tid, 5000);
#endif

   CAdasManager::deleteInstance();
   CAdasCtrl::delInstance();
   CCommandLineParser::deleteInstance();

   return(0);
}



