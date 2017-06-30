#ifndef _CPPS_H
#define _CPPS_H

#include "foundation.h"
#include "CBasePPSParser.h"

class CPPS : public IRunnable
{
public://enum struct
	struct tagObject
	{
		Int32 			fd;
		string			strName;
		CBasePPSParser*	pHooker;
	};

public://method
	static CPPS*	getInstance();
	static void		deleteInstance();
	virtual ~CPPS();

	virtual void start();
	virtual void quit();
	virtual void join();
	virtual void run();

	void	registerHooker(const string& strName, CBasePPSParser* pHooker);

protected: // method
	CPPS();

	Int32	openPPSObject(const string& strName);
	CBasePPSParser*	getHooker(fd_set& rfd, string& strName, Int32& fd);

private:
	static CPPS*		s_pInstance;

	 Thread  			m_hThread;
	 BOOLEAN		 	m_bQuit;

	//map<string,CBasePPSParser*>	m_mapNameHooker;
	//map<Int32,string>	m_mapFDName;
	 Array<tagObject>	m_aryPPSObject;
};

#endif
