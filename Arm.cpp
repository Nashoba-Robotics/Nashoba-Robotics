/*
 * Arm.cpp
 *
 *  Created on: Jan 13, 2011
 *      Author: Nick Alberts
 */

#include "Arm.h"
#include "diag/diagnostics_center.h"
#include "Math.h"
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
	while ( fabs( instance->upperArmAngle - instance->arm_control_angle ) < kCloseEnough )
	{
		// Conversion factor is from clicks to angles and k is to fix the angle
		instance->upperArmAngle = instance->GetTilt();
		instance->armMotor.Set( ( instance->arm_control_angle - instance->upperArmAngle ) / 500.0 );
	}

	instance->armMotor.Set( 0.0 );
}


// TODO: needs actual arguments and ports
/**
 * constructor for arm class
 */
Arm::Arm():
	armMotor( 4 ),
	armSolenoidRaise( 1 ),
	armSolenoidLower( 2 ),
	armEncoder( 4,5 ),
	arm_control_thread(new nr::conc::thread::function_entry( Arm::control_arm_motor ) )

{
	lowerArm = false;
	
	nr::diag::diagnostics_center& diag = nr::diag::diagnostics_center::get_shared_instance();
	diag.register_device( new nr::diag::observable_speed_controller( armMotor ), "Arm Motor" );
	diag.register_device( new nr::diag::observable_encoder( armEncoder ), "Arm Encoder" );
}
/**
 * THis function sets the lower arm to a boolean position value:true corresponds to raised and false corresponds to lower
 */
void Arm::SetLowerArm( bool position )
{

	if ( (! lowerArm && position) )
	{
		//fires the arm solenoid
		armSolenoidRaise.Set( true );
		armSolenoidLower.Set( false );
		lowerArm=true;
	}

	else if ( lowerArm && ! position )
	{
		armSolenoidLower.Set( true );
		armSolenoidRaise.Set( false );
		lowerArm=false;
	}
}

void Arm::SetUpperArm( double angle )
{
	// TODO: Constants and real angle factors
	if ( ! arm_control_mutex.trylock() )
	{
		arm_control_thread.Stop();
	}
	arm_control_thread.Start( (void *) this );
	arm_control_angle = angle;
}

// TODO: fix this for real values with actual correction value
double Arm::GetTilt()
{
	return armEncoder.Get();
}
