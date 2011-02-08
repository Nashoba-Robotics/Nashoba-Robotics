/*
 *  Mutex.h
 *  Nashoba Robotics 2011
 *
 *  Copyright 2010 RC Howe
 *  All Rights Reserved
 */

#pragma once

#include "ThreadException.h"
#include <pthread.h>

#define SYNCHRONIZED(MUTEX) class nr::conc::Mutex::Lock MUTEX##_macro_lock = MUTEX;\
	for ( ; (MUTEX##_macro_lock) ;\
		MUTEX##_macro_lock.Release() )

namespace nr {
	namespace conc
	{
		/**
		 *  A class representing a mutex. This is an abstraction over a
		 *  pthread_mutex
		 */
		class Mutex
		{
		public:
			/**
			 * Creates a new mutex
			 */
			Mutex() throw ( ThreadException );

			/**
			 * Destroys a mutex, unlocking if necessary
			 */
			~Mutex() throw ();

			/**
			 *  A lock on a mutex, in an RAII-compatible fashion
			 */
			class Lock
			{
			public:
				/**
				 *  Creates a new lock on mutex m
				 *
				 *	@param m The mutex to lock
				 */
				Lock( Mutex &m ) throw ( ThreadException );

				/**
				 *  Destroys this lock, releasing the mutex if necessary
				 */
				~Lock() throw ( ThreadException );

				/**
				 *	@return Whether or not the lock is locked
				 */
				operator bool () const throw () { return locked; }

				/**
				 *	Releases the lock on this mutex
				 */
				void Release() throw ( ThreadException );

			private:
				Mutex &mut;
				bool locked;
			};

			/**
			 *  Acquires a lock on the mutex
			 */
			void Acquire() throw ( ThreadException );

			/**
			 *  Releases an acquired lock on the mutex
			 */
			void Release() throw ( ThreadException );

			/**
			 *  Trys to lock the mutex
			 *
			 *  @return true if successfully locked, false otherwise
			 */
			bool TryLock() throw ();

		private:
			pthread_mutex_t raw_mutex;
		};
	}
}
