#ifndef __LCOMMON_H__
#define __LCOMMON_H__

#include "Rosal.h"
#include "PVRTVector.h"
#include "time.h"
#include "RVSDefine.h"

/************************************************************************/
/*                  Camera Based Parameters    -  Begin                 */
/************************************************************************/
typedef struct camera_intrinsic {
   f32_t          fx;           /**< focal length in x */
   f32_t          fy;           /**< focal length in y */
   f32_t          cx;           /**< offset of principle point in x */
   f32_t          cy;           /**< offset of principle point in y */
   f32_t          k1;           /**< radial distortion parameter */
   f32_t          k2;           /**< radial distortion parameter */
   //f32_t          k3;           /**< radial distortion parameter */
   //f32_t          k4;           /**< radial distortion parameter */
   //f32_t          k5;           /**< radial distortion parameter */
   //f32_t          p1;           /**< tangential distortion */
   //f32_t          p2;           /**< tangential distortion */
   //f32_t          asp;          /**< aspect ratio */
}camera_intrinsic_t;

typedef struct camera_extrinsic {
   f32_t          tx;           /**< translation - x */
   f32_t          ty;           /**< translation - y */
   f32_t          tz;           /**< translation - z */
   f32_t          rx;           /**<  rotation - x  */ 
   f32_t          ry;           /**<  rotation - y  */
   f32_t          rz;           /**<  rotation - z  */
}camera_extrinsic_t;

//typedef struct camera
//{
//   camera_intrinsic_t intrinsic;
//   camera_extrinsic_t extrinsic;
//}camera_t;


typedef struct camera_matrix
{
   /**< intrinsic matrix, 4*4
   | fx 0 cx 0|
   | 0 fy cy 0|
   | 0  0  1 0|
   | 0  0  0 1|
   */
   PVRTMat4          intrin;
   ///**< extrinsic matrix - translation 4x4 
   //| 1 0 0 tx |
   //| 0 1 0 ty |
   //| 0 0 1 tz |
   //| 0 0 0  1 | 
   //*/
   //PVRTMat4          ex_trans;
   ///**< extrinsic matrix - rotation 4x4
   //*  ex_rotx * ex_roty * ex_rotz;
   //*/
   //PVRTMat4          ex_rot;  /**< extrinsic matrix - rotation    4x4 */

   /**< extrinsic matrix - rotation * translation, 4x4 */
   PVRTMat4          ex_all;

   PVRTMat4          ex_all_inv;

   /**< projection matrix: intrin * ex_all(1:3,:), 3x4 */
   PVRTMat4          projection;

}camera_matrix_t;

typedef struct camera_para
{
   camera_intrinsic_t intrinsic;
   camera_extrinsic_t extrinsic;
   camera_matrix_t    mat;
}cameraPara_t;
#if 1
const camera_intrinsic_t CAM_INTRINSIC_GM = {
   0.4728*1,  //fx;
   0.6304*1,  //fy;
   0.5*1,  //cx;
   (0.5-0.154)*1,  //cy;
   -0.27,    //k1;
   0.05,    //k2;
   //0.0,         //k3;
   //0.0,         //k4;
   //0.0,         //k5;
   //0.0,    //p1;
   //-0.0,    //p2;
   //1.33         //asp;
};

const camera_extrinsic_t CAM_EXTRINSIC_GM = {
	0.0,
	0.1,
	1.3,
	118.0,
	0.0,
	0.0,
};

#else
const camera_intrinsic_t CAM_INTRINSIC_GM = {
   0.31207*1,  //fx;1.11847mm*1000/5.6/640
   0.41609*1,  //fy;1.11847mm*1000/5.6/480
   0.5*1,  //cx;  center
   0.5*1,  //cy;  center
   -0.047394,    //k1;
    0.001080,    //k2;
   //0.0,         //k3;
   //0.0,         //k4;
   //0.0,         //k5;
   //0.0,    //p1;
   //-0.0,    //p2;
   //1.33         //asp;
};
#define PI 3.1415926
#define HALF_PI (PI/2)
#define Deg2Rad(x) (x*PI/180.0)
const camera_extrinsic_t CAM_EXTRINSIC_GM = {
	0.0,   //48.894
	0,//
	1.5,
	130,//36.3
	0.0,
	0.0,
};
#endif

const camera_extrinsic_t CAM_EXTRINSIC_GL8 = {
	-0.0,
	0.0,
	0.875,
	120.0,
	0.0,
	0.0
};

const camera_intrinsic_t CAM_ALPINE_C100 = {
   212.014233/720.0,  //fx;
   255.477769/480.0,  //fy;
   357.389014/720.0,  //cx;
   244.679096/480.0,  //cy;
   -0.074558,    //k1;
   0.003298,    //k2;
};
/************************************************************************/
/*                  Camera Based Parameters    -  End                   */
/************************************************************************/


class LCamera
{

public:
   LCamera(void);
   ~LCamera(void);
//   void init();
   void init(cameraPara_t param);
   void init(rvs_camera_params param);

   void setCameraMatrix();
   void setExtrinsicMatrix();
   void setIntrinsicMatrix();
   void setProjectionMatrix();
   void setInvExtrinsicMatrix();

   PVRTMat4& getCamExtrinMat() {return cameraPara.mat.ex_all;}
   PVRTMat4& getCamIntrinMat(){return cameraPara.mat.intrin;}
   PVRTMat4& getCamProjMat(){return cameraPara.mat.projection;}

   PVRTMat4 getCamExtrinMatTranspose(){return m_ExtrinMatTranspose;}
   PVRTMat4 getCamProjMatTranspose(){return m_ProjMatTranspose;}


   f32_t getCamTx(){ return cameraPara.extrinsic.tx;}
   f32_t getCamTy(){ return cameraPara.extrinsic.ty;}
   f32_t getCamTz(){ return cameraPara.extrinsic.tz;}
   f32_t getCamRx(){ return cameraPara.extrinsic.rx;}
   f32_t getCamRy(){ return cameraPara.extrinsic.ry;}
   f32_t getCamRz(){ return cameraPara.extrinsic.rz;}

   f32_t getCamFx(){ return cameraPara.intrinsic.fx;}
   f32_t getCamFy(){ return cameraPara.intrinsic.fy;}
   f32_t getCamCx(){ return cameraPara.intrinsic.cx;}
   f32_t getCamCy(){ return cameraPara.intrinsic.cy;}
   f32_t getCamK1(){ return cameraPara.intrinsic.k1;}
   f32_t getCamK2(){ return cameraPara.intrinsic.k2;}

   void setCamRx(f32_t rx){cameraPara.extrinsic.rx = rx;}
   void setCamRy(f32_t ry){cameraPara.extrinsic.ry = ry;}
   void setCamRz(f32_t rz){cameraPara.extrinsic.rz = rz;}
   void setCamTx(f32_t tx){cameraPara.extrinsic.tx = tx;}
   void setCamTy(f32_t ty){cameraPara.extrinsic.ty = ty;}
   void setCamTz(f32_t tz){cameraPara.extrinsic.tz = tz;}

   void setCamFx(f32_t fx){cameraPara.intrinsic.fx = fx;}
   void setCamFy(f32_t fy){cameraPara.intrinsic.fy = fy;}
   void setCamCx(f32_t cx){cameraPara.intrinsic.cx = cx;}
   void setCamCy(f32_t cy){cameraPara.intrinsic.cy = cy;}
   void setCamK1(f32_t k1){cameraPara.intrinsic.k1 = k1;}
   void setCamK2(f32_t k2){cameraPara.intrinsic.k2 = k2;}

   void cam2Pixel(const f32_t x, const f32_t y, const f32_t z,f32_t &u, f32_t &v);
   void world2Cam(const f32_t x, const f32_t y, const f32_t z, f32_t &xCam, f32_t &yCam, f32_t &zCam);
   void world2Pixel(const f32_t x, const f32_t y, const f32_t z, f32_t &u, f32_t &v);

   void cam2Pixel_noDistort(const f32_t x, const f32_t y, const f32_t z,f32_t &u, f32_t &v);
   void world2Pixel_noDistort(const f32_t x, const f32_t y, const f32_t z, f32_t &u, f32_t &v);

   void pixel2Cam(const f32_t u, const f32_t v, f32_t& xCam, f32_t& yCam, f32_t& zCam);
   void cam2WorldZ(const f32_t& xCam, const f32_t& yCam, const f32_t& zCam, const f32_t& z,f32_t& xWorld, f32_t& yWorld);
   void pixel2WorldZ(const f32_t u, const f32_t v, const f32_t z, f32_t& xWorld, f32_t& yWorld);

   //for test
   void OutputCamMatTranspose(const char* filename);
   void OutputCamMat(const char* filename);
   void OutputExtrinMat(const char* filename);

private:
   cameraPara_t cameraPara;

   //mat for shader input;
   PVRTMat4 m_ProjMatTranspose;
   PVRTMat4 m_ExtrinMatTranspose;
};

/************************************************************************/
/*               L   Camera Based Functions     -  End                   */
/************************************************************************/

/************************************************************************/
/*               Time count Based Functions     -  begin                   */
/************************************************************************/

/*
 * FrequencyCntl: used for graphic flash control,calculated by ms.
 * m_ulFrequency: flash frequency,integer,if 0, no flash
 * m_ulDuration:  flash duration time, if 0, always flashing
 */
class FrequencyCntl
{
public:
	FrequencyCntl();
	/*
	 * duration: seconds
	 */
	FrequencyCntl(unsigned long freq,unsigned long duration=0);
	~FrequencyCntl();

	void SetParam(unsigned long freq,unsigned long duration=0);
	/*
	 * reset the startTime, stat. again
	 */
	void Reset();
	bool Overtime();
	bool OddInterval();
	bool EvenInterval();

private:
//    unsigned long GetTime();
    int IntervalIndex();
    void CurTimeElapse();
private:
//	unsigned long m_ulStartTime;
//	unsigned long m_ulCurTime;
   //tbd struct timespec m_startTime;
   //tbd struct timespec m_curTime;
int m_startTime;
int m_curTime;
	unsigned long m_ulDeltaTime;

	unsigned long m_ulFrequency;
	unsigned long m_ulDuration;
	float m_fIntervalDur;
	bool m_bOverTime;

	//prevent overflow;
#define MAXDELTATIME 8000
//#define MAXDELTATIME 24*3600*1000

};

/************************************************************************/
/*               Time count Based Functions     -  end                   */
/************************************************************************/
#endif
