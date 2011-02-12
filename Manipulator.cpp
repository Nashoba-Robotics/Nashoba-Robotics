/*
 *	Manipulator.cpp
 *	Nashoba Robotics 2011
 *
 *	Copyright 2011 Nick Alberts
 *	All Rights Reserved
 */

#include "Manipulator.h"

Manipulator::Manipulator( Joystick &joy ):
	joystick( joy )
{
}

void Manipulator::Run( void* ) throw ()
{
	// TODO: resolve issue of getting state of robot in Manipulator thread and object 
	
	//claw.Grab();
	//claw.ClawTest();

	while ( /*IsOperatorControl()*/ true )
	{

		arm.SimpleUpperArm( joystick.GetY() );
		if (joystick.GetRawButton(2))
		{
			claw.Grab();
		}
		if (joystick.GetRawButton(1))
		{
			claw.Release();
		}
		if (joystick.GetRawButton(3))
		{
			claw.RotateUp();
		}
		if (joystick.GetRawButton(6))
		{
			claw.RotateDown();
		}
	}
}



