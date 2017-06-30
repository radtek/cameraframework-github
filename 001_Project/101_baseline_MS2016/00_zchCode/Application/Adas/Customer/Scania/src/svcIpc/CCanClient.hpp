#ifndef _CCAN_CLIENT_HPP
#define _CCAN_CLIENT_HPP

#include "svs.h"


class CCanClient : public CBaseDBUSParser
{
public:	//enum struct typedef

public: // method
   static CCanClient* getInstance();
   static void delInstance();
   ~CCanClient();

   // signal
   void onCruiseControlVehSpeed(const string& strData);
   void onDirectionSwitchParams(const string& strData);
   void onCANRequestOnOffCamera(const string& strData);

protected: // method
   CCanClient();

private: // data
   static CCanClient*		s_pInstance;
  // tagSwitchParams			m_tagSwitchParams;
  // tagCruiseControlVehSpeed	m_tagCruiseControlVelSpeed;

};

#endif
