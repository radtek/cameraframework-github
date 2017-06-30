#include "CVertexBuffer.h"


	CVertexBuffer::CVertexBuffer(BOOLEAN bGPU)
		: m_uiVertexStride(0)
		, m_format(0)
		, m_eUsage(EGPUMU_STATIC)
		, m_uiCnt(0)
		, m_uiCapacity(0)
		, m_pBuf(NULL)
		, m_iVBO(0)
		, m_bGPUBuffer(bGPU)
	{
		;
	}

	CVertexBuffer::~CVertexBuffer()
	{
		release();
	}

	void CVertexBuffer::bind(UInt32 format)
	{
		if( m_bGPUBuffer)
		{
			glBindBuffer( GL_ARRAY_BUFFER, m_iVBO );
			if ( format == 0 )
			{
				bindAttributes(m_format);
			}
			else
			{
				bindAttributes(format);
			}
		}
	}

	void CVertexBuffer::unBind(UInt32 format)
	{
		if( m_bGPUBuffer)
		{
			if ( format == 0 )
			{
				unBindAttributes(m_format);
			}			
			else
			{
				unBindAttributes(format);
			}
			glBindBuffer( GL_ARRAY_BUFFER, 0 );
			
		}
	}

	void CVertexBuffer::fillBy(const CVertexBuffer& rVB)
	{
		if ( m_bGPUBuffer )
		{
			glBufferData(GL_ARRAY_BUFFER, rVB.getCount() * rVB.getVertexStride() * sizeof(Float32), rVB.getBuffer(), (GLenum)m_eUsage);
		}
	}

	void CVertexBuffer::setup(const Float32* pBuf, UInt32 uiCnt, UInt32 format, EGPUMemUsage eUsage)
	{
		if ( m_bGPUBuffer )
		{
			if ( m_iVBO != 0 && m_uiCapacity < uiCnt )
			{
				glDeleteBuffers(1,&m_iVBO);
				m_iVBO = 0;
				m_uiCnt = 0;
				m_uiCapacity = 0;
			}

			if ( m_iVBO == 0 )
			{
				m_uiCapacity = uiCnt;
				m_format = format;
				m_uiVertexStride = getVertexStride(format);
			
				GLuint id;
				glGenBuffers(1, &id);

				glBindBuffer(GL_ARRAY_BUFFER, id );
				glBufferData( GL_ARRAY_BUFFER, m_uiVertexStride * uiCnt * sizeof(Float32), pBuf, (GLenum)eUsage);
				glBindBuffer(GL_ARRAY_BUFFER, 0 );

				m_iVBO = id;
			}
			m_eUsage = eUsage;
		}
		else
		{
			if (m_uiCapacity < uiCnt && m_pBuf != NULL )
			{
				delete[] m_pBuf;
				m_pBuf = NULL;
				m_uiCnt = 0;
				m_uiCapacity = 0;
			}

			if( m_pBuf == NULL )
			{
				m_uiVertexStride = getVertexStride(format);
				m_format = format;
				m_uiCapacity = uiCnt;
				m_pBuf = new Float32[uiCnt*m_uiVertexStride];
				if( pBuf )
				{
					memcpy(m_pBuf, pBuf, m_uiVertexStride * uiCnt * sizeof(Float32));
					m_uiCnt = uiCnt;
				}
			}
		}
	}

	void CVertexBuffer::constructQuad(Int32 x, Int32 y, UInt32 uiWidth, UInt32 uiHeight)
	{
		setup(NULL, 4,EVBFMT_POSITION3|EVBFMT_TEXCOORD0|EVBFMT_REPLACE3 );

		m_uiVertexStride = getVertexStride(m_format);
		UInt32 cnt = 0;
		m_pBuf[cnt *m_uiVertexStride + 0] = Float32(x);
		m_pBuf[cnt *m_uiVertexStride + 1] = Float32(y);
		m_pBuf[cnt *m_uiVertexStride + 2] = 1.0f;
		m_pBuf[cnt *m_uiVertexStride + 3] = 0.0f;
		m_pBuf[cnt *m_uiVertexStride + 4] = 0.0f;
		++cnt;

		m_pBuf[cnt *m_uiVertexStride + 0] = Float32(x);
		m_pBuf[cnt *m_uiVertexStride + 1] = Float32(y+uiHeight);
		m_pBuf[cnt *m_uiVertexStride + 2] = 1.0f;
		m_pBuf[cnt *m_uiVertexStride + 3] = 0.0f;
		m_pBuf[cnt *m_uiVertexStride + 4] = 1.0f;
		++cnt;

		m_pBuf[cnt *m_uiVertexStride + 0] = Float32(x+uiWidth);
		m_pBuf[cnt *m_uiVertexStride + 1] = Float32( y+uiHeight);
		m_pBuf[cnt *m_uiVertexStride + 2] = 1.0f;
		m_pBuf[cnt *m_uiVertexStride + 3] = 1.0f;
		m_pBuf[cnt *m_uiVertexStride + 4] = 1.0f;
		++cnt;

		m_pBuf[cnt *m_uiVertexStride + 0] = Float32(x+uiWidth);
		m_pBuf[cnt *m_uiVertexStride + 1] = Float32(y);
		m_pBuf[cnt *m_uiVertexStride + 2] = 1.0f;
		m_pBuf[cnt *m_uiVertexStride + 3] = 1.0f;
		m_pBuf[cnt *m_uiVertexStride + 4] = 0.0f;

		m_uiCnt = 4;
	}

	void CVertexBuffer::release()
	{
		if ( m_bGPUBuffer )
		{
			if( m_iVBO )
			{
				glDeleteBuffers(1, &m_iVBO);
				m_iVBO = 0;
			}
		}
		else
		{
			if( m_pBuf )
			{
				delete[] m_pBuf;
				m_pBuf = NULL;
			}
		}
	}

	UInt32 CVertexBuffer::getVertexStride(UInt32 uiFmt)
	{
		UInt32 uiStride = 0;
		if( uiFmt & EVBFMT_POSITION2)
		{
			uiStride +=2;
		}
		else if ( uiFmt & EVBFMT_POSITION3)
		{
			uiStride +=3;
		}

		if ( uiFmt & EVBFMT_NORMAL )
		{
			uiStride +=3;
		}

		if ( uiFmt & EVBFMT_TEXCOORD0)
		{
			uiStride += 2;
		}

		if ( uiFmt & EVBFMT_COLOR4 )
		{
			uiStride += 4;
		}

		if ( uiFmt & EVBFMT_REPLACE3 )
		{
			uiStride += 3;
		}

		if ( uiFmt & EVBFMT_REPLACE2 )
		{
			uiStride += 2;
		}

		return uiStride;
	}

	void CVertexBuffer::bindAttributes(UInt32 format)
	{
		UInt32 uiVertexSize = m_uiVertexStride;
		UInt32 uiOffset = 0;
		UInt32 uiFmt = format;
		UInt32 uiVAAIndex = 0;

		if ( uiFmt & EVBFMT_POSITION2 )
		{
			glEnableVertexAttribArray(uiVAAIndex);
			glVertexAttribPointer(uiVAAIndex, 2 , GL_FLOAT, GL_FALSE, uiVertexSize * sizeof(Float32) , (void*)uiOffset);
			
			uiOffset+= 2* sizeof(Float32);
			++uiVAAIndex;
		}
		else if ( uiFmt & EVBFMT_POSITION3 )
		{
			glEnableVertexAttribArray(uiVAAIndex);
			glVertexAttribPointer(uiVAAIndex, 3 , GL_FLOAT, GL_FALSE, uiVertexSize * sizeof(Float32) , (void*)uiOffset);
			
			uiOffset+= 3* sizeof(Float32);
			++uiVAAIndex;
		}

		if ( uiFmt & EVBFMT_TEXCOORD0 )
		{
			glEnableVertexAttribArray(uiVAAIndex);
			glVertexAttribPointer(uiVAAIndex, 2, GL_FLOAT, GL_FALSE, uiVertexSize * sizeof(Float32), (void*)uiOffset);
			++uiVAAIndex;
			uiOffset+= 2* sizeof(Float32);
		}

		if ( uiFmt & EVBFMT_COLOR4 )
		{
			glEnableVertexAttribArray(uiVAAIndex);
			glVertexAttribPointer(uiVAAIndex, 4, GL_FLOAT, GL_FALSE, uiVertexSize * sizeof(Float32), (void*)uiOffset);
//			++uiVAAIndex;
//			uiOffset+= 4* sizeof(Float32);
		}

	}

	void CVertexBuffer::unBindAttributes(UInt32 format)
	{
		//UInt32 uiVertexSize = m_uiVertexStride;
		//UInt32 uiOffset = 0;
		UInt32 uiFmt = format;
		UInt32 uiVAAIndex = 0;

		if ( uiFmt & EVBFMT_POSITION2 )
		{
			glDisableVertexAttribArray( uiVAAIndex );
			++uiVAAIndex;
		}
		else if ( uiFmt & EVBFMT_POSITION3 )
		{
			glDisableVertexAttribArray( uiVAAIndex );
			++uiVAAIndex;
		}
		if ( uiFmt & EVBFMT_TEXCOORD0 )
		{
			glDisableVertexAttribArray( uiVAAIndex );
			++uiVAAIndex;
		}
		if ( uiFmt & EVBFMT_COLOR4 )
		{
			glDisableVertexAttribArray( uiVAAIndex );
	//		++uiVAAIndex;
		}

	}
