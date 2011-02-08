/*
 *  Observable.h
 *  Nashoba Robotics 2011
 *
 *  Copyright 2010 RC Howe
 *  All Rights Reserved
 */

#pragma once

#include <iostream>
#include "DiagnosticsCenter.h"

namespace nr
{
	namespace diag
	{
		class DiagnosticsCenter;
		
		class Observable
		{
		public:
			Observable( const std::string &ident = "Device" )
				: identifier( ident ) {}
			virtual ~Observable();
		
			virtual const std::string Value() throw () = 0;

			virtual bool Setable() throw () { return false; }
			virtual void Set( float value ) throw () {}
		
		private:
			std::string identifier;
			
			friend class DiagnosticsCenter;
		};
	}
}
