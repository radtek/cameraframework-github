
#ifndef __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_PDCGRAPHICFORD_H__
#define __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_PDCGRAPHICFORD_H__

#include "ADASManager/PAS/PDCGraphic.h"
#include "ADASManager/PAS/GraphicCore/GraphicVPAFord.h"
#include "ADASManager/PAS/GraphicCore/IGraphicPDC.h"

using Harman::Adas::AFramework::ABase::ADASManager::IGraphicPDC;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {
namespace Pas {

class PDCGraphicFord
{
public:
	enum ePDCGraphicState {
		eDISABLED,
		eENABLED
	};
	enum ePDCDayNightMode {
		eNOTSET_NIGHTMOD,
		eDAY,
		eNIGHT
	};
	enum ePDCDedicateMode {
		eNOTSET_DEDIMOD,
		eDEDICATE,
		eSHARESCREEN
	};
	enum ePDCSegment {
		eNOTSET_SEGMENT,
		ePOS1,
		ePOS2
	};

	PDCGraphicFord(IGraphicPDC* pIGraphicPDC);
	~PDCGraphicFord();
private:
	IGraphicPDC* m_pIGraphicPDC;
	ePDCDayNightMode m_ePDCDayNightMode ;
	ePDCDedicateMode m_ePDCDedicateMode ;
	ePDCGraphicState m_ePDCGraphicState ;
	ePDCSegment m_ePDCSegment ;
};

} // namespace Pas
} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_PDCGRAPHICFORD_H__