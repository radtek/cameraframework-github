/*
 * adv7182.c
 *
 *  Created on: 2013-5-22
 *      Author: Whuang
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
//#include <hw/i2c.h>
#include <hw/inout.h>
#include <sys/mman.h>
#include <sys/neutrino.h>
#include "adv7182.h"
#include "main.h"

#include <atomic.h>
#include <inttypes.h>
#include <sys/rsrcdbmgr.h>
#include <sys/rsrcdbmsg.h>
#include <sys/slog.h>
#include <i2c-dev.h>
#include "osal.h"
#define ADV7180_I2C_BASE 0x21



/*
 *  Definitions for control registers for ADV7180
 */
typedef struct adv7180_registers {
#define INPUT_CTL       		0x00
	struct input_ctl {
		u8  insel      :4, // [3:0] default:00, try {00, 03, 04}
			vid_sel    :4; // [7:4]
	} input_ctl;

	u8           input_ctlx[2];

#define OUTPUT_CTL       		0x03
	struct output_ctl {
		u8  reserved1   :2, // [1:0]
			of_sel      :4, // [5:2]
			reserved2   :2; // [7:6]
	} output_ctl;

	u8           output_ctlx[4];

#define CON						0x08
	u8           con;			// Contrast Adjust
	u8           conx;

#define BRI						0x0A
	u8           bri;

#define	HUE						0x0B
	u8           hue;			// hue adjustment {0x00, 0x7F:-90, 0x80:+90}

#define DEF_Y_CTL       		0x0C
	struct def_y_ctl {
		u8  def_val_en     :1,  // [0]       0
			def_val_auto_en:1,	// [1]       1:free-mode, blue screen
			def_y          :6;  // [7:2]    13
	} def_y_ctl;

#define DEF_C_CTL       		0x0D
	u8           def_c_ctl;		// 0x7C

#define ADI_CONTROL1            0x0E
	u8           adi_control1;
	u8           power_mgmt;

#define STATUS_1				0x10
	struct status_1 {
		u8  reserved1     :4, // [3:0]
#define NTSM           0
#define NTSC           1
#define PAL_M          2
#define PAL_60         3
#define PAL_B_G_H_I_D  4
#define PAL_PAL_COMB_N 6
			ad_result     :3, // [6:4]
			reserved2     :1; // [7]
	} status_1;

	u8           reserved1;

#define STATUS_2				0x12
	u8           status_2;

#define STATUS_3				0x13
	struct status_3 {
		u8  reserved1     :4, // [3:0]
			free_run_act  :1, // [4] ADV7180 outputs a blue screen (see the DEF_VAL_EN, Default Value Enable, Address 0x0C[0] section)
			std_fld_len   :1, // [5]
			interlaced    :1, // [6] Interlaced video detected
			reserved2     :1;
	} status_3;

	/* [0x14 - 0x16] */
	u8           reserved2[3];

	/* 0x17 */
	u8           shaping_filter_control1;

	/* [0x18 - 0x30] */
	u8           reserved[25];

#define VS_FIELD_CTL       		0x31
	u8           vs_field_ctl;	// 2:default

	/* [0x32 - 0x3C] */
	u8           reserved5[11];

#define MANUAL_WINDOW_CONTROL   0x3d
	u8           manual_window_control; // 2:default
	u8           x3e;                   // 0x6a
	u8           x3f;                   // 0xa0

	/* [0x40 - 0x4C] */
	u8           reserved3[13];

#define CTI_DNR_CONTROL1        0x4D
	u8           cti_dnr_control1;      // 0xe0 // e3:alpha, e1, e2:smooth

	/* [0x4E - 0x54] */
	u8           reserved4[7];

	u8           x55; // 0x81

	/* [0x56 - 0xFA] */
	u8           reserved10[165];

	/* 0xFB */
	u8           peaking_control;

}  __attribute__ ((aligned(1))) adv7180_registers_t;



#define INSEL         		(0xF<<0) /* Input Control Register */
#define OF_SEL         		(0xF<<2) /* Output Control Register */
#define NEWAVMODE           (0x1<<4) /* VS/Field Control Register */
#define DEF_C         		(0xFF<<0)
#define IN_LOCK				(0x1<<0)

#if 0
typedef struct _adv7180
{
	char               *name;
	s32                 fd;
	s32                 i2c_addr;
	adv7180_registers_t regs;

	struct   registers {
		u8 	addr;    /* 8-bit address */
		u8 	val;	 /* 8-bit value */
		u8  mask;	 /* 8-bit mask */
	} registers[72];  //[16] for adv7180

} adv7180_t;
static adv7180_t  adv7180;
#endif

typedef struct _adv7180
{
	char               *name;
	s32                 i2c_addr;

	struct   registers {
		u8 	addr;    /* 8-bit address */
		u8 	val;	 /* 8-bit value */
		u8  mask;	 /* 8-bit mask */
	} registers[72];  //[16] for adv7180

	s32                 fd;
	adv7180_registers_t regs;
} adv7180_t;

static adv7180_t  adv7180 = {
		(char*)(I2C_DEV_NAME),
		ADV7180_I2C_BASE,
		 {
				#if 1 //adi recommended configuration (adv7182)
				{0x0f,0x00,0xff},
				{0x00,0x0e,0x1f},
				{0x03,0x0c,0xff},
				{0x04,0x17,0xff},
				{0x13,0x00,0xff},
				{0x17,0x41,0xff},
				{0x1d,0x40,0xff},
				{0x52,0xc0,0xff},
				{0x5f,0xa8,0xff},
				{0x5a,0x90,0xff},
				{0x60,0xb0,0xff},
				{0x0e,0x80,0xff},
				{0xb6,0x08,0xff},
				{0xc0,0xa0,0xff},
				{0x0e,0x00,0xff},
				//{0x27,0xd8,0xff},		//U V swap
				#endif
		},
};


#if 0
static adv7180_t  adv7180 = {
//static struct _adv7180 adv7180 = {
	.name     = "/dev/i2c3",
	.i2c_addr = ADV7180_I2C_BASE,
	.registers = {
		#if 0 //for older adv7180
		//{INPUT_CTL,     0x04, INSEL}, // TODO: check {00-(RSE - VES1), 03-(RDC - VES2), 04-(Camera)}
		{INPUT_CTL,     0x14, 0x0F},
		{OUTPUT_CTL,    0x0C, OF_SEL},// TODO: check
		{CON,           0x80, 0xFF},
		{HUE,           0x00, 0xFF},
		{DEF_Y_CTL,     0x36, 0xFF}, // Y=0x34, auto free-run
		{DEF_C_CTL,     0x7C, 0xFF}, // TODO: check blue, Cr=0x70, Cb=0xC0
		{0x17,          0x41, 0xFF},
		{VS_FIELD_CTL,  0x02, 0xFF}, // TODO: check
		{0x3d,          0xa2, 0xFF},
		{0x3e,          0x6a, 0xFF},
		{0x3f,          0xa0, 0xFF},
		{0x4D,          0xe0, 0xFF},
		{0xfb,          0x68, 0xFF},
		{0x55,          0x81, 0xFF},
		{0x0e,          0x00, 0xFF},
		{0x0a,          0x00, 0xFF},
		#endif

		#if 0 //adi recommended configuration (adv7281)
		{0x00,0x0e,0x1f},
		{0x03,0x0c,0xff},
		{0x04,0x17,0xff},
		{0x0f,0x00,0xff},
		{0x13,0x00,0xff},
		{0x17,0x41,0xff},
		{0x1d,0x40,0xff},
		{0x52,0xc0,0xff},
		{0x5f,0xa8,0xff},
		{0x5a,0x90,0xff},
		{0x60,0xb0,0xff},
		{0x0e,0x80,0xff},
		{0xb6,0x08,0xff},
		{0xc0,0xa0,0xff},
		{0x0e,0x00,0xff},
		{0x5d,0x1c,0xff},
		{0x5e,0x1c,0xff},
		#endif

		#if 1 //adi recommended configuration (adv7182)
		{0x0f,0x00,0xff},
		{0x00,0x0e,0x1f},
		{0x03,0x0c,0xff},
		{0x04,0x17,0xff},
		{0x13,0x00,0xff},
		{0x17,0x41,0xff},
		{0x1d,0x40,0xff},
		{0x52,0xc0,0xff},
		{0x5f,0xa8,0xff},
		{0x5a,0x90,0xff},
		{0x60,0xb0,0xff},
		{0x0e,0x80,0xff},
		{0xb6,0x08,0xff},
		{0xc0,0xa0,0xff},
		{0x0e,0x00,0xff},
		//{0x27,0xd8,0xff},		//U V swap
		#endif
	},
};
#endif


typedef struct adv7180_send {
	i2c_send_t i2c_send;
	uint8_t    buf[2];
} adv7180_send_t;

typedef struct adv7180_send_recv {
	i2c_sendrecv_t i2c_sendrecv;
	uint8_t        buf[2];
} adv7180_send_recv_t;


static inline int adv7180_write(uint8_t    register_address,
								uint8_t    val,
								uint8_t    bitmask)
{
	//printf("\n");
#if 0
	adv7180_send_recv_t  rd = {
		.i2c_sendrecv = {
			.slave = {
				.addr = adv7180.i2c_addr,
				.fmt  = I2C_ADDRFMT_7BIT,
			},
			.send_len = 1,
			.recv_len = 1,
			.stop     = 0,
		},
		.buf[0]       = register_address,
	};
#else
	adv7180_send_recv_t  rd;
	rd.i2c_sendrecv.slave.addr = adv7180.i2c_addr;
	rd.i2c_sendrecv.slave.fmt = I2C_ADDRFMT_7BIT;
	rd.i2c_sendrecv.send_len = 1;
	rd.i2c_sendrecv.recv_len = 1;
	rd.i2c_sendrecv.stop = 0;
	rd.buf[0] = register_address;
#endif

    // lock the driver
    if( EOK != devctl (adv7180.fd, DCMD_I2C_LOCK, NULL, 0, NULL) )
    {
        printf("\nERROR I2C MASTER_LOCK");
        return -1;
    }


	if(devctl(adv7180.fd, DCMD_I2C_SENDRECV,
			  &rd, sizeof(rd), NULL)) {
		printf("Failed to read codec reg values: %s\n", strerror(errno));
		return -1;
	}


	/*
	 * Now that the register value is read,
	 * Set and clear the required bits only
	 */
#if 0
	adv7180_send_t       wd = {
		.i2c_send = {
			.slave = {
				.addr = adv7180.i2c_addr,
				.fmt  = I2C_ADDRFMT_7BIT,
			},
			.len      = 2,
			.stop     = 1,
		},
		.buf[0]       = register_address,
	};
#else
	adv7180_send_t       wd;
	wd.i2c_send.slave.addr = adv7180.i2c_addr;
	wd.i2c_send.slave.fmt = I2C_ADDRFMT_7BIT;
	wd.i2c_send.len = 2;
	wd.i2c_send.stop = 1;
	wd.buf[0] = register_address;
#endif

	wd.buf[1]         = (rd.buf[0] & ~bitmask) | (val & bitmask);
	if(devctl(adv7180.fd, DCMD_I2C_SEND,
			  &wd, sizeof (wd), NULL)) {
		printf("Failed to write to codec: %s\n", strerror(errno));
		return -1;
	}

    // unlock the driver
    if( EOK != devctl (adv7180.fd, DCMD_I2C_UNLOCK, NULL, 0, NULL) )
    {
        //printf("\nERROR I2C MASTER_LOCK");
        return -1;
    }

	return 0;
}

static inline uint8_t adv7180_read(void *r)
{
	uint8_t  register_address = ((u8*)r) - (u8*)&adv7180.regs;

	//printf("register_address = %x \n", (int)register_address);

#if 0
	adv7180_send_recv_t d = {
		.i2c_sendrecv = {
			.slave = {
				.addr = adv7180.i2c_addr,
				.fmt  = I2C_ADDRFMT_7BIT,
			},
			.send_len = 1,
			.recv_len = 1,
			.stop     = 1,
		},
		.buf[0] = register_address,
	};
#else
	adv7180_send_recv_t d;
	d.i2c_sendrecv.slave.addr = adv7180.i2c_addr;
	d.i2c_sendrecv.slave.fmt = I2C_ADDRFMT_7BIT;
	d.i2c_sendrecv.send_len = 1;
	d.i2c_sendrecv.recv_len = 1;
	d.i2c_sendrecv.stop = 1;
	d.buf[0] = register_address;
#endif

    // lock the driver
    if( EOK != devctl (adv7180.fd, DCMD_I2C_LOCK, NULL, 0, NULL) )
    {
        printf("\nERROR I2C MASTER_LOCK");
        return -1;
    }


	if(devctl(adv7180.fd, DCMD_I2C_SENDRECV,
			  &d, sizeof(d),
			  NULL)) {
		printf("Failed to write to codec: %s\n", strerror(errno));
	}

    // unlock the driver
    if( EOK != devctl (adv7180.fd, DCMD_I2C_UNLOCK, NULL, 0, NULL) )
    {
        //printf("\nERROR: I2C MASTER_LOCK");
        return -1;
    }


	*(u8*)r = d.buf[0];

	return d.buf[0];
}

s32 adv7180_enable(void)
{
	//__D("\n");
	s32         mode = 2;

	if((adv7180.fd = open(adv7180.name, O_RDWR)) < 0) {
		printf("could not open i2c device %s \n", strerror(errno));
		return -1;
	}

	u32 i;

	for(i = 0; i < ARRAY_SIZE(adv7180.registers); i++)
	{

			adv7180_write(adv7180.registers[i].addr,
						  adv7180.registers[i].val,
						  adv7180.registers[i].mask);

	}

	  // printf("set blue color\n");
	   //adv7180_write(0x0D,0xC7,0xFF);//set blue screen when RVC no signal
	//adv7180_write(0x0C,0x37,0xFF);//force free run mode
	//adv7180_write(0xF9,0x0b,0xFF);//force 480i60Hz mode
	//adv7180_write(0x14,0x15,0xFF);//force Boundary box mode
	//adv7180_write(0x27,0xd8,0xFF);//UV swap

#if 0 //for adv7180
	__D( "INPUT_CTL:    0x%x\n", adv7180_read(&adv7180.regs.input_ctl));
	__D( "OUTPUT_CTL:   0x%x\n", adv7180_read(&adv7180.regs.output_ctl));
	__D( "VS_FIELD_CTL: 0x%x\n", adv7180_read(&adv7180.regs.vs_field_ctl));
	__D( "DEF_C_CTL:    0x%x\n", adv7180_read(&adv7180.regs.def_c_ctl));
	__D( "STATUS_1:     0x%x\n", adv7180_read(&adv7180.regs.status_1));
	__D( "\n\n\n\n:::::::::::::::::::::::::::::::::::::::::::::STATUS_3:     0x%x:::::::::::::::::::::::::::::::::::::::::::::\n\n\n\n", adv7180_read(&adv7180.regs.status_3));

#endif
   if (rear_camera_selected())
   {
      // rear view camera is always NTSC
      mode = 1;
   }

   #if 0 //for adv7180
   else
   {
		//for adv7180
	 // adv7180_read((void*)&adv7180.regs.status_1);
      __D("AD_RESULT: 0x%x \n", adv7180.regs.status_1.ad_result);

      switch(adv7180.regs.status_1.ad_result) {
      case NTSM:
      case NTSC:
      default:
         mode = 1;
         break;

      case PAL_M:
      case PAL_60:
      case PAL_B_G_H_I_D:
      case PAL_PAL_COMB_N:
         mode = 0;
         break;
      }
   }
   #endif
#if 1
	close (adv7180.fd);
#endif
	return mode;
}




int update_adv7180_register (int idx, uint8_t val)
{
	int ret=0;

	adv7180.registers[idx].val = val;

#if 1
	if((adv7180.fd = open(adv7180.name, O_RDWR)) < 0)
	{
		printf("could not open i2c device %s \n", strerror(errno));
		return -1;
	}
#endif

	adv7180_write(	adv7180.registers[idx].addr,
					adv7180.registers[idx].val,
					adv7180.registers[idx].mask);

	close (adv7180.fd);


	return ret;
}



uint8_t read_adv7180_register (int idx)
{

	//printf("\n::::::::::::::::::: idx :::::::::::::::::::::: %d", idx);
#if 1
	if((adv7180.fd = open(adv7180.name, O_RDWR)) < 0)
	{
		printf("could not open i2c device %s \n", strerror(errno));
		return -1;
	}
#endif

	uint8_t  register_address = adv7180.registers[idx].addr;

	printf("register_address = %d \n", (int)register_address);

#if 0
	adv7180_send_recv_t d = {
		.i2c_sendrecv = {
			.slave = {
				.addr = adv7180.i2c_addr,
				.fmt  = I2C_ADDRFMT_7BIT,
			},
			.send_len = 1,
			.recv_len = 1,
			.stop     = 1,
		},
		.buf[0] = register_address,
	};
#else
	adv7180_send_recv_t d;
	d.i2c_sendrecv.slave.addr = adv7180.i2c_addr;
	d.i2c_sendrecv.slave.fmt = I2C_ADDRFMT_7BIT;
	d.i2c_sendrecv.send_len = 1;
	d.i2c_sendrecv.recv_len = 1;
	d.i2c_sendrecv.stop = 1;
	d.buf[0] = register_address;
#endif

    // lock the driver
    if( EOK != devctl (adv7180.fd, DCMD_I2C_LOCK, NULL, 0, NULL) )
    {
       // printf("\nERROR I2C MASTER_LOCK");
        return -1;
    }


	if(devctl(adv7180.fd, DCMD_I2C_SENDRECV,
			  &d, sizeof(d),
			  NULL)) {
		printf("Failed to write to codec: %s\n", strerror(errno));
	}

    // unlock the driver
    if( EOK != devctl (adv7180.fd, DCMD_I2C_UNLOCK, NULL, 0, NULL) )
    {
       // printf("\nERROR: I2C MASTER_LOCK");
        return -1;
    }

#if 1
	close (adv7180.fd);
#endif
	d.buf[1] = (d.buf[0] & adv7180.registers[idx].mask);

	return d.buf[0];

}


/*
 * uint8_t get_7180_status3(void)
 *
 * gets the status of the register status3 from ADV7180 device.
 * This register holds value of free run active value which is  set if there is no signal present
 * when the device receives HS\VS pulses on the selected channel, this bit is cleared.
 *
 * Used for diagnostics.
 *
 * returns register value in hex and null if the function fails
 *
 * */
uint8_t get_7180_status3(void)
{
    uint8_t i;
#if 1
	if((adv7180.fd = open(adv7180.name, O_RDWR)) < 0) {
		printf("could not open i2c device %s \n", strerror(errno));
		return NULL;
	}
#endif
	i = adv7180_read(&adv7180.regs.status_3);

#if 1
	close (adv7180.fd);
#endif
	return i;

}


//
// returns 1 if the rear camera is the selected input
//
uint8_t rear_camera_selected()
{
   if (((adv7180.registers[0].val & 0x1F)== 0x0F)||((adv7180.registers[0].val & 0x1F)== 0x0E))//((adv7180.registers[INPUT_CTL].val & 0x0F)== 0x04)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

#if 0
static int i2c_devctl(SV_Video_Capture *videoCapture, unsigned int cmd, void *pdata, unsigned int nbytes)
{
   uint64_t timeout = ULONGLONG_MAX; // Assume the longest timeout
   int err_code = EOK;  // No error code up to now
   ClockTime(CLOCK_MONOTONIC, 0, &timeout); // Get current clock value

   // Add the number of ns to the actual time
   timeout += 1000 * (uint64_t)(1000000);

   do {
      // setup kernel timer
      if ( TimerTimeout( CLOCK_MONOTONIC,
                        (TIMER_ABSTIME | _NTO_TIMEOUT_SEND | _NTO_TIMEOUT_REPLY),
                        0,
                        &timeout,
                        0) >= 0 ) {
         // try to do the devctl call
         err_code = devctl( videoCapture->adv7182_dev.i2c_fd, cmd, pdata, nbytes, 0 );
      }
   } while( err_code == EINTR);

   // check for error
   if(err_code != EOK) {
      errno = err_code;
      return -1;
   }

   return EOK;
}

int32_t adv7182_open(SV_Video_Capture *videoCapture)
{
    videoCapture->adv7182_dev.i2c_fd = open(videoCapture->adv7182_dev.i2c_name, O_RDWR);

   if (videoCapture->adv7182_dev.i2c_fd != -1) {
      i2c_driver_info_t info;

      // Get the possible bus speed and the address format
      if ( i2c_devctl(videoCapture, DCMD_I2C_DRIVER_INFO, &info, sizeof(i2c_driver_info_t)) >= 0 )
         return 0;
   }

   return -1;
}

static int adv7182_write_reg(SV_Video_Capture *videoCapture, uint8_t reg, uint8_t value)
{
	struct send {
		i2c_send_t hdr;
		unsigned char  buf[2];
	} adv7182_wr_data;
	
	/* Now that the register value is read, Set and clear the required bits only */
	adv7182_wr_data.buf[0] = reg;
	adv7182_wr_data.buf[1] = value;

	adv7182_wr_data.hdr.len = 2;
	adv7182_wr_data.hdr.slave.addr = videoCapture->adv7182_dev.i2c_addr; //slave address
	adv7182_wr_data.hdr.slave.fmt = I2C_ADDRFMT_7BIT;
	adv7182_wr_data.hdr.stop = 1;

	if ( EOK != devctl(videoCapture->adv7182_dev.i2c_fd, DCMD_I2C_SEND,
		                        &adv7182_wr_data, sizeof (adv7182_wr_data), NULL)) {
		printf ("Failed to write to adv7182: %s\n", strerror (errno));
		return -1;
	}

    return 0;
}

/**
 * Read a single register.
 */
static int adv7182_read_reg(SV_Video_Capture *videoCapture, uint8_t reg, uint8_t* value)
{
    struct send {
		i2c_send_t hdr;
		unsigned char  buf[1];
	} adv7182_wr_data;
	
	/* Now that the register value is read, Set and clear the required bits only */
	adv7182_wr_data.buf[0] = reg;
	adv7182_wr_data.hdr.len = 1;
	adv7182_wr_data.hdr.slave.addr = videoCapture->adv7182_dev.i2c_addr; //slave address
	adv7182_wr_data.hdr.slave.fmt = I2C_ADDRFMT_7BIT;
	adv7182_wr_data.hdr.stop = 1;

	if ( EOK != devctl(videoCapture->adv7182_dev.i2c_fd, DCMD_I2C_SEND,
		                        &adv7182_wr_data, sizeof (adv7182_wr_data), NULL)) {
		printf ("Failed to DCMD_I2C_SEND to codec: %s\n", strerror (errno));
		return -1;
	}
	

	struct recv {
		i2c_recv_t hdr;
		unsigned char  buf[1];
	} adv7182_rec_data;
	
	/* Now that the register value is read, Set and clear the required bits only */
	adv7182_rec_data.buf[0] = 0x00;

	adv7182_rec_data.hdr.len = 1;
	adv7182_rec_data.hdr.slave.addr = videoCapture->adv7182_dev.i2c_addr; //slave address
	adv7182_rec_data.hdr.slave.fmt = I2C_ADDRFMT_7BIT;
	adv7182_rec_data.hdr.stop = 1;

	if ( EOK != devctl(videoCapture->adv7182_dev.i2c_fd, DCMD_I2C_RECV,
		                        &adv7182_rec_data, sizeof (adv7182_rec_data), NULL)) {
		printf ("Failed to DCMD_I2C_RECV to adv7182: %s\n", strerror (errno));
		return -1;
	}
		
	if(NULL != value)
	    *value = adv7182_rec_data.buf[0];

    return 0;
}
#endif
#define MX6X_GPIO5_BASE                         0x020AC000
#define MX6X_GPIO5_REG_SIZE                 4*1024

int32_t adv7182_resetpin_init(SV_Video_Capture *videoCapture)
{
	uint32_t value;

	value = in32(videoCapture->ipu2_csi.iomuxc_base + 0x19c);
	value &= ~0x7;
	out32(videoCapture->ipu2_csi.iomuxc_base + 0x19c, value|0x5);

	videoCapture->adv7182_dev.pin_base = mmap_device_io(MX6X_GPIO5_REG_SIZE, MX6X_GPIO5_BASE);
         if (MAP_DEVICE_FAILED == videoCapture->adv7182_dev.pin_base) {
             printf("unable to map GPIO5 registers\n");
             videoCapture->adv7182_dev.pin_base = NULL;
             return -1;
        }

	out32(videoCapture->adv7182_dev.pin_base + 0x04, in32(videoCapture->adv7182_dev.pin_base + 0x04)|0x1<<5);
	//out32(videoCapture->adv7182_dev.pin_base, in32(videoCapture->adv7182_dev.pin_base) &~( 0x1<<5));
	return 0;
}

void adv7182_resetpin_high(SV_Video_Capture *videoCapture)
{
         out32(videoCapture->adv7182_dev.pin_base, in32(videoCapture->adv7182_dev.pin_base) | 0x1<<5);
}

void adv7182_resetpin_low(SV_Video_Capture *videoCapture)
{
	out32(videoCapture->adv7182_dev.pin_base, in32(videoCapture->adv7182_dev.pin_base) &~( 0x1<<5));
}



int adv7182_enable_composite_video(SV_Video_Capture *videoCapture)
{
    return update_adv7180_register(0x02, 0x0C);    //Recommeded setting in example
}

int adv7182_disable_composite_video(SV_Video_Capture *videoCapture)
{
    return update_adv7180_register(0x02, 0x4C);    //Recommeded setting in example
}

#if 0
uint16_t adv7182_get_chip_id(SV_Video_Capture *videoCapture)
{
	uint8_t id[2];
	int error=0;

	error |= adv7182_read_reg(videoCapture, adv7182_REG_DEVICE_ID_MSB, &id[0]);
	error |= adv7182_read_reg(videoCapture, adv7182_REG_DEVICE_ID_LSB, &id[1]);
	if (error)
		return 0;

	return (uint16_t)id[0]<<8 | id[1];
}

int adv7182_enable_agc(SV_Video_Capture *videoCapture)
{
    return adv7182_write_reg(videoCapture, adv7182_REG_ANALOG_CTRL, 0x01);
}

int adv7182_disable_agc(SV_Video_Capture *videoCapture)
{
    return adv7182_write_reg(videoCapture, adv7182_REG_ANALOG_CTRL, 0x00);
}

int adv7182_enable_powerdown(SV_Video_Capture *videoCapture)
{
    uint8_t value;

    adv7182_read_reg(videoCapture, adv7182_REG_OPERATION_MODE_CTRL, &value);
    value |= 0x01;
    return adv7182_write_reg(videoCapture, adv7182_REG_OPERATION_MODE_CTRL, value);
}

int adv7182_disable_powerdown(SV_Video_Capture *videoCapture)
{
	uint8_t value;

    adv7182_read_reg(videoCapture, adv7182_REG_OPERATION_MODE_CTRL, &value);
    value &= ~0x01;
    return adv7182_write_reg(videoCapture, adv7182_REG_OPERATION_MODE_CTRL, value);
}
#endif

uint8_t adv7182_get_syncstatus(SV_Video_Capture *videoCapture)
{
    uint8_t val;
#if 1
	if((adv7180.fd = open(adv7180.name, O_RDWR)) < 0) {
		printf("could not open i2c device %s \n", strerror(errno));
		return NULL;
	}
#endif
    val = adv7180_read(&adv7180.regs.status_1);
    //printf("sync status is %x\n", val);
#if 1
    close (adv7180.fd);
#endif
    return ((val&0x03)==0x01) ? 1 : 0;
}

void adv7182_set_brightness(SV_Video_Capture *videoCapture, uint8_t brightness)
{
	//printf("bri is %d\n", brightness);
	if((adv7180.fd = open(adv7180.name, O_RDWR)) < 0) {
		printf("could not open i2c device %s \n", strerror(errno));
		//return NULL;
	}
	adv7180_write(0x0A,brightness,0xFF);
	close (adv7180.fd);
}

void adv7182_set_contrast(SV_Video_Capture *videoCapture, uint8_t contrast)
{
	//printf("con is %d\n", contrast);
	if((adv7180.fd = open(adv7180.name, O_RDWR)) < 0) {
		printf("could not open i2c device %s \n", strerror(errno));
		//return NULL;
	}
	adv7180_write(0x08,contrast,0xFF);
	close (adv7180.fd);
}

uint8_t adv7182_get_cur_videostandard(SV_Video_Capture *videoCapture)
{
    uint8_t val;
#if 1
	if((adv7180.fd = open(adv7180.name, O_RDWR)) < 0) {
		printf("could not open i2c device %s \n", strerror(errno));
		return NULL;
	}
#endif
    val = adv7180_read(&adv7180.regs.status_1);
    printf("video standard is %x\n", val);
#if 1
    close (adv7180.fd);
#endif
    return ((val&adv7182_REG_VIDEOSTD_BIT_MASK) >> 4);
}

uint32_t adv7182_get_cur_pix_w(SV_Video_Capture *videoCapture)
{
    uint8_t video_std;
    uint32_t pix_w;

    video_std = adv7182_get_cur_videostandard(videoCapture);
    switch (video_std) {
        case NTSC_4_43_ITU_R_BT_601 :
        case NTSC_ITU_R_BT_601 :
        case PAL_M_ITU_R_BT_601 :
        case PAL_60_ITU_R_BT_601 :
            pix_w = NTSC_PAL_M_PIXELS_PER_LINE;
	   break;
        case SECAM_ITU_R_BT_601:
        case PAL_N_ITU_R_BT_601:
        case PAL_NC_ITU_R_BT_601:
        case SECAM_525_ITU_R_BT_601:
            pix_w = SECAM_PAL_PIXELS_PER_LINE;
	   break;
        default:
	   pix_w = NTSC_PAL_M_PIXELS_PER_LINE;
	   break;
    }

     return pix_w;
}

uint32_t adv7182_get_cur_video_standard(SV_Video_Capture *videoCapture)
{
    uint8_t video_std;

    video_std = adv7182_get_cur_videostandard(videoCapture);
    switch (video_std) {
		case NTSC_ITU_R_BT_601 :
			printf("current video is NTSC_ITU_R_BT_601\n");
	   break;
        case NTSC_4_43_ITU_R_BT_601 :
            printf("current video is NTSC_4_43_ITU_R_BT_601\n");
	   break;
        case PAL_60_ITU_R_BT_601 :
	   printf("current video is PAL_60_ITU_R_BT_601\n");
	   break;
        case PAL_M_ITU_R_BT_601 :
	   printf("current video is PAL_M_ITU_R_BT_601\n");
	   break;
        case SECAM_ITU_R_BT_601:
	   printf("current video is SECAM_ITU_R_BT_601\n");
	   break;
        case PAL_N_ITU_R_BT_601:
	   printf("current video is PAL_N_ITU_R_BT_601\n");
	   break;
        case PAL_NC_ITU_R_BT_601:
	   printf("current video is PAL_NC_ITU_R_BT_601\n");
	   break;
        case SECAM_525_ITU_R_BT_601:
	   printf("current video is SECAM_525_ITU_R_BT_601\n");
	   break;
        default:
   	   printf("current video is UNKNOWN\n");
	   break;
    }

    return video_std;
}

uint32_t adv7182_get_cur_active_pix_w(SV_Video_Capture *videoCapture)
{
    uint8_t video_std;
    uint32_t pix_w;

    video_std = adv7182_get_cur_videostandard(videoCapture);
    switch (video_std) {
        case NTSC_4_43_ITU_R_BT_601 :
        case NTSC_ITU_R_BT_601 :
        case PAL_M_ITU_R_BT_601 :
        case SECAM_ITU_R_BT_601:
        case PAL_N_ITU_R_BT_601:
        case PAL_NC_ITU_R_BT_601:
        case SECAM_525_ITU_R_BT_601:
        case PAL_60_ITU_R_BT_601 :
        default:
	   pix_w = SECAM_PAL_ACTIVE_PIXELS_PER_LINE;
	   break;
    }

     return pix_w;
}

uint32_t adv7182_get_cur_pix_h(SV_Video_Capture *videoCapture)
{
    uint8_t video_std;
    uint32_t pix_h;

    video_std = adv7182_get_cur_videostandard(videoCapture);
    switch (video_std) {
        case NTSC_4_43_ITU_R_BT_601 :
        case NTSC_ITU_R_BT_601 :
        case PAL_M_ITU_R_BT_601 :
        case PAL_60_ITU_R_BT_601 :
        case SECAM_525_ITU_R_BT_601:
            pix_h = NTSC_PAL_M_PIXELS_PER_FRAME;
	   break;
        case SECAM_ITU_R_BT_601:
        case PAL_N_ITU_R_BT_601:
        case PAL_NC_ITU_R_BT_601:
            pix_h = SECAM_PAL_PIXELS_PER_FRAME;
	   break;
        default:
	   pix_h = NTSC_PAL_M_PIXELS_PER_FRAME;
	   break;
    }

     return pix_h;
}

uint32_t adv7182_get_cur_active_pix_h(SV_Video_Capture *videoCapture)
{
    uint8_t video_std;
    uint32_t pix_h;

    video_std = adv7182_get_cur_videostandard(videoCapture);
    switch (video_std) {
        case NTSC_4_43_ITU_R_BT_601 :
        case NTSC_ITU_R_BT_601 :
        case PAL_M_ITU_R_BT_601 :
        case PAL_60_ITU_R_BT_601 :
            pix_h = NTSC_PAL_M_ACTIVE_PIXELS_PER_FRAME;
	   break;
        case SECAM_ITU_R_BT_601:
        case PAL_N_ITU_R_BT_601:
        case PAL_NC_ITU_R_BT_601:
        case SECAM_525_ITU_R_BT_601:
            pix_h = SECAM_PAL_ACTIVE_PIXELS_PER_FRAME;
	   break;
        default:
	   pix_h = NTSC_PAL_M_ACTIVE_PIXELS_PER_FRAME;
	   break;
    }

     return pix_h;
}
#if 0
uint8_t adv7182_get_cur_weaksignal(SV_Video_Capture *videoCapture)
{
    uint8_t val;

    adv7182_read_reg(videoCapture, adv7182_REG_STATUS_REG2, &val);
    return (val&(0x1<<6));
}

void adv7182_set_actv_video_start(SV_Video_Capture *videoCapture, int16_t offset)
{
    int8_t high_val;
    int8_t low_val;

    high_val = offset >> 2;
    low_val = offset & 0x3;
    adv7182_write_reg(videoCapture, adv7182_REG_ACTV_VIDEO_START_1, high_val);
    adv7182_write_reg(videoCapture, adv7182_REG_ACTV_VIDEO_START_2, low_val);
}

void adv7182_set_actv_video_stop(SV_Video_Capture *videoCapture, int16_t offset)
{
    int8_t high_val;
    int8_t low_val;

    high_val = offset >> 2;
    low_val = offset & 0x3;
    adv7182_write_reg(videoCapture, adv7182_REG_ACTV_VIDEO_STOP_1, high_val);
    adv7182_write_reg(videoCapture, adv7182_REG_ACTV_VIDEO_STOP_2, low_val);
}

void adv7182_adjust_frame_position(SV_Video_Capture *videoCapture)
{
    int8_t high_val;
    int8_t low_val;

    adv7182_write_reg(videoCapture, adv7182_REG_INDIRECT_REGISTER_ADDRESS, 0x4d);
    adv7182_write_reg(videoCapture, adv7182_REG_INDIRICT_REGISTER_RW_STROBE, 0x5);
    adv7182_read_reg(videoCapture, adv7182_REG_INDIRECT_REGISTER_DATA_1, &high_val);
    adv7182_read_reg(videoCapture, adv7182_REG_INDIRECT_REGISTER_DATA_2, &low_val);

    printf("adv7182 : HSYNC_START-H = 0x%x, HSYNC_START-L = 0x%x\n", high_val, low_val);
    adv7182_write_reg(videoCapture, adv7182_REG_INDIRECT_REGISTER_DATA_1, 0x51);
    adv7182_write_reg(videoCapture, adv7182_REG_INDIRECT_REGISTER_DATA_2, 0x50);
    adv7182_write_reg(videoCapture, adv7182_REG_INDIRECT_REGISTER_ADDRESS, 0xff);
    adv7182_write_reg(videoCapture, adv7182_REG_INDIRICT_REGISTER_RW_STROBE, 0x4);

    adv7182_write_reg(videoCapture, adv7182_REG_INDIRECT_REGISTER_DATA_1, high_val);
    adv7182_write_reg(videoCapture, adv7182_REG_INDIRECT_REGISTER_DATA_2, low_val - 64);
    adv7182_write_reg(videoCapture, adv7182_REG_INDIRECT_REGISTER_ADDRESS, 0x4d);
    adv7182_write_reg(videoCapture, adv7182_REG_INDIRICT_REGISTER_RW_STROBE, 0x6);

}
#endif
void adv7182_on(SV_Video_Capture *videoCapture)
{
#if 0
    adv7182_resetpin_low(videoCapture);
    usleep(10000);
    adv7182_resetpin_high(videoCapture);
    usleep(400000);
#endif
    //adv7182_disable_powerdown(videoCapture);
    adv7182_enable_composite_video(videoCapture);
}

void adv7182_off(SV_Video_Capture *videoCapture)
{
#if 0
    adv7182_resetpin_low(videoCapture);
    usleep(10000);
    adv7182_resetpin_high(videoCapture);
    usleep(400000);
#endif
    adv7182_disable_composite_video(videoCapture);
}
#if 0
void adv7182_fifo_reset(SV_Video_Capture *videoCapture)
{
    adv7182_write_reg(videoCapture, adv7182_REG_FIFO_RESET, 0xff);
}

uint8_t adv7182_get_cur_vblanking_start(SV_Video_Capture *videoCapture)
{
    uint8_t val;

    adv7182_read_reg(videoCapture, adv7182_REG_VERTICAL_BLANKING_START, &val);
     return val;
}

uint8_t adv7182_get_cur_vblanking_stop(SV_Video_Capture *videoCapture)
{
    uint8_t val;

    adv7182_read_reg(videoCapture, adv7182_REG_VERTICAL_BLANKING_STOP, &val);
     return val;
}

void adv7182_set_cur_vblanking_start(SV_Video_Capture *videoCapture, uint8_t start)
{
    adv7182_write_reg(videoCapture, adv7182_REG_VERTICAL_BLANKING_START, start);
}

void adv7182_set_cur_vblanking_stop(SV_Video_Capture *videoCapture, uint8_t stop)
{
    adv7182_write_reg(videoCapture, adv7182_REG_VERTICAL_BLANKING_STOP, stop);
}
#endif

void adv7182_init(SV_Video_Capture *videoCapture)
{
//	int n = 0;
//	int val;
    adv7180_enable();
    //adv7182_off(videoCapture); //output disable
    //adv7182_resetpin_init(videoCapture);
    //adv7182_set_actv_video_start(videoCapture, -1);
    //adv7182_set_actv_video_stop(videoCapture, 1);
    //adv7182_set_cur_vblanking_start(videoCapture, 0xff);
    //adv7182_set_cur_vblanking_stop(videoCapture, 0xff);
    //adv7182_enable_composite_video(videoCapture);
    //usleep(100000);
    videoCapture->info.pix_w = 720;//adv7182_get_cur_pix_w(videoCapture);
    videoCapture->info.pix_h = 525;//adv7182_get_cur_pix_h( videoCapture);
    videoCapture->info.pix_active_w = 720;//adv7182_get_cur_active_pix_w( videoCapture);
    videoCapture->info.pix_active_h = 480;//adv7182_get_cur_active_pix_h( videoCapture);
    //adv7182_get_cur_video_standard(videoCapture);
    //printf("The sensor info : pix_w = %d, pix_h = %d, pix_active_w = %d, pix_active_h = %d\n",
	//	videoCapture->info.pix_w, videoCapture->info.pix_h, videoCapture->info.pix_active_w, videoCapture->info.pix_active_h);
}

void adv7182_exit(SV_Video_Capture *videoCapture)
{
    adv7182_disable_composite_video(videoCapture) ;
    close(videoCapture->adv7182_dev.i2c_fd);
}

