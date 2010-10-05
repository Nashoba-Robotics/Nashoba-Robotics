/*
 *  diagnostics_center.h
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
		class observable;
		
		/**
		 *	A singleton class representing a diagnostics center and server. Individual
		 *	inputs and outputs register themselves with the diagnostics center by using
		 *	the `register_device' method. Devices must provide a unique identifier when
		 *	registering themselves, which is sent back to the console.
		 *
		 *	Any device that wishes to register itself should either be a subclass of
		 *	the `observable' class or should implement a wrapper class that descends
		 *	from `observable'. Wrappers for common WPILib classes are available in the
		 *	observable_wpi.h header.
		 */
		class diagnostics_center : private nr::conc::thread::entry
		{
		public:
			/**
			 *	Registers a given device and unique identifier pair with the diagnostics
			 *	center. See the class description for more detail.
			 */
			void register_device( observable &device, const std::string &identifier ) throw ();
			
			/**
			 *	Unregisters the device with the given identifier from the server
			 */
			void unregister_device( const std::string &identifier ) throw ();
			
			/**
			 *	Gets the shared diagnostics center instance
			 */
			static diagnostics_center& get_shared_instance() throw ();

		private:
			std::vector<observable> devices;
			nr::conc::mutex devices_mutex;

			// Threading Stuff
			void run( void *userinfo = NULL ) throw ();
			nr::conc::thread thread;
			bool running;

			// Constructors and destructors
			diagnostics_center() throw ();
			virtual ~diagnostics_center() throw ();

			diagnostics_center( const diagnostics_center& );
			diagnostics_center& operator=( const diagnostics_center& );

			void handle_client( nr::net::socket &client );
		};
	}
}
