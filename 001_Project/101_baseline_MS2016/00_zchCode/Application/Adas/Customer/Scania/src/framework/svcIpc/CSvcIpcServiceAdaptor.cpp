#include "CSvcIpcServiceAdaptor.h"
#include "CSvcIpc.h"

CSvcIpcServiceAdaptor* CSvcIpcServiceAdaptor::s_pInstance = NULL;

CSvcIpcServiceAdaptor* CSvcIpcServiceAdaptor::getInstance()
{
	if( s_pInstance == NULL )
	{
		s_pInstance = new CSvcIpcServiceAdaptor();
	}

	return s_pInstance;
}

void CSvcIpcServiceAdaptor::deleteInstance()
{
	if( s_pInstance != NULL )
	{
		delete s_pInstance;
		s_pInstance = NULL;
	}
}

CSvcIpcServiceAdaptor::CSvcIpcServiceAdaptor()
: m_pServiceParser(NULL)
, m_bIsConnected(FALSE)
{
	;
}

CSvcIpcServiceAdaptor::~CSvcIpcServiceAdaptor()
{
	;
}
TRC_SCOPE_DEF(ADAS, CSvcIpcServiceAdaptor, connectDBus);
void CSvcIpcServiceAdaptor::connectDBus()
{
    TRC_SCOPE(ADAS, CSvcIpcServiceAdaptor, connectDBus);
	CSvcIpc * psvcipc = CSvcIpc::getInstance();
	psvcipc->start();

	if( m_pServiceParser )
	{
		m_pServiceParser->connect(psvcipc);
	}

	for(UInt32 i = 0 ; i < m_aryClientParser.size(); ++i)
	{
		m_aryClientParser[i]->connect(psvcipc);
	}

	m_bIsConnected = TRUE;
	DBG_MSG(("CSvcIpcServiceAdaptor::connectDBus end!\n"));

	//return TRUE;
}

TRC_SCOPE_DEF(ADAS, CSvcIpcServiceAdaptor, disConnectDBus);
void CSvcIpcServiceAdaptor::disConnectDBus()
{
    TRC_SCOPE(ADAS, CSvcIpcServiceAdaptor, disConnectDBus);
	m_bIsConnected = FALSE;
	DBG_MSG(("CSvcIpcServiceAdaptor::disConnectDBus begin!\n"));
	CSvcIpc * psvcipc = CSvcIpc::getInstance();
	for(UInt32 i = 0 ; i < m_aryClientParser.size(); ++i)
	{
		m_aryClientParser[i]->disconnect();
		delete m_aryClientParser[i];
	}

	DBG_MSG(("CSvcIpcServiceAdaptor::disConnectDBus 1!\n"));
	m_aryClientParser.clear();

	DBG_MSG(("CSvcIpcServiceAdaptor::disConnectDBus 2!\n"));
	if( m_pServiceParser )
	{
		m_pServiceParser->disconnect();
		delete m_pServiceParser;
		m_pServiceParser = NULL;
	}

	DBG_MSG(("CSvcIpcServiceAdaptor::disConnectDBus 3!\n"));

	psvcipc->stop();

	DBG_MSG(("CSvcIpcServiceAdaptor::disConnectDBus 4!\n"));

	CSvcIpc::deleteInstance();

	DBG_MSG(("CSvcIpcServiceAdaptor::disConnectDBus end!\n"));
}

void CSvcIpcServiceAdaptor::registerClientParser(CBaseDBUSParser* pParser)
{
	if( pParser )
	{

		m_aryClientParser.push_back(pParser);
	}
}

TRC_SCOPE_DEF(ADAS, CSvcIpcServiceAdaptor, registerServiceParser);
void CSvcIpcServiceAdaptor::registerServiceParser(CBaseDBUSParser* pParser)
{
    TRC_SCOPE(ADAS, CSvcIpcServiceAdaptor, registerServiceParser);
	if( m_pServiceParser == NULL )
	{

		m_pServiceParser = pParser;
	}
	else
	{
		DBG_MSG(("CSvcIpcServiceAdaptoR::registerServiceParser ServiceParser has exsited!\n"));
	}
}


