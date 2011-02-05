/*
 *	Drive.h
 *	Nashoba Robotics 2011
 */

#pragma once

#include "WPILib.h"
#include "CANJaguar.h"

/**
 *	A pair of motors, which can be conveniently set together
 */
class MotorPair
{
public:
	/**
	 *	@brief Creates the motor pair with the given motors
	 *	@param fr The "front" motor
	 *	@param rr The "rear" motor
	 */
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
	
	/**
	 *	@brief Creates the motor pair with the given motors
	 *	@param fr The "front" motor CAN number
	 *	@param rr The "rear" motor CAN number
	 *	@param controlMode The CAN control mode to use
	 */
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
	
	/**
	 *	Sets the motor pair
	 *	@param value The value to set both motors to
	 */
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

	/**
	 *	@param Whether to reverse the direction of the motors from the parameter passed to set
	 */
	bool reversed;
private:
#ifdef NR_CLOSED_LOOP_CONTROL
	PIDController frontPID, rearPID;
#endif
};

/**
 *	The class to drive the robot
 */
class Drive
{
public:
	/**
	 *	@brief Constructs a new drive object with the given motors and encoders
	 *	@param frontRightMotor The front right motor
	 *	@param rearRightMotor The rear right motor
	 *	@param frontLeftMotor The front left motor
	 *	@param rearLeftMotor The rear left motor
	 *	@param leftEncoder The left encoder
	 *	@param rightEncoder	The right encoder
	 */
	Drive( CANJaguar frontRightMotor,
		   CANJaguar rearRightMotor,
		   CANJaguar frontLeftMotor,
		   CANJaguar rearLeftMotor,
		   Encoder leftEncoder,
		   Encoder rightEncoder );
	
	/**
	 *	@brief Constructs a new drive object with the given motors and encoders
	 *	@param frontRightMotor The front right motor CAN number
	 *	@param rearRightMotor The rear right motor CAN number
	 *	@param frontLeftMotor The front left motor CAN number
	 *	@param rearLeftMotor The rear left motor CAN number
	 *	@param encoderLeftSlot1 The first slot of the left encoder
	 *	@param encoderLeftChannel1 The first channel of the left encoder
	 *	@param encoderLeftSlot2 The second slot of the left encoder
	 *	@param encoderLeftChannel2 The second channel of the left encoder
	 *	@param encoderRightSlot1 The first slot of the right encoder
	 *	@param encoderRightChannel1 The first channel of the right encoder
	 *	@param encoderRightSlot2 The second slot of the right encoder
	 *	@param encoderRightChannel2 The second channel of the right encoder
	 */
	Drive( UINT8 frontRightMotor,
				    UINT8 rearRightMotor,
				    UINT8 frontLeftMotor,
				    UINT8 rearLeftMotor,
				    UINT8 encoderLeftSlot1, UINT8 encoderLeftChannel1,
				    UINT8 encoderLeftSlot2, UINT8 encoderLeftChannel2,
				    UINT8 encoderRightSlot1, UINT8 encoderRightChannel1,
				    UINT8 encoderRightSlot2, UINT8 encoderRightChannel2,
				    CANJaguar::ControlMode controlMode = CANJaguar::kPercentVbus );
	
	/**
	 *	Drives via tank drive
	 *	@param The value to set the left to
	 *	@param The value to set the right to
	 */
	void TankDrive( float left, float right );
	
private:
	MotorPair leftMotors;
	MotorPair rightMotors;
	
	Encoder encoderLeft;
	Encoder encoderRight;
	
	void InitializeDiagnostics();
};
