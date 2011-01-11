/*
 *  Robot.cpp
 *  Nashoba Robotics 2011
 *
 *  Copyright 2011 RC Howe
 *  All Rights Reserved
 */

#include "Robot.h"

Robot :: Robot()
:	primaryJoystick( 1 ),
	secondaryJoystick( 2 )
{
}

void Robot :: Autonomous( void )
{
	GetWatchdog().SetEnabled( false );
	
	// TODO: Implement operations in autonomous mode
}

void Robot :: OperatorControl( void )
{
	GetWatchdog().SetEnabled( true );
	GetWatchdog().SetTimeout( 0.1  );
	
	while ( IsOperatorControl() )
	{
		// TODO: Implement operations in teleoperated mode
		Wait( 0.005 );
	}
}
