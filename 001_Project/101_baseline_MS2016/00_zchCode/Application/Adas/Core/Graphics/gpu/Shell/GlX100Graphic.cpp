#include "GlX100Graphic.h"

GlX100Graphic* GlX100Graphic::instance = NULL;

GlX100Graphic* GlX100Graphic::getInstance()
{
	if(!instance)
	{
		instance = new GlX100Graphic;
		return instance;
	}
	else
		return instance;
}

GlX100Graphic::GlX100Graphic()
{
	;
}

GlX100Graphic::~GlX100Graphic()
{
	;
}

int GlX100Graphic::Init(void* ctx,int screenWidth, int screenHeight, void* pDisplayContext)
{
	rvs_guideline_ctx_t* pCtx = (rvs_guideline_ctx_t*)ctx;
//	printf("width=%d, height=%d\n",screenWidth, screenHeight);
	m_GuideLineX100.SetWindowParam(screenWidth,screenHeight);
	m_GuideLineX100.InitTest_test(&(pCtx->guidelineCfg));
	return 0;
}

int GlX100Graphic::Update(void* ctx)
{
	PVRTMat4 mat = PVRTMat4::Identity();
	m_GuideLineX100.Render(mat);
//	int err = glGetError();
//	printf("err = %d\n",err);
	return 0;
}

void GlX100Graphic::Update_GuideLineCfg(void* ctx)
{
	rvs_guideline_ctx_t* pCtx = (rvs_guideline_ctx_t*)ctx;
	rvs_GuideLineCfg_t* pCfg = &(pCtx->guidelineCfg);
	int copyLeftPos[GUIDELINE_GROUP_NUM][4];
	int copyRightPos[GUIDELINE_GROUP_NUM][4];
	int** pCfgLeftPos = pCfg->m_iLeftPos;
	int** pCfgRightPos = pCfg->m_iRightPos;
	for(int i=0;i<GUIDELINE_GROUP_NUM;i++)
	{
		memcpy(copyLeftPos[i],pCfgLeftPos[i],4*sizeof(int));
		memcpy(copyRightPos[i],pCfgRightPos[i],4*sizeof(int));
	}
	m_GuideLineX100.UpdateGuideLineInfo(GUIDELINE_GROUP_NUM,(int**)copyLeftPos,(int**)copyRightPos);
}
