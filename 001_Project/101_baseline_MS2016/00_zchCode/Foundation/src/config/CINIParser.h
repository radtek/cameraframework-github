
#ifndef __CINIPARSER_H_INCLUDED__
#define __CINIPARSER_H_INCLUDED__

#include "common.h"
#include "CFile.h"

class CINIParser : public Ref
{
public:// const define

private:// const define

public:// embed class or struct or enum

private:// embed class or struct or enum
	struct tagSection
	{
		map<string, string>	mapItem;
	};

	enum EParserState
	{
		PS_SECTION_START	= 1,
		PS_SECTION_END		= 2,
		PS_KEY_START		= 3,
		PS_KEY_END			= 4,
		PS_VALUE			= 5,
		PS_NEXT				= 6
	};

public:// method

	CINIParser();
	virtual ~CINIParser();

	BOOLEAN									parse(const string &strPath);
	BOOLEAN									save(const string &strPath);

	BOOLEAN									hasSection(const string &strSection)	{ return m_mapSection.find(strSection) != m_mapSection.end(); }
	BOOLEAN									hasSections()							{ return m_mapSection.size() > 0; }
	UInt32									getSectionCount()						{ return m_mapSection.size(); };
	//map<string, string>*					getSectionByIndex(UInt32 uiIndex);
	map<string, string>*					getSection(const string &strSection);
	void									createSection(const string &strSection);
	void									deleteSection(const string &strSection);
	//void									deleteSectionByIndex(UInt32 uiIndex);

	const string							getItemstring(const string &strSectionName, const string &strKey);
	Int32									getItemInt(const string &strSectionName, const string &strKey);
	UInt32									getItemUInt(const string &strSectionName, const string &strKey);
	Float32									getItemFloat(const string &strSectionName, const string &strKey);
	BOOLEAN									getItemBool(const string &strSectionName, const string &strKey);

	void									setItem(const string &strSectionName, const string &strKey, const string &strValue);
	void									setItem(const string &strSectionName, const string &strKey, const char *pcValue);
	void									setItem(const string &strSectionName, const string &strKey, Int32 iValue);
	void									setItem(const string &strSectionName, const string &strKey, UInt32 uiValue);
//	void									setItem(const string &strSectionName, const string &strKey, Float32 fValue);
	void									setItem(const string &strSectionName, const string &strKey, BOOLEAN bValue);

protected:// method
	CINIParser(const CINIParser&){}
	CINIParser& operator =(const CINIParser&){return *this;}

private:// method
	void									notifyDataChanged();

	void									parseData(const char *pcData);
	tagSection*								innerCreateSection(const string &strSection);
	tagSection*								innerGetSection(const string &strSection);
	const string							getItemValue(const string &strSectionName, const string &strKey);

protected:// property

private:// property
	map<string, tagSection*>		m_mapSection;

	tagSection*						m_pCurSection;
	tagSection*						m_pSection;
	string							m_strCurSection;
};

#endif
