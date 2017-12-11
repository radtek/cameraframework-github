

#include "AOpenGLES.h"

namespace Harman 				{
namespace Adas        			{
namespace AFramework  			{
namespace AGraphic    			{


CAdasOpenGLES::CAdasOpenGLES(emoduleType moduleType)
{
	mModuleType = moduleType;

	if(MODULE_PAS == mModuleType)
	{
		mGLInfo.unOpenGLType.pTypePAS = new tOpenGLPAS;
	}
	else if(MODULE_RVC == mModuleType)
	{
		mGLInfo.unOpenGLType.pTypeRVC = new tOpenGLRVC;
	}
	else
	{

	}
}

CAdasOpenGLES::~CAdasOpenGLES()
{
}

VOID CAdasOpenGLES::OpenGLESInitPAS()
{
	const CHAR vShaderStr[] =
			"attribute vec4 a_position;   \n"
			"attribute vec2 a_texCoord;   \n"
			"varying vec2 v_texCoord;	  \n"
			"void main()				  \n"
			"{							  \n"
			"	gl_Position = a_position; \n"
			"	v_texCoord = a_texCoord;  \n"
			"}							  \n";

	const CHAR fShaderStr[] =
			"precision mediump float;							 \n"
			"varying vec2 v_texCoord;							 \n"
			"uniform sampler2D s_baseMap;						 \n"
			"uniform sampler2D s_otherMap;						 \n"
			"uniform sampler2D s_lightMap;						 \n"
			"uniform mediump float Alpha;						 \n"
			"void main()										 \n"
			"{													 \n"
			"  vec4 baseColor;									 \n"
			"  vec4 lightColor; 								 \n"
			"  vec4 otherColor; 								  \n"
			"													 \n"
			"  baseColor = texture2D( s_baseMap, v_texCoord );	 \n"
			"  lightColor = texture2D( s_lightMap, v_texCoord ); \n"
			"  otherColor = texture2D( s_otherMap, v_texCoord ); \n"
			//"  gl_FragColor = baseColor * (lightColor + 0.25);   \n"
			//"  gl_FragColor = baseColor * (1.0 - lightColor.a) + lightColor;			 \n"
			"  gl_FragColor = lightColor * (1.0 - baseColor.a) + baseColor; 		 \n"
			"  gl_FragColor = gl_FragColor * (1.0 - otherColor.a) + otherColor; 		 \n"
			//"  gl_FragColor = lightColor * (baseColor + Alpha);	\n"
			//"  gl_FragColor = vec4(baseColor.rgb, Alpha);   \n"
			"}													 \n";

	// Load the shaders and get a linked program object
	mGLInfo.programObject = OpenGLESLoadProgram(vShaderStr, fShaderStr);

	// Get the attribute locations
	mGLInfo.positionLoc = glGetAttribLocation(mGLInfo.programObject, "a_position");
	mGLInfo.texCoordLoc = glGetAttribLocation(mGLInfo.programObject, "a_texCoord");

	glUseProgram(mGLInfo.programObject);

	// Get the image location
	mGLInfo.unOpenGLType.pTypePAS->baseMapLoc = glGetUniformLocation(mGLInfo.programObject, "s_baseMap");
	mGLInfo.unOpenGLType.pTypePAS->lightMapLoc = glGetUniformLocation(mGLInfo.programObject, "s_lightMap");
	mGLInfo.unOpenGLType.pTypePAS->otherMapLoc = glGetUniformLocation(mGLInfo.programObject, "s_otherMap");

	// Load the textures
	mGLInfo.unOpenGLType.pTypePAS->baseMapTexId = OpenGLESLoadTexture();
	mGLInfo.unOpenGLType.pTypePAS->lightMapTexId = OpenGLESLoadTexture();
	mGLInfo.unOpenGLType.pTypePAS->otherMapTexId = OpenGLESLoadTexture();

	if(mGLInfo.unOpenGLType.pTypePAS->baseMapTexId == 0 || mGLInfo.unOpenGLType.pTypePAS->lightMapTexId == 0  || mGLInfo.unOpenGLType.pTypePAS->otherMapTexId == 0)
		return ;
}

VOID CAdasOpenGLES::OpenGLESInitRVC()
{
	const CHAR vShaderStr[] =
            "attribute vec4 vertexIn; \n"
            "attribute vec2 textureIn; \n"
            "varying vec2 textureOut; \n"
            "void main(void) \n"
            "{ \n"
            " gl_Position = vertexIn;  \n"
            " textureOut = textureIn; \n"
            "} \n";

	const CHAR fShaderStr[] =
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

	// Load the shaders and get a linked program object
	mGLInfo.programObject = OpenGLESLoadProgram(vShaderStr, fShaderStr);

	// Get the attribute locations
	mGLInfo.positionLoc = 0;
	mGLInfo.texCoordLoc = 1;
    glBindAttribLocation(mGLInfo.programObject, mGLInfo.positionLoc, "vertexIn");
    glBindAttribLocation(mGLInfo.programObject, mGLInfo.texCoordLoc, "textureIn");

	glUseProgram(mGLInfo.programObject);

	// Get the image location
	mGLInfo.unOpenGLType.pTypeRVC->uiTxtformY = glGetUniformLocation(mGLInfo.programObject, "tex_y");
	mGLInfo.unOpenGLType.pTypeRVC->uiTxtformU = glGetUniformLocation(mGLInfo.programObject, "tex_u");
	mGLInfo.unOpenGLType.pTypeRVC->uiTxtformV = glGetUniformLocation(mGLInfo.programObject, "tex_v");

	// Load the textures
	mGLInfo.unOpenGLType.pTypeRVC->textureYId = OpenGLESLoadTexture();
	mGLInfo.unOpenGLType.pTypeRVC->textureUId = OpenGLESLoadTexture();
	mGLInfo.unOpenGLType.pTypeRVC->textureVId = OpenGLESLoadTexture();
	if(mGLInfo.unOpenGLType.pTypeRVC->textureYId == 0 || mGLInfo.unOpenGLType.pTypeRVC->textureUId == 0  || mGLInfo.unOpenGLType.pTypeRVC->textureVId == 0)
		return ;
}

VOID CAdasOpenGLES::OpenGLESRenderPAS(map<string, tbufInfo>  bufferMap)
{
	//auto it;
	GLfloat vVertices[] = { -1.0f, 1.0f, 0.0f,  // Position 0
		0.0f, 0.0f,        // TexCoord 0
		-1.0f, -1.0f, 0.0f,  // Position 1
		0.0f, 1.0f,        // TexCoord 1
		1.0f, -1.0f, 0.0f,  // Position 2
		1.0f, 1.0f,        // TexCoord 2
		1.0f, 1.0f, 0.0f,  // Position 3
		1.0f, 0.0f         // TexCoord 3
	};
	GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

	glViewport (0, 0, 640, 720);

	// Load the vertex position
    glVertexAttribPointer(mGLInfo.positionLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    glEnableVertexAttribArray(mGLInfo.positionLoc);

	// Load the texture coordinate
    glVertexAttribPointer(mGLInfo.texCoordLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    glEnableVertexAttribArray(mGLInfo.texCoordLoc);

    static BOOLEAN isBakegroundShowed = FALSE;
    static BOOLEAN isCarShowed = FALSE;

    if(!isBakegroundShowed){
		auto it3 = bufferMap.find(ADAS_PAS_BACKGROUND_STATUS);
		if(it3 != bufferMap.end()) {
		    glActiveTexture(GL_TEXTURE2);
		    glBindTexture(GL_TEXTURE_2D, mGLInfo.unOpenGLType.pTypePAS->otherMapTexId);
		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, it3->second.width, it3->second.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, it3->second.buffer);
		    glUniform1i(mGLInfo.unOpenGLType.pTypePAS->otherMapLoc, 0);

		    isBakegroundShowed = TRUE;
		}
	}

    if(!isCarShowed){
    	auto it2 = bufferMap.find(ADAS_PAS_CAR_STATUS);
		if(it2 != bufferMap.end()) {
		    glActiveTexture(GL_TEXTURE1);
		    glBindTexture(GL_TEXTURE_2D, mGLInfo.unOpenGLType.pTypePAS->lightMapTexId);
		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, it2->second.width, it2->second.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, it2->second.buffer);
		    glUniform1i(mGLInfo.unOpenGLType.pTypePAS->lightMapLoc, 2);

		    isCarShowed = TRUE;
		}
    }

    auto it1 = bufferMap.find(ADAS_PAS_RADAR_STATUS);
	if(it1 != bufferMap.end()) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mGLInfo.unOpenGLType.pTypePAS->baseMapTexId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, it1->second.width, it1->second.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, it1->second.buffer);
		glUniform1i(mGLInfo.unOpenGLType.pTypePAS->baseMapLoc, 1);
	}


	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

VOID CAdasOpenGLES::OpenGLESRenderRVC(map<string, tbufInfo>  bufferMap)
{
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

	glViewport (0, 0, 1280, 720);

    glVertexAttribPointer(mGLInfo.positionLoc, 2, GL_FLOAT, 0, 0, vertexVertices);
    glEnableVertexAttribArray(mGLInfo.positionLoc);

    glVertexAttribPointer(mGLInfo.texCoordLoc, 2, GL_FLOAT, 0, 0, textureVertices);
    glEnableVertexAttribArray(mGLInfo.texCoordLoc);

	auto it = bufferMap.find(ADAS_PAS_CAR_STATUS);
	if(it != bufferMap.end())
	{
		glActiveTexture(GL_TEXTURE0);
	    glBindTexture(GL_TEXTURE_2D, mGLInfo.unOpenGLType.pTypeRVC->textureYId);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, it->second.width, it->second.height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, it->second.buffer);
	    glUniform1i(mGLInfo.unOpenGLType.pTypeRVC->uiTxtformY, 0);

	    glActiveTexture(GL_TEXTURE1);
	    glBindTexture(GL_TEXTURE_2D, mGLInfo.unOpenGLType.pTypeRVC->textureUId);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, it->second.width/2, it->second.height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, it->second.buffer + (it->second.width*it->second.height));
	    glUniform1i(mGLInfo.unOpenGLType.pTypeRVC->uiTxtformU, 1);

	    glActiveTexture(GL_TEXTURE2);
	    glBindTexture(GL_TEXTURE_2D, mGLInfo.unOpenGLType.pTypeRVC->textureVId);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, it->second.width/2, it->second.height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, it->second.buffer + (it->second.width*it->second.height >> 1));
	    glUniform1i(mGLInfo.unOpenGLType.pTypeRVC->uiTxtformV, 2);
	}

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

VOID CAdasOpenGLES::OpenGLESInitialize(emoduleType moduleType)
{
	printf("	 [%s, %d]  mModuleType = %d\n", __FUNCTION__, __LINE__, mModuleType);

	switch(mModuleType)
	{
		case MODULE_PAS:
			OpenGLESInitPAS();
			break;
		case MODULE_RVC:
			OpenGLESInitRVC();
			break;
		default:
			break;
	}

}

VOID CAdasOpenGLES::OpenGLESRender(map<string, tbufInfo>  bufferMap)
{
	switch(mModuleType)
	{
		case MODULE_PAS:
			OpenGLESRenderPAS(bufferMap);
			break;
		case MODULE_RVC:
			OpenGLESRenderRVC(bufferMap);
			break;
		default:
			break;
	}

}



GLuint CAdasOpenGLES::OpenGLESLoadProgram(const CHAR *vertShaderSrc, const CHAR *fragShaderSrc)
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint programObject;
	GLint  linked;

	//Load the vertex/fragment shaders
	vertexShader = OpenGLESLoadShader(GL_VERTEX_SHADER, vertShaderSrc);
	if(0 == vertexShader)
	{
		return 0;
	}

	fragmentShader = OpenGLESLoadShader(GL_FRAGMENT_SHADER, fragShaderSrc);
	if(0 == fragmentShader)
	{
		glDeleteShader(vertexShader);
		return 0;
	}

	//Create the program object
	programObject = glCreateProgram();
	if(0 == programObject)
	{
      return 0;
	}

	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);

	//Link the program
	glLinkProgram(programObject);

	//Check the link status
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
	if(!linked)
	{
		GLint infoLen = 0;

		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
		if(infoLen > 1)
		{
			char* infoLog = (char *)malloc (sizeof(char) * infoLen);
			glGetProgramInfoLog( programObject, infoLen, NULL, infoLog);

			free(infoLog);
		}

		glDeleteProgram(programObject);
		return 0;
	}

	//Free up no longer needed shader resources
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return programObject;
}

GLuint CAdasOpenGLES::OpenGLESLoadShader(GLenum type, const CHAR *shaderSrc)
{
	GLuint shader;
	GLint compiled;

	//Create the shader object
	shader = glCreateShader(type);
	if(0 == shader)
	{
		return 0;
	}

	//Load the shader source
	glShaderSource(shader, 1, &shaderSrc, NULL);

	//Compile the shader
	glCompileShader(shader);

	//Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if(!compiled)
	{
		GLint infoLen = 0;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if(infoLen > 1)
		{
			char* infoLog = (char *)malloc(sizeof(char) * infoLen);
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			//esLogMessage("Error compiling shader:\n%s\n", infoLog);
			free(infoLog);
	  }

	  glDeleteShader(shader);
	  return 0;
   }

   return shader;
}

GLuint CAdasOpenGLES::OpenGLESLoadTexture()//(Int32 width, Int32 height)
{
	GLuint texId;
	//textWidth = width;
	//texHeight = height;

	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return texId;
}


}
}
}
}

/* EOF */

