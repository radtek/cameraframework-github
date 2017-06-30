#pragma once

#include "common.h"
#include "ResourceEnum.h"


	class CIndexBuffer : public Ref
	{
	public:
		CIndexBuffer(BOOLEAN bGPU = FALSE);
		virtual ~CIndexBuffer();

		void	bind();
		void	unBind();
		void	fillBy(const CIndexBuffer& rIB);

		void	setup(const USHORT* pBuf, UInt32 uiCnt, EGPUMemUsage eUsage=EGPUMU_DYNAMIC);
		void	constructQuad();

		void	draw(UInt32 uiOffset, UInt32 uiCnt);

		UInt32			getCount() const		{ return m_uiCnt;		}
		const USHORT*	getBuffer()	const		{ return m_pBuf;		}

		void	release();

	protected:
		UInt32		m_uiCnt;
		UInt32		m_uiCapacity;
		USHORT*		m_pBuf;
		UInt32		m_iIBO;
		BOOLEAN		m_bGPUBuffer;
		EGPUMemUsage	m_eUsage;
	};


