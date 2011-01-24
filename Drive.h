/*
 *	Drive.h
 *	Nashoba Robotics 2011
 */

#pragma once

#include "WPILib.h"

class MotorPair
{
public:
/*	MotorPair( Jaguar fr, Jaguar rr )
	:	front( fr ), rear( rr )
#ifdef NR_CLOSED_LOOP_CONTROL
		,frontPID( kPIDProportional, kPIDIntegral, kPIDDifferential, front, front ),
		rearPID( kPIDProportional, kPIDIntegral, kPIDDifferential, rear, rear )
#endif
	{
	}
	*/
	
	MotorPair( UINT8 fr, UINT8 rr, UINT8 enc1, UINT8 enc2, CANJaguar::ControlMode controlMode )
	:	front( 4, fr ),
		rear( 4, rr ),
		encoder( 4, enc1, 4, enc2 )
#ifdef NR_CLOSED_LOOP_CONTROL
		,frontPID( kPIDProportional, kPIDIntegral, kPIDDifferential, front, front ),
		rearPID( kPIDProportional, kPIDIntegral, kPIDDifferential, rear, rear )
#endif
	{
		reverse = false;
	}
	
	void Set( float value )
	{
#ifdef NR_CLOSED_LOOP_CONTROL
		frontPID.Set( (reverse ? -1 : 1) * value );
		rearPID.Set(  (reverse ? -1 : 1) * value );
#else
		front.Set( (reverse ? -1 : 1) * value );
		rear.Set(  (reverse ? -1 : 1) * value );
#endif
	}
	
	bool reverse;
	Jaguar front, rear;
	
	Encoder encoder;
	
private:
#ifdef NR_CLOSED_LOOP_CONTROL
	PIDController frontPID, rearPID;
#endif
};

class Drive
{
public:
	/*
	Drive( Jaguar frontLeftMotor,
		   Jaguar rearLeftMotor,
		   Jaguar frontRightMotor,
		   Jaguar rearRightMotor );
		   */
	
	Drive( UINT8 frontLeftMotor, UINT8 rearLeftMotor,
		   UINT8 frontRightMotor, UINT8 rearRightMotor,
		   UINT8 leftEncoder1, UINT8 leftEncoder2,
		   UINT8 rightEncoder1, UINT8 rightEncoder2,
		   CANJaguar::ControlMode controlMode = CANJaguar::kPercentVbus );
	
	void TankDrive( float left, float right );
	
private:
	MotorPair leftMotors;
	MotorPair rightMotors;
	
	void InitializeDiagnostics();
};
