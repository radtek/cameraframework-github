
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_GRAPHICVPAFORD_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_GRAPHICVPAFORD_H__

#include "CRunableBase.h"
#include "ADASManager/PAS/GraphicCore/IGraphicPDC.h"
#include "ADASManager/PAS/GraphicCore/GraphicPDC.h"
#include "AGraphic.h"

#include <thread>
#include <unistd.h>

using namespace std;

using Harman::Adas::AFramework::AFoundation::CRunableBase;
using Harman::Adas::AFramework::AGraphic::CAdasGraphic;

#define PNG_BYTES_TO_CHECK 4
#define VERTEX_ARRAY 0
#define TEXCOORD_ARRAY 1

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class GraphicVPAFord : public CRunableBase , public GraphicPDC
{

public:
    GraphicVPAFord();
    ~GraphicVPAFord();
    virtual bool vInit(int screenWidth, int screenHeight);
    void setscSize(int w,int h);
    int getScSizeWidth();
    int getScSizeHeight();



    bool bSetVPALeftBottom(int x, int y);
    bool bSetVPASize(int w, int h);

    // bool bSetGraphicVPAPause();
    // bool bSetGraphicVPAResume();
    void update();
	virtual VOID init() override;

    void Render();
    void RenderGroupLines(int index);
    void CBPause();//update last state before pause
    void vEleToArray(float *eleData,float *arrData);
    void vSetDayMode();
    void vSetNightMode();
private:
    //share vary value
    int temp_x;
    int temp_y;
    float rescale ;

    int m_iWidth;
    int m_iHeight;

    CAdasGraphic* graphic = nullptr;
    trenderData renderData1;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_GRAPHICVPAFORD_H__