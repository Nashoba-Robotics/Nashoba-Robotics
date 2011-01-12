/*
 *	Robot.cpp
 *	Nashoba Robotics 2011
 */

#include "Robot.h"
 
Robot :: Robot( void )
:	motor1( 4, 1 ),
	motor2( 4, 2 ),
	motor3( 4, 3 ),
	motor4( 4, 4 ),
	drive( motor1, motor2, motor3, motor4 )
{
}

void Robot :: Autonomous( void )
{
	GetWatchdog().SetEnabled( false );

	// Drive forward for two seconds
	drive.TankDrive( 1.0f, 1.0f );
	Wait( 2.0f );
	drive.TankDrive( 0.0f, 0.0f );
}

void Robot :: OperatorControl( void )
{
	GetWatchdog().SetEnabled( true );
	
	while ( IsOperatorControl() )
	{
		drive.TankDrive( joy1.GetY(), joy2.GetY() );
		Wait( kMainRunLoopDelta );
	}
}