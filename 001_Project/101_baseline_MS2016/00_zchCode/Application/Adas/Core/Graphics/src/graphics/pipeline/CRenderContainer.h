#pragma once

#include "common.h"
#include "CRenderElement.h"

class CVertexBuffer;
class CIndexBuffer;
class CRenderLayout;
class CRenderTarget;
class CRenderContainer
{
public:
	CRenderContainer(UInt32 uiLayoutMaxNum=10);
	~CRenderContainer();

public:
	void setRenderTarget(CRenderTarget* pRT);
	void setRectangle(Int32 x, Int32 y, UInt32 uiW, UInt32 uiH)
	{
		m_iX = x;
		m_iY = y;
		m_uiW = uiW;
		m_uiH = uiH;
	}

	void addRenderElement(CRenderElement* pElement);

	void render(CVertexBuffer& vbo, CIndexBuffer& ibo);

	void clear();

	const C3DMatrix4& getProjectMatrix() const { return m_matProject;	}

protected:
	void _render(CVertexBuffer& vbo, CIndexBuffer& ibo);

protected:
	Int32					m_iX;
	Int32					m_iY;
	UInt32					m_uiW;
	UInt32					m_uiH;

	CRenderTarget*			m_ptrRT;
	C3DMatrix4				m_matProject;

	Array<CRenderLayout*>	m_aryRenderLayout;

	Array<CRenderElement*>	m_aryRenderElement;
};

