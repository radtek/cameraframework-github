#include "CaptureDriverConfig.h"

#ifdef PLATFORM_QNX
#include <screen/screen.h>
#include <vcapture/capture.h>
#include "foundation.h"

tagQNXCaptureDriverConfig::tagQNXCaptureDriverConfig()
{
	device = 0;
	memset(source,0,sizeof(source));
	uiSrcNum = 0;
	fid_pol = -1;
	vsync_pol = -1;
	hsync_pol = -1;
	clock_pol = -1;
	sfsize[0] = -1;
	sfsize[1] = -1;
	dfsize[0] = -1;
	dfsize[1] = -1;
	ssize[0] = -1;
	ssize[1] = -1;
	spos[0] = 0;
	spos[1] = 0;
	csize[0] = -1;
	csize[1] = -1;
	cpos[0] = 0;
	cpos[1] = 0;
	format = SCREEN_FORMAT_UYVY;
	pipeline = -1;
	interlaced = SCREEN_INTERLACED_NONE;
	deinterlace_mode = CAPTURE_DEINTERLACE_NONE_MODE;
	deinterlace_flags = 0;
	capture_priority =-1;
	verbosity = 0;
	data_bus_width = 0;
	norm = CAPTURE_NORM_AUTO;
	interface_type = -1;
	mem_fill = -1;
	nlanes = -1;
	use_resmgr = false;
	rdonly_cnt = 0;
	nfields_in_buf = 0;

#ifdef CAPTURE_J5
	sync_type = -1;
	actvid_hsync = -1;
	edma_chan = -1;
	adaptive_dei_int_mode = J5_ADAPTIVE_DEI_INT_MODE_3;
#endif
#ifdef CAPTURE_OMAP4_5
	ddr_clk = -1;
#endif
#ifdef CAPTURE_ADV
	source_type = -1;
#endif
#ifdef CAPTURE_IMX6X
	sensor_clk_mode = -1;
	adaptive_dei_motion_mode = VDI_MOTION_MODE_MED;
#endif
}
#endif
