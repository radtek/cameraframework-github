#ifndef _ADAS_SVS_H
#define _ADAS_SVS_H



class CBaseDBUSParser;

class CBasePPSParser;
class CPPS;


#include "foundation.h"
#include "jsoncpp/json.h"
#include "svcipc/svcipc.h"

// svcIpc
#include "svcIpc/ISvcIpc.h"
#include "svcIpc/ISvcIpcHooker.h"
#include "svcIpc/CSvcIpc.h"
#include "svcIpc/CBaseDBUSParser.h"
#include "svcIpc/CSvcIpcServiceAdaptor.h"

// pps
#include "pps/CBasePPSParser.h"
#include "pps/CPPS.h"

// logic

#include "IAdasCtrl.h"
#include "CAdasManager.h"

#endif
