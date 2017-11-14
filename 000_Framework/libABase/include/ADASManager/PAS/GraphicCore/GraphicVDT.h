
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_GRAPHICVDT_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_GRAPHICVDT_H__

#include "ADASManager/PAS/GraphicCore/IGraphicVDT.h"
#include "ADASManager/PAS/GraphicCore/HeadDefine.h"
#include "ADASManager/PAS/GraphicCore/lineBorderOp.h"

#include <math.h>

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class GraphicVDT : public IGraphicVDT
{
public:
    typedef enum _eDRVState {
        eRearward,
        eForward,
    } eDRVState;

    typedef enum  _eSymbolState{
        eNegative,
        ePositive,
    } eSymbolState;

    typedef enum  _eLineStyle{
        eDayStyle,
        eNightStyle,
    } eLineStyle;

    typedef enum  _eLineIndex{
        eShortCircle =0,
        eLongCircle =1,
		eSCircleCtrVert =2,
		eSCircleCtrHorz =3,
		eLCircleCtrVert =4,
		eLCircleCtrHorz =5,
		eLineMaxIndex ,
    } eLineIndex;

	typedef struct tagCarPointofTangency
	{
		//(0,0) is left bottom of the view
	    point2D LeftBottom;//start point
	    point2D RightBottom;
	    point2D LeftTop;
	    point2D RightTop;

	    float fCarWidth;//base point x transmit
	    float fCarHeight;//base point y transmit
	    //two line length
	    float fVisibleLongLineLength;
	    float fVisibleShortLineLength;

	    //two semicircle radius
	    float shortsemi_circle_radius;
	    float long_semi_circle_radius;
	    //angle
	    float ftheta_short; //fix to a quater
		float ftheta_long;
		float fTheta_startShortR;
		float fTheta_startLongR;
	    point2D semi_circle_certer_short; //fix POT of the short radius
		point2D semi_circle_certer_long; //fix POT of the long radius
	}tCarPOT;

    GraphicVDT();
    ~GraphicVDT();
    virtual bool InitVDT(int screenWidth, int screenHeight);
    virtual bool bSetVDTState(int vdtDir,int vdtStatus,int shortRadius,int longRadius);
    virtual bool bSetVDTLeftBottom(int x, int y);
    virtual bool bSetVDTSize(int posX,int posY,float rescale);
    virtual bool bSetVDTEnable();
    virtual bool bSetVDTDisable();

    void vSetStyle(eLineStyle DayNight);
    bool ReadVDTConfigFile(const char* cfgPath);
    void MallocLineData();
    void CalLineData();
	void vUpdateCarVertex(float fLeftBottomX,float fLeftBottomY,float fCarWidth=0, float fCarHeight=0);
    enum eVDTState {
        e_Forward,
        e_Forward_Lt,
        e_Forward_Rt,
        e_Rearward,
        e_Rearward_Lt,
        e_Rearward_Rt,

        e_VDTStateNum,
    };

protected:
    bool b_vdtState;
	paslinesData* m_Lines;
	//line data
    char* m_linetex;
    float *m_temp[eLineMaxIndex];// line data

    int line_status;//6 status
    float m_fLineWidth;//line width
    float m_fLineSegmentHeight;//line segment offset
	tCarPOT m_CarPOT;
	float m_fScale;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_GRAPHICVDT_H__