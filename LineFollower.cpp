/*
 *	LineFollower.cpp
 *	Nashoba Robotics 2011
 *
 *	Copyright 2011 RC Howe
 *	All Rights Reserved
 */

#include "LineFollower.h"
#include <cmath>

LineFollower :: LineFollower( UINT8 sensor1Channel,
			  UINT8 sensor2Channel,
			  UINT8 sensor3Channel,
			  UINT8 gyroChannel )
:	sensor1( sensor1Channel ),
	sensor2( sensor2Channel ),
	sensor3( sensor3Channel ),
	gyroscope( gyroChannel )
{
}

LineFollower :: LineFollower( UINT8 sensor1Slot, UINT8 sensor1Channel,
			  UINT8 sensor2Slot, UINT8 sensor2Channel,
			  UINT8 sensor3Slot, UINT8 sensor3Channel,
			  UINT8 gyroSlot, UINT8 gyroChannel )
:	sensor1( sensor1Slot, sensor1Channel ),
	sensor2( sensor2Slot, sensor2Channel ),
	sensor3( sensor3Slot, sensor3Channel ),
	gyroscope( gyroSlot, gyroChannel )
{
}

void LineFollower :: WaitUntilLineDetected()
{
	while ( not IsLineDetected() )
		Wait( LineFollower::kWaitDelta );
}

bool LineFollower :: WaitUntilLineDetectedOrTimeout( double timeout )
{
	time_t start_time = time( NULL );
	while ( true )
	{
		Wait( LineFollower::kWaitDelta );
		
		if ( IsLineDetected() )
			return true;
		if ( difftime( time( NULL ), start_time ) < timeout )
			return false;
	}
}

bool LineFollower :: IsLineDetected()
{
	return false;
}

void LineFollower :: WaitUntilFacing( FieldSide side )
{
	float angle = side == kScoringSide ? 0 : 180;
	while ( fabs( gyroscope.GetAngle() - angle ) > kAngleError )
		Wait( kWaitDelta );
}
