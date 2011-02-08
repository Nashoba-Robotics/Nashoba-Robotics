/*
 *  DiagnosticsCenter.h
 *  Nashoba Robotics 2011
 *
 *  Copyright 2010 RC Howe
 *  All Rights Reserved
 */

#pragma once

#include <vector>
#include "../conc/thread.h"
#include "../conc/mutex.h"
#include "../net/socket.h"
#include "observable.h"

namespace nr{
	namespace diag
	{
		class Observable;
		class DiagnosticsCenter;
		
		/**
		 *	Gets the shared diagnostics center
		 *	@return The shared diagnostics center instance
		 */
		DiagnosticsCenter& SharedDiagnosticsCenter();
		
		/**
		 *	@brief A diagnostics class that takes observable objects and hosts a web server with values
		 *
		 *	A singleton class representing a diagnostics center and server. Individual
		 *	inputs and outputs register themselves with the diagnostics center by using
		 *	the `register_device' method. Devices must provide a unique identifier when
		 *	registering themselves, which is sent back to the console.
		 *
		 *	Any device that wishes to register itself should either be a subclass of
		 *	the `observable' class or should implement a wrapper class that descends
		 *	from `observable'. Wrappers for common WPILib classes are available in the
		 *	ObservableWPI.h header.
		 */
		class DiagnosticsCenter : private nr::conc::thread::entry
		{
		public:
			/**
			 *	Registers a given device and unique identifier pair with the diagnostics
			 *	center. See the class description for more detail.
			 */
			void RegisterDevice( Observable &device, const std::string &identifier ) throw ();
			
			/**
			 *	Registers a given device and unique identifier pair with the diagnostics
			 *	center. See the class description for more detail.
			 */
			void RegisterDevice( Observable *device, const std::string &identifier ) throw ();
			
			/**
			 *	Gets the shared diagnostics center instance
			 */
			static DiagnosticsCenter& GetSharedInstance() throw ();

		private:
			std::vector<Observable*> devices;
			nr::conc::mutex devices_mutex;

			// Threading Stuff
			void Run( void *userinfo = NULL ) throw ();
			nr::conc::thread thread;
			bool running;

			// Constructors and destructors
			DiagnosticsCenter() throw ();
			virtual ~DiagnosticsCenter() throw ();

			DiagnosticsCenter( const DiagnosticsCenter& );
			DiagnosticsCenter& operator=( const DiagnosticsCenter& );

			void HandleClient( nr::net::socket &client );
		};
	}
}
