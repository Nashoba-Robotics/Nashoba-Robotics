/*
 *  observable_wpi.cpp
 *  Nashoba Robotics 2011
 *
 *  Copyright 2010 RC Howe
 *  All Rights Reserved
 */

#include "observable_wpi.h"

#ifdef WPILIB

using namespace nr::conc;

observable_jaguar::observable_jaguar( const Jaguar &j )
: device( j )
{
}

const std::string observable_jaguar::value() const
{
	char out[6];
	::snprintf( out, sizeof out, "%f", device.Get() );

	return std::string( out );
}

const std::string observable_jaguar::identifier() const
{
	return "";
}

#endif
