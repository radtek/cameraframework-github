#ifndef GLDISTANCEBAR_H_
#define GLDISTANCEBAR_H_

//#include "GlBase.h"
#include "GlShell.h"
//#include "Gfx_ForwardCollision.h"

typedef enum distBarParam{
	eBottomPos,
	eBottomWidth,
	eBottomAlpha,
	eTopPos,
	eTopWidth,
	eTopAlpha,
	eColor,
}distBarParam_t;

class GlDistanceBar : public GlShellApp
{
public:
	GlDistanceBar();
	~GlDistanceBar();

	void Init(void* ctx);
	void Render(PVRTMat4& mvpMat);
	void Update(int posX, int posY, int width);

	void UpdateParamiv(distBarParam_t type,int* param);
	void UpdateParamfv(distBarParam_t type, float* param);

private:
	void SetTopParam(int posX, int posY, int width);
	void SetBottomParam(int posX, int posY, int width);

	void UpdateTopPos(int posX, int posY);
	void UpdateTopWidth(int width);
	void UpdateBottomPos(int posX, int posY);
	void UpdateBottomWidth(int width);

	void UpdateColor(float r, float g, float b);
	void UpdateBottomAlpha(float alpha);
	void UpdateTopAlpha(float alpha);

	void UpdateVertexArray();

	void UpdateBottomVertexPos();
	void UpdateTopVertexPos();

	int LoadShaders();
	int LoadMeshes();

//	void UpdateAccordResults();

private:
	int m_iBottomPosX;
	int m_iBottomPosY;
	int m_iBottomWidth;
	int m_iTopPosX;
	int m_iTopPosY;
	int m_iTopWidth;

	float m_fColor[3];
	float m_fBottomAlpha;
	float m_fTopAlpha;

	float m_fVertexArray[12]; //(x,y,alpha)
	unsigned short m_usIndexArray[6];

//	bool m_bRenderEnable;

	struct{
		GLuint uiId;
		GLuint uiMVP;
		GLuint uiColor;
	}m_distBarObj;

//	overlay_context_t* overlay_ctx;
//	FCW_Result_Data* pResult;
//	overlay_FCW_t* pParam;
};

#endif /* GLDISTANCEBAR_H_ */
