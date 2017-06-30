#include "CRenderLayout.h"
#include "CRenderImage.h"


	CRenderLayout::CRenderLayout(CRenderContainer* pParent)
		: m_pParent(pParent)
		, m_pTex(NULL)
		, m_pProgram(NULL)
	{
		;
	}

	CRenderLayout::~CRenderLayout()
	{
		reset();
	}

	void CRenderLayout::constructFrom(CRenderElement* pRndElement)
	{
		switch( pRndElement->getType() )
		{
		case CRenderElement::ERET_IMAGE:
			{
				CRenderImage* pRndImage = static_cast<CRenderImage*>(pRndElement);
				if( pRndImage->getTexture() == NULL ||
					pRndImage->getProgram() == NULL )
					return;
				m_pTex = pRndImage->getTexture();
				m_pTex->retain();
				m_pProgram = pRndImage->getProgram();
				m_pProgram->retain();
			}
			break;
		case CRenderElement::ERET_RT:
			{
				//CRenderTargetElement* pRnd = static_cast<CRenderTargetElement*>(pRndElement);
				//m_pTex = pRnd->getTexture();
				//m_pProgram = pRnd->getProgram();
			}
			break;
		default:
			break;
		}

		constructMesh(pRndElement);
	}

	void CRenderLayout::render(CVertexBuffer& vbo, CIndexBuffer& ibo)
	{
		if( m_pTex == NULL || m_pProgram == NULL )
			return;

		UInt32 format = m_vb.getFormat();
		vbo.bind(format);
		ibo.bind();

		m_pProgram->begin();
		m_pProgram->setUniforms(this);
		m_pProgram->setTextureUniforms(m_pTex);
		m_pProgram->end();

		vbo.fillBy(m_vb);
		ibo.fillBy(m_ib);

		//vbo.bindVertexFormat(m_vb.getFormat());
		ibo.draw(0, m_ib.getCount());

		vbo.unBind(format);
		ibo.unBind();
	}

	void CRenderLayout::reset()
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

		//m_vb.reset();
		//m_ib.reset();
	}

	void CRenderLayout::constructMesh(CRenderElement* pRndElement)
	{
		m_vb.setFormat(EVBFMT_POSITION3|EVBFMT_TEXCOORD0|EVBFMT_REPLACE3);
		m_vb.constructQuad(pRndElement->getX(), pRndElement->getY(), 
			pRndElement->getWidth(), pRndElement->getHeight());
		
		m_ib.constructQuad();
	}
