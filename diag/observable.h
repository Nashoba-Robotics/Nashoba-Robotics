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
		
		/**
		 *	@brief An abstract class for devices to be used in the diagnostics center
		 */
		class observable
		{
		public:
			/**
			 *	Creates a new observable device
			 *	@param ident The identifier to use for the observable device
			 */
			observable( const std::string &ident = "Device" )
				: identifier( ident ) {}
			virtual ~observable() {}
			
			/**
			 *	Get a string representing the current value of the device
			 */
			virtual const std::string value() throw () = 0;

			/**
			 *	Returns whether or not the device is `settable' from the diagnostics center or not
			 *	If true, it should override the set method.
			 *	@return Whether or not the device is settable
			 */
			virtual bool setable() throw () { return false; }
			
			/**
			 *	Sets the device to a new value
			 *	@param value The new value to set the device to (between -1.0 and 1.0)
			 */
			virtual void set( float value ) throw () {}
		
		private:
			std::string identifier;
			
			friend class diagnostics_center;
		};
	}
}
