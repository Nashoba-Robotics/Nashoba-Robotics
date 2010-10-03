/*
 *	socket.cpp
 *	Nashoba Robotics
 *
 *	Copyright 2010 RC Howe
 *	All Rights Reserved
 */

#include "socket.h"

#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string>

using namespace nr::net;

socket_exception::socket_exception( const char *desc ) throw ()
:	description( desc )
{
}

const char* socket_exception::what() const throw ()
{
	return description.c_str();
}

socket::socket( bool server ) throw ( socket_exception )
:	explicit_close( false ),
 	fd( -1 )
{
	memset( &address_info, 0, sizeof( address_info ) );

	if ( server )
	{
		fd = ::socket( AF_INET, SOCK_STREAM, 0 );
		if ( ! valid() )
			throw socket_exception( "Unable to create socket" );

		int reuse = 1;
		if ( setsockopt( fd, SOL_SOCKET, SO_REUSEADDR, (const char *) &reuse, sizeof( reuse ) ) == -1 )
			throw socket_exception( "Unable to create socket" );
	}
}

socket::~socket() throw ()
{
	if ( valid() && ! explicit_close )
		::close( fd );
}

class socket& socket::bind( int port ) throw ( socket_exception )
{
	if ( ! valid() )
		throw socket_exception( "Invalid Socket" );

	address_info.sin_family = AF_INET;
	address_info.sin_port = htons( port );
	address_info.sin_addr.s_addr = INADDR_ANY;

	if ( ::bind( fd, (struct sockaddr *) &address_info, sizeof( address_info )) == -1 )
		throw socket_exception( "Unable to bind socket" );

	return *this;
}

class socket& socket::listen( int max_connections ) throw ( socket_exception )
{
	if ( ! valid() )
		throw socket_exception( "Invalid Socket" );

	if ( ::listen( fd, max_connections ) == -1 )
		throw socket_exception( "Unable to listen on socket" );

	return *this;
}

class socket socket::accept() const throw ( socket_exception )
{
	if ( ! valid() )
		throw socket_exception( "Invalid Socket" );

	// The socket to return
	class socket s( false );

	// Accept the socket on the new one
	int addr_len = sizeof( address_info );
	s.fd = ::accept( fd, (struct sockaddr *) &address_info, (socklen_t *) &addr_len );

	if ( ! s.valid() )
		throw socket_exception( "Unable to accept socket" );

	return s;
}

class socket* socket::accept_ref() const throw ( socket_exception )
{
	if ( ! valid() )
		throw socket_exception( "Invalid Socket" );

	class socket *s = new class socket( false );

	int addr_len = sizeof( address_info );
	s->fd = ::accept( fd, (struct sockaddr *) &address_info, (socklen_t *) &addr_len );

	if ( ! s->valid() )
		throw socket_exception( "Unable to accept socket" );

	return s;
}

bool socket::write( const std::string &s ) const throw ( socket_exception )
{
	return ::send( fd, s.c_str(), s.size(), MSG_NOSIGNAL ) != -1;
}

size_t socket::read( std::string &buffer ) const throw ( socket_exception )
{
	// Create a temp buffer
	char *cbuf = new char[kMaxReceiveLength+1];
	memset( cbuf, 0, kMaxReceiveLength + 1 );

	// Zero the output buffer
	buffer = "";

	int status = ::recv( fd, cbuf, kMaxReceiveLength, 0 );;

	if ( status == -1 )
		throw socket_exception( "Unable to receive on socket" );
	else if ( status == 0 )
		return 0;

	buffer = cbuf;
	return status;
}

const class socket& socket::operator<<( const std::string &s ) const throw ( socket_exception )
{
	write( s );
	return *this;
}

const class socket& socket::operator>>( std::string &s ) const throw ( socket_exception )
{
	read( s );
	return *this;
}

bool socket::connect( const std::string &host, int port ) throw ( socket_exception )
{
	if ( ! valid() )
		throw socket_exception( "Invalid Socket" );

	address_info.sin_family = AF_INET;
	address_info.sin_port = htons( port );

	inet_pton( AF_INET, host.c_str(), &address_info.sin_addr );

	if ( errno == EAFNOSUPPORT )
		throw socket_exception( "Address family not known to kernel" );

	return ::connect( fd, (struct sockaddr *) &address_info, sizeof( address_info ) ) == 0;
}

void socket::close() throw ( socket_exception )
{
	if ( ::close( fd ) == -1 )
		throw socket_exception( "Error closing socket" );

	fd = -1;
}

void socket::set_nonblocking( bool nonblocking ) throw ()
{
	int options = fcntl( fd, F_GETFL );
	if ( options < 0 )
		return;

	if ( nonblocking )
		options |= O_NONBLOCK;
	else
		options &= ~O_NONBLOCK;

	fcntl( fd, F_SETFL, options );
}

bool socket::valid() const throw ()
{
	return fd >= 0;
}
