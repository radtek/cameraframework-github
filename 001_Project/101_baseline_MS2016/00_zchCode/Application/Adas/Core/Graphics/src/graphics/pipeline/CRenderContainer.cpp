#include "CRenderContainer.h"
#include "CRenderLayout.h"
#include "CRenderUtility.h"


	CRenderContainer::CRenderContainer(UInt32 uiLayoutMaxNum)
		: m_ptrRT(NULL)
	{
		for( UInt32 i = 0 ; i < uiLayoutMaxNum; ++i )
		{
			m_aryRenderLayout.push_back(new CRenderLayout(this));
		}
	}

	CRenderContainer::~CRenderContainer()
	{
		m_ptrRT = NULL;
	}

	void CRenderContainer::setRenderTarget(CRenderTarget* pRT)
	{
		m_ptrRT = pRT;
	}

	void CRenderContainer::addRenderElement(CRenderElement* pElement)
	{
		m_aryRenderElement.push_back(pElement);
		pElement->retain();
	}

	void CRenderContainer::render(CVertexBuffer& vbo, CIndexBuffer& ibo)
	{
		for( UInt32 i = 0 ; i < m_aryRenderElement.size(); ++i )
		{
			CRenderElement* pRndElement = m_aryRenderElement[i];
			CRenderLayout* p = m_aryRenderLayout[i];
			p->constructFrom(pRndElement);
		}

		//tagScreenContext *pScreenContext = CRenderEngineOS::getInstance()->getScreenContext();
		//tagRenderContext *pRenderContext = CRenderEngineOS::getInstance()->getRenderContext();
		m_matProject.makeOrthognal(m_iX,m_uiW,m_iY, m_uiH,2.0f,1000.0f);

		_render(vbo,ibo);
		

		for( UInt32 i = 0 ; i < m_aryRenderElement.size(); ++i )
		{
			CRenderLayout* p = m_aryRenderLayout[i];
			p->reset();
		}
	}

	void CRenderContainer::clear()
	{
		for( UInt32 i = 0 ; i < m_aryRenderElement.size(); ++i )
		{
			m_aryRenderElement[i]->release();
		}
		m_aryRenderElement.clear();

		for( UInt32 i = 0 ; i < m_aryRenderLayout.size(); ++i )
		{
			m_aryRenderLayout[i]->release();
		}
		m_aryRenderLayout.clear();

	}

	void CRenderContainer::_render(CVertexBuffer& vbo, CIndexBuffer& ibo)
	{
		//tagScreenContext *pScreenContext = CRenderEngineOS::getInstance()->getScreenContext();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glClear( GL_COLOR_BUFFER_BIT );
		glViewport(m_iX, m_iY, m_uiW, m_uiH);

		for( UInt32 i = 0 ; i < m_aryRenderElement.size(); ++i )
		{
			CRenderLayout* p = m_aryRenderLayout[i];
			p->render(vbo, ibo);
		}
	}
