/*
 *	socket.h
 *	Nashoba Robotics
 *
 *	Copyright 2010 RC Howe
 *	All Rights Reserved
 */

#include <typeinfo>
#include <string>

#include <netinet/in.h>

namespace nr
{
	namespace net
	{
		class socket_exception : public std::exception
		{
		public:
			socket_exception( const char *desc ) throw ();
			virtual ~socket_exception() throw () {}

			const char* what() const throw ();

		private:
			std::string description;
		};

		class socket
		{
		public:
			socket( bool server = false ) throw ( socket_exception );
			virtual ~socket() throw ();

			// Server socket
			socket& bind( int port ) throw ( socket_exception );
			socket& listen( int max_connections = 10 ) throw ( socket_exception );
			socket accept() const throw ( socket_exception );
			socket* accept_ref() const throw ( socket_exception );

			// Client sockets
			bool connect( const std::string& host, int port ) throw ( socket_exception );

			// Data Transmission
			bool write( const std::string& ) const throw ( socket_exception );
			size_t read( std::string& ) const throw ( socket_exception );

			const socket& operator<<( const std::string& ) const throw ( socket_exception );
			const socket& operator>>( std::string& ) const throw ( socket_exception );

			void close() throw ( socket_exception );

			// Validity
			bool valid() const throw ();

			// Options
			void set_nonblocking( bool nonblocking ) throw ();

			bool explicit_close;

			static const size_t kMaxReceiveLength = 4096;

		private:
			int fd;
			struct ::sockaddr_in address_info;
		};
	}
}
