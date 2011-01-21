/*
 *  observable.h
 *  Nashoba Robotics 2011
 *
 *  Copyright 2010 RC Howe
 *  All Rights Reserved
 */

#pragma once

#include <iostream>
#include "diagnostics_center.h"

namespace nr
{
	namespace diag
	{
		class diagnostics_center;
		
		class observable
		{
		public:
			observable( const std::string &ident = "Device" )
				: identifier( ident ) {}
			virtual ~observable() {}
		
			virtual const std::string value() const throw () = 0;

			virtual bool setable() const throw () { return false; }
			virtual void set( float value ) throw () {}
		
		private:
			std::string identifier;
			
			friend class diagnostics_center;
		};
	}
}
