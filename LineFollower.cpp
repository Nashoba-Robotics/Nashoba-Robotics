/*
 *	LineFollower.cpp
 *	Nashoba Robotics 2011
 *
 *	Copyright 2011 RC Howe
 *	All Rights Reserved
 */

#include "LineFollower.h"
#include <cmath>
#include "diag/diagnostics_center.h"
#include "diag/observable_wpi.h"

LineFollower :: LineFollower( UINT8 sensor1Channel,
			  UINT8 sensor2Channel,
			  UINT8 sensor3Channel,
			  UINT8 gyroChannel )
:	sensor1( sensor1Channel ),
	sensor2( sensor2Channel ),
	sensor3( sensor3Channel )
{
	InitializeDiagnostics();
}

LineFollower :: LineFollower( UINT8 sensor1Slot, UINT8 sensor1Channel,
			  UINT8 sensor2Slot, UINT8 sensor2Channel,
			  UINT8 sensor3Slot, UINT8 sensor3Channel,
			  UINT8 gyroSlot, UINT8 gyroChannel )
:	sensor1( sensor1Slot, sensor1Channel ),
	sensor2( sensor2Slot, sensor2Channel ),
	sensor3( sensor3Slot, sensor3Channel )
//	gyroscope( gyroSlot, gyroChannel )
{
	InitializeDiagnostics();
}

void LineFollower :: WaitUntilLineDetected()
{
	while ( not IsLineDetected() )
		Wait( LineFollower::kWaitDelta );
}

bool LineFollower :: WaitUntilLineDetectedOrTimeout( double timeout )
{
	double time_remaining = timeout;
	while ( time_remaining > 0 )
	{
		Wait( LineFollower::kWaitDelta );
		time_remaining -= LineFollower::kWaitDelta;
		
		if ( IsLineDetected() )
			return true;
	}
	
	return false;
}

bool LineFollower :: IsLineDetected()
{
	return sensor2.Get();
}

void LineFollower :: WaitUntilFacing( FieldSide side )
{
	/*
	float angle = side == kScoringSide ? 0 : 180;
	while ( fabs( gyroscope.GetAngle() - angle ) > kAngleError )
		Wait( kWaitDelta );
	*/
}

void LineFollower :: InitializeDiagnostics()
{
	nr::diag::diagnostics_center &diag = nr::diag::diagnostics_center::get_shared_instance();

	diag.register_device( new nr::diag::observable_digitalinput( sensor1 ), "Left Line Sensor" );
	diag.register_device( new nr::diag::observable_digitalinput( sensor2 ), "Center Line Sensor" );
	diag.register_device( new nr::diag::observable_digitalinput( sensor3 ), "Right Line Sensor" );
}
