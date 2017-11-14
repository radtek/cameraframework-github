
#ifndef __HARMAN_ADAS_AGRAPHIC_TYPEDEF_H__
#define __HARMAN_ADAS_AGRAPHIC_TYPEDEF_H__

#include <iostream>
#include "TypeDefine.h"


#define ADAS_PAS_RADAR_STATUS	"RADAR_STATUS"
#define ADAS_PAS_CAR_STATUS		"CAR_STATUS"
#define ADAS_PAS_WARNING_STATUS	"WARNING_STATUS"


typedef enum 
{
    COLOR_YUV,
    COLOR_RGB,
	COLOR_RGBA,
    UNKNOWN_COLOR
}ecolorType;

typedef enum 
{
    MODULE_UNKNOW,
	MODULE_PAS,
    MODULE_RVC,
    MODULE_GUIDELINE,
    MODULE_MAX_NUM
}emoduleType;


typedef struct
{
	string					surfaceName;
	UInt32					surfaceId;
	emoduleType 			moduleType;
	BOOLEAN					bActiveEGL;
	//EGLSurface			  egl_surf;
	viewInfo				viewPos;
}tsurfaceInfo;

typedef struct
{
	BYTE 					*buffer;
	UInt32					width;
	UInt32					height;
	BOOLEAN 				bRender;
}tbufInfo;

typedef struct
{
	UInt32					surfaceID;
	//vector<tbufInfo> 		bufferArray;
	//map<string, tbufInfo*>  bufferMap;
	map<string, tbufInfo>  bufferMap;
}trenderData;


// } // namespace AFoundation
// } // namespace AFramework
// } // namespace Adas
// } // namespace Harman

#endif // __HARMAN_ADAS_AGRAPHIC_TYPEDEF_H__
