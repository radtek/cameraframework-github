#ifndef _RVS_CRC_H_
#define _RVS_CRC_H_
#include <inttypes.h>

int iCRCProc();
uint32_t rc_crc32(uint32_t crc, const char *buf, size_t len);

#endif
