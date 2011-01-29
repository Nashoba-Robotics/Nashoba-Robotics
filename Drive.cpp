/*
 *	Drive.cpp
 *	Nashoba Robotics 2011
 */

#include "Drive.h"
#include "diag/diagnostics_center.h"
#include "diag/observable_wpi.h"

Drive :: Drive( CANJaguar frontRightMotor,
				CANJaguar rearRightMotor,
				CANJaguar frontLeftMotor,
				CANJaguar rearLeftMotor,
				Encoder leftEncoder,
				Encoder rightEncoder )
:	leftMotors(  frontLeftMotor,  rearLeftMotor  ),
	rightMotors( frontRightMotor, rearRightMotor ),
	encoderLeft( 4, 1, 4, 2 ), // FIXME: Use arguments
	encoderRight( 4, 3, 4, 4 )
{
	rightMotors.reversed = true;
	encoderLeft.Start();
	encoderRight.Start();
	InitializeDiagnostics();
}

Drive :: Drive( UINT8 frontRightMotor,
			    UINT8 rearRightMotor,
			    UINT8 frontLeftMotor,
			    UINT8 rearLeftMotor,
			    UINT8 encoderLeftSlot1, UINT8 encoderLeftChannel1,
			    UINT8 encoderLeftSlot2, UINT8 encoderLeftChannel2,
			    UINT8 encoderRightSlot1, UINT8 encoderRightChannel1,
			    UINT8 encoderRightSlot2, UINT8 encoderRightChannel2,
			    CANJaguar::ControlMode controlMode )
:	leftMotors(  frontLeftMotor,  rearLeftMotor,  controlMode ),
	rightMotors( frontRightMotor, rearRightMotor, controlMode ),
	encoderLeft( encoderLeftSlot1, encoderLeftChannel1, encoderLeftSlot2, encoderLeftChannel2 ),
	encoderRight( encoderRightSlot1, encoderRightChannel1, encoderRightSlot2, encoderRightChannel2 )
{
	rightMotors.reversed = true;
	encoderLeft.Start();
	encoderRight.Start();
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
	
	diag.register_device( new nr::diag::observable_speed_controller( leftMotors.front ), "Left Front Motor" );
	diag.register_device( new nr::diag::observable_speed_controller( leftMotors.rear ), "Left Rear Motor" );
	diag.register_device( new nr::diag::observable_speed_controller( rightMotors.front ), "Right Front Motor" );
	diag.register_device( new nr::diag::observable_speed_controller( rightMotors.rear ), "Right Rear Motor" );
	
	diag.register_device( new nr::diag::observable_encoder( encoderLeft ), "Left Encoder" );
	diag.register_device( new nr::diag::observable_encoder( encoderRight ), "Right Encoder" );
}
