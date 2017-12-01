
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_GRAPHICVPAFORD_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_GRAPHICVPAFORD_H__

#include "CRunableBase.h"
#include "AGraphic.h"

#include "ADASManager/PAS/PasManager.h"


#include <thread>
#include <unistd.h>

using namespace std;

using Harman::Adas::AFramework::AFoundation::CRunableBase;
using Harman::Adas::AFramework::AGraphic::CAdasGraphic;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class GraphicVPAFord : public CRunableBase
{

public:
    GraphicVPAFord();
    ~GraphicVPAFord();

    virtual bool vInit(int screenWidth, int screenHeight);

    void setscSize(int w,int h);
    int getScSizeWidth();
    int getScSizeHeight();

    void update();
	virtual VOID init() override;

private:
    int m_iWidth;
    int m_iHeight;

    CAdasGraphic* graphic = nullptr;
    trenderData renderData1;

    tsurfaceList surfaceArry;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_GRAPHICVPAFORD_H__