#include "StringUtil.h"
//#ifdef OS_QNX
	#include <stdarg.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <wchar.h>
	#include <memory.h>
//#endif

	Int32 StringUtil::toInt(const char *pcSrc)
	{
		if (pcSrc == NULL)
		{
			return 0;
		}

		BOOLEAN bNegative = FALSE;
		if (*pcSrc == '-')
		{
			bNegative = TRUE;
			pcSrc++;
		}

		Int32 iValue = 0;
		while ('0' <= *pcSrc && *pcSrc <= '9')
		{
			iValue = iValue * 10 + (*pcSrc - '0');
			pcSrc++;
		}

		return bNegative ? -iValue : iValue;
	}

	UInt32 StringUtil::toUInt(const char *pcSrc)
	{
		if (pcSrc == NULL)
		{
			return 0;
		}

		UInt32 uiValue = 0;

		if (*pcSrc == '0' && *(pcSrc + 1) == 'x')
		{
			pcSrc = pcSrc + 2;

			while (pcSrc != NULL && *pcSrc != '\0')
			{
				if ('0' <= *pcSrc && *pcSrc <= '9')
				{
					uiValue = uiValue * 16 + (*pcSrc - '0');
				}
				else if ('A' <= *pcSrc && *pcSrc <= 'F')
				{
					uiValue = uiValue * 16 + (*pcSrc - 'A') + 10;
				}
				else if ('a' <= *pcSrc && *pcSrc <= 'f')
				{
					uiValue = uiValue * 16 + (*pcSrc - 'a') + 10;
				}
				pcSrc++;
			}
		}
		else
		{
			while ('0' <= *pcSrc && *pcSrc <= '9')
			{
				uiValue = uiValue * 10 + (*pcSrc - '0');
				pcSrc++;
			}
		}

		return uiValue;
	}

	Float32 StringUtil::toFloat(const char *pcSrc)
	{
		if (pcSrc == NULL)
		{
			return 0;
		}

		BOOLEAN bNegative = FALSE;
		if (*pcSrc == '-')
		{
			bNegative = TRUE;
			pcSrc++;
		}

		Float32 fValue = 0;
		while ('0' <= *pcSrc && *pcSrc <= '9')
		{
			fValue = fValue * 10 + (*pcSrc - '0');
			pcSrc++;
		}

		if (*pcSrc == '.')
		{
			pcSrc++;
		}

		Float32 fTag = 10.0f;
		while ('0' <= *pcSrc && *pcSrc <= '9')
		{
			fValue += (*pcSrc - '0') / fTag;
			fTag *= 10.0f;
			pcSrc++;
		}

		return bNegative ? -fValue : fValue;
	}

	BOOLEAN StringUtil::toBool(const char *pcSrc)
	{
		if (   pcSrc == NULL
			|| *(pcSrc) != 't'
			|| *(pcSrc + 1) != 'r'
			|| *(pcSrc + 2) != 'u'
			|| *(pcSrc + 3) != 'e'
			|| *(pcSrc + 4) != '\0' )
		{
			return FALSE;
		}

		return TRUE;
	}

	string StringUtil::toString(Int32 iValue)
	{		
		char acTemp[32] = {0};

		Int32 iStart = 0;
		if (iValue < 0)
		{
			acTemp[0] = '-';
			iStart = 1;

			iValue = -iValue;
		}
		else if (iValue == 0)
		{
			acTemp[0] = '0';
			return acTemp;
		}

		Int32 i = iStart;
		while (iValue > 0)
		{
			acTemp[i++] = (iValue % 10 + '0');
			iValue /= 10;
		}

		Int32 iEnd = i - 1;
		while (iStart < iEnd)
		{
			char cTemp = acTemp[iStart];
			acTemp[iStart] = acTemp[iEnd];
			acTemp[iEnd] = cTemp;

			iStart++;
			iEnd--;
		}

		return acTemp;
	}

	string StringUtil::toString(UInt32 uiValue)
	{
		char acTemp[32] = {0};

		Int32 iStart = 0;
		if (uiValue == 0)
		{
			acTemp[0] = '0';
			return acTemp;
		}

		Int32 i = iStart;
		while (uiValue > 0)
		{
			acTemp[i++] = (uiValue % 10 + '0');
			uiValue /= 10;
		}

		Int32 iEnd = i - 1;
		while (iStart < iEnd)
		{
			char cTemp = acTemp[iStart];
			acTemp[iStart] = acTemp[iEnd];
			acTemp[iEnd] = cTemp;

			iStart++;
			iEnd--;
		}

		return acTemp;
	}
/*
	string StringUtil::toString(Float32 fValue, UInt32 uiDotUintCount)
	{
		char acFormat[32] = {0};
		char acValue[32] = {0};
#if 0
#ifdef OS_WIN		
		sprintf(acFormat, 10, "%%.%df", uiDotUintCount);
		sprintf(acValue, 32, acFormat, fValue);
#endif

#ifdef OS_QNX
		sprintf(acFormat, 10, "%%.%df", uiDotUintCount);
		sprintf(acValue, 32, acFormat, fValue);
#endif

#ifdef OS_LINUX
		sprintf(acFormat, 10, "%%.%df", uiDotUintCount);
		sprintf(acValue, 32, acFormat, fValue);
#endif

#else
		snprintf(acFormat, 10, "%%.%df", uiDotUintCount);
		snprintf(acValue, 32, acFormat, fValue);
#endif

		return acValue;
	}*/

	string StringUtil::toString(BOOLEAN bValue)
	{
		return bValue ? "true" : "false";
	}

	Int32 vscprintf(const char *format, va_list argptr)
	{
	    return(vsnprintf(0, 0, format, argptr));
	}

	string StringUtil::format(const char *pcFormat, ...)
	{
		if (pcFormat == NULL)
		{
			return "";
		}

		//string strFormat(pcFormat);
		//strFormat.replaceAll(L"%s", L"%ls");

		Int32 iLen = 0;
		//char *pcTemp = NULL;

		va_list argList;
		va_start(argList, pcFormat);
		iLen = vscprintf(pcFormat, argList);
		if (iLen < 0)
		{
			printf("vscprintf failed: %s\n", strerror(errno));
			return "";
		}
		string strOut;
		strOut.resize(iLen+1);
			//pcTemp = new char[iLen + 1];
			//strOut.reserve(iLen+1);
		vsnprintf(&strOut[0], iLen + 1, pcFormat, argList);
		strOut[iLen] = '\0';
		va_end(argList);


			//strOut.m_pc = pcTemp;
			//strOut.m_uiLen = iLen;

		return strOut;
	
	}

	void StringUtil::encodeChars(const string &strSrc, UInt32 uiCharCount, const char acCharTab[], const char* apcEncStrTab[], string &strOut)
	{
		UInt32 uiSrcLen = strSrc.length();
		if (uiSrcLen == 0)
		{
			strOut = STRING_NULL;
			return;
		}

		// Calculate buffer size requested.
		BOOLEAN bFound;
		UInt32 uiDestLen = 0;
		for (UInt32 i = 0; i < uiSrcLen; i++)
		{
			bFound = FALSE;
			for (UInt32 j = 0; j < uiCharCount; j++)
			{
				if (strSrc[i] == acCharTab[j])
				{
					uiDestLen += strlen(apcEncStrTab[j]);
					bFound = TRUE;
					break;
				}
			}
			if (bFound)
			{
				continue;
			}

			++uiDestLen;
		}

		char* pcBuffer = new char[uiDestLen + sizeof(char)];
		pcBuffer[uiDestLen] = '\0';
		UInt32 uiBufPos = 0;

		for (UInt32 i = 0; i < uiSrcLen; i++)
		{
			bFound = FALSE;
			for (UInt32 j = 0; j < uiCharCount; j++)
			{
				if (strSrc[i] == acCharTab[j])
				{
					UInt32 uiStrEncLen = strlen(apcEncStrTab[j]);
					for (UInt32 k = 0; k < uiStrEncLen; k++)
					{
						pcBuffer[uiBufPos] = apcEncStrTab[j][k];
						++uiBufPos;
					}
					bFound = TRUE;
					break;
				}
			}
			if (bFound)
			{
				continue;
			}

			pcBuffer[uiBufPos] = strSrc[i];
			++uiBufPos;
		}

		strOut = pcBuffer;
		delete[] pcBuffer;
	}

	void StringUtil::decodeChars(const string &strSrc, UInt32 uiCharCount, const char acCharTab[], const char* apcEncStrTab[], string &strOut)
	{
		UInt32 uiSrcLen = strSrc.length();
		if (uiSrcLen == 0)
		{
			strOut = STRING_NULL;
			return;
		}

		char* pcBuffer = new char[uiSrcLen + sizeof(char)];
		const char* pcSrcStr = (const char*)(strSrc.c_str());
		const char* pcEndPos = pcSrcStr + uiSrcLen;
		UInt32 uiBufPos = 0;
		BOOLEAN bFound;

		while (pcSrcStr <= pcEndPos)
		{
			bFound = FALSE;
			for (UInt32 j = 0; j < uiCharCount; j++)
			{
				UInt32 uiStrEncLen = strlen(apcEncStrTab[j]);

				if ((pcSrcStr <= pcEndPos - uiStrEncLen) &&
					strncmp(pcSrcStr, apcEncStrTab[j], uiStrEncLen))
				{
					pcBuffer[uiBufPos] = acCharTab[j];
					pcSrcStr += uiStrEncLen;
					++uiBufPos;
					bFound = TRUE;
					break;
				}
			}
			if (bFound)
			{
				continue;
			}

			pcBuffer[uiBufPos] = *pcSrcStr;
			++pcSrcStr;
			++uiBufPos;
		}

		pcBuffer[uiBufPos] = '\0';
		strOut = pcBuffer;
		delete[] pcBuffer;
	}
