
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PDCGRAPHIC_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PDCGRAPHIC_H__

#include "ADASManager/PAS/GraphicCore/IGraphicPDC.h"
#include "TraceMacros.h"
#include "AFoundation.h"

using namespace Harman::Adas::AFramework::AFoundation;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class PDCGraphic {
public:
    PDCGraphic(IGraphicPDC* pIPDCInterface);
    virtual bool bSetPDCLeftBottom(int x, int y);
    virtual bool bSetPDCSize(int w, int h);
    virtual bool bSetGraphicPDCState(int* pdcStatus);
    virtual bool bSetGraphicPDCPause();
    virtual bool bSetGraphicPDCResume();
    virtual void vInit(int screenWidth, int screenHeight);

protected:
    int m_iPDCXLeftBottom ;
    int m_iPDCYLeftBottom ;
    int m_iPDCWidth ;
    int m_iPDCHeigth ;
    IGraphicPDC* m_IPDCInterface = nullptr;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PDCGRAPHIC_H__