#ifndef	_CFILE_H_
#define _CFILE_H_

#include "common.h"

#ifdef PLATFORM_WIN
	#include <stdio.h>
#endif

#ifdef PLATFORM_QNX
	#include <stdio.h>
#endif

#ifdef PLATFORM_LINUX
	#include <stdio.h>
#endif


class CFile : public Ref
{
public:// const define

private:// const define

public:// embed class or struct or enum
	enum ESeekType
	{
		ST_BEGIN = 0,
		ST_CURRENT = 1,
		ST_END = 2,
	};

private:// embed class or struct or enum

public:// method
	CFile();
	virtual ~CFile();

	static	BOOLEAN isExist(const char * pcFilePath);
	static	BOOLEAN	isReadOnly(const char * pcFilePath);
	static	BOOLEAN	renameFile(const char *pcOldFilePath, const char* pcNewFilePath);
	static	BOOLEAN deleteFile(const char *pcFilePath);

	BOOLEAN	open(const char *pcFilePath, BOOLEAN bRead);
	BOOLEAN open(const char *pcFilePath, const char* pcMode);
	void	close();

	BOOLEAN	isEmpty();
	UInt32	getFileSize();

	BOOLEAN	writeData(const BYTE *pbtData, UInt32 uiDataLen);
	BOOLEAN	readData(BYTE *pbtData, UInt32 uiDataLen);
	Int32	seekTo(Int32 iDistance, ESeekType eSeekType);
	void	flush();

protected:// method
	CFile(const CFile&){}
	CFile& operator =(const CFile&){return *this;}

	FILE * innerOpen(const char *pcFilePath, const char *pcMode);

private:// method

protected:// property

private:// property
	FILE		*m_pFile;
};

#endif
