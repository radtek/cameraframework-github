#ifndef __CCACHETEXTURE_H_INCLUDED__
#define __CCACHETEXTURE_H_INCLUDED__

#include "common.h"
#include "ResourceEnum.h"
	class CCacheTexture : public Ref
	{
	public:// const define

	private:// const define

	public:// embed class or struct or enum
		enum ETexType
		{
			TEXTYPE_2D			= GL_TEXTURE_2D,
		};

		enum ETexUsage
		{
			TEXUSAGE_NULL		= 0x00001000,
			TEXUSAGE_TEXTMERGE	= 0x00010000,
		};

		enum EWrapParameter 
		{
            WRAP_S,
            WRAP_T,
            WRAP_R
        };

        enum EWrapMode 
		{
            WRAPMODE_CLAMP_TO_EDGE	= GL_CLAMP_TO_EDGE,
            WRAPMODE_REPEAT			= GL_REPEAT,
        };

		enum EFilterParameter 
		{
            FP_MIN_FILTER,
            FP_MAG_FILTER
        };

        enum EFilterMode 
		{
            FM_LINEAR                    = GL_LINEAR,
            FM_LINEAR_MIPMAP_LINEAR      = GL_LINEAR_MIPMAP_LINEAR,
            FM_LINEAR_MIPMAP_NEAREST     = GL_LINEAR_MIPMAP_NEAREST,
            FM_NEAREST                   = GL_NEAREST,
            FM_NEAREST_MIPMAP_LINEAR     = GL_NEAREST_MIPMAP_LINEAR,
            FM_NEAREST_MIPMAP_NEAREST    = GL_NEAREST_MIPMAP_NEAREST
        };

	private:// embed class or struct or enum

	public:// method	
		//IMP_OPERATOR_NEW(CCacheTexture)

		CCacheTexture();
		virtual ~CCacheTexture();

		void		setup(UInt32 uiWith, UInt32 uiHeight, const BYTE* pData, UInt32 uiFormat);

		UInt32		getWidth() const			{ return m_uiWidth;								}
		UInt32		getHeight() const			{ return m_uiHeight;							}
		UInt32		getFormat() const			{ return m_uiFormat;							}

		void		setType(UInt32 type)			{ m_uiType = type;								}
		UInt32		getType() const				{ return m_uiType;								}

		// texture usage may be GPU related parameter ,now just usage
		void		setUsage(UInt32 usage)		{ m_uiUsage = usage;							}
		UInt32		getUsage() const			{ return m_uiUsage;								}
		BOOLEAN		isTextMergeTexture() const	{ return (m_uiUsage & TEXUSAGE_TEXTMERGE) != 0;	}

		void		setDirty()					{ m_bDirty = TRUE;								}
		BOOLEAN		getDirty() const			{ return m_bDirty;								}


		EWrapMode	getWrap(EWrapParameter eWhich) const;
		void		setWrap(EWrapParameter eWhich, EWrapMode eMode);

		EFilterMode	getFilter(EFilterParameter eWhich) const;
		void		setFilter(EFilterParameter eWhich, EFilterMode eMode);

		UInt32		getTexID() const			{ return m_uiTexId;								}

		UInt32		getGPUByteSize() const		{ return m_uiGPUByteSize;						}
		
		void		fill(const BYTE* pData);
		void		fill(Int32 uiXOffset, Int32 uiYOffset, Int32 uiWidth, Int32 uiHeight, const BYTE* pData);

		void		applyTextureParameters();

		void		flush(UInt32 uiW, UInt32 uiH, const BYTE* pData, UInt32 uiFormat);

		static void TransferTexFormat(UInt32 format, GLint& internalFormat, GLenum& type);

	protected:// method
		CCacheTexture(const CCacheTexture &){}
		CCacheTexture &operator = (const CCacheTexture &){return *this;}

		void			dirtyTextureParameters(){ m_bNeedUpdateParameter = TRUE;	}
	
		virtual void	onGenerateGPUResource()	{}

	private:// method

	protected:// property
		UInt32		m_uiWidth;
		UInt32		m_uiHeight;
		UInt32		m_uiFormat;			// RGB888 RGB556 RGGA8888
		UInt32		m_uiType;			// 2D Texture
		UInt32		m_uiUsage;			// texture usage
		UInt32		m_uiTexId;
		UInt32		m_uiGPUByteSize;	// the memory byte size the texture loads

		EWrapMode	m_wrap_s;
        EWrapMode	m_wrap_t;
        EWrapMode	m_wrap_r;

        EFilterMode m_min_filter;
        EFilterMode m_mag_filter;
		
		BOOLEAN		m_bNeedUpdateParameter;
		BOOLEAN		m_bDirty;

	private:// property	
		
	};



#endif
