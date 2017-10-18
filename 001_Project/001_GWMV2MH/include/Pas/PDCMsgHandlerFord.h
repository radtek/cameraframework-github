
#ifndef __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_PDCMSGHANDLERFORD_H__
#define __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_PDCMSGHANDLERFORD_H__

#include "CMessageHandler.h"

using Harman::Adas::AFramework::AFoundation::CMessageHandler;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {
namespace Pas {

class PDCMsgHandlerFord : public CMessageHandler
{
public:
	PDCMsgHandlerFord();

protected:
    virtual VOID _handle(UInt32 uiType, UInt32 uiEventID, const string& pData) override;
};

} // namespace Pas
} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_PDCMSGHANDLERFORD_H__