#ifndef _GRAPHICSMESSAGE_DEFINE_H
#define _GRAPHICSMESSAGE_DEFINE_H

#include "svs.h"
#include "CEOL.hpp"

enum EGraphicsMsgID
{
	eGraphicsMsgID_GuideLine,
	eGraphicsMsgID_PosSize,
	eGraphicsMsgID_ShowStartUpImage,
//	eGraphicsMsgID_NotifyGraphicReady
};

struct tagGuideLine : public tagBaseMessage
{
	tagGuideLine()
	: tagBaseMessage(0, eGraphicsMsgID_GuideLine)
	{
		_uidx = EOL::eOffReverseGuideline;
	}

	UInt32 _uidx;

};

struct tagGraphicsPosSize: public tagBaseMessage
{
	tagGraphicsPosSize()
	: tagBaseMessage(0, eGraphicsMsgID_PosSize)
	{
		;
	}

	CRectangle	_rc;
};

struct tagshowStartUpImage : public tagBaseMessage
{
	tagshowStartUpImage()
	: tagBaseMessage(0, eGraphicsMsgID_ShowStartUpImage)
	{
		bShowStartUpImage = FALSE;
	}

	Int32 idx;
	BOOLEAN  bShowStartUpImage;
};
#if 0
struct tagNotifyIfGraphicReady : public tagBaseMessage
{
	tagNotifyIfGraphicReady()
	: tagBaseMessage(0, eGraphicsMsgID_NotifyGraphicReady)
	{
		bNeedToNotifyLayerReady = FALSE;
	}
	BOOLEAN  bNeedToNotifyLayerReady;
};
#endif

#endif
