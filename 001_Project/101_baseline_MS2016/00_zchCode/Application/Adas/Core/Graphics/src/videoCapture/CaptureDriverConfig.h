#ifndef _CAPTUREDRIVER_CONFIG_H
#define _CAPTUREDRIVER_CONFIG_H

#define MAXSOURCECOUNT	4
#include "foundation.h"


struct tagQNXCaptureDriverConfig
{
	int 			device;
	int 			source[MAXSOURCECOUNT];
	unsigned int	uiSrcNum;
	int 			fid_pol;
	int 			vsync_pol;
	int 			hsync_pol;
	int 			clock_pol;
	int 			sfsize[2]; //source field size
	int 			dfsize[2];
	int				ssize[2]; //size of the source viewport
	int				spos[2]; //position of the source viewport
	int 			bsize[2];
	int 			csize[2];
	int 			cpos[2];
	int 			format;
	int 			pipeline;
	int 			interlaced;
	int 			deinterlace_mode ;
	int 			deinterlace_flags ;
	int 			capture_priority;
	int 			verbosity;
	int 			data_bus_width;
	string 			norm;
	int 			interface_type;
	int 			mem_fill;
	int 			nlanes;
	bool 			use_resmgr;
	int				rdonly_cnt; //number of read-only buffers
	int				nfields_in_buf; //number of fields (0, 1, 2) in a buffer

#ifdef CAPTURE_J5
	int 	sync_type;
	int 	actvid_hsync;
	int 	edma_chan;
	int 	adaptive_dei_int_mode;
#endif
#ifdef CAPTURE_OMAP4_5
	int 	ddr_clk;
#endif
#ifdef CAPTURE_ADV
	int 	source_type;
#endif
#ifdef CAPTURE_IMX6X
	int 	sensor_clk_mode;
	int 	adaptive_dei_motion_mode;
#endif

	tagQNXCaptureDriverConfig();
};

#endif
