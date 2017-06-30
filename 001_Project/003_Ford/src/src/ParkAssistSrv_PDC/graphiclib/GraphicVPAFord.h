#if !defined(_GraphicVPAFord_H)
#define _GraphicVPAFord_H

#include "../core/CRunableService.h"
#include "IGraphicPDC.h"
#include "GraphicPDC.h"
#include "GraphicVDT.h"
#include "GlShell.h"
#include <thread>
#include <unistd.h>
using namespace std;
#define PNG_BYTES_TO_CHECK 4
#define VERTEX_ARRAY 0
#define TEXCOORD_ARRAY 1



class GraphicVPAFord : public CRunableService , public GraphicPDC , public GraphicVDT , public GlShell
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
	void init();

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
};

#endif