#include "LCommon.h"

LCamera::LCamera()
{
	;
}

LCamera::~LCamera()
{
	;
}

void LCamera::init(cameraPara_t param)
{
	cameraPara = param;
	setCameraMatrix();
}

void LCamera::init(rvs_camera_params param)
{
	camera_extrinsic_t* extrin = &cameraPara.extrinsic;
	camera_intrinsic_t* intrin = &cameraPara.intrinsic;

	extrin->rx = param.rotx;
	extrin->ry = param.roty;
	extrin->rz = param.rotz;
	extrin->tx = param.offsetx;
	extrin->ty = param.offsety;
	extrin->tz = param.offsetz;

	intrin->fx = param.fu;
	intrin->fy = param.fv;
	intrin->cx = param.cu;
	intrin->cy = param.cv;
	intrin->k1 = param.distortCoef1;
	intrin->k2 = param.distortCoef2;
	setCameraMatrix();
}

void LCamera::setCameraMatrix()
{
	setIntrinsicMatrix();
	setExtrinsicMatrix();
	setInvExtrinsicMatrix();
	setProjectionMatrix();

	m_ProjMatTranspose = cameraPara.mat.projection.transpose();
	m_ExtrinMatTranspose = cameraPara.mat.ex_all.transpose();
}

void LCamera::setExtrinsicMatrix()
{
	f32_t tx = -cameraPara.extrinsic.tx;
	f32_t ty = -cameraPara.extrinsic.ty;
	f32_t tz = -cameraPara.extrinsic.tz;

	PVRTMat4 transMat = PVRTMat4::Translation(tx,ty,tz);

   f32_t rx = -R_Deg2Rad(cameraPara.extrinsic.rx);
   f32_t ry = -R_Deg2Rad(cameraPara.extrinsic.ry);
   f32_t rz = -R_Deg2Rad(cameraPara.extrinsic.rz);

   PVRTMat4 rotX =PVRTMat4::RotationX(rx);
   PVRTMat4 rotY = PVRTMat4::RotationY(ry);
   PVRTMat4 rotZ = PVRTMat4::RotationZ(rz);

   PVRTMat4 rotYZ = rotY*rotZ;
   PVRTMat4 rotXYZ = rotX*rotYZ;

   cameraPara.mat.ex_all = rotXYZ * transMat;

//   printf("tx=%f,ty=%f,tz=%f,rx=%f,ry=%f,rz=%f\n",tx,ty,tz,rx,ry,rz);
//
//   float* ptr= cameraPara.mat.ex_all.ptr();
//   printf("exMat:\n");
//   for(int i=0;i<16;i++)
//   {
//	   printf("%f\n",ptr[i]);
//   }
}

void LCamera::setInvExtrinsicMatrix()
{
	f32_t tx = cameraPara.extrinsic.tx;
	f32_t ty = cameraPara.extrinsic.ty;
	f32_t tz = cameraPara.extrinsic.tz;

	PVRTMat4 transMat = PVRTMat4::Translation(tx,ty,tz);

   f32_t rx = R_Deg2Rad(cameraPara.extrinsic.rx);
   f32_t ry = R_Deg2Rad(cameraPara.extrinsic.ry);
   f32_t rz = R_Deg2Rad(cameraPara.extrinsic.rz);

   PVRTMat4 rotX = PVRTMat4::RotationX(rx);
   PVRTMat4 rotY = PVRTMat4::RotationY(ry);
   PVRTMat4 rotZ = PVRTMat4::RotationZ(rz);

   PVRTMat4 rotZY = rotZ*rotY;
   PVRTMat4 rotZYX = rotZY*rotX;

   cameraPara.mat.ex_all_inv = transMat*rotZYX;

//   float* ptr= cameraPara.mat.ex_all_inv.ptr();
//   printf("exInvMat:\n");
//   for(int i=0;i<16;i++)
//   {
//	   printf("%f\n",ptr[i]);
//   }
}

void LCamera::setIntrinsicMatrix()
{
	PVRTMat4* pMat = &cameraPara.mat.intrin;
	*pMat = PVRTMat4::Identity();
	f32_t* pData = pMat->ptr();
	pData[0] = cameraPara.intrinsic.fx;
	pData[5] = cameraPara.intrinsic.fy;
	pData[8] = cameraPara.intrinsic.cx;
	pData[9] = cameraPara.intrinsic.cy;

//	   float* ptr= cameraPara.mat.intrin.ptr();
//	   printf("inMat:\n");
//	   for(int i=0;i<16;i++)
//	   {
//		   printf("%f\n",ptr[i]);
//	   }
}

void LCamera::setProjectionMatrix()
{
	PVRTMat4 tmpMat = PVRTMat4::Identity();
	float* tmpPtr = tmpMat.ptr();
	tmpPtr[0] = -1.0;

	cameraPara.mat.projection = cameraPara.mat.intrin*tmpMat*cameraPara.mat.ex_all;
}

void LCamera::cam2Pixel(const f32_t x, const f32_t y, const f32_t z,f32_t &u, f32_t &v)
{
	f32_t k1 = cameraPara.intrinsic.k1;
	f32_t k2 = cameraPara.intrinsic.k2;

	f32_t x1 = -x/z;
	f32_t y1 = y/z;

	f32_t r2 = x1 * x1 + y1 * y1;
	f32_t r4 = r2 * r2;
	f32_t scale = 1.0 +  k1 * r2 +  k2 * r4;

	f32_t x2 = x1 * scale;
	f32_t y2 = y1 * scale;

	u = cameraPara.intrinsic.fx * x2 + cameraPara.intrinsic.cx;
	v = cameraPara.intrinsic.fy * y2 + cameraPara.intrinsic.cy;
}

void LCamera::world2Cam(const f32_t x, const f32_t y, const f32_t z, f32_t &xCam, f32_t &yCam, f32_t &zCam)
{
	PVRTVec4 inVec(x,y,z,1.0);
	PVRTVec4 outVec = cameraPara.mat.ex_all*inVec;
	f32_t* pOut = outVec.ptr();
	xCam = pOut[0];
	yCam = pOut[1];
	zCam = pOut[2];
}

void LCamera::world2Pixel(const f32_t x, const f32_t y, const f32_t z, f32_t &u, f32_t &v)
{
	f32_t xCam,yCam,zCam;
	world2Cam(x,y,z,xCam,yCam,zCam);
	cam2Pixel(xCam,yCam,zCam,u,v);
//	printf("x=%f,y=%f,z=%f,xCam=%f,yCam=%f,zCam=%f,u=%f,v=%f\n",x,y,z,xCam,yCam,zCam,u,v);
}

void LCamera::cam2Pixel_noDistort(const f32_t x, const f32_t y, const f32_t z,f32_t &u, f32_t &v)
{
	f32_t x1 = -x/z;
	f32_t y1 = y/z;

	u = cameraPara.intrinsic.fx * x1 + cameraPara.intrinsic.cx;
	v = cameraPara.intrinsic.fy * y1 + cameraPara.intrinsic.cy;
}

void LCamera::world2Pixel_noDistort(const f32_t x, const f32_t y, const f32_t z, f32_t &u, f32_t &v)
{
	f32_t xCam,yCam,zCam;
	world2Cam(x,y,z,xCam,yCam,zCam);
	cam2Pixel_noDistort(xCam,yCam,zCam,u,v);
}

void LCamera::pixel2Cam(const f32_t u, const f32_t v, f32_t& xCam, f32_t& yCam, f32_t& zCam)
{
	f32_t x1 = (u - cameraPara.intrinsic.cx)/cameraPara.intrinsic.fx;
   f32_t y1 = (v - cameraPara.intrinsic.cy)/cameraPara.intrinsic.fy;

   f32_t y2 = y1;
   f32_t x2 = -x1;
   f32_t z2 = 1.0;

   f32_t length = sqrt(x2*x2 + y2*y2 + z2*z2);

   xCam = x2/length;
   yCam = y2/length;
   zCam = z2/length;
}

void LCamera::cam2WorldZ(const f32_t& xCam, const f32_t& yCam, const f32_t& zCam, const f32_t& z,f32_t& xWorld, f32_t& yWorld)
{
	PVRTVec4 inVec(xCam,yCam,zCam,0.0);
	PVRTVec4 outVec = cameraPara.mat.ex_all_inv*inVec;

	f32_t* pData = outVec.ptr();
	f32_t x1 = pData[0];
	f32_t y1 = pData[1];
	f32_t z1 = pData[2];

	f32_t startX = cameraPara.extrinsic.tx;
	f32_t startY = cameraPara.extrinsic.ty;
	f32_t startZ = cameraPara.extrinsic.tz;

	f32_t delta = (z - startZ)/z1;
	xWorld = startX + delta * x1;
	yWorld = startY + delta * y1;
}

void LCamera::pixel2WorldZ(const f32_t u, const f32_t v, const f32_t z, f32_t& xWorld, f32_t& yWorld)
{
	f32_t xCam,yCam,zCam;
	pixel2Cam(u, v, xCam, yCam, zCam);
	cam2WorldZ(xCam, yCam, zCam, z,xWorld, yWorld);
}

//PVRTMat4& LCamera::getCamExtrinMat()
//{
//	return cameraPara.mat.ex_all;
//}

//PVRTMat4& LCamera::getCamIntrinMat()
//{
//	return cameraPara.mat.intrin;
//}

//PVRTMat4& LCamera::getCamProjMat()
//{
//	return cameraPara.mat.projection;
//}

//PVRTMat4 LCamera::getCamExtrinMatTranspose()
//{
//	return m_ExtrinMatTranspose;
//}

//PVRTMat4 LCamera::getCamProjMatTranspose()
//{
//	return m_ProjMatTranspose;
//}

void LCamera::OutputCamMatTranspose(const char* filename)
{
	f32_t* pCamPtr=NULL;
	FILE* pFile;

	pFile = fopen(filename,"w");
	if(!pFile)
		return;

	pCamPtr = m_ProjMatTranspose.ptr();
	fprintf(pFile,"projTransMat:\n");
	for(int i=0;i<4;i++)
	{
		fprintf(pFile,"\t  %f\t %f\t %f\t %f\t\n",pCamPtr[i],pCamPtr[4+i],pCamPtr[8+i],pCamPtr[12+i]);
	}
	fprintf(pFile,"\n");

	pCamPtr = m_ExtrinMatTranspose.ptr();
	fprintf(pFile,"extrinTransMat:\n");
	for(int i=0;i<4;i++)
	{
		fprintf(pFile,"\t  %f\t %f\t %f\t %f\t\n",pCamPtr[i],pCamPtr[4+i],pCamPtr[8+i],pCamPtr[12+i]);
	}
	fprintf(pFile,"\n");

	fclose(pFile);
}

void LCamera::OutputCamMat(const char* filename)
{
	f32_t* pCamPtr=NULL;
	FILE* pFile;

	pFile = fopen(filename,"w");
	if(!pFile)
		return;

	pCamPtr = cameraPara.mat.projection.ptr();
	fprintf(pFile,"projMat:\n");
	for(int i=0;i<4;i++)
	{
		fprintf(pFile,"\t  %f\t %f\t %f\t %f\t\n",pCamPtr[i],pCamPtr[4+i],pCamPtr[8+i],pCamPtr[12+i]);
	}
	fprintf(pFile,"\n");

	pCamPtr = cameraPara.mat.ex_all.ptr();
	fprintf(pFile,"extrinMat:\n");
	for(int i=0;i<4;i++)
	{
		fprintf(pFile,"\t  %f\t %f\t %f\t %f\t\n",pCamPtr[i],pCamPtr[4+i],pCamPtr[8+i],pCamPtr[12+i]);
	}
	fprintf(pFile,"\n");

	fclose(pFile);
}

void LCamera::OutputExtrinMat(const char* filename)
{

	f32_t tx = -cameraPara.extrinsic.tx;
	f32_t ty = -cameraPara.extrinsic.ty;
	f32_t tz = -cameraPara.extrinsic.tz;

	PVRTMat4 transMat = PVRTMat4::Translation(tx,ty,tz);

   f32_t rx = -R_Deg2Rad(cameraPara.extrinsic.rx);
   f32_t ry = -R_Deg2Rad(cameraPara.extrinsic.ry);
   f32_t rz = -R_Deg2Rad(cameraPara.extrinsic.rz);

   PVRTMat4 rotX =PVRTMat4::RotationX(rx);
   PVRTMat4 rotY = PVRTMat4::RotationY(ry);
   PVRTMat4 rotZ = PVRTMat4::RotationZ(rz);

   PVRTMat4 rotYZ = rotY*rotZ;
   PVRTMat4 rotXYZ = rotX*rotYZ;

   	f32_t* pCamPtr=NULL;
	FILE* pFile;

	pFile = fopen(filename,"w");
	if(!pFile)
		return;

	pCamPtr = cameraPara.mat.ex_all.ptr();
	fprintf(pFile,"extrinMatAll: \n");
	for(int i=0;i<4;i++)
	{
		fprintf(pFile,"\t  %f\t %f\t %f\t %f\t\n",pCamPtr[i],pCamPtr[4+i],pCamPtr[8+i],pCamPtr[12+i]);
	}
	fprintf(pFile,"\n");

	pCamPtr = transMat.ptr();
	fprintf(pFile,"transMat:\n");
	for(int i=0;i<4;i++)
	{
		fprintf(pFile,"\t  %f\t %f\t %f\t %f\t\n",pCamPtr[i],pCamPtr[4+i],pCamPtr[8+i],pCamPtr[12+i]);
	}
	fprintf(pFile,"\n");

	pCamPtr = rotXYZ.ptr();
	fprintf(pFile,"rotMat:\n");
	for(int i=0;i<4;i++)
	{
		fprintf(pFile,"\t  %f\t %f\t %f\t %f\t\n",pCamPtr[i],pCamPtr[4+i],pCamPtr[8+i],pCamPtr[12+i]);
	}
	fprintf(pFile,"\n");

	fclose(pFile);
}

FrequencyCntl::FrequencyCntl()
{
//	m_ulStartTime = 0;
//	m_ulCurTime = 0;
	m_ulDeltaTime = 0;
	m_ulFrequency = 0;
	m_ulDuration = 0;
}

FrequencyCntl::FrequencyCntl(unsigned long freq,unsigned long duration)
{
//	m_ulStartTime = 0;
//	m_ulCurTime = 0;
	m_ulDeltaTime = 0;
	m_ulFrequency = freq;
	m_ulDuration = duration*1000;
	if(freq)
		m_fIntervalDur = 500.0/freq;
	else
		m_fIntervalDur = 0;

	m_bOverTime = false;

}

FrequencyCntl::~FrequencyCntl()
{
	;
}

void FrequencyCntl::SetParam(unsigned long freq,unsigned long duration)
{
	clock_gettime(CLOCK_REALTIME, &m_startTime);
	m_curTime = m_startTime;
	m_ulDeltaTime = 0;
	m_ulFrequency = freq;
	m_ulDuration = duration*1000;
	if(freq)
		m_fIntervalDur = 500.0/freq;
	else
		m_fIntervalDur = 0.0;
	m_bOverTime = false;
}

//unsigned long FrequencyCntl::GetTime()
//{
//	struct timespec rt;
//    clock_gettime(CLOCK_REALTIME, &rt);
//    return rt.tv_sec * 1000 + rt.tv_nsec/1000000;
//}

void FrequencyCntl::Reset()
{
	clock_gettime(CLOCK_REALTIME, &m_startTime);
	m_curTime = m_startTime;
	m_ulDeltaTime = 0;
	m_bOverTime = false;
}

void FrequencyCntl::CurTimeElapse()
{
	clock_gettime(CLOCK_REALTIME, &m_curTime);
	m_ulDeltaTime = (m_curTime.tv_sec - m_startTime.tv_sec)*1000+
			(m_curTime.tv_nsec - m_startTime.tv_nsec)/1000000;
}

bool FrequencyCntl::Overtime()
{
	if(0 == m_ulFrequency)
		return true;
	if(0 == m_ulDuration)
		return false;

	if(m_bOverTime)
		return true;
	else
	{
		CurTimeElapse();
		if(m_ulDeltaTime>m_ulDuration)
			m_bOverTime = true;
		return m_bOverTime;
	}
}

int FrequencyCntl::IntervalIndex()
{
	CurTimeElapse();
	unsigned long res = m_ulDeltaTime%1000;
	int index = res/m_fIntervalDur;
	//always flash
	if(m_ulDuration==0&&m_ulDeltaTime>MAXDELTATIME)
	{
		m_startTime = m_curTime;
		m_startTime.tv_nsec -= res*1000;
	}
	return index;
}

bool FrequencyCntl::OddInterval()
{
	int index = IntervalIndex();
	if(index%2)
		return true;
	else
		return false;
}

bool FrequencyCntl::EvenInterval()
{
	int index = IntervalIndex();
	if(index%2)
		return false;
	else
		return true;
}

