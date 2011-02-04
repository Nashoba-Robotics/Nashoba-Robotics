/*
 * Claw.cpp
 *
 *  Created on: Jan 13, 2011
 *      Author: Nick Alberts
 */

#include "Claw.h"
#include "diag/diagnostics_center.h"

//needs port numbers
Claw::Claw():
clawServoTop( 1 ),
clawServoBottom( 2 ),
claw_control_thread(Claw::claw_servo_stop)
{
	// Add the servos to the diagnostics center
	nr::diag::diagnostics_center &diag = nr::diag::diagnostics_center::get_shared_instance();
	
	diag.register_device( new nr::diag::observable_speed_controller( clawServoTop, "Top Claw Servo" );
	diag.register_device( new nr::diag::observable_speed_controller( clawServoBottom, "Bottom Claw Servo" );
};

void Claw::claw_servo_stop( void *object)
{

	claw *instance = (claw *) object;
	
	Wait( 2.0f );
	instance->clawServoTop.Set( 176 );
	instance->clawServoBottom.Set( 176 );
}


//pulls both motors in

//TODO: Real times and motor speeds

void Claw::Grab()
{

	if ( ! claw_control_mutex.TryLock() )
	{
		claw_control_thread.Stop();
	}
	claw_control_thread.Start( (void *) this );
	clawServoTop.Set( 0 );
	clawServoBottom.Set( 256 );
}

//pushes the tube out, with the top motor faster to change orientation
//TODO: REAL VALUES
void Claw::Release()
{
	if ( ! claw_control_mutex.TryLock() )
	{
		claw_control_thread.Stop();
	}
	claw_control_thread.Start( (void *) this );
	clawServoTop.Set( 256 );
	clawServoBottom.Set( 0 );
}

void Claw::RotateUp()
{
		if ( ! claw_control_mutex.TryLock() )
		{
			claw_control_thread.Stop();
		}
		claw_control_thread.Start( (void *) this );
		clawServoTop.Set( 0 );
		clawServoBottom.Set( 0 );
}

void Claw::RotateDown()
{
		if ( ! claw_control_mutex.TryLock() )
		{
			claw_control_thread.Stop();
		}
		claw_control_thread.Start( (void *) this );
		clawServoTop.Set( 256 );
		clawServoBottom.Set( 256 );
}
