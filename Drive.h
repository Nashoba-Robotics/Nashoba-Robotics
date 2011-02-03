/*
 *	Drive.h
 *	Nashoba Robotics 2011
 */

#pragma once

#include "WPILib.h"
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
		front.SetSafetyEnabled( false );
		rear.SetSafetyEnabled( false );
		reversed = false;
	}
	
	MotorPair( UINT8 fr, UINT8 rr, CANJaguar::ControlMode controlMode )
	:	front( fr, controlMode ),
		rear( rr, controlMode )
#ifdef NR_CLOSED_LOOP_CONTROL
		,frontPID( kPIDProportional, kPIDIntegral, kPIDDifferential, front, front ),
		rearPID( kPIDProportional, kPIDIntegral, kPIDDifferential, rear, rear )
#endif
	{
		front.SetSafetyEnabled( false );
		rear.SetSafetyEnabled( false );
		reversed = false;
	}
	
	void Set( float value )
	{
#ifdef NR_CLOSED_LOOP_CONTROL
		frontPID.Set( value );
		rearPID.Set( value );
#else
		front.Set( value * (reversed ? -1 : 1) );
		rear.Set(  value * (reversed ? -1 : 1) );
#endif
	}
	
	CANJaguar front, rear;

	bool reversed;
	
private:
#ifdef NR_CLOSED_LOOP_CONTROL
	PIDController frontPID, rearPID;
#endif
};

class Drive
{
public:
	Drive( CANJaguar frontRightMotor,
		   CANJaguar rearRightMotor,
		   CANJaguar frontLeftMotor,
		   CANJaguar rearLeftMotor,
		   Encoder leftEncoder,
		   Encoder rightEncoder );
	
	Drive( UINT8 frontRightMotor,
				    UINT8 rearRightMotor,
				    UINT8 frontLeftMotor,
				    UINT8 rearLeftMotor,
				    UINT8 encoderLeftSlot1, UINT8 encoderLeftChannel1,
				    UINT8 encoderLeftSlot2, UINT8 encoderLeftChannel2,
				    UINT8 encoderRightSlot1, UINT8 encoderRightChannel1,
				    UINT8 encoderRightSlot2, UINT8 encoderRightChannel2,
				    CANJaguar::ControlMode controlMode = CANJaguar::kPercentVbus );
	
	void TankDrive( float left, float right );
	
private:
	MotorPair leftMotors;
	MotorPair rightMotors;
	
	Encoder encoderLeft;
	Encoder encoderRight;
	
	void InitializeDiagnostics();
};
