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
			observable_jaguar( Jaguar& ) throw ();

			const std::string value() throw ();

			bool setable() const throw () { return true; }
			void set( float value ) throw () { device.Set( value ); }

		private:
			Jaguar &device;
		};
		
		class observable_encoder : public observable
		{
		public:
			observable_encoder( Encoder & ) throw ();
			
			const std::string value() throw ();
			bool setable() const throw () { return false; }
			void set( float value ) throw () { }
			
		private:
			Encoder &device;
		};
		
		class observable_digitalinput : public observable
		{
		public:
			observable_digitalinput( DigitalInput & ) throw ();
			
			const std::string value() throw ();
			bool setable() const throw () { return false; }
			void set( float value ) throw () { }
			
		private:
			DigitalInput &device;
		};
	}
}
