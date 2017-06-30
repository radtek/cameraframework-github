#include "CRenderUtility.h"
#include "CRenderLayout.h"
#include "CProgramPool.h"
#include "CTexturePool.h"


CRenderUtility::CRenderUtility()
: m_vbo(TRUE)
, m_ibo(TRUE)
{
}

CRenderUtility::~CRenderUtility()
{
}

void CRenderUtility::initialize()
{
	m_vbo.setup(NULL, 10, EVBFMT_POSITION3|EVBFMT_TEXCOORD0|EVBFMT_REPLACE3);
	m_ibo.setup(NULL, 10);

	//tagScreenContext *pScreenContext = CRenderEngineOS::getInstance()->getScreenContext();
	//m_matProject.makeOrthognal(0,pScreenContext->uiScreenWidth,0.0f, pScreenContext->uiScreenHeight,2.0f,1000.0f);

	CProgramPool::getInstance()->initialize();

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void CRenderUtility::unInitialize()
{
	m_vbo.release();
	m_ibo.release();

	CTexturePool::getInstance()->unInitialize();
	CProgramPool::getInstance()->unInitialize();
	CProgramPool::deleteInstance();
	CTexturePool::deleteInstance();
	CImageParser::close();
}

void CRenderUtility::render(Array<CRenderContainer*>& aryRndContainer)
{
	for( UInt32 i = 0 ; i < aryRndContainer.size(); ++i )
	{
		aryRndContainer[i]->render(m_vbo,m_ibo);
	}

/*	tagRenderContext *pRenderContext = CRenderEngineOS::getInstance()->getRenderContext();
	if ( eglSwapBuffers(pRenderContext->eglDisplay, pRenderContext->eglSurface) != EGL_TRUE )
	{
		EGLint error = eglGetError();

	}*/
}

