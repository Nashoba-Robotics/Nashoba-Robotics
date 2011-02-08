/*
 *	Mutex.cpp
 *	Nashoba Robotics 2011
 *
 *	Copyright 2010 RC Howe
 *	All Rights Reserved
 */

#include "Mutex.h"
#include <iostream>
#include <pthread.h>

using namespace nr::conc;

Mutex::Mutex() throw ( ThreadException )
{
	if ( 0 != ::pthread_mutex_init( &raw_mutex, NULL ) )
		throw ThreadException( "Unable to create mutex" );
}

Mutex::~Mutex() throw ()
{
	if ( 0 != ::pthread_mutex_destroy( &raw_mutex ) )
		std::cerr << "Unable to destroy mutex" << std::endl;
}

void Mutex::Acquire() throw ( ThreadException )
{
	if ( 0 != ::pthread_mutex_lock( &raw_mutex ) )
		throw ThreadException( "Unable to lock mutex" );
}

void Mutex::Release() throw ( ThreadException )
{
	if ( 0 != ::pthread_mutex_unlock( &raw_mutex ) )
		throw ThreadException( "Unable to unlock mutex" );
}

bool Mutex::TryLock() throw ()
{
	return (0 == ::pthread_mutex_trylock( &raw_mutex ));
}

Mutex::Lock::Lock( Mutex &m ) throw ( ThreadException )
:	mut( m ),
 	locked( true )
{
	mut.Acquire();
}

Mutex::Lock::~Lock() throw ( ThreadException )
{
	if ( locked )
		mut.Release();
}

void Mutex::Lock::Release() throw ( ThreadException )
{
	locked = false;
	mut.Release();
}

