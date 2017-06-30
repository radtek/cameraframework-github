#pragma once

#include "common.h"
#include "CRenderElement.h"
#include "../resource/CCacheTexture.h"
#include "../resource/CCacheProgram.h"
#include "../resource/CVertexBuffer.h"
#include "../resource/CIndexBuffer.h"


	class CRenderContainer;
	class CRenderLayout : public Ref
	{
	public:
		CRenderLayout(CRenderContainer* pParent);
		virtual ~CRenderLayout();

		void constructFrom(CRenderElement* pRndElement);
		void render(CVertexBuffer& vbo, CIndexBuffer& ibo);
		void reset();

		CRenderContainer*		getParent()		{ return m_pParent;	}

	protected:
		void constructMesh(CRenderElement* pRndElement);

	protected:
		CRenderContainer*		m_pParent;
		CCacheTexture*			m_pTex;
		CCacheProgram*			m_pProgram;
		CVertexBuffer			m_vb;
		CIndexBuffer			m_ib;

	};

