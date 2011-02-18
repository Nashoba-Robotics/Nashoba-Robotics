/*
 *	LineFollower.cpp
 *	Nashoba Robotics 2011
 *
 *	Copyright 2011 RC Howe
 *	All Rights Reserved
 */

#include "LineFollower.h"
#include <cmath>

#define NR_USE_WPILIB
#include "diag/DiagnosticsCenter.h"
#include "diag/ObservableWPI.h"
#undef NR_USE_WPILIB

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
	nr::diag::DiagnosticsCenter &diag = nr::diag::SharedDiagnosticsCenter();
	diag.RegisterDevice( new nr::diag::ObservableDigitalInput( sensor1 ), "Left Sensor" );
	diag.RegisterDevice( new nr::diag::ObservableDigitalInput( sensor2 ), "Center Sensor" );
	diag.RegisterDevice( new nr::diag::ObservableDigitalInput( sensor3 ), "Right Sensor" );
}
