#pragma once

#include "common.h"
#include "CUniform.h"
#include "CProgramPool.h"
#include "ResourceEnum.h"

	struct tagUniformInfo
	{
		EUniformType	eType;
		char*			pszUniformName;
	};

	struct tagProgramInfo
	{
		char*			pszVS;
		char*			pszFS;
		char**			ppszVSAttributes;
		UInt32			uiVSAttrNum;
		tagUniformInfo*	pVSUniforms;
		UInt32			uiVSUniformNum;
		tagUniformInfo*	pFSUniforms;
		UInt32			uiFSUniformNum;
		char**			ppszFSSamplers;
		UInt32			uiFSSamplerNum;
	};


	extern const tagProgramInfo& g_getInternalProgramInfo(EProgramType eType);


