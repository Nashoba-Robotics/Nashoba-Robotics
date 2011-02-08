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
		class ObservableSpeedController : public Observable
		{
		public:
			ObservableSpeedController( SpeedController& ) throw ();
			
			const std::string Value() throw ();
			
			bool Setable() const throw () { return true; }
			void Set( float value ) throw () { device.Set( value ); }

		private:
			SpeedController &device;
		};
		
		class ObservableEncoder : public Observable
		{
		public:
			ObservableEncoder( Encoder & ) throw ();
			
			const std::string Value() throw ();						
			bool Setable() const throw () { return false; }
			
		private:
			Encoder &device;
		};
		
		class ObservableDigitalInput : public Observable
		{
		public:
			ObservableDigitalInput( DigitalInput & ) throw ();

			const std::string Value() throw ();
			bool Setable() const throw () { return false; }
			
		private:
			DigitalInput &device;
		};
		
		class ObservableJaguarCurrent : public Observable
		{
		public:
			ObservableJaguarCurrent( CANJaguar & ) throw ();

			const std::string Value() throw ();
			bool Setable() const throw () { return false; }
			
		private:
			CANJaguar &device;
		};
	}
}
