#ifndef _CDIAGNOSTIC_CLIENT_HPP
#define _CDIAGNOSTIC_CLIENT_HPP

#include "svs.h"
#include "CCamera.hpp"

class CDiagnosticClient : public CBaseDBUSParser
{
public:	//enum struct typedef
	enum EStatus
	{
		eNOT_AVAILABLE 		= 0,
		eACTIVE_NOTCONFIRM,
		eACTIVE_CONFIRM,
		eINACTIVE_NOTCONFIRM,
		eINACTIVE_CONFIRM,
	};

	enum EFaultID
	{
		eFaultID_Camera1Invalid = 66,
		eFaultID_Camera2Invalid = 67,
	};

public: // method
   static CDiagnosticClient* getInstance();
   static void delInstance();
   ~CDiagnosticClient();

   // request
   void reportFault(EStatus eFaultStatus, CCamera::EPos ePos);

   // signal
   void onCheckFault(const string& strData);

protected: // method
   CDiagnosticClient();

private: // data
   static CDiagnosticClient*		s_pInstance;

};

#endif
