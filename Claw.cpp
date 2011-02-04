/*
<<<<<<< HEAD
 * Claw.cpp
 *
 *  Created on: Jan 13, 2011
 *      Author: Nick Alberts
 */

#include "Claw.h"

//needs port numbers
Claw::Claw():
clawMotorTop( 4, 1 ),
clawMotorBottom( 4, 2 )
{

};

void Claw::claw_motor_stop( void *object )
{
	claw *instance = (claw *) object;
	Wait( 0.7 );
	instance->clawMotorTop.Set( 0.0 );
	instance->clawMotorBottom.Set( 0.0 );
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
	clawMotorBottom.Set( 0.4 );
	clawMotorTop.Set( 0.4 );
}

//pushes the tube out, with the top motor faster to change orientation
void Claw::Release()
{
	clawMotorBottom.Set( -0.2 );
	clawMotorTop.Set( -0.5 );
	Wait( 0.7 );

}
=======
 *	Claw.cpp
 *	Nashoba Robotics 2011
 */

void Claw :: RotateTubeTo( float angle )
{
	topServo.SetAngle( angle * kTopGearRatio );
	bottomServo.SetAngle( angle * kBottonGearRatio );
}

void Claw :: ReleaseTube()
{
	topServo.SetAngle( Servo::GetMaxAngle() )
	bottomServo.SetAngle( Servo::GetMinAngle() );
}

void Claw :: GrabTube()
{
	topServo.SetAngle( Servo::GetMaxAngle() )
	bottomServo.SetAngle( Servo::GetMinAngle() );
}
>>>>>>> 83d07d249ae3b4e66502441270b70214f77a6d2c
