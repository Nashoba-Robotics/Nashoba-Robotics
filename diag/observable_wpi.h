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
		class observable_jaguar : public observable
		{
		public:
			observable_jaguar( const Jaguar& ) throw ();

			const std::string value() const throw ();

			bool setable() const throw () { return true; }
			void set( float value ) throw () { device.Set( value ); }

		private:
			Jaguar device;
		};
		
		class observable_can_jaguar : public observable
		{
		public:
			observable_can_jaguar( const CANJaguar& ) throw ();
			
			const std::string value() const throw ();
			
			bool setable() const throw () { return true; }
			void set( float value ) throw () { device.Set( value ); }
			
		private:
			Jaguar device;
		};
	}
}
