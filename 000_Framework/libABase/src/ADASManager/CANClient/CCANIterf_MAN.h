#ifndef _CCAN_INTF_MAN_H
#define _CCAN_INTF_MAN_H

#include "svs.h"
#include "ICANIterf.h"
class CCANIterfMAN : public ICANIterf , CBasePPSParser
{

public:// method
	void SetUpCANCmdTable(map<string,CFunctor*>* mapCANCMD);
	static CCANIterfMAN* getInstance();
	~CCANIterfMAN();
private:
	CCANIterfMAN();
	static CCANIterfMAN*		s_pInstance;
	void onCANReverseGear(const string& strData);
    void onCruiseControlVehSpeedMAN(const string& strData);
    void ondebug(const string& strData);
};

#endif
