
#ifndef __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_PDCMGDEFINEFORD_H__
#define __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_PDCMGDEFINEFORD_H__

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {
namespace Pas {

enum EMsgType
{
	eMSG_HMI,
	eMSG_AMB,
	eMSG_INTERNAL,
};

enum EPdcEvent
{
	ePDC_SHOW,
	ePDC_HIDE,
	ePDC_SETMODE_DAYNIGHT,
	ePDC_SETPOSITON,
	ePDC_SETSIZE,
	ePDC_UPDATE_DISTANCE,
};

#define DATASIZE 512

typedef struct stTagPDCEvents
{
	int MsgType;
	int EventID;
	char data[DATASIZE];
}stPDCEvents;

} // namespace Pas
} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_APROJECT_GWMV2MH_PAS_PDCMGDEFINEFORD_H__