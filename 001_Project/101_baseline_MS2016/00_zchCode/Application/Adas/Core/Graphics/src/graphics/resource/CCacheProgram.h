#pragma once

#include "common.h"

#include "ResourceEnum.h"

	class CUniform;
	class CCacheTexture;
	class CCacheProgram : public Ref
	{
	public:// const define

	private:// const define

	public:// embed class or struct or enum

	private:// embed class or struct or enum

	public:// method	
		CCacheProgram();
		virtual ~CCacheProgram();

		virtual void	begin();
		virtual void	setUniforms(Ref* p);
		virtual void	setTextureUniforms(CCacheTexture* pTex);
		virtual void	end();
		virtual void	generate(EProgramType eType);

	protected:// method
		CCacheProgram(const CCacheProgram &){}
		CCacheProgram &operator = (const CCacheProgram &){return *this;}	

	private:// method

	protected:// property
		Array<CUniform*>				m_aryUniform;

	private:// property	
		
	};


