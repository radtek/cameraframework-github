/*
 * GlCautionTriangle.cpp
 *
 *  Created on: 2012-5-2
 *      Author: QiLiu
 */

#include "GlCautionTriangle.h"

const char* pLineVertShader = "\
			attribute mediump vec4 inVert;\
			attribute mediump vec2 inCoord;\
			uniform mediump mat4 mvpMat;\
			varying mediump vec2 texCoord;\
			void main()\
			{\
			  gl_Position = mvpMat*inVert;\
			  texCoord = inCoord;\
			}";

const char* pLineFragShader = "\
		varying mediump vec2 texCoord;\
		uniform lowp sampler2D tex;\
		uniform mediump vec3 color;\
		void main()\
		{\
			float alpha = texture2D(tex,texCoord).a;\
			gl_FragColor = vec4(color, alpha);\
		}";

#define VERTEX_ARRAY 0
#define TEXCOORD_ARRAY 1

GlCautionTriangle::GlCautionTriangle()
{
	m_pfTriLineBorders = NULL;
	m_pusTriIndex = NULL;
	m_usTriBorderPtNum = 0;
	m_usTriIndexNum = 0;
	m_fSymbolHeight = 0.f;
	m_fLineWidth = 0.f;

	m_pfMarkBorders = NULL;
	m_pusMarkIndex = NULL;
	m_usMarkPtNum = 0.f;
	m_usMarkIndexNum = 0.f;
}

GlCautionTriangle::~GlCautionTriangle()
{
	if(m_pfTriLineBorders)
		free(m_pfTriLineBorders);
	if(m_pusTriIndex)
		free(m_pusTriIndex);
	if(m_pfMarkBorders)
		free(m_pfMarkBorders);
	if(m_pusMarkIndex)
		free(m_pusMarkIndex);
	Shutdown();
}

void GlCautionTriangle::Init(float height,int lineWidth,int screenWidth,int screenHeight)
{
	m_fSymbolHeight = height;
	m_iScreenLineWidth = lineWidth;
	m_fLineWidth = 2.0*lineWidth/screenWidth*2.0;
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	LoadShaders();
	LoadTextures();
	LoadMeshes();
}

void GlCautionTriangle::Shutdown()
{
	glDeleteTextures(1,&m_uiTexture);
	glDeleteShader(m_RenderObj.uiId);
}

void GlCautionTriangle::Update(PVRTMat4& PVMat,float posX, float posY)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(m_RenderObj.uiId);
	glBindTexture(GL_TEXTURE_2D,m_uiTexture);
	glUniform3f(m_RenderObj.uiColor,1.0,0.0,0.0);

	PVRTMat4 transMat = PVRTMat4::Translation(posX,posY,0.0);
	PVRTMat4 mat = PVMat * transMat;
	glUniformMatrix4fv(m_RenderObj.uiMVP,1,GL_FALSE,mat.ptr());

	glEnableVertexAttribArray(VERTEX_ARRAY);
	glEnableVertexAttribArray(TEXCOORD_ARRAY);
	//lines
	glVertexAttribPointer(VERTEX_ARRAY, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)m_pfTriLineBorders);
	glVertexAttribPointer(TEXCOORD_ARRAY,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)(&m_pfTriLineBorders[2]));
	glDrawElements(GL_TRIANGLES,m_usTriIndexNum,GL_UNSIGNED_SHORT,m_pusTriIndex);

	glVertexAttribPointer(VERTEX_ARRAY, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)m_pfMarkBorders);
	glVertexAttribPointer(TEXCOORD_ARRAY,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)(&m_pfMarkBorders[2]));
	glDrawElements(GL_TRIANGLES,m_usMarkIndexNum,GL_UNSIGNED_SHORT,m_pusMarkIndex);

	glDisableVertexAttribArray(VERTEX_ARRAY);
	glDisableVertexAttribArray(TEXCOORD_ARRAY);

	glDisable(GL_BLEND);
}

void GlCautionTriangle::CalTriPoints()
{
	float data[6];
	float triHalfLength = m_fSymbolHeight/sqrt(3.0);
	float halfHeight = m_fSymbolHeight/2.0;
	data[0] = -triHalfLength;
	data[1] = -halfHeight;
	data[2] = triHalfLength;
	data[3] = -halfHeight;
	data[4] = 0.0f;
	data[5] = halfHeight;

	lineBorderOp lineBorder;
	lineBorder.CalLine2DBorderPtNum_Loop(3,m_usTriBorderPtNum,m_usTriIndexNum);
	if(m_pfTriLineBorders)
		free(m_pfTriLineBorders);
	m_pfTriLineBorders = (float*)malloc(m_usTriBorderPtNum*sizeof(float));
	if(m_pusTriIndex)
		free(m_pusTriIndex);
	m_pusTriIndex = (unsigned short*)malloc(m_usTriIndexNum*sizeof(unsigned short));
	lineBorder.CalLine2DBorder_Loop(data,3,m_fLineWidth,0,m_pfTriLineBorders,m_pusTriIndex);
}

void GlCautionTriangle::CalMarkPoints()
{
	m_usMarkPtNum = 8*4;
	m_usMarkIndexNum = 12;

	if(m_pfMarkBorders)
		free(m_pfMarkBorders);
	m_pfMarkBorders = (float*)malloc(m_usMarkPtNum*sizeof(float));

	if(m_pusMarkIndex)
		free(m_pusMarkIndex);
	m_pusMarkIndex = (unsigned short*)malloc(m_usMarkIndexNum*sizeof(unsigned short));

	float data[4];
	float halfHeight = m_fSymbolHeight/2.0;
	data[0] = 0.0;
	data[1] = halfHeight*0.5;
	data[2] = 0.0;
	data[3] = -halfHeight*0.45;
	lineBorderOp lineBorder;
	lineBorder.CalLine2DBorder(data,2,m_fLineWidth,0,m_pfMarkBorders,m_pusMarkIndex);

	data[0] = 0.0;
	data[1] = -halfHeight*0.6;
	data[2] = 0.0;
	data[3] = -halfHeight*0.8;
	lineBorder.CalLine2DBorder(data,2,m_fLineWidth,4,&m_pfMarkBorders[16],&m_pusMarkIndex[6]);
}

void GlCautionTriangle::LoadShaders()
{
	const char* aszAttribs[] = { "inVert","inCoord" };
	m_RenderObj.uiId =LoadShaderFromString(pLineVertShader,pLineFragShader,aszAttribs,2);
	m_RenderObj.uiMVP = glGetUniformLocation(m_RenderObj.uiId,"mvpMat");
	m_RenderObj.uiColor = glGetUniformLocation(m_RenderObj.uiId,"color");
//	printf("uiId = %d,uiMVP = %d,uiColor = %d\n",m_RenderObj.uiId,m_RenderObj.uiMVP,m_RenderObj.uiColor);
}

void GlCautionTriangle::LoadTextures()
{
	int texWidth = m_iScreenLineWidth*2;
	int texHeight = 2;
	unsigned char* pData = (unsigned char*)malloc(texWidth*texHeight);
	int index = 0;
	for(int i=0;i<texHeight;i++)
		for(int j=0;j<texWidth;j++)
		{
			if(j<m_iScreenLineWidth)
				pData[index] = 255;
			else
				pData[index] = 0;
			index++;
		}
	glGenTextures(1, &m_uiTexture);
	glBindTexture(GL_TEXTURE_2D,m_uiTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, texWidth, texHeight, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pData);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D,0);
//	int err = glGetError();
//	printf("load texture: err = %d,texWidth = %d\n",err,texWidth);
}

void GlCautionTriangle::LoadMeshes()
{
	CalTriPoints();
	CalMarkPoints();
}
