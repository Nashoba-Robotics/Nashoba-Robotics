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
clawServoTop1( 1 ),
clawServoTop2 (2),
clawServoBottom1( 3 ),
clawServoBottom2( 4 ),
claw_control_thread(new nr::conc::thread::function_entry( Claw::claw_servo_stop ) )
{
	// Add the servos to the diagnostics center
	nr::diag::diagnostics_center &diag = nr::diag::diagnostics_center::get_shared_instance();
	
	diag.register_device( new nr::diag::observable_servo( clawServoTop1 ), "Top Claw Servo 1" );
	diag.register_device( new nr::diag::observable_servo( clawServoTop2 ), "Top Claw Servo 2" );
	diag.register_device( new nr::diag::observable_servo( clawServoBottom1 ), "Bottom Claw Servo 1" );
	diag.register_device( new nr::diag::observable_servo( clawServoBottom2 ), "Bottom Claw Servo 2" );
};

void Claw::claw_servo_stop( void *object)
{

	Claw *instance = (Claw *) object;
	
	Wait( 2.0f );
	instance->clawServoTop1.Set( 176 );
	instance->clawServoTop2.Set( 176 );
	instance->clawServoBottom1.Set( 176 );
	instance->clawServoBottom2.Set( 176 );
}


//pulls both motors in

//TODO: Real times and motor speeds

void Claw::Grab()
{

	if ( ! claw_control_mutex.trylock() )
	{
		claw_control_thread.Stop();
	}
	claw_control_thread.Start( (void *) this );
	clawServoTop1.Set( 0 );
	clawServoTop2.Set( 0 );
	clawServoBottom1.Set( 255 );
	clawServoBottom2.Set(255);
}

//pushes the tube out, with the top motor faster to change orientation
//TODO: REAL VALUES
void Claw::Release()
{
	if ( ! claw_control_mutex.trylock() )
	{
		claw_control_thread.Stop();
	}
	claw_control_thread.Start( (void *) this );
	clawServoTop1.Set( 256 );
	clawServoTop2.Set( 256 );
	clawServoBottom1.Set( 0 );
	clawServoBottom2.Set( 0 );
}

void Claw::RotateUp()
{
		if ( ! claw_control_mutex.trylock() )
		{
			claw_control_thread.Stop();
		}
		claw_control_thread.Start( (void *) this );
		clawServoTop1.Set( 0 );
		clawServoTop2.Set( 0 );
		
		clawServoBottom1.Set( 0 );
		clawServoBottom2.Set( 0 );
}

void Claw::RotateDown()
{
		if ( ! claw_control_mutex.trylock() )
		{
			claw_control_thread.Stop();
		}
		claw_control_thread.Start( (void *) this );
		clawServoTop1.Set( 256 );
		clawServoTop2.Set( 256 );
		clawServoBottom1.Set( 256 );
		clawServoBottom2.Set( 256 );

}
