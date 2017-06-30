#ifndef _CLAYERMANAGER_CLIENT_HPP
#define _CLAYERMANAGER_CLIENT_HPP

#include "svs.h"
#include "MessageDefineSCANIA.hpp"
class CLayerManagerClient : public CBaseDBUSParser
{
public:	//enum struct typedef

public: // method
   static CLayerManagerClient* getInstance();
   static void delInstance();
   ~CLayerManagerClient();

   // request
   //power supply for sania is always on, the control logic is MAN actually
   void RequestShowADASLayer();
   void onRspRequestShowADASLayer(const string& strData);
protected: // method
   CLayerManagerClient();

private: // data
   static CLayerManagerClient*		s_pInstance;
};

#endif
