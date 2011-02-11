/*
 *  observable_wpi.cpp
 *  Nashoba Robotics 2011
 *
 *  Copyright 2010 RC Howe
 *  All Rights Reserved
 */

#include "observable_wpi.h"

#define WPILIB
#ifdef WPILIB

using namespace nr::diag;

observable_speed_controller::observable_speed_controller( SpeedController &d ) throw ()
:	device( d )
{
}

const std::string observable_speed_controller::value() throw ()
{
	static char out[6];
	memset( out, 0, sizeof( out ) );
	::snprintf( out, sizeof out, "%f", device.Get() );
	
	return std::string( out );
}

observable_encoder::observable_encoder( Encoder &e ) throw ()
:	device( e )
{
}

const std::string observable_encoder::value() throw ()
{
	char out[10];
	::snprintf( out, sizeof out, "%2f", device.GetDistance() );
	
	return std::string( out );
}

observable_digitalinput::observable_digitalinput( DigitalInput &i ) throw ()
:	device( i )
{
}

const std::string observable_digitalinput::value() throw ()
{
	if ( device.Get() )
		return "True";
	return "False";
}

observable_jaguar_current::observable_jaguar_current( CANJaguar &j ) throw ()
:	device( j )
{
}

#endif
