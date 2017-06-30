/*
 * GlCautionTriangle.h
 *
 *  Created on: 2012-5-2
 *      Author: QiLiu
 */

#ifndef GlCautionTriangle_H_
#define GlCautionTriangle_H_
#include "GlShell.h"
#include "lineBorderOp.h"

class GlCautionTriangle : public GlShellApp
{
public:
	GlCautionTriangle();
	~GlCautionTriangle();

	void Init(float height,int lineWidth,int screenWidth,int screenHeight);
	void Update(PVRTMat4& PVMat,float posX, float posY);
	void Shutdown();

private:
	void CalTriPoints();
	void CalMarkPoints();
	void LoadShaders();
	void LoadTextures();
	void LoadMeshes();
private:
	struct{
		GLuint uiId;
		GLuint uiMVP;
		GLuint uiColor;
	}m_RenderObj;
	GLuint m_uiTexture;
private:
	float* m_pfTriLineBorders;
	unsigned short* m_pusTriIndex;
	unsigned short m_usTriBorderPtNum;
	unsigned short m_usTriIndexNum;

	float* m_pfMarkBorders;
	unsigned short* m_pusMarkIndex;
	unsigned short m_usMarkPtNum;
	unsigned short m_usMarkIndexNum;

	float m_fSymbolHeight;
	float m_fLineWidth;
	int m_iScreenLineWidth;

//	int m_iScreenWidth;
//	int m_iScreenHeight;
};

#endif /* GlCautionTriangle_H_ */
