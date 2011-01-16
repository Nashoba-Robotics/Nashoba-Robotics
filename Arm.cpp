/*
 * Arm.cpp
 *
 *  Created on: Jan 13, 2011
 *      Author: Nick Alberts
 */

#include "Arm.h"

void Arm::control_arm_motor( void *object )
{
	Arm *instance = (Arm *) object;
	instance->upperArmAngle = instance->GetTilt();

	// Runs when the difference in angles is large enough
	//TODO: fix kCloseEnough with real value
	while ( fabs( instance->upperArmangle - instance->arm_control_angle ) < kCloseEnough )
	{
		// Conversion factor is from clicks to angles and k is to fix the angle
		instance->upperArmAngle = instance->GetTilt();
		instance->armMotor.Set( ( instance->arm_control_angle - instance->upperArmAngle ) / 500.0 );
	}

	instance->upperArmMotor.Set( 0.0 );
}


// TODO: needs actual arguments and ports
Arm::Arm():
	armMotor( 4 ),
	armSolenoidRaise( 1 ),
	armSolenoidLower( 2 ),
	armEncoder( 4 )

{
	lowerArm = false;
}

void Arm::SetLowerArm( bool position )
{

	if ( (! lowerArm && position) )
	{
		//fires the arm solenoid
		armSolenoidRaise->Set( true );
		armSolenoidLower->Set( false );
	}

	else if ( lowerArm && ! position )
	{
		armSolenoidLower->Set( true );
		armSolenoidRaise->Set( false );
	}
}

void Arm::SetUpperArm( double angle )
{
	// TODO: Constants and real angle factors
	if ( ! arm_control_mutex.TryLock() )
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
