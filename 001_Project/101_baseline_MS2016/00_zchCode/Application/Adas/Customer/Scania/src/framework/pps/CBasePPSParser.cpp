#include "CBasePPSParser.h"
#include "CAdasManager.h"

CBasePPSParser::CBasePPSParser()
{
	//CPPS::getInstance()->registerHooker("pps/EOL/camera", this);
	//CPPS::getInstance()->registerHooker("pps/EOL/uv", this);

	//registerFunctor("");
}

CBasePPSParser::~CBasePPSParser()
{

}

void CBasePPSParser::process(const string& strName, char* buf)
{
	HashMap<string, CFunctor*>::Iterator it= m_hashMapFunctor.find(strName);
	if( it!= m_hashMapFunctor.end() )
	{
		CFunctor* pfunctor = (*it).second;
		string strData(buf);
		(*pfunctor)(strData);
	}
	return ;

}

void CBasePPSParser::registerFunctor(const string& strName, CFunctor* pFunctor)
{
	if( pFunctor )
		m_hashMapFunctor.insert( makePair(strName,pFunctor) );
}

BOOLEAN CBasePPSParser::parse(char* buf, map<string,string>& mapParam)
{
	if( buf == NULL )
		return FALSE;

	pps_attrib_t info;
	pps_status_t rc;

	memset(&info, 0, sizeof(info));
	while ((rc = ppsparse(&buf, NULL, NULL, &info, 0)) != PPS_END)
	{
		if (rc == PPS_ATTRIBUTE)
		{
			if( (info.attr_name != NULL) && (info.value != NULL))
			{   
                //fprintf(stderr,"AAAAAAAAAAAAAAAAAA-->basepasre inserted att name- %s and att value - %sBBB \n",info.attr_name,info.value);
				//mapParam.insert( makePair(info.attr_name, info.value) );
				mapParam[info.attr_name]=info.value;
			}
		}
	}

	return TRUE;
}
TRC_SCOPE_DEF(ADAS, CBasePPSParser, asynSendMessage);
void CBasePPSParser::asynSendMessage(const tagBaseMessage& rMsg, UInt32 uiLen)
{
    TRC_SCOPE(ADAS, CBasePPSParser, asynSendMessage);
	DBG_MSG(("CBasePPSParser::asynSendMessage\n"));
	CAdasManager::getInstance()->pushMessage(rMsg, uiLen);
}
