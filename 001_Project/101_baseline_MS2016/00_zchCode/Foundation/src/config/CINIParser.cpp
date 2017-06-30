#include "CINIParser.h"

const Int32	INT_ENC_TABLESIZE	= 7;
const char	INT_ENC_CHARTABLE[]	= {('\n'), ('\r'), ('\t'), ('['), (']'), ('='), (';')};
const char* INT_ENC_DESTTABLE[]	= {"\\n", "\\r", "\\t", "\\pl", "\\pr", "\\eq", "\\se"};

CINIParser::CINIParser()
	: m_pCurSection(NULL)
{
	;
}

CINIParser::~CINIParser()
{
	;
}

BOOLEAN CINIParser::parse(const string &strPath)
{
	CFile file;
	if (file.open(strPath.c_str(), TRUE) == FALSE)
	{
		return FALSE;
	}

	UInt32 uiSize  = file.getFileSize();

	//ArrayPtr<BYTE> ptrData(new BYTE[uiSize + sizeof(CHAR)], uiSize + sizeof(CHAR));
	char* pData = new char[uiSize+1];
	memset(pData, 0, uiSize+1);
	file.readData((BYTE*)pData, uiSize);

	//string			strContent;
	//StringUtil::convertFromBYTE_UTF16(ptrData, uiSize, strContent);

	m_mapSection.clear();
	m_pCurSection = NULL;
	m_strCurSection = STRING_NULL;

	parseData(pData);

	delete[] pData;

	return TRUE;
}

BOOLEAN CINIParser::save(const string &strPath)
{
	BOOLEAN bRet = FALSE;
	string strSection;

	//m_mapSection.resetIterator();
	for ( map<string, tagSection*>::iterator it = m_mapSection.begin();
			it != m_mapSection.end() ; ++it )
	{
		tagSection *pSection = (*it).second;

		string strItem;
		for ( map<string, string>::iterator it1 = pSection->mapItem.begin();
				it1 != pSection->mapItem.end() ; ++it1 )
		{
			string strValue;
			StringUtil::encodeChars((*it1).second, INT_ENC_TABLESIZE, INT_ENC_CHARTABLE, INT_ENC_DESTTABLE, strValue);

			strItem = strItem + StringUtil::format("%s=%s;\n", (*it1).first.c_str(), strValue.c_str());
		}

		if (strItem.length() > 0)
		{
			strSection = strSection + (StringUtil::format("[%s]\n%s\n", (*it).first.c_str() ,strItem.c_str() ) );
		}
		else
		{
			strSection = strSection + StringUtil::format("[%s]\n\n",  (*it).first.c_str());
		}
	}

	CFile file;
	if (file.open(strPath.c_str(), FALSE))
	{
		BYTE abtBOM[2];
		abtBOM[0] = 0xFF;
		abtBOM[1] = 0xFE;
		file.writeData(abtBOM, 2);

		//UInt32 uiDataLen = strSection.length() * 2;
		//BYTE* pbtData = new BYTE[uiDataLen];
		//StringUtil::convertToBYTE_UTF16(strSection, pbtData, uiDataLen);
		bRet = file.writeData((BYTE*)strSection.c_str(), strSection.length());
		//delete[] pbtData;
	}

	return bRet;
}

map<string, string>* CINIParser::getSection(const string &strSection)
{
	tagSection * pSection = innerGetSection(strSection);
	if (pSection != NULL)
	{
		return &pSection->mapItem;
	}
	else
	{
		return NULL;
	}
}

void CINIParser::createSection(const string &strSection)
{
	innerCreateSection(strSection);
}

void CINIParser::deleteSection(const string &strSection)
{
	if (m_mapSection.erase(strSection))
	{
		if (m_strCurSection == strSection)
		{
			m_pCurSection = NULL;
			m_strCurSection = STRING_NULL;
		}

		notifyDataChanged();
	}
}

const string CINIParser::getItemstring(const string &strSectionName, const string &strKey)
{
	return getItemValue(strSectionName, strKey);
}

Int32 CINIParser::getItemInt(const string &strSectionName, const string &strKey)
{
	return StringUtil::toInt(getItemValue(strSectionName, strKey).c_str());
}

UInt32 CINIParser::getItemUInt(const string &strSectionName, const string &strKey)
{
	return StringUtil::toUInt(getItemValue(strSectionName, strKey).c_str());
}

Float32 CINIParser::getItemFloat(const string &strSectionName, const string &strKey)
{
	return StringUtil::toFloat(getItemValue(strSectionName, strKey).c_str());
}

BOOLEAN CINIParser::getItemBool(const string &strSectionName, const string &strKey)
{
	return StringUtil::toBool(getItemValue(strSectionName, strKey).c_str());
}

void CINIParser::setItem(const string &strSectionName, const string &strKey, const string &strValue)
{
	tagSection *pSection = innerCreateSection(strSectionName);

	if (pSection != NULL)
	{
		if (getItemstring(strSectionName, strKey) != strValue)
		{
			//string *pstrValue = new string(strValue);
			pSection->mapItem.insert(makePair(strKey, string(strValue)));

			notifyDataChanged();
		}
	}
}

void CINIParser::setItem(const string &strSectionName, const string &strKey, const char *pcValue)
{
	tagSection *pSection = innerCreateSection(strSectionName);

	if (pSection != NULL)
	{
		if (getItemstring(strSectionName, strKey) != pcValue)
		{
			//string *pstrValue = new string(pcValue);
			pSection->mapItem.insert(makePair(strKey, string(pcValue)));

			notifyDataChanged();
		}
	}
}

void CINIParser::setItem(const string &strSectionName, const string &strKey, Int32 iValue)
{
	tagSection *pSection = innerCreateSection(strSectionName);

	if (pSection != NULL)
	{
		if (getItemInt(strSectionName, strKey) != iValue)
		{
			//string *pstrValue = new string(StringUtil::tostring(iValue));
			pSection->mapItem.insert(makePair(strKey, StringUtil::toString(iValue)));

			notifyDataChanged();
		}
	}
}

void CINIParser::setItem(const string &strSectionName, const string &strKey, UInt32 uiValue)
{
	tagSection *pSection = innerCreateSection(strSectionName);

	if (pSection != NULL)
	{
		if (getItemUInt(strSectionName, strKey) != uiValue)
		{
			//string *pstrValue = new string(StringUtil::tostring(uiValue));
			pSection->mapItem.insert(makePair(strKey, StringUtil::toString(uiValue)));

			notifyDataChanged();
		}
	}
}
/*
void CINIParser::setItem(const string &strSectionName, const string &strKey,  Float32 fValue)
{
	tagSection *pSection = innerCreateSection(strSectionName);

	if (pSection != NULL)
	{
		if (getItemFloat(strSectionName, strKey) != fValue)
		{
			//string *pstrValue = new string(StringUtil::tostring(fValue));
			pSection->mapItem.insert( makePair( strKey, StringUtil::toString(fValue) ) );

			notifyDataChanged();
		}
	}
}
*/
void CINIParser::setItem(const string &strSectionName, const string &strKey, BOOLEAN bValue)
{
	tagSection *pSection = innerCreateSection(strSectionName);

	if (pSection != NULL)
	{
		if (getItemBool(strSectionName, strKey) != bValue)
		{
			//string *pstrValue = new string(StringUtil::tostring(bValue));
			pSection->mapItem.insert( makePair( strKey, StringUtil::toString(bValue) ) );

			notifyDataChanged();
		}
	}
}

void CINIParser::notifyDataChanged()
{
	;
}

void CINIParser::parseData(const char *pcData)
{
	if (pcData == NULL)
	{
		return;
	}

	tagSection		*pSection = NULL;
	EParserState	eState = PS_SECTION_START;
	string 			strKey;
	char			c = '0';
	Int32			iStart = 0;
	Int32			iEnd = 0;
	Int32			iIndex = 0;

	c = pcData[iIndex++];

	while (c != 0)
	{
		if (c != '\t' && c != '\r' && c != '\n')
		{
			switch ( eState )
			{
			case PS_SECTION_START:
				{
					if (c == '[')
					{
						eState = PS_SECTION_END;
						iStart = iIndex;
					}

					break;
				}

			case PS_SECTION_END:
				{
					if (c == ']')
					{
						eState = PS_KEY_START;
						// save section;
						iEnd = iIndex - 1;

						Int32 iSize = iEnd - iStart + 1;
						string strTmp;
						strTmp.reserve(iSize);
						//ArrayPtr<CHAR> pcTemp(new CHAR[iSize], iSize);
						//StringUtil::strncpy(pcTemp, (const CHAR*)(pcData+iStart), iEnd - iStart);
						//::strncpy(pcTemp);
						strTmp.assign(pcData+iStart, iSize-1);
						pSection = new tagSection;

						m_mapSection.insert(makePair(strTmp, pSection));
					}

					break;
				}

			case PS_KEY_START:
				{
					if (c == '[')
					{
						eState = PS_SECTION_END;
						iStart = iIndex;
					}
					else
					{
						eState = PS_KEY_END;
						iStart = iIndex - 1;
					}

					break;
				}

			case PS_KEY_END:
				{
					if (c == '=')
					{
						eState = PS_VALUE;
						// save key;
						iEnd = iIndex - 1;

						Int32 iSize = iEnd - iStart + 1;
						strKey.assign(pcData+iStart, iSize-1);
						iStart = iIndex;
					}

					break;
				}

			case PS_VALUE:
				{
					if (c == ';')
					{
						eState = PS_NEXT;
						// save value;
						iEnd = iIndex - 1;

						Int32 iSize = iEnd - iStart + 1;
						string strValue;
						strValue.reserve(iSize);
						strValue.assign(pcData+iStart, iSize-1);

						string strValue1;
						StringUtil::decodeChars(strValue, INT_ENC_TABLESIZE, INT_ENC_CHARTABLE, INT_ENC_DESTTABLE, strValue1);

						pSection->mapItem.insert(makePair(strKey, strValue1));
					}

					break;
				}

			case PS_NEXT:
				{
					if (c == L'[')
					{
						// start new section
						eState = PS_SECTION_END;
						iStart = iIndex;
					}
					else
					{
						// start new key
						eState = PS_KEY_END;
						iStart = iIndex - 1;
					}

					break;
				}
			}
		}

		c = pcData[iIndex++];
	}
}

CINIParser::tagSection* CINIParser::innerCreateSection(const string &strSection)
{
	if (m_pCurSection == NULL || m_strCurSection != strSection)
	{
		m_pCurSection = m_mapSection[strSection];

		if (m_pCurSection == NULL)
		{
			m_pCurSection = new tagSection;
			m_mapSection.insert(makePair(strSection, m_pCurSection));

			notifyDataChanged();
		}

		m_strCurSection = strSection;
	}

	return m_pCurSection;
}

CINIParser::tagSection* CINIParser::innerGetSection(const string &strSection)
{
	if (m_pCurSection == NULL || m_strCurSection != strSection)
	{
		tagSection *pSection = m_mapSection[strSection];
		if (pSection == NULL)
		{
			return NULL;
		}

		m_pCurSection = pSection;
		m_strCurSection = strSection;
	}

	return m_pCurSection;
}

const string CINIParser::getItemValue(const string &strSectionName, const string &strKey)
{
	m_pSection = innerGetSection(strSectionName);

	if (m_pSection != NULL)
	{
		return m_pSection->mapItem[strKey];
	}

	return STRING_NULL;
}

