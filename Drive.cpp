/*
 *	Drive.cpp
 *	Nashoba Robotics 2011
 */

#include "Drive.h"

Drive :: Drive( CANJaguar frontLeftMotor,
				CANJaguar rearLeftMotor,
				CANJaguar frontRightMotor,
				CANJaguar rearRightMotor )
:	leftMotors(  frontLeftMotor,  rearLeftMotor  ),
	rightMotors( frontRightMotor, rearRightMotor )
{
}

Drive :: Drive( UINT8 frontLeftMotor,
			    UINT8 rearLeftMotor,
			    UINT8 frontRightMotor,
			    UINT8 rearRightMotor,
			    CANJaguar::ControlMode controlMode )
:	leftMotors(  frontLeftMotor,  rearLeftMotor,  controlMode ),
	rightMotors( frontRightMotor, rearRightMotor, controlMode )
{
}

void Drive :: TankDrive( float left, float right )
{
	leftMotors.Set(  left );
	rightMotors.Set( right );
}
