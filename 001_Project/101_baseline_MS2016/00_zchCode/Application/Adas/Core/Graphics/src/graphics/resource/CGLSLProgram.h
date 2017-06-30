#pragma once

#include "common.h"
#include "CInternalShaderLibrary.h"
#include "CCacheProgram.h"

#include "ResourceEnum.h"

	class CGLSLProgram : public CCacheProgram
	{
	public:// const define

	private:// const define

	public:// embed class or struct or enum

	private:// embed class or struct or enum

	public:// method	
		CGLSLProgram();
		virtual ~CGLSLProgram();

		virtual void	begin();
		virtual void	setTextureUniforms(CCacheTexture* pTex);
		virtual void	generate(EProgramType eType);

		UInt32			getProgramID() const				{ return m_uiProgramID;	}
		
	protected:// method
		CGLSLProgram(const CGLSLProgram &){}
		CGLSLProgram &operator = (const CGLSLProgram &){return *this;}	

	private:// method
		GLuint		loadShader(GLenum eType, const char *pcShaderSrc);
		BOOLEAN		linkProgram(GLuint uiProgram);
		void		bindAttributes(GLuint uiProgram, const tagProgramInfo& tagPrgInfo);
		void		getUniforms(GLuint uiProgram, const tagProgramInfo& tagPrgInfo);
		CUniform*	getUniformByType(EUniformType eType, const char* psz);

	protected:// property

	private:// property	
		GLuint						m_uiProgramID;

		UInt32						m_uiSamplerNum;

	};

