#ifndef _CCOMMANDLINE_PARSER_H
#define _CCOMMANDLINE_PARSER_H

#include "common.h"

/*
 * format
 * xx key=value key=value key=value...
 * */
class CCommandLineParser
{
public:// enum struct typedef
	enum EParserState
	{
		PS_KEY_START		= 3,
		PS_KEY_END			= 4,
		PS_VALUE			= 5,
		PS_NEXT				= 6
	};

public:// method
	static CCommandLineParser* 	getInstance();
	static void					deleteInstance();
	~CCommandLineParser();

	void parse(Int32 argc, char **argv);
	const string		getItemstring(const string &strKey);
	Int32				getItemInt(const string &strKey);
	UInt32				getItemUInt(const string &strKey);
	Float32				getItemFloat(const string &strKey);
	BOOLEAN				getItemBool(const string &strKey);

protected:// method
	const string getItemValue(const string &strKey);

private:// method
	CCommandLineParser();

protected: // data

private: // data
	static CCommandLineParser* s_pInstance;
	map<string, string>	m_mapParam;

};

#endif
