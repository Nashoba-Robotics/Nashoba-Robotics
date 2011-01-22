/*
 *	Drive.cpp
 *	Nashoba Robotics 2011
 */

#include "Drive.h"
#include "diag/diagnostics_center.h"
#include "diag/observable_wpi.h"

Drive :: Drive( CANJaguar frontLeftMotor,
				CANJaguar rearLeftMotor,
				CANJaguar frontRightMotor,
				CANJaguar rearRightMotor )
:	leftMotors(  frontLeftMotor,  rearLeftMotor  ),
	rightMotors( frontRightMotor, rearRightMotor )
{
	InitializeDiagnostics();
}

Drive :: Drive( UINT8 frontLeftMotor,
			    UINT8 rearLeftMotor,
			    UINT8 frontRightMotor,
			    UINT8 rearRightMotor,
			    CANJaguar::ControlMode controlMode )
:	leftMotors(  frontLeftMotor,  rearLeftMotor,  controlMode ),
	rightMotors( frontRightMotor, rearRightMotor, controlMode )
{
	InitializeDiagnostics();
}

void Drive :: TankDrive( float left, float right )
{
	leftMotors.Set(  left );
	rightMotors.Set( right );
}

void Drive :: InitializeDiagnostics()
{
	nr::diag::diagnostics_center &diag = nr::diag::diagnostics_center::get_shared_instance();
	
	diag.register_device( new nr::diag::observable_can_jaguar( leftMotors.front ), "Left Front Motor" );
	diag.register_device( new nr::diag::observable_can_jaguar( leftMotors.rear ), "Left Rear Motor" );
	diag.register_device( new nr::diag::observable_can_jaguar( rightMotors.front ), "Right Front Motor" );
	diag.register_device( new nr::diag::observable_can_jaguar( rightMotors.rear ), "Right Rear Motor" );
}
