#include "CScreenBufferArray.h"
#include "CScreenWindow.h"

#ifdef PLATFORM_QNX

CScreenBufferArray::CScreenBufferArray(CScreenWindow* pWindow)
: m_pParent(pWindow)
, m_pBuf(NULL)
, m_pPhysicalAddr(NULL)
, m_pVirtualAddr(NULL)
, m_uiBufNum(0)
, m_uiFormat(0)
, m_uiStride(0)
, m_uiW(0)
, m_uiH(0)
{

}

CScreenBufferArray::~CScreenBufferArray()
{
	destroy();
}
TRC_SCOPE_DEF(ADAS, CScreenBufferArray, setup);
BOOLEAN CScreenBufferArray::setup(UInt32 uiW, UInt32 uiH, UInt32 uiNum, BOOLEAN bContinous)
{
	if( m_pBuf != NULL || m_pParent == NULL )
		return FALSE;
	TRC_SCOPE(ADAS, CScreenBufferArray, setup);
	DBG_MSG(("CScreenBufferArray::setup num = %u\n", uiNum));

	m_uiW = uiW;
	m_uiH = uiH;
	m_uiFormat = m_pParent->getFormat();
	m_uiBufNum = uiNum;

	screen_window_t screenWin = m_pParent->getWin();

	Int32 rc = 0;
	if(NULL == m_pBuf)
	{
		m_pBuf = (screen_buffer_t*)malloc(uiNum * sizeof(screen_buffer_t));
		if (NULL != m_pBuf)
		{
			memset(m_pBuf,0,sizeof(screen_buffer_t));
		}
		else
		{
			DBG_ERROR(("malloc screen buffer failed!\n"));
			return FALSE;
		}
	}

	//set window buffer size
	Int32 iSize[2];
	iSize[0] = uiW;
	iSize[1] = uiH;
    rc = screen_set_window_property_iv(screenWin, SCREEN_PROPERTY_BUFFER_SIZE, iSize);
    if (rc) {
        DBG_ERROR(( "screen_set_window_property_iv(SCREEN_PROPERTY_BUFFER_SIZE):%s\n",strerror(errno)));
        return FALSE;
    }
    //set window buffer number
    rc = screen_create_window_buffers(screenWin, uiNum);
    if (rc) {
        DBG_ERROR(( "screen_create_window_buffers:%s\n",strerror(errno)));
        return FALSE;
    }

    rc = screen_get_window_property_pv(screenWin, SCREEN_PROPERTY_RENDER_BUFFERS, (void **)m_pBuf);
	if (rc) {
		DBG_ERROR(("screen_get_window_property_pv(SCREEN_PROPERTY_RENDER_BUFFERS):%s\n",strerror(errno)));
		return FALSE;
	}

	if( bContinous  )
	{
		if( !getContiguousBufAddress() )
		{
			DBG_ERROR(("getContiguousBufAddress failed\n"));
			return FALSE;
		}
	}

	if(m_pBuf[0] && m_uiStride == 0 )
	{
		Int32 iStride = 0;
		Int32 rc = screen_get_buffer_property_iv(m_pBuf[0], SCREEN_PROPERTY_STRIDE, (Int32*)&iStride);
		if (rc) {
			DBG_ERROR(("screen_get_buffer_property_iv(SCREEN_PROPERTY_STRIDE):%s\n",strerror(errno)));
			return 0;
		}
		DBG_MSG(("screenbuffer stride ver1 %d\n", iStride));
		m_uiStride = (UInt32)iStride;
	}

    SetupDummyBuffer();

	return TRUE;
}

#define DUMMY_YUV_COLOR_BLACK  (0x80)
TRC_SCOPE_DEF(ADAS, CScreenBufferArray, SetupDummyBuffer);
void CScreenBufferArray::SetupDummyBuffer()
{
	TRC_SCOPE(ADAS, CScreenBufferArray, SetupDummyBuffer);
    int height = m_uiH/2;
    int length = m_uiStride;
	void** pScreenBufData = (void** )getVirtualAddr();    
    unsigned short* pImage = NULL;
    if((NULL!=pScreenBufData)&&(NULL!=pScreenBufData[m_uiBufNum-1]))
    {
        pImage = (unsigned short*)pScreenBufData[m_uiBufNum-1];
        DBG_MSG(("pImageDummy point value:%x\n",(unsigned int)pImage));
    }  
    else
    {
        DBG_MSG(("pImageDummy point value not exist!\n"));  
        return;
    }   
    
    for(int i=0;i<height;i++)
    {
      for(int j=0;j<length;j++)
      {
         pImage[i*length+j]=DUMMY_YUV_COLOR_BLACK;
      }

    }
}

void CScreenBufferArray::destroy()
{
	if( m_pBuf && m_uiBufNum )
	{
		free(m_pBuf);
		m_pBuf = NULL;
		m_uiBufNum = NULL;
	}

	if( m_pPhysicalAddr)
	{
		free(m_pPhysicalAddr);
		m_pPhysicalAddr = NULL;
	}

	if( m_pVirtualAddr)
	{
		free(m_pVirtualAddr);
		m_pVirtualAddr = NULL;
	}
}
TRC_SCOPE_DEF(ADAS, CScreenBufferArray, getContiguousBufAddress);
BOOLEAN CScreenBufferArray::getContiguousBufAddress()
{
	TRC_SCOPE(ADAS, CScreenBufferArray, getContiguousBufAddress);
	Int32 rc = 0;
	//physical address
	if(NULL == m_pPhysicalAddr)
	{
		m_pPhysicalAddr = (long long*)malloc(m_uiBufNum * sizeof(long long));
		if(NULL == m_pPhysicalAddr)
		{
			DBG_ERROR(("malloc screen physical address buffer failed!\n"));
			return FALSE;
		}
		else
		{
			memset(m_pPhysicalAddr,0,sizeof(m_uiBufNum * sizeof(long long)));
			for(UInt32 i = 0; i < m_uiBufNum; i++ )
			{
				rc = screen_get_buffer_property_llv(m_pBuf[i], SCREEN_PROPERTY_PHYSICAL_ADDRESS, &(m_pPhysicalAddr[i]));
				if (rc)
				{
					DBG_ERROR(("screen_get_buffer_property_llv(SCREEN_PROPERTY_PHYSICAL_ADDRESS):%s\n",strerror(errno)));
					return FALSE;
				}
			}
		}
	}

	//virtual address
	if(NULL == m_pVirtualAddr)
	{
		m_pVirtualAddr = (unsigned char**)malloc(m_uiBufNum * sizeof(unsigned char*));
		if(NULL == m_pVirtualAddr)
		{
			DBG_ERROR(("malloc screen virtual address buffer failed!\n"));
			return FALSE;
		}
		else
		{
			memset(m_pVirtualAddr,0,m_uiBufNum * sizeof(unsigned char*));
			for(UInt32 i = 0; i < m_uiBufNum; i++ )
			{
				rc = screen_get_buffer_property_pv(m_pBuf[i], SCREEN_PROPERTY_POINTER, (void**)(&(m_pVirtualAddr[i])));
				if (rc)
				{
					DBG_ERROR(("screen_get_buffer_property_pv(SCREEN_PROPERTY_POINTER):%s\n",strerror(errno)));
					return FALSE;
				}
			}
		}
	}

    for(int cnt=0;cnt<m_uiBufNum; cnt++)
    {
       DBG_MSG(("-------->set capture buf addr= %x\n",(unsigned int)m_pVirtualAddr[cnt]));
    }

	return TRUE;
}

void CScreenBufferArray::fill(UInt32 uidx, unsigned char* pData)
{
	unsigned char *ptr = NULL;
	screen_get_buffer_property_pv(m_pBuf[uidx], SCREEN_PROPERTY_POINTER, (void **)&ptr);

	memcpy(ptr, pData, m_uiStride*m_uiW*m_uiH);	//the size of pData is the same as screen buffer
	// if the size is not the same, should not use it
}

#endif
