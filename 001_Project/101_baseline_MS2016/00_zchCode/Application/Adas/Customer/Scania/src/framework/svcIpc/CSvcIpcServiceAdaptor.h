#ifndef _CSVCIPC_SERVICE_ADAPTOR_H
#define _CSVCIPC_SERVICE_ADAPTOR_H

#include "foundation.h"
#include "CBaseDBUSParser.h"

class CSvcIpcServiceAdaptor
{
public:
	static CSvcIpcServiceAdaptor*	getInstance();
	static void 					deleteInstance();

	void	connectDBus();
	void	disConnectDBus();
	void	registerClientParser(CBaseDBUSParser* pParser);
	void	registerServiceParser(CBaseDBUSParser* pParser);
	BOOLEAN	isConnected() const	{ return m_bIsConnected;	}

protected:
	CSvcIpcServiceAdaptor();
	~CSvcIpcServiceAdaptor();

private:
	static CSvcIpcServiceAdaptor*	s_pInstance;

	Array<CBaseDBUSParser*>	m_aryClientParser;
	CBaseDBUSParser*		m_pServiceParser;
	BOOLEAN					m_bIsConnected;
};

#endif
