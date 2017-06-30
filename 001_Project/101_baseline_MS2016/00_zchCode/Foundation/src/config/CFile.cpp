#include "CFile.h"

#ifdef PLATFORM_WIN

#endif

#ifdef PLATFORM_QNX

#endif

#ifdef PLATFORM_LINUX
	#include <errno.h>
	#include <sys/stat.h>
#endif

BOOLEAN CFile::isExist(const char * pcFilePath)
{
#ifdef OS_WIN

	BOOLEAN bRet = FALSE;
	WIN32_FIND_DATA findData;
	HANDLE hFile = FindFirstFile(pcFilePath, &findData);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		bRet = TRUE;
	}

	FindClose(hFile);
	hFile = NULL;

	return bRet;
#endif

#ifdef OS_QNX

	//char acFilePath[1024];
	//String::convertToMBCS(pcFilePath, acFilePath, 1024);

	if (access(pcFilePath, F_OK) != -1)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

// 		struct stat buf;
// 		INT iRet = stat(acFilePath, &buf);
// 		if (iRet == 0)
// 		{
// 			return TRUE;
// 		}
// 		else if (iRet == 2)
// 		{
// 			return FALSE;
// 		}
// 		else
// 		{
// 			return TRUE;
// 		}

#endif	

#ifdef OS_LINUX

	//char acFilePath[1024];
	//String::convertToMBCS(pcFilePath, acFilePath, 1024);

// 		if(access(acFilePath, F_OK) != -1)
// 		{
// 			return TRUE;
// 		}
// 		else
// 		{
// 			return FALSE;
// 		}

	struct stat buf;
	INT iRet = lstat(pcFilePath, &buf);
	if (iRet == 0)
	{
		return TRUE;
	}
	else if (iRet == 2)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
#endif
}

BOOLEAN	CFile::isReadOnly(const char * pcFilePath)
{
#ifdef OS_WIN

	DWORD dwAttrs;
	dwAttrs = GetFileAttributes(pcFilePath);

	if (dwAttrs != INVALID_FILE_ATTRIBUTES && (dwAttrs & FILE_ATTRIBUTE_READONLY))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
#endif

	return FALSE;
}

BOOLEAN	CFile::renameFile(const char *pcOldFilePath, const char* pcNewFilePath)
{
#ifdef OS_WIN
	return MoveFile(pcOldFilePath, pcNewFilePath) != 0;
#endif

#ifdef OS_LINUX
	//return __rename(pcOldFilePath, pcNewFilePath) = 0;
	return FALSE;
#endif

#ifdef OS_QNX
	return FALSE;
#endif
}

BOOLEAN CFile::deleteFile(const char *pcFilePath)
{
#ifdef OS_WIN
	return DeleteFile(pcFilePath) != 0;
#endif

#ifdef OS_LINUX
	//return unlink(pcFilePath) <> -1;
	return FALSE;
#endif

#ifdef OS_QNX
	return FALSE;
#endif
}

CFile::CFile()
	: m_pFile(NULL)
{
	;
}

CFile::~CFile()
{
	close();
}

BOOLEAN CFile::open(const char *pcFilePath, BOOLEAN bRead)
{
	close();

	if (pcFilePath == NULL)
	{
		return FALSE;
	}

	if (bRead)
	{
		m_pFile = innerOpen(pcFilePath, "rb");
	}
	else
	{
		m_pFile = innerOpen(pcFilePath, "wb");
	}

	return m_pFile != NULL;
}

BOOLEAN CFile::open(const char *pcFilePath, const char* pcMode)
{
	close();

	if (pcFilePath == NULL || pcMode == NULL)
	{
		return FALSE;
	}

	m_pFile = innerOpen(pcFilePath, pcMode);

	return m_pFile != NULL;
}


FILE * CFile::innerOpen(const char *pcFilePath, const char *pcMode)
{
#ifdef OS_WIN
	FILE *pFile = NULL;
	_fopen_s(&pFile, pcFilePath, pcMode);
	return pFile;
#endif

#ifdef OS_QNX
	//char acFilePath[1024];
	//char acMode[32];
	//String::convertToMBCS(pcFilePath, acFilePath, 1024);
	//String::convertToMBCS(pcMode, acMode, 32);

	return fopen(pcFilePath, pcMode);
#endif

#ifdef OS_LINUX
	//char acFilePath[1024];
	//char acMode[32];
	//String::convertToMBCS(pcFilePath, acFilePath, 1024);
	//String::convertToMBCS(pcMode, acMode, 32);

	return fopen(pcFilePath, pcMode);
#endif
}

void CFile::close()
{
	if (m_pFile)
	{
		if(::fclose(m_pFile) == 0)
		{
			m_pFile = NULL;
		}
	}
}

BOOLEAN CFile::isEmpty()
{
	return getFileSize() == 0;
}
TRC_SCOPE_DEF(ADAS, CFile, getFileSize);
UInt32 CFile::getFileSize()
{
	TRC_SCOPE(ADAS, CFile, getFileSize);
	Int32 iFileSize = 0;
	Int32 iCurrentPosition;

	if (m_pFile)
	{
		iCurrentPosition = ftell(m_pFile);
		if(iCurrentPosition == -1)
		{
			DBG_MSG(("CFile::getFileSize iCurrentPosition ftell error\n"));
			return FALSE;
		}
		seekTo(0, ST_END);
		iFileSize = ftell(m_pFile);
		if(iFileSize == -1)
		{
			DBG_MSG(("CFile::getFileSize iFileSize ftell error\n"));
			return FALSE;
		}
		seekTo(iCurrentPosition, ST_BEGIN);
	}

	return iFileSize;
}
TRC_SCOPE_DEF(ADAS, CFile, writeData);
BOOLEAN CFile::writeData(const BYTE *pbtData, UInt32 uiDataLen)
{
	if (m_pFile == NULL)
	{
		return FALSE;
	}
	TRC_SCOPE(ADAS, CFile, writeData);
	if (pbtData != NULL && uiDataLen > 0)
	{
		UInt32 uiWriteCount = ::fwrite(pbtData, 1, uiDataLen, m_pFile);
		if (uiWriteCount < uiDataLen)
		{
			Int32 iErrorCode = ::ferror(m_pFile);
			if (iErrorCode)
			{
				DBG_ERROR(("writeData,iErrorCode=%d\n", iErrorCode));
			}

			return FALSE;
		}
	}

	return TRUE;
}
TRC_SCOPE_DEF(ADAS, CFile, readData);
BOOLEAN CFile::readData(BYTE *pbtData, UInt32 uiDataLen)
{
	if (m_pFile == NULL)
	{
		return FALSE;
	}
	TRC_SCOPE(ADAS, CFile, readData);
	if (pbtData != NULL && uiDataLen > 0)
	{
		UInt32 uiReadCount = ::fread(pbtData, 1, uiDataLen, m_pFile);
		if (uiReadCount < uiDataLen)
		{
			Int32 iErrorCode = ::ferror(m_pFile);
			if (iErrorCode)
			{
				DBG_ERROR(("CFile::readData, error code = %d\n", iErrorCode));
			}

			return FALSE;
		}
	}

	return TRUE;
}
TRC_SCOPE_DEF(ADAS, CFile, seekTo);
Int32 CFile::seekTo(Int32 iDistance, ESeekType eSeekType)
{
	TRC_SCOPE(ADAS, CFile, seekTo);
	Int32 ret;
	if (m_pFile)
	{
		ret = fseek(m_pFile, iDistance, eSeekType);
		if(ret == -1)
		{
			DBG_ERROR(("seek exceed range\n"));
			return FALSE;
		}
		return TRUE;
	}
	return TRUE;
}

void CFile::flush()
{
	if (m_pFile)
	{
		::fflush(m_pFile);
	}
}

