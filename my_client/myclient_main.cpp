#include <iostream>

using namespace std;
#include <socket.hpp>

int main() {
	try {
		cout << "Client..." << endl;
		SocketBase base( SOCK_STREAM, IPPROTO_TCP );
		base.connect( "127.0.0.1", 51000 );

		cout << "Client connected" << endl;

		int myInt = 108;

		base.send<int>( &myInt );
		base.recv<int>( &myInt );

		cout << "2 x 108 = " << myInt << endl;

		cout << "Enter a message: ";
		std::string message;
		getline( cin, message );
		auto const length = message.length();
		base.send( &length );
		base.send( message.data(), length );
	}
	catch( std::runtime_error const& e ) {
		cerr << e.what() << endl;
	}
}