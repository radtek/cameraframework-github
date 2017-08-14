/**
 */
#include "PaintImpl.h"

PaintImpl::PaintImpl()
{
}

PaintImpl::~PaintImpl()
{

}

VOID PaintImpl::init()
{
    printf("xiaole---debug PaintImpl| init\n");
    initShader();
    // initEGL();
}

#if 0
VOID PaintImpl::initEGL()
{
    if (0 != textureYId && 0!=textureUId && 0!= textureVId) {
       // stopDraw();
    }
    glGenTextures(1, &textureYId);
    glBindTexture (GL_TEXTURE_2D, textureYId);

    glGenTextures(1, &textureUId);
    glBindTexture (GL_TEXTURE_2D, textureUId);

    glGenTextures(1, &textureVId);
    glBindTexture (GL_TEXTURE_2D, textureVId);
}
#endif

BYTE* PaintImpl::YUV422_PackedFormat2PlanarFormat(VOID* buffer, Int32 width, Int32 height)
{
    BYTE* _buffer = (BYTE*)buffer;

    int lenth = width * height * 2;
    BYTE* m_TmpBuffer = (BYTE*)malloc(lenth);

    int i = 0;
    int j = i + width * height;
    int k = j + ((width * height) >> 1) ;
    for(int l = 0; l < lenth; l++) {
      if(l % 4 == 0 || l % 4 == 2) { m_TmpBuffer[i] = _buffer[l]; i++;}
      if(l % 4 == 1) { m_TmpBuffer[j] = _buffer[l]; j++;}
      if(l % 4 == 3) { m_TmpBuffer[k] = _buffer[l]; k++;}
    }

    return m_TmpBuffer;
}

VOID PaintImpl::update(Int32 width, Int32 height, VOID* buffer)
{
    printf("xiaole---debug update, buffer=%p\n", buffer);
    if(buffer == NULL) {
        return;
    }

    m_width = width;
    m_height = height;
    //plane[0] = (BYTE*)buffer;
    plane[0] = YUV422_PackedFormat2PlanarFormat(buffer, width, height);
    plane[1] = plane[0] + width*height;
    plane[2] = plane[1] + (width*height >> 1);
    printf("xiaole---debug update ok\n");
}

VOID PaintImpl::draw()
{
    printf("xiaole---debug draw\n");
    glViewport (0, 0, m_width, m_height);
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // Use the program object
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureYId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, m_width, m_height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, plane[0]);
    glUniform1i(textureUniformY, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureUId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, m_width/2, m_height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, plane[1]);
    glUniform1i(textureUniformU, 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, textureVId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, m_width/2, m_height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, plane[2]);
    glUniform1i(textureUniformV, 2);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    if(m_TmpBuffer) free(m_TmpBuffer);
    printf("xiaole---debug draw  ok\n");
}


VOID PaintImpl::shutDown()
{
   // Delete texture object
   glDeleteTextures(1, &textureYId);
   glDeleteTextures(1, &textureUId);
   glDeleteTextures(1, &textureVId);

   // Delete program object
   glDeleteProgram(programObject);
}


Int32 PaintImpl::initShader()
{
    printf("xiaole---debug PaintImpl| initShader\n");
    GLbyte vShaderStr[] =
            "attribute vec4 vertexIn; \n"
            "attribute vec2 textureIn; \n"
            "varying vec2 textureOut; \n"
            "void main(void) \n"
            "{ \n"
            " gl_Position = vertexIn;  \n"
            " textureOut = textureIn; \n"
            "} \n";
    GLbyte fShaderStr[] =
             "precision mediump float;                          \n"
             "varying vec2 textureOut;                          \n"
             "uniform sampler2D tex_y;                            \n"
             "uniform sampler2D tex_u;                        \n"
             "uniform sampler2D tex_v;                    \n"
             "void main(void)                                         \n"
             "{                                                   \n"
             "  vec3 yuv;                               \n"
             "  vec3 rgb;                                \n"
             "                                                    \n"
             "  yuv.x = texture2D(tex_y, textureOut).r;   \n"
             "  yuv.y = texture2D(tex_u, textureOut).r - 0.5;   \n"
             "  yuv.z = texture2D(tex_v, textureOut).r - 0.5;   \n"
             "  rgb = mat3(1.0, 1.0, 1.0, 0.0, -0.337633, 1.732446, 1.370705, -0.698001, 0.0) * yuv;  \n"
             "  gl_FragColor = vec4(rgb, 1.0);  \n "
             "}                                                   \n";

    programObject = esLoadProgram((const char *)vShaderStr, (const char *)fShaderStr);
    // Bind positionLoc to attribute 0
    positionLoc = glGetAttribLocation(programObject, "vertexIn");
    texCoordLoc = glGetAttribLocation(programObject, "textureIn");

    glUseProgram (programObject);

    textureUniformY = glGetUniformLocation(programObject, "tex_y");
    textureUniformU = glGetUniformLocation(programObject, "tex_u");
    textureUniformV = glGetUniformLocation(programObject, "tex_v");

    static const GLfloat vertexVertices[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f,
    };
    static const GLfloat textureVertices[] = {
        0.0f,  1.0f,
        1.0f,  1.0f,
        0.0f,  0.0f,
        1.0f,  0.0f,
    };

    #if 0
    GLfloat vVertices[] = { -1.0f,  1.0f, 0.0f,  // Position 0
                               0.0f,  0.0f,        // TexCoord 0
                              -1.0f, -1.0f, 0.0f,  // Position 1
                               0.0f,  1.0f,        // TexCoord 1
                               1.0f, -1.0f, 0.0f,  // Position 2
                               1.0f,  1.0f,        // TexCoord 2
                               1.0f,  1.0f, 0.0f,  // Position 3
                               1.0f,  0.0f         // TexCoord 3
                            };
      GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
#endif

    glVertexAttribPointer(positionLoc, 2, GL_FLOAT, 0, 0, vertexVertices);
    glEnableVertexAttribArray(positionLoc);

    glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, 0, 0, textureVertices);
    glEnableVertexAttribArray(texCoordLoc);

    glGenTextures(1, &textureYId);
    glBindTexture(GL_TEXTURE_2D, textureYId);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenTextures(1, &textureUId);
    glBindTexture(GL_TEXTURE_2D, textureUId);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenTextures(1, &textureVId);
    glBindTexture(GL_TEXTURE_2D, textureVId);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    #if 0
    glVertexAttribPointer (positionLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices);
        // Load the texture coordinate
    glVertexAttribPointer (texCoordLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);

    glEnableVertexAttribArray (positionLoc);
    glEnableVertexAttribArray (texCoordLoc);
    #endif

    return 1;
}

GLuint  PaintImpl::esLoadProgram ( const char *vertShaderSrc, const char *fragShaderSrc )
{
   printf("xiaole---debug PaintImpl| esLoadProgram\n");
   GLuint vertexShader;
   GLuint fragmentShader;
   GLuint programObjectTmp;
   GLint linked;

   // Load the vertex/fragment shaders
   vertexShader = loadShader(GL_VERTEX_SHADER, vertShaderSrc );
   if ( vertexShader == 0 )
      return 0;

   fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragShaderSrc );
   if ( fragmentShader == 0 )
   {
      glDeleteShader( vertexShader );
      return 0;
   }

   // Create the program object
   programObjectTmp = glCreateProgram();

   if ( programObjectTmp == 0 )
      return 0;

   glAttachShader ( programObjectTmp, vertexShader );
   glAttachShader ( programObjectTmp, fragmentShader );

   // Link the program
   glLinkProgram ( programObjectTmp );

   // Check the link status
   glGetProgramiv ( programObjectTmp, GL_LINK_STATUS, &linked );

   if ( !linked )
   {
      GLint infoLen = 0;

      glGetProgramiv ( programObjectTmp, GL_INFO_LOG_LENGTH, &infoLen );

      if ( infoLen > 1 )
      {
         char* infoLog = (char*)malloc (sizeof(char) * infoLen );

         glGetProgramInfoLog ( programObjectTmp, infoLen, NULL, infoLog );

         printf("PROGRAM: %s\n", infoLog);
         free ( infoLog );
      }

      glDeleteProgram ( programObjectTmp );
      return 0;
   }

   // Free up no longer needed shader resources
   glDeleteShader ( vertexShader );
   glDeleteShader ( fragmentShader );

   return programObjectTmp;
}


GLuint  PaintImpl::loadShader(GLenum type, const char *shaderSrc)
{
    printf("xiaole---debug PaintImpl| loadShader\n");
    GLuint shader;
    GLint compiled;
    shader = glCreateShader(type);
    if (shader == 0) {
        return 0;
    }
    // Load the shader source
    glShaderSource(shader, 1, &shaderSrc, NULL);
    // Compile the shader
    glCompileShader(shader);
    // Check the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char* infoLog = static_cast<char*>(malloc(sizeof(char) * infoLen));
            if (infoLog  != NULL) {
                glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
                printf("SHADER %d: %s\n", type, infoLog);
                free(infoLog);
             }
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

/* EOF */