/*
 *  Thread.h
 *  Nashoba Robotics 2011
 *
 *  Copyright 2010 RC Howe
 *  All Rights Reserved
 */

#pragma once

#include "ThreadException.h"
#include <pthread.h>

namespace nr {
	namespace conc
	{
		/**
		 *	@brief A class describing a thread
		 */
		class Thread
		{
		public:
			/**
			 *	@brief A functor class describing an entry point for a thread
			 */
			class Entry
			{
			public:
				/**
				 *  The run function. This is the entry point that runs when the
				 *  thread is run.
				 *
				 *  @param userinfo Any extra info to be passed to the function,
				 *  taken from the first argument to the thread::start(void*)
				 *  method.
				 */
				virtual void Run( void *userinfo = NULL ) throw () = 0;
			};

			/**
			 *	@brief A specific thread entry point describing a function entry
			 */
			class FunctionEntry : public Entry
			{
			public:
				/**
				 *  Creates a new function entry with the given function to use.
				 *
				 *	@param fn The function to be contained in the class
				 */
				FunctionEntry( void(*fn)(void*) ) throw () : function( fn ) {}

				void Run( void *userinfo ) throw () { function( userinfo ); }

			private:
				void(*function)(void*);
			};

			/**
			 *  Creates a new thread with the given entry point.
			 *
			 *	@param en Entry Point
			 */
			Thread( Entry *en ) throw ();

			/**
			 *	Destroys a thread, cleaning up any resources used
			 */
			virtual ~Thread() throw ();

			/**
			 *  Starts a thread
			 *
			 *	@param userinfo Information to be passed to the entry point
			 */
			void Start( void *userinfo = NULL ) throw ( ThreadException );

			/**
			 *  Joins the given thread object to the calling thread.
			 *
			 *	@return The returned value from the thread::exit() method.
			 */
			void* Join() throw ( ThreadException );

			/**
			 *  Sleeps the calling thread. Note that this sleeps across
			 *  interrupt signals. If you need this functionallity, use this,
			 *  otherwise use sleep().
			 *
			 *	@param secs Time to sleep, in seconds
			 */
			static void Sleep( unsigned int secs ) throw ();

			/**
			 *  Exits the current thread, returning the passed value
			 *
			 *  @param retval The value to return to a thread joined to this
			 *  one.
			 */
			static void Exit( void *retval = NULL ) throw ();
			
			/**
			 *	Kills the given thread, using SIGKILL by default.
			 *	
			 *	@param signal The signal to pass to the killed thread.
			 */
			void Stop( int signal = SIGKILL );

		private:
			pthread_t raw_thread;
			Entry *entry_point;

			// Disallow copy and assign
			Thread( Thread& );
			Thread& operator=( Thread& );

			// This is the internal start point for the thread
			static void* entry_function( void *args );
		};
	}
}
