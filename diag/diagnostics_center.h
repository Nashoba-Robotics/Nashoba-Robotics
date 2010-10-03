/*
 *  diagnostics_center.h
 *  Nashoba Robotics 2011
 *
 *  Copyright 2010 RC Howe
 *  All Rights Reserved
 */

#pragma once

#include "../conc/thread.h"
#include "../conc/mutex.h"
#include "../net/socket.h"
#include "observable.h"
#include <vector>

namespace nr{
	namespace diag
	{
		class diagnostics_center : private nr::conc::thread::entry
		{
		public:
			void register_device( observable &device ) throw ();
			void register_device( observable *device ) throw ();

			static diagnostics_center& get_shared_instance() throw ();

		private:
			std::vector<observable*> devices;
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
