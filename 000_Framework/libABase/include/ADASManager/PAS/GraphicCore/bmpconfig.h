/**
 * Copyright @ 2013 - 2014 Suntec Software(Shanghai) Co., Ltd.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are NOT permitted except as agreed by
 * Suntec Software(Shanghai) Co., Ltd.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */
/**
 * @file define.h
 * @brief Declaration file of constants and structures.
 */

#ifndef DEFINE_H
#define DEFINE_H

// #ifndef __cplusplus
// #    error ERROR: This file requires C++ compilation (use a .cpp suffix)
// #endif

//  //#include "ncore/NCTypesDefine.h"

//  #define  OPENING_STORAGEDRIVER_DEV_NAND_NAME    "/dev/block/mmcblk0"
//  #define  MAX_RESERVED_SIZE     476
//  #define  OPENING_INFO_ADDR   0x100000
//  #define  OPENING_IMAGE_ADDR   0x100200

#define  IMAGEINFO_MAX_SIZE     472
// #define  OPENINGINFO_MAX_SIZE 492

//  typedef signed char        BOOL;
// typedef unsigned char    BYTE;
// typedef int                      INT;
// typedef void                  *LPVOID;
// typedef unsigned short   WORD;
// typedef unsigned int              DWORD;
// typedef int                    LONG;
// typedef unsigned int              UINT32;




// // typedef unsigned int            UInt32;
// // typedef long                    LONG;
// // typedef unsigned long           UInt64;
// // typedef bool                    BOOLEAN;
// // typedef int                     Int32;
// // typedef unsigned short          USHORT;
// // typedef float                   Float32;
// // typedef unsigned char           BYTE;
// // typedef char                    CHAR;
// // typedef void                    VOID;





//  enum VEHICLE_PARAM_THUMB_TYPE
// {
//      VEHICLE_PARAM_THUMB_TYPE_LEXUS_LS = 0,
//      VEHICLE_PARAM_THUMB_TYPE_LEXUS_GS,
//      VEHICLE_PARAM_THUMB_TYPE_LEXUS,
//      VEHICLE_PARAM_THUMB_TYPE_TOYOTA,
//      VEHICLE_PARAM_THUMB_TYPE_NONE
// };

 typedef struct imageInformation
 {
     int image_size;
     int width;
     int height;
     int crop_X;
     int crop_Y;
     int crop_width;
     int crop_height;
     int screen_X;
     int screen_Y;
     int movie;
     char reserved[IMAGEINFO_MAX_SIZE];
 }IMAGEINFO;

//  typedef struct OpeningInformation
//  {
//      int show_image;
//      int preset_info_addr;
//      int second_info_addr;
//      int vehicle_param_thumb_type;
//      int vehicle_param_opening_pic;
//      char reserved[OPENINGINFO_MAX_SIZE];
//  }OPENINGINFO;

// #pragma pack(push,2)
//  typedef struct bitmapfileinfo
//  {
//         WORD wbfType;
//         DWORD dwbfSize;
//         WORD wbfReserved1;
//         WORD wbfReserved2;
//         DWORD dwbfOffBits;
//  } BITMAPFILEHEADER1;

// typedef struct bitmapinfo
// {
//         DWORD dwbiSize;
//         LONG lbiWidth;
//         LONG lbiHeight;
//         WORD wbiPlanes;
//         WORD wbiBitCount;
//         DWORD dwbiCompression;
//         DWORD dwbiSizeImage;
//         LONG lbiXPelsPerMeter;
//         LONG lbiYpelsPerMeter;
//         DWORD dwbiClrUsed;
//         DWORD dwbiClrImportant;
//     } BITMAPINFOHEADER1;

//     #pragma pack(pop)

#define HEAD_MAX_SIZE 54


static unsigned char head[HEAD_MAX_SIZE] = {
                          0x42,0x4d, //2 wbfType
                          0x30,0x0C,0x01,0, //4 dwbfSize
                          0,0, //2 wbfReserved1
                          0,0, //2 wbfReserved2
                          0x36,0,0,0,//4 dwbfOffBits

                          0x28,0,0,0, //4 dwbiSize
                          0x00,0,0,0, //4 lbiWidth
                          0x00,0,0,0, //4 lbiHeight
                          0x01,0,//2 wbiPlanes
                          0x20,0,//2 wbiBitCount
                          0,0,0,0, //4 dwbiCompression
                          0x00,0x00,0x00,0x00, //4 dwbiSizeImage
                          0x00,0x00,0x00,0x00, //4 lbiXPelsPerMeter
                          0x00,0x00,0x00,0x00, //4  lbiYpelsPerMeter
                          0,0,0,0,//4 dwbiClrUsed
                          0,0,0,0//4 dwbiClrImportant
                          };

#define bfSize  2  //4

#define Width  18  //4
#define Height 22  //4
#define BitCount 28  //2
#define SizeImage 34 //4

static void saveAsBmp(const char* path, void* databuffer, IMAGEINFO imageinfo)
{
    head[bfSize] = HEAD_MAX_SIZE + imageinfo.image_size;
    head[Width] = imageinfo.width;
    head[Height] = imageinfo.height;
    head[SizeImage] = imageinfo.image_size;
    head[BitCount] = 0x20;

    FILE * stream = fopen(path, "wb");
    if(stream == NULL) return;


    fwrite(head,  HEAD_MAX_SIZE, 1, stream);
    fwrite(databuffer,  imageinfo.image_size, 1, stream);

    fclose(stream);
}

#endif /* DEFINE_H */
 /* EOF */