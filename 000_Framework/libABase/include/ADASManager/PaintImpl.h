#ifndef PAINTERIMP_H
#define PAINTERIMP_H
#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <stdio.h>
#include <stdlib.h>
#include "TypeDefine.h"


class PaintImpl
{
public:
    PaintImpl();
    ~PaintImpl();
    VOID init();
    VOID update(Int32 width, Int32 height, VOID* buffer);
    VOID draw();
    VOID shutDown();


private:
    GLuint loadShader(GLenum type, const char* shaderSrc);
    Int32 initShader();
    Int32 initEGL();
    GLuint  esLoadProgram ( const char *vertShaderSrc, const char *fragShaderSrc );

    BYTE* YUYV_PackedFormat2PlanarFormat(VOID* buffer, Int32 width, Int32 height);
    BYTE* UYVY_PackedFormat2PlanarFormat(VOID* buffer, Int32 width, Int32 height);

private:
    GLuint programObject;
    GLint  positionLoc;
    GLint  texCoordLoc;
    // Sampler location
    GLint  textureUniformY;
    GLint  textureUniformU;
    GLint  textureUniformV;

    GLuint  textureYId;
    GLuint  textureUId;
    GLuint  textureVId;

private:
    Int32   m_width;
    Int32   m_height;
    BYTE*   plane[3];
    BYTE*   m_TmpBuffer = nullptr;
};

#endif  //  OPENINGPAINTERIMP_H
/* EOF */
