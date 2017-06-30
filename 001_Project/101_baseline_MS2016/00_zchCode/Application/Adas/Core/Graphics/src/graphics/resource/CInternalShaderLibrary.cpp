#include "CInternalShaderLibrary.h"


	////////////////////////////////////// UI_DEFAUT //////////////////////////////////////////
	 char s_pszVtx001[] = "\
					attribute vec3			a_position; \
					attribute vec2			a_texCoord; \
					uniform mat4			u_uimatrix; \
					varying mediump vec2	v_texCoord; \
					void main(void)						\
					{									\
						gl_Position = u_uimatrix * vec4(a_position.x, a_position.y, -2.0, 1.0);\
						v_texCoord = a_texCoord;		\
					}";
	
	char* s_pvsAtt001[] = {"a_position", "a_texCoord" };
	//char* s_pvsUni001[] = {"u_uimatrix"};
	tagUniformInfo	s_aryVSUniform001[] = {{EUNTYPE_MATRIX4,"u_uimatrix"}};

	 char s_pszFrg001[] = "\
				precision mediump float;							\
				varying mediump vec2	v_texCoord;					\
				uniform sampler2D s_texture;						\
				void main()											\
				{													\
				  gl_FragColor = texture2D( s_texture, v_texCoord );\
				} ";                                                  

	char* s_pfsSampler001[]	=	{"s_texture"};
	

	////////////////////////////////////// UI_APHA //////////////////////////////////////////
	//------------------------------
	 char s_pszVtx002[] = "\
					attribute vec3			a_position; \
					attribute vec2			a_texCoord; \
					uniform mat4			u_uimatrix; \
					varying mediump vec2	v_texCoord; \
					varying mediump float	v_alpha;	\
					void main(void)						\
					{									\
						gl_Position = u_uimatrix * vec4(a_position.x, a_position.y, 2.0, 1.0);\
						v_texCoord = a_texCoord;		\
						v_alpha = a_position.z;			\
					}";
	
	 char* s_pvsAtt002[] = {"a_position", "a_texCoord" };
	 //char* s_pvsUni002[] = {"u_uimatrix"};
	 tagUniformInfo	s_aryVSUniform002[] = {{EUNTYPE_MATRIX4,"u_uimatrix"}};

	//--------------------------------
	 char s_pszFrg002[] = "\
				precision mediump float;							\
				varying mediump vec2	v_texCoord;					\
				varying mediump float	v_alpha;	\
				uniform sampler2D s_texture;						\
				void main()											\
				{													\
				  gl_FragColor = texture2D( s_texture, v_texCoord );\
				  gl_FragColor = v_alpha * gl_FragColor;	\
				} ";                                                  

	 char* s_pfsSampler002[]	=	{"s_texture"};


#define CONSTRUCTPROGRAMINFO(i, VSUniforms, FSUniforms, FSSamplers)	\
	s_PrgInfos[i-1].pszVS = s_pszVtx##00##i;									\
	s_PrgInfos[i-1].pszFS = s_pszFrg##00##i;									\
	s_PrgInfos[i-1].ppszVSAttributes = s_pvsAtt##00##i;							\
	s_PrgInfos[i-1].uiVSAttrNum = sizeof(s_pvsAtt##00##i)/sizeof(char*);		\
	s_PrgInfos[i-1].pVSUniforms = VSUniforms;								\
	s_PrgInfos[i-1].uiVSUniformNum = (VSUniforms == NULL ? 0 : ( sizeof(VSUniforms)/sizeof(tagUniformInfo)));		\
	s_PrgInfos[i-1].pFSUniforms = FSUniforms;								\
	s_PrgInfos[i-1].uiFSUniformNum = (FSUniforms == NULL ? 0 : ( sizeof(FSUniforms)/sizeof(tagUniformInfo)));		\
	s_PrgInfos[i-1].ppszFSSamplers = FSSamplers;						\
	s_PrgInfos[i-1].uiFSSamplerNum = (FSSamplers == NULL ? 0 : ( sizeof(FSSamplers)/sizeof(char*)));		

	const tagProgramInfo& g_getInternalProgramInfo(EProgramType eType)
	{
		//const UInt32	uiInternalProgramNum = EPRG_NUM;
		static tagProgramInfo s_PrgInfos[EPRG_NUM];

		static BOOLEAN s_bHasInitialize = FALSE;

		if(!s_bHasInitialize)
		{
			CONSTRUCTPROGRAMINFO(1, s_aryVSUniform001,  NULL, s_pfsSampler001 );
			CONSTRUCTPROGRAMINFO(2, s_aryVSUniform002,  NULL, s_pfsSampler002);
			
			s_bHasInitialize = TRUE;
		}
		
		return s_PrgInfos[eType];
		
	}
