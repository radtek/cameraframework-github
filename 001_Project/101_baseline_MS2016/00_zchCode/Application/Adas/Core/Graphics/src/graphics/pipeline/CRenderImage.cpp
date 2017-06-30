#include "CRenderImage.h"



	CRenderImage::CRenderImage()
		: CRenderElement(CRenderElement::ERET_IMAGE)
		, m_pTex(NULL)
		, m_pProgram(NULL)
	{
		;
	}

	CRenderImage::~CRenderImage()
	{
		if( m_pTex )
		{
			m_pTex->release();
		}

		if( m_pProgram )
		{
			m_pProgram->release();
		}

		m_pTex = NULL;
		m_pProgram = NULL;
	}

	void CRenderImage::setTexture(CCacheTexture* pTex)
	{
		if( m_pTex )
			m_pTex->release();

		m_pTex = pTex;

		if( m_pTex )
			m_pTex->retain();

	}

	void CRenderImage::setProgram(CCacheProgram* pPrg)
	{
		if( m_pProgram )
			m_pProgram->release();

		m_pProgram = pPrg;

		if( m_pProgram )
			m_pProgram->retain();

	}
