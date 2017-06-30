#include "CPPS.h"

CPPS* CPPS::s_pInstance = NULL;

CPPS* CPPS::getInstance()
{
	if( s_pInstance == NULL )
	{
		s_pInstance = new CPPS();
	}

	return s_pInstance;
}

void CPPS::deleteInstance()
{
	if( s_pInstance )
	{
		s_pInstance->quit();
		s_pInstance->join();
		delete s_pInstance;
		s_pInstance = NULL;
	}
}

CPPS::CPPS()
: m_bQuit(FALSE)
{
	m_aryPPSObject.reserve(10);
}

CPPS::~CPPS()
{

}

void CPPS::start()
{
	m_hThread.start(*this);
}

void CPPS::quit()
{
	m_bQuit = true;
}

void CPPS::join()
{
	m_hThread.join();
}
TRC_SCOPE_DEF(ADAS, CPPS, run);
void CPPS::run()
{
    TRC_SCOPE(ADAS, CPPS, run);
#ifdef PLATFORM_QNX
	pthread_setname_np(pthread_self(), "CPPS");
#endif

	DBG_MSG(("PPS Thread start~~~~~~~~~~\n"));

	fd_set rfd,rfdbak;
	FD_ZERO( &rfd );
	Int32 maxfd = -1;
	for(Array<tagObject>::iterator iter = m_aryPPSObject.begin();
				iter != m_aryPPSObject.end(); ++iter)
	{
		tagObject& object = (*iter);
		DBG_MSG(("try to open PPS Object =%s \n",object.strName.c_str()));
		Int32 fd = openPPSObject(object.strName);
		if( fd == -1 )
		{
			DBG_ERROR(("open PPS Object failed\n"));
			continue;
		}
      else
      {
			DBG_MSG(("success! open PPS Object =%s \n",object.strName.c_str()));
      }

		//m_mapFDName.insert(makePair(fd,(*iter).first));
		object.fd = fd;

		FD_SET( fd, &rfd ); /*将fd加入rfd集合*/
		DBG_MSG(("fd= %d rfd = %d\n",fd,rfd));
		if( maxfd < fd )
			maxfd = fd;
	}

	if( maxfd == -1 )
	{
		DBG_MSG(("No PPS Object need to read\n"));
		return;
	}

	DBG_MSG(("PPS Thread loop start~~~~~~~~~~\n"));
	//struct timeval intervaltime;
	memcpy(&rfdbak,&rfd,sizeof(fd_set));

	while (!m_bQuit)
	{
		memcpy(&rfd,&rfdbak,sizeof(fd_set));

		//intervaltime.tv_usec = 2000;
		//usleep(200000);
		DBG_MSG(("start-------write select: maxfd = %d rfd = %d\n",maxfd,rfd));
		//Int32 n = select( 1 + maxfd, 0, &rfd, 0, &intervaltime);
		Int32 n = select( 1 + maxfd, &rfd, 0,  0, NULL);
		DBG_MSG(("end  -------write select: maxfd = %d rfd = %d\n",maxfd,rfd));
		//DBG_MSG(("PPS Thread: select %d\n",n));
		if( n == -1 )
			break;

		switch(n)
		{
		//case -1:
		//	perror( "select" );
		//	break;
		case  0:
			DBG_MSG(( "select timed out\n" ));
			break;
		default:

			for(Array<tagObject>::iterator iter = m_aryPPSObject.begin();
					iter != m_aryPPSObject.end(); ++iter)
			{
				Int32 curFd = (*iter).fd;
				if( FD_ISSET(curFd, &rfd) )
				{
					string strName = (*iter).strName;
					CBasePPSParser* pHooker = (*iter).pHooker;
					if( pHooker )
					{
						//call the call back on the pps node write access happened(but value may not change), if( pHooker->is)
						static const UInt32 RVS_PPS_DEFAILT_SIZE = 1024;
						char buf[RVS_PPS_DEFAILT_SIZE];
						DBG_MSG(("ADAS-PPS Thread read wait for: select %d - %s\n",n, strName.c_str()));
						memset(buf,0,sizeof(buf));
						Int32 nRead = read(curFd, buf, sizeof(buf)-1);
						if (nRead > 0)
						{
							//DBG_MSG(("PPS Thread: select %d %s\n",n, strName.c_str()));
							buf[nRead] = 0;
							DBG_MSG(("PPS::run: read %s\n", buf));
							pHooker->process(strName,buf);
						}
					}
				}
			}
			break;
		}
	}

	DBG_MSG(("PPS Thread loop end~~~~~~~~~~\n"));

	for(Array<tagObject>::iterator iter = m_aryPPSObject.begin();
					iter != m_aryPPSObject.end(); ++iter)
	{
		Int32 fd = (*iter).fd;
		if( fd != -1 )
		{
			FD_CLR(fd, &rfd);
			close(fd);
		}
	}

	DBG_MSG(("PPS Thread end~~~~~~~~~~\n"));
}

void CPPS::registerHooker(const string& strName, CBasePPSParser* pHooker)
{
	tagObject object;
    object.fd = 0;
	object.strName = strName;
	object.pHooker = pHooker;

	m_aryPPSObject.push_back(object);
}

TRC_SCOPE_DEF(ADAS, CPPS, openPPSObject);
Int32 CPPS::openPPSObject(const string& strName)
{
	Int32 fd = -1;
	fd = open(  strName.c_str(), O_RDONLY);
	if ( fd < 0)
	{
        TRC_SCOPE(ADAS, CPPS, openPPSObject);
		DBG_ERROR(("CPPS::openPPSObject:can't open PPS %s\n", strName.c_str()));
	}
	return fd;
}

CBasePPSParser*	CPPS::getHooker(fd_set& rfd, string& strName, Int32& fd)
{
	for(Array<tagObject>::iterator iter = m_aryPPSObject.begin();
		iter != m_aryPPSObject.end(); ++iter)
	{
		Int32 curFd = (*iter).fd;
		if( FD_ISSET(curFd, &rfd) )
		{
			strName = (*iter).strName;
			return (*iter).pHooker;
		}
	}

	return NULL;
}
