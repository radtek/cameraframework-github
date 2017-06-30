#ifndef _CCAN_PPSPARSER_H
#define _CCAN_PPSPARSER_H

#include "svs.h"
#include "ICANIterf.h"

class CCANPPSParser : public CBasePPSParser
{
public:	//enum struct typedef

public: // method
   static CCANPPSParser* getInstance(ICANIterf* pCANIterf);
 //  static void delInstance();
   ~CCANPPSParser();

   // signal
protected: // method
   CCANPPSParser(ICANIterf* pCANIterf);

private: // data
   static CCANPPSParser*		s_pInstance;
   //ICANIterf* pCANIterfObj;
   map<string, CFunctor*>	m_mapCANFunc;
  // tagSwitchParams			m_tagSwitchParams;
  // tagCruiseControlVehSpeed	m_tagCruiseControlVelSpeed;

};

#endif
