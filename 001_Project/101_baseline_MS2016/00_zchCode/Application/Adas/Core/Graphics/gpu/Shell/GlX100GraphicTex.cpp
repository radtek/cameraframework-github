#include "GlX100GraphicTex.h"
//#include <dir.h>
//#include <direct.h>
//#include <unistd.h>

GlX100GraphicTex* GlX100GraphicTex::instance = NULL;

GlX100GraphicTex* GlX100GraphicTex::getInstance()
{
	if(!instance)
	{
		instance = new GlX100GraphicTex;
		return instance;
	}
	else
		return instance;
}

GlX100GraphicTex::GlX100GraphicTex()
{
//	m_LangType = eEnglish;
}

GlX100GraphicTex::~GlX100GraphicTex()
{
	;
}

int GlX100GraphicTex::Init(void* ctx,int screenWidth, int screenHeight, void* pDisplayContext)
{
	printf("m_EnglishTex init begin!\n");
	m_EnglishTex.Init(GUIDELINETEXPATH_ENGLISH);
//	m_KoreaTex.Init(GUIDELINETEXPATH_KOREA);
	printf("m_EnglishTex init end!\n");

	return 0;
}

int GlX100GraphicTex::Update(void* ctx)
{
	PVRTMat4 mat = PVRTMat4::Identity();

	glEnable(GL_BLEND);
//	if(eEnglish == m_LangType)
//		m_EnglishTex.Render(mat);
//	else if(eKorean == m_LangType)
//		m_KoreaTex.Render(mat);
	m_EnglishTex.Render(mat);
	glDisable(GL_BLEND);
	return 0;
}
