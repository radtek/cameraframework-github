/*
 * GlAlphaTexRect.cpp
 *
 *  Created on: 2012-4-10
 *      Author: QiLiu
 */
#include "GlAlphaTexRect.h"

const char* pAlphaTexRectVertShader = "\
   attribute mediump vec4 inVert;\
   attribute mediump vec2 inCoord;\
   uniform mediump mat4 mvpMat;\
   varying mediump vec2 texCoord;\
   void main()\
   {\
      gl_Position = mvpMat*inVert;\
	  texCoord = inCoord;\
   }";

const char* pAlphaTexRectFragShader = "\
	varying mediump vec2 texCoord;\
	uniform lowp sampler2D tex;\
	uniform mediump vec3 color;\
	void main()\
	{\
		gl_FragColor = vec4(color, texture2D(tex,texCoord).a);\
	}";

#define VERTEX_ARRAY 0
#define TEXCOORD_ARRAY 1

GlAlphaTexRect::GlAlphaTexRect()
{
	m_fColor[0] = 1.0;
	m_fColor[1] = 0.0;
	m_fColor[2] = 0.0;

	m_iTexImageWidth = 0;
	m_iTexImageHeight = 0;
}

GlAlphaTexRect::~GlAlphaTexRect()
{
	Shutdown();
}

int GlAlphaTexRect::Init(const char* texFile,int screenWidth,int screenHeight)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	if(LoadShaders())
		return -1;
	if(LoadTextures(texFile))
		return -1;
	LoadMeshes();
	return 0;
}

void GlAlphaTexRect::Shutdown()
{
	//delete buffer
	glDeleteBuffers(1,&m_uiVBO);
	//delete texture
	glDeleteTextures(1,&m_uiTexture);
	//delete shaders
	glDeleteProgram(m_RectObj.uiId);
}

void GlAlphaTexRect::Render(const PVRTMat4& pvMat,float scale,float x, float y)
{
	Render(pvMat,scale,x,y,m_fColor);
}

void GlAlphaTexRect::Render(const PVRTMat4& pvMat,float scale,float x, float y,float* pColor)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(m_RectObj.uiId);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D,m_uiTexture);


	PVRTMat4 transMat = PVRTMat4::Translation(x,y,0.0);
	PVRTMat4 scaleMat = PVRTMat4::Scale(scale,scale,1.0);
//	PVRTMat4 mat = pvMat*transMat*scaleMat;
	PVRTMat4 mat = transMat*pvMat*scaleMat;
	glUniformMatrix4fv(m_RectObj.uiMVP,1,GL_FALSE,mat.ptr());
	glUniform3fv(m_RectObj.uiColor,1,pColor);

	glBindBuffer(GL_ARRAY_BUFFER,m_uiVBO);

	glEnableVertexAttribArray(VERTEX_ARRAY);
	glEnableVertexAttribArray(TEXCOORD_ARRAY);

	glVertexAttribPointer(VERTEX_ARRAY,2,GL_FLOAT,GL_FALSE,4*sizeof(float),0);
	glVertexAttribPointer(TEXCOORD_ARRAY,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)(2*sizeof(float)));

	glDrawArrays(GL_TRIANGLES, 0,6);

	glDisableVertexAttribArray(VERTEX_ARRAY);
	glDisableVertexAttribArray(TEXCOORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER,0);

	glDisable(GL_BLEND);
}

void GlAlphaTexRect::RenderWithNoScale(const PVRTMat4& pvMat,float x, float y, float* pColor)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(m_RectObj.uiId);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D,m_uiTexture);

	PVRTMat4 transMat = PVRTMat4::Translation(x,y,0.0);
	PVRTMat4 scaleMat = PVRTMat4::Scale(m_fTexScreenWidthRatio,m_fTexScreenHeightRatio,1.0);
//	PVRTMat4 mat = pvMat*transMat*scaleMat;
	PVRTMat4 mat = transMat*pvMat*scaleMat;

	glUniformMatrix4fv(m_RectObj.uiMVP,1,GL_FALSE,mat.ptr());
	glUniform3fv(m_RectObj.uiColor,1,pColor);

	glBindBuffer(GL_ARRAY_BUFFER,m_uiVBO);

	glEnableVertexAttribArray(VERTEX_ARRAY);
	glEnableVertexAttribArray(TEXCOORD_ARRAY);

	glVertexAttribPointer(VERTEX_ARRAY,2,GL_FLOAT,GL_FALSE,4*sizeof(float),0);
	glVertexAttribPointer(TEXCOORD_ARRAY,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)(2*sizeof(float)));

	glDrawArrays(GL_TRIANGLES, 0,6);

	glDisableVertexAttribArray(VERTEX_ARRAY);
	glDisableVertexAttribArray(TEXCOORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER,0);

	glDisable(GL_BLEND);
}

void GlAlphaTexRect::Render(const PVRTMat4& pvMat,float scale,float rotZ,float x,float y)
{
	Render(pvMat,scale,rotZ,x,y,m_fColor);
}

void GlAlphaTexRect::Render(const PVRTMat4& pvMat,float scale,float rotZ,float x,float y,float* pColor)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(m_RectObj.uiId);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D,m_uiTexture);


	PVRTMat4 transMat = PVRTMat4::Translation(x,y,0.0);
	PVRTMat4 scaleMat = PVRTMat4::Scale(scale,scale,1.0);
	PVRTMat4 rotZMat = PVRTMat4::RotationZ(rotZ);

//	PVRTMat4 mat = pvMat*transMat*scaleMat*rotZMat;
	PVRTMat4 mat = transMat*pvMat*scaleMat*rotZMat;
	glUniformMatrix4fv(m_RectObj.uiMVP,1,GL_FALSE,mat.ptr());
	glUniform3fv(m_RectObj.uiColor,1,pColor);

	glBindBuffer(GL_ARRAY_BUFFER,m_uiVBO);

	glEnableVertexAttribArray(VERTEX_ARRAY);
	glEnableVertexAttribArray(TEXCOORD_ARRAY);

	glVertexAttribPointer(VERTEX_ARRAY,2,GL_FLOAT,GL_FALSE,4*sizeof(float),0);
	glVertexAttribPointer(TEXCOORD_ARRAY,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)(2*sizeof(float)));

	glDrawArrays(GL_TRIANGLES, 0,6);

	glDisableVertexAttribArray(VERTEX_ARRAY);
	glDisableVertexAttribArray(TEXCOORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER,0);

	glDisable(GL_BLEND);
}

void GlAlphaTexRect::SetColor(float r, float g, float b)
{
	m_fColor[0] = r;
	m_fColor[1] = g;
	m_fColor[2] = b;
}

int GlAlphaTexRect::LoadShaders()
{
	const char* aszAttribs[] = { "inVert","inCoord" };
	m_RectObj.uiId =LoadShaderFromString(pAlphaTexRectVertShader,pAlphaTexRectFragShader,aszAttribs,2);
	if(0 == m_RectObj.uiId)
		return -1;
	m_RectObj.uiMVP = glGetUniformLocation(m_RectObj.uiId,"mvpMat");
	m_RectObj.uiColor = glGetUniformLocation(m_RectObj.uiId,"color");
	glUniform1i(glGetUniformLocation(m_RectObj.uiId,"tex"),4);
	return 0;
}

void GlAlphaTexRect::LoadMeshes()
{
	float height = 1.0;
	float width = (float)m_iTexImageWidth/m_iTexImageHeight;
	float data[] = { -width,-height, 0.0, 0.0,
					 width, -height, 1.0, 0.0,
					 -width, height, 0.0, 1.0,
					 width, -height, 1.0, 0.0,
					 width, height,  1.0, 1.0,
					 -width, height, 0.0, 1.0};

	glGenBuffers(1, &m_uiVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int GlAlphaTexRect::LoadTextures(const char* texFile)
{
	int res = LoadAlphaTextureFromBMP(texFile, &m_uiTexture,m_iTexImageWidth,m_iTexImageHeight);
	m_fTexScreenWidthRatio = (float)m_iTexImageWidth/m_screenWidth;
	m_fTexScreenHeightRatio = (float)m_iTexImageHeight/m_screenHeight ;
//	printf("texWidth=%d,texHeight=%d,screenWidth=%d,screenHeight=%d\n",m_iTexImageWidth,m_iTexImageHeight,m_screenWidth,m_screenHeight);
//	printf("widthRatio=%f,heightRatio=%f\n",m_fTexScreenWidthRatio,m_fTexScreenHeightRatio);
	return res;
}
