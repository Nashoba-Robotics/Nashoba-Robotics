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
	while ( /*IsOperatorControl()*/ true )
	{
		if ( joystick.GetRawButton( 2 ) )
		{
			arm.SetLowerArm( ! arm.lowerArm );
		}

		arm.SetUpperArm( (joystick.GetY()+1)*kAngleRatio/2 );
	}
}



