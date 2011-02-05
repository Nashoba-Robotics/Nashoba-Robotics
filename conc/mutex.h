/*
 *  mutex.h
 *  Nashoba Robotics 2011
 *
 *  Copyright 2010 RC Howe
 *  All Rights Reserved
 */

#pragma once

#include "thread_exception.h"
#include <pthread.h>

#define SYNCHRONIZED(MUTEX) class nr::conc::mutex::lock MUTEX##_macro_lock = MUTEX;\
	for ( ; (MUTEX##_macro_lock) ;\
		MUTEX##_macro_lock.release() )

namespace nr {
	namespace conc
	{
		/**
		 *  @brief A class representing a mutex. This is an abstraction over a pthread_mutex
		 */
		class mutex
		{
		public:
			/**
			 * Creates a new mutex
			 */
			mutex() throw ( thread_exception );

			/**
			 * Destroys a mutex, unlocking if necessary
			 */
			~mutex() throw ();

			/**
			 *  @brief A lock on a mutex, in an RAII-compatible fashion
			 */
			class lock
			{
			public:
				/**
				 *  Creates a new lock on mutex m
				 *
				 *	@param m The mutex to lock
				 */
				lock( mutex &m ) throw ( thread_exception );

				/**
				 *  Destroys this lock, releasing the mutex if necessary
				 */
				~lock() throw ( thread_exception );

				/**
				 *	@return Whether or not the lock is locked
				 */
				operator bool () const throw () { return locked; }

				/**
				 *	Releases the lock on this mutex
				 */
				void release() throw ( thread_exception );

			private:
				mutex &mut;
				bool locked;
			};

			/**
			 *  Acquires a lock on the mutex
			 */
			void acquire() throw ( thread_exception );

			/**
			 *  Releases an acquired lock on the mutex
			 */
			void release() throw ( thread_exception );

			/**
			 *  Trys to lock the mutex
			 *
			 *  @return true if successfully locked, false otherwise
			 */
			bool trylock() throw ();

		private:
			pthread_mutex_t raw_mutex;
		};
	}
}
