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

observable_speed_controller::observable_speed_controller( const SpeedController &d )
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

#endif
