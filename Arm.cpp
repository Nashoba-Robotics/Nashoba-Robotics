/*
 * Arm.cpp
 *
 *  Created on: Jan 13, 2011
 *      Author: Nick Alberts
 */

#include "Arm.h"
#include "diag/diagnostics_center.h"
#include <math.h>

/**
 * This function runs in the control thread, and continually sets the motors to the correct speed.
 * The speed is determined by the difference in angle divided by a constant.
 */
void Arm::control_arm_motor( void *object )
{
	Arm *instance = (Arm *) object;
	instance->upperArmAngle = instance->GetTilt();
	// Runs when the difference in angles is large enough
	//TODO: fix kCloseEnough with real value
	while ( fabs( instance->upperArmAngle - instance->arm_control_angle ) > kCloseEnough )
	{

		instance->upperArmAngle = instance->GetTilt();
		if (((instance->upperArmAngle-instance->arm_control_angle ) / 1000 < 0.2) && ((instance->upperArmAngle-instance->arm_control_angle ) / 2000 > 0) )
		{
			instance->armMotor.Set(0.5);
		}
		else if (((instance->upperArmAngle-instance->arm_control_angle ) / 1000 > -0.2) && ((instance->upperArmAngle-instance->arm_control_angle ) / 2000 < 0) )
		{
					instance->armMotor.Set(-0.4);
		}
		else if ((instance->upperArmAngle-instance->arm_control_angle ) / 1000 >= 1.0 )
		{
			instance->armMotor.Set(1.0);
		}
		else if ((instance->upperArmAngle-instance->arm_control_angle ) / 1000 <= -1.0 )
		{
			instance->armMotor.Set(-1.0);
		}
		else
		{
		instance->armMotor.Set( ( instance->upperArmAngle-instance->arm_control_angle ) / 1000 );
		}
		printf( "%f", instance->arm_control_angle );
		Wait( 0.05 );		

	}

	instance->armMotor.Set( 0.0 );
}


/**
 * @brief Constructor for arm class
 */
Arm::Arm():
	armMotor( 5 ),
	armSolenoidRaise( 7, 2 ),
	armSolenoidLower( 7, 1 ),
	armEncoder( 9,10 ),
	arm_control_thread(new nr::conc::thread::function_entry( Arm::control_arm_motor ) )

{
	armEncoder.Start();
	nr::diag::diagnostics_center& diag = nr::diag::diagnostics_center::get_shared_instance();
	diag.register_device( new nr::diag::observable_speed_controller( armMotor ), "Arm Motor" );
	diag.register_device( new nr::diag::observable_encoder( armEncoder ), "Arm Encoder" );
}
/**
 * This function sets the lower arm to a boolean position value:true corresponds to raised and false corresponds to lower
 */
void Arm::SetLowerArm( bool position )
{

	if ( position )
	{
		//fires the arm solenoid
		armSolenoidRaise.Set( true );
		armSolenoidLower.Set( false );
	}

	else if ( ! position )
	{
		armSolenoidLower.Set( true );
		armSolenoidRaise.Set( false );
		//printf("going down");
	}
}

void Arm::SimpleUpperArm (float value)
{
	armMotor.Set(value);
}

void Arm::SetUpperArm( double angle )
{
	// TODO: Constants and real angle factors
	if ( ! arm_control_mutex.trylock() )
	{
		arm_control_thread.Stop();
	}
	arm_control_angle = angle;
	arm_control_thread.Start( (void *) this );
}

// TODO: fix this for real values with actual correction value
double Arm::GetTilt()
{
	return armEncoder.Get();
}
