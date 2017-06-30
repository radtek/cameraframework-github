#ifndef __QNX_I2C_H__
#define __QNX_I2C_H__


/*
 * The following devctls are used by a client application
 * to control the I2C interface.
 */

#include <devctl.h>
#define _DCMD_I2C   _DCMD_MISC

#define DCMD_I2C_SET_SLAVE_ADDR     __DIOT (_DCMD_I2C, 1, i2c_addr_t)
#define DCMD_I2C_SET_BUS_SPEED      __DIOT (_DCMD_I2C, 2, _Uint32t)
#define DCMD_I2C_MASTER_SEND        __DIOT (_DCMD_I2C, 3, i2c_masterhdr_t)
#define DCMD_I2C_MASTER_RECV        __DIOTF(_DCMD_I2C, 4, i2c_masterhdr_t)
#define DCMD_I2C_SEND               __DIOT (_DCMD_I2C, 5, i2c_send_t)
#define DCMD_I2C_RECV               __DIOTF(_DCMD_I2C, 6, i2c_recv_t)
#define DCMD_I2C_SENDRECV           __DIOTF(_DCMD_I2C, 7, i2c_sendrecv_t)
#define DCMD_I2C_LOCK               __DION (_DCMD_I2C, 8)
#define DCMD_I2C_UNLOCK             __DION (_DCMD_I2C, 9)
#define DCMD_I2C_DRIVER_INFO        __DIOF (_DCMD_I2C, 10, i2c_driver_info_t)

typedef enum {
    I2C_ADDRFMT_10BIT   = 0x0001,
    I2C_ADDRFMT_7BIT    = 0x0002,
} i2c_addrfmt_t;

typedef struct {
    uint32_t            addr;   /* I2C address */
    uint32_t            fmt;    /* 7- or 10-bit format */
} i2c_addr_t;

typedef struct {
    i2c_addr_t          slave;  /* slave address */
    uint32_t            len;    /* length of send data in bytes */
    uint32_t            stop;   /* send stop when complete? (0=no, 1=yes) */
} i2c_send_t;

typedef struct {
    i2c_addr_t          slave;  /* slave address */
    uint32_t            len;    /* length of receive data in bytes */
    uint32_t            stop;   /* send stop when complete? (0=no, 1=yes) */
} i2c_recv_t;

typedef struct {
    i2c_addr_t          slave;      /* slave address */
    uint32_t            send_len;   /* length of send data in bytes */
    uint32_t            recv_len;   /* length of receive data in bytes */
    uint32_t            stop;       /* set stop when complete? */
} i2c_sendrecv_t;



#endif	/* __QNX_I2C_H__ */

