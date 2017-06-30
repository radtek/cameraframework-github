#ifndef _ICAN_ITERF_H
#define _ICAN_ITERF_H

#include "foundation.h"

class ICANIterf
{
public:// method
	virtual void SetUpCANCmdTable(map<string,CFunctor*>* mapCANCMD){};
};

#endif
