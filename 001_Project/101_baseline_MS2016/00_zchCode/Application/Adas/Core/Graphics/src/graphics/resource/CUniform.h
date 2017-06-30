#pragma once

#include "common.h"

	enum EUniformType
	{
		EUNTYPE_INT,
		EUNTYPE_INTARRAY,
		EUNTYPE_FLOAT,
		EUNTYPE_FLOATARRAY,
		EUNTYPE_VEC2,
		EUNTYPE_VEC2ARRAY,
		EUNTYPE_VEC3,
		EUNTYPE_VEC3ARRAY,
		EUNTYPE_VEC4,
		EUNTYPE_VEC4ARRAY,
		EUNTYPE_MATRIX3,
		EUNTYPE_MATRIX3ARRAY,
		EUNTYPE_MATRIX4,
		EUNTYPE_MATRIX4ARRAY,

		EUNTYPE_NUM
	};

	// name call back func
	extern void getProject_UI(Ref* p,C3DMatrix4& ret);
	extern void getMP_UI(Ref* p,C3DMatrix4& ret);
	//extern void getTextSizeX_UI(Object* p,Int32& ret);
	//extern void getTextSizeY_UI(Object* p,Int32& ret);

	class CUniform : public Ref
	{
	public:
		CUniform()
			: m_pFunctor(NULL)
		{
			;
		}

		virtual ~CUniform()
		{
			;
		}

		void setCallBack(Ref* pFunctor)
		{
			m_pFunctor = pFunctor;
		}

		virtual void use(Ref* p)
		{
			;
		}

	protected:
		Ref*		m_pFunctor;
	};

