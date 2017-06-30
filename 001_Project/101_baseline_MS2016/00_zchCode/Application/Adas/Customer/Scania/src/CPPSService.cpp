#include "CPPSService.hpp"

#ifdef PLATFORM_QNX
	#include <sys/pps.h>
	#include <fcntl.h>
#endif

//test
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
//using namespace std;
//EOL change buf size request:(4096*2)
#define RVS_PPS_DEFAILT_SIZE           8192
#define WAIT_TIME_MSEC                  (100000)       // 100ms

CPPSService * CPPSService::m_pInstance = NULL;

CPPSService::CPPSService()
{   
	;
}

CPPSService::~CPPSService()
{

}

CPPSService* CPPSService::getInstance()
{
   if(m_pInstance == NULL)
   {
      m_pInstance = new CPPSService();
   }
   return m_pInstance;
}

void CPPSService::delInstance()
{
   if(m_pInstance != NULL)
   {
      delete m_pInstance;
      m_pInstance = NULL;
   }
}

TRC_SCOPE_DEF(ADAS, CPPSService, initialize);
BOOLEAN CPPSService::initialize(const char* szFilePath)
{
	TRC_SCOPE(ADAS, CPPSService, initialize);

	if( szFilePath == NULL )
	{
		DBG_ERROR(("CPPSService::initialize: szFilePath==NULL"));
		return FALSE;
	}

	m_strFilePath = szFilePath;
	pps_attrib_t info;
	pps_status_t rc;
	char buffer[RVS_PPS_DEFAILT_SIZE];
	char *ppsdata = buffer;
	Int32 n;
	static Int32 timeout = 5;

	Int32 fd = -1;
	while ( (fd = open(m_strFilePath.c_str(), O_RDONLY)) < 0)
	{
		usleep(WAIT_TIME_MSEC);
		if(timeout >=0)
		{
			timeout--;
		}
		else
		{
			//close(fd);
			DBG_ERROR(("PSService::initialize: timer out, Cannot open %s yet!!!\n", m_strFilePath.c_str()));
			return FALSE;
		}
	}

	memset(&info, 0, sizeof(info));

	n = read(fd, ppsdata, RVS_PPS_DEFAILT_SIZE);
	if(n <= 0)
	{
		close(fd);
		DBG_ERROR(("PPSService::initialize: Cannot read %s yet!!!",  m_strFilePath.c_str()));
		return FALSE;
	}

	close(fd);

	DBG_MSG(("%s\n", ppsdata));
	while((rc = ppsparse(&ppsdata, NULL, NULL, &info,0)) != PPS_END)
	{
	  if((PPS_ATTRIBUTE == rc))
	  {
		  if( info.attr_name != NULL && info.value != NULL )
		  {
			  m_mapParam.insert(makePair(info.attr_name,info.value));
		  }
	  }
	}

	return TRUE;
}

//function which is responsible to validate data using lookup table and send to IOC through /dev/ipc/chX.
TRC_SCOPE_DEF(ADAS, CPPSService, DecodePPSData);
BOOLEAN  CPPSService::DecodePPSData(const char *name, const char* value, UInt32* pbuf)
{
    TRC_SCOPE(ADAS, CPPSService, DecodePPSData);
    char delim = ',';
    int i = 0;
    std::string tempStr1="";
    std::string tempStr="";
    tempStr1 = value;
    std::string::iterator it=tempStr1.begin(); 
    if('['==*it)
    {
       DBG_MSG(("DecodePPSData<-- SigName: %s value: %s", name, value));
       tempStr.assign(tempStr1,1,tempStr1.length()-2);
    }
    else
    {
    	return FALSE;
    }
    std::stringstream ss(tempStr);
    string item;

    while(std::getline(ss, item, delim)) {
    	pbuf[i] =std::atoi(const_cast<char*>(item.c_str()));
    	i++;
    }
    for(int cnt=0; cnt<i; cnt++)
    {
        DBG_MSG(("DecodePPSData result array[%d] = %d", cnt, pbuf[cnt]));
    }
    return TRUE;
    //printf(" Size of vectData : %d",i);

}

TRC_SCOPE_DEF(ADAS, CPPSService, getUIntValue);
BOOLEAN CPPSService::getUIntValue(const string& strKey, UInt32* valueBuf)
{
	TRC_SCOPE(ADAS, CPPSService, getUIntValue);
	const string strValue = m_mapParam[strKey];

	if( !strValue.empty() )
	{
        if(!DecodePPSData(strKey.c_str(), strValue.c_str(), valueBuf))
        {
		    *(valueBuf) = StringUtil::toUInt(strValue.c_str());
        }
		DBG_MSG(("CPPSService get getUIntValue success %s= %d\n",strKey.c_str(),*valueBuf));
		return TRUE;
	}

	return FALSE;
}

//not support to decode signed value as not request so far
TRC_SCOPE_DEF(ADAS, CPPSService, getIntValue);
BOOLEAN CPPSService::getIntValue(const string& strKey, Int32* valueBuf)
{
    TRC_SCOPE(ADAS, CPPSService, getIntValue);
	const string strValue = m_mapParam[strKey];

	if( !strValue.empty() )
	{
		*(valueBuf) = StringUtil::toInt(strValue.c_str());

		DBG_MSG(("CPPSService get getIntValue success %s= %d\n",strKey.c_str(),*valueBuf));
		return TRUE;
	}

	return FALSE;
}

