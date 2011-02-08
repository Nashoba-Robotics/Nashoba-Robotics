/*
 *  Thread.cpp
 *  Nashoba Robotics 2011
 *
 *  Copyright 2010 RC Howe
 *  All Rights Reserved
 */

#include "thread.h"
#include <ctime>

using namespace nr::conc;

class entry_data
{
public:
	entry_data( Thread::Entry *e, void *a ) : thread_entry( e ), args( a ) {}

	Thread::Entry *thread_entry;
	void *args;
};

Thread::Thread( Entry *en ) throw ()
: entry_point( en )
{
};

Thread::~Thread() throw ()
{
}

void Thread::Start( void *userinfo ) throw ( ThreadException )
{
	entry_data *ed = new entry_data( entry_point, userinfo );
	if ( 0 != ::pthread_create( &raw_thread, NULL,
			Thread::entry_function, (void *) ed ) )
	{
		throw ThreadException( "Unable to create thread" );
	}
}

void* Thread::Join() throw ( ThreadException )
{
	void *ptr = NULL;
	if ( 0 != ::pthread_join( raw_thread, &ptr ) )
		throw ThreadException( "Unable to join thread" );

	return ptr;
}

void Thread::Sleep( unsigned int secs ) throw ()
{
	struct timespec sleep_time, remaining_time;
	sleep_time.tv_sec = secs;
	
	nanosleep( &sleep_time, &remaining_time );
}

void Thread::Stop( int signal )
{
	pthread_kill( raw_thread, signal );
}

void Thread::Exit( void *retval ) throw ()
{
	pthread_exit( retval );
}

void* Thread::entry_function( void *d )
{
	entry_data *data = (entry_data *) d;

	Thread::Entry *en = data->thread_entry;
	void *args = data->args;

	delete data;

	en->Run( args );

	return NULL;
}
