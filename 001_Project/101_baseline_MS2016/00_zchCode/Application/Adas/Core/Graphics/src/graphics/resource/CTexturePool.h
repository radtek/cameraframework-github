#ifndef __CTEXTUREPOOL_H_INCLUDED__
#define __CTEXTUREPOOL_H_INCLUDED__

#include "common.h"

class CCacheTexture;

	class CTexturePool
	{
	public:// const define

	private:// const define

	public:// embed class or struct or enum

	private:// embed class or struct or enum

	public:// method	
		//IMP_OPERATOR_NEW(CTexturePool)

		static	CTexturePool*	getInstance();
		static	void			deleteInstance();

		void				initialize();
		void				unInitialize();
		void				clear();


		CCacheTexture*		getExternalTexture(const string& strFilePath);


		void				onTextureRelease(CCacheTexture* pTex);
		UInt32				getTextureGPUByteSize() const		{ return m_uiTexGPUByteSize;	}

	protected:// method	
		CTexturePool();
		virtual ~CTexturePool();

	private:// method		
		CCacheTexture*	createTexture(Int32 uiWidth,Int32 uiHeight,const BYTE* pData,UInt32 uiTexFormat);
		string			generateName(const char* sz, UInt32 uiAddress);

		void			onTextureCreate(CCacheTexture* pTex);

	protected:// property

	private:// property
		static	CTexturePool	*s_pInstance;

		//CachePool<String, CCacheTexture, tagStringCompare>	m_cacheImgPool;
		//CachePool<String, CCacheTexture, tagStringCompare>	m_cacheBigImgPool;
		
		HashMap<string, CCacheTexture*>		m_hashMapTexture;

		UInt32												m_uiTexGPUByteSize;
	};


#endif
