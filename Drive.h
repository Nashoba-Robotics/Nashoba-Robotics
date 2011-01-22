/*
 *	Drive.h
 *	Nashoba Robotics 2011
 */

#pragma once

#include "CANJaguar.h"

class MotorPair
{
public:
	MotorPair( CANJaguar fr, CANJaguar rr )
	:	front( fr ), rear( rr )
#ifdef NR_CLOSED_LOOP_CONTROL
		,frontPID( kPIDProportional, kPIDIntegral, kPIDDifferential, front, front ),
		rearPID( kPIDProportional, kPIDIntegral, kPIDDifferential, rear, rear )
#endif
	{
	}
	
	MotorPair( UINT8 fr, UINT8 rr, CANJaguar::ControlMode controlMode )
	:	front( fr, controlMode ),
		rear( rr, controlMode )
#ifdef NR_CLOSED_LOOP_CONTROL
		,frontPID( kPIDProportional, kPIDIntegral, kPIDDifferential, front, front ),
		rearPID( kPIDProportional, kPIDIntegral, kPIDDifferential, rear, rear )
#endif
	{
	}
	
	void Set( float value )
	{
#ifdef NR_CLOSED_LOOP_CONTROL
		frontPID.Set( value );
		rearPID.Set( value );
#else
		front.Set( value );
		rear.Set(  value );
#endif
	}
	
	CANJaguar front, rear;
	
private:
#ifdef NR_CLOSED_LOOP_CONTROL
	PIDController frontPID, rearPID;
#endif
};

class Drive
{
public:
	Drive( CANJaguar frontLeftMotor,
		   CANJaguar rearLeftMotor,
		   CANJaguar frontRightMotor,
		   CANJaguar rearRightMotor );
	
	Drive( UINT8 frontLeftMotor, UINT8 rearLeftMotor, UINT8 frontRightMotor, UINT8 rearRightMotor, CANJaguar::ControlMode controlMode = CANJaguar::kPercentVbus );
	
	void TankDrive( float left, float right );
	
private:
	MotorPair leftMotors;
	MotorPair rightMotors;
	
	void InitializeDiagnostics();
};
