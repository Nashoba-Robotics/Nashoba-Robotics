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
		/*
		/*	
		claw.clawServoBottom1.SetRaw(0);
		claw.clawServoTop4.SetRaw(0);
		claw.clawServoTop3.SetRaw(0);
		claw.clawServoBottom2.SetRaw(0);
		Wait(4.0f);

		claw.clawServoBottom1.SetRaw(255);
		claw.clawServoBottom2.SetRaw(1);
		claw.clawServoTop4.SetRaw(255);
		claw.clawServoTop3.SetRaw(1);
		Wait(4.0f);
		/*
		printf("A\n");
		
		Wait(4.0f);
		
		claw.clawServoBottom1.Set(0.0f);
		claw.clawServoBottom2.Set(1.0f);
		claw.clawServoTop4.Set(0.0f);
		claw.clawServoTop3.Set(1.0f);
		
		printf("B\n");	
		
		Wait(1.0f);
		
		/*
		if (joystick.GetRawButton(2))
		{
			if (arm.lowerArm)
			{
				arm.SetLowerArm(true);
			}
			if ( ! arm.lowerArm)
			{
				arm.SetLowerArm(false);
			}
		}

		/*
		claw.ClawTest();
		//claw.SimpleGripper( joystick.GetY() );
		*/
		
		/*
		claw.clawServoBottom1.Set( ((joystick.GetY())+1.0f )/2.0f );
		claw.clawServoBottom2.Set( 1.0f-((joystick.GetY())+1.0f)/2.0f);
		claw.clawServoTop4.Set( 1.0f-((joystick.GetX())+1.0f)/2.0f);
		claw.clawServoTop3.Set( ((joystick.GetX())+1.0f )/2.0f );Wait(0.05);
		Wait(0.05);
		/*
		dashboard.AddFloat(((joystick.GetY())+1.0f )/2.0f);
		dashboard.AddFloat(((joystick.GetX())+1.0f )/2.0f);
		dashboard.AddFloat(1.0f-((joystick.GetX())+1.0f)/2.0f);
		dashboard.AddFloat(1.0f-((joystick.GetY())+1.0f)/2.0f);
		*/
	}
}



