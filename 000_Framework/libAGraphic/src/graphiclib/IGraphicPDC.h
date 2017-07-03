#if !defined(_IGraphicPDC_H)
#define _IGraphicPDC_H

class IGraphicPDC {

public:
	virtual bool InitPDC(int screenWidth, int screenHeight)= 0;
    virtual bool bSetPDCLeftBottom(int x, int y)=0;
    virtual bool bSetPDCSize(int w, int h)=0;
    virtual bool bSetGraphicPDCState(int *pdcStatus)=0;
    virtual bool bSetGraphicPDCPause() = 0;
    virtual bool bSetGraphicPDCResume() = 0;    
    virtual bool bSetPDCDisable()=0;
};

#endif
