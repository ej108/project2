#if !defined( SOCKET_HPP )
#define SOCKET_HPP

#include "winsock.hpp"

struct WSAStarter {
	WSAStarter();
};

class SocketBase : public WSAStarter {
private:
	SOCKET _hSocket;
	sockaddr_in _endpoint;

	SocketBase( SocketBase const& );
	SocketBase const& operator=( SocketBase const& );

public:

	SocketBase();

	SocketBase( int type, int protocol );

	void bind( std::string const& address, unsigned short port );

	void connect( std::string const& address, unsigned short port );

	void listen( int backlog = 1 );

	void accept( SocketBase& other );

	template <typename T>
	int send( T* ptr, std::size_t n = 1 ) const {
		int nBytes = n * sizeof(T);
		int nSent = ::send( _hSocket, reinterpret_cast<char const*>(ptr), nBytes, 0 );
		if( nBytes != nSent ) {
			std::stringstream err;
			err << "Error: send(): failed";
			throw_error( err.str() );
		}
		return nSent;
	}

	template <typename T>
	int recv( T* ptr, std::size_t n = 1 ) const {
		int nBytes = n * sizeof(T);
		int nRecv = ::recv( _hSocket, reinterpret_cast<char*>(ptr), nBytes, MSG_WAITALL );
		if( nBytes != nRecv ) {
			std::stringstream err;
			err << "Error: recv(): failed";
			throw_error( err.str() );
		}
		return nRecv;
	}

	~SocketBase();
};

#endif