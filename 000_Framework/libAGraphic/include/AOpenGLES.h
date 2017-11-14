#ifndef  AOPENGLES_H
#define  AOPENGLES_H
#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif


#include <GLES2/gl2.h>
#include "graphicType.h"

namespace Harman 			{
namespace Adas 				{
namespace AFramework 		{
namespace AGraphic 			{

typedef struct
{
	// Sampler locations
	GLint baseMapLoc;
	GLint lightMapLoc;
	GLint otherMapLoc;

	// Texture handle
	GLuint baseMapTexId;
	GLuint lightMapTexId;
	GLuint otherMapTexId;
}tOpenGLPAS;

typedef struct
{
	// Sampler locations
	GLint uiTxtformY;
	GLint uiTxtformU;
	GLint uiTxtformV;

	// Texture handle
	GLuint textureYId;
	GLuint textureUId;
	GLuint textureVId;
}tOpenGLRVC;

typedef union
{
	tOpenGLPAS *pTypePAS;
	tOpenGLRVC *pTypeRVC;
}uOpenGLType;

typedef struct
{
	// Handle to a program object
	GLuint programObject;

	// Attribute locations
	GLint  positionLoc;
	GLint  texCoordLoc;

	uOpenGLType unOpenGLType;
}UserData;

class CAdasOpenGLES
{

public:
    CAdasOpenGLES(emoduleType moduleType);
	virtual ~CAdasOpenGLES();
    VOID OpenGLESInitialize(emoduleType moduleType);
	VOID OpenGLESRender(map<string, tbufInfo>  bufferMap);

private:
    VOID OpenGLESInitPAS();
    VOID OpenGLESInitRVC();
	VOID OpenGLESRenderPAS(map<string, tbufInfo>  bufferMap);
	VOID OpenGLESRenderRVC(map<string, tbufInfo>  bufferMap);
	GLuint OpenGLESLoadProgram(const CHAR *vertShaderSrc, const CHAR *fragShaderSrc);
	GLuint OpenGLESLoadShader(GLenum type, const CHAR *shaderSrc);
	GLuint OpenGLESLoadTexture();//(Int32 width, Int32 height)
		
private:
	UserData mGLInfo;
	Int32 mWidth; 
	Int32 mHeight;
	emoduleType mModuleType;
};


}
}
}
}

#endif  //  AOPENGLES_H
/* EOF */


