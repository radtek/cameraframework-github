#ifndef _IADAS_CTRL_H
#define _IADAS_CTRL_H

class IAdasCtrl
{
public:
	virtual BOOLEAN initialize() = 0;
	virtual void	unInitialize() = 0;
	virtual void 	beforeHandleMessageQueue() = 0;
	virtual void 	afterHandleMessageQueue() = 0;
	virtual BOOLEAN	isNeedFastADAS() = 0;
	virtual void	startFastADAS() = 0;
	virtual void	startNormalADAS() = 0;
    virtual void	checkSystemEventAfterStartUp() = 0;
};

#endif
