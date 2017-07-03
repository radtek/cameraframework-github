#include "GraphicVDT.h"
#include <math.h>

#define VDT_TEX_RED 255
#define VDT_TEX_GREEN 0
#define VDT_TEX_BLUE 0
#define VDT_TEX_ALPHA 255

//these parameter is related to variants of the car
//can be chagnged by reading from cfgfiles, todo tuning by HMI?
#define CAR_POT_LEFTBOTTOM_X   372
#define CAR_POT_LEFTBOTTOM_Y   206
#define CAR_POT_WIDTH    56
#define CAR_POT_HEIGHT   80
//visible length of tht POT line
#define CAR_POT_LONG_VLENGTH    150
#define CAR_POT_SHORT_VLENGTH   100
#define CAR_POT_LONG_RADIUS    80
#define CAR_POT_SHORT_RADIUS   50

#define LINE_WIDTH 4
#define LINE_SEGMENT_HEIGHT 10

//#define LINE_NUM 2
//#define LINE_PTN_NUM 60

GraphicVDT::GraphicVDT(void)
{
    m_linetex = (char *)malloc(4*4*4*sizeof(char));
    
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            m_linetex[i*4*4+j*4] = VDT_TEX_RED;
            m_linetex[i*4*4+j*4+1] = VDT_TEX_GREEN;
            m_linetex[i*4*4+j*4+2] = VDT_TEX_BLUE;
            m_linetex[i*4*4+j*4+3] = VDT_TEX_ALPHA;
        }
    }
	//default
	
    vUpdateCarVertex(CAR_POT_LEFTBOTTOM_X,CAR_POT_LEFTBOTTOM_Y,CAR_POT_WIDTH,CAR_POT_HEIGHT);

    m_fLineWidth = LINE_WIDTH;
    m_fLineSegmentHeight = LINE_SEGMENT_HEIGHT;
	m_fScale=1;
	
    m_CarPOT.fVisibleLongLineLength = CAR_POT_LONG_VLENGTH;
    m_CarPOT.fVisibleShortLineLength = CAR_POT_SHORT_VLENGTH;
    m_CarPOT.shortsemi_circle_radius = CAR_POT_SHORT_RADIUS;
    m_CarPOT.long_semi_circle_radius = CAR_POT_LONG_RADIUS;
	
	m_CarPOT.ftheta_short =2*R_PI; //R_PI/2;
	m_CarPOT.ftheta_long =2*R_PI; //R_PI/2;
	m_CarPOT.fTheta_startShortR = 0; //fixed to 0

	/*
	m_CarPOT.ftheta_short;
	m_CarPOT.ftheta_long;
	m_CarPOT.fTheta_startShortR;
	m_CarPOT.fTheta_startLongR;
	m_CarPOT.semi_circle_certer_short;
	m_CarPOT.semi_circle_certer_long;
	*/
}


GraphicVDT::~GraphicVDT(void)
{
	for(int i=0;i<eLineMaxIndex;i++)
	{
		delete [] m_temp[i];
		m_temp[i] = NULL;
	}
}

void GraphicVDT::vUpdateCarVertex(float fLeftBottomX,float fLeftBottomY,float fCarWidth, float fCarHeight)
{
    if(fCarWidth) m_CarPOT.fCarWidth = fCarWidth;
    if(fCarHeight) m_CarPOT.fCarHeight = fCarHeight;
	m_CarPOT.LeftBottom.x  = fLeftBottomX; 
	m_CarPOT.LeftBottom.y  = fLeftBottomY;	
	m_CarPOT.LeftTop.x     = fLeftBottomX; 
	m_CarPOT.LeftTop.y     = fLeftBottomY + m_CarPOT.fCarHeight;	
	m_CarPOT.RightBottom.x = fLeftBottomX + m_CarPOT.fCarWidth; 
	m_CarPOT.RightBottom.y = fLeftBottomY;		
	m_CarPOT.RightTop.x    = fLeftBottomX + m_CarPOT.fCarWidth;  
	m_CarPOT.RightTop.y    = fLeftBottomY + m_CarPOT.fCarHeight;
}


bool GraphicVDT::InitVDT(int screenWidth, int screenHeight)
{

    //if (ReadVDTConfigFile(CFG_PATH))
	if(1)
    {
		line_status = 1;
		MallocLineData();
		//CalLineData();
		return true;
    }
    else
    {
        cout<<"ReadVDTConfigFile is failed!"<<endl;
        return false;
    }
}
#if 0
bool GraphicVDT:: ReadVDTConfigFile(const char* cfgfilepath)
{
    //cout<<"Read ReadVDTConfigFile Config File1!"<<endl;

    //cout << "File path in GraphicVDT is >>" << cfgfilepath << "\n";

    fstream cfgFile;
    cfgFile.open(cfgfilepath, std::fstream::in );//OpenFiles
    if( ! cfgFile.is_open())
    {
        cout<<"can not open GraphicVDT cfg file1!"<<endl;
        return false;
    }

    char tmp[1000];
    int lineNum = 0;
    size_t notePos,assignmentPos;

    while(!cfgFile.eof())//read line
    {
        cfgFile.getline(tmp,200);

        //cout << "value read from getline is >>" << tmp << "\n";
        string line(tmp);
        //cout<< lineNum<<endl;
        lineNum++;
        //cout << "string is lineNum is >>" << line << "::" <<lineNum << "\n";
        
        // fine note line and blank line
        notePos = line.find('#');

        if(notePos == string::npos ) 
        {
            //cout << "find size and npos size matches..\n";
            assignmentPos = line.find('=');//find '='

            //cout << "assignmentPos is >>" <<assignmentPos << "\n";
            if ( assignmentPos == string::npos)
            {
                //cout<< "black line"<<endl;
            } 
            else
            {
                //bug on this text parser....
               // assignmentPos+=1;

                //cout<< "assignment line"<<endl;
                string tmpKey = line.substr(0,assignmentPos-1);
                string value ;
               
                if(tmpKey == "curX1")
                {
                    value = line.substr(assignmentPos+2);//
                    m_CarPOT.LeftBottom.x = (float)atoi(value.c_str());
                    //cout<< "m_CarPOT.LeftBottom.x is -------->"<<m_CarPOT.LeftBottom.x<<endl;
                }
                else if(tmpKey == "curY1")
                {
                    value = line.substr(assignmentPos+2);//
                    m_CarPOT.LeftBottom.y = (float)atoi(value.c_str());
                    //cout<< "m_CarPOT.LeftBottom.y is -------->"<<m_CarPOT.LeftBottom.y<<endl;
                }
                else if(tmpKey == "posx_trans")
                {
                    value = line.substr(assignmentPos+2);//
                    m_CarPOT.fCarWidth = (float)atoi(value.c_str());
                    //cout<< "m_CarPOT.fCarWidth is -------->"<<m_CarPOT.fCarWidth<<endl;
                }
                else if(tmpKey == "posy_trans")
                {
                    value = line.substr(assignmentPos+2);//
                    m_CarPOT.fCarHeight = (float)atoi(value.c_str());
                    //cout<< "m_CarPOT.fCarHeight is -------->"<<m_CarPOT.fCarHeight<<endl;
                }
                else if(tmpKey == "line_width")
                {
                    value = line.substr(assignmentPos+2);//
                    m_fLineWidth = (float)atoi(value.c_str());
                    //cout<< "m_fLineWidth is -------->"<<m_fLineWidth<<endl;
                }
                else if(tmpKey == "deltaY")
                {
                    value = line.substr(assignmentPos+2);//
                    m_fLineSegmentHeight = (float)atoi(value.c_str());
                    //cout<< "m_fLineSegmentHeight is -------->"<<m_fLineSegmentHeight<<endl;
                }
                else if(tmpKey == "short_length")
                {
                    value = line.substr(assignmentPos+2);//
                    m_CarPOT.fVisibleShortLineLength = (float)atoi(value.c_str());
                    //cout<< "m_CarPOT.fVisibleShortLineLength is -------->"<<m_CarPOT.fVisibleShortLineLength<<endl;
                }
                else if(tmpKey == "long_length")
                {
                    value = line.substr(assignmentPos+2);//
                    m_CarPOT.fVisibleLongLineLength = (float)atoi(value.c_str());
                    //cout<< "m_CarPOT.fVisibleLongLineLength is -------->"<<m_CarPOT.fVisibleLongLineLength<<endl;
                }

                else if(tmpKey == "shortsemi_circle_radius")
                {
                    value = line.substr(assignmentPos+2);//
                    m_CarPOT.shortsemi_circle_radius = (float)atoi(value.c_str());
                    //cout<< "m_CarPOT.shortsemi_circle_radius is -------->"<<m_CarPOT.shortsemi_circle_radius<<endl;
                }
                else if(tmpKey == "long_semi_circle_radius")
                {
                    value = line.substr(assignmentPos+2);//
                    m_CarPOT.long_semi_circle_radius = (float)atoi(value.c_str());
                    //cout<< "m_CarPOT.long_semi_circle_radius is -------->"<<m_CarPOT.long_semi_circle_radius<<endl;
                }

            }

        }

        else
        {
            //cout<< "note line"<<endl;
        }
    }

    if(cfgFile.is_open())
    {
        cfgFile.close();
    }
    return true;

}
#endif
void GraphicVDT::MallocLineData()
{
    m_Lines = (linesData*)malloc(eLineMaxIndex*sizeof(linesData));
    linesData* curLineData;
    lineBorderOp borderOp;
    unsigned short tmpPtElemNum;
    unsigned short tmpIndexElemNum;
    if(NULL != m_Lines)
    {
        for (int i=0;i<eLineMaxIndex;i++)
        {
            curLineData = &m_Lines[i];
            curLineData->startIndex = 0;
            borderOp.CalLine2DBorderPtNum(LINE_PTN_NUM/2,tmpPtElemNum,tmpIndexElemNum);
            curLineData->pLinePtElemNum = tmpPtElemNum;
            curLineData->pLineIndexNum = tmpIndexElemNum;
            curLineData->pLineData = (float*)malloc(tmpPtElemNum*sizeof(float));
            curLineData->pArrayData = (float*)malloc(tmpIndexElemNum*4*sizeof(float));
            curLineData->pLineIndex = (unsigned short*)malloc(tmpIndexElemNum*sizeof(unsigned short));
        }
    }
    else
    {
        cout << "m_Lines is NULL...\n";
    }
    for(int i=0;i<eLineMaxIndex;i++)
	{
		m_temp[i] =  (float *)new float[2*LINE_PTN_NUM];
	}
}
/*
1	ForwardNegative will show driving lines extending toward the front and left side of the vehicle
2	ForwardPositive will show driving lines extending toward the front and right side of the vehicle
3	BackwardNegative will show driving lines extending toward the rear and left side of the vehicle
4	BackwardPositive will show driving lines extending toward the rear and right side of the vehicle

My understanding is that the point of tangency will not vary dynamically, 
for the example case below it would always be the right rear POT and the left front POT and they are fixed. 
The thing that varies based on steering wheel angle is the point you have circled in red (you called it the ??quad circle??)
CAN sig    <---> Line tended     <----> POT 
FrtNeg           Frt-Left		        bottom left(long left)   +top right(short right)
FrtPos           Frt-Right		        top left   (short left)  +bottom right(long right)
BakNeg           Rear-Left		        top left   (long left)   +bottom right(short right)
BakPos           Rear-Right		        bottom left(short left)  +top right(long right)
*/

/*
center of the circle of the long radius and the short radius shall be same 
but the POT on of long radius and the short radius connected to car is fixed

so current implementation is:
1 fix the POT of long radius and the short radius
2 calculate the center of the circle, if they are not at same position/range then report a warning 

*/
void GraphicVDT:: CalLineData()
{
    cout<<"Calculate Line Data"<<endl;
    /************************************************************************/
    /*  6 status:
        0->Forward
        1->Left_Forward
        2->Right_Forward
        3->RearWard
        4->Left_Forward
        5->Right_ForWard
    */
    /************************************************************************/
    lineBorderOp borderOp;
    linesData* group;

	m_CarPOT.fTheta_startLongR  = atan(m_CarPOT.fCarHeight/m_CarPOT.long_semi_circle_radius);
    if (line_status==e_Forward)//forward
    {
    	//line 0 is left line, line 1 is right line

        //line is composited by small segment - 4 points(2 triangles)
        for (int j=0;j<LINE_PTN_NUM/2;j++)
        {	
            //segment(j) bottom left x
            m_temp[eShortCircle][j*4] =   m_CarPOT.LeftBottom.x;//two lines x offset is m_CarPOT.fCarWidth
            //line y - vertex vertical offset = m_fLineSegmentHeight
            m_temp[eShortCircle][j*4+1] = m_CarPOT.LeftBottom.y+j*m_fLineSegmentHeight;//height of one segment of the line is m_fLineSegmentHeight
            //segment(j) bottom right x
            m_temp[eShortCircle][j*4+2] = m_temp[eShortCircle][j*4]+m_fLineWidth;//line witdh is m_fLineWidth
            m_temp[eShortCircle][j*4+3] = m_temp[eShortCircle][j*4+1];

			m_temp[eLongCircle][j*4] =   m_CarPOT.LeftBottom.x+m_CarPOT.fCarWidth;//two lines x offset is m_CarPOT.fCarWidth
            //line y - vertex vertical offset = m_fLineSegmentHeight
            m_temp[eLongCircle][j*4+1] = m_CarPOT.LeftBottom.y+j*m_fLineSegmentHeight;//height of one segment of the line is m_fLineSegmentHeight
            //segment(j) bottom right x
            m_temp[eLongCircle][j*4+2] = m_temp[eLongCircle][j*4]+m_fLineWidth;//line witdh is m_fLineWidth
            m_temp[eLongCircle][j*4+3] = m_temp[eLongCircle][j*4+1];
        }
    }
    else if (line_status==e_Rearward)
    {
        for (int j=0;j<LINE_PTN_NUM/2;j++)
        {
            m_temp[eShortCircle][j*4] =   m_CarPOT.LeftBottom.x;
            m_temp[eShortCircle][j*4+1] = m_CarPOT.LeftBottom.y+m_CarPOT.fCarHeight-j*m_fLineSegmentHeight;//rear direction is towards bottom of the view
            m_temp[eShortCircle][j*4+2] = m_temp[eShortCircle][j*4]+m_fLineWidth;
            m_temp[eShortCircle][j*4+3] = m_temp[eShortCircle][j*4+1];

            m_temp[eLongCircle][j*4] =   m_CarPOT.LeftBottom.x+m_CarPOT.fCarWidth;
            m_temp[eLongCircle][j*4+1] = m_CarPOT.LeftBottom.y+m_CarPOT.fCarHeight-j*m_fLineSegmentHeight;//rear direction is towards bottom of the view
            m_temp[eLongCircle][j*4+2] = m_temp[eLongCircle][j*4]+m_fLineWidth;
            m_temp[eLongCircle][j*4+3] = m_temp[eLongCircle][j*4+1];
        }
    }
    else if (line_status==e_Forward_Lt)//left turn is negative turn, and short leftR long rightR
    {
        //m_CarPOT.ftheta_short = m_CarPOT.fVisibleLongLineLength/m_CarPOT.shortsemi_circle_radius;
        //m_CarPOT.ftheta_long = m_CarPOT.fVisibleShortLineLength/m_CarPOT.long_semi_circle_radius;
        //center for short short R
        m_CarPOT.semi_circle_certer_short.SetData(m_CarPOT.LeftBottom.x-m_CarPOT.shortsemi_circle_radius,m_CarPOT.LeftBottom.y);//left bottom of view --rear left of car as the curx cury
        //center for long long R
        m_CarPOT.fTheta_startLongR = asin(m_CarPOT.fCarHeight/m_CarPOT.long_semi_circle_radius);
        float flongTriangleLine =m_CarPOT.long_semi_circle_radius*cos(m_CarPOT.fTheta_startLongR);
        m_CarPOT.semi_circle_certer_long.SetData(m_CarPOT.RightBottom.x-flongTriangleLine,m_CarPOT.RightBottom.y);
		
        for (int j=0;j<LINE_PTN_NUM/2;j++)
        {

            //long visiable line segment(j) bottom left x left x, 0~90 degree, step is 2/LINE_PTN_NUM
            m_temp[eShortCircle][j*4] =   m_CarPOT.semi_circle_certer_long.x+m_CarPOT.long_semi_circle_radius*(cos(m_CarPOT.fTheta_startLongR+j*m_CarPOT.ftheta_long*2/LINE_PTN_NUM));
            m_temp[eShortCircle][j*4+1] = m_CarPOT.semi_circle_certer_long.y+m_CarPOT.long_semi_circle_radius*(sin(m_CarPOT.fTheta_startLongR+j*m_CarPOT.ftheta_long*2/LINE_PTN_NUM));
            m_temp[eShortCircle][j*4+2] = m_CarPOT.semi_circle_certer_long.x+(m_CarPOT.long_semi_circle_radius+m_fLineWidth)*(cos(m_CarPOT.fTheta_startLongR+j*m_CarPOT.ftheta_long*2/LINE_PTN_NUM));
            m_temp[eShortCircle][j*4+3] = m_CarPOT.semi_circle_certer_long.y+(m_CarPOT.long_semi_circle_radius+m_fLineWidth)*(sin(m_CarPOT.fTheta_startLongR+j*m_CarPOT.ftheta_long*2/LINE_PTN_NUM));

            //short visiable line segment(j) bottom left x left x, 0~90 degree, step is 2/LINE_PTN_NUM , fTheta_startShorR is 0
            m_temp[eLongCircle][j*4] = m_CarPOT.semi_circle_certer_short.x+m_CarPOT.shortsemi_circle_radius*(cos(j*m_CarPOT.ftheta_short*2/LINE_PTN_NUM));
            m_temp[eLongCircle][j*4+1] = m_CarPOT.semi_circle_certer_short.y+m_CarPOT.shortsemi_circle_radius*(sin(j*m_CarPOT.ftheta_short*2/LINE_PTN_NUM));
			//short visiable line segment(j) bottom right x
            m_temp[eLongCircle][j*4+2] = m_CarPOT.semi_circle_certer_short.x+(m_CarPOT.shortsemi_circle_radius+m_fLineWidth)*(cos(j*m_CarPOT.ftheta_short*2/LINE_PTN_NUM));
            m_temp[eLongCircle][j*4+3] = m_CarPOT.semi_circle_certer_short.y+(m_CarPOT.shortsemi_circle_radius+m_fLineWidth)*(sin(j*m_CarPOT.ftheta_short*2/LINE_PTN_NUM));
        }

    }
    else if (line_status==e_Forward_Rt)//right turn is positive turn, and long leftR short rightR
    {
        m_CarPOT.semi_circle_certer_short.SetData(m_CarPOT.RightBottom.x+m_CarPOT.shortsemi_circle_radius,m_CarPOT.RightBottom.y);
        //center for long long R
        m_CarPOT.fTheta_startLongR = asin(m_CarPOT.fCarHeight/m_CarPOT.long_semi_circle_radius);
        float flongTriangleLine =m_CarPOT.long_semi_circle_radius*cos(m_CarPOT.fTheta_startLongR);
        m_CarPOT.semi_circle_certer_long.SetData(m_CarPOT.LeftBottom.x+flongTriangleLine,m_CarPOT.LeftBottom.y);

        for (int j=0;j<LINE_PTN_NUM/2;j++)
        {
            m_temp[eLongCircle][j*4] = m_CarPOT.semi_circle_certer_long.x+m_CarPOT.long_semi_circle_radius*(cos(R_PI-m_CarPOT.fTheta_startLongR-j*m_CarPOT.ftheta_long*2/LINE_PTN_NUM));
            m_temp[eLongCircle][j*4+1] = m_CarPOT.semi_circle_certer_long.y+m_CarPOT.long_semi_circle_radius*(sin(R_PI-m_CarPOT.fTheta_startLongR-j*m_CarPOT.ftheta_long*2/LINE_PTN_NUM));
            m_temp[eLongCircle][j*4+2] = m_CarPOT.semi_circle_certer_long.x+(m_CarPOT.long_semi_circle_radius-m_fLineWidth)*(cos(R_PI-m_CarPOT.fTheta_startLongR-j*m_CarPOT.ftheta_long*2/LINE_PTN_NUM));
            m_temp[eLongCircle][j*4+3] = m_CarPOT.semi_circle_certer_long.y+(m_CarPOT.long_semi_circle_radius-m_fLineWidth)*(sin(R_PI-m_CarPOT.fTheta_startLongR-j*m_CarPOT.ftheta_long*2/LINE_PTN_NUM));

            m_temp[eShortCircle][j*4] = m_CarPOT.semi_circle_certer_short.x+m_CarPOT.shortsemi_circle_radius*(cos(R_PI-j*m_CarPOT.ftheta_short*2/LINE_PTN_NUM));
            m_temp[eShortCircle][j*4+1] = m_CarPOT.semi_circle_certer_short.y+m_CarPOT.shortsemi_circle_radius*(sin(R_PI-j*m_CarPOT.ftheta_short*2/LINE_PTN_NUM));
            m_temp[eShortCircle][j*4+2] = m_CarPOT.semi_circle_certer_short.x+(m_CarPOT.shortsemi_circle_radius-m_fLineWidth)*(cos(R_PI-j*m_CarPOT.ftheta_short*2/LINE_PTN_NUM));
            m_temp[eShortCircle][j*4+3] = m_CarPOT.semi_circle_certer_short.y+(m_CarPOT.shortsemi_circle_radius-m_fLineWidth)*(sin(R_PI-j*m_CarPOT.ftheta_short*2/LINE_PTN_NUM));
        }
    }
	else if (line_status==e_Rearward_Rt)
    {
        m_CarPOT.semi_circle_certer_short.SetData(m_CarPOT.RightBottom.x+m_CarPOT.shortsemi_circle_radius,m_CarPOT.RightBottom.y);
        //center for long long R
        m_CarPOT.fTheta_startLongR = asin(m_CarPOT.fCarHeight/m_CarPOT.long_semi_circle_radius);
        float flongTriangleLine =m_CarPOT.long_semi_circle_radius*cos(m_CarPOT.fTheta_startLongR);
        m_CarPOT.semi_circle_certer_long.SetData(m_CarPOT.LeftBottom.x+flongTriangleLine,m_CarPOT.LeftBottom.y);

        for (int j=0;j<LINE_PTN_NUM/2;j++)
        {
            m_temp[eShortCircle][j*4] = m_CarPOT.semi_circle_certer_short.x+m_CarPOT.shortsemi_circle_radius*(cos(R_PI+j*m_CarPOT.ftheta_short*2/LINE_PTN_NUM));
            m_temp[eShortCircle][j*4+1] = m_CarPOT.semi_circle_certer_short.y+m_CarPOT.shortsemi_circle_radius*(sin(R_PI+j*m_CarPOT.ftheta_short*2/LINE_PTN_NUM));
            m_temp[eShortCircle][j*4+2] = m_CarPOT.semi_circle_certer_short.x+(m_CarPOT.shortsemi_circle_radius-m_fLineWidth)*(cos(R_PI+j*m_CarPOT.ftheta_short*2/LINE_PTN_NUM));
            m_temp[eShortCircle][j*4+3] = m_CarPOT.semi_circle_certer_short.y+(m_CarPOT.shortsemi_circle_radius-m_fLineWidth)*(sin(R_PI+j*m_CarPOT.ftheta_short*2/LINE_PTN_NUM));
     
            m_temp[eLongCircle][j*4] = m_CarPOT.semi_circle_certer_long.x+m_CarPOT.long_semi_circle_radius*(cos(R_PI-m_CarPOT.fTheta_startLongR+j*m_CarPOT.ftheta_long*2/LINE_PTN_NUM));
            m_temp[eLongCircle][j*4+1] = m_CarPOT.semi_circle_certer_long.y+m_CarPOT.long_semi_circle_radius*(sin(R_PI-m_CarPOT.fTheta_startLongR+j*m_CarPOT.ftheta_long*2/LINE_PTN_NUM));
            m_temp[eLongCircle][j*4+2] = m_CarPOT.semi_circle_certer_long.x+(m_CarPOT.long_semi_circle_radius-m_fLineWidth)*(cos(R_PI-m_CarPOT.fTheta_startLongR+j*m_CarPOT.ftheta_long*2/LINE_PTN_NUM));
            m_temp[eLongCircle][j*4+3] = m_CarPOT.semi_circle_certer_long.y+(m_CarPOT.long_semi_circle_radius-m_fLineWidth)*(sin(R_PI-m_CarPOT.fTheta_startLongR+j*m_CarPOT.ftheta_long*2/LINE_PTN_NUM));
		}
    }else if (line_status==e_Rearward_Lt)
    {
        //m_CarPOT.ftheta_short = m_CarPOT.fVisibleShortLineLength/m_CarPOT.shortsemi_circle_radius;
        //m_CarPOT.ftheta_long = m_CarPOT.fVisibleLongLineLength/m_CarPOT.long_semi_circle_radius;
        m_CarPOT.semi_circle_certer_short.SetData(m_CarPOT.LeftBottom.x-m_CarPOT.shortsemi_circle_radius,m_CarPOT.LeftBottom.y);
        //center for long right R
        m_CarPOT.fTheta_startLongR = asin(m_CarPOT.fCarHeight/m_CarPOT.long_semi_circle_radius);
        float flongTriangleLine =m_CarPOT.long_semi_circle_radius*cos(m_CarPOT.fTheta_startLongR);
        m_CarPOT.semi_circle_certer_long.SetData(m_CarPOT.RightBottom.x-flongTriangleLine,m_CarPOT.RightBottom.y);

        for (int j=0;j<LINE_PTN_NUM/2;j++)
		{
			m_temp[eShortCircle][j*4] =   m_CarPOT.semi_circle_certer_short.x+m_CarPOT.shortsemi_circle_radius*(cos(-j*m_CarPOT.ftheta_short*2/LINE_PTN_NUM));
			m_temp[eShortCircle][j*4+1] = m_CarPOT.semi_circle_certer_short.y+m_CarPOT.shortsemi_circle_radius*(sin(-j*m_CarPOT.ftheta_short*2/LINE_PTN_NUM));
			m_temp[eShortCircle][j*4+2] = m_CarPOT.semi_circle_certer_short.x+(m_CarPOT.shortsemi_circle_radius+m_fLineWidth)*(cos(-j*m_CarPOT.ftheta_short*2/LINE_PTN_NUM));
			m_temp[eShortCircle][j*4+3] = m_CarPOT.semi_circle_certer_short.y+(m_CarPOT.shortsemi_circle_radius+m_fLineWidth)*(sin(-j*m_CarPOT.ftheta_short*2/LINE_PTN_NUM));

			m_temp[eLongCircle][j*4] = m_CarPOT.semi_circle_certer_long.x+m_CarPOT.long_semi_circle_radius*(cos(m_CarPOT.fTheta_startLongR-j*m_CarPOT.ftheta_long*2/LINE_PTN_NUM));
			m_temp[eLongCircle][j*4+1] = m_CarPOT.semi_circle_certer_long.y+m_CarPOT.long_semi_circle_radius*(sin(m_CarPOT.fTheta_startLongR-j*m_CarPOT.ftheta_long*2/LINE_PTN_NUM));
			m_temp[eLongCircle][j*4+2] = m_CarPOT.semi_circle_certer_long.x+(m_CarPOT.long_semi_circle_radius+m_fLineWidth)*(cos(m_CarPOT.fTheta_startLongR-j*m_CarPOT.ftheta_long*2/LINE_PTN_NUM));
			m_temp[eLongCircle][j*4+3] = m_CarPOT.semi_circle_certer_long.y+(m_CarPOT.long_semi_circle_radius+m_fLineWidth)*(sin(m_CarPOT.fTheta_startLongR-j*m_CarPOT.ftheta_long*2/LINE_PTN_NUM));
		}
    }

	//debug purpose : draw a cross line to center of circle
	//line 2,3 short circle cross
	//line 4,5 long circle cross
	//if ((line_status!=e_Forward)&&(line_status!=e_Rearward))//forward
	{
		//vertical line
		for (int j=0;j<LINE_PTN_NUM/2;j++)
		{	
			//vertical line cross short radius circle 
			m_temp[eSCircleCtrVert][j*4] =   m_CarPOT.semi_circle_certer_short.x-0.5;//two lines x offset is m_CarPOT.fCarWidth
			//line y - vertex vertical offset = m_fLineSegmentHeight
			m_temp[eSCircleCtrVert][j*4+1] = m_CarPOT.semi_circle_certer_short.y+j*m_fLineSegmentHeight;//height of one segment of the line is m_fLineSegmentHeight
			//segment(j) bottom right x
			m_temp[eSCircleCtrVert][j*4+2] = m_temp[eSCircleCtrVert][j*4]+1;//line witdh is m_fLineWidth
			m_temp[eSCircleCtrVert][j*4+3] = m_temp[eSCircleCtrVert][j*4+1];

			//horizontal line cross short radius circle 
			m_temp[eSCircleCtrHorz][j*4] =   m_CarPOT.semi_circle_certer_short.x+j*m_fLineSegmentHeight;//two lines x offset is m_CarPOT.fCarWidth
			//line y - vertex vertical offset = m_fLineSegmentHeight
			m_temp[eSCircleCtrHorz][j*4+1] = m_CarPOT.semi_circle_certer_short.y-0.5;//height of one segment of the line is m_fLineSegmentHeight
			//segment(j) bottom right x
			m_temp[eSCircleCtrHorz][j*4+2] = m_temp[eSCircleCtrHorz][j*4];//line witdh is m_fLineWidth
			m_temp[eSCircleCtrHorz][j*4+3] = m_temp[eSCircleCtrHorz][j*4+1]+1;

		   //vertical line cross long radius circle 
			m_temp[eLCircleCtrVert][j*4] =   m_CarPOT.semi_circle_certer_long.x-0.5;//two lines x offset is m_CarPOT.fCarWidth
			//line y - vertex vertical offset = m_fLineSegmentHeight
			m_temp[eLCircleCtrVert][j*4+1] = m_CarPOT.semi_circle_certer_long.y+j*m_fLineSegmentHeight;//height of one segment of the line is m_fLineSegmentHeight
			//segment(j) bottom right x
			m_temp[eLCircleCtrVert][j*4+2] = m_temp[eLCircleCtrVert][j*4]+1;//line witdh is m_fLineWidth
			m_temp[eLCircleCtrVert][j*4+3] = m_temp[eLCircleCtrVert][j*4+1];


			//horizontal line cross long radius circle 
			m_temp[eLCircleCtrHorz][j*4] =   m_CarPOT.semi_circle_certer_long.x+j*m_fLineSegmentHeight;//two lines x offset is m_CarPOT.fCarWidth
			//line y - vertex vertical offset = m_fLineSegmentHeight
			m_temp[eLCircleCtrHorz][j*4+1] = m_CarPOT.semi_circle_certer_long.y-0.5;//height of one segment of the line is m_fLineSegmentHeight
			//segment(j) bottom right x
			m_temp[eLCircleCtrHorz][j*4+2] = m_temp[eLCircleCtrHorz][j*4];//line witdh is m_fLineWidth
			m_temp[eLCircleCtrHorz][j*4+3] = m_temp[eLCircleCtrHorz][j*4+1]+1;
		}
	}

    for (int i=0;i<eLineMaxIndex;i++)
    {
        group = &m_Lines[i];
        float* borderData = group->pLineData;
        unsigned short lineStartIndex = group->startIndex;
        unsigned short* borderIndex = group->pLineIndex;
        borderOp.CalLine2DBorder(m_temp[i],group->pLinePtElemNum,lineStartIndex,borderData,borderIndex);
    }
}
/*
the PrkAidDrvDir_D_Stat is now going to indicate the turning and driving direction with the signals. 
This is again going to be covered in the new v1.3 SPSS but here is a summary of what is in that new SPSS:

1	ForwardNegative will show driving lines extending toward the front and left side of the vehicle
2	ForwardPositive will show driving lines extending toward the front and right side of the vehicle
3	BackwardNegative will show driving lines extending toward the rear and left side of the vehicle
4	BackwardPositive will show driving lines extending toward the rear and right side of the vehicle

My understanding is that the point of tangency will not vary dynamically, 
for the example case below it would always be the right rear POT and the left front POT and they are fixed. 
The thing that varies based on steering wheel angle is the point you have circled in red (you called it the ¡°quad circle¡±)
CAN sig    <---> Line tended     <----> POT(visible line is long-short -- but radius is short-long) 
FrtNeg           Frt-Left		        bottom left(long left)   +top right(short right)
FrtPos           Frt-Right		        top left   (short left)  +bottom right(long right)
BakNeg           Rear-Left		        top left   (long left)   +bottom right(short right)
BakPos           Rear-Right		        bottom left(short left)  +top right(long right)

*short radius is always 1/4 cycle
*the center of the cycle changes

table of forward & rearward , positive & negative , radius , cycle point
	       FN    FP    BN    BP 
short R  
long  R

*/

bool GraphicVDT::bSetVDTState(int vdtDir,int vdtStatus,int shortRadius,int longRadius)
{
    if(vdtDir==eForward)
    {
        if(shortRadius==0&&longRadius==0)
        {
            shortRadius=1000;
            longRadius=1000;
            line_status = e_Forward;
        }
		else if(vdtStatus==ePositive)
        {
            line_status = e_Forward_Rt;

        }else
        {
            line_status = e_Forward_Lt;
        }

    }
	else
    {
        if(shortRadius==0&&longRadius==0)
        {
            shortRadius=1000;
            longRadius=1000;
            line_status = e_Rearward;
        }
		else if(vdtStatus==ePositive)
        {
            line_status = e_Rearward_Rt;

        }else
        {
            line_status = e_Rearward_Lt;
        }

    }
	shortRadius*=1.22;
	longRadius*=1.22;
    m_CarPOT.shortsemi_circle_radius = shortRadius+56;//*m_fScale?
    m_CarPOT.long_semi_circle_radius = longRadius+100;
    //m_CarPOT.long_semi_circle_radius = sqrt((m_CarPOT.shortsemi_circle_radius+m_CarPOT.fCarWidth)*(m_CarPOT.shortsemi_circle_radius+m_CarPOT.fCarWidth)+m_CarPOT.fCarHeight*m_CarPOT.fCarHeight);
    CalLineData();
    return false;
}

bool GraphicVDT::bSetVDTLeftBottom(int x, int y)
{
	vUpdateCarVertex(x,y);
    CalLineData();
    return true;
}

bool GraphicVDT::bSetVDTSize(int posX,int posY,float rescale)
{
	m_fScale = rescale;
    m_CarPOT.LeftBottom.x = posX+(int)(m_CarPOT.LeftBottom.x-posX)*rescale;//base point x
    m_CarPOT.LeftBottom.y = posY+(int)(m_CarPOT.LeftBottom.y-posY)*rescale;//base point y
    m_fLineWidth = m_fLineWidth*rescale;
    m_fLineSegmentHeight = (int)m_fLineSegmentHeight*rescale;
    m_CarPOT.fCarWidth = m_CarPOT.fCarWidth*rescale;
    m_CarPOT.fCarHeight = m_CarPOT.fCarHeight*rescale;
	//no need to dynamica change guide line size? otherwise the radius shall be rescaled on every update
	vUpdateCarVertex(m_CarPOT.LeftBottom.x,m_CarPOT.LeftBottom.y,m_CarPOT.fCarWidth,m_CarPOT.fCarHeight);
    m_CarPOT.shortsemi_circle_radius = m_CarPOT.shortsemi_circle_radius*rescale;//
    m_CarPOT.long_semi_circle_radius = m_CarPOT.long_semi_circle_radius*rescale;//
    //m_CarPOT.long_semi_circle_radius = sqrt((m_CarPOT.shortsemi_circle_radius+m_CarPOT.fCarWidth)*(m_CarPOT.shortsemi_circle_radius+m_CarPOT.fCarWidth)+m_CarPOT.fCarHeight*m_CarPOT.fCarHeight);
    m_CarPOT.fVisibleShortLineLength = m_CarPOT.fVisibleShortLineLength*rescale;
    m_CarPOT.fVisibleLongLineLength = m_CarPOT.fVisibleLongLineLength*rescale;
    //m_CarPOT.ftheta_short = m_CarPOT.fVisibleShortLineLength/m_CarPOT.shortsemi_circle_radius;
    //m_CarPOT.ftheta_long = m_CarPOT.fVisibleLongLineLength/m_CarPOT.long_semi_circle_radius;
    //m_CarPOT.fTheta_startShortR = atan(m_CarPOT.fCarHeight/(m_CarPOT.shortsemi_circle_radius+m_CarPOT.fCarWidth));
	m_CarPOT.fTheta_startLongR = atan(m_CarPOT.fCarHeight/(m_CarPOT.long_semi_circle_radius+m_CarPOT.fCarWidth));
    CalLineData();
    return false;
}

bool GraphicVDT::bSetVDTEnable()
{
    PDCL_LOG_INFO("Plane::SetVDTEnable()");
    b_vdtState = true;
    return true;
}


bool GraphicVDT::bSetVDTDisable()
{
    PDCL_LOG_INFO("Plane::SetVDTDisable()");
    b_vdtState = false;
    return true;

}


