
#ifndef __CRECTANGLE_H_INCLUDED__
#define __CRECTANGLE_H_INCLUDED__

#include "common/TypeDefine.h"
#include "common/ADASMarco.h"

	class  CRectangle
	{
	public:// const define

	private:// const define

	public:// embed class or struct or enum

	private:// embed class or struct or enum

	public:// method
		CRectangle();
		CRectangle(const CRectangle &src);
		CRectangle(Int32 iX, Int32 iY, UInt32 uiWidth, UInt32 uiHeight);
		virtual ~CRectangle();

		void	set(Int32 iX, Int32 iY, UInt32 uiW, UInt32 uiH)	{ m_iX = iX; m_iY = iY; m_uiWidth = uiW; m_uiHeight = uiH;	}
		void	setX(Int32 iValue)		{ m_iX = iValue; }
		Int32		getX() const			{ return m_iX; }
		void	setY(Int32 iValue)		{ m_iY = iValue; }
		Int32		getY() const			{ return m_iY; }
		void	setWidth(UInt32 uiValue)	{ m_uiWidth = uiValue; }
		UInt32	getWidth() const		{ return m_uiWidth; }
		void	setHeight(UInt32 uiValue)	{ m_uiHeight = uiValue; }
		UInt32	getHeight() const		{ return m_uiHeight; }
		Int32		getRight() const		{ return m_iX + ((Int32)m_uiWidth > 0 ? (Int32)m_uiWidth - 1 : 0); }
		Int32		getBottom() const		{ return m_iY + ((Int32)m_uiHeight > 0 ? (Int32)m_uiHeight - 1 : 0); }
		Int32		getCenterX() const		{ return m_iX + (Int32)m_uiWidth / 2; }
		Int32		getCenterY() const		{ return m_iY + (Int32)m_uiHeight / 2; }

		BOOLEAN		isEmpty() const		{ return (m_uiWidth == 0) || (m_uiHeight == 0); }
		void		offset(Int32 iX, Int32 iY);		
		//BOOLEAN		ptInRect(const CPoint &pt) const;
		BOOLEAN		rectInRect(const CRectangle &rc) const;
		CRectangle	intersect(const CRectangle &rc) const;

		BOOLEAN		isIntersect(const CRectangle &rc) const;
		void		clear();
		void		add(const CRectangle &rc);

		CRectangle& operator =(const CRectangle &src);
		BOOLEAN operator ==(const CRectangle &src) const;
		BOOLEAN operator !=(const CRectangle &src) const;

	protected:// method

	private:// method

	public:// property
		Int32		m_iX;
		Int32		m_iY;
		UInt32	m_uiWidth;
		UInt32	m_uiHeight;

	protected:// property

	private:// property
		
	};

#endif
