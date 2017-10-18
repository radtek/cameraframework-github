
#include "Pas/PDCGraphicFord.h"

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {
namespace Pas {

PDCGraphicFord::PDCGraphicFord(IGraphicPDC* pIGraphicPDC)
:m_pIGraphicPDC(pIGraphicPDC)
{
	m_ePDCDayNightMode = eNOTSET_NIGHTMOD;
	m_ePDCDedicateMode = eNOTSET_DEDIMOD;
	m_ePDCGraphicState = eDISABLED;
	m_ePDCSegment = eNOTSET_SEGMENT;
}

PDCGraphicFord::~PDCGraphicFord()
{
	//m_pGraphicPDCFord->destory();
}

} // namespace Pas
} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman