/*
 *	LineFollower.cpp
 *	Nashoba Robotics 2011
 *
 *	Copyright 2011 RC Howe
 *	All Rights Reserved
 */

#include "LineFollower.h"

LineFollower( uint8_t sensor1Channel,
			  uint8_t sensor2Channel,
			  uint8_t sensor3Channel,
			  uint8_t gyroChannel )
:	sensor1( sensor1Channel ),
	sensor2( sensor2Channel ),
	sensor3( sensor3Channel ),
	gyroscope( gyroChannel )
{
}

LineFollower( uint8_t sensor1Slot, uint8_t sensor1Channel,
			  uint8_t sensor2Slot, uint8_t sensor2Channel,
			  uint8_t sensor3Slot, uint8_t sensor3Channel,
			  uint8_t gyroSlot, uint8_t gyroChannel )
:	sensor1( sensor1Slot, sensor1Channel ),
	sensor2( sensor2Slot, sensor2Channel ),
	sensor3( sensor3Slot, sensor3Channel ),
	gyroscope( gyroSlot, gyroChannel )
{
}

LineFollower( LightSensor &s1,
			  LightSensor &s2,
			  LightSensor &s3,
			  Gyro &gyro )
:	sensor1( s1 ),
	sensor2( s2 ),
	sensor3( s3 ),
	gyroscope( gyro )
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
