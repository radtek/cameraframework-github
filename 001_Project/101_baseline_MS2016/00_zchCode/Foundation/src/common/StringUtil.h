#ifndef _STRING_UTIL_H
#define	_STRING_UTIL_H

#include "ADASMarco.h"
#include "TypeDefine.h"

class StringUtil
{
public:
	static	Int32	toInt(const char *pcSrc);
	//static	Int32	toInt(const BYTE *pbtSrc);
	static	UInt32	toUInt(const char *pcSrc);
	//static	UInt32	toUInt(const BYTE *pbtSrc);
	static	Float32	toFloat(const char *pcSrc);
	//static	Float32	toFloat(const BYTE *pbtSrc);
	static	BOOLEAN	toBool(const char *pcSrc);
	//static	BOOLEAN	toBool(const BYTE *pbtSrc);

	static	string	toString(Int32 iValue);
	static	string	toString(UInt32 uiValue);
//	static	string	toString(Float32 fValue, UInt32 uiDotUintCount=4);
	static	string	toString(BOOLEAN bValue);

	static 	string  format(const char *pcFormat, ...);

	static void encodeChars(const string &strSrc, UInt32 uiCharCount, const char acCharTab[],
			const char* apcEncStrTab[], string &strOut);
	static void decodeChars(const string &strSrc, UInt32 uiCharCount, const char acCharTab[],
			const char* apcEncStrTab[], string &strOut);
};

#endif
