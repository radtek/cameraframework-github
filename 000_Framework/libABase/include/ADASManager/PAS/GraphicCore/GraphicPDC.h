#if !defined(_GraphicPDC_H)
#define _GraphicPDC_H

#include "IGraphicPDC.h"
#include "HeadDefine.h"



class GraphicPDC : public IGraphicPDC
{
public:
    GraphicPDC();
    ~GraphicPDC();

    virtual bool InitPDC(int screenWidth, int screenHeight);
    virtual bool bSetPDCLeftBottom(int x, int y);
    virtual bool bSetPDCSize(int w, int h);
    virtual bool bSetGraphicPDCState(int *pdcStatus);
    virtual bool bSetGraphicPDCPause();
    virtual bool bSetGraphicPDCResume();    
    virtual bool bSetPDCDisable();

   // bool bSetPDCSlowState(bool bEnable,bool bForward );
    void vSetPDCBackgroundState(bool bState);
    //bool bSetPDCBackgroundForward(bool bForward);


    bool ReadConfigFile(const char* cfgPath);
    void SetMode();
    void SetSumNum();
    void InitGroupMap();
    int LoadTextureData(int index);
    void MallocGroupPlaneData();
    void MallocGroupBorderData(int index);

    void CalPlaneData();
    void CalPlaneBorder(int index);

    int LoadTextures();
    bool CompoundTex();
    void MallocBackgroundPlaneData();
    void LoadBackgroundTexFiles();
    void CalBackgroundPlaneData();
  


protected:
    planesData* m_Planes;//save info from side line and distance mark line according groups
    int m_iScreenWidth;
    int m_iScreenHeight;
    bool m_bPause;

    groupMap* m_iGroupMaps;

    planesData* m_pdc_background;
    bool bBackgroundEnable;
    //configuration information
    int m_iGroupNum;    //show group
    int sumNum;
    int dayCamPosx,dayCamPosy,dayCamTexWidth,dayCamTexHeight;
    int dayNoCamPosx,dayNoCamPosy,dayNoCamTexWidth,dayNoCamTexHeight;
    int nightCamPosx,nightCamPosy,nightCamTexWidth,nightCamTexHeight;
    int nightNoCamPosx,nightNoCamPosy,nightNoCamTexWidth,nightNoCamTexHeight;
    int posX,posY,texWidth,texHeight,planeWidth,planeHeight;// position and size
    int backgroundWidth,backgroundHeight;
    int texBackgroundWidth,texBackgroundHeight,posXBackground,posYBackground;
    int* familyNum;
    int *defaultShow;
    string modeStr,texFilePath;

    //files path
    string texfilesPathDayCam,texfilesPathDayNoCam,texfilesPathNightCam,texfilesPathNightNoCam;
    string familyNumStr,defaultShowStr;
    string texNames[200],backgroundName;
    char *tex;
	char *infoBuffer;
	char *carBuffer1;
	char *carBuffer2;
    unsigned int iPingPong;
	unsigned char carStatus;
	unsigned char lastCarStatus;
};


#endif
