#include "CCacheProgram.h"
#include "CUniform.h"
#include "CProgramPool.h"

	TRC_SCOPE_DEF(ADAS, CCacheProgram, CCacheProgram);
	CCacheProgram::CCacheProgram()
	{
		TRC_SCOPE(ADAS, CCacheProgram, CCacheProgram);
		DBG_MSG(("new CCacheProgram::CCacheProgram()\n"));
	}

	TRC_SCOPE_DEF(ADAS, CCacheProgram, deCCacheProgram);
	CCacheProgram::~CCacheProgram()
	{
		TRC_SCOPE(ADAS, CCacheProgram, deCCacheProgram);
		DBG_MSG(("delete CCacheProgram::~CCacheProgram()\n"));
	}

	void CCacheProgram::begin()
	{
		;
	}

	void CCacheProgram::setUniforms(Ref* p)
	{
		for( UInt32 i = 0; i< m_aryUniform.size() ; ++i )
		{
			CUniform* pUniform = m_aryUniform[i];
			pUniform->use(p);
		}
	}

	void CCacheProgram::setTextureUniforms(CCacheTexture* pTex)
	{
		;
	}

	void CCacheProgram::end(/*CPass* p*/)
	{
		;
	}

	void CCacheProgram::generate(EProgramType eType)
	{
		;
	}
