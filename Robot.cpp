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
 	manipulatorJoystick( 3 ),
	drive( 1, 2, 3, 4, 4, 4, 4, 5, 4, 6, 4, 7 ),
	lineFollower( 1, 2, 3, 4, 4, 14, 4, 13 ),
	ultrasonic( 4, 1, 4, 2 )
	manipulator( manipulatorJoystick ),
	lineFollower( 1, 2, 3, 4 ),
	manipulatorThread( &manipulator ),
	//relay(4,2,Relay::kForwardOnly)
	compressor(4, 12, 4, 2),
	ultrasonic(13)
{
	manipulatorThread.Start();
	compressor.Start();
	//ultrasonic.SetEnabled(true);
	//relay.Set(Relay::kOn);
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
		//printf( "%d", compressor.GetPressureSwitchValue());
		//printf("%f\n",ultrasonic.GetRangeInches());
		//ultrasonic.Ping();
		GetWatchdog().Feed();
		ultrasonic.Pulse(.001);
		Wait( kMainRunLoopDelta );
		
	}
}
