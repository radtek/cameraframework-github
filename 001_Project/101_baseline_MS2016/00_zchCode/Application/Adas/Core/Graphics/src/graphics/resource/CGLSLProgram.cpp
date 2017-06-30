#include "CGLSLProgram.h"
#include "CProgramPool.h"
#include "CUniform.h"
#include "CCacheTexture.h"



	class CBaseOGLES2Uniform : public CUniform
	{
	public:
		CBaseOGLES2Uniform() 
			: m_iLoc(-1)
		{
			;
		}

		virtual ~CBaseOGLES2Uniform()
		{
			;
		}

		void setLocation(Int32 iLoc)
		{
			m_iLoc = iLoc;
		}

	protected:
		Int32		m_iLoc;
	};

	template<EUniformType>
	class COGLES2Uniform
	{
	public:

	};

	template<>
	class COGLES2Uniform<EUNTYPE_INT> : public CBaseOGLES2Uniform
	{
	public:
		virtual void use(Ref* pObj)
		{
			
			Int32 iRet;
			CGlobalFuncArg2<Ref*,Int32&>* p = static_cast<CGlobalFuncArg2<Ref*,Int32&>* >(m_pFunctor);
			if( p )
			{
				(*p)(pObj,iRet);
				glUniform1i(m_iLoc,iRet);
			}
				
		}
		
	};

	//template<>
	//class COGLES2Uniform<EUNTYPE_INTARRAY> : public CBaseOGLES2Uniform
	//{
	//public:
	//	virtual void use(Object* pObj)
	//	{
	//		Array2<Int32> ret;
	//		CGlobalFuncArg2<Object*,Array2<Int32>& >* p = static_cast<CGlobalFuncArg2<Object*,Array2<Int32>& >* >(m_pFunctor);
	//		if( p )
	//		{
	//			p->func(pObj,ret);
	//			glUniform1iv(m_iLoc,ret.size(),&ret[0]);
	//		}	
	//	}
	//};

	template<>
	class COGLES2Uniform<EUNTYPE_FLOAT> : public CBaseOGLES2Uniform
	{
	public:
		virtual void use(Ref* pObj)
		{
			Float32 ret;
			CGlobalFuncArg2<Ref*,Float32& >* p = static_cast<CGlobalFuncArg2<Ref*,Float32&>* >(m_pFunctor);
			if( p )
			{
				(*p)(pObj,ret);
				glUniform1f(m_iLoc,ret);
			}	
		}
	};

	//template<>
	//class COGLES2Uniform<EUNTYPE_FLOATARRAY> : public CBaseOGLES2Uniform
	//{
	//public:
	//	virtual void use(Object* pObj)
	//	{
	//		Array2<FLOAT> ret;
	//		CGlobalFuncArg2<Object*,Array2<FLOAT>& >* p = static_cast<CGlobalFuncArg2<Object*,Array2<FLOAT>& >* >(m_pFunctor);
	//		if( p )
	//		{
	//			p->func(pObj,ret);
	//			glUniform1fv(m_iLoc,ret.size(),&ret[0]);
	//		}	
	//	}
	//};

	template<>
	class COGLES2Uniform<EUNTYPE_VEC2> : public CBaseOGLES2Uniform
	{
	public:
		virtual void use(Ref* pObj)
		{
			// ret;
			//CGlobalFuncArg2<Object*,Array2<Int32>& >* p = static_cast<CGlobalFuncArg2<Object*,Array2<Int32>& >* >(m_pFunctor);
			//if( p )
			//{
			//	p->func(pObj,ret);
			//	glUniform1iv(m_iLoc,ret.size(),&ret[0]);
			//}	
		}
	};

	template<>
	class COGLES2Uniform<EUNTYPE_VEC2ARRAY> : public CBaseOGLES2Uniform
	{
	public:
		virtual void use(Ref* pObj)
		{
			//Array2<Int32> ret;
			//CGlobalFuncArg2<Object*,Array2<Int32>& >* p = static_cast<CGlobalFuncArg2<Object*,Array2<Int32>& >* >(m_pFunctor);
			//if( p )
			//{
			//	p->func(pObj,ret);
			//	glUniform1iv(m_iLoc,ret.size(),&ret[0]);
			//}	
		}
	};

	template<>
	class COGLES2Uniform<EUNTYPE_VEC3> : public CBaseOGLES2Uniform
	{
	public:
		virtual void use(Ref* pObj)
		{
			C3DVector3 ret;
			CGlobalFuncArg2<Ref*,C3DVector3& >* p = static_cast<CGlobalFuncArg2<Ref*,C3DVector3& >* >(m_pFunctor);
			if( p )
			{
				(*p)(pObj,ret);
				glUniform3f(m_iLoc,ret.getX(),ret.getY(),ret.getZ());
			}	
		}
		
	};

	//template<>
	//class COGLES2Uniform<EUNTYPE_VEC3ARRAY> : public CBaseOGLES2Uniform
	//{
	//public:
	//	virtual void use(Object* pObj)
	//	{
	//		Array2<C3DVector3> ret;
	//		CGlobalFuncArg2<Object*,Array2<C3DVector3>& >* p = static_cast<CGlobalFuncArg2<Object*,Array2<C3DVector3>& >* >(m_pFunctor);
	//		if( p )
	//		{
	//			p->func(pObj,ret);
	//			glUniform3fv(m_iLoc,ret.size(), (const GLfloat*)&ret[0]);
	//		}	
	//	}
	//};

	template<>
	class COGLES2Uniform<EUNTYPE_VEC4> : public CBaseOGLES2Uniform
	{
	public:
		virtual void use(Ref* pObj)
		{
			C3DVector4 ret;
			CGlobalFuncArg2<Ref*,C3DVector4& >* p = static_cast<CGlobalFuncArg2<Ref*,C3DVector4& >* >(m_pFunctor);
			if( p )
			{
				(*p)(pObj,ret);
				glUniform4f(m_iLoc,ret.getX(),ret.getY(),ret.getZ(),ret.getW() );
			}	
		}
	};

	//template<>
	//class COGLES2Uniform<EUNTYPE_VEC4ARRAY> : public CBaseOGLES2Uniform
	//{
	//public:
	//	virtual void use(Object* pObj)
	//	{
	//		Array2<C3DVector4> ret;
	//		CGlobalFuncArg2<Object*,Array2<C3DVector4>& >* p = static_cast<CGlobalFuncArg2<Object*,Array2<C3DVector4>& >* >(m_pFunctor);
	//		if( p )
	//		{
	//			p->func(pObj,ret);
	//			glUniform4fv(m_iLoc,ret.size(),(const GLfloat*)&ret[0]);
	//		}	
	//	}
	//};

	template<>
	class COGLES2Uniform<EUNTYPE_MATRIX3> : public CBaseOGLES2Uniform
	{
	public:
		virtual void use(Ref* pObj)
		{
			//C3DMatrix3 ret;
			//CGlobalFuncArg2<Object*,C3DMatrix3& >* p = static_cast<CGlobalFuncArg2<Object*,C3DMatrix3& >* >(m_pFunctor);
			//if( p )
			//{
			//	p->func(pObj,ret);
			//	glUniformMatrix3fv(m_iLoc,1,GL_FALSE,(const GLfloat*)&ret);
			//}
		}
	};

	template<>
	class COGLES2Uniform<EUNTYPE_MATRIX3ARRAY> : public CBaseOGLES2Uniform
	{
	public:
		virtual void use(Ref* pObj)
		{
/*			Array2<C3DMatrix3> ret;
			CGlobalFuncArg2<Object*,Array2<C3DMatrix3>& >* p = static_cast<CGlobalFuncArg2<Object*,Array2<C3DMatrix3>& >* >(m_pFunctor);
			if( p )
			{
				p->func(pObj,ret);
				glUniformMatrix3fv(m_iLoc,ret.size() ,GL_FALSE,(const GLfloat*)&ret);
			}*/	
		}
	};

	template<>
	class COGLES2Uniform<EUNTYPE_MATRIX4> : public CBaseOGLES2Uniform
	{
	public:
		virtual void use(Ref* pObj)
		{
			C3DMatrix4 ret;
			CGlobalFuncArg2<Ref*,C3DMatrix4& >* p = static_cast<CGlobalFuncArg2<Ref*,C3DMatrix4& >* >(m_pFunctor);
			if( p )
			{
				(*p)(pObj,ret);
				glUniformMatrix4fv(m_iLoc,1,GL_FALSE,(const GLfloat*)ret.ptr());
			}
		}
	};

	//template<>
	//class COGLES2Uniform<EUNTYPE_MATRIX4ARRAY> : public CBaseOGLES2Uniform
	//{
	//public:
	//	virtual void use(Object* pObj)
	//	{
	//		Array2<C3DMatrix4> ret;
	//		CGlobalFuncArg2<Object*,Array2<C3DMatrix4>& >* p = static_cast<CGlobalFuncArg2<Object*,Array2<C3DMatrix4>& >* >(m_pFunctor);
	//		if( p )
	//		{
	//			p->func(pObj,ret);
	//			glUniformMatrix4fv(m_iLoc,ret.size() ,GL_FALSE,(const GLfloat*)&ret);
	//		}	
	//	}
	//};


	//------------------------------------------------------------------------------

	CGLSLProgram::CGLSLProgram()
		: m_uiProgramID(0)
		, m_uiSamplerNum(0)
	{
	//	CLog::debug2(RENDER_ENGINE_NAME, L"new CCacheProgram");
	}

	CGLSLProgram::~CGLSLProgram()
	{
		//CLog::debug2(String(RENDER_ENGINE_NAME),String(L"delete CCacheProgram") + getName());
		if (m_uiProgramID != 0)
		{
			//changeRenderContext();
			glUseProgram(0);
			glDeleteProgram( m_uiProgramID );
			m_uiProgramID = 0;
			//resetRenderContext();
		}
	}

	void CGLSLProgram::begin()
	{
		glUseProgram(m_uiProgramID);
	}

	void CGLSLProgram::setTextureUniforms(CCacheTexture* pTex)
	{
		if ( pTex == NULL )
		{
			return;
		}

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, pTex->getTexID());
	}

	void CGLSLProgram::generate(EProgramType eType)
	{
		const tagProgramInfo& rPrgInfo = g_getInternalProgramInfo(eType);
		GLuint uiVSID = loadShader(GL_VERTEX_SHADER, rPrgInfo.pszVS);
		GLuint uiFSID = loadShader(GL_FRAGMENT_SHADER, rPrgInfo.pszFS);
		GLuint uiID = glCreateProgram( );
		
		if ( uiID == 0 )
		{
			//CLog::info(String(RENDER_ENGINE_NAME), String(L"CProgramPool generateProgram ERROR glCreateProgram failed"));
			return;
		}

		bindAttributes(uiID, rPrgInfo);

		glAttachShader( uiID, uiVSID );
		glAttachShader( uiID, uiFSID );

		if (linkProgram(uiID) == FALSE)
		{
			//CLog::info(String(RENDER_ENGINE_NAME), String(L"linkProgram failed") );
			return;
		}
		m_uiProgramID = uiID;

		glUseProgram(uiID);
		getUniforms(uiID, rPrgInfo);
		glUseProgram(0);
		glDeleteShader(uiVSID);
		glDeleteShader(uiFSID);
	}

	GLuint CGLSLProgram::loadShader(GLenum eType, const char *pcShaderSrc)
	{
		GLuint	uiShader;
		GLint	iCompiled;

		// Create the shader object
		uiShader = glCreateShader( eType );
		if ( uiShader == 0 )
		{
			return 0;
		}

		// Load the shader source
		glShaderSource( uiShader, 1, &pcShaderSrc, NULL );

		// Compile the shader
		glCompileShader( uiShader );

		// Check the compile status
		glGetShaderiv( uiShader, GL_COMPILE_STATUS, &iCompiled );

		if ( !iCompiled ) 
		{
			GLint iInfoLen = 0;

			glGetShaderiv( uiShader, GL_INFO_LOG_LENGTH, &iInfoLen );

			//if ( iInfoLen > 1 )
			//{
				//ArrayPtr<char> ptrInfoLog(new char [iInfoLen], iInfoLen);

				//glGetShaderInfoLog( uiShader, iInfoLen, NULL, (char*)ptrInfoLog );

				//String strInfoLog;
				//String::convertFromMBCS((char*)ptrInfoLog, strInfoLog);
				//CLog::error2(RENDER_ENGINE_NAME, (const CHAR*)strInfoLog);
			//}

			glDeleteShader( uiShader );

			return 0;
		}

		return uiShader;
	}

	BOOLEAN CGLSLProgram::linkProgram(GLuint uiProgram)
	{
		GLint	iLinked;

		// Link the program
		glLinkProgram( uiProgram );

		// Check the link status
		glGetProgramiv( uiProgram, GL_LINK_STATUS, &iLinked );

		if ( !iLinked ) 
		{
			GLint iInfoLen = 0;

			glGetProgramiv( uiProgram, GL_INFO_LOG_LENGTH, &iInfoLen );

		//	if ( iInfoLen > 1 )
		//	{
				//ArrayPtr<char> ptrInfoLog(new char [iInfoLen], iInfoLen);

				//glGetProgramInfoLog( uiProgram, iInfoLen, NULL, (char*)ptrInfoLog );
				
				//String strInfoLog;
				//String::convertFromMBCS((char*)ptrInfoLog, strInfoLog);
				//CLog::debug2(RENDER_ENGINE_NAME, (const CHAR*)strInfoLog);
		//	}

			glDeleteProgram( uiProgram );

			return FALSE;
		}

		return TRUE;
	}

	void CGLSLProgram::bindAttributes(GLuint uiProgram, const tagProgramInfo& tagPrgInfo)
	{
		Int32 i = 0 ; 
		for(UInt32 uidx = 0; uidx < tagPrgInfo.uiVSAttrNum; ++uidx)
		{
			const char* psz = tagPrgInfo.ppszVSAttributes[uidx];
			if( psz )
			{
				glBindAttribLocation(uiProgram, i, psz);
				++i;
			}
		}
	}

	void CGLSLProgram::getUniforms(GLuint uiProgram, const tagProgramInfo& tagPrgInfo)
	{
		for(UInt32 i = 0; i < tagPrgInfo.uiVSUniformNum; ++i)
		{
			const tagUniformInfo& tagUni = tagPrgInfo.pVSUniforms[i];
			CUniform* pUniform = getUniformByType(tagUni.eType, tagUni.pszUniformName);

			//String strUniformName;
			//String::convertFromMBCS(tagUni.pszUniformName, strUniformName);
			pUniform->setCallBack( CProgramPool::getInstance()->getUniformFunctor(tagUni.pszUniformName) );

			m_aryUniform.push_back(pUniform);
		}

		for(UInt32 i = 0; i < tagPrgInfo.uiFSUniformNum; ++i)
		{
			const tagUniformInfo& tagUni = tagPrgInfo.pFSUniforms[i];
			CUniform* pUniform = getUniformByType(tagUni.eType, tagUni.pszUniformName);
			//String strUniformName;
			//String::convertFromMBCS(tagUni.pszUniformName, strUniformName);
			pUniform->setCallBack( CProgramPool::getInstance()->getUniformFunctor(tagUni.pszUniformName) );

			m_aryUniform.push_back(pUniform);
		}

		m_uiSamplerNum = tagPrgInfo.uiFSSamplerNum;
		Int32 idx = 0;
		for ( UInt32 i = 0; i < tagPrgInfo.uiFSSamplerNum; ++i )
		{
			const char* psz = tagPrgInfo.ppszFSSamplers[i];
			if( psz == NULL )
			{
				//CLog::error2(RENDER_ENGINE_NAME, L"generateUniforms fpsource.getSampler(i) error");
				return;
			}

			Int32 iTexLoc = glGetUniformLocation(uiProgram, psz );
			glUniform1i(iTexLoc, idx);

			++idx;
		}
	}

	CUniform* CGLSLProgram::getUniformByType(EUniformType eType, const char* psz)
	{
		//CUniform* pUniform = NULL;
		switch(eType)
		{
		case EUNTYPE_INT:
			{
			COGLES2Uniform<EUNTYPE_INT>* pUniform = new COGLES2Uniform<EUNTYPE_INT>();
			pUniform->setLocation( glGetUniformLocation( m_uiProgramID, psz ) );
			return pUniform;
			}
		case EUNTYPE_INTARRAY:
			{
			//COGLES2Uniform<EUNTYPE_INTARRAY>* pUniform = new COGLES2Uniform<EUNTYPE_INTARRAY>();
			//pUniform->setLocation( glGetUniformLocation( m_uiProgramID, psz ) );
			//return pUniform;
			}
		case EUNTYPE_FLOAT:
			{
			COGLES2Uniform<EUNTYPE_FLOAT>* pUniform = new COGLES2Uniform<EUNTYPE_FLOAT>();
			pUniform->setLocation( glGetUniformLocation( m_uiProgramID, psz ) );
			return pUniform;
			}
		case EUNTYPE_FLOATARRAY:
			{
			//COGLES2Uniform<EUNTYPE_FLOATARRAY>* pUniform = new COGLES2Uniform<EUNTYPE_FLOATARRAY>();
			//pUniform->setLocation( glGetUniformLocation( m_uiProgramID, psz ) );
			//return pUniform;
			}
		case EUNTYPE_VEC2:
			{
			COGLES2Uniform<EUNTYPE_VEC2>* pUniform = new COGLES2Uniform<EUNTYPE_VEC2>();
			pUniform->setLocation( glGetUniformLocation( m_uiProgramID, psz ) );
			return pUniform;
			}
		case EUNTYPE_VEC2ARRAY:
			{
			//COGLES2Uniform<EUNTYPE_VEC2ARRAY>* pUniform = new COGLES2Uniform<EUNTYPE_VEC2ARRAY>();
			//pUniform->setLocation( glGetUniformLocation( m_uiProgramID, psz ) );
			//return pUniform;
			}
		case EUNTYPE_VEC3:
			{
			COGLES2Uniform<EUNTYPE_VEC3>* pUniform = new COGLES2Uniform<EUNTYPE_VEC3>();
			pUniform->setLocation( glGetUniformLocation( m_uiProgramID, psz ) );
			return pUniform;
			}
		case EUNTYPE_VEC3ARRAY:
			{
			//COGLES2Uniform<EUNTYPE_VEC3ARRAY>* pUniform = new COGLES2Uniform<EUNTYPE_VEC3ARRAY>();
			//pUniform->setLocation( glGetUniformLocation( m_uiProgramID, psz ) );
			//return pUniform;
			}
		case EUNTYPE_VEC4:
			{
			COGLES2Uniform<EUNTYPE_VEC4>* pUniform = new COGLES2Uniform<EUNTYPE_VEC4>();
			pUniform->setLocation( glGetUniformLocation( m_uiProgramID, psz ) );
			return pUniform;
			}
		case EUNTYPE_VEC4ARRAY:
			{
			//COGLES2Uniform<EUNTYPE_VEC4ARRAY>* pUniform = new COGLES2Uniform<EUNTYPE_VEC4ARRAY>();
			//pUniform->setLocation( glGetUniformLocation( m_uiProgramID, psz ) );
			//return pUniform;
			}
		case EUNTYPE_MATRIX3:
			{
			COGLES2Uniform<EUNTYPE_MATRIX3>* pUniform = new COGLES2Uniform<EUNTYPE_MATRIX3>();
			pUniform->setLocation( glGetUniformLocation( m_uiProgramID, psz ) );
			return pUniform;
			}
		case EUNTYPE_MATRIX3ARRAY:
			{

			//COGLES2Uniform<EUNTYPE_MATRIX3ARRAY>* pUniform = new COGLES2Uniform<EUNTYPE_MATRIX3ARRAY>();
			//pUniform->setLocation( glGetUniformLocation( m_uiProgramID, psz ) );
			//return pUniform;
			}
		case EUNTYPE_MATRIX4:
			{
			COGLES2Uniform<EUNTYPE_MATRIX4>* pUniform = new COGLES2Uniform<EUNTYPE_MATRIX4>();
			pUniform->setLocation( glGetUniformLocation( m_uiProgramID, psz ) );
			return pUniform;
			}
		case EUNTYPE_MATRIX4ARRAY:
			{
			//COGLES2Uniform<EUNTYPE_MATRIX4ARRAY>* pUniform = new COGLES2Uniform<EUNTYPE_MATRIX4ARRAY>();
			//pUniform->setLocation( glGetUniformLocation( m_uiProgramID, psz ) );
			//return pUniform;
			}
		case EUNTYPE_NUM:
			break;
		}
		return NULL;
	}
