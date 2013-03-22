#include "socket.hpp"	

WSAStarter::WSAStarter() {
	get_winsock_instance();
}

SocketBase::SocketBase() : _hSocket( (SOCKET)SOCKET_ERROR ) {
}

SocketBase::SocketBase( int type, int protocol ) : _hSocket( INVALID_SOCKET ) {
	_hSocket = socket( AF_INET, type, protocol );
	if( _hSocket == INVALID_SOCKET ) {
		std::stringstream err;
		err << "Error: socket(): " << WSAGetLastError();
		throw_error( err.str() );
	}
}

void SocketBase::bind( std::string const& address, unsigned short port ) {
	memset( &_endpoint, 0, sizeof(_endpoint) );
	_endpoint.sin_family = AF_INET;
	_endpoint.sin_port = htons(port);
	_endpoint.sin_addr.s_addr = inet_addr( address.c_str() );

	if( ::bind( _hSocket, (SOCKADDR*)&_endpoint, sizeof(_endpoint) ) == SOCKET_ERROR ) {
		std::stringstream err;
		err << "Error: bind(): " << WSAGetLastError();
		throw_error( err.str() );
	}
}

void SocketBase::connect( std::string const& address, unsigned short port ) {
	memset( &_endpoint, 0, sizeof(_endpoint) );
	_endpoint.sin_family = AF_INET;
	_endpoint.sin_port = htons(port);
	_endpoint.sin_addr.s_addr = inet_addr( address.c_str() );

	if( ::connect( _hSocket, (SOCKADDR*)&_endpoint, sizeof(_endpoint) ) == SOCKET_ERROR ) {
		std::stringstream err;
		err << "Error: connect(): " << WSAGetLastError();
		throw_error( err.str() );
	}
}

void SocketBase::listen( int backlog ) {
	if( ::listen( _hSocket, backlog ) == SOCKET_ERROR ) {
		throw_error( "Error: failed to listen" );
	}
}

void SocketBase::accept( SocketBase& other ) {
	_hSocket = (SOCKET)SOCKET_ERROR;
	while( _hSocket == SOCKET_ERROR ) {
		_hSocket = ::accept( other._hSocket, NULL, NULL );
	}
}

SocketBase::~SocketBase() {
	closesocket( _hSocket );
}