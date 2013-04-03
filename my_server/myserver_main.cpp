#include <iostream>
#include <memory>

using namespace std;
#include <socket.hpp>

int main() {
	try {
		cout << "Server..." << endl;
		SocketBase base( SOCK_STREAM, IPPROTO_TCP );
		base.bind( "127.0.0.1", 51000 );

		base.listen();

		cout << "Waiting for a connection" << endl;
		SocketBase accepted;
		accepted.accept( base );
		cout << "Client connected" << endl;

		int i;
		accepted.recv( &i );
		cout << "Received from client: " << i << endl;
		cout << "Doubling and sending to client" << endl;
		i *= 2;
		accepted.send( &i );

		std::string::size_type length;
		accepted.recv( &length );
		std::unique_ptr<char[]> buffer( new char[length+1] );
		accepted.recv( buffer.get(), length );
		buffer[length] = '\0';

		cout << "Message received from client: " << buffer.get() << endl;
	}
	catch( std::runtime_error const& e ) {
		cerr << e.what() << endl;
	}
	catch( std::exception const& e ) {
		cerr << e.what() << endl;
	}
}