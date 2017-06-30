#ifndef GLX100GRAPHIC_H_
#define GLX100GRAPHIC_H_

#include "GlGuideLineX100.h"

class GlX100Graphic{

public:
	static GlX100Graphic* getInstance();
	~GlX100Graphic();

	int Init(void* ctx,int screenWidth, int screenHeight, void* pDisplayContext=NULL);
	int Update(void* ctx);
	void Update_GuideLineCfg(void* ctx);

private:
	static GlX100Graphic* instance;
	GlX100Graphic();

	GlGuideLineX100 m_GuideLineX100;
};

#endif /* GLX100GRAPHIC_H_ */
