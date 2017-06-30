/*
 * main.h
 *
 *  Created on: 2012-3-15
 *      Author: LLuo
 */

#ifndef MAIN_H_
#define MAIN_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <sys/neutrino.h>
#include <pthread.h>
#include <stdint.h>

#define DMA_MAX_BUFNUM 12
enum capture_state
{
    NONE = 0,
    ENABLE,
    DISABLE,
};
 /*****************************************************************************
 ** Structures
 *****************************************************************************/
 
typedef struct 
{
    char   *i2c_name;
    uint8_t sync_status;
    uint32_t i2c_addr; // the i2c slave address of adv7182
    uint32_t i2c_fd; 
    uintptr_t pin_base;//reset pin
}adv7182_t;

typedef struct 
{
    int32_t    irq; 
    int32_t    intr_id; // The value returned by InterruptAttach() or InterruptAttachEvent()
    uintptr_t ipu2_base; // the start address of IPU2
    uintptr_t src_base; // the start address of src
    uintptr_t iomuxc_base; // the start address of iomux
    void * ch0_param;
}ipu_csi_t;

typedef struct 
{
    uint32_t state;
    uint32_t pix_buf_w;
    uint32_t pix_buf_h;
    uint32_t pix_w;
    uint32_t pix_h;
    uint32_t pix_active_w;
    uint32_t pix_active_h;
    uint32_t stride;	
    uint8_t   brightness;
    uint8_t   contrast;
}info_t;

typedef struct 
{
    long *buffer_phyaddr[DMA_MAX_BUFNUM];
    uint32_t work_buf_index; // point the current using buffer by mda
    uint32_t ready_buf_index; //point the current accessable buffer
    uint32_t buf_num;
    pthread_t thread_id;
    struct sigevent event;
}resource_t_1;

typedef struct _SV_Video_Capture_t
{
    adv7182_t  adv7182_dev;
    ipu_csi_t     ipu2_csi;
    info_t          info;
    resource_t_1 resource;
}SV_Video_Capture;

#ifdef __cplusplus
}
#endif


#endif /* MAIN_H_ */
