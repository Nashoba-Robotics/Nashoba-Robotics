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

	while ( RobotBase::getInstance().IsOperatorControl() )
	{

		if ( joystick.GetRawButton( 8 ) )
			arm.SimpleUpperArm( joystick.GetY() );
		
		if ( joystick.GetRawButton( 2 ) )
			claw.Grab();
		
		if ( joystick.GetRawButton( 1 ) )
			claw.Release();

		if ( joystick.GetRawButton( 3 ) )
			claw.RotateUp();

		if ( joystick.GetRawButton( 4 ) )
			claw.RotateDown();

		if ( joystick.GetRawButton( 5 ) )
			arm.SetLowerArm( true );
		
		if ( joystick.GetRawButton( 6 ) )
			arm.SetLowerArm( false );

		if ( joystick.GetRawButton( 10 ) )
		{
			arm.SetLowerArm( true );
			arm.SetUpperArm( -1953 );
		}
		
		if ( joystick.GetRawButton( 7 ) )
		{
			arm.SetLowerArm( false );
			arm.SetUpperArm( -800 );
		}
		
		if ( joystick.GetRawButton( 11 ) )
		{
			arm.SetLowerArm( false );
			arm.SetUpperArm( -50 );
		}
		
		if ( joystick.GetRawButton( 9 ) )
			GoDown();
		
		arm.encoderValue = arm.armEncoder.Get();
		
		Wait(0.05);
	}
}

void Manipulator::GoDown()
{
	arm.SetLowerArm( false );
	Wait( 1.5f );
	arm.SetUpperArm( -70 );
}

