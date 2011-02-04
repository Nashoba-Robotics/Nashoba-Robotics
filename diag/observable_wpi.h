/*
 *  observable_wpi.h
 *  Nashoba Robotics 2011
 *
 *  Copyright 2010 RC Howe
 *  All Rights Reserved
 */

#pragma once

#include "WPILib.h"
#include "observable.h"

namespace nr {
	namespace diag
	{
		class observable_speed_controller : public observable
		{
		public:
			observable_speed_controller( const SpeedController& ) throw ();
			
			const std::string value() throw ();
			
			bool setable() const throw () { return true; }
			void set( float value ) throw () { device.Set( value ); }
			
		private:
			SpeedController &device;
		};
		
		// For backwards compatibility
		typedef observable_speed_controller observable_jaguar;
		typedef observable_speed_controller observable_can_jaguar;
	}
}
