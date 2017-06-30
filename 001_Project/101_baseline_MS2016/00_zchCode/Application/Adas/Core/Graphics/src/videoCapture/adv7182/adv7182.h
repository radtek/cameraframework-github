/*
 * adv7182.h
 *
 *  Created on: 2013-5-22
 *      Author: Whuang
 */

#ifndef _adv7182_H_
#define _adv7182_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/*adv7182 registers */
#if 0
#define adv7182_REG_ANALOG_CTRL           (0x01)
#define adv7182_REG_OPERATION_MODE_CTRL           (0x02)
#define adv7182_REG_MISC_CTRL           (0x03)
#define adv7182_REG_BRIGHTNESS_CTRL  (0X09)
#define adv7182_REG_CONTRAST_CTRL  (0x0C)
#define adv7182_REG_ACTV_VIDEO_START_1 (0x11)
#define adv7182_REG_ACTV_VIDEO_START_2 (0x12)
#define adv7182_REG_ACTV_VIDEO_STOP_1 (0x13)
#define adv7182_REG_ACTV_VIDEO_STOP_2 (0x14)
#define adv7182_REG_VERTICAL_BLANKING_START (0x18)
#define adv7182_REG_VERTICAL_BLANKING_STOP (0x19)
#define adv7182_REG_INDIRECT_REGISTER_DATA_1 (0x21)
#define adv7182_REG_INDIRECT_REGISTER_DATA_2 (0x22)
#define adv7182_REG_INDIRECT_REGISTER_ADDRESS (0x23)
#define adv7182_REG_INDIRICT_REGISTER_RW_STROBE (0x24)
#define adv7182_REG_RAM_VERSION_LSB     (0x33)
#define adv7182_REG_DEVICE_ID_MSB       (0x80)
#define adv7182_REG_DEVICE_ID_LSB       (0x81)
#define adv7182_REG_ROM_VERSION         (0x82)
#define adv7182_REG_RAM_VERSION_MSB     (0x83)
#define adv7182_REG_STATUS_REG1 (0x88)
#define adv7182_REG_STATUS_REG2 (0x89)
#define adv7182_REG_STATUS_REG5 (0x10)
#define adv7182_REG_FIFO_RESET (0xc9)
#endif
/* adv7182 Video Standard map*/
#define adv7182_REG_VIDEOSTD_BIT_MASK 0x70
#define NTSC_ITU_R_BT_601 		0x00
#define NTSC_4_43_ITU_R_BT_601 	0x01
#define PAL_M_ITU_R_BT_601 		0x02
#define PAL_60_ITU_R_BT_601 	0x03
#define PAL_N_ITU_R_BT_601 		0x04
#define SECAM_ITU_R_BT_601 		0x05
#define PAL_NC_ITU_R_BT_601 	0x06
#define SECAM_525_ITU_R_BT_601 	0x07

#define NTSC_PAL_M_PIXELS_PER_LINE 858
#define NTSC_PAL_M_ACTIVE_PIXELS_PER_LINE 720
#define NTSC_PAL_M_PIXELS_PER_FRAME 525
#define NTSC_PAL_M_ACTIVE_PIXELS_PER_FRAME 480
#define SECAM_PAL_PIXELS_PER_LINE 864
#define SECAM_PAL_ACTIVE_PIXELS_PER_LINE 720
#define SECAM_PAL_PIXELS_PER_FRAME 625
#define SECAM_PAL_ACTIVE_PIXELS_PER_FRAME 576

//#define adv7182AM1_I2C_ADDR     (0x5D)
#define ADV7182_I2C_BASE 		(0x21)
#define I2C_DEV_NAME "/dev/i2c3"

uint8_t adv7182_get_syncstatus(SV_Video_Capture *videoCapture);
void adv7182_set_brightness(SV_Video_Capture *videoCapture, uint8_t brightness);
void adv7182_set_contrast(SV_Video_Capture *videoCapture, uint8_t contrast);
void adv7182_init(SV_Video_Capture *videoCapture);
void adv7182_exit(SV_Video_Capture *videoCapture);
void adv7182_on(SV_Video_Capture *videoCapture);
void adv7182_off(SV_Video_Capture *videoCapture);
//void adv7182_fifo_reset(SV_Video_Capture *videoCapture);
//uint8_t adv7182_get_cur_vblanking_start(SV_Video_Capture *videoCapture);
//uint8_t adv7182_get_cur_vblanking_stop(SV_Video_Capture *videoCapture);


int adv7180_enable (void);
extern int update_adv7180_register (int idx, uint8_t val);
extern uint8_t read_adv7180_register (int idx);
extern uint8_t get_7180_status3(void);
extern uint8_t rear_camera_selected(void);

#define FREE_RUN_ACT_MASK   0x10
#define FREE_RUN_ACT_POS 	4

#ifdef __cplusplus
}
#endif

#endif
