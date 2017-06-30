/*
 * GlImage.h
 *
 *  Created on: 2012-5-10
 *      Author: QiLiu
 */

#ifndef GLIMAGE_H_
#define GLIMAGE_H_
#include "GlShell.h"

class GlImage : public GlShellApp
{
public:
	GlImage();
	~GlImage();
	void Init(const char* fileName);
	void Render(PVRTMat4& pvMat);
private:
	void LoadShaders();
	void LoadMeshes();
	void LoadTextures(const char* fileName);
	void Shutdown();
private:
	struct{
		GLuint uiId;
		GLuint uiMVP;
	}m_ImageObj;

	GLuint m_uiTexture;
	GLuint m_uiVBO;
};

#endif /* GLIMAGE_H_ */
