#ifndef __HARMAN_ADAS_AFRAMEWORK_AGRAPGIC_GUIDELINE_H_
#define __HARMAN_ADAS_AFRAMEWORK_AGRAPGIC_GUIDELINE_H_

#include "Calculator.h"

using namespace std;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AGraphic {

class GuideLine
{
public:
	void GuideLineRender(guidelineinfo infos);
	void GuideLineHide();

	GuideLine();

	~GuideLine();

private:
	void GenTexture();
	void LoadProgram();
	GLuint LoadShaders(const char* vertexShaderSrc,const char* fragmentShaderSrc);
	void RenderGroupLines(int index);

private:
	GLuint programObject;
	GLuint GuideLineTexture;
	guidelineinfo info;
	Calculator* calpointer=nullptr;
};

}//namespace AGraphic
}//namespace AFramework
}//namespace Adas
}//namespace Harman

#endif  //__HARMAN_ADAS_AFRAMEWORK_AGRAPGIC_GUIDELINE_H_
