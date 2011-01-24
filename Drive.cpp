/*
 *	Drive.cpp
 *	Nashoba Robotics 2011
 */

#include "Drive.h"
#include "diag/diagnostics_center.h"
#include "diag/observable_wpi.h"

/*
Drive :: Drive( Jaguar frontLeftMotor,
				Jaguar rearLeftMotor,
				Jaguar frontRightMotor,
				Jaguar rearRightMotor )
:	leftMotors(  frontLeftMotor,  rearLeftMotor  ),
	rightMotors( frontRightMotor, rearRightMotor )
{
	InitializeDiagnostics();
}
*/

Drive :: Drive( UINT8 frontLeftMotor,
			    UINT8 rearLeftMotor,
			    UINT8 frontRightMotor,
			    UINT8 rearRightMotor,
			    UINT8 leftEncoder1, UINT8 leftEncoder2,
			    UINT8 rightEncoder1, UINT8 rightEncoder2,
			    CANJaguar::ControlMode controlMode )
:	leftMotors(  frontLeftMotor,  rearLeftMotor, leftEncoder1, leftEncoder2, controlMode ),
	rightMotors( frontRightMotor, rearRightMotor, rightEncoder1, rightEncoder2, controlMode )
{
	leftMotors.reverse = true;
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
	
	diag.register_device( new nr::diag::observable_jaguar( leftMotors.front ), "Left Front Motor" );
	diag.register_device( new nr::diag::observable_jaguar( leftMotors.rear ), "Left Rear Motor" );
	diag.register_device( new nr::diag::observable_jaguar( rightMotors.front ), "Right Front Motor" );
	diag.register_device( new nr::diag::observable_jaguar( rightMotors.rear ), "Right Rear Motor" );
	
	diag.register_device( new nr::diag::observable_encoder( rightMotors.encoder ), "Right Encoder" );
	diag.register_device( new nr::diag::observable_encoder( leftMotors.encoder ), "Left Encoder" );
	
}
