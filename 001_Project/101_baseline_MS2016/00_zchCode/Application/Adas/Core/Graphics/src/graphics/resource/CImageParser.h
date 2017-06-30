#pragma once

#include "common.h"

	class CImageParser
	{
	public:// const define

	private:// const define

	public:// embed class or struct or enum
		class tagImageInfo
		{
		public:
			tagImageInfo()
				: uiWidth(0)
				, uiHeight(0)
				, pbtPixelData(NULL)
			{
				;
			}

			UInt32	uiWidth;
			UInt32	uiHeight;
			BYTE	*pbtPixelData;
		};

	private:// embed class or struct or enum

	public:// method	
		static tagImageInfo decodeFromFile(const char* pszFilePath);
		static void			close();

	protected:// method
		CImageParser(){}
		CImageParser(const CImageParser&){}
		virtual ~CImageParser(){}		
		CImageParser& operator =(const CImageParser&){return *this;}

	private:// method

	protected:// property

	private:// property

	};
