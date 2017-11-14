
#include "ADASManager/PAS/GraphicCore/GraphicVPAFord.h"
#include "ADASManager/PAS/GraphicCore/GraphicPDC.h"
#include "ADASManager/PAS/GraphicCore/bmpconfig.h"
#include "ADASManager/PAS/GraphicCore/lodepng.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

#define PNG01_PATH "/usr/bin/Night_Camera/pdc_focus_warning.png"
//#define PNG02_PATH "apa_reverse_arrow_fill_16.png"
#define PNG02_PATH "/usr/bin/Night_Camera/pdc_front_right_inside_0.png"
#define PNG03_PATH "/usr/bin/Night_Camera/pdc_malfunction.png"
//#define PNG04_PATH "pdc_trailer.png"
#define PNG04_PATH "/usr/bin/Night_Camera/pdc_front_right_inside_1.png"

#define PNG05_PATH "/usr/bin/Night_Camera/apa_reverse_arrow_fill_16.png"
#define PNG06_PATH "/usr/bin/Night_Camera/apa_stop.png"
#define PNG07_PATH "/usr/bin/Night_Camera/apa_cancel.png"
//#define PNG08_PATH "apa_caution.png"
#define PNG08_PATH "/usr/bin/Night_Camera/apa_forward_arrow_fill_16.png"

static unsigned char* LodePNGImage(std::string filename, unsigned int &width, unsigned int &height)
{
    unsigned w, h;
    unsigned char *buffer = NULL;
    unsigned char *text = NULL;
    std::vector<unsigned char> image; //the raw pixels
    unsigned error = lodepng::decode(image, w, h, filename, LCT_RGBA, 8);
    printf("   [%s, %d] error = %d\n", __FUNCTION__, __LINE__, error);
    if (error != 0)
    {
        printf("   [%s, %d] open file fail\n", __FUNCTION__, __LINE__);
        return NULL;
    }

    buffer = new unsigned char[w*h*4];
    memset(buffer, 0, w*h*4);
    width = w;
    height = h;
    for (int i=0;i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            buffer[4 * i*width + 4 * j]     = (unsigned char)image[4 * i*width + 4 * j];
            buffer[4 * i*width + 4 * j + 1] = (unsigned char)image[4 * i*width + 4 * j + 1];
            buffer[4 * i*width + 4 * j + 2] = (unsigned char)image[4 * i*width + 4 * j + 2];
            buffer[4 * i*width + 4 * j + 3] = (unsigned char)image[4 * i*width + 4 * j + 3];
        }
    }

    //return buffer;

    /*std::vector<char> tex;
    int k = 0;
    while(k < width*height*4)
    {
        if(buffer[k+3]!=0)
        {
            tex.pushback(buffer[k]);
            tex.pushback(buffer[k+1]);
            tex.pushback(buffer[k+2]);
            tex.pushback(buffer[k+3]);
        }
        k = k+4;
    }*/
    int k = 0;
    /*unsigned int len = 0;
    while(k < width*height*4)
    {
        //if(buffer[k+3] != 0)
        {
            len += 4;
        }
        k += 4;
    }
    printf("   [%s, %d] len = %d\n", __FUNCTION__, __LINE__, len);*/

    text = new unsigned char[w*h*4];
    memset(text, 0, w*h*4);
    k = 0;
    int index = 0;
    while(k < width*height*4)
    {
        if(buffer[k+3] != 0)
        {
            text[k]   = buffer[k];
            text[k+1] = buffer[k+1];
            text[k+2] = buffer[k+2];
            text[k+3] = buffer[k+3];
            //index += 4;
        }
        else
        {
            //text[k]   = 0xFF;
            //text[k+1] = 0xFF;
            //text[k+2] = 0xFF;
            //text[k+3] = 0xFF;
            //text[k]   = buffer[k];
            //text[k+1] = buffer[k+1];
            //text[k+2] = buffer[k+2];
            //text[k+3] = buffer[k+3];
        }
        k += 4;
    }
    delete buffer;
    buffer = NULL;

    //printf("   [%s, %d] %x, %x, %x, %x\n", __FUNCTION__, __LINE__, text[0], text[1], text[2], text[3]);
    return text;
}


GraphicVPAFord::GraphicVPAFord()
    : CRunableBase("GraphicVPAFord", false)
{
    printf(" [%s, %d] GraphicVPAFord::GraphicVPAFord() \n", __FUNCTION__, __LINE__);
	m_bPause = false;

    graphic = new CAdasGraphic();
}

GraphicVPAFord::~GraphicVPAFord()
{
}

bool GraphicVPAFord::vInit(int screenWidth, int screenHeight)
{
    printf(" [%s, %d]\n", __FUNCTION__, __LINE__);

    //setscSize(screenWidth,screenHeight);

    // if(!InitVDT(screenWidth,screenHeight)) {
    //     PDCL_LOG_INFO(" InitVDT init is failed!\n");
    // }

    // if(InitPDC(screenWidth,screenHeight)) {
    //     PDCL_LOG_INFO(" GraphicPDC init is failed!\n");
    //     return true;
    // }

	return false;
}

bool GraphicVPAFord::bSetVPALeftBottom(int x, int y)
{
//     temp_x = m_CarPOT.LeftBottom.x + x - posX;
//     temp_y = m_CarPOT.LeftBottom.y + y - posY;
//     bSetPDCLeftBottom(x,y);
//     bSetVDTLeftBottom(temp_x,temp_y);

    return true;
}

bool GraphicVPAFord::bSetVPASize(int w, int h)
{
    // rescale = (float)w/planeWidth;
    // bSetPDCSize(w,h);
    // bSetVDTSize(posX,posY,rescale);
    return true;
}

VOID GraphicVPAFord::init()
{
    printf(" [%s, %d] GraphicVPAFord::init(), carBuffer2 = %p, texWidth = %d, texHeight = %d  \n", __FUNCTION__, __LINE__, carBuffer2,  texWidth, texHeight);

	// if(InitView(800, 480, carBuffer2, texWidth, texHeight)) {
	// 	PDCL_LOG_INFO("GraphicPDC::init failed!\n");
	// 	quit();
	// }else{
	// 	PDCL_LOG_INFO("GraphicPDC::init success! swap a first blank frame\n");
	// }


    unsigned int width, height;

    tsurfaceInfo surfaceInfo;
    tsurfaceList surfaceArry;
    //unsigned int width, height;
    //trenderData renderData1;
    tbufInfo bufferInfo1;
    tbufInfo bufferInfo2;
    tbufInfo bufferInfo3;
    renderData1.surfaceID = 52;


    surfaceInfo.surfaceName = "Graphic_1";
    surfaceInfo.surfaceId = 52;
    surfaceInfo.moduleType = MODULE_PAS;
    surfaceInfo.bActiveEGL = TRUE;
    surfaceInfo.viewPos.width = 640;//width;
    surfaceInfo.viewPos.height = 720;//height;
    surfaceInfo.viewPos.viewPos.x = 0;
    surfaceInfo.viewPos.viewPos.y = 0;
    surfaceArry.push_back(surfaceInfo);
    graphic->createSurface(surfaceArry);

    unsigned char *buffer1 = LodePNGImage(PNG01_PATH, width, height);
    bufferInfo1.buffer = buffer1;
    bufferInfo1.width = width;
    bufferInfo1.height = height;
    bufferInfo1.bRender = TRUE;
    renderData1.bufferMap.insert(make_pair(ADAS_PAS_CAR_STATUS, bufferInfo1));
    unsigned char *buffer2 = LodePNGImage(PNG02_PATH, width, height);
    bufferInfo2.buffer = buffer2;
    bufferInfo2.width = width;
    bufferInfo2.height = height;
    bufferInfo2.bRender = TRUE;
    renderData1.bufferMap.insert(make_pair(ADAS_PAS_RADAR_STATUS, bufferInfo2));
    unsigned char *buffer3 = LodePNGImage(PNG03_PATH, width, height);
    bufferInfo3.buffer = buffer3;
    bufferInfo3.width = width;
    bufferInfo3.height = height;
    bufferInfo3.bRender = TRUE;
    renderData1.bufferMap.insert(make_pair(ADAS_PAS_WARNING_STATUS, bufferInfo3));
}

void GraphicVPAFord::update()
{
    printf(" [%s, %d] GraphicVPAFord::update() \n", __FUNCTION__, __LINE__);

    // //printf("   [%s, %d] OPENGL ES Render always step1   !!!!!!!!!!!!!!!!!!!!\n", __FUNCTION__, __LINE__);
    // //make sure init is done...
    // //glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
    // glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    // glDisable(GL_DEPTH_TEST);
    // //eglSwapBuffers(window_shell->display->egl.dpy, window_shell->egl_surface);
    // //usleep(5000000);//30ms sleep  //100ms
    // Render();
    // eglSwapBuffers(window_shell->display->egl.dpy, window_shell->egl_surface);
    // //PDCL_LOG_INFO("GraphicPDC::swap a  frame\n");
    // usleep(30000);//30ms sleep  //100ms

    static unsigned int count = 1;
    unsigned char *buffer4;

    unsigned int width, height;

    if(1 == count%2)
    {
        //printf(" [%s, %d]  count = %d\n", __FUNCTION__, __LINE__, count);
        buffer4 = LodePNGImage(PNG04_PATH, width, height);
        auto it1 = renderData1.bufferMap.find(ADAS_PAS_RADAR_STATUS);
        it1->second.buffer = buffer4;
        it1->second.width = width;
        it1->second.height = height;
    }
    else
    {
        //printf(" [%s, %d]  count = %d\n", __FUNCTION__, __LINE__, count);
        buffer4 = LodePNGImage(PNG02_PATH, width, height);
        auto it3 = renderData1.bufferMap.find(ADAS_PAS_RADAR_STATUS);
        it3->second.buffer = buffer4;
        it3->second.width = width;
        it3->second.height = height;

    }

    count++;
    graphic->Render(renderData1);
    sleep(1);
    delete buffer4;
}

void GraphicVPAFord::CBPause()
{
    printf(" [%s, %d] GraphicVPAFord::CBPause() \n", __FUNCTION__, __LINE__);

    // //glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
    // glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    // glDisable(GL_DEPTH_TEST);
    // Render();
    // eglSwapBuffers(window_shell->display->egl.dpy,window_shell->egl_surface);
    // PDCL_LOG_INFO(" run GraphicPDC::CBPause!!\n");
} //update last state before pause

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

#define NUM_OF_LINE_TO_DRAW 2
void GraphicVPAFord::Render()
{
// 	printf("   [%s, %d] GraphicVPAFord::Render()!! begine,  bBackgroundEnable=%d\n", __FUNCTION__, __LINE__, bBackgroundEnable);
//     glEnable(GL_BLEND);

//     glEnableVertexAttribArray(VERTEX_ARRAY);
//     glEnableVertexAttribArray(TEXCOORD_ARRAY);
//     //backgrounddown tag
//     if (bBackgroundEnable)
//     {
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texBackgroundWidth, texBackgroundHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_pdc_background->tex);
//         glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
//         glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//         vEleToArray(m_pdc_background->pBorderData,m_pdc_background->pArrayData);
//         glVertexAttribPointer(VERTEX_ARRAY, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)m_pdc_background->pArrayData);
//         glVertexAttribPointer(TEXCOORD_ARRAY,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)(&m_pdc_background->pArrayData[2]));
//         //glDrawElements(GL_TRIANGLES,m_pdc_background->pBorderIndexNum,GL_UNSIGNED_SHORT,m_pdc_background->pBorderIndex);
//         glDrawArrays(GL_TRIANGLES,0,6);
//     }

// #if 1
//     //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//     glUseProgram(m_RenderObj.uiId);
//     glActiveTexture(GL_TEXTURE0);
//     glBindTexture(GL_TEXTURE_2D, m_uiTexture);
// 	glUniform1i(m_RenderObj.uiTxtLoc,0);
//     glUniform2f(m_RenderObj.uiImgSize,m_iWidth-1,m_iHeight-1);

//     IMAGEINFO imageinfo;
//     imageinfo.height = texHeight;
//     imageinfo.width = texWidth;
//     imageinfo.image_size = texWidth*texHeight*4;
//     saveAsBmp("/usr/bin/snowuse.bmp", (void*)tex, imageinfo);

//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
//     //
//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
// #endif

// 	static unsigned int index = 0;
//  	//Car PNG
// 	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
// 	glActiveTexture(GL_TEXTURE1);
// 	glBindTexture(GL_TEXTURE_2D, m_uiCarTexture);
// 	glUniform1i(m_RenderObj.uiCarLoc, 1);
// //	glUniform2f(m_RenderObj.uiImgSize, m_iWidth-1, m_iHeight-1);
// 	if(index%2 == 0)
// 	{
// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, carBuffer2);
// 	}
// 	else
// 	{
// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, carBuffer1);
// 	}
// 	index++;
// 	//printf(" [%s, %d] CarStatus = %d, %d\n", __FUNCTION__, __LINE__, carStatus, lastCarStatus);
// 	if(carStatus != lastCarStatus)
// 	{
// 		lastCarStatus = carStatus;
// 		if(0 == carStatus)
// 		{
// 			if(NULL != carBuffer1)
// 			{
// 				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, carBuffer1);
// 			}
// 		}
// 		else
// 		{
// 			if(NULL != carBuffer2)
// 			{
// 				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, carBuffer2);
// 			}
// 		}
// 		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
// 		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
// 	}

// 	glActiveTexture(GL_TEXTURE2);
// 	glBindTexture(GL_TEXTURE_2D, m_uiWarningTexture);
// 	glUniform1i(m_RenderObj.uiWarningLoc, 2);
// 	if(NULL != infoBuffer)
// 	{
// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, infoBuffer);
// 	}
// 	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
// 	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    //glVertexAttribPointer(VERTEX_ARRAY, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)lineGroup.pBorderData);
//    //glVertexAttribPointer(TEXCOORD_ARRAY,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)(&lineGroup.pBorderData[2]));
//    //glDrawElements(GL_TRIANGLES,lineGroup.pBorderIndexNum,GL_UNSIGNED_SHORT,lineGroup.pBorderIndex);
//     planesData lineGroup = m_Planes[0];
//     vEleToArray(lineGroup.pBorderData,lineGroup.pArrayData);

//     glVertexAttribPointer(VERTEX_ARRAY, 2, GL_FLOAT, GL_FALSE,4*sizeof(float), (void*)(&lineGroup.pArrayData[0]));
//     glVertexAttribPointer(TEXCOORD_ARRAY,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)(&lineGroup.pArrayData[2]));

//     glDrawArrays(GL_TRIANGLES, 0, 6);

// 	//b_vdtState = false;
//     if(b_vdtState)
//     {
//         for (int i=0;i<NUM_OF_LINE_TO_DRAW;i++)
//         {
//             RenderGroupLines(i);
//         }

//     }
// 	glDisableVertexAttribArray(VERTEX_ARRAY);
// 	glDisableVertexAttribArray(TEXCOORD_ARRAY);
//     glDisable(GL_BLEND);

//     printf("   [%s, %d] GraphicVPAFord::Render()!! end \n", __FUNCTION__, __LINE__);
}

//guilde line
void GraphicVPAFord::RenderGroupLines(int index)
{
    // paslinesData curLines = m_Lines[index];
    // for(int jx = 0 ;jx<(LINE_PTN_NUM/2)-1;jx++ )
    // {
    //     vEleToArray(&(curLines.pLineData[jx*8]),&(curLines.pArrayData[jx*24]));
    // }

    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE,m_linetex);
    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    // glVertexAttribPointer(VERTEX_ARRAY, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)curLines.pArrayData);
    // glVertexAttribPointer(TEXCOORD_ARRAY,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)(&curLines.pArrayData[2]));
    // //glDrawElements(GL_TRIANGLES,curLines.pLineIndexNum,GL_UNSIGNED_SHORT,curLines.pLineIndex);
    // glDrawArrays(GL_TRIANGLES,0,curLines.pLineIndexNum);
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

void GraphicVPAFord::vSetDayMode()
{
    //SetMode();//pdc todo
    //vSetStyle(GraphicVDT::eDayStyle);
}

void GraphicVPAFord::vSetNightMode()
{
    //SetMode();//pdc todo
    //vSetStyle(GraphicVDT::eNightStyle);
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman