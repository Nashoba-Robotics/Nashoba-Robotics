/*
 *	thread_exception.h
 *	Nashoba Robotics 2011
 *
 *	Copyright 2010 RC Howe
 *	All Rights Reserved
 */

#pragma once

#include <string>

namespace nr {
	namespace conc
	{
		/**
		 *  @brief A thread exception
		 */
		class thread_exception : public std::exception
		{
		public:
			/**
			 *  Creates a new thread exception with the given message
			 *  @param msg The error message
			 */
			explicit thread_exception( const std::string& msg ) throw ();

			/**
			 *  Cleans up any resources used by this exception
			 */
			virtual ~thread_exception() throw ();

			/**
			 *  Returns the description string
			 *  @return The error message given when the exception was thrown.
			 */
			const char* what() const throw ();

		private:
			const std::string description;
		};
	}
}
