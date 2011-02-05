/*
 *	Drive.cpp
 *	Nashoba Robotics 2011
 */

#include "Drive.h"
#include "diag/diagnostics_center.h"
#include "diag/observable_wpi.h"

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

	diag.register_device( new nr::diag::observable_jaguar_current( leftMotors.front ), "Left Front Current" );
	diag.register_device( new nr::diag::observable_jaguar_current( leftMotors.rear ), "Left Rear Current" );
	diag.register_device( new nr::diag::observable_jaguar_current( rightMotors.front ), "Right Front Current" );
	diag.register_device( new nr::diag::observable_jaguar_current( rightMotors.rear ), "Right Rear Current" );
	
	diag.register_device( new nr::diag::observable_encoder( encoderLeft ), "Left Encoder" );
	diag.register_device( new nr::diag::observable_encoder( encoderRight ), "Right Encoder" );
}
