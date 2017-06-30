/*
 * trajectory_GM.cpp
 *
 *  Created on: 2012-5-7
 *      Author: QiLiu
 */

#include "trajectory.h"
#define STEER_WHEEL_ANGLE_PRECISION 0.01

trajectory::trajectory()
{
	vehicle.wheelBase = 2.946;//l
	vehicle.rearAxleOffset = 1.21;
//	vehicle.steeringAngle = 0.0f;//in rad,
	vehicle.maxSteeringAngle = 560.0f;
	vehicle.inverseFrontRatio = 0.0582*R_PI/180.0f;//wheel rotate Angle/steering wheel rotate angle
	vehicle.inverseRearRatio = 0.0f;
	m_bTurnRadiusSmall = false;

	SetVehicleSteeringAngle(0);
}

trajectory::~trajectory()
{
	;
}

void trajectory::Init(rvs_steer_params& param)
{
	vehicle.wheelBase = param.wheelBase;
	vehicle.rearAxleOffset = param.rearAxleOffset;
	vehicle.maxSteeringAngle = param.saturationAngle;
	vehicle.inverseFrontRatio = param.invFrontRatio*R_PI/180.0f;
	vehicle.inverseRearRatio = param.invRearRatio*R_PI/180.0f;
	m_fHalfTrackWidth = param.trackWidth/2;
	m_bTurnRadiusSmall = false;
	SetVehicleSteeringAngle(0);
}

void trajectory::UpdateTrackWidth(f32_t width)
{
	m_fHalfTrackWidth = width * 0.5;
	CalTrajectoryParam();
}

void trajectory::SetVehicleSteeringAngle(f32_t Deg)
{
	if(Deg>vehicle.maxSteeringAngle)
		m_fSteerWheelAngle = vehicle.maxSteeringAngle;
	else if(Deg<-vehicle.maxSteeringAngle)
		m_fSteerWheelAngle = -vehicle.maxSteeringAngle;
	else
		m_fSteerWheelAngle = Deg;

//	printf("m_fSteerWheelAngle = %f\n",m_fSteerWheelAngle);
	m_fFrontWheelAngle = vehicle.inverseFrontRatio * m_fSteerWheelAngle;
	m_fRearWheelAngle = vehicle.inverseRearRatio * m_fSteerWheelAngle;
	CalTrajectoryParam();
}

void trajectory::CalTrajectoryParam()
{
//	printf("m_fSteerWheelAngle = %f\n",m_fSteerWheelAngle);
//	if(0 == m_fSteerWheelAngle)
	if(fabs(m_fSteerWheelAngle)<STEER_WHEEL_ANGLE_PRECISION)
	{
		m_fTurningCenterX = 99999999.0;
		m_fTurningCenterY = 0.0;
	}
	else
	{
		f32_t tmpCenter;
		if(fabs(vehicle.inverseRearRatio)<INVERSE_REAR_RATIO_PRECISION)
		{
			tmpCenter = vehicle.wheelBase/tan(m_fFrontWheelAngle);
			m_fTurningCenterX = tmpCenter;
			m_fTurningCenterY = 0.0;

		}
		else
		{
			tmpCenter = vehicle.wheelBase*cos(m_fFrontWheelAngle)/sin(m_fFrontWheelAngle+m_fRearWheelAngle);
			m_fTurningCenterX = tmpCenter*cos(m_fRearWheelAngle);
			m_fTurningCenterY = tmpCenter*sin(m_fRearWheelAngle);
		}
	}
//	printf("turningCenterx = %f,turningCentery = %f\n",m_fTurningCenterX,m_fTurningCenterY);

	m_fTurningTotalY = m_fTurningCenterY - vehicle.rearAxleOffset;
	m_fInvRadius = 1.0/sqrt((m_fTurningCenterX*m_fTurningCenterX)+(m_fTurningTotalY*m_fTurningTotalY));
	if(m_fInvRadius>10.0)
	{
		m_bTurnRadiusSmall = true;
		printf("radius is too small(less than 0.1 meter);\n");
		return;
	}

	m_fLeftStartX = -m_fHalfTrackWidth - m_fTurningCenterX;
	m_fLeftStartY = -m_fTurningTotalY;
	m_fRightStartX = m_fHalfTrackWidth - m_fTurningCenterX;
	m_fRightStartY = -m_fTurningTotalY;
//	printf("leftstartx = %f,leftstarty = %f,rightstartx = %f,rightstarty = %f\n",m_fLeftStartX,m_fLeftStartY,
//			m_fRightStartX,m_fRightStartY);
}

void trajectory::GetLeftPosition(f32_t rad,f32_t& outx,f32_t& outy)
{
	f32_t cosTheta = cos(rad);
	f32_t sinTheta = sin(rad);
	outx = cosTheta * m_fLeftStartX + sinTheta * m_fLeftStartY + m_fTurningCenterX;
	outy = -sinTheta * m_fLeftStartX + cosTheta * m_fLeftStartY + m_fTurningTotalY;
}

void trajectory::GetRightPosition(f32_t rad,f32_t& outx,f32_t& outy)
{
	f32_t cosTheta = cos(rad);
	f32_t sinTheta = sin(rad);
	outx = cosTheta * m_fRightStartX + sinTheta * m_fRightStartY + m_fTurningCenterX;
	outy = -sinTheta * m_fRightStartX + cosTheta * m_fRightStartY + m_fTurningTotalY;
}

void trajectory::GetLeftPosition(f32_t rad,f32_t* out)
{
	GetLeftPosition(rad,out[0],out[1]);
}

void trajectory::GetRightPosition(f32_t rad,f32_t* out)
{
	GetRightPosition(rad,out[0],out[1]);
}


