/*
 *  observable_wpi.h
 *  Nashoba Robotics 2011
 *
 *  Copyright 2010 RC Howe
 *  All Rights Reserved
 */

#pragma once

#ifdef WPILIB_H_

#include "observable.h"
#include "WPILib.h"

namespace nr {
	namespace conc
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
	}
}

#endif
