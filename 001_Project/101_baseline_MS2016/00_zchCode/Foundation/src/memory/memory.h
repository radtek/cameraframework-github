#ifndef _MEMORY_MANAGER_H
#define _MEMORY_MANAGER_H

#include "../common.h"
#include "thread/Mutex.h"

#define USE_MEMMANAGER \
	void* operator new(size_t size) \
	{ \
		return CMemManager::getInstance()->alloc(size);	\
	} \
	void operator delete(void* p)\
	{\
		CMemManager::getInstance()->dealloc(p);\
	}


class CMemManager
{
public: // enum struct
	// 8, 16, 24, 32, 40,48, 56,64, 72, 80,88, 96, 104, 112, 120, 128
	enum { eSmallBinNum = (128/8) 	};
	enum { eMaxChunkSize = 128		};
	enum { eMinChunkSize = 8		};
	struct tagChunkHead
	{
		unsigned short	_uiChunkMemSize;
	};

	typedef struct _tagFreeChunk
	{
		_tagFreeChunk* 	_pNext;
		_tagFreeChunk*	_pPrev;
	}tagFreeChunk;

	struct tagSmallBin
	{
		UInt32			_uiChunkMemSize;
		UInt32			_uiInitialSize;
		UInt32			_uiExtendSize;
		tagFreeChunk*	_pHeadFreeChunk;
		UInt32			_uiTotalSize;
		Array<void*>	_aryMemBlock;

	};

public: // method
	static CMemManager* getInstance();
	static void			delelteInstance();

	void	registerSmallBin(UInt32 uiChunkMemSize, UInt32 uiInitialSize, UInt32 uiExtendSize);

	BOOLEAN	initialize();
	void	unInitialize();

	void*	alloc(UInt32 uiSize);
	void	dealloc(void* p);

private: // method
	CMemManager();
	~CMemManager();

	void*	allocFromSmallBin(UInt32 uidx);
	void	deallocToSmallBin(tagFreeChunk* pChunk, UInt32 uidx);
	void*  	sysAlloc(UInt32 uiSize);
	void	sysDealloc(void* p);

	void	allocSmallBin(tagSmallBin* pSmallBin, BOOLEAN bExtendAlloc );

private: // data
	static CMemManager*	s_pInstance;
	tagSmallBin			m_smallBins[eSmallBinNum];
	Mutex				m_mutex;
	//map<UInt32, UInt32>		m_mapSmallBin
};

#endif
