/*
 *	Drive.cpp
 *	Nashoba Robotics 2011
 */

#include "Drive.h"

#define NR_USE_WPILIB
#include "diag/DiagnosticsCenter.h"
#include "diag/ObservableWPI.h"
#undef NR_USE_WPILIB

MotorPair::MotorPair( CANJaguar &fr, CANJaguar &rr, Encoder &e )
:	front( fr ), rear( rr ),
	encoder( 4, 1, 4, 2 )
#ifdef NR_CLOSED_LOOP_CONTROL
	,
	frontPID( kPIDProportional, kPIDIntegral, kPIDDifferential, &encoder, &front ),
	rearPID( kPIDProportional, kPIDIntegral, kPIDDifferential, &encoder, &rear )
#endif
{
	front.SetSafetyEnabled( false );
	rear.SetSafetyEnabled(  false );
	
	reversed = false;
}

MotorPair::MotorPair( UINT8 fr, UINT8 rr,
		  UINT8 encoderSlot1, UINT8 encoderChannel1,
		  UINT8 encoderSlot2, UINT8 encoderChannel2,
		  CANJaguar::ControlMode controlMode )
:	front( fr, controlMode ),
	rear( rr, controlMode ),
	encoder( encoderSlot1, encoderChannel1, encoderSlot2, encoderChannel2 )
#ifdef NR_CLOSED_LOOP_CONTROL
	,
	frontPID( kPIDProportional, kPIDIntegral, kPIDDifferential, &encoder, &front ),
	rearPID(  kPIDProportional, kPIDIntegral, kPIDDifferential, &encoder, &rear )
#endif
{
	front.SetSafetyEnabled( false );
	rear.SetSafetyEnabled(  false );

	reversed = false;
}

void MotorPair::Set( float value )
{
#ifdef NR_CLOSED_LOOP_CONTROL
	frontPID.Set( value * (reversed ? -1 : 1) );
	rearPID.Set(  value * (reversed ? -1 : 1) );
#else
	front.Set( value * (reversed ? -1 : 1) );
	rear.Set(  value * (reversed ? -1 : 1) );
#endif
}

// Drive code starts here

Drive :: Drive( CANJaguar frontRightMotor,
				CANJaguar rearRightMotor,
				CANJaguar frontLeftMotor,
				CANJaguar rearLeftMotor,
				Encoder leftEncoder,
				Encoder rightEncoder )
:	leftMotors(  frontLeftMotor,  rearLeftMotor,  leftEncoder ),
	rightMotors( frontRightMotor, rearRightMotor, rightEncoder )
{
	rightMotors.reversed = true;
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
:	leftMotors(  frontLeftMotor,  rearLeftMotor,  encoderLeftSlot1,  encoderLeftChannel1,  encoderLeftSlot2,  encoderLeftChannel2,  controlMode ),
	rightMotors( frontRightMotor, rearRightMotor, encoderRightSlot1, encoderRightChannel1, encoderRightSlot2, encoderRightChannel2, controlMode )
{
	rightMotors.reversed = true;
	InitializeDiagnostics();
}

void Drive :: TankDrive( float left, float right )
{
	leftMotors.Set(  left );
	rightMotors.Set( right );
}

void Drive :: InitializeDiagnostics()
{
	nr::diag::DiagnosticsCenter &diag = nr::diag::SharedDiagnosticsCenter();

	diag.RegisterDevice( leftMotors.front,  "Left Front Motor" );
	diag.RegisterDevice( leftMotors.rear,   "Left Rear Motor" );
	diag.RegisterDevice( rightMotors.front, "Right Front Motor" );
	diag.RegisterDevice( rightMotors.rear,  "Right Rear Motor" );

	diag.RegisterDevice( new nr::diag::ObservableJaguarCurrent( leftMotors.front ),  "Left Front Motor - Current" );
	diag.RegisterDevice( new nr::diag::ObservableJaguarCurrent( leftMotors.rear ),   "Left Rear Motor - Current" );
	diag.RegisterDevice( new nr::diag::ObservableJaguarCurrent( rightMotors.front ), "Right Front Motor - Current" );
	diag.RegisterDevice( new nr::diag::ObservableJaguarCurrent( rightMotors.rear ),  "Right Rear Motor - Current" );
	
	diag.RegisterDevice( leftMotors.encoder,  "Left Encoder" );
	diag.RegisterDevice( rightMotors.encoder, "Right Encoder" );
}
