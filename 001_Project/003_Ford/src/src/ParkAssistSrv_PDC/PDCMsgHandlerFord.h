//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Ford-LCIS
//  @ File Name : PDCMsgHandlerFord.h
//  @ Date : 2016-11-23
//  @ Author : Guofeng.lu@harman.com
//
//


#if !defined(_PDCMSGHANDLERFORD_H)
#define _PDCMSGHANDLERFORD_H

#include "CMessageHandler.h"

class PDCMsgHandlerFord : public CMessageHandler
{
public:
	PDCMsgHandlerFord();

protected:
	virtual void _handle(unsigned int uiType, unsigned int uiID, void* pData);
};
#endif  //_PDCMSGHANDLERFORD_H
