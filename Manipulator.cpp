/*
 *	Manipulator.cpp
 *	Nashoba Robotics 2011
 *
 *	Copyright 2011 Nick Alberts
 *	All Rights Reserved
 */

#include "Manipulator.h"

Manipulator::Manipulator( Joystick &joy ):
	joystick( joy ),
	limitSwitch( 1, 5 )
{

}

void Manipulator::Run( void* ) throw ()
{
	// TODO: resolve issue of getting state of robot in Manipulator thread and object 
	
	//claw.Grab();
	//claw.ClawTest();

	while ( true )
	{
		while ( RobotBase::getInstance().IsOperatorControl() )
		{
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
				arm.SetUpperArm( Arm::kTopMiddleRung );
			}
			
			if ( joystick.GetRawButton( 7 ) )
			{
				arm.SetLowerArm( false );
				arm.SetUpperArm( -800 );
			}
			
			if ( joystick.GetRawButton( 11 ) )
			{
				arm.SetLowerArm( false );
				Wait( 1.5 );
				arm.SetUpperArm( 0 );
			}
			
			if ( joystick.GetRawButton( 9 ) )
				GoDown();
			
			if ( joystick.GetRawButton( 8 ) )
			{
				double value = joystick.GetY();
				if ( value >= 0.0 || (limitSwitch.GetVoltage() < 4.5 && value < 0.0) )
					arm.SimpleUpperArm( joystick.GetY() );
				else
					arm.SimpleUpperArm( 0.0 );
			}
			
			else if ( limitSwitch.GetVoltage() > 4.5 )
				arm.armMotor.Set( 0.0 );
			
			arm.encoderValue = arm.armEncoder.Get();
			
			Wait(0.05);
		}
		Wait( 0.10 );
	}
}

void Manipulator::GoDown()
{
	arm.SetLowerArm( false );
	Wait( 3.0f );
	arm.SetUpperArm( -70 );
}
