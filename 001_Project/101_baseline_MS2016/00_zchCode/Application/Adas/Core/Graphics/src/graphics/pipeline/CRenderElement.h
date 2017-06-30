#pragma once

#include "common.h"
	class CRenderElement : public Ref
	{
	public:
		enum ERenderElementType
		{
			ERET_NON,
			ERET_IMAGE,
			ERET_RT,
		};

		//typedef CGlobalFuncArg4<CRenderElement*, Int32, Int32, BOOLEAN&>	EventHandlerFunc;

	public:
		CRenderElement(ERenderElementType eType);
		virtual ~CRenderElement();

		ERenderElementType getType() const	{ return m_eType;	}

		void	set(Int32 x, Int32 y ,UInt32 w, UInt32 h);
		Int32		getX()		const	{ return  m_x;	}
		Int32		getY()		const	{ return  m_y;	}
		UInt32	getWidth()	const	{ return  m_width;	}
		UInt32	getHeight() const	{ return  m_height;	}

		//virtual BOOLEAN	isHit(Int32 x, Int32 y) const;
		//BOOLEAN			handleEvent(Int32 x, Int32 y);
		//void			setEventHandler(EventHandlerFunc* pFunc)	{ m_pEventHandler = pFunc;	}

	protected:
		ERenderElementType	m_eType;
		Int32		m_x;
		Int32		m_y;
		UInt32	m_width;
		UInt32	m_height;

		//EventHandlerFunc*	m_pEventHandler;
	};

