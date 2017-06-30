#pragma once

#include "common.h"
#include "ResourceEnum.h"

	class CVertexBuffer : public Ref
	{
	public:
		CVertexBuffer(BOOLEAN bGPU = FALSE);
		virtual ~CVertexBuffer();

		void			bind(UInt32 format=0);
		void			unBind(UInt32 format=0);
		void			fillBy(const CVertexBuffer& rVB);
		
		void			setup(const Float32* pBuf, UInt32 cnt, UInt32 format, EGPUMemUsage eUsage=EGPUMU_DYNAMIC);
		void			constructQuad(Int32 x, Int32 y, UInt32 uiWidht, UInt32 uiHeight);

		UInt32			getCount() const		{ return m_uiCnt;			}
		const Float32*	getBuffer()	const		{ return m_pBuf;			}
		
		void			setFormat(UInt32 format)	{ m_format = format;		}
		UInt32			getFormat() const		{ return m_format;			}
		UInt32			getVertexStride() const	{ return m_uiVertexStride;	}

		void			release();

		static UInt32		getVertexStride(UInt32 uiFmt);

	protected:
		void		bindAttributes(UInt32 format);
		void		unBindAttributes(UInt32 format);

	protected:
		UInt32		m_uiVertexStride;
		UInt32		m_format;
		EGPUMemUsage	m_eUsage;
		UInt32		m_uiCnt;
		UInt32		m_uiCapacity;
		Float32*		m_pBuf;
		UInt32		m_iVBO;
		BOOLEAN		m_bGPUBuffer;
		
	};


