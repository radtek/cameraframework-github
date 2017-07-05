#include "GraphicVPAFord.h"
#include "GraphicPDC.h"

GraphicVPAFord::GraphicVPAFord()
:CRunableBase("GraphicVPAFord",false)
{
	//m_bPause =false;
}


GraphicVPAFord::~GraphicVPAFord()
{
//debug

}

bool GraphicVPAFord::vInit(int screenWidth, int screenHeight)
{
    setscSize(screenWidth,screenHeight);

    if(!InitVDT(screenWidth,screenHeight))
    {   
        PDCL_LOG_INFO(" InitVDT init is failed!\n");
    }
    //if(InitPDC(screenWidth,screenHeight))
    //{
    //    PDCL_LOG_INFO(" GraphicPDC init is failed!\n");
    //    return true;
	return false;
}

bool GraphicVPAFord::bSetVPALeftBottom(int x, int y)
{
    //temp_x = curX1 + x - posX;
    //temp_y = curY1 + y - posY;
    //bSetPDCLeftBottom(x,y);
    //bSetVDTLeftBottom(temp_x,temp_y);

    return true;
}


bool GraphicVPAFord::bSetVPASize(int w, int h)
{
    //rescale = (float)w/planeWidth;
    //bSetPDCSize(w,h);    
    //bSetVDTSize(posX,posY,rescale);
    return true;
}

void GraphicVPAFord::init()
{
	if(InitView(800, 480))
	{
		PDCL_LOG_INFO("GraphicPDC::init failed!\n");
		quit();	
	}
	else
	{
		PDCL_LOG_INFO("GraphicPDC::init success! swap a first blank frame\n");
	}
}

 void GraphicVPAFord::update()
 {
#ifdef WIN_OS 
 	Sleep(1);   
#else
    //make sure init is done...
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    Render();
    eglSwapBuffers(window_shell->display->egl.dpy,window_shell->egl_surface);
    //PDCL_LOG_INFO("GraphicPDC::swap a  frame\n");
	usleep(30000);//30ms sleep  //100ms
#endif
 }

 void GraphicVPAFord::CBPause()
 {

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    Render();
#ifndef WIN_OS 	
    eglSwapBuffers(window_shell->display->egl.dpy,window_shell->egl_surface);
#endif	
    PDCL_LOG_INFO(" run GraphicPDC::CBPause!!\n");
 };//update last state before pause

void GraphicVPAFord::vEleToArray(float *eleData,float *arrData)
{
    arrData[0] = eleData[0];
    arrData[1] = eleData[1];
    arrData[2] = eleData[2];
    arrData[3] = eleData[3];

    arrData[4] = eleData[4];
    arrData[5] = eleData[5];
    arrData[6] = eleData[6];
    arrData[7] = eleData[7];

    arrData[8] = eleData[8];
    arrData[9] = eleData[9];
    arrData[10] = eleData[10];
    arrData[11] = eleData[11];

    arrData[12] = eleData[4];
    arrData[13] = eleData[5];
    arrData[14] = eleData[6];
    arrData[15] = eleData[7];

    arrData[16] = eleData[12];
    arrData[17] = eleData[13];
    arrData[18] = eleData[14];
    arrData[19] = eleData[15];

    arrData[20] = eleData[8];
    arrData[21] = eleData[9];
    arrData[22] = eleData[10];
    arrData[23] = eleData[11];
}

void GraphicVPAFord::Render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
	glUseProgram(m_RenderObj.uiId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,m_uiTexture);
    glUniform2f(m_RenderObj.uiImgSize,m_iWidth-1,m_iHeight-1);

	glEnableVertexAttribArray(VERTEX_ARRAY);
	glEnableVertexAttribArray(TEXCOORD_ARRAY);
    if(b_vdtState)
    {
        for (int i=0;i<eLineMaxIndex;i++)
        {
            RenderGroupLines(i);         
        }

    }
	glDisableVertexAttribArray(VERTEX_ARRAY);
	glDisableVertexAttribArray(TEXCOORD_ARRAY);
    glDisable(GL_BLEND);
   
}

//guilde line
void GraphicVPAFord::RenderGroupLines(int index)
{
    linesData curLines = m_Lines[index];
    for(int jx = 0 ;jx<(LINE_PTN_NUM/2)-1;jx++ )
    {
        vEleToArray(&(curLines.pLineData[jx*8]),&(curLines.pArrayData[jx*24]));     
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE,m_linetex);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glVertexAttribPointer(VERTEX_ARRAY, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)curLines.pArrayData);
    glVertexAttribPointer(TEXCOORD_ARRAY,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)(&curLines.pArrayData[2]));
    //glDrawElements(GL_TRIANGLES,curLines.pLineIndexNum,GL_UNSIGNED_SHORT,curLines.pLineIndex);
    glDrawArrays(GL_TRIANGLES,0,curLines.pLineIndexNum);
}

void GraphicVPAFord::setscSize(int screenWidth,int screenHeight)
 {
    m_iHeight = screenHeight;
    m_iWidth = screenWidth;
 }


 int GraphicVPAFord::getScSizeWidth()
 {
    return m_iWidth;
 }


 int GraphicVPAFord::getScSizeHeight()
 {
    return m_iHeight;
 }






