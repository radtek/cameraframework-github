
#include <assert.h>
#include "PAS/PDCGraphic.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

PDCGraphic::PDCGraphic(IGraphicPDC* pIPDCInterface)
    : m_iPDCXLeftBottom(0)
    , m_iPDCYLeftBottom(0)
    , m_iPDCWidth(0)
    , m_iPDCHeigth(0)
    , m_IPDCInterface(pIPDCInterface)
{
    ALOGD("PDCGraphic constructor \n");
}

bool PDCGraphic::bSetPDCLeftBottom(int x, int y)
{
    m_iPDCXLeftBottom = x;
    m_iPDCYLeftBottom = y;

    assert(m_IPDCInterface != nullptr);
    return m_IPDCInterface->bSetPDCLeftBottom(x, y);
}

bool PDCGraphic::bSetPDCSize(int x, int y)
{
    assert(m_IPDCInterface != nullptr);
    return m_IPDCInterface->bSetPDCSize(x, y);
}

bool PDCGraphic::bSetGraphicPDCState(int *pdcStatus)
{
    assert(m_IPDCInterface != nullptr);
    return m_IPDCInterface->bSetGraphicPDCState(pdcStatus);
}

bool PDCGraphic::bSetGraphicPDCPause()
{
    assert(m_IPDCInterface != nullptr);
    return m_IPDCInterface->bSetGraphicPDCPause();
}

bool PDCGraphic::bSetGraphicPDCResume()
{
    assert(m_IPDCInterface != nullptr);
    return m_IPDCInterface->bSetGraphicPDCResume();
}

void PDCGraphic::vInit(int screenWidth, int screenHeight)
{
    m_iPDCWidth = screenWidth;
    m_iPDCHeigth = screenHeight;

    assert(m_IPDCInterface != nullptr);

    ALOGD("PDCGraphic call layer init start! \n");
    m_IPDCInterface->InitPDC(screenWidth,screenHeight);
    ALOGD("PDCGraphic call layer init end! \n");
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane