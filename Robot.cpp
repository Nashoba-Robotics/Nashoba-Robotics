/*
 *  Robot.cpp
 *  Nashoba Robotics 2011
 *
 *  Copyright 2011 RC Howe
 *  All Rights Reserved
 */

#include "Robot.h"
#include "Arm.h"
 
Robot :: Robot( void )
:	joy1( 1 ), joy2( 2 ),
	manipulatorJoystick( 3 ),
	drive( 1, 2, 3, 4, 4, 4, 4, 5, 4, 6, 4, 7 ),
	lineFollower( 1, 2, 3, 8 ),
	manipulator( manipulatorJoystick ),
	compressor( 4, 12, 4, 2 ),
	ultrasonic( 14, 13 )
{
	compressor.Start();
	nr::conc::Thread th( &manipulator );
	th.Start();
}

void Robot :: Autonomous( void )
{
	GetWatchdog().SetEnabled( false );
	
	bool pastY = true;
	double speed = 0.9;
	
	while ( IsAutonomous() )
	{
		if ( ultrasonic.GetRangeInches() < 60.0 )
			speed = 0.5;
		else
			speed = 0.9;
		
		if ( pastY && lineFollower.sensor1.Get() && lineFollower.sensor2.Get() && lineFollower.sensor3.Get() )
		{
			drive.TankDrive( 0.3, 0.3 );
			Wait( 1.2 );
			drive.TankDrive( 0.0, 0.0 );
			
			// Raise the claw
			manipulator.arm.SetLowerArm( true );
			manipulator.arm.SetUpperArm( Arm::kTopSideRung );
			
			// Drive forwards slightly
			drive.TankDrive( -0.3, -0.3 );
			Wait( 0.4 );
			drive.TankDrive( 0.0, 0.0 );

			Wait( 6.5 );
			// Spit out the tube
			manipulator.claw.RotateDown();
			Wait(0.3f);
			manipulator.claw.RotateDown();
			Wait(0.3f);
			manipulator.claw.RotateDown();
			Wait(0.3f);
			manipulator.claw.RotateDown();
			Wait(0.3f);
			manipulator.claw.RotateDown();
			Wait(0.3f);
			manipulator.claw.Release();
			
			return;
		}
		else if ( lineFollower.sensor2.Get() )
			drive.TankDrive( -0.5 * speed, -0.5 * speed );
		else if ( lineFollower.sensor3.Get() && lineFollower.sensor1.Get() )
		{
			drive.TankDrive( -0.5 * speed, 0.5 * speed );
			Wait( 0.2 );
			pastY = true;
		}
		else if ( lineFollower.sensor3.Get() )
			drive.TankDrive( -0.5 * speed, 0.1 * speed );
		else if ( lineFollower.sensor1.Get() )
			drive.TankDrive( 0.1 * speed, -0.5 * speed );
		
		Wait( 0.001 );
	}
}

void Robot :: OperatorControl( void )
{
	GetWatchdog().SetEnabled( false );
	
	while ( IsOperatorControl() )
	{
		drive.TankDrive( joy1.GetY(), joy2.GetY() );
		Wait( kMainRunLoopDelta );
	}
}
