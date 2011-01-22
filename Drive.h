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
	{
	}
	
	MotorPair( UINT8 fr, UINT8 rr, CANJaguar::ControlMode controlMode )
	:	front( fr, controlMode ),
		rear( rr, controlMode )
	{
	}
	
	void Set( float value )
	{
		front.Set( value );
		rear.Set(  value );
	}
	
	CANJaguar front, rear;
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
