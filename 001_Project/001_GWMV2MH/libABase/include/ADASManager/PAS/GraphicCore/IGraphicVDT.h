
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_IGRAPHICVDT_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_IGRAPHICVDT_H__

#include <stdio.h>

#ifdef __cplusplus

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

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

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __cplusplus

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_IGRAPHICVDT_H__