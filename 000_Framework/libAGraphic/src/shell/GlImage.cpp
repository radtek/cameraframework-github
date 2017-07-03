/*
 * GlImage.cpp
 *
 *  Created on: 2012-5-10
 *      Author: QiLiu
 */
#include "GlImage.h"

#define VERTEX_ARRAY 0
#define TEXCOORD_ARRAY 1

const char* pImageVertShader = "\
		attribute mediump vec4 inVert;\
		attribute mediump vec2 inCoord;\
		uniform mediump mat4 mvpMat;\
		varying mediump vec2 texCoord;\
		void main()\
		{\
		   gl_Position = mvpMat * inVert;\
		   texCoord = inCoord;\
		}";

const char* pImageFragShader = "\
		varying mediump vec2 texCoord;\
		uniform mediump sampler2D tex;\
		void main()\
		{\
		   gl_FragColor = vec4(texture2D(tex,texCoord).rgb,1.0);\
	   }";

GlImage::GlImage()
{
	;
}

GlImage::~GlImage()
{
	Shutdown();
}

void GlImage::Init(const char* fileName)
{
	LoadShaders();
	LoadMeshes();
	LoadTextures(fileName);
}

void GlImage::Shutdown()
{
	glDeleteTextures(1,&m_uiTexture);
	glDeleteBuffers(1,&m_uiVBO);
	glDeleteProgram(m_ImageObj.uiId);
}

void GlImage::Render(PVRTMat4& pvMat)
{
	glUseProgram(m_ImageObj.uiId);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D,m_uiTexture);
	PVRTMat4 mat = PVRTMat4::Identity();
	glUniformMatrix4fv(m_ImageObj.uiMVP,1,GL_FALSE,mat.ptr());

	glBindBuffer(GL_ARRAY_BUFFER,m_uiVBO);

	glEnableVertexAttribArray(VERTEX_ARRAY);
	glEnableVertexAttribArray(TEXCOORD_ARRAY);

	glVertexAttribPointer(VERTEX_ARRAY,3,GL_FLOAT,GL_FALSE,5*sizeof(float),0);
	glVertexAttribPointer(TEXCOORD_ARRAY,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));

	glDrawArrays(GL_TRIANGLES, 0,6);

	glDisableVertexAttribArray(VERTEX_ARRAY);
	glDisableVertexAttribArray(TEXCOORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glActiveTexture(GL_TEXTURE0);

//	static int cnt = 0;
//	if(cnt%100==0)
//	{
//		int err = glGetError();
//		printf("err = %d\n",err);
//	}
//	cnt ++;
}

void GlImage::LoadShaders()
{
	const char* aszAttribs[] = { "inVert","inCoord" };
	m_ImageObj.uiId = LoadShaderFromString(pImageVertShader,pImageFragShader,aszAttribs,2);
	m_ImageObj.uiMVP = glGetUniformLocation(m_ImageObj.uiId,"mvpMat");
	glUniform1i(glGetUniformLocation(m_ImageObj.uiId,"tex"),4);
}

void GlImage::LoadMeshes()
{
	float data[] = {
			-1.0,-1.0,-1.0,
			0.0,0.0,
			1.0,-1.0,-1.0,
			1.0,0.0,
			1.0,1.0,-1.0,
			1.0,1.0,
			//
			1.0,1.0,-1.0,
			1.0,1.0,
			-1.0,1.0,-1.0,
			0.0,1.0,
			-1.0,-1.0,-1.0,
			0.0,0.0
	};
	glGenBuffers(1, &m_uiVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GlImage::LoadTextures(const char* fileName)
{
//	LoadRGBTextureFromBMP(fileName,&m_uiTexture);
	LoadAlphaTextureFromBMP(fileName,&m_uiTexture);

}
