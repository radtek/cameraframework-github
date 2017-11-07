
#include "ADASManager/PAS/GraphicCore/GraphicPDC.h"
#include "ADASManager/PAS/GraphicCore/lineBorderOp.h"
//#include "ADASManager/PAS/GraphicCore/lodepng.h"
#include "ADASManager/PAS/GraphicCore/bmpconfig.h"
//#include "ADASManager/PAS/GraphicCore/PDCSensor.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

GraphicPDC::GraphicPDC(void)
{
    defaultShow=NULL;
    m_iGroupMaps = NULL;
    m_Planes =NULL;
    m_pdc_background =NULL;
    familyNum =NULL;
    m_iScreenWidth = 0;
    m_iScreenHeight = 0;
	carStatus = 1;
	lastCarStatus = 1;
	//carStatus = 0;//s_iPDCState[PDCSensorHub::e_CARSTATE];
	//lastCarStatus = 0;//s_iPDCState[PDCSensorHub::e_CARSTATE];
	printf(" [%s, %d] CarStatus = %d, %d\n", __FUNCTION__, __LINE__, carStatus, lastCarStatus);
}
GraphicPDC::~GraphicPDC(void)
{
    if(NULL!=defaultShow) delete[] defaultShow;
	if(NULL!=m_iGroupMaps)  delete[] m_iGroupMaps;
    if(NULL!=familyNum) delete[] familyNum;
    if(NULL!=m_Planes)
    {
        for(int index=0;index<sumNum;index++)
        {
            planesData* pPlanes = &m_Planes[index] ;
            if(NULL!=pPlanes)
            {
                 if(NULL!=pPlanes->tex) delete pPlanes->tex;
                 if(NULL!=pPlanes->pBorderData) delete pPlanes->pBorderData;
                 if(NULL!=pPlanes->pArrayData) delete pPlanes->pArrayData;
                 if(NULL!=pPlanes->pBorderIndex) delete pPlanes->pBorderIndex;
            }
        }
        delete[] m_Planes;
    }
    if(NULL!=m_pdc_background)
    {
        if(NULL!=m_pdc_background->tex) delete m_pdc_background->tex;
        if(NULL!=m_pdc_background->pBorderData) delete m_pdc_background->pBorderData;
        if(NULL!=m_pdc_background->pArrayData) delete m_pdc_background->pArrayData;
        if(NULL!=m_pdc_background->pBorderIndex) delete m_pdc_background->pBorderIndex;
        delete m_pdc_background;
    }

    defaultShow=NULL;
    m_iGroupMaps = NULL;
    m_Planes =NULL;
    m_pdc_background =NULL;
	if(NULL != infoBuffer)
	{
		delete infoBuffer;
		infoBuffer = NULL;
	}
	if(NULL != carBuffer1)
	{
		delete carBuffer1;
		carBuffer1 = NULL;
	}
	if(NULL != carBuffer2)
	{
		delete carBuffer2;
		carBuffer2 = NULL;
	}
}
#define GBUFF_NUM 8
static char bigbuffPingPong[GBUFF_NUM][800*480*4*2];// add buffer gap
bool GraphicPDC::InitPDC(int screenWidth, int screenHeight)
{
    m_iScreenWidth = screenWidth;
    m_iScreenHeight = screenHeight;
    if(ReadConfigFile(CFG_PATH))
    {
		SetMode();
		SetSumNum();
		MallocGroupPlaneData();
		CalPlaneData();
		InitGroupMap();
		if(LoadTextures()) return true;
		iPingPong=0;
		tex = bigbuffPingPong[iPingPong];//(char*)malloc(texWidth*texHeight*4*sizeof(char));
		CompoundTex();

        //background down
        bBackgroundEnable = false;
        //bBackgroundForward = false;
		MallocBackgroundPlaneData();
		LoadBackgroundTexFiles();
		posXBackground = (int)((m_iScreenWidth-texBackgroundWidth)/2);
		posYBackground = (int)((m_iScreenHeight-texBackgroundHeight)/2);
		CalBackgroundPlaneData();
		return false;
    }
	else
    {
        cout<<"InitPDC is failed!"<<endl;
        return true;
    }
}

bool GraphicPDC:: ReadConfigFile(const char* cfgfilepath)
{
    cout<<"GraphicPDC::ReadConfigFile() : File path = " << cfgfilepath <<endl;

    fstream cfgFile;
    cfgFile.open(cfgfilepath, std::fstream::in);//OpenFiles
    if( ! cfgFile.is_open())
    {
        cout<<"can not open cfg file!"<<endl;
        return false;
    }

    char tmp[1000];
    int lineNum = 0;
    size_t notePos,assignmentPos;

    while(!cfgFile.eof())//read line
    {
        cfgFile.getline(tmp,200);

        string line(tmp);
        //cout<< lineNum<<endl;
        lineNum++;
        // fine note line and blank line
        notePos = line.find('#');

        if(notePos==string::npos ) {
            assignmentPos = line.find('=');//find '='
            if ( assignmentPos==string::npos)
            {
                //cout<< "black line"<<endl;
                ;
            } else
            {
                //bug on this text parser....
               // assignmentPos+=1;

                //cout<< "assignment line"<<endl;
                string tmpKey = line.substr(0,assignmentPos-1);
                string value;
                if (tmpKey == "mode" )
                {
                    cout<< "mode config "<<endl;
                    value = line.substr(assignmentPos+2);
                    modeStr = value.substr(0,value.size());
					printf(" [%s, %d] modeStr = %s\n", __FUNCTION__, __LINE__, modeStr.c_str());
                }

                else if (tmpKey == "texfilesPathDayCam" )
                {
                    cout<< "texfilesPathDayCam config "<<endl;
                    value = line.substr(assignmentPos+2);
                    texfilesPathDayCam = value.substr(0,value.size());
                    cout<< "texfilesPathDayCam is  ----------- "<<texfilesPathDayCam<<endl;

                }
                else if (tmpKey == "texfilesPathDayNoCam" )
                {
                    cout<< "texfilesPathDayNoCam config "<<endl;
                    value = line.substr(assignmentPos+2);//
                    texfilesPathDayNoCam = value.substr(0,value.size());
                    cout<< "texfilesPathDayNoCam is  ----------- "<<texfilesPathDayNoCam<<endl;

                }
                else if (tmpKey == "texfilesPathNightCam" )
                {
                    cout<< "texfilesPathNightCam config "<<endl;
                    value = line.substr(assignmentPos+2);//
                    texfilesPathNightCam = value.substr(0,value.size());
                    cout<< "texfilesPathNightCam is  ----------- "<<texfilesPathNightCam<<endl;

                }
                else if (tmpKey == "texfilesPathNightNoCam" )
                {
                    cout<< "texfilesPathNightNoCam config "<<endl;
                    value = line.substr(assignmentPos+2);//
                    texfilesPathNightNoCam = value.substr(0,value.size());
                    cout<< "texfilesPathNightNoCam is  ----------- "<<texfilesPathNightNoCam<<endl;

                }
                else if(tmpKey == "groupNum")
                {
                    cout<< "groupNum config"<<endl;
                    value = line.substr(assignmentPos+2);//
                    m_iGroupNum = atoi(value.c_str());
                    //m_iGroupNum = atoi(value.c_str()) - 1;
                    cout<< "m_iGroupNum is -----"<<m_iGroupNum<<endl;

                }
                else if(tmpKey == "familyNum")
                {
                    cout<< "familyNum config"<<endl;
                    size_t frontPos = line.find('[');//
                    size_t rearPos = line.find(']');//
                    int  delta = (rearPos - frontPos);
                    value = line.substr(frontPos+1,delta-1);
                    familyNumStr = value;
                    cout<< "familyNumStr is -----"<<familyNumStr<<endl;

                }
                else if(tmpKey == "defaultShow")
                {
                    cout<< "defaultShow config"<<endl;
                    size_t frontPos = line.find('[');//
                    size_t rearPos = line.find(']');//
                    int  delta = (rearPos - frontPos);
                    value = line.substr(frontPos+1,delta-1);
                    defaultShowStr = value;
                    cout<< "defaultShowStr is -----"<<defaultShowStr<<endl;

                }
                else if(tmpKey == "sectorTexString")
                {
                    cout<< "sectorTexString config"<<endl;

                    size_t frontPos,endPos;

                    char texStr[1000];
                    int i = 0;
                    while (!cfgFile.eof())
                    {
                        cfgFile.getline(texStr,1000);//1000 char
                        string texName(texStr);
                        endPos = texName.find('}');//find '}' end symbol
                        if (endPos==string::npos)
                        {
                            frontPos = texName.find(',');//find '='
                            if (frontPos==string::npos)
                            {
                                //cout<<"Cannot find texture name!";
                                ;
                            }
                            else
                            {
                                value = texName.substr(0,frontPos);
                                size_t n = value.find_last_not_of( " \r\n\t" );
                                if( n != string::npos )
                                {
                                    value.erase( n + 1 , value.size() - n );
                                }

                                n = value.find_first_not_of( " \r\n\t" );
                                if( n != string::npos )
                                {
                                    value.erase( 0 , n );
                                }

                                texNames[i] = value;
                                cout<<value<<endl;
                                i++;
                            }

                        }
                        else
                        {
                            break;
                        }
                    }

                }
                else if(tmpKey == "dayCamPosx")
                {
                    cout<< "dayCamPosx config"<<endl;
                    value = line.substr(assignmentPos+2);
                    dayCamPosx = atoi(value.c_str());
                    cout<< "dayCamPosx is -----"<<dayCamPosx<<endl;

                }
                else if(tmpKey == "dayCamPosy")
                {
                    cout<< "dayCamPosy config"<<endl;
                    value = line.substr(assignmentPos+2);
                    dayCamPosy = atoi(value.c_str());
                    cout<< "dayCamPosy is -----"<<dayCamPosy<<endl;
                }
                else if(tmpKey == "dayCamTexWidth")
                {
                    cout<< "dayCamTexWidth config"<<endl;
                    value = line.substr(assignmentPos+2);
                    dayCamTexWidth = atoi(value.c_str());
                    cout<< "dayCamTexWidth is -----"<<dayCamTexWidth<<endl;
                }
                else if(tmpKey == "dayCamTexHeight")
                {
                    cout<< "dayCamTexHeight config"<<endl;
                    value = line.substr(assignmentPos+2);
                    dayCamTexHeight = atoi(value.c_str());
                    cout<< "dayCamTexHeight is -----"<<dayCamTexHeight<<endl;
                }
                else if(tmpKey == "dayNoCamPosx")
                {
                    cout<< "dayNoCamPosx config"<<endl;
                    value = line.substr(assignmentPos+2);
                    dayNoCamPosx = atoi(value.c_str());
                    cout<< "dayNoCamPosx is -----"<<dayNoCamPosx<<endl;
                }
                else if(tmpKey == "dayNoCamPosy")
                {
                    cout<< "dayNoCamPosy config"<<endl;
                    value = line.substr(assignmentPos+2);
                    dayNoCamPosy = atoi(value.c_str());
                    cout<< "dayNoCamPosy is -----"<<dayNoCamPosy<<endl;
                }
                else if(tmpKey == "dayNoCamTexWidth")
                {
                    cout<< "dayNoCamTexWidth config"<<endl;
                    value = line.substr(assignmentPos+2);
                    dayNoCamTexWidth = atoi(value.c_str());
                    cout<< "dayNoCamTexWidth is -----"<<dayNoCamTexWidth<<endl;
                }
                else if(tmpKey == "dayNoCamTexHeight")
                {
                    cout<< "dayNoCamTexHeight config"<<endl;
                    value = line.substr(assignmentPos+2);
                    dayNoCamTexHeight = atoi(value.c_str());
                    cout<< "dayNoCamTexHeight is -----"<<dayNoCamTexHeight<<endl;
                }
                else if(tmpKey == "nightCamPosx")
                {
                    cout<< "nightCamPosx config"<<endl;
                    value = line.substr(assignmentPos+2);
                    nightCamPosx = atoi(value.c_str());
                    cout<< "nightCamPosx is -----"<<nightCamPosx<<endl;
                }
                else if(tmpKey == "nightCamPosy")
                {
                    cout<< "nightCamPosy config"<<endl;
                    value = line.substr(assignmentPos+2);
                    nightCamPosy = atoi(value.c_str());
                    cout<< "nightCamPosy is -----"<<nightCamPosy<<endl;
                }
                else if(tmpKey == "nightCamTexWidth")
                {
                    cout<< "nightCamTexWidth config"<<endl;
                    value = line.substr(assignmentPos+2);
                    nightCamTexWidth = atoi(value.c_str());
                    cout<< "nightCamTexWidth is -----"<<nightCamTexWidth<<endl;
                }
                else if(tmpKey == "nightCamTexHeight")
                {
                    cout<< "nightCamTexHeight config"<<endl;
                    value = line.substr(assignmentPos+2);
                    nightCamTexHeight = atoi(value.c_str());
                    cout<< "nightCamTexHeight is -----"<<nightCamTexHeight<<endl;
                }
                else if(tmpKey == "nightNoCamPosx")
                {
                    cout<< "nightNoCamPosx config"<<endl;
                    value = line.substr(assignmentPos+2);
                    nightNoCamPosx = atoi(value.c_str());
                    cout<< "nightNoCamPosx is -----"<<nightNoCamPosx<<endl;
                }
                else if(tmpKey == "nightNoCamPosy")
                {
                    cout<< "nightNoCamPosy config"<<endl;
                    value = line.substr(assignmentPos+2);
                    nightNoCamPosy = atoi(value.c_str());
                    cout<< "nightNoCamPosy is -----"<<nightNoCamPosy<<endl;
                }
                else if(tmpKey == "nightNoCamTexWidth")
                {
                    cout<< "nightNoCamTexWidth config"<<endl;
                    value = line.substr(assignmentPos+2);
                    nightNoCamTexWidth = atoi(value.c_str());
                    cout<< "nightNoCamTexWidth is -----"<<nightNoCamTexWidth<<endl;
                }
                else if(tmpKey == "nightNoCamTexHeight")
                {
                    cout<< "nightNoCamTexHeight config"<<endl;
                    value = line.substr(assignmentPos+2);
                    nightNoCamTexHeight = atoi(value.c_str());
                    cout<< "nightNoCamTexHeight is -----"<<nightNoCamTexHeight<<endl;
                }
                else if(tmpKey == "backgroundname")
                {
                    cout<< "backgroundName config"<<endl;
                    value = line.substr(assignmentPos+2);//
                    backgroundName = value.substr(0,value.size());
                    cout<< "backgroundName  is -----"<<backgroundName<<endl;
                }

            }

        } else
        {
            //cout<< "note line"<<endl;
        }
    }

    if(cfgFile.is_open())
    {
        cfgFile.close();
    }

    cout<<endl<<"GraphicPDC::ReadConfigFile() ok ! " <<endl<<endl;

    return true;

}

void GraphicPDC::SetMode()
{
    cout<<"GraphicPDC::SetMode() Set Mode :" <<endl;

    if (modeStr=="DAY_CAMERA")
    {
        cout<<"Set DAY_CAMERA Mode"<<endl;
        texFilePath = texfilesPathDayCam;
        posX = dayCamPosx;
        posY = dayCamPosy;
        planeHeight = dayCamTexHeight;
        planeWidth = dayCamTexWidth;

    }
    else if (modeStr=="DAY_NOCAMERA")
    {
        cout<<"Set DAY_NOCAMERA Mode"<<endl;
        texFilePath = texfilesPathDayNoCam;
        posX = dayNoCamPosx;
        posY = dayNoCamPosy;
        planeHeight = dayNoCamTexHeight;
        planeWidth = dayNoCamTexWidth;
    }
    else if (modeStr=="NIGHT_CAMERA")
    {
        cout<<"Set NIGHT_CAMERA Mode"<<endl;
        texFilePath = texfilesPathNightCam;
        posX = nightCamPosx;
        posY = nightCamPosy;
        planeHeight = nightCamTexHeight;
        planeWidth = nightCamTexWidth;
    }
    else if (modeStr=="NIGHT_NOCAMERA")
    {
        cout<<"Set NIGHT_NOCAMERA Mode"<<endl;
        texFilePath = texfilesPathNightNoCam;
        posX = nightNoCamPosx;
        posY = nightNoCamPosy;
        planeHeight = nightNoCamTexHeight;
        planeWidth = nightNoCamTexWidth;
    }
    else
    {
        cout<<"faild to read PDC mode, defult: Set DAY_CAMERA Mode"<<endl;
        texFilePath = texfilesPathDayCam;
        posX = dayCamPosx;
        posY = dayCamPosy;
        planeHeight = dayCamTexHeight;
        planeWidth = dayCamTexWidth;
    }


    cout<<"modeStr is ------"<<modeStr<<endl;
    cout<<"posX is ------"<<posX<<endl;
    cout<<"posY is ------"<<posY<<endl;
    cout<<"planeHeight is ------"<<planeHeight<<endl;
    cout<<"planeWidth is ------"<<planeWidth<<endl;
    cout << "texFilePath is ------" << texFilePath << endl;

    cout<<endl<<"GraphicPDC::SetMode() Set Mode OK!" <<endl<<endl;
}


void GraphicPDC::SetSumNum()
{
    //cout<<"Set Sum Number"<<endl;
    stringstream numStr(familyNumStr);
    string tempStr;
    familyNum = new int[m_iGroupNum];
    int i = 0;
    sumNum =0;
    while(getline(numStr,tempStr,','))
    {
        //cout<<tempStr<<endl;
        familyNum[i] = atoi(tempStr.c_str());
        sumNum += familyNum[i];
        i++;
    }

    cout << "GraphicPDC::SetSumNum() familyNumStr = "<<  familyNumStr << "sumNum = " << sumNum << "m_iGroupNum = " << m_iGroupNum << endl;
}


void GraphicPDC::MallocGroupPlaneData()
{
   // cout<<"Malloc Group Plane Data"<<endl;
    m_Planes = new planesData[sumNum];
    for(int i=0;i<sumNum;i++)
        MallocGroupBorderData(i);
}

void GraphicPDC::MallocGroupBorderData(int index)
{
    planesData* curLineData = &m_Planes[index];

    unsigned short tmpPtElemNum;
    unsigned short tmpIndexElemNum;
    unsigned short totalPtElemNum=0;
    unsigned short totalIndexElemNum = 0;

    lineBorderOp borderOp;
    borderOp.CalLine2DBorderPtNum(4,tmpPtElemNum,tmpIndexElemNum);
    totalPtElemNum += tmpPtElemNum;
    totalIndexElemNum += tmpIndexElemNum;

    curLineData->pBorderPtElemNum = totalPtElemNum;				//= 32
    curLineData->pBorderIndexNum = totalIndexElemNum;			//= 18
    curLineData->pBorderData = new float[totalPtElemNum];		//32 len
    curLineData->pArrayData = new float[totalPtElemNum*3/2];	//48 len
    curLineData->pBorderIndex =(unsigned short*)new short[totalIndexElemNum];	//18 len

}



void GraphicPDC::CalPlaneData()
{
    //cout<<"Calculate Plane Data"<<endl;
    for(int i=0;i<sumNum;i++)
        CalPlaneBorder(i);

}

void GraphicPDC::CalPlaneBorder(int index)
{
    lineBorderOp borderOp;
    planesData* group = &m_Planes[index];
    if(NULL==group->tex)
    {
        cout<<"CalPlaneBorder is ----------"<<index<<endl;
        return;
    }
    float* borderData = group->pBorderData;
    unsigned short* borderIndex = group->pBorderIndex;
    borderOp.CalLine2D(index,borderData,borderIndex,posX,posY,planeWidth,planeHeight);
   // cout<<"group->pBorderData[0] is ----------"<<group->pBorderData[0]<<endl;
    //cout<<"group->pBorderData[1] is ----------"<<group->pBorderData[1]<<endl;
   // cout<<"planeWidth is ----------"<<planeWidth<<endl;
   // cout<<"planeHeight is ---------"<<planeHeight<<endl;


}

void GraphicPDC::InitGroupMap()
{
    stringstream numStr(defaultShowStr);
    string tempStr;
     cout<<"m_iGroupNum is ------->"<<m_iGroupNum<<endl;
    defaultShow = new int[m_iGroupNum];
    int k = 0;
    while(getline(numStr,tempStr,','))
    {
        defaultShow[k] = atoi(tempStr.c_str());
        defaultShow[k] -=1;//index start from 0 and -1 means draw nothing
        k++;
    }
    cout<<"Init Group Map (default)"<<endl;
    m_iGroupMaps = new groupMap[m_iGroupNum];

    // typedef struct _groupMap{
    //     int planeNum;//这个区域块一共有几个块，底块也算一个
    //     int beginHead;//这个区域在familyNum数组中的起始下标
    //     int showPlaneNum;// 这个区域需要显示几个色块
    //     int planeSeq[10];// 这个区域要显示色块的下标（一个或多个）
    // } groupMap;

    m_iGroupMaps[0].beginHead = 0;
    m_iGroupMaps[0].planeNum = familyNum[0];
    m_iGroupMaps[0].showPlaneNum = 1;
    m_iGroupMaps[0].planeSeq[0] = defaultShow[0];
    printf("Init Group Map (default) planeNum=%d, beginHead=%d, showPlaneNum=%d, planeSeq=%d\n",m_iGroupMaps[0].planeNum, m_iGroupMaps[0].beginHead,
            m_iGroupMaps[0].showPlaneNum, m_iGroupMaps[0].planeSeq[0]);

    for (int i=1;i<m_iGroupNum;i++)
    {
        m_iGroupMaps[i].beginHead = m_iGroupMaps[i-1].beginHead + familyNum[i-1];
        m_iGroupMaps[i].planeNum = familyNum[i];
        m_iGroupMaps[i].showPlaneNum = 1;
        m_iGroupMaps[i].planeSeq [0] = defaultShow[i];
        printf("Init Group Map (default) planeNum=%d, beginHead=%d, showPlaneNum=%d, planeSeq=%d\n",m_iGroupMaps[i].planeNum, m_iGroupMaps[i].beginHead,
            m_iGroupMaps[i].showPlaneNum, m_iGroupMaps[i].planeSeq[0]);
    }

}


int GraphicPDC::LoadTextureData(int index)
{
    // typedef struct _planesData{
    //     char* tex;  // *.png data
    //     float* pBorderData;//two for vertex and two for TEXCOORD,so stride is 4
    //     float* pArrayData;//two for vertex and two for TEXCOORD,so stride is 4
    //     unsigned short* pBorderIndex;
    //     unsigned short pBorderIndexNum;
    //     unsigned short pBorderPtElemNum;
    // }planesData;

    planesData* curPlaneData = &m_Planes[index];
    string filepath = texFilePath + texNames[index] +".png";

    printf(" [%s, %d] GraphicPDC::LoadTextureData , filepath = %s\n", __FUNCTION__, __LINE__, filepath.c_str());

   // cout<<"filepath name is -----------------"<<filepath<<endl;
    //printf(" [%s, %d] %s\n", __FUNCTION__, __LINE__, filepath.c_str());
    std::vector<unsigned char> image; //the raw pixels
    unsigned width=0, height=0;
    unsigned error;// = lodepng::decode(image, width, height, filepath, LCT_RGBA, 8);
    //printf(" [%s, %d] error = %d\n", __FUNCTION__, __LINE__, error);
    texHeight = (int)height;
    texWidth = (int)width;
    if(error)
    {
        cout<<filepath.c_str()<<endl;
		return 1;
    }

    curPlaneData->tex = new char[texWidth*texHeight*4];
    char* pTexData = curPlaneData->tex;
    for (int i=0;i<texHeight;i++)
    {
        for (int j=0;j<texWidth;j++)
        {
            pTexData[4*i*texWidth+4*j] = (char)image[4*i*texWidth+4*j+2];
            pTexData[4*i*texWidth+4*j+1] = (char)image[4*i*texWidth+4*j+1];
            pTexData[4*i*texWidth+4*j+2] = (char)image[4*i*texWidth+4*j];
            pTexData[4*i*texWidth+4*j+3] = (char)image[4*i*texWidth+4*j+3];
        }
    }



    IMAGEINFO imageinfo;
    imageinfo.height = texHeight;
    imageinfo.width = texWidth;
    imageinfo.image_size = texWidth*texHeight*4;
    string path("/usr/bin/snowpath/");
    path += texNames[index];
    path += ".bmp";
    printf(" [%s, %d] GraphicPDC::LoadTextureData , path = %s\n", __FUNCTION__, __LINE__, path.c_str());
    saveAsBmp(path.c_str(), (void*)pTexData, imageinfo);


	return 0;
}


int GraphicPDC::LoadTextures()
{

    for (int i=0; i<sumNum;i++)
    {
    	int iErr =  LoadTextureData(i);
        if(iErr) return iErr;
    }
    return 0;
    //cout<<"Load Texture Data finished!"<<endl;
}

//todo read default pdc state
bool GraphicPDC::CompoundTex()
{
    printf(" [%s, %d] GraphicPDC::CompoundTex() \n", __FUNCTION__, __LINE__);

    for (int i=0;i<m_iGroupNum;i++)
    {
        groupMap* currentMap = &m_iGroupMaps[i]; //one of 21 group
        if ((currentMap->planeSeq[0]<-1)||(currentMap->planeSeq[0]>=currentMap->planeNum))
        {
            printf( "GraphicPDC Defult Status is Exception index[%d] val[%d]\n",i,currentMap->planeSeq[0]);
            currentMap->planeSeq[0] = currentMap->planeNum-1;
            //return false;
        }
    }

    //flash last valid state first
    int indexTex = 0;
    printf(" texWidth = %d , texHeight = %d \n", texWidth, texHeight);
    while(indexTex<(texWidth*texHeight*4))
    {
        tex[indexTex] = 0;
        indexTex++;
    }
    int k;
    for(int i=0; i<m_iGroupNum-1-4; i++)  //16 ge qu yu
    {
		groupMap* currentMap = &m_iGroupMaps[i];
        if (currentMap->planeSeq[0]==-1)
        {
            printf( "currentMap value is   %d \n",currentMap->planeSeq[0]);
            continue;
        }

        planesData plansGroup = m_Planes[currentMap->beginHead+currentMap->planeSeq[0]];
        //planesData plansGroup = m_Planes[3];
        k=0;
        while(k<texWidth*texHeight*4)
        {
            if(plansGroup.tex[k+3]!=0)
            {
                tex[k] =  plansGroup.tex[k];
                tex[k+1] =  plansGroup.tex[k+1];
                tex[k+2] =  plansGroup.tex[k+2];
                tex[k+3] =  plansGroup.tex[k+3];
            }
            k = k+4;
        }
    }

    IMAGEINFO imageinfo;
    imageinfo.height = texHeight;
    imageinfo.width = texWidth;
    imageinfo.image_size = texWidth*texHeight*4;
    saveAsBmp("/usr/bin/snow.bmp", (void*)tex, imageinfo);


	infoBuffer = new char[texWidth*texHeight*4*8];
	if(NULL != infoBuffer)
	{
		memset(infoBuffer, 0, texWidth*texHeight*4*8);
	}


	planesData plansGroup1 = m_Planes[sumNum-2];
	carBuffer1 = new char[texWidth*texHeight*4];
	if(NULL != carBuffer1)
	{
		memset(carBuffer1, 0, texWidth*texHeight*4);
		k=0;
        while(k<texWidth*texHeight*4)
        {
            if(plansGroup1.tex[k+3]!=0)
            {
                carBuffer1[k] =  plansGroup1.tex[k];
                carBuffer1[k+1] =  plansGroup1.tex[k+1];
                carBuffer1[k+2] =  plansGroup1.tex[k+2];
                carBuffer1[k+3] =  plansGroup1.tex[k+3];
            }
            k = k+4;
        }

        IMAGEINFO imageinfo;
        imageinfo.height = texHeight;
        imageinfo.width = texWidth;
        imageinfo.image_size = texWidth*texHeight*4;
        saveAsBmp("/usr/bin/snow1.bmp", (void*)carBuffer1, imageinfo); // car with alarm
	}

	planesData plansGroup2 = m_Planes[sumNum-1];
	carBuffer2 = new char[texWidth*texHeight*4];
	if(NULL != carBuffer2)
	{
		memset(carBuffer2, 0, texWidth*texHeight*4);
		k=0;
        while(k<texWidth*texHeight*4)
        {
            if(plansGroup2.tex[k+3]!=0)
            {
                carBuffer2[k] =  plansGroup2.tex[k];
                carBuffer2[k+1] =  plansGroup2.tex[k+1];
                carBuffer2[k+2] =  plansGroup2.tex[k+2];
                carBuffer2[k+3] =  plansGroup2.tex[k+3];
            }
            k = k+4;
        }
        IMAGEINFO imageinfo;
        imageinfo.height = texHeight;
        imageinfo.width = texWidth;
        imageinfo.image_size = texWidth*texHeight*4;
        saveAsBmp("/usr/bin/snow2.bmp", (void*)carBuffer2, imageinfo);  // car without alarm
	}


    PDCL_LOG_INFO( " GraphicPDC flash default graphic---------- \n");
    return true;
}


bool GraphicPDC::bSetPDCLeftBottom(int x,int y)
{
    PDCL_LOG_INFO( " GraphicPDC SetLeftBottom %d,%d\n",x,y);
    //cout<<"GraphicPDC SetLeftBottom-------------------->"<<endl;
    posX = x;
    posY = y;
    //bSetPDCBackgroundForward(bBackgroundForward);
    CalPlaneData();
    return true;
}

bool GraphicPDC::bSetPDCSize(int w,int h)
{
    PDCL_LOG_INFO( "GraphicPDC SetSize %d,%d\n",w,h);
    backgroundHeight = (h/planeWidth)*backgroundHeight;
    backgroundWidth = (w/planeWidth)*backgroundWidth;
    planeWidth = w;
    planeHeight = h;
    //bSetPDCBackgroundForward(bBackgroundForward);
    CalPlaneData();
    return true;
}

enum ePDCSensorPNG{
        e_FRONTLEFTCNTR,
        e_FRONTRIGHTCNTR,
        e_FRONTLEFTCRNR,
        e_FRONTRIGHTCRNR,

        e_SIDELEFT1,
        e_SIDERIGHT1,
        e_SIDELEFT2,
        e_SIDERIGHT2,

        e_SIDELEFT3,
        e_SIDERIGHT3,
        e_SIDELEFT4,
        e_SIDERIGHT4,

        e_REARLEFTCRNR,
        e_REARRIGHTCRNR,
        e_REARLEFTCNTR,
        e_REARRIGHTCNTR,

        e_EXTSTATEFRONT,
        e_EXTSTATEREAR,
        e_EXTSTATELEFT,
        e_EXTSTATERIGHT,

        e_CARSTATE,

        e_PDCPNGNUM,
    };

bool GraphicPDC::bSetGraphicPDCState(int *pdcStatus)
{
    PDCL_LOG_INFO("bSetGraphicPDCState run !! [%d-%d-%d-%d][%d-%d-%d-%d][%d-%d-%d-%d][%d-%d-%d-%d][%d-%d-%d-%d][%d]", \
    pdcStatus[0],pdcStatus[1],pdcStatus[2],pdcStatus[3], \
    pdcStatus[4],pdcStatus[5],pdcStatus[6],pdcStatus[7], \
    pdcStatus[8],pdcStatus[9],pdcStatus[10],pdcStatus[11], \
    pdcStatus[12],pdcStatus[13],pdcStatus[14],pdcStatus[15], \
    pdcStatus[16],pdcStatus[17],pdcStatus[18],pdcStatus[19], \
    pdcStatus[20]);
    //printf("bSetGraphicPDCState run !! [%d-%d-%d-%d][%d-%d-%d-%d][%d-%d-%d-%d][%d-%d-%d-%d][%d-%d-%d-%d][%d]\n", \
    pdcStatus[0],pdcStatus[1],pdcStatus[2],pdcStatus[3], \
    pdcStatus[4],pdcStatus[5],pdcStatus[6],pdcStatus[7], \
    pdcStatus[8],pdcStatus[9],pdcStatus[10],pdcStatus[11], \
    pdcStatus[12],pdcStatus[13],pdcStatus[14],pdcStatus[15], \
    pdcStatus[16],pdcStatus[17],pdcStatus[18],pdcStatus[19], \
    pdcStatus[20]);
	carStatus = pdcStatus[/*PDCSensorHub::*/e_CARSTATE];
#if 1
    // status check
    for (int i=0;i<m_iGroupNum;i++)
    {
        groupMap* currentMap = &m_iGroupMaps[i];
		//take -1 and -2 as to keep default/last res index value
        if ((pdcStatus[i]< 0)||(pdcStatus[i]>=currentMap->planeNum))
        {
            PDCL_LOG_INFO( "res[%d] index not valid %d %d, \n",i,pdcStatus[i],currentMap->planeSeq[0]);
            //printf( "res[%d] index not valid %d %d, \n",i,pdcStatus[i],currentMap->planeSeq[0]);
            //return false;
        }
        else
        {
            PDCL_LOG_INFO( "res[%d] index  good %d %d, \n",i,pdcStatus[i],currentMap->planeSeq[0]);
            currentMap->planeSeq[0]=pdcStatus[i];
        }
    }
#endif

#if 0
     printf("currentMap run !! \n%d-%d-%d-%d-\n%d-%d-%d-%d-\n%d-%d-%d-%d-\n%d-%d-%d-%d-\n%d\n", \
            m_iGroupMaps[0].beginHead,m_iGroupMaps[1].beginHead,m_iGroupMaps[2].beginHead,m_iGroupMaps[3].beginHead, \
            m_iGroupMaps[4].beginHead,m_iGroupMaps[5].beginHead,m_iGroupMaps[6].beginHead,m_iGroupMaps[7].beginHead, \
            m_iGroupMaps[8].beginHead,m_iGroupMaps[9].beginHead,m_iGroupMaps[10].beginHead,m_iGroupMaps[11].beginHead, \
            m_iGroupMaps[12].beginHead,m_iGroupMaps[13].beginHead,m_iGroupMaps[14].beginHead,m_iGroupMaps[15].beginHead, \
            m_iGroupMaps[16].beginHead);
 #endif
    //flash last valid state first
    //int indexTex = 0;
    //while(indexTex<(texWidth*texHeight*4))
    //{
    //    tex[indexTex] = 0;
    //    indexTex++;
    //}
    iPingPong +=1;
    iPingPong %=GBUFF_NUM;
    //PDCL_LOG_INFO("bSetGraphicPDCState ---update tex done !! %d \n",iPingPong);
    tex = bigbuffPingPong[iPingPong];
    memset(tex,0,texWidth*texHeight*4);
    int k;

    for (int i=0;i<m_iGroupNum-1-4;i++)
    {
        groupMap* currentMap = &m_iGroupMaps[i];
        //-1 is clear current res png
        //-2 is show  default/last res png
        if (pdcStatus[i]==-1)
        {
            //printf( "pdcStatus[%d] value is -1 , last group tex index is  %d \n",i,currentMap->planeSeq[0]);
            continue;
        }

        planesData plansGroup = m_Planes[currentMap->beginHead+currentMap->planeSeq[0]];
        //planesData plansGroup = m_Planes[3];
        k=0;
        while(k<texWidth*texHeight*4)
        {
            if(plansGroup.tex[k+3]!=0)
            {
                tex[k] =  plansGroup.tex[k];
                tex[k+1] =  plansGroup.tex[k+1];
                tex[k+2] =  plansGroup.tex[k+2];
                tex[k+3] =  plansGroup.tex[k+3];
            }
            k = k+4;
        }
    }

	memset(infoBuffer, 0, texWidth*texHeight*4*8);
	for (int i=m_iGroupNum-1-4; i<m_iGroupNum-1; i++)
    {
        groupMap* currentMap = &m_iGroupMaps[i];
        //-1 is clear current res png
        //-2 is show  default/last res png
        if (pdcStatus[i]==-1)
        {
            //printf( "pdcStatus[%d] value is -1 , last group tex index is  %d \n",i,currentMap->planeSeq[0]);
            continue;
        }

        planesData plansGroup = m_Planes[currentMap->beginHead+currentMap->planeSeq[0]];
        //planesData plansGroup = m_Planes[3];
        k=0;
        while(k<texWidth*texHeight*4)
        {
            if(plansGroup.tex[k+3]!=0)
            {
                infoBuffer[k] =  plansGroup.tex[k];
                infoBuffer[k+1] =  plansGroup.tex[k+1];
                infoBuffer[k+2] =  plansGroup.tex[k+2];
                infoBuffer[k+3] =  plansGroup.tex[k+3];
            }
            k = k+4;
        }
    }

    return true;
}


bool GraphicPDC::bSetPDCDisable()
{
    PDCL_LOG_INFO( "GraphicPDC bSetPDCDisable \n");
    CompoundTex();
    return true;
}


bool GraphicPDC::bSetGraphicPDCPause()
{
    PDCL_LOG_INFO( "bSetGraphicPDC Pause run...........\n");
    m_bPause = true;
    return true;
}

bool GraphicPDC::bSetGraphicPDCResume()
{
    PDCL_LOG_INFO( "bSetGraphicPDC Resume run...........\n");
    m_bPause = false;
    return true;
}

void GraphicPDC::MallocBackgroundPlaneData()
{
    //return ;
    cout<<"malloc Group Plane Data"<<endl;

    m_pdc_background = new planesData;
    unsigned short tmpPtElemNum;
    unsigned short tmpIndexElemNum;

    lineBorderOp borderOp;
    borderOp.CalLine2DBorderPtNum(PLANE_SEG,tmpPtElemNum,tmpIndexElemNum);
    m_pdc_background->pBorderPtElemNum = tmpPtElemNum;			//= 16
    m_pdc_background->pBorderIndexNum = tmpIndexElemNum;		//= 6
    m_pdc_background->pBorderData = new float[tmpPtElemNum]();	//16 len
    m_pdc_background->pArrayData = new float[tmpPtElemNum*3/2]();	//24 len
    m_pdc_background->pBorderIndex = (unsigned short*)new short[tmpIndexElemNum]();		//6 len
}

void GraphicPDC::LoadBackgroundTexFiles()
{
    //return ;
    //cout<<"Load Background Tex Files"<<endl;
    string filepath = texFilePath + backgroundName +".png";
    cout<<"Background file is ----------"<<filepath<<endl;
    std::vector<unsigned char> image; //the raw pixels
    unsigned int width=0, height=0;
    unsigned int error;// = lodepng::decode(image, width, height, filepath, LCT_RGBA, 8);
    if(error)
    {
       cout<<"lodepng::decode error"<<endl;
    }
    texBackgroundWidth = width;
    texBackgroundHeight = height;
    backgroundWidth = texBackgroundWidth;
    backgroundHeight = texBackgroundHeight;
    printf("background size is %d-%d\n",backgroundWidth,backgroundHeight);
    m_pdc_background->tex = new char[texBackgroundWidth*texBackgroundHeight*4]();
    char* pTexData = m_pdc_background->tex;
    for (int i=0;i<texBackgroundHeight;i++)
    {
        for (int j=0;j<texBackgroundWidth;j++)
        {
            pTexData[4*i*width+4*j] = (char)image[4*i*width+4*j+2];
            pTexData[4*i*width+4*j+1] = (char)image[4*i*width+4*j+1];
            pTexData[4*i*width+4*j+2] = (char)image[4*i*width+4*j];
            pTexData[4*i*width+4*j+3] = (char)image[4*i*width+4*j+3];
        }
    }

    IMAGEINFO imageinfo;
    imageinfo.height = backgroundHeight;
    imageinfo.width = backgroundWidth;
    imageinfo.image_size = backgroundWidth*backgroundHeight*4;
    string path("/usr/bin/snowpath/");
    path += backgroundName;
    path += ".bmp";
    printf(" [%s, %d] GraphicPDC::LoadBackgroundTexFiles , path = %s\n", __FUNCTION__, __LINE__, path.c_str());
    saveAsBmp(path.c_str(), (void*)pTexData, imageinfo);

}

void GraphicPDC::CalBackgroundPlaneData()
{
    //return ;
    cout<<"Calculate Background Plane Data"<<endl;
    lineBorderOp borderOp;
    float* borderData = m_pdc_background->pBorderData;
    unsigned short* borderIndex = m_pdc_background->pBorderIndex;
    borderOp.CalLine2D(0,borderData,borderIndex,posXBackground,posYBackground,backgroundWidth,backgroundHeight);
}

// bool GraphicPDC::bSetPDCBackgroundState( bool bEnable, bool bForward)
// {
//     //return true;
//     bBackgroundForward = bForward;
//     bBackgroundEnable = bEnable;
//     if (bForward)
//     {
//         posXBackground = posX+(int)((planeWidth-backgroundWidth)/2);
//         posYBackground = posY+(planeHeight -backgroundHeight);
//     }else
//     {
//         posXBackground = posX+(int)((planeWidth-backgroundWidth)/2);
//         posYBackground = posY;
//     }
//     CalBackgroundPlaneData();
//     return true;
// }

void GraphicPDC::vSetPDCBackgroundState(bool bState)
{
    bBackgroundEnable = bState;
}
#if 0
bool GraphicPDC::bSetPDCBackgroundForward(bool bForward)
{
    bBackgroundForward = bForward;
    if (bForward)
    {
        posXBackground = posX+(int)((planeWidth-backgroundWidth)/2);
        posYBackground = posY+(planeHeight -backgroundHeight);
    }else
    {
        posXBackground = posX+(int)((planeWidth-backgroundWidth)/2);
        posYBackground = posY;
    }
    CalBackgroundPlaneData();
    return true;

}
#endif


} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman