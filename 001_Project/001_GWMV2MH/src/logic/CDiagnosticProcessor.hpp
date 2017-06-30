#ifndef _CDIAGNOSTICROCESSOR_HPP_
#define _CDIAGNOSTICROCESSOR_HPP_

#include "svs.h"
#include "CDiagnosticClient.hpp"
#include "CCameraFaultCheck.hpp"
#include "CCamera.hpp"

class CDiagnosticProcessor : public CMessageSubHandler
{
public: // enum struct embedded class


public:
   static CDiagnosticProcessor* 	getInstance();
   static void 						delInstance();
   virtual ~CDiagnosticProcessor();

   DECLARE_DISPATCH

   // CDiagnosticClient
   void onCheckFaultStart(void* );
   void onCheckFaultStop(void*);
   void onCheckFaultResetCamera1(void*);
   void onCheckFaultResetCamera2(void*);

   //
   void	onVsyncValid(CCamera::EPos ePos);
   void onVsyncInvalid(CCamera::EPos ePos);
   void	onShowCamera(CCamera::EPos ePos);
   void	onHideCamera(CCamera::EPos ePos);

private:
   CDiagnosticProcessor();

private: // data
   static CDiagnosticProcessor* s_pInstance;
   //BOOLEAN				m_bInCheckCameraFaults[2];
   CCameraFaultCheck*	m_camera1FaultCheck;
   CCameraFaultCheck*	m_camera2FaultCheck;
};

#endif

