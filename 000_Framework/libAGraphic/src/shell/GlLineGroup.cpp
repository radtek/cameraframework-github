/*
 * GlLineGroup.cpp
 *
 *  Created on: 2012-6-11
 *      Author: QiLiu
 */
#include "GlLineGroup.h"

#define VERTEX_ARRAY 0
#define TEXCOORD_ARRAY 1
#if 1
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
#else

const char* pAntiAliasedLineVertShader = "\
		attribute mediump vec4 myVert;\
		uniform mediump vec2 imgSize;\
		void main()\
		{\
		  float x = 2.0*myVert.x/imgSize.x-1.0;\
		  float y = 2.0 * myVert.y/imgSize.y - 1.0;\
		  gl_Position = vec4(x,y,0.0,1.0);\
		}";

const char* pAntiAliasedLineFragShader = "\
	uniform mediump vec3 color;\
	void main()\
	{\
		gl_FragColor = vec4(color,1);\
	}";


#endif

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
			//pDst[j] = 0;
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

void GlLineGroup::RenderTest(PVRTMat4& mat)
{
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(m_RenderObj.uiId);
	//glActiveTexture(GL_TEXTURE2);
	//glBindTexture(GL_TEXTURE_2D,m_uiTexture);
	glUniform2f(m_RenderObj.uiImgSize,m_iScreenWidth-1,m_iScreenHeight-1);

	glEnableVertexAttribArray(VERTEX_ARRAY);
	//glEnableVertexAttribArray(TEXCOORD_ARRAY);

	for(int i=0;i<4;i++)
	{
		RenderLinesTest(i);
	}

	glDisableVertexAttribArray(VERTEX_ARRAY);
	//glDisableVertexAttribArray(TEXCOORD_ARRAY);

	//glDisable(GL_BLEND);
}
//only use alpha value from tex image,so when "calc" a tex image for guide line ,only set the alpha value
//and in texcoord_array, just pick a pixle which has the target value(only have 2 value in the whole texture image)
//so we only got two pixle from tex pic to rend the guide line
void GlLineGroup::RenderGroupLines(int index)
{
	linesData lineGroup = m_pGroups[index];
	glUniform3fv(m_RenderObj.uiColor,1,lineGroup.color);
	glVertexAttribPointer(VERTEX_ARRAY, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)lineGroup.pBorderData);
	glVertexAttribPointer(TEXCOORD_ARRAY,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)(&lineGroup.pBorderData[2]));
	glDrawElements(GL_TRIANGLES,lineGroup.pBorderIndexNum,GL_UNSIGNED_SHORT,lineGroup.pBorderIndex);
}
//left-bottom point + left-top point = left line
#define RVS_DISPLAY_LINE_lbx (RVS_DISPLAY_LEFT_MAX+30)
#define RVS_DISPLAY_LINE_lby (RVS_DISPLAY_BOTTOM_MAX+30)
#define RVS_DISPLAY_LINE_ltx (RVS_DISPLAY_LEFT_MAX+40)
#define RVS_DISPLAY_LINE_lty (RVS_DISPLAY_TOP_MAX-30)
//right line
#define RVS_DISPLAY_LINE_rbx (RVS_DISPLAY_RIGHT_MAX-30)
#define RVS_DISPLAY_LINE_rby (RVS_DISPLAY_BOTTOM_MAX+30)
#define RVS_DISPLAY_LINE_rtx (RVS_DISPLAY_RIGHT_MAX-40)
#define RVS_DISPLAY_LINE_rty (RVS_DISPLAY_TOP_MAX-30)
//bottom line
#define RVS_DISPLAY_LINE_blx  RVS_DISPLAY_LINE_lbx
#define RVS_DISPLAY_LINE_bly (RVS_DISPLAY_LINE_lby +10)
#define RVS_DISPLAY_LINE_brx  RVS_DISPLAY_LINE_rbx
#define RVS_DISPLAY_LINE_bry (RVS_DISPLAY_LINE_rby +10)
//top line
#define RVS_DISPLAY_LINE_tlx  RVS_DISPLAY_LINE_ltx
#define RVS_DISPLAY_LINE_tly (RVS_DISPLAY_LINE_lty -10)
#define RVS_DISPLAY_LINE_trx  RVS_DISPLAY_LINE_rtx
#define RVS_DISPLAY_LINE_try (RVS_DISPLAY_LINE_rty -10)

float testLineVertex[]={
	//left line
	RVS_DISPLAY_LINE_lbx,RVS_DISPLAY_LINE_lby,   RVS_DISPLAY_LINE_ltx,RVS_DISPLAY_LINE_lty,
	//right
	RVS_DISPLAY_LINE_rbx,RVS_DISPLAY_LINE_rby,  RVS_DISPLAY_LINE_rtx,RVS_DISPLAY_LINE_rty,
	//bottom
	RVS_DISPLAY_LINE_blx,RVS_DISPLAY_LINE_bly,	RVS_DISPLAY_LINE_brx,RVS_DISPLAY_LINE_bry,
	//top
	RVS_DISPLAY_LINE_tlx,RVS_DISPLAY_LINE_tly,   RVS_DISPLAY_LINE_trx,RVS_DISPLAY_LINE_try,
};

float testLineCoord[]={
	0,1,
	0,1,
	2,2,
	2,2
};
unsigned short testLineIndex[]={
	0,1,
	2,3,
	4,5,
	6,7,
};

unsigned short testLinePart[]={
	0,1
};

#define RVS_COLOR_RED                   {1.0,0.0,0.0}
#define RVS_COLOR_YELLOW                {1.0,1.0,0.0}
#define RVS_COLOR_GREEN                 {0.0,1.0,0.0}
#define RVS_COLOR_BLACK                 {0.0,0.0,0.0}
color3 colorTable[]=
{
	RVS_COLOR_YELLOW,
	RVS_COLOR_YELLOW,
	RVS_COLOR_RED,
	RVS_COLOR_GREEN,
};
#define DOT_LINE   0
#define NORMAL_LINE 1 
int lineStyle[]=
{
	NORMAL_LINE,
	NORMAL_LINE,
	DOT_LINE,
	DOT_LINE
};
#define DOT_LENGH 10
typedef struct tagLinePoints
{
	float startpointX;
	float startpointY;
	float stoppointX;
	float stoppointY;
}tLinePoints;

//struct Edit point,must the point of the line top and bottom
typedef struct tagEditPoints
{
	float editX;
	float editY;
}tEditPoints;

static void drawDotLine(float *vertex,GLuint uiColour,int index)
{
	float startpointX = vertex[0];
	float startpointY = vertex[1];
	float stoppointX = vertex[2];
	float stoppointY = vertex[3];
	int   lenSegNum = 0;
	float len = 0.0;
	len = stoppointX - startpointX;
	if(len<0.0)
	{
		len = -len;
	}

	lenSegNum = len/DOT_LENGH;
	tLinePoints *pLinePoints = (tLinePoints *)malloc(lenSegNum*sizeof(tLinePoints));
	unsigned short *LineIndex = (unsigned short *)malloc(lenSegNum*2*sizeof(unsigned short));
	for(int i=0;i<lenSegNum;i++)
	{
		pLinePoints[i].startpointX=startpointX+i*DOT_LENGH;
		pLinePoints[i].startpointY=startpointY;
		LineIndex[2*i]=2*i;
		pLinePoints[i].stoppointX=startpointX+(i+1)*DOT_LENGH;
		pLinePoints[i].stoppointY=stoppointY;
		LineIndex[2*i+1]=2*i+1;
		if((i%2)==0)
		{
			glUniform3fv(uiColour,1,colorTable[index]);
			glVertexAttribPointer(VERTEX_ARRAY, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void *)&pLinePoints[i]);
			glLineWidth(RVS_LINE_WIDTH);
			glDrawElements(GL_LINES,2,GL_UNSIGNED_SHORT,&LineIndex[0]);
		}
		else
		{
			//nothing to draw
		}	
	}

	free(pLinePoints);
}
int g_testLine=0;
int g_testDotLine=0;
void GlLineGroup::RenderLinesTest(int index)
{	
	g_testLine++;
	g_testDotLine++;
	switch(lineStyle[index])
	{
	case NORMAL_LINE:
		glUniform3fv(m_RenderObj.uiColor,1,colorTable[index]);
		glVertexAttribPointer(VERTEX_ARRAY, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)&testLineVertex[4*index]);
		glLineWidth(RVS_LINE_WIDTH);
		glDrawElements(GL_LINES,2,GL_UNSIGNED_SHORT,testLinePart);
		break;
	case DOT_LINE:
		drawDotLine(&testLineVertex[4*index],(GLuint)m_RenderObj.uiColor,index);
		break;
	default:
		break;
	}
	//glVertexAttribPointer(VERTEX_ARRAY, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)&testLineVertex[4*index]);
	//glVertexAttribPointer(TEXCOORD_ARRAY,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)&testLineCoord[4*index]);

	//glDrawArrays(GL_TRIANGLES,0,3);
}
