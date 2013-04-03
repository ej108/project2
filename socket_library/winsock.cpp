#include <winsock.hpp>

bool WinSock::_init = false;

WinSock::WinSock() {
	if( _init ) {
		return;
	}

	// Winsock v2.2
	int iResult = WSAStartup( _version, &_wsaData );
	if( iResult != NO_ERROR ) {
		std::stringstream err;
		err << "WinSock(): WSAStartup failed, error code #" << WSAGetLastError();
		throw_error( err.str() );
	}

	_init = true;

	// Is there a suitable WinSock dll?
	if( LOBYTE( _wsaData.wVersion ) != 2 || HIBYTE( _wsaData.wVersion ) != 2 ) {
		throw_error( "WinSock(): no suitable DLL" );
	}

	unsigned long nProtocols = 0;
	WSAEnumProtocols( NULL, NULL, &nProtocols );

	std::unique_ptr< WSAPROTOCOL_INFOW[] > buffer( new WSAPROTOCOL_INFOW[nProtocols] );
	if( !buffer ) {
		throw_error( "WinSock(): failed to initialize buffer" );
	}

	// Number of available protocols
	int desired[2] = { IPPROTO_TCP, IPPROTO_UDP };
	iResult = WSAEnumProtocols( desired, buffer.get(), &nProtocols );
	if( iResult == SOCKET_ERROR ) {
		throw_error( "WinSock(): no TCP or UDP protocol" );
	}
}

WinSock::~WinSock() {
	if( _init ) {
		WSACleanup();
	}
}


WinSock& get_winsock_instance() {
	static WinSock ws;
	return ws;
}