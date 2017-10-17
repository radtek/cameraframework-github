#if !defined(_IGraphicVDT_H)
#define _IGraphicVDT_H

#include <stdio.h>
#ifdef __cplusplus
class IGraphicVDT 
{

public:
    virtual bool InitVDT(int screenWidth, int screenHeight)=0;
    virtual bool bSetVDTState(int vdtDir,int vdtStatus,int shortRadius,int longRadius)=0;
    virtual bool bSetVDTLeftBottom(int x, int y)=0;
    virtual bool bSetVDTSize(int posX,int posY,float rescale)=0;
    virtual bool bSetVDTEnable()=0;
    virtual bool bSetVDTDisable()=0;


};

#endif
#endif
