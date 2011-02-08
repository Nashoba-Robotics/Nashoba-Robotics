/*
 *  ObservableWPI.cpp
 *  Nashoba Robotics 2011
 *
 *  Copyright 2010 RC Howe
 *  All Rights Reserved
 */

#include "ObservableWPI.h"

#define WPILIB
#ifdef WPILIB

using namespace nr::diag;

ObservableSpeedController::ObservableSpeedController( SpeedController &d ) throw ()
:	device( d )
{
}

const std::string ObservableSpeedController::Value() throw ()
{
	static char out[6];
	memset( out, 0, sizeof( out ) );
	::snprintf( out, sizeof out, "%f", device.Get() );
	
	return std::string( out );
}

ObservableEncoder::ObservableEncoder( Encoder &e ) throw ()
:	device( e )
{
}

const std::string ObservableEncoder::Value() throw ()
{
	char out[10];
	::snprintf( out, sizeof out, "%2f", device.GetDistance() );
	
	return std::string( out );
}

ObservableDigitalInput::ObservableDigitalInput( DigitalInput &i ) throw ()
:	device( i )
{
}

const std::string ObservableDigitalInput::Value() throw ()
{
	if ( device.Get() )
		return "True";
	return "False";
}

ObservableJaguarCurrent::ObservableJaguarCurrent( CANJaguar &j ) throw ()
:	device( j )
{
}

#endif