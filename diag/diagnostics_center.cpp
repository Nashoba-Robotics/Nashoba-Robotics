/*
 *  diagnostics_center.cpp
 *  Nashoba Robotics 2011
 *
 *  Copyright 2010 RC Howe
 *  All Rights Reserved
 */

#include "diagnostics_center.h"
#include "../conc/thread_exception.h"
#include <iostream>
#include <sstream>
#include <ctime>

using namespace nr::diag;

static diagnostics_center *shared_diagnostics_center = NULL;
static const char* headers = "charset=ASCII\r\nServer: NRWeb/1.0\r\n";
static const char* source = "<html><head><style>body{font-family:monospace}</style><script>var r=new XMLHttpRequest();function t(){u();setTimeout(t,250);}function u(){r.onreadystatechange=function(){if(r.readyState==4&&r.status==200){document.getElementById('devices').innerHTML=r.responseText.replace('\\n','<br/>');}};r.open('GET','/devices');r.send(null)}</script></head><body onload='t()'><h1>Devices</h1><div id='devices'></div></body></html>";

static inline const std::string http_format( const std::string& status, const std::string &headers, const std::string &content, const std::string &content_type = "text/plain" )
{
	std::stringstream ss;
	ss << "HTTP/1.0 ";
	ss << status;
	ss << "\r\n";
	ss << headers;
	ss << "Content-Length: ";
	ss << content.size();
	ss << "\r\n";
	ss << "Content-Type: ";
	ss << content_type;
	ss << "\r\n\r\n";
	ss << content;

	return ss.str();
}

diagnostics_center::diagnostics_center() throw ()
: thread( this ), running( true )
{
	try {
		thread.start();
	}

	catch ( nr::conc::thread_exception &e ) {
		std::cerr << "Unable to start diagnostics center: " << e.what() << std::endl;
		running = false;
	}
}

diagnostics_center::~diagnostics_center() throw ()
{
}

void diagnostics_center::register_device( observable &device ) throw ()
{
	register_device( &device );
}

void diagnostics_center::register_device( observable *device ) throw ()
{
	if ( device == NULL )
		return;

	std::vector<observable*>::iterator it;
	for ( it = devices.begin(); it != devices.end(); it++ )
	{
		if ( device == *it )
			return;
	}

	SYNCHRONIZED(devices_mutex) {
		devices.push_back( device );
	}
}

void diagnostics_center::run( void *userinfo ) throw ()
{
	// TODO: This is the diagnostics server code.
	// Might want to fix this up a little.

	try {
		// Create the server socket
		nr::net::socket server( true );
		server.bind( 1100 ).listen();

		while ( true )
		{
			// Blocks until a client connects
			nr::net::socket client = server.accept();
			handle_client( client );
		}
	}

	catch ( ... )
	{
		std::cerr << "Unable to start diagnostics server" << std::endl;
	}
}

void diagnostics_center::handle_client( nr::net::socket &client )
{
	try {
		std::string s = "";

		size_t len;
		try {
			len = client.read( s );
		}

		catch ( nr::net::socket_exception &e )
		{
			return;
		}

		if ( len == 0 )
			// The client disconnected
			return;

		if ( s.size() >= 12 && s.substr( 0, 12 ) == "GET /devices" )
		{
			std::stringstream ss;
			time_t now = time( NULL );

			// Generate the devices list and write it to the socket
			std::vector<observable*>::iterator it;
			for ( it = devices.begin(); it != devices.end(); it++ )
			{
				ss << now;
				ss << ',';
				ss << '"';
				ss << (*it)->identifier();
				ss << "\",";
				ss << (*it)->value();
				ss << ',';
				ss << ((*it)->setable() ? "YES" : "NO");
				ss << '\n';
			}

			client.write( http_format( "200 OK", headers, ss.str(), "text/csv" ) );
		}

		else if ( s.size() >= 5 && s.substr( 0, 5 ) == "GET /" )
		{
			client.write( http_format( "200 OK", headers, source, "text/html" ) );
		}

		else if ( s.size() >= 6 && s.substr( 0, 6 ) == "POST /" )
		{
			client.write( http_format( "400 Bad Request", headers, "Bad Request" ) );
		}

		else
		{
			client.write( http_format( "400 Bad Request", headers, "Bad Request" ) );
		}
	}

	catch ( ... )
	{
	}
}

diagnostics_center& diagnostics_center::get_shared_instance() throw ()
{
	if ( shared_diagnostics_center == NULL )
		shared_diagnostics_center = new diagnostics_center();

	return *shared_diagnostics_center;
}
