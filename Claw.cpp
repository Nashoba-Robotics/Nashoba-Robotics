/*
 * Claw.cpp
 *
 *  Created on: Jan 13, 2011
 *      Author: Nick Alberts
 */

#include "Claw.h"
#include "diag/DiagnosticsCenter.h"


Claw::Claw():
clawServoTop4( 4 ),
clawServoTop3 ( 3 ),
clawServoBottom1( 5 ),
clawServoBottom2( 6 ),
claw_control_thread(new nr::conc::Thread::FunctionEntry( Claw::claw_servo_stop ) )
{
	clawControlRunning = false;
};

void Claw::claw_servo_stop( void *object)
{

	Claw *instance = (Claw *) object;
	
	Wait( instance->time );
	instance->clawServoTop4.SetRaw( 0 );
	instance->clawServoTop3.SetRaw( 0 );
	instance->clawServoBottom1.SetRaw( 0 );
	instance->clawServoBottom2.SetRaw( 0 );
	
	instance->clawControlRunning = false;
}


//pulls both motors in



//TODO: Real times and motor speeds

void Claw::Grab()
{

	if ( clawControlRunning )
	{
		claw_control_thread.Stop();
	}
	claw_control_thread.Start( (void *) this );
	clawControlRunning = true;
	clawServoTop4.SetRaw( 1 );
	clawServoTop3.SetRaw( 255 );
	clawServoBottom1.SetRaw( 255 );
	clawServoBottom2.SetRaw( 1 );
	time=0.2;
}

//pushes the tube out, with the top motor faster to change orientation
//TODO: REAL VALUES
void Claw::Release()
{
	if ( clawControlRunning )
	{
		claw_control_thread.Stop();
	}
	claw_control_thread.Start( (void *) this );
	clawControlRunning = true;
	clawServoTop4.SetRaw( 255 );
	clawServoTop3.SetRaw( 1 );
	clawServoBottom1.SetRaw( 1 );
	clawServoBottom2.SetRaw( 255 );
	time = 2.0;
}

void Claw::RotateUp()
{
		if ( clawControlRunning )
		{
			claw_control_thread.Stop();
		}
		claw_control_thread.Start( (void *) this );
		clawControlRunning = true;
		clawServoTop4.SetRaw( 1 );
		clawServoTop3.SetRaw( 255 );
		
		clawServoBottom1.SetRaw( 1 );
		clawServoBottom2.SetRaw( 255 );
		time = 0.5;
}

void Claw::RotateDown()
{
		if ( clawControlRunning )
		{
			claw_control_thread.Stop();
		}
		claw_control_thread.Start( (void *) this );
		clawControlRunning = true;
		clawServoTop4.SetRaw( 255 );
		clawServoTop3.SetRaw( 1 );
		clawServoBottom1.SetRaw( 255 );
		clawServoBottom2.SetRaw( 1 );
		time = 0.5;
}

