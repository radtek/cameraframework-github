#ifndef _PDCMGDEFINEFORD_H
#define _PDCMGDEFINEFORD_H

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

#endif
