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
	lineFollower( 1, 2, 3, 4, 4, 14, 4, 13 ),
	manipulator( manipulatorJoystick )
{
}

void Robot :: Autonomous( void )
{
	GetWatchdog().SetEnabled( false );
	
	bool pastY = false;
	
	while ( true )
	{
		if ( pastY && lineFollower.sensor1.Get() && lineFollower.sensor2.Get() && lineFollower.sensor3.Get() )
		{
			drive.TankDrive( 0.3, 0.3 );
			Wait( 1.0 );
			drive.TankDrive( 0.0, 0.0 );
			
			// Raise the claw
			manipulator.arm.SetLowerArm( true );
			manipulator.arm.SetUpperArm( Arm::kTopSideRung );
			
			// Drive forwards slightly
			drive.TankDrive( -0.3, -0.3 );
			Wait( 0.4 );
			drive.TankDrive( 0.0, 0.0 );
			
			// Spit out the tube
			manipulator.claw.Release();
			
			return;
		}
		else if ( lineFollower.sensor2.Get() )
			drive.TankDrive( -0.5, -0.5 );
		else if ( lineFollower.sensor3.Get() && lineFollower.sensor1.Get() )
		{
			drive.TankDrive( -0.5, 0.5 );
			Wait( 0.2 );
			pastY = true;
		}
		else if ( lineFollower.sensor3.Get() )
			drive.TankDrive( -0.5, 0.1 );
		else if ( lineFollower.sensor1.Get() )
			drive.TankDrive( 0.1, -0.5 );
		
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
