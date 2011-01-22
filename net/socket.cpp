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

#ifdef WPILIB
#include <sockLib.h>
#endif

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <cstdlib>

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL SO_NOSIGPIPE
#endif

nr::net::socket_exception::socket_exception( const char *desc ) throw ()
:	description( desc )
{
}

const char* nr::net::socket_exception::what() const throw ()
{
	return description.c_str();
}

nr::net::socket::socket( bool server ) throw ( nr::net::socket_exception )
:	explicit_close( false ),
 	fd( -1 )
{
	memset( &address_info, 0, sizeof( address_info ) );

	if ( server )
	{
		fd = ::socket( AF_INET, SOCK_STREAM, 0 );
		if ( ! valid() )
			throw nr::net::socket_exception( "Unable to create socket" );

		int reuse = 1;
		if ( ::setsockopt( fd, SOL_SOCKET, SO_REUSEADDR, (char *) &reuse, sizeof( reuse ) ) == -1 )
			throw nr::net::socket_exception( "Unable to create socket" );
	}
}

nr::net::socket::~socket() throw ()
{
	if ( valid() && ! explicit_close )
		::close( fd );
}

nr::net::socket& nr::net::socket::bind( int port ) throw ( nr::net::socket_exception )
{
	if ( ! valid() )
		throw nr::net::socket_exception( "Invalid Socket" );

	address_info.sin_family = AF_INET;
	address_info.sin_port = htons( port );
	address_info.sin_addr.s_addr = INADDR_ANY;

	if ( ::bind( fd, (struct sockaddr *) &address_info, sizeof( address_info )) == -1 )
		throw nr::net::socket_exception( "Unable to bind socket" );

	return *this;
}

nr::net::socket& nr::net::socket::listen( int max_connections ) throw ( nr::net::socket_exception )
{
	if ( ! valid() )
		throw nr::net::socket_exception( "Invalid Socket" );

	if ( ::listen( fd, max_connections ) == -1 )
		throw nr::net::socket_exception( "Unable to listen on socket" );

	return *this;
}

nr::net::socket nr::net::socket::accept() const throw ( nr::net::socket_exception )
{
	if ( ! valid() )
		throw nr::net::socket_exception( "Invalid Socket" );

	// The socket to return
	nr::net::socket s( false );

	// Accept the socket on the new one
	int addr_len = sizeof( address_info );
	s.fd = ::accept( fd, (struct sockaddr *) &address_info, (int *) &addr_len );

	if ( ! s.valid() )
		throw nr::net::socket_exception( "Unable to accept socket" );

	return s;
}

nr::net::socket* nr::net::socket::accept_ref() const throw ( nr::net::socket_exception )
{
	if ( ! valid() )
		throw nr::net::socket_exception( "Invalid Socket" );

	nr::net::socket *s = new nr::net::socket( false );

	int addr_len = sizeof( address_info );
	s->fd = ::accept( fd, (struct sockaddr *) &address_info, (int *) &addr_len );

	if ( ! s->valid() )
		throw nr::net::socket_exception( "Unable to accept socket" );

	return s;
}

bool nr::net::socket::write( const std::string &s ) const throw ( nr::net::socket_exception )
{
	return ::send( fd, s.c_str(), s.size(), 0 ) != -1;
}

size_t nr::net::socket::read( std::string &buffer ) const throw ( nr::net::socket_exception )
{
	// Create a temp buffer
	char *cbuf = new char[kMaxReceiveLength+1];
	memset( cbuf, 0, kMaxReceiveLength + 1 );

	// Zero the output buffer
	buffer = "";

	int status = ::recv( fd, cbuf, kMaxReceiveLength, 0 );;

	if ( status == -1 )
		throw nr::net::socket_exception( "Unable to receive on socket" );
	else if ( status == 0 )
		return 0;

	buffer = cbuf;
	return status;
}

const nr::net::socket& nr::net::socket::operator<<( const std::string &s ) const throw ( nr::net::socket_exception )
{
	write( s );
	return *this;
}

const nr::net::socket& nr::net::socket::operator>>( std::string &s ) const throw ( nr::net::socket_exception )
{
	read( s );
	return *this;
}

bool nr::net::socket::connect( const std::string &host, int port ) throw ( nr::net::socket_exception )
{
	if ( ! valid() )
		throw nr::net::socket_exception( "Invalid Socket" );

	address_info.sin_family = AF_INET;
	address_info.sin_port = htons( port );

	inet_pton( AF_INET, host.c_str(), &address_info.sin_addr );

	if ( errno == EAFNOSUPPORT )
		throw nr::net::socket_exception( "Address family not known to kernel" );

	return ::connect( fd, (struct sockaddr *) &address_info, sizeof( address_info ) ) == 0;
}

void nr::net::socket::close() throw ( nr::net::socket_exception )
{
	if ( ::close( fd ) == -1 )
		throw nr::net::socket_exception( "Error closing socket" );

	fd = -1;
}

void nr::net::socket::set_nonblocking( bool nonblocking ) throw ()
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

bool nr::net::socket::valid() const throw ()
{
	return fd >= 0;
}
