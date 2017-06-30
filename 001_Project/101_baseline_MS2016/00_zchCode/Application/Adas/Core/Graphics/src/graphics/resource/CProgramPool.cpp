#include "CProgramPool.h"
#include "CGLSLProgram.h"

	CProgramPool* CProgramPool::s_pInstance	= NULL;

	CProgramPool*	CProgramPool::getInstance()		
	{
		if (s_pInstance == NULL)
		{
			s_pInstance = new CProgramPool();
		}

		return s_pInstance;
	}

	void CProgramPool::deleteInstance()
	{
		if (s_pInstance != NULL)
		{
			delete s_pInstance;
			s_pInstance = NULL;
		}
	}

	CProgramPool::CProgramPool()
	{
		;
	}

	CProgramPool::~CProgramPool()
	{
		;
	}

	void CProgramPool::initialize()
	{
		initializeUniform();
	}

	void CProgramPool::unInitialize()
	{
		clear();
	}

	void CProgramPool::clear()
	{
		for( HashMap<EProgramType, CCacheProgram*>::Iterator it = m_hashMapProgram.begin();
				it != m_hashMapProgram.end() ; ++it )
		{
			(*it).second->release();

		}
		m_hashMapProgram.clear();

		for( HashMap<string, Ref*>::Iterator it = m_hashMapUniformFunctor.begin();
						it != m_hashMapUniformFunctor.end() ; ++it )
		{
			(*it).second->release();

		}
		m_hashMapUniformFunctor.clear();

	}

	CCacheProgram* CProgramPool::getProgram(EProgramType ePrgType)
	{
		HashMap<EProgramType, CCacheProgram*>::Iterator it = m_hashMapProgram.find(ePrgType);
		if( it == m_hashMapProgram.end() )
		{
			CCacheProgram* p = new CGLSLProgram();
			p->generate(ePrgType);
			//p->retain();

			m_hashMapProgram.insert(makePair(ePrgType,p));

			return p;
		}
		return (*it).second;
	}

	Ref* CProgramPool::getUniformFunctor(const string& strName)
	{
		HashMap<string, Ref*>::Iterator iter = m_hashMapUniformFunctor.find(strName);
		if( iter != m_hashMapUniformFunctor.end() )
			return (*iter).second;

		return NULL;
	}

	void  CProgramPool::initializeUniform()
	{
		m_hashMapUniformFunctor.insert(makePair( "u_uimatrix", makeFunctor(&getProject_UI) ) );
		m_hashMapUniformFunctor.insert(makePair("u_uiMPmatrix", makeFunctor(&getMP_UI)) );
		//m_hashMapUniformFunctor.insert("u_textSizeX", makeFunctor(&getTextSizeX_UI) );
		//m_hashMapUniformFunctor.insert("u_textSizeY", makeFunctor(&getTextSizeY_UI) );
	}
	
