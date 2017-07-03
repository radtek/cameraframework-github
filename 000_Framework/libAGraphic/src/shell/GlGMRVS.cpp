/*
 * GlGMRVS.cpp
 *
 *  Created on: 2012-4-6
 */
#include "GlGMRVS.h"
#include "RVSDefine.h"
#define RVS_OVLAY_TRACK_WIDTH 5
//#define RVS_OVLAY_DELTA_DIST_MARKS 1
//#define RVS_OVLAY_NUM_DIST_MARKS 2
#define RVS_OVLAY_LINE_WIDTH 5
GlGMRVS* GlGMRVS::instance = NULL;
GlGMRVS* GlGMRVS::getInstance()
{
	if(!instance)
	{
		instance = new GlGMRVS;
		return instance;
	}
	else
		return instance;
}


GlGMRVS::GlGMRVS()
{
//	m_pGuideLine = NULL;
	m_ParkingSymbolZone[0] = 0;
	m_ParkingSymbolZone[1] = 0;
	m_ParkingSymbolZone[2] = 0;

//	m_RCTALeft.RCTAIndication = 0;
//	m_RCTARight.RCTAIndication = 0;
	m_bContinue2Draw = true;
	pEglDisplay = NULL;
}

GlGMRVS::~GlGMRVS()
{
//	if(m_pGuideLine)
//		delete m_pGuideLine;
}
extern "C" {
#if 0
extern int gdebug_tdis1;
extern int gdebug_tdis2;

extern int gdebug_tlen1;
extern int gdebug_tlen2;

extern int gdebug_mstardis;
extern int gdebug_width;
extern int gdebug_overtrackw;
extern int gdebug_overdeltaDis;
extern int  gdebug_overnumDis;
extern int  gdebug_overLineDis;
#endif
}
int GlGMRVS::Init(int screenWidth, int screenHeight, void* pDisplayContext)
{

	m_iScreenWidth = screenWidth;
	m_iScreenHeight = screenHeight;

	pEglDisplay = pDisplayContext;

	//if(ctx->calibFromPPS)
	//{
	//	InitParamFromPPS(ctx,screenWidth,screenHeight);
	//}
	//else
	{
		cameraPara_t param;
		param.extrinsic = CAM_EXTRINSIC_GM;
		param.intrinsic = CAM_INTRINSIC_GM;
		m_LCamera.init(param);
		//draw line---need to change according to group nums
		float groupSep[RVS_GUIDELINE_GROUP_NUM+1] = {0.0,RVS_GUIDELINE_L_SEGMENT_DISTANCE,2*RVS_GUIDELINE_L_SEGMENT_DISTANCE,3*RVS_GUIDELINE_L_SEGMENT_DISTANCE,RVS_GUIDELINE_FAR_END_DISTANCE};//in GM:take distance as 2 segment:0-0.5m red(L-segment)  0.5m-5m orange
		color3 color[RVS_GUIDELINE_GROUP_NUM] = {RVS_COLOR_RED,RVS_COLOR_RED, RVS_COLOR_YELLOW,RVS_COLOR_GREEN};
		m_GuideLine.SetWindowParam(m_iScreenWidth,m_iScreenHeight);
		float tickLength[RVS_GUIDELINE_GROUP_NUM] =  {0.0,0.0,0.0,0.0};//{RVS_GUIDELINE_L_SEGMENT_LENGTH,0.0,0.0};
		trajectory tmpTrajectory;

		//fprintf(stderr,"guideLine config  = %d",ctx->vehicleConfig.guideLine);
//test
		int Cfg_guideLine = EGdLStatic;
		if( EGdLStatic == Cfg_guideLine)
		{
		
			//fprintf(stderr,"GlGMRVS EGdLStatic----------------------------");
			m_GuideLine.InitLineParam(RVS_GUIDELINE_GROUP_NUM,groupSep,tickLength,color,RVS_GUIDELINE_MARKER_STARTDIS,
					RVS_OVLAY_DELTA_DIST_MARKS,RVS_OVLAY_NUM_DIST_MARKS,RVS_OVLAY_TRACK_WIDTH,
					RVS_GUIDELINE_WIDTH,&m_LCamera,tmpTrajectory);

		}
		else if( EGdLDynamic == Cfg_guideLine)
		{
			m_GuideLine.InitLineParam(RVS_GUIDELINE_GROUP_NUM,groupSep,tickLength,color,RVS_GUIDELINE_MARKER_STARTDIS,
					RVS_OVLAY_DELTA_DIST_MARKS,RVS_OVLAY_NUM_DIST_MARKS,RVS_OVLAY_MARKER_WIDTH,
					RVS_GUIDELINE_WIDTH,&m_LCamera,tmpTrajectory,eDynamicGuideLine,false);
		}
		m_GuideLine.SetSWAUpdatePrecision(RVS_STEERING_WHEEL_DELTA);

	}
#if 0
	PVRTVec3	vFrom, vTo, vUp;
	VERTTYPE	fFOV;
	vFrom.x = 0.0f;
	vFrom.y = 0.0f;
	vFrom.z = 4.95f;
	vTo.x = 0.0f;
	vTo.y = 0.0f;
	vTo.z = 0.0f;
	vUp.x = 0.0f;
	vUp.y = 1.0f;
	vUp.z = 0.0f;
	fFOV = 0.398f;
	m_mView = PVRTMat4::LookAtRH(vFrom, vTo, vUp);
	m_mProj = PVRTMat4::PerspectiveFovRH(fFOV, (float)m_iScreenWidth/(float)m_iScreenHeight, CAM_NEAR, CAM_FAR, PVRTMat4::OGL, false);
	m_mPVMat = m_mProj*m_mView;

	glClearColor(0.0,0.0,0.0,1.0);
	glClearDepthf(-1.0);
	glDepthFunc(GL_GEQUAL);
	glEnable(GL_DEPTH_TEST);
#endif
	return 0;
}

int GlGMRVS::InitParamFromPPS(rvs_ctx_t* ctx,int screenWidth,int screenHeight)
{
	//init CamParam
	if(InitCamParamFromPPS(ctx,&m_LCamera))
		return -1;

	if(InitGuideLineParamFromPPS(ctx,screenWidth,screenHeight,&m_LCamera))
		return -1;

	if(InitUPAParamFromPPS(ctx,screenWidth,screenHeight))
		return -1;

	if(InitRCTAParamFromPPS(ctx))
		return -1;

//	if(InitFontParamFromPPS(ctx,screenWidth,screenHeight))
//		return -1;

	return 0;
}

int GlGMRVS::InitCamParamFromPPS(rvs_ctx_t* ctx,LCamera* pCam)
{
    rvs_camera_params rvsCamParam;
  //  if(!PPS_InitCameraParam(rvsCamParam))
    	return -1;
    pCam->init(rvsCamParam);
    return 0;
}

int GlGMRVS::InitUPAParamFromPPS(rvs_ctx_t* ctx,int screenWidth,int screenHeight)
{//tbd x100 no upa confg, no cr now
#if 0
	//init upa params;
    rvs_parkAssist_params upaParam;
	static bool initUPA = false;//?

	//Initialization has been done ! Skip the following lines.
	if(initUPA)
		return 0;
	
 //   if(!PPS_InitUPAParam(upaParam))
//    	return -1;
//    PrintUPAParam(upaParam);
	float symbolSize[ePARearZoneNum] = {RVS_UPA_SIZE_ZONE0,RVS_UPA_SIZE_ZONE1,RVS_UPA_SIZE_ZONE2,RVS_UPA_SIZE_ZONE3,RVS_UPA_SIZE_ZONE4};
	PASymbolColor symbolColor[ePARearZoneNum] = {RVS_PA_SYMBOL_RED,RVS_PA_SYMBOL_RED,RVS_PA_SYMBOL_RED,RVS_PA_SYMBOL_ORANGE,RVS_PA_SYMBOL_ORANGE};
    if(m_ParkSymbol.Init(RVS_UPA_RES,upaParam,symbolSize,symbolColor,
		RVS_UPA_FLASH_FREQUENCY,RVS_UPA_FLASH_DURATION,screenWidth,screenHeight/*,upaParam.upaType*/))
    {
    	printf("Error:UPA init failed!\n");
		return -1;
    }

	//UPA found
	ctx->symblAvail.UPAResourceAvail = true;
	initUPA = true;
#endif
    return 0;
}

int GlGMRVS::InitRCTAParamFromPPS(rvs_ctx_t* ctx)
{//tbd x100 no rcta confg, no cr now
    //init rcta params
    rvs_rcta_params rctaParam;
	static bool initRCTA = false;

	//Initialization has been done ! Skip the following lines.
	if(initRCTA)
		return 0;
	
  //  if(!PPS_InitRCTAParam(rctaParam))
  //  	return -1;
	const char* file[2] = {RVS_RCTALEFT_RES,RVS_RCTARIGHT_RES};

	if(m_RCTASymbol.Init(rctaParam,file,RVS_RCTA_ICON_FLASH_FREQUENCY,m_iScreenWidth,m_iScreenHeight))
	{
		printf("Error: RCTA init failed!\n");
		return -1;
	}

	ctx->symblAvail.RCTAResourceAvail = true;
	initRCTA = true;
	
	return 0;
}

int GlGMRVS::InitGuideLineParamFromPPS(rvs_ctx_t* ctx,int screenWidth,int screenHeight,LCamera* pCam)
{
    //init guideline params
    rvs_steer_params steerParam;
  //  PPS_InitSteerParam(steerParam);
//    PrintSteerParam(steerParam);

    float farestMarker = RVS_GUIDELINE_MARKER_STARTDIS + steerParam.deltaDistMarks*(steerParam.numDistMarks-1);
	float groupSep[RVS_GUIDELINE_GROUP_NUM+1] = {0.0,RVS_GUIDELINE_L_SEGMENT_DISTANCE,farestMarker};
	color3 color[RVS_GUIDELINE_GROUP_NUM] = {RVS_COLOR_RED, RVS_COLOR_GREEN};
	float tickLength[RVS_GUIDELINE_GROUP_NUM] =  {RVS_GUIDELINE_L_SEGMENT_LENGTH,0.0};
	m_GuideLine.SetWindowParam(screenWidth,screenHeight);
	if( EGdLStatic == ctx->vehicleConfig.guideLine)
	{
		m_GuideLine.InitLineParam(RVS_GUIDELINE_GROUP_NUM,groupSep,tickLength,color,
				RVS_GUIDELINE_MARKER_STARTDIS,steerParam,RVS_GUIDELINE_WIDTH,pCam);
	}
	else if( EGdLDynamic == ctx->vehicleConfig.guideLine)
	{
		m_GuideLine.InitLineParam(RVS_GUIDELINE_GROUP_NUM,groupSep,tickLength,color,
				RVS_GUIDELINE_MARKER_STARTDIS,steerParam,RVS_GUIDELINE_WIDTH,pCam,
				eDynamicGuideLine,false);
	}
	m_GuideLine.SetSWAUpdatePrecision(steerParam.swaDeltaAngle);

	return 0;
}

//int GlGMRVS::InitFontParamFromPPS(rvs_ctx_t* ctx,int screenWidth,int screenHeight)
//{
//	unsigned int fontLoc = 0;
//	PPS_InitTexPos(fontLoc);
//
//    rvs_driverMsg driverMsg;
//    PPS_InitDriverMsg(driverMsg);
//	TextPos msgPos[DRIVERMSGNUM] = {
//			{RVS_MSG_FAILED_SYNC,RVS_MSG_CENTER},
//			{RVS_MSG_GUIDELINES_FAIL,RVS_MSG_LINE2},
//			{RVS_MSG_CALIB_STEERING,RVS_MSG_LINE2},
//			{RVS_MSG_PARK_ASST_FAIL,RVS_MSG_LINE2},
//			{RVS_MSG_FAILED_TRANSMISSION,RVS_MSG_CENTER}
//	};
//
//	if(m_Font.Init(RVS_FONTTEX_RES,RVS_FONTTEXINFO_RES,screenWidth,screenHeight,eNumMsgs,MAXMSGLENGTH,fontLoc))
//	{
//		printf("Error: Font init failed!\n");
//		return -1;
//	}
//	m_Font.LoadMsgInfo(driverMsg,msgPos);
//	return 0;
//}

int GlGMRVS::Update()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glViewport(0,0,m_iScreenWidth,m_iScreenHeight);

	Update_EnableState();

	return 0;
}


void GlGMRVS::Update_EnableState()
{
	if(1)
	{
		PVRTMat4 mat = PVRTMat4::Identity();
		if(1)
		{
			m_GuideLine.Render(mat);
			//m_GuideLine.RenderTest(mat);
			
			//drawtest();
		}
		else if(0)
		{
			//m_GuideLine.Update(/*angle*/ctx->GMLANMessage.steeringWheelAngle);
			m_GuideLine.Update(/*angle*/0);
			m_GuideLine.Render(mat);
	
		}
	}
#if 0
	if(vConfig.UPASymbol == EUPASymPresent&&dCustom.RVS_ParkAsstSymbols)
	{
		/*
		 * for text priority
		 */
//		if(DiagnosticState.RVS_Failed_UPA)
//		{
//			if(!DiagnosticState.RVS_Failed_Steering&&!DiagnosticState.RVS_Failed_SWASensor)
//				m_Font.Draw(RVS_MSG_PARK_ASST_FAIL,m_mPVMat);
//		}
//		else
		if(!ctx->diagnosticStat.RVS_Failed_UPA)
		{
			if(ctx->symblAvail.UPAResourceAvail)
			{
				InitUPAParamFromPPS(ctx, m_iScreenWidth, m_iScreenHeight);

				m_ParkingSymbolZone[0] = ctx->GMLANMessage.PARearStatus.PARearRegion1ObjectStatus;
				m_ParkingSymbolZone[1] = ctx->GMLANMessage.PARearStatus.PARearRegion2ObjectStatus;
				m_ParkingSymbolZone[2] = ctx->GMLANMessage.PARearStatus.PARearRegion3ObjectStatus;
				m_ParkSymbol.Render(m_mPVMat,m_ParkingSymbolZone);
			}
		}
	}
	//*   TODO:  displayed whenever the rear camera images are being displayed
//	m_Font.Draw(RVS_MSG_PROPER_USAGE,m_mPVMat);

	if(ctx->symblAvail.RCTAResourceAvail)
	{
		InitRCTAParamFromPPS(ctx);
		m_RCTASymbol.Update(m_mPVMat,ctx->GMLANMessage.RCTALeft,ctx->GMLANMessage.RCTARight);
	}
#endif		
//	m_RCTASymbol.Update(m_mPVMat,m_RCTALeft,m_RCTARight);
}

//void GlGMRVS::Update_DisableState(rvs_ctx_t* ctx)
//{
//	/*
//	 * !!!attention the sequence
//	 * RVS_Failed_Sync shall have priority over the RVS_Failed_Transmission
//	 */
//	if(DiagnosticState.RVS_Failed_Sync)
//	{
//		glClearColor(0.0,0.0,0.0,1.0);
//		glClear(GL_COLOR_BUFFER_BIT);
//		m_Font.Draw(RVS_MSG_FAILED_SYNC,m_mPVMat);
//		glClearColor(0.0,0.0,0.0,0.0);
//	}
//	else if(DiagnosticState.RVS_Failed_Transmission)
//		m_Font.Draw(RVS_MSG_FAILED_TRANSMISSION,m_mPVMat);
//}

//void GlGMRVS::SetTestParam()
//{
//	m_Param.ParkingSymbolZone[0] = eRVS_PA_OBJECT_STATUS_UNKNOWN;
//	m_Param.ParkingSymbolZone[1] = eRVS_PA_OBJECT_STATUS_UNKNOWN;
//	m_Param.ParkingSymbolZone[2] = eRVS_PA_OBJECT_STATUS_UNKNOWN;
//
//	m_Param.leftRCTAState.RCTAIndication = 1;
//	m_Param.leftRCTAState.RCTAIndicationControl = eRVS_RCTA_CONTINUOUS_INDICATION;
//	m_Param.rightRCTAState.RCTAIndication = 0;
//	m_Param.rightRCTAState.RCTAIndicationControl = eRVS_RCTA_CONTINUOUS_INDICATION;
//
//	m_Param.SteeringAngleRad = PI/4;
//
//}
