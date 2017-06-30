#include "CIndexBuffer.h"


	CIndexBuffer::CIndexBuffer(BOOLEAN bGPU)
		: m_uiCnt(0)
		, m_uiCapacity(0)
		, m_pBuf(NULL)
		, m_iIBO(0)
		, m_bGPUBuffer(bGPU)
		, m_eUsage(EGPUMU_STATIC)
	{
	}

	CIndexBuffer::~CIndexBuffer()
	{
		release();
	}

	void CIndexBuffer::bind()
	{
		if( m_bGPUBuffer)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iIBO );
		}
	}

	void CIndexBuffer::unBind()
	{
		if( m_bGPUBuffer)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0 );
		}
	}

	void CIndexBuffer::fillBy(const CIndexBuffer& rIB)
	{
		if ( m_bGPUBuffer )
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, rIB.getCount()*sizeof(USHORT), rIB.getBuffer(), (GLenum)m_eUsage);
		}
	}

	void CIndexBuffer::setup(const USHORT* pBuf, UInt32 uiCnt, EGPUMemUsage eUsage)
	{
		if ( m_bGPUBuffer )
		{
			if ( m_iIBO != 0 && m_uiCapacity < uiCnt )
			{
				glDeleteBuffers(1,&m_iIBO);
				m_iIBO = 0;
				m_uiCnt = 0;
				m_uiCapacity = 0;
			}

			if ( m_iIBO == 0 )
			{
				m_uiCapacity = uiCnt;
				
				GLuint id;
				glGenBuffers(1, &id);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id );
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, uiCnt*sizeof(USHORT), pBuf, (GLenum)eUsage);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0 );

				m_iIBO = id;
			}
			else
			{
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
				m_uiCapacity = uiCnt;
				m_pBuf = new USHORT[uiCnt];
				if( pBuf )
				{
					memcpy(m_pBuf, pBuf, uiCnt * sizeof(USHORT));
					m_uiCnt = uiCnt;
				}
			}
		}
	}

	void CIndexBuffer::constructQuad()
	{
		setup(NULL,6);
		UInt32 cnt = 0;
		UInt32 uiIdxidx = 0;
		m_pBuf[uiIdxidx+0] = cnt + 0;
		m_pBuf[uiIdxidx+1] = cnt + 1;
		m_pBuf[uiIdxidx+2] = cnt + 2;
		m_pBuf[uiIdxidx+3] = cnt + 0;
		m_pBuf[uiIdxidx+4] = cnt + 2;
		m_pBuf[uiIdxidx+5] = cnt + 3;
		m_uiCnt = 6;
	}

	void CIndexBuffer::draw(UInt32 uiOffset, UInt32 uiCnt)
	{
		if ( m_bGPUBuffer )
		{
			glDrawElements( GL_TRIANGLES, uiCnt, GL_UNSIGNED_SHORT, (void*)(uiOffset) );
		}
	}

	void CIndexBuffer::release()
	{
		if ( m_bGPUBuffer )
		{
			if( m_iIBO )
			{
				glDeleteBuffers(1, &m_iIBO);
				m_iIBO = 0;
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
