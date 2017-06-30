/*
 * GlAlphaTexRect.h
 *
 *  Created on: 2012-4-6
 *      Author: QiLiu
 */

#ifndef GLALPHATEXRECT_H_
#define GLALPHATEXRECT_H_

#include "GlShell.h"


class GlAlphaTexRect : public GlShellApp
{
public:
	GlAlphaTexRect();
	~GlAlphaTexRect();

	int Init(const char* texFile,int screenWidth,int screenHeight);
	//scale: scale ratio to the screen size
	void Render(const PVRTMat4& pvMat,float scale,float x, float y);
	void Render(const PVRTMat4& pvMat,float scale,float x, float y, float* pColor);
	//render as the size of the input texture image size
	void RenderWithNoScale(const PVRTMat4& pvMat,float x, float y, float* pColor);

	void Render(const PVRTMat4& pvMat,float scale,float rotZ,float x,float y);
	void Render(const PVRTMat4& pvMat,float scale,float rotZ,float x,float y,float* pColor);

	void SetColor(float r, float g, float b);

	void Shutdown();

private:
	int LoadShaders();
	/*
	 * depending on the parameter get from "LoadTextures",
	 * must call LoadTextures first before call this function
	 */
	void LoadMeshes();
	int LoadTextures(const char* texFile);

private:
	struct{
		GLuint uiId;
		GLuint uiMVP;
		GLuint uiColor;
	}m_RectObj;

	GLuint m_uiVBO;
	GLuint m_uiTexture;
	int m_iTexImageWidth;
	int m_iTexImageHeight;

	float m_fTexScreenWidthRatio;
	float m_fTexScreenHeightRatio;

	float m_fColor[3];

};

#endif /* GLALPHATEXRECT_H_ */
