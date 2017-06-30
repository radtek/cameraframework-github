#include "CCommandLineParser.h"

CCommandLineParser* CCommandLineParser::s_pInstance = NULL;
CCommandLineParser* CCommandLineParser::getInstance()
{
	if( s_pInstance == NULL)
	{
		s_pInstance = new CCommandLineParser();
	}

	return s_pInstance;
}

void CCommandLineParser::deleteInstance()
{
	if( s_pInstance != NULL )
	{
		delete s_pInstance;
		s_pInstance = NULL;
	}
}

CCommandLineParser::CCommandLineParser()
{

}

CCommandLineParser::~CCommandLineParser()
{

}
TRC_SCOPE_DEF(ADAS, CCommandLineParser, parse);
void CCommandLineParser::parse(Int32 argc, char **argv)
{
	TRC_SCOPE(ADAS, CCommandLineParser, parse);
	string 			strKey;

	for(Int32 i = 0; i < argc; ++i)
	{
		char* pcData = argv[i];

		char			c = '0';
		Int32			iStart = 0;
		Int32			iEnd = strlen(pcData);
		Int32			iIndex = 0;
		c = pcData[iIndex++];


		while (c != 0)
		{
			if ( c == '=' )
			{
				Int32 iSize = iIndex - iStart;
				strKey.assign(pcData, iSize-1);
				iStart = iIndex;
				iSize=iEnd-iIndex+1;
				string strValue;
				strValue.assign(pcData+iStart, iSize);
				m_mapParam.insert(makePair(strKey, strValue));
			}
			c = pcData[iIndex++];
		}
	}

	DBG_MSG(("begin print command\n"));
	for( map<string,string>::iterator it = m_mapParam.begin(); it != m_mapParam.end(); ++it  )
	{
		DBG_MSG(("COMMANDLINE key=%s value=%s\n",(*it).first.c_str(), (*it).second.c_str()));;
	}
}

const string CCommandLineParser::getItemstring(const string &strKey)
{
	return getItemValue(strKey);
}

Int32 CCommandLineParser::getItemInt(const string &strKey)
{
	//DBG_MSG(("CCommandLineParser::getItemInt %s\n", getItemValue(strKey).c_str()));
	return StringUtil::toInt(getItemValue(strKey).c_str());
}

UInt32 CCommandLineParser::getItemUInt(const string &strKey)
{
	return StringUtil::toUInt(getItemValue(strKey).c_str());
}

Float32	CCommandLineParser::getItemFloat(const string &strKey)
{
	return StringUtil::toFloat(getItemValue(strKey).c_str());
}

BOOLEAN	CCommandLineParser::getItemBool(const string &strKey)
{
	return StringUtil::toBool(getItemValue(strKey).c_str());
}
TRC_SCOPE_DEF(ADAS, CCommandLineParser, getItemValue);
const string CCommandLineParser::getItemValue(const string &strKey)
{
	TRC_SCOPE(ADAS, CCommandLineParser, getItemValue);
	//const string strValue = m_mapParam[strKey];
	DBG_MSG(("----------------CCommandLineParser::getItemValue key=%s\n", strKey.c_str()));
	map<string, string>::iterator it = m_mapParam.find(strKey);
	if( it != m_mapParam.end() )
	{
		//DBG_MSG(("CCommandLineParser::getItemValue value = %s\n", (*it).second.c_str()));
		return (*it).second;
	}

	return STRING_NULL;
}
