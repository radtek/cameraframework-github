//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Ford-LCIS
//  @ File Name : PDCGraphic.h
//  @ Date : 2016-11-22
//  @ Author : Guofeng.lu@harman.com
//
//

#include "PDCGraphic.h"

/*
    virtual bool bSetPDCLeftBottom(int x, int y)=0;
    virtual bool bSetPDCSize(int w, int h)=0;
    virtual bool bSetGraphicPDCState(int *pdcStatus)=0;
    virtual bool bSetGraphicPDCPause() = 0;
    virtual bool bSetGraphicPDCResume() = 0;
    virtual void init(int screenWidth, int screenHeight)= 0;

*/
PDCGraphic::PDCGraphic(IGraphicPDC* pIPDCInterface)
{
    m_iPDCXLeftBottom = 0;
    m_iPDCYLeftBottom = 0;
    m_iPDCWidth = 0;
    m_iPDCHeigth = 0;
    m_IPDCInterface = pIPDCInterface;
}


bool PDCGraphic::bSetPDCLeftBottom(int x, int y)
{
    m_iPDCXLeftBottom = x;
    m_iPDCYLeftBottom = y;
    if(m_IPDCInterface)
    {
        ;
    }
    else
    {
        PDCC_LOG_INFO("PDCGraphic bSetPDCLeftBottom m_IPDCInterface failed! ") ;
    }
    return m_IPDCInterface->bSetPDCLeftBottom(x,y);
}
bool PDCGraphic::bSetPDCSize(int x, int y)
{
    if(m_IPDCInterface)
    {
        ;
    }
    else
    {
        PDCC_LOG_INFO("PDCGraphic bSetPDCSize m_IPDCInterface failed! ") ;
    }
    return m_IPDCInterface->bSetPDCSize(x,y);
}

bool PDCGraphic::bSetGraphicPDCState(int *pdcStatus)
{
    if(m_IPDCInterface)
    {
        ;
    }
    else
    {
        PDCC_LOG_INFO("PDCGraphic bSetGraphicPDCState m_IPDCInterface failed! ") ;
    }
    return m_IPDCInterface->bSetGraphicPDCState(pdcStatus);
}
bool PDCGraphic::bSetGraphicPDCPause()
{
    if(m_IPDCInterface)
    {
        ;
    }
    else
    {
        PDCC_LOG_INFO("PDCGraphic bSetGraphicPDCPause m_IPDCInterface failed! ") ;
    }
    return m_IPDCInterface->bSetGraphicPDCPause();
}
bool PDCGraphic::bSetGraphicPDCResume()
{
    if(m_IPDCInterface)
    {
        ;
    }
    else
    {
        PDCC_LOG_INFO("PDCGraphic bSetGraphicPDCResume m_IPDCInterface failed! ") ;
    }
    return m_IPDCInterface->bSetGraphicPDCResume();
}
void PDCGraphic::vInit(int screenWidth, int screenHeight)
{
    m_iPDCWidth =screenWidth;
    m_iPDCHeigth =screenHeight;
    if(m_IPDCInterface)
    {
        PDCC_LOG_INFO("PDCGraphic call layer init start! ") ;
        m_IPDCInterface->InitPDC(screenWidth,screenHeight);
        PDCC_LOG_INFO("PDCGraphic call layer init end!") ;
    }
    else
    {
        PDCC_LOG_INFO("PDCGraphic init m_IPDCInterface failed! ") ;
    }
}
