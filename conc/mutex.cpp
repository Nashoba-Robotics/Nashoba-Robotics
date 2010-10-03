/*
 *	mutex.cpp
 *	Nashoba Robotics 2011
 *
 *	Copyright 2010 RC Howe
 *	All Rights Reserved
 */

#include "mutex.h"
#include <iostream>
#include <pthread.h>

using namespace nr::conc;

mutex::mutex() throw ( thread_exception )
{
	if ( 0 != ::pthread_mutex_init( &raw_mutex, NULL ) )
		throw thread_exception( "Unable to create mutex" );
}

mutex::~mutex() throw ()
{
	if ( 0 != ::pthread_mutex_destroy( &raw_mutex ) )
		std::cerr << "Unable to destroy mutex" << std::endl;
}

void mutex::acquire() throw ( thread_exception )
{
	if ( 0 != ::pthread_mutex_lock( &raw_mutex ) )
		throw thread_exception( "Unable to lock mutex" );
}

void mutex::release() throw ( thread_exception )
{
	if ( 0 != ::pthread_mutex_unlock( &raw_mutex ) )
		throw thread_exception( "Unable to unlock mutex" );
}

bool mutex::trylock() throw ()
{
	return (0 == ::pthread_mutex_trylock( &raw_mutex ));
}

mutex::lock::lock( mutex &m ) throw ( thread_exception )
:	mut( m ),
 	locked( true )
{
	mut.acquire();
}

mutex::lock::~lock() throw ( thread_exception )
{
	if ( locked )
		mut.release();
}

void mutex::lock::release() throw ( thread_exception )
{
	locked = false;
	mut.release();
}

