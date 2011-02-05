/*
 *	Drive.h
 *	Nashoba Robotics 2011
 */

#pragma once

#include "WPILib.h"
#include "CANJaguar.h"

/**
 *	@brief A pair of motors, which can be conveniently set together
 */
class MotorPair;

/**
 *	@brief The class to drive the robot
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
