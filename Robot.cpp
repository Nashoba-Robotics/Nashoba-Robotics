/*
 *  Robot.cpp
 *  Nashoba Robotics 2011
 *
 *  Copyright 2011 RC Howe
 *  All Rights Reserved
 */

#include "Robot.h"
 
Robot :: Robot( void )
:	joy1( 1 ), joy2( 2 ),
	drive( 1, 2, 3, 4, 4, 4, 4, 5, 4, 6, 4, 7 ),
	lineFollower( 1, 2, 3, 4 ) // FIXME: Not actual #s
{
}

void Robot :: Autonomous( void )
{
	GetWatchdog().SetEnabled( false );
	
	// Drive forward for two seconds
	drive.TankDrive( 0.2f, 0.2f );
	if ( lineFollower.WaitUntilLineDetectedOrTimeout( 5.0f ) )
	{
		drive.TankDrive( -0.5f, 0.5f );
		lineFollower.WaitUntilFacing( LineFollower::kScoringSide );

		drive.TankDrive( 0.5f, 0.5f );
		Wait( 2.0f );
		
		drive.TankDrive( 0.0f, 0.0f );
	}
	
	else
	{
	//	drive.TankDrive( 0.0f, 0.0f );
		drive.TankDrive( 0.3f, -0.3f );
	}
}

void Robot :: OperatorControl( void )
{
	GetWatchdog().SetEnabled( false );
	GetWatchdog().SetExpiration( 0.1f );
	
	while ( IsOperatorControl() )
	{
		drive.TankDrive( joy1.GetY(), joy2.GetY() );
		Wait( kMainRunLoopDelta );
	}
}
