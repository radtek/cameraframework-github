/*
 * trajectory_GM.h
 *
 *  Created on: 2012-5-7
 *      Author: QiLiu
 */

#ifndef TRAJECTORY_H_
#define TRAJECTORY_H_
#include "Rosal.h"
#include <stdio.h>
#include "RVSDefine.h"


typedef struct GMVehicleInfo
{
	f32_t wheelBase;//l
	f32_t rearAxleOffset;
//	int steeringAngle;//in rad,
	f32_t maxSteeringAngle; //in degree
	f32_t inverseFrontRatio;//wheel rotate Angle/steering wheel rotate angle
	f32_t inverseRearRatio;
}GMVehicleInfo_t;

#define ANGLE_PRECISION 0.01
#define INVERSE_REAR_RATIO_PRECISION 0.001

class trajectory{
public:
	trajectory();
	~trajectory();

	void Init(rvs_steer_params& param);

public:
	void GetLeftPosition(f32_t rad,f32_t& outx,f32_t& outy);
	void GetRightPosition(f32_t rad,f32_t& outx,f32_t& outy);

	void GetLeftPosition(f32_t rad,f32_t* out);
	void GetRightPosition(f32_t rad,f32_t* out);

	void SetVehicleSteeringAngle(f32_t Deg);
	f32_t GetVehicleSteerWheelAngle() { return m_fSteerWheelAngle;}
	f32_t GetVehicleRearAxleOffset() { return vehicle.rearAxleOffset;}

	bool IsTurningRadiusSmall(){ return m_bTurnRadiusSmall;}
	f32_t GetInvRadius(){ return m_fInvRadius;}
	f32_t GetTurnCenterX(){ return m_fTurningCenterX;}
	void SetTrackWidth(f32_t width){ m_fHalfTrackWidth = width * 0.5;}

	void UpdateTrackWidth(f32_t width);

private:
	void CalTrajectoryParam();

private:
	GMVehicleInfo_t vehicle;

	f32_t m_fFrontWheelAngle;
	f32_t m_fRearWheelAngle;
//	int m_iSteerWheelAngle;
	f32_t m_fSteerWheelAngle;  //in degree
//	f32_t m_fTrackWidth;

	f32_t m_fLeftStartX;
	f32_t m_fLeftStartY;
	f32_t m_fRightStartX;
	f32_t m_fRightStartY;
	f32_t m_fTurningCenterX;
	f32_t m_fTurningCenterY;
	f32_t m_fTurningTotalY;

//	f32_t m_fRadius;
	bool m_bTurnRadiusSmall;
	f32_t m_fHalfTrackWidth;

	f32_t m_fInvRadius;


};
#endif /* TRAJECTORY_H_ */
