#ifndef _CADAS_SERVICES_H_
#define _CADAS_SERVICES_H_

#include "svs.h"


class CAdasService : public CBaseDBUSParser
{
public:	//enum struct typedef
	typedef CFunctorRetArg0<BOOLEAN> CCommandFunctor;

public: // method
   static CAdasService* getInstance();
   static void delInstance();
   ~CAdasService();

   // request
   void setAttribute(SVCIPC_tReqContext context, const string& parms);
   void getAttribute(SVCIPC_tReqContext context, const string& parms);
   void setPositionAndSize(SVCIPC_tReqContext context, const string& parms);
   void getCameraState(SVCIPC_tReqContext context, const string& parms);
   void getCameraConfig(SVCIPC_tReqContext context, const string& parms);

   // emit
   void emitCameraState(BOOLEAN bSendDiagState,BOOLEAN bForceSend);
   void emitCameraConfig();

protected:// method

private: // method
   CAdasService();
   static CAdasService * s_pInstance;

   void parseADASCommand(SVCIPC_tReqContext context, Json::Value& parms);
   
protected:// data

private:// data

};

#endif // _CADAS_SERVICES_H_

