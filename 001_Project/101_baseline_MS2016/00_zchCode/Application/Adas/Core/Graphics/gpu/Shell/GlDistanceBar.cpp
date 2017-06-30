#include "GlDistanceBar.h"

const char* pDistBarVertShader = "\
		attribute mediump vec4	myVertex;\
		attribute mediump float myAlpha;\
		uniform mediump mat4	myPMVMatrix;\
		varying mediump float alpha;\
		void main(void)\
		{\
			gl_Position = myPMVMatrix * myVertex;\
			alpha = myAlpha;\
		}";

const char* pDistBarFragShader = "\
		uniform mediump vec3 color;\
		varying mediump float alpha;\
		void main (void)\
		{\
			gl_FragColor = vec4(color, alpha);\
		}";


#define BOTTOMLEFT 0
#define BOTTOMRIGHT 1
#define TOPLEFT 2
#define TOPRIGHT 3

#define VERTEXSTRIDE 3
#define POSX 0
#define POSY 1
#define ALPHA 2

#define VERTEX_ARRAY 0
#define ALPHA_ARRAY 1

GlDistanceBar::GlDistanceBar()
{
	m_iBottomPosX = 400;
	m_iBottomPosY = 480;
	m_iBottomWidth = 400;
	m_iTopPosX = 600;
	m_iTopPosY = 200;
	m_iTopWidth = 100;

	m_fColor[0] = 0.5;
	m_fColor[1] = 0.5;
	m_fColor[2] = 0.8;
	m_fBottomAlpha = 0.8;
	m_fTopAlpha = 0.3;

	m_screenWidth = 800;
	m_screenHeight = 480;

//	m_bRenderEnable = true;
}
GlDistanceBar::~GlDistanceBar()
{
	;
}

void GlDistanceBar::Init(void* ctx)
{
//	overlay_ctx = (overlay_context_t*)ctx;
////	pResult = (FCW_Result_Data*) overlay_ctx->result;
//	pParam = (overlay_FCW_t*)(overlay_ctx->fcwParam);
	LoadShaders();
	LoadMeshes();
}

void GlDistanceBar::Update(int posX, int posY, int width)
{
	SetTopParam(posX, posY, width);
}

void GlDistanceBar::Render(PVRTMat4& mvpMat)
{
//	UpdateAccordResults();
//	printf("distBar update begin!\n");
//	if(!m_bRenderEnable)
//		return;

	glUseProgram(m_distBarObj.uiId);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glEnableVertexAttribArray(VERTEX_ARRAY);
	glEnableVertexAttribArray(ALPHA_ARRAY);
	glVertexAttribPointer(VERTEX_ARRAY, 2, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(m_fVertexArray));
	glVertexAttribPointer(ALPHA_ARRAY, 1, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(&(m_fVertexArray[2])));

	glUniformMatrix4fv(m_distBarObj.uiMVP, 1, GL_FALSE, mvpMat.ptr());
	glUniform3fv(m_distBarObj.uiColor,1,m_fColor);
//	glDrawArrays( GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6 ,GL_UNSIGNED_SHORT, m_usIndexArray);

	glDisableVertexAttribArray(VERTEX_ARRAY);
	glDisableVertexAttribArray(ALPHA_ARRAY);
}

int GlDistanceBar::LoadShaders()
{
	const char* aszAttribs[] = {"myVertex","myAlpha"};

	if(!(m_distBarObj.uiId = LoadShaderFromString(pDistBarVertShader,pDistBarFragShader,aszAttribs,2)))
	{
		printf("Load distBar shader failed!\n");
			return -1;
	}
	m_distBarObj.uiMVP = glGetUniformLocation(m_distBarObj.uiId,"myPMVMatrix");
	m_distBarObj.uiColor = glGetUniformLocation(m_distBarObj.uiId,"color");
	return 0;
}

int GlDistanceBar::LoadMeshes()
{
	UpdateVertexArray();
	m_usIndexArray[0] = 0;
	m_usIndexArray[1] = 1;
	m_usIndexArray[2] = 3;
	m_usIndexArray[3] = 3;
	m_usIndexArray[4] = 2;
	m_usIndexArray[5] = 0;
	return 0;
}

void GlDistanceBar::UpdateVertexArray()
{
	UpdateBottomVertexPos();
	UpdateTopVertexPos();
	m_fVertexArray[BOTTOMLEFT*VERTEXSTRIDE+ALPHA] = m_fBottomAlpha;
	m_fVertexArray[BOTTOMRIGHT*VERTEXSTRIDE+ALPHA] = m_fBottomAlpha;

	m_fVertexArray[TOPLEFT*VERTEXSTRIDE+ALPHA] = m_fTopAlpha;
	m_fVertexArray[TOPRIGHT*VERTEXSTRIDE+ALPHA] = m_fTopAlpha;

//	for(int i=0;i<4;i++)
//	{
//		printf("x=%f, y=%f, alpha=%f\n",m_fVertexArray[i*3],m_fVertexArray[i*3+1],m_fVertexArray[i*3+2]);
//	}
}

void GlDistanceBar::UpdateBottomVertexPos()
{
	m_fVertexArray[BOTTOMLEFT*VERTEXSTRIDE+POSX] = ( 2.0 * m_iBottomPosX - m_iBottomWidth) / m_screenWidth - 1.0;
	m_fVertexArray[BOTTOMLEFT*VERTEXSTRIDE+POSY] = 1.0 - 2.0 * m_iBottomPosY / m_screenHeight;

	m_fVertexArray[BOTTOMRIGHT*VERTEXSTRIDE+POSX] = ( 2.0 * m_iBottomPosX + m_iBottomWidth) / m_screenWidth - 1.0;
	m_fVertexArray[BOTTOMRIGHT*VERTEXSTRIDE+POSY] = m_fVertexArray[BOTTOMLEFT*VERTEXSTRIDE+POSY];
}

void GlDistanceBar::UpdateTopVertexPos()
{
	m_fVertexArray[TOPLEFT*VERTEXSTRIDE+POSX] = ( 2.0 * m_iTopPosX - m_iTopWidth) / m_screenWidth - 1.0;
	m_fVertexArray[TOPLEFT*VERTEXSTRIDE+POSY] = 1.0 - 2.0 * m_iTopPosY / m_screenHeight;

	m_fVertexArray[TOPRIGHT*VERTEXSTRIDE+POSX] = ( 2.0 * m_iTopPosX + m_iTopWidth) / m_screenWidth - 1.0;
	m_fVertexArray[TOPRIGHT*VERTEXSTRIDE+POSY] = m_fVertexArray[TOPLEFT*VERTEXSTRIDE+POSY];
}

void GlDistanceBar::UpdateParamiv(distBarParam_t type,int* param)
{
	switch(type)
	{
	case eBottomPos:
		UpdateBottomPos(param[0],param[1]);
		break;
	case eBottomWidth:
		UpdateBottomWidth(param[0]);
		break;
	case eTopPos:
		UpdateTopPos(param[0],param[1]);
		break;
	case eTopWidth:
		UpdateTopWidth(param[0]);
		break;
	default:
		break;
	}
}

void GlDistanceBar::UpdateParamfv(distBarParam_t type, float* param)
{
	switch(type)
	{
	case eBottomAlpha:
		UpdateBottomAlpha(param[0]);
		break;
	case eTopAlpha:
		UpdateTopAlpha(param[0]);
		break;
	case eColor:
		UpdateColor(param[0],param[1],param[2]);
		break;
	default:
		break;
	}
}

void GlDistanceBar::SetTopParam(int posX, int posY, int width)
{
	m_iTopPosX = posX;
	m_iTopPosY = posY;
	m_iTopWidth = width;
	UpdateTopVertexPos();
}

void GlDistanceBar::SetBottomParam(int posX, int posY, int width)
{
	m_iBottomPosX = posX;
	m_iBottomPosY = posY;
	m_iBottomWidth = width;
	UpdateBottomVertexPos();
}

void GlDistanceBar::UpdateTopPos(int posX, int posY)
{
	m_iTopPosX = posX;
	m_iTopPosY = posY;
	UpdateTopVertexPos();
}

void GlDistanceBar::UpdateTopWidth(int width)
{
	m_iTopWidth = width;
	UpdateBottomVertexPos();
}

void GlDistanceBar::UpdateBottomPos(int posX, int posY)
{
	m_iBottomPosX = posX;
	m_iBottomPosY = posY;
	UpdateBottomVertexPos();
}
void GlDistanceBar::UpdateBottomWidth(int width)
{
	m_iBottomWidth = width;
	UpdateBottomVertexPos();
}

void GlDistanceBar::UpdateColor(float r, float g, float b)
{
	m_fColor[0] = r;
	m_fColor[1] = g;
	m_fColor[2] = b;
}

void GlDistanceBar::UpdateBottomAlpha(float alpha)
{
	m_fBottomAlpha = alpha;
	m_fVertexArray[BOTTOMLEFT*VERTEXSTRIDE+ALPHA] = m_fBottomAlpha;
	m_fVertexArray[BOTTOMRIGHT*VERTEXSTRIDE+ALPHA] = m_fBottomAlpha;
}

void GlDistanceBar::UpdateTopAlpha(float alpha)
{
	m_fTopAlpha = alpha;
	m_fVertexArray[TOPLEFT*VERTEXSTRIDE+ALPHA] = m_fTopAlpha;
	m_fVertexArray[TOPLEFT*VERTEXSTRIDE+ALPHA] = m_fTopAlpha;
}

//void GlDistanceBar::UpdateAccordResults()
//{
//	int m_iTopPosX;
//	int m_iTopPosY;
//	int m_iTopWidth;
//	m_iTopPosX = pResult->car_rect_x + pResult->car_rect_width * 0.5;
//	m_iTopPosY = pResult->car_rect_y + pResult->car_rect_height;
//	m_iTopWidth = pResult->car_rect_width;
//	UpdateTopVertexPos();
//}
