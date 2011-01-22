/*
 *  observable_wpi.cpp
 *  Nashoba Robotics 2011
 *
 *  Copyright 2010 RC Howe
 *  All Rights Reserved
 */

#include "observable_wpi.h"

#ifdef WPILIB

using namespace nr::diag;

observable_jaguar::observable_jaguar( const Jaguar &j )
: device( j )
{
}

const std::string observable_jaguar::value()
{
	char out[6];
	::snprintf( out, sizeof out, "%f", device.Get() );
	
	return std::string( out );
}

observable_can_jaguar::observable_can_jaguar( const CANJaguar &j )
: device( j )
{
}

const std::string observable_can_jaguar::value()
{
	char out[6];
	::snprintf( out, sizeof out, "%f", device.Get() );
	
	return std::string( out );
}

#endif
