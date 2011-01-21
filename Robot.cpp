/*
 *	Robot.cpp
 *	Nashoba Robotics 2011
 */

#include "Robot.h"
 
Robot :: Robot( void )
:	joy1( 1 ), joy2( 2 ),
	drive( 1, 2, 3, 4 ),
	lineFollower( 1, 2, 3, 4 ) // FIXME: Not actual #s
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
	
	while ( IsOperatorControl() )
	{
		drive.TankDrive( joy1.GetY(), joy2.GetY() );
		Wait( kMainRunLoopDelta );
	}
}