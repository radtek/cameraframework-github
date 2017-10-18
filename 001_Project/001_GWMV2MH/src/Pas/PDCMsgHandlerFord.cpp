
#include "Pas/PDCMsgHandlerFord.h"
#include "Pas/PDCServiceFord.h"
#include "Pas/PDCMsgDefineFord.h"

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {
namespace Pas {

PDCMsgHandlerFord::PDCMsgHandlerFord()
{
	PDCA_LOG_INFO("PDCMsgHandlerFord created \n") ;
}

VOID PDCMsgHandlerFord::_handle(UInt32 uiType, UInt32 uiEventID, const string& pData)
{
	//int* ptmp = (int*)pData;
	//PDCA_LOG_INFO("start PDCMsgHandlerFord _handle: uiType[%d] - data0[%d]- data1[%d] \n",uiType,ptmp[0],ptmp[1]) ;
	switch( uiType )
	{
		default:
			PDCServiceFord::getInstance()->dispatchEvent(uiType, pData);
		break;
	}
	//PDCA_LOG_INFO("end PDCMsgHandlerFord _handle: uiType[%d] - data0[%d]- data1[%d] \n",uiType,ptmp[0],ptmp[1]) ;
	return;
}

} // namespace Pas
} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman