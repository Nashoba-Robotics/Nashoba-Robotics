/*
 *	thread_exception.cpp
 *	Nashoba Robotics 2011
 *
 *	Copyright 2010 RC Howe
 *	All Rights Reserved
 */

#include "thread_exception.h"

using namespace nr::conc;

thread_exception::thread_exception( const std::string& msg ) throw ()
: description( msg )
{
}

thread_exception::~thread_exception() throw ()
{
}

const char* thread_exception::what() const throw ()
{
	return this->description.c_str();
}
