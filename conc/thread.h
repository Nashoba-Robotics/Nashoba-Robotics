/*
 *  thread.h
 *  Nashoba Robotics 2011
 *
 *  Copyright 2010 RC Howe
 *  All Rights Reserved
 */

#pragma once

#include "thread_exception.h"
#include <pthread.h>

namespace nr {
	namespace conc
	{
		/**
		 *	A class describing a thread
		 */
		class thread
		{
		public:
			/**
			 *	A functor class describing an entry point for a thread
			 */
			class entry
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
				virtual void run( void *userinfo = NULL ) throw () = 0;
			};

			/**
			 *	A specific thread entry point describing a function entry
			 */
			class function_entry : public entry
			{
			public:
				/**
				 *  Creates a new function entry with the given function to use.
				 *
				 *	@param fn The function to be contained in the class
				 */
				function_entry( void(*fn)(void*) ) throw () : function( fn ) {}

				void run( void *userinfo ) throw () { function( userinfo ); }

			private:
				void(*function)(void*);
			};

			/**
			 *  Creates a new thread with the given entry point.
			 *
			 *	@param en Entry Point
			 */
			thread( entry *en ) throw ();

			/**
			 *	Destroys a thread, cleaning up any resources used
			 */
			virtual ~thread() throw ();

			/**
			 *  Starts a thread
			 *
			 *	@param userinfo Information to be passed to the entry point
			 */
			void start( void *userinfo = NULL ) throw ( thread_exception );

			/**
			 *  Joins the given thread object to the calling thread.
			 *
			 *	@return The returned value from the thread::exit() method.
			 */
			void* join() throw ( thread_exception );

			/**
			 *  Sleeps the calling thread. Note that this sleeps across
			 *  interrupt signals. If you need this functionallity, use this,
			 *  otherwise use sleep().
			 *
			 *	@param secs Time to sleep, in seconds
			 */
			static void sleep( unsigned int secs ) throw ();

			/**
			 *  Exits the current thread, returning the passed value
			 *
			 *  @param retval The value to return to a thread joined to this
			 *  one.
			 */
			static void exit( void *retval = NULL ) throw ();

		private:
			pthread_t raw_thread;
			entry *entry_point;

			// Disallow copy and assign
			thread( thread& );
			thread& operator=( thread& );

			// This is the internal start point for the thread
			static void* entry_function( void *args );
		};
	}
}
