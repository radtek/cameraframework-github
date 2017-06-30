#ifndef GLX100GRAPHICTEX_H_
#define GLX100GRAPHICTEX_H_

#include "GlImage.h"
#include "RVSGuideLineDefine.h"

class GlX100GraphicTex{

public:
	static GlX100GraphicTex* getInstance();
	~GlX100GraphicTex();

	int Init(void* ctx,int screenWidth, int screenHeight, void* pDisplayContext=NULL);
	int Update(void* ctx);
//	void Update_GuideLineCfg(void* ctx);
//	void LanguageTypeUpdate(int type) { m_LangType = (LanguageType_t) type;}

private:
	static GlX100GraphicTex* instance;
	GlX100GraphicTex();

	GlImage m_EnglishTex;
//	GlImage m_KoreaTex;

//	LanguageType_t m_LangType;
};


#endif /* GLX100GRAPHICTEX_H_ */
