#pragma once

#include "common.h"
#include "CCacheProgram.h"
#include "ResourceEnum.h"

	class CProgramPool
	{
	public:// const define

	private:// const define

	public:// embed class or struct or 
		
		
	private:// embed class or struct or enum
		//typedef	CFunctorArg2<Ref*,C3DMatrix4&>	CFunctor;

	public:// method	
		static	CProgramPool*	getInstance();
		static	void			deleteInstance();

		void		initialize();
		void		unInitialize();
		void		clear();

		CCacheProgram* 	getProgram(EProgramType ePrgType);

		Ref*			getUniformFunctor(const string& strName);

	protected:// method	
		CProgramPool();
		virtual ~CProgramPool();

	private:// method
		void				initializeUniform();

	protected:// property

	private:// property
		static	CProgramPool	*s_pInstance;

		HashMap<EProgramType, CCacheProgram*>	m_hashMapProgram;
		HashMap<string, Ref*>					m_hashMapUniformFunctor;
		
	};
