#pragma once

#include "CRenderElement.h"
#include "../resource/CCacheTexture.h"
#include "../resource/CCacheProgram.h"

	
	class CRenderImage : public CRenderElement
	{
	public:
		CRenderImage();
		virtual ~CRenderImage();

		void	setTexture(CCacheTexture* pTex);
		void	setProgram(CCacheProgram* pPrg);
		
		CCacheTexture*	getTexture()				{ return m_pTex;		}
		CCacheProgram*	getProgram()				{ return m_pProgram;	}

	protected:
		CCacheTexture*	m_pTex;
		CCacheProgram*	m_pProgram;
	};
