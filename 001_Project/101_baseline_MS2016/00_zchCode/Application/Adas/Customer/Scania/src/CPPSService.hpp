#ifndef _CPPS_SERVICE_H_
#define _CPPS_SERVICE_H_

#include "svs.h"

class CPPSService
{
public:
   static CPPSService* getInstance();
   static void delInstance();
   ~CPPSService();

   BOOLEAN getUIntValue(const string& strKey, UInt32* valueBuf);
   BOOLEAN getIntValue(const string& strKey, Int32* valueBuf);
   BOOLEAN initialize(const char* szFilePath);
   
private:
   CPPSService();
   static CPPSService * m_pInstance;
   map<string, string>	m_mapParam;
   BOOLEAN DecodePPSData(const char *name,const char* value, UInt32* pbuf);

   string m_strFilePath;
};

#endif // _CPPS_SERVICE_H_

