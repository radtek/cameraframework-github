#include "memory.h"

#define UsedChunkHead(pChunk)	(tagChunkHead*)((char*)pChunk - sizeof(tagChunkHead))
static const UInt32 s_uiAlignSize = 8;

CMemManager* CMemManager::s_pInstance = NULL;

CMemManager* CMemManager::getInstance()
{
	if( s_pInstance == NULL )
	{
		s_pInstance = new CMemManager();
	}

	return s_pInstance;
}

void CMemManager::delelteInstance()
{
	if( s_pInstance )
	{
		delete s_pInstance;
		s_pInstance = NULL;
	}
}

CMemManager::CMemManager()
{
	for(UInt32 i = 0 ;i < eSmallBinNum; ++i)
	{
		m_smallBins[i]._pHeadFreeChunk = NULL;
		m_smallBins[i]._uiChunkMemSize = (i+1)*8;
		m_smallBins[i]._uiExtendSize = 8;
		m_smallBins[i]._uiInitialSize = 32;
		m_smallBins[i]._uiTotalSize = 0;
	}
}

CMemManager::~CMemManager()
{
	unInitialize();
}

void CMemManager::registerSmallBin(UInt32 uiChunkMemSize, UInt32 uiInitialSize, UInt32 uiExtendSize)
{
	UInt32 uidx = ((uiChunkMemSize + s_uiAlignSize - 1) >> 3);
	m_smallBins[uidx]._uiInitialSize = uiInitialSize;
	m_smallBins[uidx]._uiExtendSize = uiExtendSize;
}

BOOLEAN	CMemManager::initialize()
{
	return TRUE;
}

void CMemManager::unInitialize()
{
	for(UInt32 i = 0 ;i < eSmallBinNum; ++i)
	{
		Array<void*>& ary = m_smallBins[i]._aryMemBlock;
		for(UInt32 j = 0 ; j < ary.size() ; ++j )
		{
			sysDealloc(ary[j]);
		}
		ary.clear();
		m_smallBins[i]._pHeadFreeChunk = NULL;
		m_smallBins[i]._uiExtendSize = 0;
		m_smallBins[i]._uiInitialSize = 0;
		m_smallBins[i]._uiTotalSize = 0;
	}
}

void* CMemManager::alloc(UInt32 uiSize)
{

	//return sysAlloc(uiSize);


	if ( uiSize > eMaxChunkSize )
	{
		void* pChunk = sysAlloc(uiSize+sizeof(tagChunkHead));
		if(pChunk!=NULL)
		{
			tagChunkHead* pHead = (tagChunkHead*)pChunk;
			pHead->_uiChunkMemSize = uiSize;

			return (void*)((char*)pChunk+sizeof(tagChunkHead));
		}
		else
			return NULL;
	}
	else
	{
		//DBG_MSG(("CMemManager::alloc %u\n", uiSize));
		UInt32 uidx = ((uiSize + s_uiAlignSize - 1) >> 3);
		//m_mutex.lock();

		void* p = allocFromSmallBin(uidx-1);
		//m_mutex.unlock();
		return p;
	}
}

void CMemManager::dealloc(void* p)
{
	tagChunkHead *pHead = UsedChunkHead(p);

	if( pHead->_uiChunkMemSize > eMaxChunkSize )
	{
		sysDealloc(pHead);
	}
	else
	{
		UInt32 uidx = ((pHead->_uiChunkMemSize + s_uiAlignSize - 1) >> 3);

		m_mutex.lock();
		deallocToSmallBin((tagFreeChunk*)pHead, uidx-1);

		m_mutex.unlock();
	}

}

void* CMemManager::allocFromSmallBin(UInt32 uidx)
{
	tagSmallBin* pSmallBin = &m_smallBins[uidx];
	if( pSmallBin->_pHeadFreeChunk == NULL )
	{
		if( pSmallBin->_uiTotalSize == 0 )
		{
			allocSmallBin(pSmallBin, FALSE);
		}
		else
		{
			allocSmallBin(pSmallBin, TRUE);
		}
	}

	{
		tagFreeChunk* pChunk = pSmallBin->_pHeadFreeChunk;
		pSmallBin->_pHeadFreeChunk = pChunk->_pNext;
		if( pSmallBin->_pHeadFreeChunk )
			pSmallBin->_pHeadFreeChunk->_pPrev = NULL;

		tagChunkHead* pHead = (tagChunkHead*)pChunk;
		pHead->_uiChunkMemSize = pSmallBin->_uiChunkMemSize;
		return (void*)((char*)pChunk+sizeof(tagChunkHead));
	}
}

void CMemManager::deallocToSmallBin(tagFreeChunk* p, UInt32 uidx)
{
	tagSmallBin* pSmallBin = &m_smallBins[uidx];

	p->_pNext = pSmallBin->_pHeadFreeChunk;
	p->_pPrev = NULL;

	if( pSmallBin->_pHeadFreeChunk )
		pSmallBin->_pHeadFreeChunk->_pPrev = p ;

	pSmallBin->_pHeadFreeChunk = p;
}
TRC_SCOPE_DEF(ADAS, CMemManager, sysAlloc);
void* CMemManager::sysAlloc(UInt32 uiSize)
{
	TRC_SCOPE(ADAS, CMemManager, sysAlloc);
	//DBG_MSG(("CMemManager::sysAlloc %u\n", uiSize));
	void *p =(void*)::malloc(uiSize);
	if(NULL == p)
	{
		DBG_ERROR(("sysAlloc failed!\n"));
		return NULL;
	}
	else 
		return p;
}

void CMemManager::sysDealloc(void* p)
{
	::free(p);
}
TRC_SCOPE_DEF(ADAS, CMemManager, allocSmallBin);
void CMemManager::allocSmallBin(tagSmallBin* pSmallBin, BOOLEAN bExtendAlloc )
{
	TRC_SCOPE(ADAS, CMemManager, allocSmallBin);
	if( pSmallBin )
	{
		UInt32 uiSize = 0;
		void* pData = NULL;
		UInt32 uiByteSize = (pSmallBin->_uiChunkMemSize + sizeof(tagChunkHead));
		if( bExtendAlloc )
		{
			UInt32 uiExtendByteSize = pSmallBin->_uiExtendSize *  uiByteSize;
			pData = sysAlloc(uiExtendByteSize);
			pSmallBin->_aryMemBlock.push_back(pData);
			pSmallBin->_uiTotalSize += pSmallBin->_uiExtendSize;

			pSmallBin->_pHeadFreeChunk = (tagFreeChunk*)pData;
			uiSize = pSmallBin->_uiExtendSize ;
		}
		else
		{
			UInt32 uiInitialByteSize = pSmallBin->_uiInitialSize * uiByteSize;
			pData = sysAlloc(uiInitialByteSize);
			pSmallBin->_aryMemBlock.push_back(pData);
			pSmallBin->_uiTotalSize = pSmallBin->_uiInitialSize;

			pSmallBin->_pHeadFreeChunk = (tagFreeChunk*)pData;
			uiSize = pSmallBin->_uiInitialSize ;
		}

		//DBG_MSG(("CMemManager::allocSmallBin 1 = %u %u\n", uiSize, uiByteSize));
		char* pCur = (char*)pData;
		tagFreeChunk* pChunk = (tagFreeChunk*)pCur;

		//DBG_MSG(("CMemManager::allocSmallBin 2-1\n"));
		tagFreeChunk* pNextChunk = (tagFreeChunk*)(pCur+uiByteSize);

		//DBG_MSG(("CMemManager::allocSmallBin 2-2\n"));
		pChunk->_pPrev = NULL;
		pChunk->_pNext = pNextChunk;
		//DBG_MSG(("CMemManager::allocSmallBin 2-3\n"));
		//DBG_MSG(("CMemManager::allocSmallBin 2-4\n"));
		for( UInt32 i = 0 ; i < (uiSize-1); ++i )
		{
			//DBG_MSG(("CMemManager::allocSmallBin 3 %u %u\n", i, (UInt32)pCur));
			pChunk->_pNext = pNextChunk;

			//DBG_MSG(("CMemManager::allocSmallBin 3-1"));
			pNextChunk->_pPrev = pChunk;
			//DBG_MSG(("CMemManager::allocSmallBin 3-2"));

			pCur += uiByteSize;
			pChunk = pNextChunk;
			pNextChunk = (tagFreeChunk*)(pCur+uiByteSize);
		}

		DBG_MSG(("CMemManager::allocSmallBin 4\n"));
		pChunk->_pNext = NULL;
	}
}
