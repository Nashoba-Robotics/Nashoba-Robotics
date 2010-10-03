/*
 *  observable.h
 *  Nashoba Robotics 2011
 *
 *  Copyright 2010 RC Howe
 *  All Rights Reserved
 */

#pragma once

#include <iostream>

namespace nr
{
	namespace diag
	{
		class observable
		{
		public:
			virtual const std::string value() const throw () = 0;
			virtual const std::string identifier() const throw () = 0;

			virtual bool setable() const throw () { return false; }
			virtual void set( float value ) throw () {}
		};
	}
}
