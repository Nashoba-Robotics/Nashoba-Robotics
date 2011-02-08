/*
 *	ThreadException.cpp
 *	Nashoba Robotics 2011
 *
 *	Copyright 2010 RC Howe
 *	All Rights Reserved
 */

#include "ThreadException.h"

using namespace nr::conc;

ThreadException::ThreadException( const std::string& msg ) throw ()
: description( msg )
{
}

ThreadException::~ThreadException() throw ()
{
}

const char* ThreadException::what() const throw ()
{
	return this->description.c_str();
}
