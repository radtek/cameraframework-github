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

	const char* Attribs[2] = { "myVert","myUV" };
	const char* vertexShader = "\
	attribute mediump vec4 myVert;\
	attribute mediump vec4 myUV;\
	uniform mediump vec2 imgSize;\
	varying mediump vec2 texCoord;\
	void main()\
	{\
		float x = 2.0*myVert.x/imgSize.x-1.0;\
		float y = 2.0 * myVert.y/imgSize.y - 1.0;\
		gl_Position = vec4(x,-y,0.0,1.0);\
		texCoord = myUV.st;\
	}";

	const char* fragmentShader = "\
	uniform lowp sampler2D tex;\
	uniform mediump float myAlpha;\
	varying mediump vec2 texCoord;\
	void main()\
	{\
		gl_FragColor = vec4(texture2D(tex, texCoord).rgb,myAlpha);\
	}";
};

}//namespace AGraphic
}//namespace AFramework
}//namespace Adas
}//namespace Harman

#endif  //__HARMAN_ADAS_AFRAMEWORK_AGRAPGIC_GUIDELINE_H_
