#include "CRenderElement.h"

CRenderElement::CRenderElement(ERenderElementType eType)
: m_eType(eType)
, m_x(0)
, m_y(0)
, m_width(0)
, m_height(0)
{
	;
}

CRenderElement::~CRenderElement()
{
}

void CRenderElement::set(Int32 x, Int32 y ,UInt32 w, UInt32 h)
{
	m_x = x;
	m_y = y;
	m_width = w;
	m_height = h;
}


