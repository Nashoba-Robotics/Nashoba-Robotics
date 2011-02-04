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

void Manipulator::Run()
{
	while ( IsOperatorControl() )
	{
		if ( joystick.GetRawButton( 2 ) )
		{
			SetLowerArm( ! lowerArm );
		}

		arm.SetUpperArm( (joy.GetY()+1)*kAngleRatio/2 );
	}
}



