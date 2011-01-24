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

observable_jaguar::observable_jaguar( Jaguar &j ) throw ()
: device( j )
{
}

const std::string observable_jaguar::value() throw ()
{
	char out[6];
	::snprintf( out, sizeof out, "%f", device.Get() );
	
	return std::string( out );
}

observable_encoder::observable_encoder( Encoder &e ) throw ()
:	device( e )
{
}

const std::string observable_encoder::value() throw ()
{
	char out[6];
	::snprintf( out, sizeof out, "%f", device.Get() );
	
	return std::string( out );
}

observable_digitalinput::observable_digitalinput( DigitalInput &i ) throw ()
:	device( i )
{
}

const std::string observable_digitalinput::value() throw ()
{
	if ( device.Get() )
		return "1";
	return "0";
}

#endif
