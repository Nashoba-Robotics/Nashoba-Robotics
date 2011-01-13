/*
 *  Robot.cpp
 *  Nashoba Robotics 2011
 *
 *  Copyright 2011 RC Howe
 *  All Rights Reserved
 */

#include "Robot.h"

Robot :: Robot()
:	joy1( 1 ),
	joy2( 2 ),
	motor1( 4, 1 ),
	motor2( 4, 2 ),
	motor3( 4, 3 ),
	motor4( 4, 4 ),
	drive( motor1, motor2, motor3, motor4 ),
	lineFollower( 1, 1, 1 ) // FIXME: Not actual #s
{
}

void Robot :: Autonomous( void )
{
	GetWatchdog().SetEnabled( false );
	
	// Drive forward for two seconds
	drive.TankDrive( 1.0f, 1.0f );
	if ( lineFollower.WaitUntilLineDetectedOrTimeout( 5.0f ) )
	{
		drive.TankDrive( -1.0f, 1.0f );
		lineFollower.WaitUntilFacing( LineFollower::kScoringSide );

		drive.TankDrive( 1.0f, 1.0f );
		Wait( 2.0f );
		
		drive.TankDrive( 0.0f, 0.0f );
	}
	
	else
		drive.TankDrive( 0.0f, 0.0f );
}

void Robot :: OperatorControl( void )
{
	GetWatchdog().SetEnabled( true );
	GetWatchdog().SetTimeout( 0.1f );
	
	while ( IsOperatorControl() )
	{
		drive.TankDrive( joy1.GetY(), joy2.GetY() );
		Wait( kMainRunLoopDelta );
	}
}
