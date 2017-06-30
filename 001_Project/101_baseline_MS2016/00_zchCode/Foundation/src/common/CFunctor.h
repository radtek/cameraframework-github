#ifndef _CFUNCTOR_H
#define _CFUNCTOR_H

#include "CCRef.h"

//------------------------------base functor-------------------------------------------
	class CFunctorArg0 : public Ref
	{
	public:
		virtual ~CFunctorArg0() {;}
		virtual void operator()() = 0;
	};

	template<class Ret>
	class CFunctorRetArg0 : public Ref
	{
	public:
		virtual ~CFunctorRetArg0() {;}
		virtual Ret operator()() = 0;
	};

	template<class Arg1>
	class CFunctorArg1 : public Ref
	{
	public:
		virtual ~CFunctorArg1() {;}
		virtual void operator()(Arg1 arg1) = 0;
	};



	template<class Arg1, class Arg2>
	class CFunctorArg2 : public Ref
	{
	public:
		virtual ~CFunctorArg2() {;}
		virtual void operator()(Arg1 arg1, Arg2 arg2) = 0;
	};

	template<class Arg1, class Arg2, class Arg3>
	class CFunctorArg3 : public Ref
	{
	public:
		virtual ~CFunctorArg3() {;}
		virtual void operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3) = 0;
	};

	template<class Arg1, class Arg2, class Arg3, class Arg4>
	class CFunctorArg4 : public Ref
	{
	public:
		virtual ~CFunctorArg4() {;}
		virtual void operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4) = 0;
	};

	template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
	class CFunctorArg5 : public Ref
	{
	public:
		virtual ~CFunctorArg5() {;}
		virtual void operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5) = 0;
	};

//---------------------------------------------------------------------------------------------

	template<class Arg1>
	class CGlobalFuncArg1 : public CFunctorArg1<Arg1>
	{
	public:
		typedef void (*FUNC)(Arg1 param);
		CGlobalFuncArg1(FUNC p) 
			: m_pFunc(p)
		{
			;
		}

		virtual ~CGlobalFuncArg1()
		{
			;
		}

		virtual void operator()(Arg1 param)
		{
			if( m_pFunc )
			{
				m_pFunc(param);
			}
		}

		
	protected:
		FUNC	m_pFunc;
	};

	template<class Arg1,class Arg2>
	class CGlobalFuncArg2 : public CFunctorArg2<Arg1,Arg2>
	{
	public:
		typedef void (*FUNC)(Arg1 param1, Arg2 param2);
		CGlobalFuncArg2(FUNC p) 
			: m_pFunc(p)
		{
			;
		}

		virtual ~CGlobalFuncArg2()
		{
			;
		}

		virtual void operator()(Arg1 param1, Arg2 param2)
		{
			if( m_pFunc )
			{
				m_pFunc(param1, param2);
			}
		}

	protected:
		FUNC	m_pFunc;
	};

	template<class Arg1,class Arg2, class Arg3>
	class CGlobalFuncArg3 : public CFunctorArg3<Arg1,Arg2,Arg3>
	{
	public:
		typedef void (*FUNC)(Arg1 param1, Arg2 param2, Arg3 param3);
		CGlobalFuncArg3(FUNC p) 
			: m_pFunc(p)
		{
			;
		}

		virtual ~CGlobalFuncArg3()
		{
			;
		}

		virtual void operator()(Arg1 param1, Arg2 param2, Arg3 param3)
		{
			if( m_pFunc )
			{
				m_pFunc(param1, param2, param3);
			}
		}

	protected:
		FUNC	m_pFunc;
	};

	template<class Arg1,class Arg2, class Arg3, class Arg4>
	class CGlobalFuncArg4 : public CFunctorArg4<Arg1,Arg2,Arg3,Arg4>
	{
	public:
		typedef void (*FUNC)(Arg1 param1, Arg2 param2, Arg3 param3, Arg4 param4);
		CGlobalFuncArg4(FUNC p) 
			: m_pFunc(p)
		{
			;
		}

		virtual ~CGlobalFuncArg4()
		{
			;
		}

		virtual void operator()(Arg1 param1, Arg2 param2, Arg3 param3, Arg4 param4)
		{
			if( m_pFunc )
			{
				m_pFunc(param1, param2, param3, param4);
			}
		}

	protected:
		FUNC	m_pFunc;
	};

	template<class Arg1,class Arg2, class Arg3, class Arg4, class Arg5>
	class CGlobalFuncArg5 : public CFunctorArg5<Arg1,Arg2,Arg3,Arg4,Arg5>
	{
	public:
		typedef void (*FUNC)(Arg1 param1, Arg2 param2, Arg3 param3, Arg4 param4, Arg5 param5);
		CGlobalFuncArg5(FUNC p) 
			: m_pFunc(p)
		{
			;
		}

		virtual ~CGlobalFuncArg5()
		{
			;
		}

		virtual void operator()(Arg1 param1, Arg2 param2, Arg3 param3, Arg4 param4, Arg5 param5)
		{
			if( m_pFunc )
			{
				m_pFunc(param1, param2, param3, param4, param5);
			}
		}

	protected:
		FUNC	m_pFunc;
	};

	//----------------------------------------------------------------------------------------------
	template<class T>
		class CMemberFuncArg0 : public CFunctorArg0
		{
		public:
			typedef void (T::*FUNC)();
			CMemberFuncArg0(T* p, FUNC func)
				: m_pObj(p)
				, m_pFunc(func)
			{
				;
			}

			virtual ~CMemberFuncArg0()
			{
				;
			}

			virtual void operator()()
			{
				if( m_pObj && m_pFunc )
				{
					return (m_pObj->*m_pFunc)();
				}

				return;
			}


		protected:
			T*		m_pObj;
			FUNC	m_pFunc;
		};



	template<class T, class Ret>
	class CMemberFuncRetArg0 : public CFunctorRetArg0<Ret>
	{
	public:
		typedef Ret (T::*FUNC)();
		CMemberFuncRetArg0(T* p, FUNC func)
			: m_pObj(p)
			, m_pFunc(func)
		{
			;
		}

		virtual ~CMemberFuncRetArg0()
		{
			;
		}

		virtual Ret operator()()
		{
			if( m_pObj && m_pFunc )
			{
				return (m_pObj->*m_pFunc)();
			}

			return (0);
		}


	protected:
		T*		m_pObj;
		FUNC	m_pFunc;
	};


	template<class T, class Arg1>
	class CMemberFuncArg1 : public CFunctorArg1<Arg1>
	{
	public:
		typedef void (T::*FUNC)(Arg1 param);
		CMemberFuncArg1(T* p, FUNC func) 
			: m_pObj(p)
			, m_pFunc(func)
		{
			;
		}

		virtual ~CMemberFuncArg1()
		{
			;
		}

		virtual void operator()(Arg1 arg1)
		{
			if( m_pObj && m_pFunc )
			{
				(m_pObj->*m_pFunc)(arg1);
			}
		}

		
	protected:
		T*		m_pObj;
		FUNC	m_pFunc;
	};

	template<class T, class Arg1, class Arg2>
	class CMemberFuncArg2 : public CFunctorArg2<Arg1, Arg2>
	{
	public:
		typedef void (T::*FUNC)(Arg1 arg1, Arg2 arg2);
		CMemberFuncArg2(T* p, FUNC func) 
			: m_pObj(p)
			, m_pFunc(func)
		{
			;
		}

		virtual ~CMemberFuncArg2()
		{
			;
		}

		virtual void operator()(Arg1 arg1, Arg2 arg2)
		{
			if( m_pObj && m_pFunc )
			{
				(m_pObj->*m_pFunc)(arg1, arg2);
			}
		}

		
	protected:
		T*		m_pObj;
		FUNC	m_pFunc;
	};

	template<class T, class Arg1, class Arg2, class Arg3 >
	class CMemberFuncArg3 : public CFunctorArg3<Arg1, Arg2, Arg3>
	{
	public:
		typedef void (T::*FUNC)(Arg1 , Arg2 , Arg3);
		CMemberFuncArg3(T* p, FUNC func) 
			: m_pObj(p)
			, m_pFunc(func)
		{
			;
		}

		virtual ~CMemberFuncArg3()
		{
			;
		}

		virtual void operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3)
		{
			if( m_pObj && m_pFunc )
			{
				(m_pObj->*m_pFunc)(arg1, arg2, arg3);
			}
		}

		
	protected:
		T*		m_pObj;
		FUNC	m_pFunc;
	};

	template<class T, class Arg1, class Arg2, class Arg3, class Arg4>
	class CMemberFuncArg4 : public CFunctorArg4<Arg1, Arg2, Arg3, Arg4>
	{
	public:
		typedef void (T::*FUNC)(Arg1 arg1, Arg2 arg2, Arg3, Arg4);
		CMemberFuncArg4(T* p, FUNC func) 
			: m_pObj(p)
			, m_pFunc(func)
		{
			;
		}

		virtual ~CMemberFuncArg4()
		{
			;
		}

		virtual void operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
		{
			if( m_pObj && m_pFunc )
			{
				(m_pObj->*m_pFunc)(arg1, arg2, arg3, arg4);
			}
		}

		
	protected:
		T*		m_pObj;
		FUNC	m_pFunc;
	};
	

	//----------------------------------------------------------------------------------------------

	template<class Arg1>
	CGlobalFuncArg1<Arg1>* makeFunctor( void (*func)(Arg1 param1) )
	{
		return new CGlobalFuncArg1<Arg1>(func);
	}

	template<class Arg1,class Arg2>
	CGlobalFuncArg2<Arg1,Arg2>* makeFunctor( void (*func)(Arg1 param1, Arg2 param2) )
	{
		return new CGlobalFuncArg2<Arg1,Arg2>(func);
	}

	template<class Arg1,class Arg2, class Arg3>
	CGlobalFuncArg3<Arg1,Arg2,Arg3>* makeFunctor( void (*func)(Arg1 param1, Arg2 param2, Arg3 param3) )
	{
		return new CGlobalFuncArg3<Arg1,Arg2,Arg3>(func);
	}

	//template<class Arg1,class Arg2, class Arg3, class Arg4>
	//CGlobalFuncArg4<Arg1,Arg2,Arg3,Arg4>* makeFunctor( void (*func)(Arg1 param1, Arg2 param2, Arg3 param3, Arg4 param4) )
	//{
	//	return new CGlobalFuncArg4<Arg1,Arg2,Arg3,Arg4>(func);
	//}
	template<class T>
	CMemberFuncArg0<T>* makeFunctor0( T* p, void (T::*func)() )
	{
		CMemberFuncArg0<T>* pRet = new CMemberFuncArg0<T>(p, func);
		pRet->autorelease();
		return pRet;
	}


	template<class T, class Ret>
	CMemberFuncRetArg0<T, Ret>* makeFunctorWithRet( T* p, Ret (T::*func)() )
	{
		CMemberFuncRetArg0<T, Ret>* pRet = new CMemberFuncRetArg0<T,Ret>(p, func);
		pRet->autorelease();
		return pRet;
	}

	template<class T, class Arg1>
	CMemberFuncArg1<T, Arg1>* makeFunctor( T* p, void (T::*func)(Arg1 param1) )
	{
		CMemberFuncArg1<T, Arg1>* pRet = new CMemberFuncArg1<T,Arg1>(p, func);
		pRet->autorelease();
		return pRet;
	}

	template<class T, class Arg1, class Arg2>
	CMemberFuncArg2<T, Arg1, Arg2>* makeFunctor( T* p, void (T::*func)(Arg1, Arg2) )
	{
		CMemberFuncArg2<T, Arg1, Arg2>* pRet = new CMemberFuncArg2<T,Arg1,Arg2>(p, func);
		pRet->autorelease();
		return pRet;
	}

	template<class T, class Arg1, class Arg2, class Arg3>
	CMemberFuncArg3<T, Arg1, Arg2, Arg3>* makeFunctor( T* p, void (T::*func)(Arg1, Arg2, Arg3) )
	{
		CMemberFuncArg3<T, Arg1, Arg2, Arg3>* pRet = new CMemberFuncArg3<T,Arg1, Arg2, Arg3>(p, func);
		pRet->autorelease();
		return pRet;
	}

	template<class T, class Arg1, class Arg2, class Arg3, class Arg4>
	CMemberFuncArg4<T, Arg1, Arg2,Arg3, Arg4>* makeFunctor( T* p, void (T::*func)(Arg1, Arg2, Arg3, Arg4) )
	{
		CMemberFuncArg4<T, Arg1, Arg2,Arg3, Arg4>*pRet = new CMemberFuncArg4<T,Arg1,Arg2,Arg3, Arg4>(p, func);
		pRet->autorelease();
		return pRet;
	}

	typedef CFunctorArg1<const string&> 					CFunctor;
    //typedef CFunctorArg0<> 					                CFunctor0;

#endif
