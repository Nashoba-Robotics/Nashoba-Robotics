/*
 *	socket.h
 *	Nashoba Robotics
 *
 *	Copyright 2010 RC Howe
 *	All Rights Reserved
 */

#pragma once

#include <typeinfo>
#include <string>

#include <netinet/in.h>

namespace nr
{
	namespace net
	{
		/**
		 *	A class to represent a socket exception
		 */
		class socket_exception : public std::exception
		{
		public:
			/**
			 *	Creates a new socket exception
			 *	@param desc A description of the event that triggered the exception
			 */
			socket_exception( const char *desc ) throw ();
			virtual ~socket_exception() throw () {}
			
			/**
			 *	@return A description of the event that triggered the exception
			 */
			const char* what() const throw ();

		private:
			std::string description;
		};
		
		/**
		 *	A class that represents a socket.
		 *
		 *	A server socket can be easily created by creating it as a server socket and calling .bind( port ).listen(), and then accepting connections
		 *	Note that sockets are automatically closed when they go out of scope, unless explicit_close is set to true
		 */
		class socket
		{
		public:
			/**
			 *	Creates a new socket. If `server', the socket is created as a TCP server socket, else a TCP client
			 *	@param server Whether to create as a server TCP socket or a client TCP socket
			 */
			socket( bool server = false ) throw ( socket_exception );
			virtual ~socket() throw ();

			// Server socket
			/**
			 *	Binds a server socket to the given port
			 *	@param port The port to bind to
			 *	@return The socket the method was called on, for method chaining
			 */
			socket& bind( int port ) throw ( socket_exception );
			
			/**
			 *	Listens on a bound socket
			 *	@param The maximum number of connections to backlog before dropping connections
			 *	@return The socket the method was called on, for method chaining
			 */
			socket& listen( int max_connections = 10 ) throw ( socket_exception );
			
			/**
			 *	Accepts a new connection from this socket
			 *	@return An initialized connection
			 */
			socket accept() const throw ( socket_exception );
			
			/**
			 *	Accepts a new connection from this socket as a pointer
			 *	@return A pointer to an initialized connection
			 */
			socket* accept_ref() const throw ( socket_exception );

			// Client sockets
			/**
			 *	Connects this socket to the given IP address
			 *	@param host The IP to connect to
			 *	@param port The port to connect to
			 *	@return Whether the connection was successful
			 */
			bool connect( const std::string& host, int port ) throw ( socket_exception );

			// Data Transmission
			/**
			 *	Writes data on a socket
			 *	@param The data to write
			 *	@return Whether transmission was successful
			 */
			bool write( const std::string& ) const throw ( socket_exception );
			
			/**
			 *	Reads data on a socket
			 *	@param A buffer to put the data in
			 *	@return The size of data read
			 */
			size_t read( std::string& ) const throw ( socket_exception );
			
			/**
			 *	Writes data, in the syntax of a stream operator
			 *	@param The data to write
			 *	@return This socket
			 */
			const socket& operator<<( const std::string& ) const throw ( socket_exception );
			
			/**
			 *	Reads data, in the syntax of a stream operator
			 *	@param The buffer to read into
			 *	@return This socket
			 */
			const socket& operator>>( std::string& ) const throw ( socket_exception );
			
			/**
			 *	Explicitly closes the socket.
			 *	Sockets are automatically closed when they go out of scope unless explicit_close is set
			 */
			void close() throw ( socket_exception );

			// Validity
			/**
			 *	@return Whether or not the socket represents a valid socket
			 */
			bool valid() const throw ();

			// Options
			/**
			 *	Sets whether or not the socket is nonblocking
			 *	@param nonblocking Whether or not the socket is nonblocking
			 */
			void set_nonblocking( bool nonblocking ) throw ();
			
			/**
			 *	Whether or not the socket closes when it goes out of scope or requires an explicit close
			 */
			bool explicit_close;

			static const size_t kMaxReceiveLength = 4096;

		private:
			int fd;
			struct ::sockaddr_in address_info;
		};
	}
}
