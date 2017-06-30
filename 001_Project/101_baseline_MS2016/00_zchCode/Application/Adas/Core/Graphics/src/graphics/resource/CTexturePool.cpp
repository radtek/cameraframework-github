#include "CTexturePool.h"
#include "CCacheTexture.h"
#include "CImageParser.h"

	CTexturePool* CTexturePool::s_pInstance	= NULL;

	CTexturePool*	CTexturePool::getInstance()		
	{
		if (s_pInstance == NULL)
		{
			s_pInstance = new CTexturePool();
		}

		return s_pInstance;
	}

	void CTexturePool::deleteInstance()
	{
		if (s_pInstance != NULL)
		{
			delete s_pInstance;
			s_pInstance = NULL;
		}
	}

	CTexturePool::CTexturePool()
		: m_uiTexGPUByteSize(0)
	{
		;
	}

	CTexturePool::~CTexturePool()
	{
		;
	}

	void CTexturePool::initialize()
	{
		;
	}

	void CTexturePool::unInitialize()
	{
		clear();
	}

	void CTexturePool::clear()
	{
		for(HashMap<string, CCacheTexture*>::Iterator it = m_hashMapTexture.begin();
				it != m_hashMapTexture.end() ;++it)
		{
			(*it).second->release();
		}
		
		m_hashMapTexture.clear();
	}
	TRC_SCOPE_DEF(ADAS, CTexturePool, getExternalTexture);
	CCacheTexture* CTexturePool::getExternalTexture(const string& strFilePath)
	{
		TRC_SCOPE(ADAS, CTexturePool, getExternalTexture);
		HashMap<string, CCacheTexture*>::Iterator it = m_hashMapTexture.find(strFilePath);

		if ( it == m_hashMapTexture.end() )
		{
			CCacheTexture* pTex = NULL;
			CImageParser::tagImageInfo info = CImageParser::decodeFromFile(strFilePath.c_str());
			if ( info.pbtPixelData != NULL )
			{
				UInt32 uiTexFormat = TEXFMT_RGBA8888;//mapImageColorTypeToTexFormat(ptrImage->getColorType());
				pTex = createTexture(info.uiWidth, info.uiHeight, info.pbtPixelData, uiTexFormat);
				//pTex->setName(strFilePath);
				//pTex->retain();

				m_hashMapTexture.insert(makePair(strFilePath, pTex));

				delete[] info.pbtPixelData;
			}
			else
			{
				DBG_ERROR(("load image %s failed\n", strFilePath.c_str()));
			}

			return pTex;
		}
		
		return (*it).second;
	}


	void CTexturePool::onTextureRelease(CCacheTexture* pTex)
	{
	//	if( pTex )
	//	{
			//m_uiTexGPUByteSize -= pTex->getGPUByteSize();
	//	}
	}

	CCacheTexture* CTexturePool::createTexture(Int32 uiWidth,Int32 uiHeight,const BYTE* pData,UInt32 uiTexFormat)
	{
		CCacheTexture* pTex = new CCacheTexture();

		pTex->setup(uiWidth,uiHeight,pData,uiTexFormat);
		
		onTextureCreate(pTex);

		return pTex;
	}


	void CTexturePool::onTextureCreate(CCacheTexture* pTex)
	{
		//if( pTex )
		//{
			//m_uiTexGPUByteSize += pTex->getGPUByteSize();
		//}
		;
	}


