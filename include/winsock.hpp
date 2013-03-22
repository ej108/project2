#if !defined( WINSOCK_HPP )
#define WINSOCK_HPP

#include <memory>
#include <sstream>
#include <string>

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment( lib, "ws2_32" )

#include "utility.hpp"


class WinSock {
public:
	static WORD const _version = MAKEWORD( 2, 2 );
	WSADATA _wsaData;
	static bool _init;


	WinSock();


	~WinSock();
};

WinSock& get_winsock_instance();

#endif