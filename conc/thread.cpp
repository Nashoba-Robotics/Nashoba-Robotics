/*
 *  thread.cpp
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
	entry_data( thread::entry *e, void *a ) : thread_entry( e ), args( a ) {}

	thread::entry *thread_entry;
	void *args;
};

thread::thread( entry *en ) throw ()
: entry_point( en )
{
};

thread::~thread() throw ()
{
}

void thread::Start( void *userinfo ) throw ( thread_exception )
{
	entry_data *ed = new entry_data( entry_point, userinfo );
	if ( 0 != ::pthread_create( &raw_thread, NULL,
			thread::entry_function, (void *) ed ) )
	{
		throw thread_exception( "Unable to create thread" );
	}
}

void* thread::Join() throw ( thread_exception )
{
	void *ptr = NULL;
	if ( 0 != ::pthread_join( raw_thread, &ptr ) )
		throw thread_exception( "Unable to join thread" );

	return ptr;
}

void thread::Sleep( unsigned int secs ) throw ()
{
	struct timespec sleep_time, remaining_time;
	sleep_time.tv_sec = secs;
	
	nanosleep( &sleep_time, &remaining_time );
}

void thread::Stop( int signal )
{
	pthread_kill( raw_thread, signal );
}

void thread::Exit( void *retval ) throw ()
{
	pthread_exit( retval );
}

void* thread::entry_function( void *d )
{
	entry_data *data = (entry_data *) d;

	thread::entry *en = data->thread_entry;
	void *args = data->args;

	delete data;

	en->Run( args );

	return NULL;
}
