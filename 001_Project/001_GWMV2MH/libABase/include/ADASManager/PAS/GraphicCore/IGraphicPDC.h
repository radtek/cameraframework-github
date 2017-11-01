
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_IGRAPHICPDC_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_IGRAPHICPDC_H__

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class IGraphicPDC
{
public:
    virtual bool InitPDC(int screenWidth, int screenHeight)= 0;
    virtual bool bSetPDCLeftBottom(int x, int y)=0;
    virtual bool bSetPDCSize(int w, int h)=0;
    virtual bool bSetGraphicPDCState(int *pdcStatus)=0;
    virtual bool bSetGraphicPDCPause() = 0;
    virtual bool bSetGraphicPDCResume() = 0;
    virtual bool bSetPDCDisable()=0;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_IGRAPHICPDC_H__