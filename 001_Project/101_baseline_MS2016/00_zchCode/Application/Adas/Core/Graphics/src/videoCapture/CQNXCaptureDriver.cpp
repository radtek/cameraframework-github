#include "CQNXCaptureDriver.hpp"

TRC_SCOPE_DEF(CQNXCaptureDriver, CQNXCaptureDriver, bCapInit);

CQNXCaptureDriver::CQNXCaptureDriver()
: m_curSourceIdx(0)
, m_bCapEnabled(FALSE)
, m_bCapActiveReady(FALSE)
{
	m_CapContext = NULL;
	m_iBufIndex = -1;
	m_iPrevBufIndex = -1;
	frame_timestamp = NULL;
	frame_flags = NULL;
	m_iInterlaceField = INTERLACE_FIELD_VALUE_INVALID;

#ifdef CAPTURE_NEED_SEQNO
	frame_seqno = NULL;
#endif
}

CQNXCaptureDriver::~CQNXCaptureDriver()
{
	;
}

void CQNXCaptureDriver::vCapRelease()
{
	if(m_CapContext != NULL) {
		capture_destroy_context( m_CapContext);
		m_CapContext = NULL;
	}
	if(frame_timestamp)
	{
		free(frame_timestamp);
		frame_timestamp = NULL;
	}
	if(frame_flags)
	{
		free(frame_flags);
		frame_flags = NULL;
	}
#ifdef CAPTURE_NEED_SEQNO
	if(frame_seqno)
	{
		free(frame_seqno);
		frame_seqno = NULL;
	}
#endif

	m_bInit = false;
}
TRC_SCOPE_DEF(ADAS, CQNXCaptureDriver, bCapInit);
bool CQNXCaptureDriver::bCapInit(void* pConfig)
{
	if(pConfig == NULL)
		return false;
	TRC_SCOPE(ADAS, CQNXCaptureDriver, bCapInit);
	DBG_MSG(("CQNXCaptureDriver::bCapInit start \n"));

	m_pConfig = (tagQNXCaptureDriverConfig*)pConfig;
	bool bRes = bConfigCaptureParam();
	if(bRes)
	{
		m_bInit = true;
	}

	DBG_MSG(("CQNXCaptureDriver::bCapInit finished! \n"));
	return bRes;
}
TRC_SCOPE_DEF(ADAS, CQNXCaptureDriver, bCapInit2);
bool CQNXCaptureDriver::bCapInit(void** pBufPtr, int bufNum, int width, int height, int stride)
{
	TRC_SCOPE(ADAS, CQNXCaptureDriver, bCapInit2);
	DBG_MSG(("CQNXCaptureDriver::bCapInitwith Params start \n"));
	bool bRes = bConfigCaptureParam();
	if(!bRes)
	{
		return bRes;
	}

	bRes = bSetCapBuffer(pBufPtr, bufNum, width, height, stride);

	DBG_MSG(("CQNXCaptureDriver::bCapInitwith Params finished! \n"));
	return bRes;
}
TRC_SCOPE_DEF(ADAS, CQNXCaptureDriver, bConfigCaptureParam);
bool CQNXCaptureDriver::bConfigCaptureParam()
{
	TRC_SCOPE(ADAS, CQNXCaptureDriver, bConfigCaptureParam);

	bool bRes = false;
	int rc;

	DBG_MSG(("CQNXCaptureDriver::bConfigCaptureParam start \n"));
#ifdef HD_DEC_CLIENT
	if(m_stCapConfig.use_resmgr) {
		rc = hd_dec_client_init(m_pConfig->verbosity);
		if(rc) {
			DBG_ERROR(("hd_dec_client_init\n"));
			goto fail;
		}
	}
#endif

	m_CapContext = capture_create_context( 0 );
	if( !m_CapContext ) {
		DBG_ERROR(("capture_create_context failed: %s\n",strerror(errno)));
		goto fail;
	}

	int ndevices;
	// get the number of devices controlled by capture libraries.
	rc = capture_get_property_i( m_CapContext, CAPTURE_PROPERTY_NDEVICES, &ndevices );
	if (rc) {
		DBG_ERROR(("capture_get_property_i(CAPTURE_PROPERTY_NDEVICES): %s\n",strerror(errno)));
		goto fail;
	}
	DBG_MSG(("wym  ndevices %d\n", ndevices));
	DBG_MSG(("device = %d\n", m_pConfig->device));
	if (m_pConfig->device >= 0)
	{

		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_DEVICE, m_pConfig->device );
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_DEVICE),%s\n",strerror(errno)));
			goto fail;
		}
	}

//#define CAPTURE_ADV
#ifdef CAPTURE_ADV
	DBG_MSG(("source_type = %d\n", m_pConfig->source_type));
	// note: for ADVxxxx decoder, the source type should be set, prior to the source index
	if (m_pConfig->source_type >= 0 && capture_is_property( m_CapContext, CAPTURE_PROPERTY_ADV_SRC_TYPE ))
	{
		//m_pConfig->source_type
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_ADV_SRC_TYPE, m_pConfig->source_type );
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_ADV_SRC_TYPE),%s\n",strerror(errno)));
			goto fail;
		}
	}
#endif

	//CAPTURE_PROPERTY_SRC_TYPE;
	DBG_MSG(("source = %d\n", m_pConfig->source[0]));
	if (m_pConfig->source[0] >= 0)
	{
        //capture_set_property_i(context, CAPTURE_PROPERTY_SRC_INDEX, camera_index);
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_SRC_INDEX, m_pConfig->source[0] );
		if (rc) {
			DBG_ERROR(("333capture_set_property_i(CAPTURE_PROPERTY_SRC_INDEX),%d %s\n",m_pConfig->source[0], strerror(errno)));
			goto fail;
		}
	}

	/*if (m_pConfig->fid_pol >= 0) {
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_INVERT_FID_POL, m_pConfig->fid_pol );
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_INVERT_FID_POL),%s\n",strerror(errno)));
			goto fail;
		}
	}

	if (m_pConfig->vsync_pol >= 0) {
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_INVERT_VSYNC_POL, m_pConfig->vsync_pol );
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_INVERT_VSYNC_POL),%s\n",strerror(errno)));
			goto fail;
		}
	}

	if (m_pConfig->hsync_pol >= 0) {
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_INVERT_HSYNC_POL, m_pConfig->hsync_pol );
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_INVERT_HSYNC_POL),%s\n",strerror(errno)));
			goto fail;
		}
	}

	if (m_pConfig->clock_pol >= 0) {
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_INVERT_CLOCK_POL, m_pConfig->clock_pol );
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_INVERT_CLOCK_POL),%s\n",strerror(errno)));
			goto fail;
		}
	}*/

	//deinterlace settings
	/*if(capture_is_property( m_CapContext, CAPTURE_PROPERTY_DEINTERLACE_FLAGS )) {
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_DEINTERLACE_FLAGS, m_pConfig->deinterlace_flags);
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_DEINTERLACE_FLAGS),%s\n",strerror(errno)));
			goto fail;
		}
	}
	if(capture_is_property( m_CapContext, CAPTURE_PROPERTY_DEINTERLACE_MODE )) {
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_DEINTERLACE_MODE, m_pConfig->deinterlace_mode);
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_DEINTERLACE_MODE),%s\n",strerror(errno)));
			goto fail;
		}
		if(m_pConfig->deinterlace_mode == CAPTURE_DEINTERLACE_WEAVE2_MODE) {
#ifdef CAPTURE_J5
			rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_J5_EDMA_CHANNEL, m_pConfig->edma_chan);
			if (rc) {
				DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_J5_EDMA_CHANNEL),%s\n",strerror(errno)));
				goto fail;
			}
#endif
		}
		if (m_pConfig->deinterlace_mode == CAPTURE_DEINTERLACE_MOTION_ADAPTIVE_MODE) {
#ifdef CAPTURE_J5
			if(capture_is_property( m_CapContext, CAPTURE_PROPERTY_J5_ADAPTIVE_DEI_INT_MODE )) {
				rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_J5_ADAPTIVE_DEI_INT_MODE, m_pConfig->adaptive_dei_int_mode );
				if (rc) {
					DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_J5_ADAPTIVE_DEI_INTERPOLATION_MODE),%s\n",strerror(errno)));
					goto fail;
				}
			}
#endif
#ifdef CAPTURE_IMX6X
			if(capture_is_property( m_CapContext, CAPTURE_PROPERTY_IMX6X_ADAPTIVE_DEI_MOTION_MODE )) {
				rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_IMX6X_ADAPTIVE_DEI_MOTION_MODE, m_pConfig->adaptive_dei_motion_mode );
				if (rc) {
					DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_IMX6X_ADAPTIVE_DEI_MOTION_MODE),%s\n",strerror(errno)));
					goto fail;
				}
			}
#endif
		}
	}*/
#ifdef CAPTURE_IMX6X
	if (m_pConfig->sensor_clk_mode >= 0 && capture_is_property( m_CapContext, CAPTURE_PROPERTY_IMX6X_SENSOR_CLK_MODE )) {
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_IMX6X_SENSOR_CLK_MODE, m_pConfig->sensor_clk_mode );
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_IMX6X_SENSOR_CLK_MODE),%s\n",strerror(errno)));
			goto fail;
		}
	}
#endif

	DBG_MSG(("databuswidth = %d\n", m_pConfig->data_bus_width));
	if(m_pConfig->data_bus_width > 0 && capture_is_property( m_CapContext, CAPTURE_PROPERTY_DATA_BUS_WIDTH )) {
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_DATA_BUS_WIDTH, m_pConfig->data_bus_width);
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_DATA_BUS_WIDTH),%s\n",strerror(errno)));
			goto fail;
		}
	}

	//printf("m_pConfig->format = %d\n",m_pConfig->format);
	rc = capture_set_property_i(m_CapContext, CAPTURE_PROPERTY_DST_FORMAT, m_pConfig->format);
	if (rc) {
		DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_DST_FORMAT),%s\n",strerror(errno)));
		goto fail;
	}

	DBG_MSG(("sfsize = %d %d\n", m_pConfig->sfsize[0], m_pConfig->sfsize[1]));
	if(capture_is_property( m_CapContext, CAPTURE_PROPERTY_SRC_WIDTH )
			&& capture_is_property( m_CapContext, CAPTURE_PROPERTY_SRC_HEIGHT )
			&& (m_pConfig->sfsize[0] != -1) && (m_pConfig->sfsize[1] != -1)) {
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_SRC_WIDTH, m_pConfig->sfsize[0]);
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_SRC_WIDTH),%s\n",strerror(errno)));
			goto fail;
		}
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_SRC_HEIGHT, m_pConfig->sfsize[1]);
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_SRC_HEIGHT),%s\n",strerror(errno)));
			goto fail;
		}
	}
//	m_pConfig->dfsize[0] = m_pConfig->bsize[0];
//	m_pConfig->dfsize[1] = m_pConfig->bsize[1];

	DBG_MSG(("priority = %d \n", m_pConfig->capture_priority));
	if(m_pConfig->capture_priority != -1) {
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_THREAD_PRIORITY, m_pConfig->capture_priority);
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_THREAD_PRIORITY),%s\n",strerror(errno)));
			goto fail;
		}
	}

	//const char* norm = CAPTURE_NORM_AUTO;(strlen(norm) != 0)&&
	if( (capture_is_property( m_CapContext, CAPTURE_PROPERTY_NORM ))) {
		//rc = capture_set_property_p(m_CapContext, CAPTURE_PROPERTY_NORM, (void*)CAPTURE_NORM_AUTO);
        rc = capture_set_property_p(m_CapContext, CAPTURE_PROPERTY_NORM, (void*)m_pConfig->norm.c_str());
        DBG_MSG(("--->capture_set_property_i(CAPTURE_PROPERTY_NORM) = %s\n",m_pConfig->norm.c_str()));
        //printf("--->capture_set_property_i(CAPTURE_PROPERTY_NORM) = %s\n",m_pConfig->norm.c_str());
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_NORM),%s\n",strerror(errno)));
			goto fail;
		}
	}

	DBG_MSG(("interface_type = %d\n", m_pConfig->interface_type));
	if(m_pConfig->interface_type != -1 && capture_is_property( m_CapContext, CAPTURE_PROPERTY_INTERFACE_TYPE )) {
		rc = capture_set_property_i(m_CapContext, CAPTURE_PROPERTY_INTERFACE_TYPE, m_pConfig->interface_type);
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_INTERFACE_TYPE),%s\n",strerror(errno)));
			goto fail;
		}
	}

	DBG_MSG(("nlanes = %d\n", m_pConfig->nlanes));
	if(m_pConfig->nlanes != -1 && capture_is_property( m_CapContext, CAPTURE_PROPERTY_CSI2_NUM_DATA_LANES )) {
		rc = capture_set_property_i(m_CapContext, CAPTURE_PROPERTY_CSI2_NUM_DATA_LANES, m_pConfig->nlanes);
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_CSI2_NUM_DATA_LANES),%s\n",strerror(errno)));
			goto fail;
		}
	}

	DBG_MSG(("verbosity = %d\n", m_pConfig->verbosity));
	if(m_pConfig->verbosity != -1 && capture_is_property( m_CapContext, CAPTURE_PROPERTY_VERBOSITY )) {
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_VERBOSITY, m_pConfig->verbosity);
        DBG_MSG(("--->capture_set_property_i(CAPTURE_PROPERTY_VERBOSITY) = %d\n",m_pConfig->verbosity));
        //printf("--->capture_set_property_i(CAPTURE_PROPERTY_VERBOSITY) = %d\n",m_pConfig->verbosity);
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_VERBOSITY),%s\n",strerror(errno)));
			goto fail;
		}
	}

#ifdef CAPTURE_J5
	if (m_pConfig->sync_type >= 0) {
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_J5_SYNC_TYPE, m_pConfig->sync_type );
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_J5_SYNC_TYPE),%s\n",strerror(errno)));
			goto fail;
		}
	}

	if (m_pConfig->actvid_hsync >= 0) {
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_J5_USE_ACTVID_HSYNC, m_pConfig->actvid_hsync );
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_J5_USE_ACTVID_HSYNC),%s\n",strerror(errno)));
			goto fail;
		}
	}
#endif
#ifdef CAPTURE_OMAP4_5
	if(capture_is_property( m_CapContext, CAPTURE_PROPERTY_OMAP_DDR_CLOCK_MHZ )) {
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_OMAP_DDR_CLOCK_MHZ, m_pConfig->ddr_clk);
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_OMAP_DDR_CLOCK_MHZ),%s\n",strerror(errno)));
			goto fail;
		}
	}
#endif

	DBG_MSG(("CQNXCaptureDriver::bConfigCaptureParam finished! \n"));
	bRes = true;
	return bRes;
fail:
	if(m_CapContext != NULL) {
		capture_destroy_context( m_CapContext);
	}
#ifdef HD_DEC_CLIENT
	if(m_pConfig->use_resmgr) {
		hd_dec_client_fini();
	}
#endif

//	free(frame_timestamp);
//	free(frame_flags);
//
//#ifdef CAPTURE_NEED_SEQNO
//	free(frame_seqno);
//#endif

	return bRes;
}

TRC_SCOPE_DEF(CQNXCaptureDriver, CQNXCaptureDriver, bCapSetBuffer);
bool CQNXCaptureDriver::bSetCapBuffer(void** pBufPtr, int bufNum, int width, int height, int stride)
{
	TRC_SCOPE(CQNXCaptureDriver, CQNXCaptureDriver, bCapSetBuffer);
	bool bRes = false;
	if(NULL == m_CapContext)
	{
		DBG_ERROR(("m_CapContext == NULL, cannot set buffer!\n"));
		return bRes;
	}
	m_iBufferNum = bufNum;

	DBG_MSG((" bufNum=%d w = %d h = %d stride=%d\n", bufNum,width,height,stride));
	int rc;
    //last buf reversed for screen save with special color
	rc = capture_set_property_i(m_CapContext, CAPTURE_PROPERTY_FRAME_NBUFFERS, bufNum-1);
	if (rc) {
		DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_FRAME_NBUFFERS),%s\n",strerror(errno)));
		return bRes;
	}

	DBG_MSG(("buffer = %d\n", pBufPtr));
	rc = capture_set_property_p(m_CapContext, CAPTURE_PROPERTY_FRAME_BUFFERS, pBufPtr );
	if (rc) {
		DBG_ERROR(("capture_set_property_p(CAPTURE_PROPERTY_FRAME_BUFFERS),%s\n",strerror(errno)));
		return bRes;
	}
	if(capture_is_property( m_CapContext, CAPTURE_PROPERTY_DST_STRIDE )) {
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_DST_STRIDE, stride);
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_DST_STRIDE),%s\n",strerror(errno)));
			return bRes;
		}
	}

	m_pConfig->dfsize[0] = width;
	m_pConfig->dfsize[1] = height;

	if(capture_is_property( m_CapContext, CAPTURE_PROPERTY_CROP_WIDTH )
			&& capture_is_property( m_CapContext, CAPTURE_PROPERTY_CROP_HEIGHT )
			&& capture_is_property( m_CapContext, CAPTURE_PROPERTY_CROP_X )
			&& capture_is_property( m_CapContext, CAPTURE_PROPERTY_CROP_Y )) {
			
        int iDebugCSizeX=CCommandLineParser::getInstance()->getItemInt("-iCSizeX");
        int iDebugCSizeY=CCommandLineParser::getInstance()->getItemInt("-iCSizeY");
        m_pConfig->csize[0] = (0==iDebugCSizeX)?m_pConfig->csize[0]:iDebugCSizeX;
        m_pConfig->csize[1] = (0==iDebugCSizeY)?m_pConfig->csize[1]:iDebugCSizeY;     
        
		if(m_pConfig->csize[0] != -1 && m_pConfig->csize[1] != -1) {
			DBG_MSG(("CROP with = %d height =%d\n", m_pConfig->csize[0], m_pConfig->csize[1]));
			//printf("CROP with = %d height =%d\n", m_pConfig->csize[0], m_pConfig->csize[1]);
			rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_CROP_WIDTH, m_pConfig->csize[0]);
			if (rc) {
				DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_CROP_WIDTH),%s\n",strerror(errno)));
				goto fail;
			}
			rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_CROP_HEIGHT, m_pConfig->csize[1]);
			if (rc) {
				DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_CROP_HEIGHT,%s\n",strerror(errno)));
				goto fail;
			}
			// the scaling is not required on the capture side
			m_pConfig->dfsize[0] = m_pConfig->csize[0];
			m_pConfig->dfsize[1] = m_pConfig->csize[1];
		}
		//if(m_pConfig->cpos[0] != 0 || m_pConfig->cpos[1] != 0)
        int iDebugCopX=CCommandLineParser::getInstance()->getItemInt("-iCopx");
        int iDebugCopY=CCommandLineParser::getInstance()->getItemInt("-iCopy");
        m_pConfig->cpos[0] = (0==iDebugCopX)?m_pConfig->cpos[0]:iDebugCopX;
        m_pConfig->cpos[1] = (0==iDebugCopY)?m_pConfig->cpos[1]:iDebugCopY;
		{
			DBG_MSG(("CROP x = %d y =%d\n", m_pConfig->cpos[0], m_pConfig->cpos[1]));
		    //printf("CROP x = %d y =%d\n", m_pConfig->cpos[0], m_pConfig->cpos[1]);
			rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_CROP_X, m_pConfig->cpos[0]);
			if (rc) {
				DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_CROP_X),%s\n",strerror(errno)));
				goto fail;
			}
			rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_CROP_Y, m_pConfig->cpos[1]);
			if (rc) {
				DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_CROP_Y),%s\n",strerror(errno)));
				goto fail;
			}
		}
	}


	if(capture_is_property( m_CapContext, CAPTURE_PROPERTY_DST_WIDTH )
			&& capture_is_property( m_CapContext, CAPTURE_PROPERTY_DST_HEIGHT )) {
		//printf("m_pConfig->dfsize=[%d, %d]\n",m_pConfig->dfsize[0],m_pConfig->dfsize[1]);
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_DST_WIDTH, m_pConfig->dfsize[0]);
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_DST_WIDTH),%s\n",strerror(errno)));
			return bRes;
		}
		rc = capture_set_property_i( m_CapContext, CAPTURE_PROPERTY_DST_HEIGHT, m_pConfig->dfsize[1]);
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_DST_HEIGHT),%s\n",strerror(errno)));
			return bRes;
		}
	}

	if((frame_timestamp = (uint64_t*)calloc(m_iBufferNum, sizeof(uint64_t))) == NULL
			|| (frame_flags = (uint32_t*)calloc(m_iBufferNum, sizeof(uint32_t))) == NULL) {
		DBG_ERROR(("calloc frame_timestamp||frame_flags,%s\n",strerror(errno)));
		goto fail;
	}
#ifdef CAPTURE_NEED_SEQNO
	if((frame_seqno = (uint32_t*)calloc(m_iBufferNum, sizeof(uint32_t))) == NULL) {
		DBG_ERROR(("calloc frame_seqno,%s\n",strerror(errno)));
		goto fail;
	}
#endif

	DBG_MSG((" INIT 5\n"));
	// tell the capture driver to use this array and update it when frames are captured.
	//capture_set_property_p( m_CapContext, CAPTURE_PROPERTY_FRAME_TIMESTAMP, frame_timestamp );
#ifdef CAPTURE_NEED_SEQNO
	//capture_set_property_p( m_CapContext, CAPTURE_PROPERTY_FRAME_SEQNO, frame_seqno );
#endif
	if(capture_is_property( m_CapContext, CAPTURE_PROPERTY_FRAME_FLAGS )) {
		rc = capture_set_property_p( m_CapContext, CAPTURE_PROPERTY_FRAME_FLAGS, frame_flags );
		if (rc) {
			DBG_ERROR(("capture_set_property_i(CAPTURE_PROPERTY_FRAME_FLAGS),%s\n",strerror(errno)));
			goto fail;
		}
	}

	// tell the driver to start capturing (when capture_update() is called).
	capture_set_property_i( m_CapContext, CAPTURE_ENABLE, 1 );
#ifdef HD_DEC_CLIENT
	if(m_pConfig->use_resmgr) {
		rc = hd_dec_client_update((m_pConfig->device - ndevices), m_pConfig->source, m_pConfig->nlanes, m_pConfig->verbosity);
		if(rc) {
			DBG_ERROR(("hd_dec_client_update,%s\n",strerror(errno)));
			goto fail;
		}
	}
#endif
	// move to timer to make it non block
	// commit changes to the H/W -- and start de-interlacing...
	//if (capture_update( m_CapContext, 0 ) == -1) {
	//	DBG_ERROR(("capture_update failed\n"));
	//}

	return true;

fail:
	if(frame_timestamp)
	{
		free(frame_timestamp);
		frame_timestamp = NULL;
	}

	if(frame_flags)
	{
		free(frame_flags);
		frame_flags = NULL;
	}


#ifdef CAPTURE_NEED_SEQNO
	if(frame_seqno)
	{
		free(frame_seqno);
		frame_seqno = NULL;
	}
#endif

	return false;
}
CTimer m_CapEnableTimer;
void CQNXCaptureDriver::onCapEnableTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus)
{
    m_CapEnableTimer.stop();

	capture_set_property_i( m_CapContext, CAPTURE_ENABLE, 1 );
   // capture_set_property_i(m_CapContext, CAPTURE_PROPERTY_SRC_INDEX, 2);
	// commit changes to the H/W -- and start capturing...
	//clock_gettime(CLOCK_MONOTONIC, &TimeStampStartUp);    
    //fprintf(stderr, "**bCapEnable 0 at %ld MS\n",(TimeStampStartUp.tv_sec)*1000 + ((TimeStampStartUp.tv_nsec)/(1000000L)));

	if(capture_update( m_CapContext, 0 ) == -1) {

		return ;
	}
    //clock_gettime(CLOCK_MONOTONIC, &TimeStampStartUp);    
    //fprintf(stderr, "**bCapEnable 1 at %ld MS\n",(TimeStampStartUp.tv_sec)*1000 + ((TimeStampStartUp.tv_nsec)/(1000000L)));

    
    //remove for outof sync issue, this delay has to be taken care in timer
    //usleep(200000);
    //DBG_MSG(("wait bCapEnable done for 200ms ver1 \n"));
   	m_bCapActiveReady = TRUE;
}
TRC_SCOPE_DEF(CQNXCaptureDriver, CQNXCaptureDriver, bCapEnable);
//use a timer to run without block

bool CQNXCaptureDriver::bCapEnable()
{
	TRC_SCOPE(CQNXCaptureDriver, CQNXCaptureDriver, bCapEnable);
	if(!m_bInit)
		return false;
    m_CapEnableTimer.setDelay(10);
    m_CapEnableTimer.setRepeatCount(1);//0 is always loop
    m_CapEnableTimer.setCallBack(makeFunctor(this, &CQNXCaptureDriver::onCapEnableTimer), NULL);
    m_CapEnableTimer.start();
    //todo --munually add delay to avoid filcker--for non block in app side now??
   
    m_bCapEnabled = TRUE;
	return true;
}

TRC_SCOPE_DEF(CQNXCaptureDriver, CQNXCaptureDriver, bCapDisable);
bool CQNXCaptureDriver::bCapDisable()
{
	TRC_SCOPE(CQNXCaptureDriver, CQNXCaptureDriver, bCapDisable);
	if(!m_bInit)
		return false;
    m_bCapEnabled = FALSE;
    m_bCapActiveReady = FALSE;
	DBG_MSG(("bCapDisable\n"));
	capture_set_property_i( m_CapContext, CAPTURE_ENABLE, 0 );
	// commit changes to the H/W -- and start capturing...
	if(capture_update( m_CapContext, 0 ) == -1) {
		DBG_ERROR(("capture_update failed,%s\n",strerror(errno)));
		return false;
	}
	return true;
}

TRC_SCOPE_DEF(CQNXCaptureDriver, CQNXCaptureDriver, bCapUpdate);
bool CQNXCaptureDriver::bCapUpdate()
{
	TRC_SCOPE(CQNXCaptureDriver, CQNXCaptureDriver, bCapUpdate);
	if(!m_bInit)
		return false;

	//DBG_MSG(("bCapUpdate\n"));
	int buf_idx = capture_get_frame(m_CapContext, 1000000, 0 );
	if(buf_idx == -1) {
		DBG_ERROR(("capture_get_frame failed(%s)\n", strerror(errno)));
		return false;
	}
	m_iBufIndex = buf_idx;

	if(capture_is_property( m_CapContext, CAPTURE_PROPERTY_FRAME_FLAGS )) {
		if((frame_flags[buf_idx] & CAPTURE_FRAME_FLAG_INTERLACED) &&
				(m_pConfig->deinterlace_mode == CAPTURE_DEINTERLACE_NONE_MODE)) {
					m_iInterlaceField = (frame_flags[buf_idx] & CAPTURE_FRAME_FLAG_FIELD_BOTTOM)?
					SCREEN_INTERLACED_BOTTOM_FIELD:
					SCREEN_INTERLACED_TOP_FIELD;
		}
	}

	// Make the buffer identified by the pre_buf_idx as available for capturing.
	if(m_iPrevBufIndex != -1) {
		capture_release_frame( m_CapContext, m_iPrevBufIndex );
	}
	m_iPrevBufIndex = m_iBufIndex;

	return true;
}
TRC_SCOPE_DEF(ADAS, CQNXCaptureDriver, bCapUpdate);
bool CQNXCaptureDriver::bCapUpdate(int& bufIndex, int& interlaceField)
{
	if(!m_bInit)
		return false;

	//DBG_MSG(("bCapUpdate\n"));
	int buf_idx = capture_get_frame(m_CapContext, CAPTURE_TIMEOUT_INFINITE, 0 );
	if(buf_idx == -1) {
		TRC_SCOPE(ADAS, CQNXCaptureDriver, bCapUpdate);
		DBG_ERROR(("capture_get_frame failed(%s)\n", strerror(errno)));
		bufIndex = BUFFER_INDEX_VALUE_INVALID;
		interlaceField = INTERLACE_FIELD_VALUE_INVALID;
		return false;
	}
	bufIndex = buf_idx;
	m_iBufIndex = buf_idx;

	interlaceField = INTERLACE_FIELD_VALUE_INVALID;
	if(capture_is_property( m_CapContext, CAPTURE_PROPERTY_FRAME_FLAGS )) {
		if((frame_flags[buf_idx] & CAPTURE_FRAME_FLAG_INTERLACED) &&
				(m_pConfig->deinterlace_mode == CAPTURE_DEINTERLACE_NONE_MODE)) {
					interlaceField = (frame_flags[buf_idx] & CAPTURE_FRAME_FLAG_FIELD_BOTTOM)?
					SCREEN_INTERLACED_BOTTOM_FIELD:
					SCREEN_INTERLACED_TOP_FIELD;
		}
	}
	m_iInterlaceField = interlaceField;

	// Make the buffer identified by the pre_buf_idx as available for capturing.
	if(m_iPrevBufIndex != -1) {
		capture_release_frame( m_CapContext, m_iPrevBufIndex );
	}
	m_iPrevBufIndex = m_iBufIndex;

	return true;
}
TRC_SCOPE_DEF(ADAS, CQNXCaptureDriver, setSourceIndex);
void CQNXCaptureDriver::setSourceIndex(Int32 idx)
{
	//Int32 idx = Int32(pData);
	if( idx < m_pConfig->uiSrcNum && idx >= 0 && m_curSourceIdx != idx )
	{
		//bCapDisable();
		TRC_SCOPE(ADAS, CQNXCaptureDriver, setSourceIndex);
		DBG_MSG(("CQNXCaptureDriver::setSourceIndex ---ver2 %d\n", m_pConfig->source[idx]));
        capture_set_property_i(m_CapContext, CAPTURE_PROPERTY_SRC_INDEX, m_pConfig->source[idx]);
        if(capture_update( m_CapContext, 0 ) == -1) {
		DBG_ERROR(("capture_update failed,%s\n",strerror(errno)));}
	}
    if(!m_bCapEnabled) bCapEnable();
	m_curSourceIdx = idx;

}
TRC_SCOPE_DEF(ADAS, CQNXCaptureDriver, checkVSYNC);
void CQNXCaptureDriver::checkVSYNC(BOOLEAN bFormatChk)
{
	/**/
#if 0	
    if(capture_is_property(m_CapContext, CAPTURE_PROPERTY_CURRENT_NORM) && bFormatChk)
	{
		char *cur_norm = NULL;
		capture_get_property_p(m_CapContext, CAPTURE_PROPERTY_CURRENT_NORM, (void **)&cur_norm);

		if(NULL == cur_norm)
		{
			m_eSignalState = eSignalState_Invalid;

		}
		else if(0 == strcmp(cur_norm, CAPTURE_NORM_NONE))
			m_eSignalState = eSignalState_Invalid;
		else if(0 == strcmp(cur_norm, CAPTURE_NORM_UNKNOWN))
			m_eSignalState = eSignalState_Valid;
		else
		{
			m_eSignalState = eSignalState_Valid;
		}
        TRC_SCOPE(ADAS, CQNXCaptureDriver, checkVSYNC);
		DBG_MSG(("UPDATE cur_norm = %s vsync= %d \n",((cur_norm == NULL)? "": cur_norm) ,m_eSignalState));
		//printf("UPDATE cur_norm = %s vsync= %d \n",((cur_norm == NULL)? "": cur_norm) ,m_eSignalState);
	}
#endif
	if(capture_is_property(m_CapContext, CAPTURE_PROPERTY_ADV_LOCK_STATUS)&&m_bCapActiveReady)
	{
		Int32 lockStatus=0;
		capture_get_property_i(m_CapContext, CAPTURE_PROPERTY_ADV_LOCK_STATUS, &lockStatus);
		//rvs_ctx->prevVideoSyncInfo = rvs_ctx->videoSyncInfo;
		//rvs_ctx->videoSyncInfo = lockStatus ? eRVS_NTSC_SYNC_VALID : eRVS_NTSC_SYNC_INVALID;
		m_eSignalState = ( lockStatus ? eSignalState_Valid : eSignalState_Invalid);
		//if(-1 == MsgSendPulse(rvs_ctx->coid, priority, VSYNC_PULSE_CODE, 0))
		//	perror("Msg Send Error in Video display Thread ");
		//DBG_MSG(("UPDATE lockStatus = %d vsync= %d \n", lockStatus ,m_eSignalState));
	}

}
