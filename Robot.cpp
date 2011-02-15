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
	lineFollower( 1, 2, 3, 4, 4, 14, 4, 13 ),
	ultrasonic( 4, 1, 4, 2 )
{
}

void Robot :: Autonomous( void )
{
	GetWatchdog().SetEnabled( false );
	
	bool pastY = false;
	
	while ( true )
	{
		float speed = 1.0;
		
		if ( pastY && lineFollower.sensor1.Get() && lineFollower.sensor2.Get() && lineFollower.sensor3.Get() )
		{
			drive.TankDrive( 0.0, 0.0 );
			return;
		}
		else if ( lineFollower.sensor2.Get() )
			drive.TankDrive( -0.5 * speed, -0.5 * speed );
		else if ( lineFollower.sensor3.Get() && lineFollower.sensor1.Get() )
		{
			drive.TankDrive( -0.5, 0.5 );
			Wait( 0.2 );
			pastY = true;
		}
		else if ( lineFollower.sensor3.Get() )
			drive.TankDrive( -0.5 * speed, 0.1 * speed );
		else if ( lineFollower.sensor1.Get() )
			drive.TankDrive( 0.1 * speed, -0.5 * speed );
		
		if ( ultrasonic.IsRangeValid() )
		{
			if ( ultrasonic.GetRangeInches() < 36.0 )
				speed = 0.5;
			else
				speed = 1.0;
		}
		
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
