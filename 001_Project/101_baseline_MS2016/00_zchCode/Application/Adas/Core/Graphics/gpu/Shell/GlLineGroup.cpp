/*
 * GlLineGroup.cpp
 *
 *  Created on: 2012-6-11
 *      Author: QiLiu
 */
#include "GlLineGroup.h"

#define VERTEX_ARRAY 0
#define TEXCOORD_ARRAY 1

const char* pAntiAliasedLineVertShader = "\
		attribute mediump vec4 myVert;\
		attribute mediump vec2 myUV;\
		uniform mediump vec2 imgSize;\
		varying mediump vec2 texCoord;\
		void main()\
		{\
		  float x = 2.0*myVert.x/imgSize.x-1.0;\
		  float y = 2.0 * myVert.y/imgSize.y - 1.0;\
		  gl_Position = vec4(x,y,0.0,1.0);\
		  texCoord = myUV;\
		}";

const char* pAntiAliasedLineFragShader = "\
	uniform lowp sampler2D tex;\
	uniform mediump vec3 color;\
	varying mediump vec2 texCoord;\
	void main()\
	{\
		gl_FragColor = vec4(color,texture2D(tex, texCoord).a);\
	}";

//gl_FragColor = vec4(color,texture2D(tex, texCoord).a);

GlLineGroup::GlLineGroup()
{
	m_pGroups = NULL;
	m_iGroupNum = 0;
}

GlLineGroup::~GlLineGroup()
{
	FreeLinesData();
	Shutdown();
}

void GlLineGroup::InitView()
{
	LoadShaders();
	LoadTextures();
}

void GlLineGroup::Shutdown()
{
	glDeleteTextures(1,&m_uiTexture);
	glDeleteProgram(m_RenderObj.uiId);
}

void GlLineGroup::FreeLinesData()
{
	if(m_pGroups)
	{
		for(int i=0;i<m_iGroupNum;i++)
			FreeGroupData(i);
		free(m_pGroups);
	}
}

void GlLineGroup::FreeGroupData(int index)
{
	if(m_pGroups[index].pLinePtNums)
		free(m_pGroups[index].pLinePtNums);

	int lineNums = m_pGroups[index].lineNums;
	if(m_pGroups[index].pLineData)
	{
		for(int i=0;i<lineNums;i++)
			free(m_pGroups[index].pLineData[i]);
		free(m_pGroups[index].pLineData);
	}

//	if(m_pGroups[index].pLineBorderData)
//	{
//		for(int i=0;i<lineNums;i++)
//			free(m_pGroups[index].pLineBorderData[i]);
//		free(m_pGroups[index].pLineBorderData);
//	}
//
//	if(m_pGroups[index].pLineBorderIndex)
//	{
//		for(int i=0;i<lineNums;i++)
//			free(m_pGroups[index].pLineBorderIndex[i]);
//		free(m_pGroups[index].pLineBorderIndex);
//	}
//
//	if(m_pGroups[index].pLineBorderIndexNum)
//		free(m_pGroups[index].pLineBorderIndexNum);
	if(m_pGroups[index].pBorderIndex)
		free(m_pGroups[index].pBorderIndex);
	if(m_pGroups[index].pBorderData)
		free(m_pGroups[index].pBorderData);
	if(m_pGroups[index].pLineBorderStartIndex)
		free(m_pGroups[index].pLineBorderStartIndex);
	if(m_pGroups[index].pLineIndexElemStartNum)
		free(m_pGroups[index].pLineIndexElemStartNum);
	if(m_pGroups[index].pLinePtElemStartNum)
		free(m_pGroups[index].pLinePtElemStartNum);
}

void GlLineGroup::LoadShaders()
{
	const char* aszAttribs[] = { "myVert","myUV" };
	m_RenderObj.uiId = LoadShaderFromString(pAntiAliasedLineVertShader,pAntiAliasedLineFragShader,aszAttribs,2);
	m_RenderObj.uiColor = glGetUniformLocation(m_RenderObj.uiId,"color");
//	m_RenderObj.uiMVP = glGetUniformLocation(m_RenderObj.uiId,"mvpMat");
	m_RenderObj.uiImgSize = glGetUniformLocation(m_RenderObj.uiId,"imgSize");

	glUniform1i(glGetUniformLocation(m_RenderObj.uiId,"tex"),2);

}

void GlLineGroup::LoadTextures()
{
	int width = 4;//m_iLinePixelWidth*2;
//	printf("texWidth: %d\n",m_iLinePixelWidth*2);
	int height = 2;
	int num = width*height;
	unsigned char* pData = (unsigned char*) malloc(num);
	unsigned char* pDst;
	int halfWidth = width/2;
	for(int i=0;i<height;i++)
	{
		pDst = pData + i*width;
		for(int j=0;j<halfWidth;j++)
			pDst[j] = 255;
		for(int j= halfWidth;j<width;j++)
			pDst[j] = 0;
	}

	glGenTextures(1, &m_uiTexture);
	glBindTexture(GL_TEXTURE_2D, m_uiTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pData);

	//glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	free(pData);
}

void GlLineGroup::Render(PVRTMat4& mat)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(m_RenderObj.uiId);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D,m_uiTexture);
	glUniform2f(m_RenderObj.uiImgSize,m_iScreenWidth-1,m_iScreenHeight-1);

	glEnableVertexAttribArray(VERTEX_ARRAY);
	glEnableVertexAttribArray(TEXCOORD_ARRAY);

	for(int i=m_iGroupNum-1;i>=0;i--)
	{
		RenderGroupLines(i);
	}

	glDisableVertexAttribArray(VERTEX_ARRAY);
	glDisableVertexAttribArray(TEXCOORD_ARRAY);
	glDisable(GL_BLEND);
}

void GlLineGroup::RenderGroupLines(int index)
{
	linesData lineGroup = m_pGroups[index];
	glUniform3fv(m_RenderObj.uiColor,1,lineGroup.color);
	glVertexAttribPointer(VERTEX_ARRAY, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)lineGroup.pBorderData);
	glVertexAttribPointer(TEXCOORD_ARRAY,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)(&lineGroup.pBorderData[2]));
	glDrawElements(GL_TRIANGLES,lineGroup.pBorderIndexNum,GL_UNSIGNED_SHORT,lineGroup.pBorderIndex);
}
