#include "CCANPPSParser.h"
#include "MessageDefine.hpp"

CCANPPSParser* CCANPPSParser::s_pInstance = NULL;

CCANPPSParser* CCANPPSParser::getInstance(ICANIterf* pCANIterf)
{
	if ( s_pInstance == NULL )
	{
		s_pInstance = new CCANPPSParser(pCANIterf);

	}

	return s_pInstance;
}
/*
void CCanClient::delInstance()
{
	if ( s_pInstance == NULL )
	{
		delete s_pInstance;
		s_pInstance = NULL;
	}
}*/
TRC_SCOPE_DEF(ADAS, CCANPPSParser, CCANPPSParser);
CCANPPSParser::CCANPPSParser(ICANIterf* pCANIterf)
{
	TRC_SCOPE(ADAS, CCANPPSParser, CCANPPSParser);
	if(NULL == pCANIterf)
	{
		DBG_ERROR(("CCANPPSParser::pCANIterf NULL\n "));
		return;
	}
	pCANIterf->SetUpCANCmdTable(&m_mapCANFunc);
	for(map<string, CFunctor*>::iterator iter = m_mapCANFunc.begin();
			iter != m_mapCANFunc.end(); ++iter)
	{
      CPPS::getInstance()->registerHooker(iter->first.c_str(), this);
      registerFunctor(iter->first.c_str(), iter->second);
	}

	CPPS::getInstance()->start();

}

CCANPPSParser::~CCANPPSParser()
{
	s_pInstance = NULL;
}


