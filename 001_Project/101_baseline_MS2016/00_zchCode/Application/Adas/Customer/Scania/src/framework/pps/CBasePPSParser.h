#ifndef _CBASEPPSPARSER_H
#define _CBASEPPSPARSER_H

#include "foundation.h"

#ifdef PLATFORM_QNX
	#include <sys/pps.h>
	#include <fcntl.h>
#endif

class CBasePPSParser
{
public:
	//typedef CFunctorArg1<const string&> 					CFunctor;
	/*
	 * void CCCANPPSParser::parseCuvInfo(const string& strValue)
	 * {
	 * 		map<string, string>	mapParam;
	 * 		parse(strValue, mapParam);
	 * 		Int32 revSwitch = StringUtil::toInt32(mapParam["RevSwtch"]);
	 * }
	 * */

public:
	CBasePPSParser();
	virtual ~CBasePPSParser();

	void	process(const string& strName, char* buf);

protected:
	void	registerFunctor(const string& strName, CFunctor* pFunctor);
	void	asynSendMessage(const tagBaseMessage& rMsg, UInt32 uiLen);

	static BOOLEAN	parse(char* buf, map<string,string>& mapParam);

private:

private:// data
	HashMap<string, CFunctor*>	m_hashMapFunctor;
};
#endif
