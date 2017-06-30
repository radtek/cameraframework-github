#pragma once

#include "common.h"
#include "CRenderImage.h"
#include "CRenderContainer.h"
#include "../resource/CVertexBuffer.h"
#include "../resource/CIndexBuffer.h"
#include "../resource/CCacheTexture.h"
#include "../resource/CCacheProgram.h"
#include "../resource/CGLSLProgram.h"
#include "../resource/CImageParser.h"


	enum EInputType
	{
		EIT_TOUCHPRESS,
		EIT_TOUCHRELEASE,
		EIT_TOUCHMOVE
	};

	class CRenderLayout;
class CRenderUtility
{
public:
	CRenderUtility();
	~CRenderUtility();

public:
	void initialize();
	void unInitialize();

	void render(Array<CRenderContainer*>& aryRndImage);

protected:
	CVertexBuffer			m_vbo;
	CIndexBuffer			m_ibo;
};


